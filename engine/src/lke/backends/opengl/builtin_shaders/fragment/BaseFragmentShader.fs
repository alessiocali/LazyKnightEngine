#version 330 core
in vec2 TextureCoordinates;

out vec4 FragColor;

uniform bool UseAlbedo = false;

uniform vec4 FallbackColor;
uniform sampler2D Albedo;

vec4 ComputeColor();

void main()
{
    FragColor = ComputeColor();
}

vec4 ComputeColor()
{
    if (UseAlbedo)
    {
        return texture2D(Albedo, TextureCoordinates);
    }
    else
    {
        return FallbackColor;
    }
}