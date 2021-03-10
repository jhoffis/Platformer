//
// Created by Jens Benz on 07.03.2021.
//

#ifndef PLATFORMER_SHADER_H
#define PLATFORMER_SHADER_H

#include <glad/glad.h> // include glad to get all the required OpenGL headers
#include <filesystem>

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>


class Shader
{
public:
    // the program ID
    unsigned int ID;

    // constructor reads and builds the shader
    explicit Shader(const char* name);
    void destroy() const {
        glDeleteProgram(ID);
    }

    void use() const {
        glUseProgram(ID);
    }

    void uniformBool(bool value, const char *location) const
    {
        glUniform1i(glGetUniformLocation(ID, location), (int)value);
    }
    void uniformInt(int value, const char *location) const
    {
        glUniform1i(glGetUniformLocation(ID, location), value);
    }
    void uniformFloat(float value, const char *location) const
    {
        glUniform1f(glGetUniformLocation(ID, location), value);
    }

    void uniformMatrix4(auto mat4f, const char *location) {
        int glslLocation = glGetUniformLocation(ID, location);
        if (glslLocation == -1)
            std::cout << "ERROR SHADER: " << location << std::endl;
        glUniformMatrix4fv(glslLocation, 1, GL_FALSE, mat4f);
    }
};


#endif //PLATFORMER_SHADER_H
