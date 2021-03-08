//
// Created by Jens Benz on 06.03.2021.
//

#ifndef PLATFORMER_SPRITE_H
#define PLATFORMER_SPRITE_H

#include "src/engine/io/Window.h"
#include "src/Camera.h"

static const float tileSize = 0.1f;
inline float realTileWidth{}, realTileHeight{};

void spriteUpdateTileSize();

class Sprite {
private:
    unsigned int VBO{}, VAO{}, EBO{}, texture{};
    glm::vec3 modelPos{};

public:
    Sprite(int tilemapX, int tilemapY, float texW, float texH, int tileX, int tileY, auto texture) {
        setPos(tileX, tileY);
        this->texture = texture;

        const auto realX = -1.0f;
        const auto realY = -1.0f;

        const float vertices[] = {
                realX + realTileWidth / 2.0f, realY + realTileHeight / 2.0f,  0.0f, 1.0f, 0.0f, 0.0f,   (tilemapX + 1) * texW,    1.0f - tilemapY * texH,          // oppe til høyre
                realX + realTileWidth / 2.0f, realY - realTileHeight / 2.0f, 0.0f,  0.0f, 1.0f, 0.0f,   (tilemapX + 1) * texW,    1.0f - (tilemapY + 1) * texH,      // nede til høyre
                realX - realTileWidth / 2.0f, realY - realTileHeight / 2.0f, 0.0f,  0.0f, 0.0f, 1.0f,   tilemapX * texW,    1.0f - (tilemapY + 1) * texH,      // nede til venstre
                realX - realTileWidth / 2.0f, realY + realTileHeight / 2.0f, 0.0f,   0.5f, 0.5f, 1.0f,  tilemapX * texW,    1.0f - tilemapY * texH,          // oppe til venstre
        };

        unsigned int indices[] = {  // note that we start from 0!
                0, 1, 3,   // first triangle
                1, 2, 3    // second triangle
        };

        glGenVertexArrays(1, &VAO);
        glGenBuffers(1, &VBO);
        glGenBuffers(1, &EBO);
        // bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
        glBindVertexArray(VAO);

        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

        // position attribute
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *) 0);
        glEnableVertexAttribArray(0);
        // color attribute
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *) (3 * sizeof(float)));
        glEnableVertexAttribArray(1);

        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *) (6 * sizeof(float)));
        glEnableVertexAttribArray(2);

        // note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
        glBindBuffer(GL_ARRAY_BUFFER, 0);

        // You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
        // VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
        glBindVertexArray(0);

    }

    void destroy() {
        glDeleteVertexArrays(1, &VAO);
        glDeleteBuffers(1, &VBO);
        glDeleteBuffers(1, &EBO);
    }

    void render(const Camera &camera, Shader &shader);

    void setPos(int tileX, int tileY) {
        // trenger ikke å bruke annet enn window aspect for å bestemme variasjon. Bruk så opengl størrelse for å si størresle på en tile.
        modelPos.x = (float) tileX * realTileWidth;
        modelPos.y = (float) tileY * realTileHeight;
    }

};


#endif //PLATFORMER_SPRITE_H
