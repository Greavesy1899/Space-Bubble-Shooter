#include "OBJLoader.h"
#include <iostream>
#include <fstream>
#include <filesystem>
#include <string>
#include <sstream>

OBJLoader::OBJLoader()
{
}


OBJLoader::~OBJLoader()
{
}

void OBJLoader::ParseVertexLine(std::string line)
{
	int bType = -1;

	if (line.find("vt") == 0)
		bType = 0;
	else if (line.find("vn") == 0)
		bType = 1;
	else if (line.find("v") == 0)
		bType = 2;

	std::istringstream input;
	input.str(line);

	std::string tempBuf = "";

	int idx = 0;
	glm::vec3 newVec = glm::vec3();
	while (std::getline(input, tempBuf, ' '))
	{
		if (idx != 0 && !tempBuf.empty())
		{
			newVec[idx - 1] = stof(tempBuf);
		}

		if (!tempBuf.empty())
			idx++;
	}

	switch (bType)
	{
	case 0:
		this->texCoords.push_back(glm::vec2(newVec.x, newVec.y));
		break;
	case 1:
		this->normals.push_back(newVec);
		break;
	case 2:
		this->vertices.push_back(newVec);
		break;
	default:
		break;
	}
}

void OBJLoader::ParseFaceLine(std::string line)
{
	std::istringstream input;
	input.str(line);

	std::string tempBuf = "";

	while (std::getline(input, tempBuf))
	{
		std::istringstream c(line.substr(2));
		glm::ivec3 v = glm::ivec3();
		glm::ivec3 vt = glm::ivec3();
		glm::ivec3 vn = glm::ivec3();

		for (int i = 0; i != 3; i++)
		{
			char slash;
			c >> v[i];
			c >> slash;
			c >> vt[i];
			c >> slash;
			c >> vn[i];
			
			v[i]--;
			vt[i]--;
			vn[i]--;

			this->indices.push_back(v[i]);
			this->indices.push_back(vt[i]);
			this->indices.push_back(vn[i]);
		}
	}
}

bool OBJLoader::ParseOBJ(const char * file)
{
	if (!std::experimental::filesystem::exists(file))
	{
		std::cout << "Failed to locate model file: " << file << std::endl;
		return false;
	}

	std::ifstream inFile(file);

	while (inFile.good())
	{
		std::string line;
		std::getline(inFile, line);

		if (line.empty())
			continue;
		else if (line[0] == '#')
			continue;
		else if (line[0] == 'v')
			ParseVertexLine(line);
		else if (line[0] == 'f')
			ParseFaceLine(line);
	}
	return true;
}
