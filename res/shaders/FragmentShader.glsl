#version 330 core
out vec4 FragColor;
in vec4 color;

void main()
{
	gl_FragColor = color;
}