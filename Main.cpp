#include<iostream>
#include<glad/glad.h>
#include<GLFW/glfw3.h>



// Vertex Shader source code. GLSL version 4.60
const char* vertexShaderSource = "#version 460 core\n"
"layout (location = 0) in vec3 aPos;\n"
"void main()\n"
"{\n"
"	gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
"}\0";

// Fragment Shader source code
const char* fragmentShaderSource = "#version 460 core\n"
"out vec4 FragColor;\n"
"void main()\n"
"{\n"
"	FragColor = vec4(0.0f, 0.6f, 0.8f, 1.0f);\n"
"}\n\0";



int main()
{
	// Initialize GLFW, tell GLFW to use OpenGL version 4.6
	// Using CORE, rather than COMPATIBILITY. Cannot use deprecated functionalities.
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// Triangle vertex coordinates
	GLfloat vertices[] =
	{
		-0.5f, -0.5f * float(sqrt(3)) / 3, 0.0f, // Lower-left vertex
		0.5f, -0.5f * float(sqrt(3)) / 3, 0.0f, // Lower-right vertex
		0.0f, 0.5f * float(sqrt(3)) * 2 / 3, 0.0f // Top-center vertex
	};

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



	// Create Vertex Shader Object and get its reference
	// Attach vertexShaderSource to the Vertex Shader Object
	// Compile the Vertex Shader Object into machine code for GPU
	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	glCompileShader(vertexShader);

	// Create Fragment Shader Object and get its reference
	// Attach fragmentShaderSource to the Fragment Shader Object
	// Compile the Fragment Shader Object into machine code for GPU
	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	glCompileShader(fragmentShader);

	// Create Shader Program Object and get its reference
	// Attach Vertex & Fragment Shader Objects to Shader Program Object
	// Link/wrap the shaders into the Shader Program Object
	GLuint shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);

	// Vertex & Fragment Shader Objects are wrapped up and no longer needed
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);



	// Create reference containers for Vertex Array Object & Vertex Buffer Object
	// Generate VAO and VBO with 1 object each
	GLuint VAO, VBO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);

	// Make the VAO the current Vertex Array Object by binding it
	// Bind the VBO; specify that it's a GL_ARRAY_BUFFER
	// Add the vertices of the triangle into the VBO
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	// Configure the Vertex Attribute so OpenGL knows how to read the VBO
	// Enable the Vertex Attribute so OpenGL knows how to use it
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	// Bind both the VBO and VAO to 0 to prevent accidental modification
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);



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
		glUseProgram(shaderProgram);
		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES, 0, 3);

		// Swap the back buffer with the front buffer
		// Handle all GLFW events
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	// Delete all created objects
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteProgram(shaderProgram);

	// Delete window and terminate GLFW before ending the program
	glfwDestroyWindow(window);
	glfwTerminate();
	return 0;
}