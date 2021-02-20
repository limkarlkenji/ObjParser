#pragma once
#include <glad/glad.h>
#include <GLM/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Logging.h"
#include "Reader.h"

class Shader
{
public:
	Shader();
	Shader(const char* vertex, const char* fragment);
	~Shader();

	
	int GetId() const { return _Id; };
	void Use();
	unsigned int GetUniformLocation(const char* name) const;
	void GetActiveUniformList() const;

	void SetUniform3fv(const char* name, glm::vec3 value);
	void SetUniformMat4fv(const char* name, glm::mat4 value);
	void SetUniform1i(const char* name, int value);
	void SetUniform1f(const char* name, float value);

private:
	unsigned int _Id;
};

