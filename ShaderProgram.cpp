#ifndef SHADER_PROGRAM_CLASS
#define SHADER_PROGRAM_CLASS
#include "ShaderProgram.h"


//Function for reading files
std::string read_file(const char* file_path) {
	

	std::string text, line;
	std::ifstream file(file_path);

	//Check if file was properly opened
	if (file.good()) {

		//Print a message to the console if file is opened
		std::cout << "File: " << file_path << " opened successfully!\n";
		
		//Read the text line by line
		while (getline(file, line)) {
			text += line + '\n';
		}
		text += "\0";

		//Close file after reading
		file.close();

		//Print text for debugging purposes
		std::cout << text << '\n';
		return text;
	}
	else {

		//Print a message to the console if file is not opened, close te file
		std::cout << "Couldn't open file: " << file_path << '\n';
		file.close();
		return "";
	}
	
}


ShaderProgram::ShaderProgram(const char* vertexShader_path, const char* fragmentShader_path) {

	//Creating variables for holding ID of vertexShader and fragmentShader
	//Creating variables for holding error info if compilation fails
	GLuint vertexShader, fragmentShader;
	int comp_error;
	char errorInfo[512];

	//Reading shaders source code
	std::string vertexShader_code = read_file(vertexShader_path);
	std::string fragmentShader_code = read_file(fragmentShader_path);

	//Converting string to const char
	const char* vertexShader_source = vertexShader_code.c_str();
	const char* fragmentShader_source = fragmentShader_code.c_str();

	//Creating shaders with OpenGL
	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

	//Compiling Vertex Shader and printing error if compilation fails
	glShaderSource(vertexShader, 1, &vertexShader_source, NULL);
	glCompileShader(vertexShader);

	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &comp_error);
	if (!comp_error) {
		glGetShaderInfoLog(vertexShader, 512, NULL, errorInfo);
		std::cout << "Vertex Shader Compilation Error:\n" << errorInfo << '\n';
	}

	//Creating Fragment Shader and printing error if compilation fails
	glShaderSource(fragmentShader, 1, &fragmentShader_source, NULL);
	glCompileShader(fragmentShader);

	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &comp_error);
	if (!comp_error) {
		glGetShaderInfoLog(fragmentShader, 512, NULL, errorInfo);
		std::cout << "Fragment Shader Compilation Error:\n" << errorInfo << '\n';
	}

	//Creating shader program and attaching Vertex and Fragment shader to it
	ID = glCreateProgram();
	glAttachShader(ID, vertexShader);
	glAttachShader(ID, fragmentShader);
	glLinkProgram(ID);

	//Handling compilation error
	glGetProgramiv(ID, GL_LINK_STATUS, &comp_error);
	if (!comp_error) {
		glGetProgramInfoLog(ID, 512, NULL, errorInfo);
		std::cout << "Shader Program Error:\n" << errorInfo << '\n';
	}

	//Freeing Memory after shader program compilation
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

}

void ShaderProgram::Activate(void) {
	//telling OpenGL to use our program
	glUseProgram(ID);
}

void ShaderProgram::Deactivate(void) {
	//telling OpenGl to not use our program
	glUseProgram(0);
}

void ShaderProgram::Delete(void) {
	//Deleting ShaderProgram
	glDeleteProgram(ID);
}

void ShaderProgram::SetFloat4(std::string uniform_name, float value1, float value2, float value3, float value4) {
	glUniform4f(glGetUniformLocation(ID, uniform_name.c_str()), value1, value2, value3, value4);
}

void ShaderProgram::SetFloat3(std::string uniform_name, float value1, float value2, float value3) {
	glUniform3f(glGetUniformLocation(ID, uniform_name.c_str()), value1, value2, value3);
}

void ShaderProgram::SetFloat2(std::string uniform_name, float value1, float value2) {
	glUniform2f(glGetUniformLocation(ID, uniform_name.c_str()), value1, value2);
}

void ShaderProgram::SetFloat1(std::string uniform_name, float value1) {
	glUniform1f(glGetUniformLocation(ID, uniform_name.c_str()), value1);
}

#endif