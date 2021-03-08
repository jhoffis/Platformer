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

    void uniformMatrix4(auto mat4f, const char *location) {
        int glslLocation = glGetUniformLocation(ID, location);
        if (glslLocation == -1)
            std::cout << "ERROR SHADER: " << location << std::endl;
        glUniformMatrix4fv(glslLocation, 1, GL_FALSE, mat4f);
    }
};


#endif //PLATFORMER_SHADER_H
