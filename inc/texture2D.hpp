#ifndef TEXTURE2D_H
#define TEXTURE2D_H

#include <glad/glad.h>

typedef unsigned char byte;

class Texture2D
{
public:
	// Texture object ID
	unsigned int _ID;
	unsigned int _Width, _Height;
	unsigned int _Internal_Format;
	unsigned int _Image_Format;
	// Texture configurations
	unsigned int _Wrap_S;
	unsigned int _Wrap_T;
	unsigned int _Filter_Min;
	unsigned int _Filter_Max;
public:
	Texture2D();
	void Generate(unsigned int width, unsigned int height, byte *data);
	void Bind() const;
	void Unbind();
};

#endif