#ifndef CUBE_OBJECT_CLASS
#define CUBE_OBJECT_CLASS
#include "Cube_Object.h"



CubeObject::CubeObject(glm::vec3 position, ShaderProgram* shader, Texture* tex, Camera* cam) {
	this->position = position;
	this->localPosition = glm::vec3(0.0f, 0.0f, 0.0f);
	this->shader = shader;
	this->texture = tex;
	this->cam = cam;

	this->vertex_data = new GLfloat[120] { 0.5f, -0.5f, 0.5f, 1.0f, 0.0f, //FRONTFACE_BOTTOM_RIGHT
										0.5f, 0.5f, 0.5f, 1.0f, 1.0f,     //FRONTFACE_TOP_RIGHT
									   -0.5f, -0.5f, 0.5f, 0.0f, 0.0f,    //FRONTFACE_BOTTOM_LEFT
								       -0.5f, 0.5f, 0.5f, 0.0f, 1.0f,     // FRONTFACE_TOP_LEFT;
										
										0.5f, -0.5f, -0.5f, 0.0f, 0.0f,   //BACKFACE_BOTTOM_LEFT
										0.5f, 0.5f, -0.5f, 0.0f, 1.0f,    //BACKFACE_TOP_LEFT
									   -0.5f, -0.5f, -0.5f, 1.0f, 0.0f,   //BACKFACE_BOTTOM_RIGHT
									   -0.5f, 0.5f, -0.5f, 1.0f, 1.0f,    //BACKFACE_TOP_RIGHT;

									   -0.5f, -0.5f, -0.5f, 0.0f, 0.0f,   //LEFTFACE_BOTTOM_LEFT
									   -0.5f, 0.5f, -0.5f, 0.0f, 1.0f,    //LEFTFACE_TOP_LEFT
									   -0.5f, -0.5f, 0.5f, 1.0f, 0.0f,    //LEFTFACE_BOTTOM_RIGHT
									   -0.5f, 0.5f, 0.5f, 1.0f, 1.0f,     //LEFTFACE_TOP_RIGHT

									    0.5f, -0.5f, -0.5f, 1.0f, 0.0f,   //RIGHTFACE_BOTTOM_RIGHT
									    0.5f, 0.5f, -0.5f, 1.0f, 1.0f,    //RIGHTFACE_TOP_RIGHT
									    0.5f, -0.5f, 0.5f, 0.0f, 0.0f,    //RIGHTFACE_BOTTOM_LEFT
									    0.5f, 0.5f, 0.5f, 0.0f, 1.0f,     //RIGHTFACE_TOP_LEFT

									    -0.5f, 0.5f, 0.5f, 0.0f, 0.0f,    //TOPFACE_BOTTOM_LEFT
									    -0.5f, 0.5f, -0.5f, 0.0f, 1.0f,   //TOPFACE_TOP_LEFT
									    0.5f, 0.5f, 0.5f, 1.0f, 0.0f,	  //TOPFACE_BOTTOM_RIGHT
										0.5f, 0.5f, -0.5f, 1.0f, 1.0f,    //TOPFACE_TOP_RIGHT

										-0.5f, -0.5f, 0.5f, 0.0f, 0.0f,   //BOTTOMFACE_BOTTOM_LEFT
										-0.5f, -0.5f, -0.5f, 0.0f, 1.0f,  //BOTTOMFACE_TOP_LEFT
										0.5f, -0.5f, 0.5f, 1.0f, 0.0f,	  //BOTTOMFACE_BOTTOM_RIGHT
										0.5f, -0.5f, -0.5f, 1.0f, 1.0f,   //BOTTOMFACE_TOP_RIGHT

									};

	this->vertex_order = new GLuint[36] {0, 1, 2, 2, 3, 1,			    /*FRONT WALL*/
										 4, 5, 6, 6, 7, 5,			    /*BACK WALL*/
										 8, 9, 10, 10, 11, 9,   	    /*LEFT WALL*/
										 12, 13, 14, 14, 15, 13,		/*RIGHT WALL*/
										 16, 17, 18, 18, 19, 17,		/*TOP WALL*/
										 20, 21, 22, 22, 23, 21			/*BOTTOM WALL*/
		 };

	Layout lay1(2, std::vector<unsigned int> {3, 2}, std::vector<unsigned int> {GL_FLOAT, GL_FLOAT}, std::vector<unsigned int> {0, 0});
	this->vbo = VBO(this->vertex_data, 120*sizeof(GLfloat));
	this->ebo = EBO(this->vertex_order, 36*sizeof(GLuint));

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
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

};






#endif
