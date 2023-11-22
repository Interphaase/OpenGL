#ifndef CUBE_OBJECT_CPP
#define CUBE_OBJECT_CPP
#include "Cube_Object.h"



CubeObject::CubeObject(glm::vec3 position, ShaderProgram* shader, Texture* tex, Camera* cam) {
	this->position = position;
	this->localPosition = glm::vec3(0.0f, 0.0f, 0.0f);
	this->shader = shader;
	this->texture = tex;
	this->cam = cam;

	this->vertex_data = new GLfloat[20] { 0.5f, -0.5f, 0.5f, 1.0f, 0.0f, //FRONT_BOTTOM_RIGHT
										0.5f, 0.5f, 0.5f, 1.0f, 1.0f,  //FRONT_TOP_RIGHT
									   -0.5f, -0.5f, 0.5f, 0.0f, 0.0f, //FRONT_BOTTOM_LEFT
								       -0.5f, 0.5f, 0.5f, 0.0f, 1.0f,    // FRONT_TOP_LEFT;
									};

	this->vertex_order = new GLuint[6] {0, 1, 2, 2, 3, 1};  /*FRONT WALL*/

	Layout lay1(2, std::vector<unsigned int> {3, 2}, std::vector<unsigned int> {GL_FLOAT, GL_FLOAT}, std::vector<unsigned int> {0, 0});
	this->vbo = VBO(this->vertex_data, 20*sizeof(GLfloat));
	this->ebo = EBO(this->vertex_order, 6*sizeof(GLuint));

	this->vao.LinkVBO(&this->vbo, lay1);
	this->vao.LinkEBO(&this->ebo);

};
void CubeObject::Draw() {
	this->texture->Bind();
	this->vao.Bind();
	this->shader->Activate();


	unsigned int mod_loc;
	mod_loc = glGetUniformLocation(this->shader->ID, "model");

	glm::mat4 model = glm::mat4(1.0f);
	glUniformMatrix4fv(mod_loc, 1, GL_FALSE, glm::value_ptr(model));
	
	cam->Calculate(this->shader);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

};






#endif
