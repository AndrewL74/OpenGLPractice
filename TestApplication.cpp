/*
* OpenGL Tutorials courtesy of http://www.opengl-tutorial.org/beginners-tutorials/
* Goals: Properly setup and use an OpenGL environment
* Rather than download opengl_tutorial's project files, I attempted to recreate their projects from scratch.
* Most of the code is still copied from the tutorial webpages with an emphasis on typing it out by hand instead
* of copying/pasting.
*/

#include<iostream>
#include<stdio.h>
#include<stdlib.h>
#include<GL/glew.h> //Need to import glew.h before glfw3.h; Order matters
#include<GLFW/glfw3.h>

//#include<glm/glm.hpp>
//using namespace glm;

int main() {

	/*
	* Tutorial01: Initial setup and open a blank window
	* http://www.opengl-tutorial.org/beginners-tutorials/tutorial-1-opening-a-window/
	* Lessons Learned:
	*	Linking can be complex, properly read the documentation
	*	Watch out for version discrepancies, Win32 libraries may not work in Win64 environments
	*	If building from scratch GLEW_STATIC will need to be defined in the preprocessor or by using #define GLEW_SATIC prior to #include<GL/glew.h>.
	*	Also the following libraries will need to be linked/included {glew32s.lib; glfw3.lib; opengl32.lib}
	*/

	glewExperimental = true;
	if (!glfwInit()) {
		fprintf(stderr, "Failed to initialize GLFW\n");
		return -1;
	}

	glfwWindowHint(GLFW_SAMPLES, 4); // 4x antialiasing
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); // We want OpenGL 3.3
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // To make MacOS happy; should not be needed
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); // We don't want the old OpenGL 

	// Open a window and create its OpenGL context
	GLFWwindow* window; // (In the accompanying source code, this variable is global for simplicity)
	window = glfwCreateWindow(1024, 768, "Tutorial 01", NULL, NULL);
	if (window == NULL) {
		fprintf(stderr, "Failed to open GLFW window. If you have an Intel GPU, they are not 3.3 compatible. Try the 2.1 version of the tutorials.\n");
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window); // Initialize GLEW
	glewExperimental = true; // Needed in core profile
	if (glewInit() != GLEW_OK) {
		fprintf(stderr, "Failed to initialize GLEW\n");
		return -1;
	}

	// Ensure we can capture the escape key being pressed below
	glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);

	do {
		// Clear the screen. It's not mentioned before Tutorial 02, but it can cause flickering, so it's there nonetheless.
		glClear(GL_COLOR_BUFFER_BIT);

		// Draw nothing, see you in tutorial 2 !

		// Swap buffers
		glfwSwapBuffers(window);
		glfwPollEvents();

	} // Check if the ESC key was pressed or the window was closed
	while (glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS &&
		glfwWindowShouldClose(window) == 0);

	return 0;
}
