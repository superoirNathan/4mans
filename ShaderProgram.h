#pragma once

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <string>
class ShaderProgram
{

public:
	ShaderProgram();
	~ShaderProgram();

	//Load a vertex shader and a fragment shader and place them in a program
	bool load(const std::string &vertFile, const std::string &fragFile);

	bool isLoaded() const;

	//Unload Shader sata from OpenGL
	void unload();

	bool linkProgram();

	//Use the shader
	void bind() const;

	//Detach the shader
	void unbind();

	//Requires a re-linnk before OpenGL will register the change
	void addAttribute(unsigned int index, const std::string &attribName);

	//Returns -1 if the attribute doesnt exist
	int getAttribLocation(const std::string &attribName);

	//Returns -1 if the uniform doesnt exist
	int getUniformLocation(const std::string &uniformName);

	//Send uniform data to the shaders
	void sendUniform(const std::string &name, int integer);
	void sendUniform(const std::string &name, unsigned int unsignedInteger);
	void sendUniform(const std::string &name, float scalar);
	void sendUniform(const std::string &name, const glm::vec2 &vector);
	void sendUniform(const std::string &name, const glm::vec3 &vector);
	void sendUniform(const std::string &name, const glm::vec4 &vector);

	void sendUniformMat3(const std::string &name, float *matrix, bool transpose);
	void sendUniformMat4(const std::string &name, float *matrix, bool transpose);

private:
	bool loaded = false;
	
	GLuint vertexShader = 0;
	GLuint fragShader = 0;
	GLuint program = 0;

	std::string readfile(const std::string &fileName) const;

	bool compileShader(GLuint shader) const;

	void outputShaderLog(GLuint shader) const;

	void outoutProgramLog() const;

};