#include<iostream>
#include<glad/glad.h>
#include<GLFW/glfw3.h>

#include"shaderClass.h"
#include"VAO.h"
#include"VBO.h"
#include"EBO.h"

int main()
{

	// Triangle vertex coordinates. Scale X-values by 2160 / 3840 = 0.5625
	GLfloat vertices[] =
	{
		-0.5f * 0.5625, -0.5f * float(sqrt(3)) / 3, 0.0f, // Lower-left vertex
		0.5f * 0.5625, -0.5f * float(sqrt(3)) / 3, 0.0f, // Lower-right vertex
		0.0f * 0.5625, 0.5f * float(sqrt(3)) * 2 / 3, 0.0f, // Top-center vertex
		-0.25f * 0.5625, 0.5f * float(sqrt(3)) / 6, 0.0f, // Inner-left vertex
		0.25f * 0.5625, 0.5f * float(sqrt(3)) / 6, 0.0f, // Inner-right vertex
		0.0f * 0.5625, -0.5f * float(sqrt(3)) / 3, 0.0f // Bottom-center vertex
	};

	GLuint indices[] =
	{
		5, 3, 0, // Lower-left triangle
		1, 4, 5, // Lower-right triangle
		4, 2, 3 // Upper triangle
	};



	// Initialize GLFW, tell GLFW to use OpenGL version 4.6
	// Using CORE, rather than COMPATIBILITY. Cannot use deprecated functionalities.
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// Set up a 4k window named "Black Hole Simulator"
	// Handle failed window creation
	GLFWwindow* window = glfwCreateWindow(3840, 2160, "Black Hole Simulator", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}

	// Introduce window to current context
	// Load GLAD to configure OpenGL
	// Viewport goes from (0, 0) to (3840, 2160)
	glfwMakeContextCurrent(window);
	gladLoadGL();
	glViewport(0, 0, 3840, 2160);



	// Generate Shader object using shaders default.vert and default.frag
	Shader shaderProgram("default.vert", "default.frag");

	// Generate and bind the Vertex Array Object
	VAO VAO1;
	VAO1.Bind();

	// Generate Vertex Buffer Object and link it to vertices
	// Generate Element Buffer Object and link it to indices
	VBO VBO1(vertices, sizeof(vertices));
	EBO EBO1(indices, sizeof(indices));

	// Link VBO to VAO
	VAO1.LinkVBO(VBO1, 0);

	// Unbind objects to prevent accidental modification
	VAO1.Unbind();
	VBO1.Unbind();
	EBO1.Unbind();



	// Main while loop
	while (!glfwWindowShouldClose(window))
	{
		// Set background to black
		// Clear back buffer and assign new color to it
		glClearColor(0.00f, 0.00f, 0.00f, 1.0f); 
		glClear(GL_COLOR_BUFFER_BIT); 
		
		// Tell OpenGL to use this Shader Program
		// Tell OpenGL to use the VAO by binding it
		// Draw the triangle with the GL_TRIANGLES primitive
		shaderProgram.Activate();
		VAO1.Bind();
		glDrawElements(GL_TRIANGLES, 9, GL_UNSIGNED_INT, 0);

		// Swap the back buffer with the front buffer
		// Handle all GLFW events
		glfwSwapBuffers(window);
		glfwPollEvents();
	}



	// Delete all created objects
	VAO1.Delete();
	VBO1.Delete();
	EBO1.Delete();
	shaderProgram.Delete();

	// Delete window and terminate GLFW before ending the program
	glfwDestroyWindow(window);
	glfwTerminate();
	return 0;

}
