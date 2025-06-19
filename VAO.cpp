#include"VAO.h"

// Generate a Vertex Array Object
VAO::VAO()
{
	glGenVertexArrays(1, &ID);
}

// Link a VBO to the VAO using a specified layout
void VAO::LinkVBO(VBO VBO, GLuint layout)
{
	VBO.Bind();
	glVertexAttribPointer(layout, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
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
