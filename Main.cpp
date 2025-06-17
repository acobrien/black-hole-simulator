#include<iostream>
#include<glad/glad.h>
#include<GLFW/glfw3.h>

int main()
{
	glfwInit(); // Initialize GLFW

	// Tell GLFW to use OpenGL version 4.6 [ major . minor ]
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);

	// Using CORE, rather than COMPATIBILITY. Cannot use deprecated functionalities.
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// Set up a 4k window named "Black Hole Simulator"
	GLFWwindow* window = glfwCreateWindow(3840, 2160, "Black Hole Simulator", NULL, NULL);

	if (window == NULL) // Handle failed window creation
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(window); // Introduce window to current context

	gladLoadGL(); // Load GLAD to configure OpenGL

	glViewport(0, 0, 3840, 2160); // Viewport goes from (0, 0) to (3840, 2160)
	glClearColor(0.02f, 0.01f, 0.03f, 1.0f); // Set background to slight purple hue
	glClear(GL_COLOR_BUFFER_BIT); // Clear back buffer and assign new color to it
	glfwSwapBuffers(window); // Swap the back buffer with the front buffer

	// Main while loop
	while (!glfwWindowShouldClose(window))
	{
		glfwPollEvents(); // Handle all GLFW events
	}

	// Delete window and terminate GLFW before ending the program
	glfwDestroyWindow(window);
	glfwTerminate();
	return 0;
}