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
    Shader(const char* name);
    void destroy() {
        glDeleteProgram(ID);
    }

    void use()
    {
        glUseProgram(ID);
    }

    void setBool(const std::string &name, bool value) const
    {
        glUniform1i(glGetUniformLocation(ID, name.c_str()), (int)value);
    }
    void setInt(const std::string &name, int value) const
    {
        glUniform1i(glGetUniformLocation(ID, name.c_str()), value);
    }
    void setFloat(const std::string &name, float value) const
    {
        glUniform1f(glGetUniformLocation(ID, name.c_str()), value);
    }
};


#endif //PLATFORMER_SHADER_H
