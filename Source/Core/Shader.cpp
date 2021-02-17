#include "Shader.h"

Shader::Shader()
{
}

Shader::Shader(const char * vertexSrc, const char * fragmentSrc) : _Id(0)
{
	unsigned int vertex, fragment;
	// vertex shader
	vertex = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertex, 1, &vertexSrc, NULL);
	glCompileShader(vertex);

	int result;
	glGetShaderiv(vertex, GL_COMPILE_STATUS, &result);

	if (result == GL_FALSE)
	{
		int length;
		glGetShaderiv(vertex, GL_INFO_LOG_LENGTH, &length);
		char* message = (char*)alloca(length * sizeof(char));
		glGetShaderInfoLog(vertex, length, &length, message);
		std::cout << "Error " << " VERT " << message << std::endl;
		glDeleteShader(vertex);
	}

	//checkCompileErrors(vertex, "VERTEX");
	// fragment Shader
	fragment = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragment, 1, &fragmentSrc, NULL);
	glCompileShader(fragment);

	glGetShaderiv(fragment, GL_COMPILE_STATUS, &result);

	if (result == GL_FALSE)
	{
		int length;
		glGetShaderiv(fragment, GL_INFO_LOG_LENGTH, &length);
		char* message = (char*)alloca(length * sizeof(char));
		glGetShaderInfoLog(fragment, length, &length, message);
		std::cout << "Error " << " FRAG " << message << std::endl;
		glDeleteShader(fragment);
	}

	//checkCompileErrors(fragment, "FRAGMENT");

	// shader Program
	_Id = glCreateProgram();
	glAttachShader(_Id, vertex);
	glAttachShader(_Id, fragment);

	glLinkProgram(_Id);
	//checkCompileErrors(Id, "PROGRAM");
	// delete the shaders as they're linked into our program now and no longer necessery
	glDeleteShader(vertex);
	glDeleteShader(fragment);

	PRINT("SHADER >> Program: " << _Id << ". Vertex and Fragment shader created.");
}

Shader::~Shader()
{
	
}


void Shader::Use()
{
	glUseProgram(_Id);
}

unsigned int Shader::GetUniformLocation(const char* name) const
{
	int loc = glGetUniformLocation(_Id, name);
	if (loc == -1)
	{
		PRINT("Can't find " << name << " " << _Id);

		
	}

	return loc;
}

void Shader::setVec3(const std::string &name, float x, float y, float z) const
{
	glUniform3f(glGetUniformLocation(_Id, name.c_str()), x, y, z);
	PRINT("setting");
}
void Shader::GetActiveUniformList() const
{
	GLint success;
	GLint size; // size of the variable
	GLenum type; // type of the variable (float, vec3 or mat4, etc)

	const GLsizei bufSize = 16; // maximum name length
	GLchar name[bufSize]; // variable name in GLSL
	GLsizei length; // name length
	glGetProgramiv(_Id, GL_ACTIVE_UNIFORMS, &success);
	PRINT("SHADER >> Program: " << _Id << " Active Uniforms: " << success);
	//printf("SHADER >> Program Active Uniforms: %d\n", success);

	for (int i = 0; i < success; i++)
	{
		glGetActiveUniform(_Id, (GLuint)i, bufSize, &length, &size, &type, name);

		printf("Uniform #%d Type: %u Name: %s\n", i, type, name);
	}
}
