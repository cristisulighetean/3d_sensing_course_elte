#version 330 core

// pipeline-b�l bej�v� per-fragment attrib�tumok
in vec3 vs_out_pos;

out vec4 fs_out_col;

void main()
{
	fs_out_col = vec4(vs_out_pos, 1);
}