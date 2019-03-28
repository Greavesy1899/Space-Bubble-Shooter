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
	if (line.find("vt") == 0)
	{
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
		this->texCoords.push_back(glm::vec2(newVec.x, newVec.y));
	}
	else if (line.find("v") == 0)
	{
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
		this->vertices.push_back(newVec);
	}
	else if (line.find("vn") == 0)
	{
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
		this->normals.push_back(newVec);
	}
}

void OBJLoader::ParseFaceLine(std::string line)
{
	std::istringstream input;
	input.str(line);

	std::string tempBuf = "";

	while (std::getline(input, tempBuf, ' '))
	{
		if (!tempBuf.empty() && tempBuf != "f")
		{
			GLushort ind = std::stoi(tempBuf.substr(0, tempBuf.find('/')));
			this->indices.push_back(ind-1);
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
	return false;
}
