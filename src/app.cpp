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

const char* fragmentShaderCode1 = R"glsl(
    #version 330 core
    out vec4 FragColor;

    void main()
    {
        FragColor = vec4(0.9f, 0.4f, 0.8f, 1.0f);
    } 
)glsl";

const char* fragmentShaderCode2 = R"glsl(
    #version 330 core
    out vec4 FragColor;

    void main()
    {
        FragColor = vec4(0.95f, 0.9f, 0.05f, 1.0f);
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

    // shaders initialization, compilation
    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderCode, NULL);
    glCompileShader(vertexShader);
    logShaderError(vertexShader);

    GLuint fragmentShader1 = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader1, 1, &fragmentShaderCode1, NULL);
    glCompileShader(fragmentShader1);
    logShaderError(fragmentShader1);

    GLuint fragmentShader2 = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader2, 1, &fragmentShaderCode2, NULL);
    glCompileShader(fragmentShader2);
    logShaderError(fragmentShader2);

    // programs init, linking
    GLuint shaderProgram1 = glCreateProgram();
    glAttachShader(shaderProgram1, vertexShader);
    glAttachShader(shaderProgram1, fragmentShader1);
    glLinkProgram(shaderProgram1);
    logProgramError(shaderProgram1);

    GLuint shaderProgram2 = glCreateProgram();
    glAttachShader(shaderProgram2, vertexShader);
    glAttachShader(shaderProgram2, fragmentShader2);
    glLinkProgram(shaderProgram2);
    logProgramError(shaderProgram2);

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader1);  
    glDeleteShader(fragmentShader2);

    // vao vbo stuff

    GLfloat vertices1[] = {
        // first triangle
        -0.9f, -0.5f, 0.0f,  // left 
        -0.0f, -0.5f, 0.0f,  // right
        -0.45f, 0.5f, 0.0f,  // top 
    }; 

    GLfloat vertices2[] = {
        // second triangle
         0.0f,  0.5f, 0.0f,  // left
         0.9f,  0.5f, 0.0f,  // right
         0.45f,-0.5f, 0.0f   // top 
    };

    GLuint vao1, vbo1, vao2, vbo2;
    glGenVertexArrays(1, &vao1);
    glGenBuffers(1, &vbo1);
    glGenVertexArrays(1, &vao2);
    glGenBuffers(1, &vbo2);

    //FIRST triangle binding and assigning data, vertex format
    glBindVertexArray(vao1);

    glBindBuffer(GL_ARRAY_BUFFER, vbo1);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices1), vertices1, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 3, (void*)0);
    glEnableVertexAttribArray(0);

    //SECOND triangle binding and assigning data, vertex format
    glBindVertexArray(vao2);

    glBindBuffer(GL_ARRAY_BUFFER, vbo2);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices2), vertices2, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 3, (void*)0);
    glEnableVertexAttribArray(0);

    //zero unbinds any bound buffers, vertex objects
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
    // end

    float ang = 0;
    float rotAng = 0;
    int stage = 0;
    const float ANGLE_120_DEGR = 120 * M_PI/180;
    float* positions = new float[6];
    
    // this switches drawing to framed polygons
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

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

        glUseProgram(shaderProgram1);
        glBindVertexArray(vao1);
        glDrawArrays(GL_TRIANGLES, 0, 6);
        glUseProgram(shaderProgram2);
        glBindVertexArray(vao2);
        glDrawArrays(GL_TRIANGLES, 0, 6);

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();

        checkGLError();
    }


    glfwTerminate();
    return 0;
}