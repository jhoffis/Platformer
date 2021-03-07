//
// Created by Jens Benz on 07.03.2021.
//

#ifndef PLATFORMER_RESOURCELOADER_H
#define PLATFORMER_RESOURCELOADER_H

#include <stdexcept>
#include "src/Shader.h"

struct CharImage {
    int w;
    int h;
    int comp;
    unsigned char *image;
};

CharImage createCharImage(const char *path);
void createGLImage(const char *path);
#endif //PLATFORMER_RESOURCELOADER_H
