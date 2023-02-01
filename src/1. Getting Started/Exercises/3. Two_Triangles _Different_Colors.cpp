#include <glad/glad.h>;
#include <GLFW/glfw3.h>;
#include <iostream>
using namespace std;
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);
int main(void)
{

	//Initializing GLFW
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	//Setting GLFW Window
	GLFWwindow* window = glfwCreateWindow(800, 600, "Hello_Triangle", NULL, NULL);
	if (window == nullptr)
	{
		cout << "Failed to Create GLFW window" << endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);

	//Setting GLAD (passing function to load the address of the OpenGL function pointers)
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		cout << "Failed to initialize GLAD" << endl;
	}

	//Setting Viewport
	glViewport(0, 0, 800, 600);
	//Setting the Viewport Callback
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	//////////////////////////////////////////////////////
	//Vertex Shader
	const char* vertexShaderSource =
		"#version 330 core\n"
		"layout(location = 0) in vec3 aPos; \n"
		"void main()\n"
		"{\n"
		"	gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0); \n"
		"}\0";

	//Compiling the Shader
	unsigned int vertexShader;
	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	glCompileShader(vertexShader);

	//Checking for Errors
	int success;
	char infoLog[512];
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);

	if (!success)
	{
		glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
		cout << "Error::Compiling the Vertex Shader Failed" << endl << infoLog << endl;
	}
	//////////////////////////////////////////////////////


	//////////////////////////////////////////////////////
	// Fragment Shader
	const char* fragmentShaderSource =
		"#version 330 core\n"
		"out vec4 FragColor; \n"
		"void main()\n"
		"{\n"
		"FragColor = vec4(1.0, 0.5, 0.2, 1.0); \n"
		"}\0";

	// 2nd Fragment Shader
	const char* fragmentShaderSource2 =
		"#version 330 core\n"
		"out vec4 FragColor; \n"
		"void main()\n"
		"{\n"
		"FragColor = vec4(1.0, 1.0, 0.0, 1.0); \n" //Yellow = R + G
		"}\0";

	unsigned int fragmentShader, fragmentShaderYellow;
	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	glCompileShader(fragmentShader);

	int fragmentSucess;
	char fragmentInfoLog[512];
	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &fragmentSucess);

	if (!fragmentSucess)
	{
		glGetShaderInfoLog(fragmentShader, 512, NULL, fragmentInfoLog);
		cout << "Error::Compiling Fragment Shader Failed\n" << fragmentInfoLog << endl;
	}

	////////////////////////////////////////////////////////////
	fragmentShaderYellow = glCreateShader(GL_FRAGMENT_SHADER);

	glShaderSource(fragmentShaderYellow, 1, &fragmentShaderSource2, NULL);
	glCompileShader(fragmentShaderYellow);

	glGetShaderiv(fragmentShaderYellow, GL_COMPILE_STATUS, &fragmentSucess);

	if (!fragmentSucess)
	{
		glGetShaderInfoLog(fragmentShaderYellow, 512, NULL, fragmentInfoLog);
		cout << "Error::Compiling Fragment Shader Failed\n" << fragmentInfoLog << endl;
	}
	//////////////////////////////////////////////////////



	//////////////////////////////////////////////////////
	//Shader Program (Linking The Shaders)
	unsigned int shaderProgram, shaderProgramYellow;
	shaderProgram = glCreateProgram();
	shaderProgramYellow = glCreateProgram();

	//Attaching Shaders
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgramYellow, vertexShader);


	glAttachShader(shaderProgram, fragmentShader);
	glAttachShader(shaderProgramYellow, fragmentShaderYellow);

	glLinkProgram(shaderProgram);
	glLinkProgram(shaderProgramYellow);
	//Checking for Linking Errors
	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
		cout << "Error::Linking Shader Program Failed\n" << infoLog << endl;
	}

	//Deleting Shaders after creating the program
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	//////////////////////////////////////////////////////

	//Triangle Initialization
	float vertices1[] = {
		//1st
		0.25f, 0.25f, 0.0f,
		0.25f, -0.25f, 0.0f,
		0.75f, -0.25f, 0.0f,

	};
	float vertices2[] = {

		//2nd
		0.25f, -0.25f, 0.0f, //bottom right
		-0.25f, -0.25f, 0.0f,
		-0.25f, 0.25f, 0.0f
	};

	//Vertex Buffer to send all vertices at once
	//Also, Vertex Array to store Vertex Buffer Configurations
	unsigned int VBO1, VBO2, VAO1, VAO2;
	glGenBuffers(1, &VBO1);
	glGenVertexArrays(1, &VAO1);
	glGenBuffers(1, &VBO2);
	glGenVertexArrays(1, &VAO2);

	//Bind Vertex Array First
	glBindVertexArray(VAO1);

	//Bind and Set Data
	glBindBuffer(GL_ARRAY_BUFFER, VBO1);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices1), vertices1, GL_STATIC_DRAW);

	//How to interpret the vertex data
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);


	//Bind 2nd VAO
	glBindVertexArray(VAO2);

	//Bind 2nd VBO and Set Data
	glBindBuffer(GL_ARRAY_BUFFER, VBO2);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices2), vertices2, GL_STATIC_DRAW);

	//How to interpret the vertex data
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);


	//Unbind Buffer
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	while (!glfwWindowShouldClose(window))
	{

		processInput(window);

		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		//Use Shader Program
		glUseProgram(shaderProgram);

		glBindVertexArray(VAO1); //Bind after every call to be called again
		glDrawArrays(GL_TRIANGLES, 0, 3);


		//Use 2nd Shader Program
		glUseProgram(shaderProgramYellow);
		glBindVertexArray(VAO2); //Bind after every call to be called again
		glDrawArrays(GL_TRIANGLES, 0, 3);

		//Checks all Events
		glfwPollEvents();
		//Swap back and front Buffers
		glfwSwapBuffers(window);


	}

	glfwTerminate();
	return 0;
}

//Callback to Adjust the Viewport on Resize
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

//Processing Input Keys
void processInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
		glfwSetWindowShouldClose(window, true);
	}
}