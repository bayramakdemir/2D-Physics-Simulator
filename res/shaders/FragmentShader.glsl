#version 330 core
out vec4 FragColor;
 
void main()
{
    vec2 pos = vec2(gl_FragCoord.x/640,gl_FragCoord.y/640);
    pos.x = pos.x * 2.0f - 1.0f;
    pos.y = pos.y * 2.0f - 1.0f;
    if( (pos.x * pos.x + pos.y*pos.y) < 0.1f ){
        FragColor = vec4(1.0f, 1.0f , 1.0f, 1.0f);
    }else
        FragColor = vec4(1.0f, 1.0f , 1.0f, 1.0f);
}