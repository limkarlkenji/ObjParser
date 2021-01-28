#pragma once

#include <vector>
#include <fstream>
#include <sstream>
#include <string>

#include "Logging.h"


class ModelLoader
{
public:
	static std::vector<float> Open(const char* filePath);
private:
	static std::vector<float> Assemble(const std::vector<float> &position, const std::vector<float> &texCoords, const std::vector<float> &normals);
};

