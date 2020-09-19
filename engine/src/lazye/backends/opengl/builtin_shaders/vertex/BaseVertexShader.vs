#version 330 core
layout (location = 0) in vec3 Position;
layout (location = 1) in vec2 InTextureCoordinates;

out vec2 TextureCoordinates;

uniform mat4 Transform;

void main()
{
    gl_Position = Transform * vec4(Position, 1.0);
    TextureCoordinates = InTextureCoordinates;
}