#include <src/engine/utils/Timer.h>
#include "src/Map.h"


//void processInput(GLFWwindow *window)
//{
//    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
//        glfwSetWindowShouldClose(window, true);
//}
//struct nk_context ctx;

int main() {
    // Setup
    Window window(false, false);
    spriteUpdateTileSize();
    static Camera camera;
    //nk_init_fixed(&ctx, calloc(1, MAX_MEMORY), MAX_MEMORY, &font);

    mapCreate("GrassTiles.png", 24.0f);
    Shader shader("main");

    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);


    glfwSetKeyCallback(window.getWindow(), [](auto window, auto key, auto scancode, auto action, auto mods) {
//        _sceneHandler->keyInput(key, action);
        std::cout << "Key: " << key << std::endl;

        if (action != GLFW_RELEASE) {
            switch (key) {
                case GLFW_KEY_UP:
                    camera.pos.y += 0.1;
                    break;
                case GLFW_KEY_DOWN:
                    camera.pos.y -= 0.1;
                    break;
                case GLFW_KEY_LEFT:
                    camera.pos.x += 0.1;
                    break;
                case GLFW_KEY_RIGHT:
                    camera.pos.x -= 0.1;
                    break;
            }
        }
    });

    static float x, y;
    glfwSetMouseButtonCallback(window.getWindow(), [](auto window, auto button, auto action, auto mods) {
       if (action != GLFW_RELEASE) {
           map.selectPalette(button, x, y);
       }
       /*else {
            topbarTransparent.release();
        }*/

       std::cout << "X: " << x << "Y: " << y << std::endl;
    });
    glfwSetCursorPosCallback(window.getWindow(), [](auto window, auto xpos, auto ypos) {
        x = xpos;
        y = ypos;
        //topbarTransparent.move(x, y);
    });

    // Run the game
    bool running = true;
    while(running)
    {
        if (glfwWindowShouldClose(window.getWindow())) {
            running = false;
            break;
        }
//        steam.update();
        //sceneHandler.tick(Timer::nowDelta());
//        audio.checkMusic();

//        processInput(window.getWindow());

        glfwPollEvents();

        glClear(GL_COLOR_BUFFER_BIT);

//        triangle.shader.
        for (auto tile : map.palette) {
            tile.render(map.palettePos, shader, true);
        }
        for (auto tile : map.mapPointToTileIndices) {
            map.palette.at(tile).render(camera.pos, shader, true);
        }
        if (map.selectedSprite >= 0)
            map.palette.at(map.selectedSprite).render(
                    glm::vec3(
                            x / Window::WIDTH * 2.0f - Sprite::realTileWidth / 2.0f,
                            y / Window::HEIGHT * 2.0f - Sprite::realTileHeight / 2.0f, 0),
                            shader, false);
//        triangle.render(camera);
//        triangle2.render(camera);
//        triangle3.render(camera);
//        triangle4.render(camera);

        glfwSwapBuffers(window.getWindow());
    }

    shader.destroy();
    map.destroy();

    return 0;
}
