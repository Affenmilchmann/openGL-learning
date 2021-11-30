#pragma once

#define GLEW_STATIC
#include <GL/glew.h>

#include <iostream>
#include <vector>

void clearGLError();
void checkGLError();
void logShaderError(GLuint shader);
void logProgramError(GLuint program);