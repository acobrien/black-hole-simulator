#include"VAO.h"

// Generate a Vertex Array Object
VAO::VAO()
{
	glGenVertexArrays(1, &ID);
}

// Link a VBO Attribute to the VAO using a specified layout
void VAO::LinkAttrib(VBO VBO, GLuint layout, GLuint numComponents,
	GLenum type, GLsizeiptr stride, void* offset)
{
	VBO.Bind();
	glVertexAttribPointer(layout, numComponents, type, GL_FALSE, stride, offset);
	glEnableVertexAttribArray(layout);
	VBO.Unbind();
}

// Bind the VAO
void VAO::Bind()
{
	glBindVertexArray(ID);
}

// Unbind the VAO
void VAO::Unbind()
{
	glBindVertexArray(0);
}

// Delete the VAO
void VAO::Delete()
{
	glDeleteVertexArrays(1, &ID);
}
