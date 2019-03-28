#version 440 core
out vec4 vertColour;

in vec3 vs_col;
in vec3 vs_nor;
in vec2 vs_uv;
in vec4 vs_pos;

uniform int renderType;
uniform sampler2D aTex;
uniform vec3 shapeColour;
uniform float colorModifier;

void main()
{		
	if(renderType == 0) //TEXTURE
	{
		vertColour = texture(aTex, vs_uv);
	}
	else if(renderType == 1) //VERTEX_COLOUR
	{
		vertColour = vec4(vs_col, 1.0f);
	}
	else if(renderType == 2) //COLOUR
	{
		vertColour = vec4(shapeColour, 1.0f);
	}
	else if(renderType == 3) //SPECIAL_BUBBLE
	{
		float r = clamp(shapeColour.r + sin(vs_pos.x) + sin(vs_pos.y), 0.25f, 1.0f);
		float g = clamp(shapeColour.g + sin(vs_pos.y) + sin(vs_pos.x), 0.25f, 1.0f);
		vec4 texAlpha = texture(aTex, vs_uv);
		vertColour = vec4(r, g, shapeColour.b, texAlpha.w);
	}
} 