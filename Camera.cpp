#ifndef CAMERA_CLASS
#define CAMERA_CLASS
#include "Camera.h"




Camera::Camera(glm::vec3 camPosition, glm::vec3 camFront, glm::vec3 camUp, ShaderProgram* shd,
				float fov, float n_clip, float f_clip,  float asp_rt, float speed) {
	camera_position = camPosition;
	camera_front = camFront;
	camera_up = camUp;
	shader = shd;
	FOV = fov;
	near_clip = n_clip;
	far_clip = f_clip;
	aspect_ratio = asp_rt;
	this->speed = speed;
}

void Camera::Calculate(void) {
	unsigned int view_loc, proj_loc;
	view_loc = glGetUniformLocation(shader->ID, "view");
	proj_loc = glGetUniformLocation(shader->ID, "projection");

	glm::mat4 projection_matrix = glm::mat4(1.0f);
	glm::mat4 view_matrix = glm::mat4(1.0f);

	projection_matrix = glm::perspective(glm::radians(FOV), aspect_ratio, near_clip, far_clip);
	view_matrix = glm::lookAt(camera_position, camera_position + camera_front, camera_up);

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