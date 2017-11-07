#pragma once
#include <string>
#include <GL/glew.h>

class Mesh
{

public:
	Mesh();
	~Mesh();

	//Load a mesh from a file
	bool loadFromFile(const std::string &file);

	//Release data from OpenGL
	void unload();

	unsigned int getNumFaces();
	unsigned int getNumVertices();

	//OpenGL buffers and objects
	GLuint vboVertices;
	GLuint vboUVs;
	GLuint vboNormals;
	GLuint vao = 0;

	unsigned int numFaces = 0;
	unsigned int numVertices = 0;

};