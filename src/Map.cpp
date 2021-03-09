//
// Created by jh on 3/8/2021.
//

#include "Map.h"

void Map::create(const char *imgPath, float tilemapPixelSize) {
    auto img = createCharImage(imgPath, true);
    auto w = static_cast<unsigned>((float) img.w / tilemapPixelSize);
    auto h = static_cast<unsigned>((float) img.h / tilemapPixelSize);

    float texW = tilemapPixelSize / (float) img.w;
    float texH = tilemapPixelSize / (float) img.h;

    unsigned int texture{};
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    // set the texture wrapping/filtering options (on the currently bound texture object)
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    // load and generate the texture
    createGLImage(img);
    glBindTexture(GL_TEXTURE_2D, 0);

    for (int i = 0; i < w * h; i++) {
        int x = i % w;
        int y = i / w;
        palette.emplace_back(x, y, texW, texH, texture);
//        map.mapPointToTileIndices.push_back(i);
    }

    width = w;
    height = h;

    palettePos = glm::vec3(Sprite::realTileWidth / 2.0f, Sprite::realTileHeight / 2.0f, 0);
}

void Map::destroy() {
    for (auto sprite : palette) {
        sprite.destroy();
    }
}

void Map::selectPalette(int button, int mX, int mY, glm::vec3 &viewPos) {
    if (selectedSprite >= 0 && button == GLFW_MOUSE_BUTTON_LEFT) {
        Tile tile{};
        auto pos = screenCoordToTilePos(mX, mY, viewPos);
        std::cout << "Place X: " << pos.x << " Place Y: " << pos.y << std::endl;
        tile.x = pos.x; // FIXME HM, her kan det bli overlapping av tiles.
        tile.y = pos.y;
        tile.pointerToSprite = selectedSprite;
        mapPointToTileIndices.push_back(tile);
    }

    for (int i = 0; i < palette.size(); i++) {
        auto tile = palette.at(i);
        if (tile.isAbove(i % (int) width, i / (int) width, palettePos, mX, mY)) {
            selectedSprite = i;
            std::cout << "Selected tile: " << i << std::endl;
            return;
        }
    }
    selectedSprite = -1;
}

void Map::render(Camera &camera, Shader &shader) {
        int i = 0;
        for (Sprite tile : palette) {
//            if (width == 0) {
//                std::cout << "Can't divide by zero!\n" << "Error number: " << width << std::endl;
//                break;
//            }
            tile.render(i % (int) width, i / (int) width, palettePos, shader);
            i++;
        }
        for (auto tile : mapPointToTileIndices) {
            palette.at(tile.pointerToSprite).render(tile.x, tile.y, camera.pos, shader);
        }
}
