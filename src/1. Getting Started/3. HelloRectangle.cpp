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
	GLFWwindow* window = glfwCreateWindow(800, 600, "Hello_Rectangle", NULL, NULL);
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

	unsigned int fragmentShader;
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
	//////////////////////////////////////////////////////



	//////////////////////////////////////////////////////
	//Shader Program (Linking The Shaders)
	unsigned int shaderProgram;
	shaderProgram = glCreateProgram();

	//Attaching Shaders
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);

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

	//Rectangle Initialization
	float vertices[] = {
		 0.5f, 0.5f, 0.0f, //top right
		 0.5f, -0.5f, 0.0f, //bottom right
		-0.5f, -0.5f, 0.0f,
		-0.5f, 0.5f, 0.0f
	};

	//Always Declare as Unsigned Int
	//Specify order of triangles vertices [2 triangles]
	unsigned int indices[] = {
		0, 1, 3,
		1, 2, 3
	};

	//Vertex Buffer to send all vertices at once
	//Also, Vertex Array to store Vertex Buffer Configurations
	//EBO As WEll now [to store indices]
	unsigned int VBO, VAO, EBO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO); //Do Not Forget Generation

	//Bind Vertex Array First
	glBindVertexArray(VAO);

	//Bind and Set Data
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	//Bind EBO [For indices]
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
	

	//How to interpret the vertex data
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);


	//Unbind Buffer
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	//KEEP THE EBO BOUND [AS LONG AS VAO IS ACTIVE]
	
	//Unbind Vertex Array
	glBindVertexArray(0);

	while (!glfwWindowShouldClose(window))
	{

		processInput(window);

		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		//Use Shader Program
		glUseProgram(shaderProgram);

		glBindVertexArray(VAO); //Bind after every call to be called again
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

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