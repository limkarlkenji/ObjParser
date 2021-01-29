#include "ModelLoader.h"

/*
	Open file
*/
std::vector<float> ModelLoader::Open(const char * filePath)
{
	std::ifstream infile;

	std::vector<float> positions;
	std::vector<float> texCoords;
	std::vector<float> normals;

	infile.open(filePath);

	for (std::string currentLine; std::getline(infile, currentLine); )
	{
		if (currentLine.find("v ", 0) != currentLine.npos)
		{
			int oIndex = currentLine.find_first_not_of(" ", 2);			// Start search ignoring "v "
			std::string found;
			for (int i = oIndex; i < currentLine.size(); i = oIndex)
			{
				int start = currentLine.find_first_not_of(" ", oIndex);	// Look for next non-whitespace character
				int end = currentLine.find(" ", oIndex);				// Look for next whitespace character
				float val = std::stof(currentLine.substr(start, end));	// Create string from 'start' to 'end' then convert to float
				positions.push_back(val);								// Add to list

				oIndex = currentLine.find_first_not_of(" ", end);		// Update index to 'end'. This is where the next search should begin
			}
		}
		else if (currentLine.find("vt", 0) != currentLine.npos)
		{
			//PRINT("VT");

		}
		else if (currentLine.find("vn", 0) != currentLine.npos)
		{
			//PRINT("VN");

		}

	}
	infile.close();

	// Test code
	texCoords.push_back(1.0f);
	texCoords.push_back(0.0f);
	texCoords.push_back(1.0f);
	texCoords.push_back(1.0f);
	texCoords.push_back(0.0f);
	texCoords.push_back(1.0f);
	texCoords.push_back(0.0f);
	texCoords.push_back(0.0f);
	//for (int k = 0; k < 8; k++)
	//{
	//	texCoords.push_back(0.0f);
	//	texCoords.push_back(0.0f);
	//}

	for (int k = 0; k < 12; k++)
	{
		normals.push_back(0.0f);
		normals.push_back(0.0f);
		normals.push_back(0.0f);
	}
	//

	return Assemble(positions, texCoords, normals);
}

/*
	Assemble vertex data
*/
std::vector<float> ModelLoader::Assemble(const std::vector<float> &positions, const std::vector<float> &texCoords, const std::vector<float> &normals)
{
	std::vector<float> vertices;
	
	int vertexCount = positions.size() / 3; // Divide by 3 because we expect (x, y, z)

	for (int i = 0; i < vertexCount; i++)
	{
		for (int v = 0; v < 3; v++)
		{
			vertices.push_back(positions[(i * 3)+ v]);
			//PRINT(positions[(i * 3) + x]);
		}
		for (int vt = 0; vt < 2; vt++)
		{
			vertices.push_back(texCoords[(i * 2) + vt]);
		}

		for (int vn = 0; vn < 3; vn++)
		{
			vertices.push_back(normals[(i * 3) + vn]);

		}
	}

	return vertices;
}


