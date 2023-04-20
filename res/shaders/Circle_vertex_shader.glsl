#version 330 core

layout(location = 0) in vec3 a_WorldPosition;
layout(location = 1) in vec3 a_LocalPosition;
layout(location = 2) in vec4 a_Color;
layout(location = 3) in float a_Thickness;
layout(location = 4) in float a_Fade;

uniform mat4 u_ViewProjection;

out vec3 LocalPosition;
out vec4 Color;
out float Thickness;
out float Fade;

void main() {
	LocalPosition = a_LocalPosition;
	Color = a_Color;
	Thickness = a_Thickness;
	Fade = a_Fade;

	gl_Position = u_ViewProjection * vec4(a_WorldPosition, 1.0);
}