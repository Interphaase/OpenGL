#ifndef VBO_H
#define VBO_H
#include <glad/glad.h>

class VBO {

public:
	GLuint ID;
	GLfloat* vertex_data;

	VBO(GLfloat* vertices, GLsizeiptr size);
	VBO();
	void Bind();
	void Unbind();
	void Delete();
};



#endif
