#ifndef SHADER_CLASS_H
#define SHADER_CALSS_H

#include<glad/glad.h>
#include<string>
#include<fstream>
#include<sstream>
#include<iostream>
#include<cerrno>

std::string get_file_contents(const char* filename);

class Shader
{
public:
	GLuint ID; // Shader Program reference ID

	// Build Shader Program with vertex and fragment shaders
	Shader(const char* vertexFile, const char* fragmentFile);

	// Activate & Delete the Shader Program
	void Activate();
	void Delete();
};

#endif