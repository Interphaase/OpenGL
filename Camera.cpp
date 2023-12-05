#ifndef CAMERA_CLASS
#define CAMERA_CLASS
#include "Camera.h"




Camera::Camera(glm::vec3 camPosition, glm::vec3 camFront, glm::vec3 camUp, float speed,
				float FOV, float aspect_ratio, float near_clip, float far_clip, float sensitivity) {

	this->camera_position = camPosition;
	this->camera_front = camFront;
	this->camera_up = camUp;
	this->speed = speed;
	this->FOV = FOV;
	this->aspect_ratio = aspect_ratio;
	this->near_clip = near_clip;
	this->far_clip = far_clip;
	this->sensitivity = sensitivity;
	

}

void Camera::Calculate(ShaderProgram* shader) {
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

void Camera::HandleMovement(GLFWwindow* window, double mouse_x, double mouse_y) {

	float currentTime = glfwGetTime();
	this->deltaTime = currentTime - this->last_time;
	this->last_time = currentTime;


	double x_offset = (mouse_x - this->last_mouse_x) * sensitivity * this->deltaTime;
	double y_offset = (mouse_y - this->last_mouse_y) * sensitivity * this->deltaTime;

	this->last_mouse_x = mouse_x;
	this->last_mouse_y = mouse_y;

	totalOffset_x += x_offset;
	totalOffset_y += y_offset;

	if (totalOffset_x > 360) {
		totalOffset_x = 0;
	}
	if (totalOffset_x < 0) {
		totalOffset_x = 360;
	}
	if (totalOffset_y < -80) {
		totalOffset_y = -80;
	}
	if (totalOffset_y > 80) {
		totalOffset_y = 80;
	}


	//std::cout << "totalX: " << totalOffset_x << "\n";
	//std::cout << "totalY: " << totalOffset_y << "\n";

	glm::vec3 direction;
	direction.x = cos(glm::radians(totalOffset_x));
	direction.y = -sin(glm::radians(totalOffset_y));
	direction.z = sin(glm::radians(totalOffset_x))*cos(glm::radians(totalOffset_y));
	camera_front = glm::normalize(direction);

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