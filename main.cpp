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




static void glfwError(int id, const char* description) {
    
    std::cout << "Error ID: " << id << "\nDescription: " << description << "\n \n";
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

    //Vec3 Vertex Coordinate, vec2 Texture Coordinate
    GLfloat vertices[] = { 0.5f, -0.5f, 0.5f, 1.0f, 0.0f, //FRONT_BOTTOM_RIGHT
                           0.5f, 0.5f, 0.5f, 1.0f, 1.0f,  //FRONT_TOP_RIGHT
                          -0.5f, -0.5f, 0.5f, 0.0f, 0.0f, //FRONT_BOTTOM_LEFT
                          -0.5f, 0.5f, 0.5f, 0.0f, 1.0f,  // FRONT_TOP_LEFT

    };

    GLuint vertex_order[] = {0, 1, 2,
                             2, 3, 1};

    stbi_set_flip_vertically_on_load(true);
    int tex_width, tex_height, nrChannels;
    unsigned char* data = stbi_load("./Textures/tex1.png", &tex_width, &tex_height, &nrChannels, 0);

    GLuint texture;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, tex_width, tex_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(GL_TEXTURE_2D);


    Layout lay1(2, std::vector<unsigned int> {3, 2}, std::vector<unsigned int> {GL_FLOAT, GL_FLOAT}, std::vector<unsigned int> {0, 0});
    VBO vbo1(vertices, sizeof(vertices));
    EBO ebo1(vertex_order, sizeof(vertex_order));
    VAO vao1;
    ShaderProgram basicShader("./Shaders/BasicVertexShader.vrtx", "./Shaders/BasicFragmentShader.frgmt");

    vao1.LinkVBO(&vbo1, lay1);
    vao1.LinkEBO(&ebo1);

    Camera cam(glm::vec3(0.0f, 0.0f, 3.0f), glm::vec3(0.0f, 0.0f, -1.0f), glm::vec3(0.0f, 1.0f, 0.0f), 3.0f);

    unsigned int mod_loc;
    mod_loc = glGetUniformLocation(basicShader.ID, "model");

    vao1.Bind();
    basicShader.Activate();
    
    
    
    

    //Draw Loop
    while (!glfwWindowShouldClose(window)) {

        glClearColor(0.66f, 0.66f, 0.66f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        
        glm::mat4 model = glm::mat4(1.0f);
        model = glm::rotate(model, (float)glfwGetTime(), glm::vec3(0.5f, 1.0f, 1.0f));
        glUniformMatrix4fv(mod_loc, 1, GL_FALSE, glm::value_ptr(model));
        
        cam.HandleMovement(window);
        cam.Calculate(&basicShader, 45.0f, (float)window_width / (float)window_height, 0.01f, 100.0f);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        
        glfwSwapBuffers(window);
        glfwPollEvents();
    }


    basicShader.Delete();
    vao1.Delete();
    ebo1.Delete();
    vbo1.Delete();
    //Terminating a window
    glfwDestroyWindow(window);

    //Terminating GLFW
    glfwTerminate();

    //Exit Code
    return 0;
    
}