#include "ModelLoader.h"

ModelLoader::ModelLoader(const char * filePath)
{
	std::ifstream infile;

	infile.open(filePath);

	std::vector<std::string> d;

	for (std::string currentLine; std::getline(infile, currentLine); )
	{
		if (currentLine.find("v ", 0) != currentLine.npos)
		{
			d = SeparateString(currentLine, 2, " ");
			for (int i = 0; i < d.size(); i++)
			{
				_vertPositions.push_back(std::stof(d[i]));
			}
		}
		else if (currentLine.find("vt", 0) != currentLine.npos)
		{
			d = SeparateString(currentLine, 2, " ");
			for (int i = 0; i < d.size(); i++)
			{
				_texCoords.push_back(std::stof(d[i]));
			}
		}
		else if (currentLine.find("vn", 0) != currentLine.npos)
		{
			d = SeparateString(currentLine, 2, " ");
			for (int i = 0; i < d.size(); i++)
			{
				_normals.push_back(std::stof(d[i]));
			}
		}
		else if (currentLine.find("f ", 0) != currentLine.npos)
		{
			ParseFaces(currentLine);
		}
	}
	infile.close();

	for (int v = 0; v < _vertPositions.size(); v += 3) // Increment by 3(x, y, z)
	{
		for (int f = 0; f < _faces.size(); f++)
		{
			if (v == _faces[f].pos * 3) // Multiplied face index by 3 to match vertexPosition index
			{
				_vertexData.push_back(_vertPositions[v]);
				_vertexData.push_back(_vertPositions[v+1]);
				_vertexData.push_back(_vertPositions[v+2]);

				_vertexData.push_back(_texCoords[_faces[f].pos]);
				_vertexData.push_back(_texCoords[_faces[f].pos] + 1);

				_vertexData.push_back(_normals[_faces[f].pos]);
				_vertexData.push_back(_normals[_faces[f].pos] + 1);
				_vertexData.push_back(_normals[_faces[f].pos] + 2);

				break;
			}
		}
	}
}

ModelLoader::~ModelLoader()
{
}

void ModelLoader::ParseFaces(const std::string &data)
{
	/*
			v, vt and vn are simple to understand. f is more tricky. So, for f 8/11/7 7/12/7 6/10/7 :

8/11/7 describes the first vertex of the triangle
7/12/7 describes the second vertex of the triangle
6/10/7 describes the third vertex of the triangle (duh)
For the first vertex, 8 says which position to use. So in this case, -1.000000 1.000000 -1.000000 (index start to 1, not to 0 like in C++)
11 says which texture coordinate to use. So in this case, 0.748355 0.998230
7 says which normal to use. So in this case, 0.000000 1.000000 -0.000000
			*/

	std::vector<std::string> faces = SeparateString(data, 2, "/ ");
	for (int o = 0; o < faces.size(); o+=3)
	{
		_faces.push_back(FaceData{ std::stoi(faces[o]), std::stoi(faces[o + 1]), std::stoi(faces[o + 2]) }); // Store faces to create vertex data for opengl

		if (o % 3 == 0)
		{
			_indexData.push_back(std::stoi(faces[o]));	// Indices for opengl
		}
	}
}


std::vector<std::string> ModelLoader::SeparateString(std::string line, int startPos, std::string separator) const
{
	std::vector<std::string> data;
	int index = line.find_first_not_of(separator, startPos); // Starting position to iterate
	for (int i = index; i < line.size(); i = index)
	{
		int start = line.find_first_not_of(separator, index);	// Look for next non-whitespace character
		int end = line.find_first_of(separator, index);				// Look for next whitespace character

		index = line.find_first_not_of(separator, end);		// Update index to 'end'. This is where the next search should begin
		data.push_back(line.substr(start, end - start));
	}

	return data;
}
