//
// Created by jh on 3/8/2021.
//

#include "Map.h"
#include <iostream>
#include <fstream>

const char *mapFilename = "map.txt";

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
        bool neg = false;
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
                tileArr[i] = (neg ? -1 : +1) * num;

                i++;
                n = 0;
                neg = false;
            } else if (c == '-') {
                neg = true;
            } else {
                digits[n] = c - '0';
                n++;
            }
        }
        Tile tile{};
        tile.x = tileArr[0];
        tile.y = tileArr[1];
        tile.pointerToSprite = tileArr[2];

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
    int n = 0;
    for (int i = 0; i < palette.size(); i += 16) {

        auto tile = palette.at(i);
        if (tile.isAbove(n % (int) width, n / (int) width, palettePos, mX, mY)) {
            if (button == GLFW_MOUSE_BUTTON_LEFT)
                selectedSprite = i;
            else
                selectedSprite = -1;
            std::cout << "Selected tile: " << i << std::endl;
            return true;
        }
        n++;
    }
    return false;
}

void Map::placePalette(glm::vec3 &newTilePos) {
    if (selectedSprite < 0 || getTileAt(newTilePos.x, newTilePos.y))
        return;

    Tile tile{};
    tile.x = newTilePos.x; // FIXME HM, her kan det bli overlapping av tiles.
    tile.y = newTilePos.y;
    if (selectedSprite == 0) {
        tile.pointerToSprite = getTileIndex(0, tile.x, tile.y);
    }
    else if (selectedSprite == 16) {
        tile.pointerToSprite = getTileIndex(1, tile.x, tile.y);
    }
    else {
        tile.pointerToSprite = selectedSprite;
    }
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

int Map::getTileIndex(int pal, int x, int y) {
    int tileIndex = 0;
    Tile *adjacentTile;
    adjacentTile = getTileAt(x, y-1);
    if (adjacentTile) {
        tileIndex += 1;
        adjacentTile->pointerToSprite += 8;
    }
    adjacentTile = getTileAt(x+1, y);
    if (adjacentTile) {
        tileIndex += 2;
        adjacentTile->pointerToSprite += 4;
    }
    adjacentTile = getTileAt(x-1, y);
    if (adjacentTile) {
        tileIndex += 4;
        adjacentTile->pointerToSprite += 2;
    }
    adjacentTile = getTileAt(x, y+1);
    if (adjacentTile) {
        tileIndex += 8;
        adjacentTile->pointerToSprite += 1;
    }
    tileIndex += pal * 16;
    return tileIndex;
}

void Map::render(Camera &camera, Shader &shader) {
    if (editMode) {
        int n = 0;
        for (int i = 0; i < palette.size(); i += 16) {
            palette.at(i).render(n % (int) width, n / (int) width, palettePos, shader, false);
            n++;
        }
    }
    for (auto tile : mapOfTiles) {
        palette.at(tile.pointerToSprite).render(tile.x, tile.y, camera.pos, shader, false);
    }
}

Tile *Map::shouldStopAtTileNearX(float velocityX, float x, float y) {
    int direction = (velocityX < 0 ? -1 : 1);

    Tile *tile = nullptr;
    int i = 0;
    do {
        auto tileTemp = getTileAt((int) x + (direction * i), (int) y);
        if (tileTemp && tileTemp->pointerToSprite < 32) {
            tile = tileTemp;
            break;
        }
        i++;
    } while (i <= abs((int) velocityX) + (velocityX > 0));

    return tile;
}

Tile *Map::shouldStopAtTileNearY(float velocityY, float x, float y) {
    int direction = (velocityY < 0 ? -1 : 1);
    Tile *tile = nullptr;
    int i = 1;
    do {
        auto tileTemp1 = getTileAt((int) x, (int) y + (direction * i));
        auto tileTemp2 = getTileAt((int) x + 1, (int) y + (direction * i));

        if (tileTemp1 && tileTemp1->pointerToSprite < 32) {

            if (tileTemp2) {
                tile = tileTemp1;
                break;
            }
            // hvis du faller sjekk om det finnes en ovenfor og fortsett om det er sant. Om du hopper, sjekk om det finnes en under. TODO kanskje tillate walljump om sant?
            float dist = abs(x - (float) tileTemp1->x);
            auto checkTile = getTileAt(tileTemp1->x, tileTemp1->y - (direction));
            if (!checkTile && dist < 0.9f) {
                tile = tileTemp1;
                break;
            }
        }
        if (tileTemp2 && tileTemp2->pointerToSprite < 32) {
            float dist = abs(x - (float) tileTemp2->x);
            auto checkTile = getTileAt(tileTemp2->x, tileTemp2->y - (direction));
            if (!checkTile && dist < 0.9f) {
                tile = tileTemp2;
                break;
            }
        }
        i++;
    } while (i <= abs((int) velocityY) + 1);

    return tile;
}

Tile* Map::getTileAt(int x, int y) {
    for (auto & mapOfTile : mapOfTiles)
        if (mapOfTile.x == x && mapOfTile.y == y)
            return &mapOfTile;
    return nullptr;
}
