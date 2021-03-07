//
// Created by Jens Benz on 06.03.2021.
//

#ifndef PLATFORMER_SPRITE_H
#define PLATFORMER_SPRITE_H

#include "Shader.h"

class Sprite {
private:
    unsigned int VBO{}, VAO{}, EBO{};
public:
    Shader shader;
    explicit Sprite(const Shader &shader);
    ~Sprite() {
        glDeleteVertexArrays(1, &VAO);
        glDeleteBuffers(1, &VBO);
        glDeleteBuffers(1, &EBO);
        shader.destroy();
    }
    void render();
};


#endif //PLATFORMER_SPRITE_H
