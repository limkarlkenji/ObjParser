#pragma once

#include "Logging.h"
#include "glad/glad.h"
#include "Vendor/stb_image.h"

class Texture
{
public:
	Texture(std::string);
	~Texture();

	void Bind();
private:
	unsigned int _textureId;
};

