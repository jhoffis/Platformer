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
//        map.mapOfTiles.push_back(i);
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

bool Map::selectPalette(int button, int mX, int mY) {
    for (int i = 0; i < palette.size(); i++) {
        auto tile = palette.at(i);
        if (tile.isAbove(i % (int) width, i / (int) width, palettePos, mX, mY)) {
            if (button == GLFW_MOUSE_BUTTON_LEFT)
                selectedSprite = i;
            else
                selectedSprite = -1;
            std::cout << "Selected tile: " << i << std::endl;
            return true;
        }
    }
    return false;
}

void Map::placePalette(glm::vec3 &newTilePos) {
    if (selectedSprite < 0)
        return;
    Tile tile{};
    tile.x = newTilePos.x; // FIXME HM, her kan det bli overlapping av tiles.
    tile.y = newTilePos.y;
    tile.pointerToSprite = selectedSprite;
    mapOfTiles.push_back(tile);
}

void Map::removePalette(glm::vec3 &newTilePos) {
    for (int i = 0; i < mapOfTiles.size(); i++) {
        auto tile = mapOfTiles.at(i);
        if (tile.x == newTilePos.x && tile.y == newTilePos.y) {
            mapOfTiles.erase(mapOfTiles.begin() + i);
        }
    }
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
        for (auto tile : mapOfTiles) {
            palette.at(tile.pointerToSprite).render(tile.x, tile.y, camera.pos, shader);
        }
}
