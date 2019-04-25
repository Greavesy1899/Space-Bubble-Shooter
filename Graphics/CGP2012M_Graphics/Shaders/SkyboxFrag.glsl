#version 440 core
out vec4 vertColour;

in vec3 vs_col;
in vec3 vs_nor;
in vec3 vs_uv;
in vec4 vs_pos;

uniform samplerCube aTex;

void main()
{	
	vertColour = texture(aTex, vs_uv);
} 