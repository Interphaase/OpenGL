#ifndef TEXTURE_H
#define TEXTURE_H
#include "stb_image.h"
#include <glad/glad.h>


class Texture {

private:
	int tex_width, tex_height, nrChannels;
	int texture_buffer;
	unsigned char* data;
	unsigned int ID;
public:
	Texture(int tex_buff_index, const char* image_location);
	void Bind();
	void Unbind();

};

#endif
