#version 330 core

in vec4 Pos;
in vec2 TexCoord;

out vec4 FragColor;

uniform sampler2D texture1;

float near = 0.1f;
float far = 100.f;

float linearizeDepth(float depth);

void main()
{
//    float Depth = linearizeDepth(gl_FragCoord.z) / far;
//    FragColor = vec4(vec3(Depth), 1.0f);
    FragColor = texture(texture1, TexCoord);
}

float linearizeDepth(float depth)
{
    float z = depth * 2.0f - 1.0f;
    return (2.0f * near * far) / (far + near - z * (far - near));
}