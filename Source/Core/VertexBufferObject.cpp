#include "VertexBufferObject.h"

//VertexBufferObject::VertexBufferObject(const void * data)
VertexBufferObject::VertexBufferObject(std::vector<float> &data)
{
	glGenBuffers(1, &_Id);
	PRINT("VBO >> VBO generated");

	Bind();
	glBufferData(GL_ARRAY_BUFFER, data.size() * sizeof(float), std::data(data), GL_STATIC_DRAW);
}

VertexBufferObject::~VertexBufferObject()
{
	glDeleteBuffers(1, &_Id);
}

void VertexBufferObject::Bind() const
{
	glBindBuffer(GL_ARRAY_BUFFER, _Id);
	PRINT("VBO >> Binding " << _Id);
}

void VertexBufferObject::Unbind() const
{
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	PRINT("VBO >> Unbinding");
}
