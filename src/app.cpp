#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <math.h>
#include <vector>

#include "errorHandling.h"

const char* vertexShaderCode = R"glsl(
    #version 330 core
    layout (location = 0) in vec3 aPos;

    void main()
    {
        gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);
    }
)glsl";

const char* fragmentShaderCode = R"glsl(
    #version 330 core
    out vec4 FragColor;

    void main()
    {
        FragColor = vec4(0.9f, 0.4f, 0.8f, 1.0f);
    } 
)glsl";

int main(void)
{
    GLFWwindow* window;
    bool end = false;

    /* Initialize the library */
    if (!glfwInit())
        return -1;

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(640, 640, "Hello World", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    if (glewInit() != GLEW_OK)
        std::cout << "Fuck" << "\n";

    std::cout << glGetString(GL_VERSION) << std::endl;

    // shaders 
    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderCode, NULL);
    glCompileShader(vertexShader);
    logShaderError(vertexShader);

    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderCode, NULL);
    glCompileShader(fragmentShader);
    logShaderError(fragmentShader);

    GLuint shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);
    logProgramError(shaderProgram);

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);  

    // vao vbo stuff

    float vertices[] = {
        -0.5f, -0.5f, 0.0f,
        0.5f, -0.5f, 0.0f,
        0.0f,  0.5f, 0.0f
    }; 

    GLuint vao, vbo;
    glGenVertexArrays(1, &vao);
    glGenBuffers(1, &vbo);

    glBindVertexArray(vao);

    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 3, (void*)0);
    glEnableVertexAttribArray(0);

    //zero unbinds any bound buffers, vertex objects
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
    // end

    float ang = 0;
    float rotAng = 0;
    int stage = 0;
    const float ANGLE_120_DEGR = 120 * M_PI/180;
    float* positions = new float[6];
    
    // this switches drawing to framed polygons
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    // enabling all we need
    glUseProgram(shaderProgram);
    glBindVertexArray(vao);

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window) && !end)
    {
        /*float val = abs(sin(ang));
        
        glUniform3f(uniColor, val * (stage == 0), val * (stage == 1), val * (stage == 2));
        rotAng += 0.01;
        positions[0] = 0.8 * sin(rotAng);
        positions[1] = 0.8 * cos(rotAng);
        positions[2] = 0.8 * sin(rotAng + ANGLE_120_DEGR);
        positions[3] = 0.8 * cos(rotAng + ANGLE_120_DEGR);
        positions[4] = 0.8 * sin(rotAng + ANGLE_120_DEGR * 2);
        positions[5] = 0.8 * cos(rotAng + ANGLE_120_DEGR * 2);
        

        ang += 0.01;
        if (ang >= M_PI) {
            ang = 0;
            stage++;
            if (stage == 3)
                stage = 0;
        }*/

        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);

        glDrawArrays(GL_TRIANGLES, 0, 3);

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }


    glfwTerminate();
    return 0;
}