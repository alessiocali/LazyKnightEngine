#version 330 core
in vec2 TextureCoordinates;

out vec4 FragColor;

uniform sampler2D Albedo;

void main()
{
    FragColor = texture(Albedo, TextureCoordinates);
}