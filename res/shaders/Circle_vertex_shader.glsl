#version 330 core
layout (location = 0) in vec4 p_Pos;
layout(location = 1) in vec3 aColor;
layout(location = 2) in vec2 aTexCoord;

uniform mat4 u_Model;
uniform mat4 u_ViewProjection;

out vec3 ourColor;
out vec2 TexCoord;

void main()
{
    //pass to fragment shader
    gl_Position = u_ViewProjection * u_Model * p_Pos;
    ourColor = aColor;
    TexCoord = aTexCoord;
}