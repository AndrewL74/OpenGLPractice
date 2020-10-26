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

#include "shader.h"

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
	GLFWwindow* window;
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

	/*
	* Tutorial02: Draw a triangle using OpenGL 3
	* http://www.opengl-tutorial.org/beginners-tutorials/tutorial-2-the-first-triangle/
	* The tutorial does a poor job explaining where in the program to add the new code segments. I advise referencing
	* the project's github for more clear instruction. Also the step to add the "glClearColor..." line of code was
	* missing and later referenced as if it had already been added
	*/

	glClearColor(0.0f, 0.0f, 0.4f, 0.0f);  //This step was missing in Tutorial02's instructions

	//Create a Vertex Array Object and set it as the current VAO
	GLuint VertexArrayID;
	glGenVertexArrays(1, &VertexArrayID);
	glBindVertexArray(VertexArrayID);

	//Load Shaders
	GLuint programID = LoadShaders("SimpleVertexShader.vertexshader", "SimpleFragmentShader.fragmentshader");

	//Vertices of the triangle
	static const GLfloat g_vertex_buffer_data[] = {
		-1.0f, -1.0f, 0.0f,
		1.0f, -1.0f, 0.0f,
		0.0f, 1.0f, 0.0f
	};

	GLuint vertexbuffer;  //Declare a vertex buffer
	glGenBuffers(1, &vertexbuffer);  //Initialize/generate a buffer and store in vertexbuffer
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);  //Bind the buffer to GL_ARRAY_BUFFER
	//Creates and initializes a buffer object's data store
	//glBufferData(GLenum target, GLsizeiptr size, const void* data, GLenum usage)
	glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW);

	do {
		// Clear the screen. It's not mentioned before Tutorial 02, but it can cause flickering, so it's there nonetheless.
		glClear(GL_COLOR_BUFFER_BIT);

		glUseProgram(programID);

		glEnableVertexAttribArray(0);  //Open AttribArray
		glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
		//Define an array of generic vertex attribute data
		//glVertexAttribPointer(GLuint index, GLint size, GLenum type, GLboolean normalized, GLsizei stride, const void* pointer)
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

		//Draw arrays of type triangles from vertex 0 and stoping after drawing 3 vertices
		glDrawArrays(GL_TRIANGLES, 0, 3);
		glDisableVertexAttribArray(0);  //Close AttribArray

		// Swap buffers
		glfwSwapBuffers(window);
		glfwPollEvents();

	} // Check if the ESC key was pressed or the window was closed
	while (glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS &&
		glfwWindowShouldClose(window) == 0);

	//Cleanup Vertex Buffer Objects
	glDeleteBuffers(1, &vertexbuffer);
	glDeleteVertexArrays(1, &VertexArrayID);
	glDeleteProgram(programID);

	glfwTerminate();

	return 0;
}
