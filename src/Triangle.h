#define GLEW_STATIC
#include <GL/glew.h>

#include "errorHandling.h"

class Triangle {
    public:
        // init with point coords
        Triangle(GLfloat x1, GLfloat y1, GLfloat x2, GLfloat y2, GLfloat x3, GLfloat y3);
        // init equilateral triangle on x y coords
        Triangle(GLfloat x, GLfloat y);

        //void move(GLfloat x, GLfloat y);
        //void moveApex(int inx, GLfloat x, GLfloat y);
        void draw(GLuint shaderProgram);
        void editCoords(float* data);
        void modifyColor(GLint var, GLfloat r, GLfloat g, GLfloat b);

        ~Triangle();
    private:
        GLfloat apex_array[6];
        GLuint buffer;
};