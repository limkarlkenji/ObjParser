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
			GenerateIndexData(currentLine);
		}
	}
	infile.close();

	for (int v = 0; v < _vertPositions.size()/3; v++) // Increment by 3(x, y, z)
	{
		for (int p = 0; p < 3; p++)
		{
			_vertexData.push_back(_vertPositions[(v * 3) + p]);
		}

		if (_texCoords.size() > 0)
		{
			for (int t = 0; t < 2; t++)
			{
				int index = (v * 2) + t;
				if (index > _texCoords.size() - 1) // meaning there is less vt than v
				{
					_vertexData.push_back(0.0f);
				}
				else
				{
					_vertexData.push_back(_texCoords[index]);

				}
			}
		}
		else
		{
			_vertexData.push_back(0.0f);
			_vertexData.push_back(0.0f);
		}

		if (_normals.size() > 0)
		{
			for (int n = 0; n < 3; n++)
			{
				int index = (v * 3) + n;

				if (index > _normals.size() - 1) // meaning there is less vn than v
				{
					_vertexData.push_back(0.0f);
				}
				else
				{
					_vertexData.push_back(_normals[index]);
				}
			}
		}
		else
		{
			_vertexData.push_back(0.0f);
			_vertexData.push_back(0.0f);
			_vertexData.push_back(0.0f);
		}
	}

	PRINT("MODEL LOADER >> Loaded file at " << filePath);
	PRINT("MODEL LOADER >> Vertices(v): " << _vertPositions.size() << "  Texture Coordinates(vt): " << _texCoords.size() << "  Vertex Normals(vn): " << _normals.size());
}

ModelLoader::~ModelLoader()
{
}

void ModelLoader::GenerateIndexData(const std::string &data)
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

	
	std::vector<std::string> faces = ParseFaceData(data, 2, '/');

	for (int o = 0; o < faces.size(); o+=3)
	{
		//_faces.push_back(FaceData{ std::stoi(faces[o])-1,  std::stoi(faces[o + 1])-1, std::stoi(faces[o + 2])-1 }); // Store faces to create vertex data for opengl
		//_faces.push_back(FaceData{ std::stoi(faces[o])-1, std::stoi(faces[o + 1])-1, std::stoi(faces[o + 2])-1 }); // Store faces to create vertex data for opengl

		if (o % 3 == 0)
		{
			_indexData.push_back(std::stoi(faces[o])-1);	// Indices for opengl
		}
	}
}

// non separator = start of triple, look for first value, if after previous value the next character is a separtor/whtiespace, insert 0, repeat until a triple is formed
std::vector<std::string> ModelLoader::SeparateString(std::string line, int startPos, std::string separator) const
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

// WIP Different face index structures
// 1/2/3 4/8/6
std::vector<std::string> ModelLoader::ParseFaceData(std::string line, int startPos, char separator)
{
	std::vector<std::string> data;

	//PRINT(line);
	std::vector<std::string> _sss = SeparateString(line, startPos, " ");
	int index = line.find_first_not_of(separator, startPos); // Starting position to iterate
	for (int i = 0; i < _sss.size(); i++)
	{
		//PRINT(" " << _sss[i]);
		// 0/0/0
		for (int j = 0; j < _sss[i].size();)
		{
			int start = _sss[i].find_first_not_of("/", j);
			int end = _sss[i].find_first_of("/", start);

			//PRINT(" " << _sss[i].substr(start, end-start));
			data.push_back(_sss[i].substr(start, end - start));
			if (end == std::string::npos)
			{
				break;
			}
			else

			{
				j += end;
			}
		}

		if (_sss[i].find("/") == std::string::npos)
		{
			//PRINT(0);
			//PRINT(0);
			data.push_back("0");
			data.push_back("0");

		}
	}

	return data;
}