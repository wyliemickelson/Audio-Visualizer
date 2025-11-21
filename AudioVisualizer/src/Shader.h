#pragma once
#define SHADER_H
#include <glad/glad.h>
#include <fstream>
#include <iostream>

/*
* Combines shaders after parsing from paths, returns shader program, -1 on failure.
*/
GLuint create_shader_program(const char* vertex_shader_path, const char* fragment_shader_path)
{
	//vertex shader 
	std::ifstream vs_file(vertex_shader_path);
	if (!vs_file) 
	{
		std::cerr << "ERROR: Failed opening vertex shader at path: " << vertex_shader_path << std::endl;
		return -1;
	}
	//get length of file
	vs_file.seekg(EOF);
	int len = vs_file.tellg();
	//read file
	std::vector<char> vs_data(len);
	vs_file.read(vs_data.data(), len);
	if (!vs_file) 
	{
		std::cerr << "ERROR: Failed reading vertex shader at path: " << vertex_shader_path << std::endl;
		return -1;
	}

	GLuint vertex_shader = glCreateShader(GL_VERTEX_SHADER);
	const GLchar* vs_source = (const GLchar*)vs_data.data();
	glShaderSource(vertex_shader, 1, &vs_source, 0);
	glCompileShader(vertex_shader);

	int is_compiled = 0; //check compilation status
	glGetShaderiv(vertex_shader, GL_COMPILE_STATUS, &is_compiled);
	if (is_compiled == GL_FALSE)
	{
		GLint max_length = 0;
		glGetShaderiv(vertex_shader, GL_INFO_LOG_LENGTH, &max_length);
		std::vector<GLchar> info_log(max_length);
		glGetShaderInfoLog(vertex_shader, max_length, &max_length, &info_log[0]);
		glDeleteShader(vertex_shader);
		std::cerr << info_log.data() << std::endl;

		return -1;
	}

	//fragment shader
	std::ifstream fs_file(fragment_shader_path);
	if (!fs_file) 
	{
		std::cerr << "ERROR: Failed opening fragment shader at path: " << fragment_shader_path << std::endl;
		return -1;
	}
	//get length of file
	fs_file.seekg(EOF);
	len = fs_file.tellg();
	//read file
	std::vector<char> fs_data(len);
	fs_file.read(fs_data.data(), len);
	if (!fs_file) 
	{
		std::cerr << "ERROR: Failed reading fragment shader at path: " << fragment_shader_path << std::endl;
		return -1;
	}

	GLuint fragment_shader = glCreateShader(GL_VERTEX_SHADER);
	const GLchar* fs_source = (const GLchar*)fs_data.data();
	glShaderSource(fragment_shader, 1, &fs_source, 0);
	glCompileShader(fragment_shader);

	//check compilation status
	is_compiled = 0; 
	glGetShaderiv(fragment_shader, GL_COMPILE_STATUS, &is_compiled);
	if (is_compiled == GL_FALSE)
	{
		GLint max_length = 0;
		glGetShaderiv(fragment_shader, GL_INFO_LOG_LENGTH, &max_length);
		std::vector<GLchar> info_log(max_length);
		glGetShaderInfoLog(fragment_shader, max_length, &max_length, &info_log[0]);
		glDeleteShader(fragment_shader);
		std::cerr << info_log.data() << std::endl;

		return -1;
	}

	GLuint program = glCreateProgram();
	glAttachShader(program, vertex_shader);
	glAttachShader(program, fragment_shader);
	glLinkProgram(program);

	//check shader program linking status
	GLint is_linked = 0;
	glGetProgramiv(program, GL_LINK_STATUS, (int*)&is_linked);
	if (is_linked == GL_FALSE)
	{
		GLint max_length = 0;
		glGetProgramiv(program, GL_INFO_LOG_LENGTH, &max_length);
		std::vector<GLchar> info_log(max_length);
		glGetProgramInfoLog(program, max_length, &max_length, &info_log[0]);
		std::cerr << info_log.data() << std::endl;
		glDeleteProgram(program);
		glDeleteShader(vertex_shader);
		glDeleteShader(fragment_shader);

		return -1;
	}

	glDetachShader(program, vertex_shader);
	glDetachShader(program, fragment_shader);

	return program;
}
