#pragma once

#include "Core/Shader.h"
#include "Core/Reader.h"

class Material
{
public:
	Material();
	Material(std::string);
	~Material();
private:
	Shader _shader;
};

