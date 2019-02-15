#version 440 core

out vec4 FragColor;
in vec3 outColor;

void main()
{
	gl_FragColor = vec4(outColor, 1.0);
}