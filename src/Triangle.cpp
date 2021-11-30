#include "Triangle.h"

Triangle::Triangle(GLfloat x1, GLfloat y1, GLfloat x2, GLfloat y2, GLfloat x3, GLfloat y3) {
    apex_array[0] = x1; apex_array[1] = y1;
    apex_array[2] = x2; apex_array[3] = y2;
    apex_array[4] = x3; apex_array[5] = y3;

    glGenBuffers(1, &buffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(apex_array), apex_array, GL_DYNAMIC_DRAW);
}

void Triangle::draw(GLuint shaderProgram) {
    glBindBuffer(GL_ARRAY_BUFFER, buffer);
    glUseProgram(shaderProgram);
    glDrawArrays(GL_TRIANGLES, 0, 3);
}

void Triangle::editCoords(float* data) {
    glBindBuffer(GL_ARRAY_BUFFER, buffer);
    
        clearGLError();
    glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(data), data);
    
        checkGLError();
}

Triangle::~Triangle() {
    delete apex_array;
    glDeleteBuffers(1, &buffer);
}