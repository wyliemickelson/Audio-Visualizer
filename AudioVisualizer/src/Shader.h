#pragma once
#define SHADER_H
#include <glad/gl.h>
#include <fstream>
#include <iostream>
#include <sstream>

/*
* Combines shader after parsing from paths.
*/
class Shader
{
public:
	Shader(const char* vertex_shader_path, const char* fragment_shader_path)
	{
		//vertex shader 
		std::string vertexCode;
		std::string fragmentCode;
		std::ifstream vFile;
		std::ifstream fFile;

		vFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
		fFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
		try
		{
			vFile.open(vertex_shader_path);
			fFile.open(fragment_shader_path);
			std::stringstream vStream, fStream;
			vStream << vFile.rdbuf();
			fStream << fFile.rdbuf();
			vFile.close();
			fFile.close();
			vertexCode = vStream.str();
			fragmentCode = fStream.str();
		}
		catch (std::ifstream::failure e)
		{
			std::cout << "ERROR SHADER FILE NOT SUCCESSFULLY READ, REASON: " << e.what() << std::endl;
		}
		const char* vs_data = vertexCode.c_str();
		const char* fs_data = fragmentCode.c_str();

		GLuint vertex_shader = glCreateShader(GL_VERTEX_SHADER);
		const GLchar* vs_source = (const GLchar*)vs_data;
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

			return;
		}

		//fragment shader
		GLuint fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
		const GLchar* fs_source = (const GLchar*)fs_data;
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

			return ;
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

			return ;
		}

		glDetachShader(program, vertex_shader);
		glDetachShader(program, fragment_shader);

		ID = program;

	}
	void Use()
	{
		glUseProgram(ID);
	}
	void setMat4(const char* name, float mat4[4][4])
	{
		glUniformMatrix4fv(glGetUniformLocation(ID, name), 1, GL_FALSE, &mat4[0][0]);
	}
	void setVec4(const char* name, float vec[4])
	{
		glUniform4fv(glGetUniformLocation(ID, name), 1, &vec[0]);
	}
	unsigned int getID()
	{
		return ID;
	}
private:
	unsigned int ID = -1;
};
