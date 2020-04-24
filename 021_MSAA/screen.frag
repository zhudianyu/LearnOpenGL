#version 330 core

in vec2 TexCoords;
out vec4 FragColor;
uniform sampler2D screenTexture;

void main()
{

    vec3 col = texture(screenTexture, TexCoords).rgb;
    float grayscale = 0.2126f * col.r + 0.7152f * col.g + 0.0722f * col.b;
    FragColor = vec4(vec3(grayscale), 1.0f);
}