#include "errorHandling.h"

void clearGLError() {
    while (glGetError()) {}
}

void checkGLError() {
    while (GLenum err = glGetError()) 
        std::cout << "[OpenGL Error] " << err << std::endl;
}

void logShaderError(GLuint shader) {
    GLint compiled = 0;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &compiled);
    if (compiled == GL_FALSE) {
        GLint maxL = 0;
        glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &maxL);

        std::vector<GLchar> errorLog(maxL);
        glGetShaderInfoLog(shader, maxL, &maxL, &errorLog[0]);

        std::cout << "[OpenGL Shader Error] shader:" << shader << std::endl;
        for (GLchar c: errorLog)
            std::cout << c;
        std::cout << std::endl;
    }
    else
        std::cout << "[OpenGL info] shader id=" << shader << " is compiled." << std::endl;
}

void logProgramError(GLuint program) {
    GLint good = 0;
    glGetProgramiv(program, GL_LINK_STATUS, &good);
    if (good == GL_FALSE) {
        GLint maxL = 0;
        glGetProgramiv(program, GL_INFO_LOG_LENGTH, &maxL);
        std::vector<GLchar> errorLog(maxL);
        glGetProgramInfoLog(program, maxL, &maxL, &errorLog[0]);

        std::cout << "[OpenGL shader program Error] program id=" << program <<std::endl;
        for (GLchar c: errorLog)
            std::cout << c;
        std::cout << std::endl;
    }
    else
        std::cout << "[OpenGL info] program id=" << program << " is linked." << std::endl;
}