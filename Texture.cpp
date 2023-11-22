#ifndef TEXTURE_CPP
#define TEXTURE_CPP
#include "Texture.h"

Texture::Texture(int tex_buff_index, const char* image_location) {

	stbi_set_flip_vertically_on_load(true); 
	this->texture_buffer = tex_buff_index;
	this->data = stbi_load(image_location, &this->tex_width, &this->tex_height, &this->nrChannels, 0);
	glGenTextures(1, &this->ID);
}
void Texture::Bind() {

	glActiveTexture(GL_TEXTURE0 + this->texture_buffer);
	glBindTexture(GL_TEXTURE_2D, this->ID);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	if (this->nrChannels == 4) {
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, this->tex_width, this->tex_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, this->data);
	}
	else {
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, this->tex_width, this->tex_height, 0, GL_RGB, GL_UNSIGNED_BYTE, this->data);
	}
	glGenerateMipmap(GL_TEXTURE_2D);

}


#endif