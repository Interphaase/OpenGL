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
	float FOV, aspect_ratio, near_clip, far_clip;
	float sensitivity;
	double last_mouse_x=0, last_mouse_y=0;
	double totalOffset_x = 270, totalOffset_y = 0;


public:
	ShaderProgram* shader;
	glm::vec3 camera_position;
	glm::vec3 camera_front;
	glm::vec3 camera_up;
	float speed;


	Camera(glm::vec3 camPosition, glm::vec3 camFront, glm::vec3 camUp, float speed,
			float FOV, float aspect_ratio, float near_clip, float far_clip, float sensitivity);

	void HandleMovement(GLFWwindow* window, double mouse_x, double mouse_y);
	void Calculate(ShaderProgram* shader);


};








#endif
