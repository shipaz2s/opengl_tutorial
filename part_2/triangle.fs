#version 330 core

in vec3 color_pos;
out vec4 color;

void main()
{
	//color = vec4(ourColor, 1.0f);
	color = vec4(color_pos, 1.0f);
}