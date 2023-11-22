#ifndef CAMERA_CLASS
#define CAMERA_CLASS
#include "Camera.h"




Camera::Camera(glm::vec3 camPosition, glm::vec3 camFront, glm::vec3 camUp, float speed) {
	this->camera_position = camPosition;
	this->camera_front = camFront;
	this->camera_up = camUp;
	this->speed = speed;
}

void Camera::Calculate(ShaderProgram* shader, float FOV, float aspect_ratio, float near_clip, float far_clip) {
	unsigned int view_loc, proj_loc;
	view_loc = glGetUniformLocation(shader->ID, "view");
	proj_loc = glGetUniformLocation(shader->ID, "projection");

	glm::mat4 projection_matrix = glm::mat4(1.0f);
	glm::mat4 view_matrix = glm::mat4(1.0f);

	projection_matrix = glm::perspective(glm::radians(FOV), aspect_ratio, near_clip, far_clip);
	view_matrix = glm::lookAt(this->camera_position, this->camera_position + this->camera_front, this->camera_up);

	glUniformMatrix4fv(view_loc, 1, GL_FALSE, glm::value_ptr(view_matrix));
	glUniformMatrix4fv(proj_loc, 1, GL_FALSE, glm::value_ptr(projection_matrix));
}

void Camera::HandleMovement(GLFWwindow* window) {

	float currentTime = glfwGetTime();
	deltaTime = currentTime - last_time;
	last_time = currentTime;



	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
		camera_position += speed * camera_front * deltaTime;
	}
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
		camera_position -= speed * camera_front * deltaTime;
	}
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
		camera_position += glm::normalize(glm::cross(camera_up, camera_front)) * speed * deltaTime;
	}
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
		camera_position -= glm::normalize(glm::cross(camera_up, camera_front)) * speed * deltaTime;
	}
}





#endif