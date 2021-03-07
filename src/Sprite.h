//
// Created by Jens Benz on 06.03.2021.
//

#ifndef PLATFORMER_SPRITE_H
#define PLATFORMER_SPRITE_H

#include <glad/glad.h>
#include <iostream>

class Sprite {
private:
    unsigned int shaderProgram, VBO, VAO;
public:
    Sprite();
    void render();
};


#endif //PLATFORMER_SPRITE_H
