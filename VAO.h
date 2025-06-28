#ifndef VAO_CLASS_H
#define VAO_CLASS_H

#include<glad/glad.h>
#include"VBO.h"

class VAO
{
public: 
	// Reference ID of the Vertex Array Object
	// Generate a Vertex Array Object
	GLuint ID;
	VAO();

	// Link a VBO Attribute to the VAO using a specified layout
	// Bind the VAO
	// Unbind the VAO
	// Delete the VAO
	void LinkAttrib(VBO VBO, GLuint layout, GLuint numComponents, 
		GLenum type, GLsizeiptr stride, void* offset);
	void Bind();
	void Unbind();
	void Delete();
};

#endif
