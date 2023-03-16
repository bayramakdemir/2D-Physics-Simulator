#version 330 core
out vec4 FragColor;

void main()
{
    float sinx = sin(gl_FragCoord.x/400);
    float siny= cos(gl_FragCoord.y/400);
    FragColor = vec4(1.0f, sinx , siny, 1.0f);
}