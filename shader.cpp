#include "shader.h"
using namespace std;

GLuint LoadShaders(const char* vertex_file_path, const char* fragment_file_path) {
	GLuint vertexShaderID = glCreateShader(GL_VERTEX_SHADER);
	GLuint fragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);

	string vertexShaderCode;
	ifstream vertexShaderStream(vertex_file_path, ios::in);
	if (vertexShaderStream.is_open()) {
		stringstream sstr;
		sstr << vertexShaderStream.rdbuf();
		vertexShaderCode = sstr.str();
		vertexShaderStream.close();
	}
	else {
		printf("Unable to open %s\n", vertex_file_path);
		getchar();
		return 0;
	}

	string fragmentShaderCode;
	ifstream fragmentShaderStream(fragment_file_path, ios::in);
	if (fragmentShaderStream.is_open()) {
		stringstream sstr;
		sstr << fragmentShaderStream.rdbuf();
		fragmentShaderCode = sstr.str();
		fragmentShaderStream.close();
	}
	else {
		printf("Unable to open %s\n", fragment_file_path);
		getchar();
		return 0;
	}

	GLint Result = GL_FALSE;
	int infoLogLength;

	printf("Compiling shader: %s\n", vertex_file_path);
	char const* vertexSourcePointer = vertexShaderCode.c_str();
	glShaderSource(vertexShaderID, 1, &vertexSourcePointer, NULL);
	glCompileShader(vertexShaderID);

	glGetShaderiv(vertexShaderID, GL_COMPILE_STATUS, &Result);
	glGetShaderiv(vertexShaderID, GL_INFO_LOG_LENGTH, &infoLogLength);
	if (infoLogLength > 0) {
		vector<char> vertexShaderErrorMessage(infoLogLength + 1);
		glGetShaderInfoLog(vertexShaderID, infoLogLength, NULL, &vertexShaderErrorMessage[0]);
		printf("%s\n", &vertexShaderErrorMessage[0]);
	}

	printf("Compiling shader: %s\n", fragment_file_path);
	char const* fragmentSourcePointer = fragmentShaderCode.c_str();
	glShaderSource(fragmentShaderID, 1, &fragmentSourcePointer, NULL);
	glCompileShader(fragmentShaderID);

	glGetShaderiv(fragmentShaderID, GL_COMPILE_STATUS, &Result);
	glGetShaderiv(fragmentShaderID, GL_INFO_LOG_LENGTH, &infoLogLength);
	if (infoLogLength > 0) {
		vector<char> fragmentShaderErrorMessage(infoLogLength + 1);
		glGetShaderInfoLog(fragmentShaderID, infoLogLength, NULL, &fragmentShaderErrorMessage[0]);
		printf("%s\n", &fragmentShaderErrorMessage[0]);
	}

	printf("Linking Program\n");
	GLuint ProgramID = glCreateProgram();
	glAttachShader(ProgramID, vertexShaderID);
	glAttachShader(ProgramID, fragmentShaderID);
	glLinkProgram(ProgramID);

	glGetProgramiv(ProgramID, GL_LINK_STATUS, &Result);
	glGetProgramiv(ProgramID, GL_INFO_LOG_LENGTH, &infoLogLength);
	if (infoLogLength > 0) {
		vector<char> programErrorMessage(infoLogLength + 1);
		glGetProgramInfoLog(ProgramID, infoLogLength, NULL, &programErrorMessage[0]);
	}

	glDetachShader(ProgramID, vertexShaderID);
	glDetachShader(ProgramID, fragmentShaderID);
	glDeleteShader(vertexShaderID);
	glDeleteShader(fragmentShaderID);

	return ProgramID;
}
