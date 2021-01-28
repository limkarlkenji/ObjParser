#pragma once

#include <vector>
#include "Logging.h"
#include <glad/glad.h>

class IndexBuffer
{
public:
	IndexBuffer(unsigned int * data[]);
	IndexBuffer(std::vector<int> data);
	~IndexBuffer();

	void Bind();
	void Unbind();
private:
	unsigned int _Id;
};

