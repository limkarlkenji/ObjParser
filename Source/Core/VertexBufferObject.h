#pragma once

#include "Logging.h"
#include <glad/glad.h>

class VertexBufferObject
{
public:
	VertexBufferObject(const void * data);
	~VertexBufferObject();

	void Bind() const;
	void Unbind() const;

private:
	unsigned int _Id;
};

