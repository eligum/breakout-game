#version 330 core
in vec2 TexCoord;

out vec4 Color;

uniform vec3 spriteColor;
uniform sampler2D image;

void main()
{
	Color = vec4(spriteColor, 1.0f) * texture(image, TexCoord);
}