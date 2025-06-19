#ifndef VBO_CLASS_H
#define VBO_CLASS_H

#include<glad/glad.h>

class VBO
{
public: 
	// Reference ID of the Vertex Buffer Object
	// Generate a Vertex Buffer Object and link it to vertices
	GLuint ID;
	VBO(GLfloat* vertices, GLsizeiptr size);

	// Bind the VBO
	// Unbind the VBO
	// Delete the VBO
	void Bind();
	void Unbind();
	void Delete();
};

#endif
