#include "Material.h"

Material::Material()
{
}

Material::Material(std::string filePath, Shader &shader) : specularStrength(0.0f)
{
	PRINT("MATERIAL >> Loaded mtl " << filePath);
	_shader = shader;

	std::ifstream infile;
	infile.open(filePath);

	std::vector<std::string> d;

	for (std::string currentLine; std::getline(infile, currentLine); )
	{
		if (currentLine.find(" Ka ", 0) != currentLine.npos)
		{
			d = SeparateString(currentLine, currentLine.find("Ka ", 0)+2, " ");
			ambientColor = Vector3f(std::stof(d[0]), std::stof(d[1]), std::stof(d[2]));
		}
		else if (currentLine.find(" Kd", 0) != currentLine.npos)
		{
			d = SeparateString(currentLine, currentLine.find("Kd", 0)+2, " ");
			diffuseColor = Vector3f(std::stof(d[0]), std::stof(d[1]), std::stof(d[2]));
		}
		else if (currentLine.find(" Ks", 0) != currentLine.npos)
		{
			d = SeparateString(currentLine, currentLine.find("Ks", 0)+2, " ");
			specularColor = Vector3f(std::stof(d[0]), std::stof(d[1]), std::stof(d[2]));
		}
		else if (currentLine.find(" Ns", 0) != currentLine.npos)
		{
			d = SeparateString(currentLine, currentLine.find("Ns", 0) + 2, " ");
			specularStrength = std::stof(d[0]);
		}
	}
	infile.close();
}

Material::~Material()
{
}

std::vector<std::string> Material::SeparateString(std::string line, int startPos, std::string separator) const
{
	std::vector<std::string> data;
	int index = line.find_first_not_of(separator, startPos); // Starting position to iterate
	for (int i = index; i < line.size(); i = index)
	{
		int start = line.find_first_not_of(separator, index);	// Look for next non-separator character
		int end = line.find_first_of(separator, index);				// Look for next separator character

		index = line.find_first_not_of(separator, end);		// Update index to 'end'. This is where the next search should begin
		data.push_back(line.substr(start, end - start));
	}

	return data;
}
