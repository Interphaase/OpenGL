#ifndef CUBE_OBJECT_H
#define CUBE_OBJECT_H
#include "VAO.h"
#include "VBO.h"
#include "EBO.h"
#include "ShaderProgram.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "Texture.h"
#include "Camera.h"
#include <iostream>

class CubeObject {

public:
	ShaderProgram* shader;
	Texture* texture;
	Camera* cam;
	VBO vbo;
	EBO ebo;
	VAO vao;

	GLfloat* vertex_data;
	GLuint* vertex_order;

public:
	glm::vec3 position;
	glm::vec3 localPosition;


	CubeObject(glm::vec3 position, ShaderProgram* shader, Texture* tex, Camera* cam);
	void Draw();


};












#endif