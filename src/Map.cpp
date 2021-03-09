//
// Created by jh on 3/8/2021.
//

#include "Map.h"
#include <iostream>
#include <fstream>

const char *mapFilename = "map.txt";

enum CollideType {
    none, top, topLeft, topRight, sideLeft, sideRight, bot, botLeft, botRight
};

int genCollideType(int pointer) {
    switch (pointer) {
        case 0:
            return topLeft;
        case 1:
            break;
        case 2:
            break;
        case 3:
            break;
        case 4:
            break;
        case 5:
            break;
        case 6:
            break;
        case 7:
            break;
        case 8:
            break;
        case 9:
            break;
    }
}

void Map::load() {

    std::string tileTextLine;

// Read from the text file
    std::ifstream mapFile(mapFilename);

// Use a while loop together with the getline() function to read the file line by line
    while (getline (mapFile, tileTextLine)) {
        int tileArr[3];
        int i = 0;
        int n = 0;
        int digits[4];
        for (auto c : tileTextLine) {
            if (c == 'x' || c == ';') {
                if (i >= sizeof(tileArr))
                    break;

                int num = 0;
                int place = n - 1;
                for (int a = 0; a < n; a++) {
                    int digit = 10 * place;
                    num += (digit != 0 ? digit : 1) * digits[a];
                    place--;
                }
                tileArr[i] = num;

                i++;
                n = 0;
            } else {
                digits[n] = c - '0';
                n++;
            }
        }
        Tile tile{};
        tile.x = tileArr[0];
        tile.y = tileArr[1];
        tile.pointerToSprite = tileArr[2];
        tile.collideType = genCollideType(tileArr[2]);

        mapOfTiles.push_back(tile);
    }

// Close the file
    mapFile.close();
}

void Map::save() {
    std::ofstream mapFile;
    mapFile.open(mapFilename, std::ofstream::out | std::ofstream::trunc);

    for (auto tile : mapOfTiles) {
        mapFile << tile.x << 'x' << tile.y << 'x' << tile.pointerToSprite << ';' << std::endl;
    }

    mapFile.close();
}

void Map::create(const char *imgPath, float tilemapPixelSize) {
    auto img = createCharImage(imgPath, true);
    auto w = static_cast<unsigned>((float) img.w / tilemapPixelSize);
    auto h = static_cast<unsigned>((float) img.h / tilemapPixelSize);

    float texW = tilemapPixelSize / (float) img.w;
    float texH = tilemapPixelSize / (float) img.h;

    unsigned int texture = createTexture(img);

    for (int i = 0; i < w * h; i++) {
        int x = i % w;
        int y = i / w;
        palette.emplace_back(x, y, texW, texH, texture);
    }

    width = w;
    height = h;

    palettePos = glm::vec3(Sprite::realTileWidth / 2.0f, Sprite::realTileHeight / 2.0f, 0);

    load();
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
        if (editMode) {
            int i = 0;
            for (Sprite tile : palette) {
                tile.render(i % (int) width, i / (int) width, palettePos, shader);
                i++;
            }
        }
        for (auto tile : mapOfTiles) {
            palette.at(tile.pointerToSprite).render(tile.x, tile.y, camera.pos, shader);
        }
}
