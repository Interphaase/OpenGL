#ifndef SHADER_PROGRAM_H
#define SHADER_PROGRAM_H
#include <fstream>
#include <iostream>
#include <string>
#include <glad/glad.h>


std::string read_file(const char* file_path);

class ShaderProgram {

	public:
		GLuint ID;
		ShaderProgram(const char* vertexShader_path, const char* fragmentShader_path);
		void Activate(void);
		void Deactivate(void);
		void Delete(void);
		void SetFloat4(std::string uniform_name, float value1, float value2, float value3, float value4);
		void SetFloat3(std::string uniform_name, float value1, float value2, float value3);
		void SetFloat2(std::string uniform_name, float value1, float value2);
		void SetFloat1(std::string uniform_name, float value1);

};


#endif
