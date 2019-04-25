#ifndef OBJ_LOADER_H
#define OBJ_LOADER_H
#include <vector>
#include <string>
#include "glm/glm.hpp"
#include "GL/glew.h"

class OBJLoader
{

	std::string parentFolder;

	void ParseMTLLine(std::string line);
	void ParseMTL(std::string& path);
	std::string ParseIndentLine(std::string line);
	void ParseVertexLine(std::string line);
	void ParseFaceLine(std::string line);

public:
	OBJLoader();
	~OBJLoader();

	std::vector<glm::vec3> vertices;
	std::vector<glm::vec3> normals;
	std::vector<glm::vec2> texCoords;
	std::vector<GLushort> indices;
	std::vector<std::pair<std::string, std::string>> materials;

	bool ParseOBJ(const char* file);
	
};
#endif