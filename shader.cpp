#include "shader.h"

shader::shader()
{
	program = 0;
	program = glCreateProgram();


}


bool shader::loadshader(std::string shaderlocation, GLenum type)
{
	std::ifstream shader(shaderlocation.c_str());

	std::vector<std::string> SLines;
	std::string line;
	std::string test;

	while (std::getline(shader, line))
	{
		line += '\n';
		test += line;
	}

	const GLchar *myshader = test.c_str();

	GLuint Shader = glCreateShader(type);

	glShaderSource(Shader, 1, &myshader, NULL);

	glCompileShader(Shader);

	if (!CheckShaderCompiled(Shader))
	{
		return 3;
	}

	glAttachShader(program, Shader);


	return true;

}

bool shader::linkcheck()
{

	GLint linked;
	glGetProgramiv(program, GL_LINK_STATUS, &linked);

	if (!linked)
	{
		GLsizei len;
		glGetProgramiv(program, GL_INFO_LOG_LENGTH, &len);

		GLchar* log = new GLchar[len + 1];
		glGetProgramInfoLog(program, len, &len, log);
		std::cerr << "ERROR: Shader linking failed: " << log << std::endl;
		delete[] log;

		return false;
	}

	return true;

}

void shader::linkshader()
{
	glLinkProgram(program);

}

void shader::useProgram()
{
	glUseProgram(program);

}

void shader::stopProgram()
{
	glUseProgram(0);
}


GLuint shader::returnprogram()
{
	return program;

}