#pragma once
#include <glad/glad.h>

#include "Logging.h"
#include "Reader.h"

class Shader
{
public:
	Shader(const char* vertex, const char* fragment);
	~Shader();

	
	int GetId() const { return _Id; };
	void Use();
	unsigned int GetUniformLocation(const char* name) const;

private:
	unsigned int _Id;
};

