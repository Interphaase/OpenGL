#ifndef CAMERA_H
#define CAMERA_H
#include "glm/glm.hpp"
#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include "ShaderProgram.h"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"


class Camera {

private:
	float last_time, deltaTime;


public:
	ShaderProgram* shader;
	glm::vec3 camera_position;
	glm::vec3 camera_front;
	glm::vec3 camera_up;
	float speed;


	Camera(glm::vec3 camPosition, glm::vec3 camFront, glm::vec3 camUp, float speed);
	void HandleMovement(GLFWwindow* window);
	void Calculate(ShaderProgram* shader, float FOV, float aspect_ratio, float near_clip, float far_clip);


};








#endif
