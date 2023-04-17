#version 330 core
out vec4 FragColor;
//in float radius;
//in vec2 screenPos;

in vec3 ourColor;
in vec2 TexCoord;
uniform sampler2D ourTexture;

void main() {
    vec4 color = texture(ourTexture, TexCoord);
    if (color.x == 0.0f)
        discard;
    gl_FragColor = color;
}