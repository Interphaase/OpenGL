#ifndef VAO_CLASS
#define VAO_CLASS
#include "VAO.h"



VAO::VAO() {
	glGenVertexArrays(1, &ID);
};

void VAO::LinkVBO(VBO* VBO, Layout layout) {

	int stride = 0;
	int first_layout_element = 0;
	for (unsigned int i = 0; i < layout.layout_count;i++) {

		stride += layout.param_count[i] * sizeof(VBO->vertex_data[first_layout_element]);

		if (i > 0) {
			first_layout_element += layout.param_count[i - 1];
		}

	}
	Bind();
	VBO->Bind();

	
	first_layout_element = 0;
	for (unsigned int i = 0; i < layout.layout_count;i++) {
		int offset = 0;
		if (i > 0) {
			first_layout_element += layout.param_count[i - 1];
			offset += layout.param_count[i - 1] * sizeof(VBO->vertex_data[first_layout_element]);
			glVertexAttribPointer(i, layout.param_count[i], layout.param_type[i], layout.normalized[i], stride, (const void*)offset);
			std::cout << "Layout: " << i << "\nParameter Count: " << layout.param_count[i] << "\nStride: " << stride
				<< "\nOffset: " << offset << '\n';
		}
		else {
			glVertexAttribPointer(i, layout.param_count[i], layout.param_type[i], layout.normalized[i], stride, (const void*)0);
			std::cout << "Layout: " << i << "\nParameter Count: " << layout.param_count[i] << "\nStride: " << stride
				<< "\nOffset: " << offset << '\n';

		}

		glEnableVertexAttribArray((GLuint)i);

	}
	Unbind();
	VBO->Unbind();
};

void VAO::LinkEBO(EBO* EBO) {
	Bind();
	EBO->Bind();
	Unbind();
	EBO->Unbind();
};

void VAO::Bind() {
	glBindVertexArray(ID);
};
void VAO::Unbind() {
	glBindVertexArray(0);
};
void VAO::Delete() {
	glDeleteVertexArrays(1, &ID);
};




#endif