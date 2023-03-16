#version 330 core
layout (location = 0) in vec3 p_Pos;
uniform vec4 u_Pos;
void main()
{
    gl_Position = vec4(p_Pos.x * u_Pos.x, p_Pos.y * u_Pos.y, p_Pos.z * u_Pos.z, 1.0 * u_Pos.w);
}