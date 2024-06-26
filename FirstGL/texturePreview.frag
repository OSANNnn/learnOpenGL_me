#version 330 core

in vec3 Pos;
in vec2 TexCoord;

out vec4 FragColor;

uniform sampler2D uTexture;

void main()
{
    //FragColor = vec4(TexCoord, 1.0f, 1.0f);
    FragColor = texture(uTexture, TexCoord);
}