#pragma once

#include <vector>
#include <fstream>
#include <sstream>
#include <string>

#include "Logging.h"


struct FaceData
{
	int pos;
	int texCoord;
	int normal;

	bool operator==(const FaceData& rhs) const
	{
		return pos == rhs.pos; // or another approach as above
	}
};

class ModelLoader
{
public:
	ModelLoader(const char * filePath);
	~ModelLoader();

	std::vector<float> GetVertexData() const { return _vertexData; };
	std::vector<int> GetIndexData() const { return _indexData; };

private:
	std::vector<float> _vertexData;
	std::vector<int> _indexData;

	std::vector<float> _vertPositions;
	std::vector<float> _texCoords;
	std::vector<float> _normals;
	std::vector<FaceData> _faces;

	std::vector<std::string> SeparateString(std::string line, int startPos, std::string separator) const;
	void ParseFaces(const std::string &data);
};

