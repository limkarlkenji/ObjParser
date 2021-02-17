#include "Material.h"

Material::Material()
{
}

Material::Material(std::string filePath)
{
	PRINT("MATERIAL >> Loaded mtl " << filePath);
}

Material::~Material()
{
}
