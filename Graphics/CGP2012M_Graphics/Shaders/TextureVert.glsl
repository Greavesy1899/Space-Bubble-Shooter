#version 440 core
layout (location=0) in vec3 Position;
layout (location=1) in vec3 vColour;
layout (location=2) in vec2 texCoord;

out vec3 Colour;
out vec2 textureCoordinate;

uniform mat4 WorldMatrix;

void main()
{

	gl_Position = WorldMatrix * vec4(Position, 1.0);
	Colour = vColour;
	textureCoordinate = vec2(texCoord.x, 1 - texCoord.y);

} 