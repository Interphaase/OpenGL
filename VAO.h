#ifndef VAO_H
#define VAO_h
#include <glad/glad.h>
#include "VBO.h"
#include "EBO.h"
#include <vector>
#include <iostream>

struct Layout {
	GLuint layout_count;
	std::vector<unsigned int> param_count;
	std::vector<unsigned int> param_type;
	std::vector<unsigned int> normalized;
	Layout(GLuint lc, std::vector<unsigned int> pc, std::vector<unsigned int> pt, std::vector<unsigned int>pn) : 
	layout_count(lc), param_count(pc), param_type(pt), normalized(pn){}
};

class VAO {
public:
	GLuint ID;
	VAO();
	void LinkVBO(VBO* VBO, Layout layout);
	void LinkEBO(EBO* EBO);
	void Bind();
	void Unbind();
	void Delete();
};




#endif

