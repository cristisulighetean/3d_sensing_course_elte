#include "MyApp.h"

#include <math.h>
#include <vector>

#include <array>
#include <list>
#include <tuple>
#include <imgui/imgui.h>

#include <Eigen/Dense>
#include <SO3.hpp>

CMyApp::CMyApp(void)
{
  m_camera.SetView(glm::vec3(5, 5, 5), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));
  srand(time(0));
}


CMyApp::~CMyApp(void)
{
  std::cout << "dtor!\n";
}

bool CMyApp::Init()
{
  glClearColor(0.125f, 0.25f, 0.5f, 1.0f);

  glEnable(GL_CULL_FACE);
  glEnable(GL_DEPTH_TEST);

  m_program.AttachShaders({
    { GL_VERTEX_SHADER, "myVert.vert"},
    { GL_FRAGMENT_SHADER, "myFrag.frag"}
    });

  m_program.BindAttribLocations({
    { 0, "vs_in_pos" },
    { 1, "vs_in_col" }	
    });

  m_program.LinkProgram();

  m_programSkybox.Init(
    {
      { GL_VERTEX_SHADER, "skybox.vert" },
      { GL_FRAGMENT_SHADER, "skybox.frag" }
    },
  {
    { 0, "vs_in_pos" },	
  }
  );

  m_gpuBufferPos.BufferData(
    std::vector<glm::vec3>{
    // backface
    glm::vec3(-1, -1, -1),
      glm::vec3(1, -1, -1),
      glm::vec3(1, 1, -1),
      glm::vec3(-1, 1, -1),
      //frontface
      glm::vec3(-1, -1, 1),
      glm::vec3(1, -1, 1),
      glm::vec3(1, 1, 1),
      glm::vec3(-1, 1, 1),

  }
  );

  m_gpuBufferIndices.BufferData(
    std::vector<int>{
    0, 1, 2,
      2, 3, 0,
      4, 6, 5,
      6, 4, 7,
      0, 3, 4,
      4, 3, 7,
      1, 5, 2,
      5, 6, 2,
      1, 0, 4,
      1, 4, 5,
      3, 2, 6,
      3, 6, 7,
  }
  );

  m_vao.Init(
    {
      { CreateAttribute<		0,			
                  glm::vec3,				
                  0,						    
                  sizeof(glm::vec3)	
                >, m_gpuBufferPos },
    },
    m_gpuBufferIndices
  );

  // skybox
  glEnable(GL_TEXTURE_CUBE_MAP_SEAMLESS);

  glGenTextures(1, &m_skyboxTexture);
  glBindTexture(GL_TEXTURE_CUBE_MAP, m_skyboxTexture);

  glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
  glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
  glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

  TextureFromFileAttach("xpos.png", GL_TEXTURE_CUBE_MAP_POSITIVE_X);
  TextureFromFileAttach("xneg.png", GL_TEXTURE_CUBE_MAP_NEGATIVE_X);
  TextureFromFileAttach("ypos.png", GL_TEXTURE_CUBE_MAP_POSITIVE_Y);
  TextureFromFileAttach("yneg.png", GL_TEXTURE_CUBE_MAP_NEGATIVE_Y);
  TextureFromFileAttach("zpos.png", GL_TEXTURE_CUBE_MAP_POSITIVE_Z);
  TextureFromFileAttach("zneg.png", GL_TEXTURE_CUBE_MAP_NEGATIVE_Z);

  glBindTexture(GL_TEXTURE_CUBE_MAP, 0);

  // camera
  m_camera.SetProj(45.0f, 640.0f / 480.0f, 0.01f, 1000.0f);

  return true;
}

void CMyApp::TextureFromFileAttach(const char* filename, GLuint role) const
{
  SDL_Surface* loaded_img = IMG_Load(filename);

  int img_mode = 0;

  if (loaded_img == 0)
  {
    std::cout << "[TextureFromFile] Error loading the image: " << filename << std::endl;
    return;
  }

#if SDL_BYTEORDER == SDL_LIL_ENDIAN
  if (loaded_img->format->BytesPerPixel == 4)
    img_mode = GL_BGRA;
  else
    img_mode = GL_BGR;
#else
  if (loaded_img->format->BytesPerPixel == 4)
    img_mode = GL_RGBA;
  else
    img_mode = GL_RGB;
#endif

  glTexImage2D(role, 0, GL_RGBA, loaded_img->w, loaded_img->h, 0, GL_RGBA, GL_UNSIGNED_BYTE, loaded_img->pixels);

  SDL_FreeSurface(loaded_img);
}

