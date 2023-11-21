#ifndef VBO_CLASS
#define VBO_CLASS
#include "VBO.h"


VBO::VBO(GLfloat* vertices, GLsizeiptr size) {
	vertex_data = vertices;
	glGenBuffers(1, &ID);
	glBindBuffer(GL_ARRAY_BUFFER, ID);
	glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0); 

};
void VBO::Bind() {
	glBindBuffer(GL_ARRAY_BUFFER, ID);
};
void VBO::Unbind() {
	glBindBuffer(GL_ARRAY_BUFFER, 0);
};
void VBO::Delete() {
	glDeleteBuffers(1, &ID);
};

#endif