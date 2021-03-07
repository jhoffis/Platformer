//
// Created by Jens Benz on 06.03.2021.
//

#include "Sprite.h"

Sprite::Sprite(const Shader &shader) : shader(shader) {
    // set up vertex data (and buffer(s)) and configure vertex attributes
    // ------------------------------------------------------------------

    auto img = createCharImage("GrassTiles.png", true);

    auto ww = Window::WIDTH;
    auto wh = Window::HEIGHT;

    auto aspect = ww / wh;

    float w = 24.0f / img.w;
    float h = 24.0f / img.h;

    float actualWidth = 1.0f / aspect;
    float actualHeight = 1.0f;

    float vertices[] = {
            actualWidth / 2.0f,   actualHeight / 2.0f,  0.0f, 1.0f, 0.0f, 0.0f,    w,    1.0f,          // oppe til høyre
            actualWidth / 2.0f,  -actualHeight / 2.0f, 0.0f,  0.0f, 1.0f, 0.0f,   w,    1.0f - h,      // nede til høyre
            -actualWidth / 2.0f, -actualHeight / 2.0f, 0.0f,  0.0f, 0.0f, 1.0f,   0.0f, 1.0f - h,      // nede til venstre
            -actualWidth / 2.0f,  actualHeight / 2.0f, 0.0f,   0.5f, 0.5f, 1.0f,  0.0f, 1.0f,          // oppe til venstre
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


    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
// set the texture wrapping/filtering options (on the currently bound texture object)
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
// load and generate the texture
    createGLImage(img);

    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    // color attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    glEnableVertexAttribArray(2);

    // note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    // You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
    // VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
    glBindVertexArray(0);

}

void Sprite::render() {
    shader.use();
    glBindTexture(GL_TEXTURE_2D, texture);
    glBindVertexArray(VAO); // seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    // glBindVertexArray(0); // no need to unbind it every time
}