void CMyApp::Clean()
{
  glDeleteTextures(1, &m_skyboxTexture);
}

double t = 0;

void CMyApp::Update()
{
  static Uint32 last_time = SDL_GetTicks();
  float delta_time = (SDL_GetTicks() - last_time) / 1000.0f;

  t += delta_time;
  m_camera.Update(delta_time);

  last_time = SDL_GetTicks();
}

void CMyApp::Render()
{
  using namespace Geometry;
  // Tasks:
  //   1. SO3::Log can still be further improved + HW
  //   2. Generate two new states once interpolation finished in "time_to_interpolate" time, then continue
  //   3. Implement Cubic interpolation between three states!
  //      (can be implemented using three linear interpolations)  [+2 pts]
  //      - SO3::interpolate is linear interpolation
  //      - SO3::cubic_interpolate(R_0, R_1, R_2, t) TODO
  //   4. Implement more complicated spline interpolation (piecewise and/or higher order, ..)  [+3..5 pts]

  // initial two states for linear interpolation
  static Mat3 R_0 = Mat3::Identity();
  static Mat3 R_1 = Eigen::Quaterniond::UnitRandom().toRotationMatrix();
  
  const double time_to_interpolate = 3; // seconds

  if (t > time_to_interpolate) {
    R_0 = R_1;
    R_1 = Eigen::Quaterniond::UnitRandom().toRotationMatrix();

    // reset timer
    t = 0;
  }

  // interpolate
  Mat3 R = SO3::interpolate(R_0, R_1, t / time_to_interpolate);

  // convert Eigen matrix to glm matrix
  glm::mat4 cubeRotation;
  auto map_to_glm = Eigen::Map<Eigen::Matrix4f>(&cubeRotation[0].x);
  map_to_glm.setIdentity();
  map_to_glm.topLeftCorner<3, 3>() = R.cast<float>();
  
  //////////////////
  // display cube //
  //////////////////
  
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  m_vao.Bind();

  m_program.Use();
  
  glm::mat4 cubeWorld = 
    cubeRotation *
    glm::scale(glm::vec3(-1, -1, -1));
  m_program.SetUniform("MVP", m_camera.GetViewProj() * cubeWorld);
  glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, nullptr);

  ////////////////////
  // display skybox //
  ////////////////////

  GLint prevDepthFnc;
  glGetIntegerv(GL_DEPTH_FUNC, &prevDepthFnc);

  glDepthFunc(GL_LEQUAL);

  m_vao.Bind();

  m_programSkybox.Use();
  m_programSkybox.SetUniform("MVP", m_camera.GetViewProj() * glm::translate(m_camera.GetEye()));

  glActiveTexture(GL_TEXTURE0);
  glBindTexture(GL_TEXTURE_CUBE_MAP, m_skyboxTexture);
  glUniform1i(m_programSkybox.GetLocation("skyboxTexture"), 0);

  glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, nullptr);

  glDepthFunc(prevDepthFnc);

  /////////////////
  // display GUI //
  /////////////////
  ImGui::ShowTestWindow();
}

void CMyApp::KeyboardDown(SDL_KeyboardEvent& key)
{
  m_camera.KeyboardDown(key);
}

void CMyApp::KeyboardUp(SDL_KeyboardEvent& key)
{
  m_camera.KeyboardUp(key);
}

void CMyApp::MouseMove(SDL_MouseMotionEvent& mouse)
{
  m_camera.MouseMove(mouse);
}

void CMyApp::MouseDown(SDL_MouseButtonEvent& mouse)
{
}

void CMyApp::MouseUp(SDL_MouseButtonEvent& mouse)
{
}

void CMyApp::MouseWheel(SDL_MouseWheelEvent& wheel)
{
}

void CMyApp::Resize(int _w, int _h)
{
  glViewport(0, 0, _w, _h);

  m_camera.Resize(_w, _h);
}