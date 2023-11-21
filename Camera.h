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
	float FOV, near_clip, far_clip, aspect_ratio, speed;
	float last_time, deltaTime;


public:
	ShaderProgram* shader;
	glm::vec3 camera_position;
	glm::vec3 camera_front;
	glm::vec3 camera_up;


	Camera(glm::vec3 camPosition, glm::vec3 camFront, glm::vec3 camUp, ShaderProgram* shd,
			float fov, float n_clip, float f_clip, float asp_rt, float speed);
	void HandleMovement(GLFWwindow* window);
	void Calculate();


};








#endif
