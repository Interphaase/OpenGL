#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "ShaderProgram.h"
#include "VBO.h"
#include "EBO.h"
#include "VAO.h"
#include "stb_image.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "Camera.h"
#include "Texture.h"
#include "Cube_Object.h"

double MOUSE_X=0, MOUSE_Y=0;

static void glfwError(int id, const char* description) {
    
    std::cout << "Error ID: " << id << "\nDescription: " << description << "\n \n";
}

void mousePosition(GLFWwindow* window, double x_pos, double y_pos) {
    MOUSE_X = x_pos;
    MOUSE_Y = y_pos;
}

int main(void) {

    //Setting window parameters
    int window_height = 800, window_width = 800;

    //Setting function for handling errors with OpenGL
    glfwSetErrorCallback(&glfwError);
    

    

    //Initializing OpenGL
    glfwInit();

    //Setting OpenGL version to 3.3x
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    //Creating a Window object for OpenGL
    GLFWwindow* window = glfwCreateWindow(window_width, window_height, "Cool Window", NULL, NULL);

    //Setting mouse position callback
    glfwSetCursorPosCallback(window, mousePosition);

    //Closing Program if failed to create a window
    if (window == NULL) {
        std::cout << "Cannot create a window (GLFW)...\n";
        glfwTerminate();
        return -1;
    }

    //Setting current OpenGL context to window object
    glfwMakeContextCurrent(window);

    //Initializing GLAD
    gladLoadGL();

    //Setting OpenGL render range in window
    glViewport(0, 0, window_width, window_height);

    

    //Creating Texture
    Texture tex1(0, "./Textures/tex1.png");

    //Creating Shader
    ShaderProgram basicShader("./Shaders/BasicVertexShader.vrtx", "./Shaders/BasicFragmentShader.frgmt");

    //Creating Camera
    Camera cam(glm::vec3(0.0f, 0.0f, 3.0f), glm::vec3(0.0f, 0.0f, -1.0f), glm::vec3(0.0f, 1.0f, 0.0f), 3.0f,
                45.0f, (float)window_width / (float)window_height, 0.01f, 100.0f, 10.0f);
    
    //Creating Cube
    CubeObject cube(glm::vec3(0.0f, 0.0f, 0.0f), &basicShader, &tex1, &cam);

    glEnable(GL_DEPTH_TEST);

    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    //Draw Loop
    while (!glfwWindowShouldClose(window)) {

        glClearColor(0.66f, 0.66f, 0.66f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        cam.HandleMovement(window, MOUSE_X, MOUSE_Y);
        cube.Draw();
        
        
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    basicShader.Delete();

    //Terminating a window
    glfwDestroyWindow(window);

    //Terminating GLFW
    glfwTerminate();

    //Exit Code
    return 0;
    
}