#ifndef EBO_CLASS
#define EBO_CLASS

#include "EBO.h"


EBO::EBO(GLuint* vertex_order, GLsizeiptr size) {
	//Generating buffer for Element Buffer
	glGenBuffers(1, &ID);
	//Binding to buffer and sending its data
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ID);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, vertex_order, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
};
EBO::EBO() {};
void EBO::Bind() {
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ID);
};
void EBO::Unbind() {
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
};
void EBO::Delete() {
	glDeleteBuffers(1, &ID);
};

#endif