#version 330 core

in vec3 LocalPosition;
in vec4 Color;
in float Thickness;
in float Fade;

void main() {
	// Calculate distance and fill circle with white
	float distance = 1.0 - length(LocalPosition);
	float circle = smoothstep(0.0, Fade, distance);
	circle *= smoothstep(Thickness + Fade, Thickness, distance);

	if (circle == 0.0)
		discard;

	// Set output color
	gl_FragColor = Color;
	gl_FragColor.a *= circle;
}
