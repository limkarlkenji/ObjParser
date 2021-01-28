#include "IndexBuffer.h"


IndexBuffer::IndexBuffer(unsigned int * data[])
{
	glGenBuffers(1, &_Id);
	PRINT("EBO >> " << sizeof((data)));
	Bind();
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, 4 * sizeof(int), data, GL_STATIC_DRAW);
}

IndexBuffer::IndexBuffer(std::vector<int> data)
{
	glGenBuffers(1, &_Id);
	PRINT("EBO >> EBO generated. Indices size: " << data.size());

	Bind();
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, data.size() * sizeof(int), std::data(data), GL_STATIC_DRAW);
}

IndexBuffer::~IndexBuffer()
{
	glDeleteBuffers(1, &_Id);
}

void IndexBuffer::Bind()
{
	PRINT("EBO >> Binding " << _Id);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _Id);
}

void IndexBuffer::Unbind()
{
	PRINT("EBO >> Unbinding");
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}
