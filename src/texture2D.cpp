#include "texture2D.hpp"
#include <SOIL.h>

Texture2D::Texture2D()
	:
	_Width(0),
	_Height(0),
	_Internal_Format(GL_RGB),
	_Image_Format(GL_RGB),
	_Wrap_S(GL_REPEAT),
	_Wrap_T(GL_REPEAT),
	_Filter_Min(GL_LINEAR),
	_Filter_Max(GL_LINEAR)
{
	glGenTextures(1, &_ID);
}

void Texture2D::Generate(unsigned int width, unsigned int height, byte *data)
{
	_Width = width;
	_Height = height;
	// Create texture
	glBindTexture(GL_TEXTURE_2D, _ID);
	glTexImage2D(GL_TEXTURE_2D,
				 0, _Internal_Format, width, height,
				 0, _Image_Format, GL_UNSIGNED_BYTE, data);
	// Set texture wrap and filter modes
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, _Wrap_S);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, _Wrap_T);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, _Filter_Min);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, _Filter_Max);
	// Unbind texture
	glBindTexture(GL_TEXTURE_2D, 0);
}

void Texture2D::Bind() const
{
	glBindTexture(GL_TEXTURE_2D, _ID);
}