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
    GLFWwindow* window = glfwCreateWindow(800, 600, "LearnOpenGL", NULL, NULL);
    if(window==nullptr) 
    {
        cout << "Failed to Create GLFW window" << endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);

    //Setting GLAD (passing function to load the address of the OpenGL function pointers)
    if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress) ) 
    {
        cout << "Failed to initialize GLAD" << endl;
    }

    //Setting Viewport
    glViewport(0, 0, 800, 600);
    //Setting the Viewport Callback
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    while(!glfwWindowShouldClose(window)) 
    {
        processInput(window);

        //Checks all Events
        glfwPollEvents();
        //Swap back and front Buffers
        glfwSwapBuffers(window);
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
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