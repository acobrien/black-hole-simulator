#ifndef EBO_CLASS_H
#define EBO_CLASS_H

#include<glad/glad.h>

class EBO
{
public:
	// Reference ID of the Element Buffer Object
	// Generate a Element Buffer Object and link it to indices
	GLuint ID;
	EBO(GLuint* indices, GLsizeiptr size);

	// Bind the EBO
	// Unbind the EBO
	// Delete the EBO
	void Bind();
	void Unbind();
	void Delete();
};

#endif
