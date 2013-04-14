#version 150

in vec3 vertexColor;
in vec3 fragNormal;

out vec3 outColor;

void main()
{
	outColor = vertexColor * (dot(fragNormal, vec3(0.05, 1.0, 0.025)) + 0.25);
	outColor = clamp(outColor, 0.0, 1.0);
}