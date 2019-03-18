#version 440 core
layout (location=0) in vec3 Position;
layout (location=1) in vec3 vColour;
layout (location=2) in vec2 texCoord;

out vec4 vs_pos;
out vec3 vs_col;
out vec2 vs_uv;

uniform mat4 ViewMatrix;
uniform mat4 ProjectionMatrix;
uniform mat4 WorldMatrix;

void main()
{

	gl_Position = ProjectionMatrix * ViewMatrix * WorldMatrix * vec4(Position, 1.0);
	vs_pos = ProjectionMatrix * ViewMatrix * WorldMatrix * vec4(Position, 1.0);
	vs_col = vColour;
	vs_uv = texCoord;
	vs_uv = vec2(texCoord.x, 1 - texCoord.y);

} 