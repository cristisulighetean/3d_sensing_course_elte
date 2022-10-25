#pragma once

// C++ includes
#include <memory>

// GLEW
#include <GL/glew.h>

// SDL
#include <SDL.h>
#include <SDL_opengl.h>

// GLM
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform2.hpp>

#include "gCamera.h"

#include "ProgramObject.h"
#include "BufferObject.h"
#include "VertexArrayObject.h"
#include "TextureObject.h"

class CMyApp
{
public:
  CMyApp(void);
  ~CMyApp(void);

  bool Init();
  void Clean();

  void Update();
  void Render();

  void KeyboardDown(SDL_KeyboardEvent&);
  void KeyboardUp(SDL_KeyboardEvent&);
  void MouseMove(SDL_MouseMotionEvent&);
  void MouseDown(SDL_MouseButtonEvent&);
  void MouseUp(SDL_MouseButtonEvent&);
  void MouseWheel(SDL_MouseWheelEvent&);
  void Resize(int, int);
protected:
  // helper methods
  void TextureFromFileAttach(const char* filename, GLuint role) const;

  // shader variables
  ProgramObject		m_program;
  ProgramObject		m_programSkybox;

  // vertex array object and related stuff for the cube geometry
  VertexArrayObject	m_vao;
  IndexBuffer			m_gpuBufferIndices;
  ArrayBuffer			m_gpuBufferPos;

  // camera
  gCamera				m_camera;

  // raw OpenGL stuff
  GLuint				m_skyboxTexture;
};

