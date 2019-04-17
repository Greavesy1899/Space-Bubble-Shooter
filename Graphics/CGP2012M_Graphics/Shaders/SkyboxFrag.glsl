#version 440 core
out vec4 vertColour;

in vec3 vs_col;
in vec3 vs_nor;
in vec3 vs_uv;
in vec4 vs_pos;

uniform int renderType;
uniform samplerCube aTex;
uniform vec3 shapeColour;
uniform float colorModifier;
uniform vec3 lightPos;

void main()
{	
	vertColour = texture(aTex, vs_uv);
} 