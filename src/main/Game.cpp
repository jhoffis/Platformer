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

    map.create("GrassTiles.png", 24.0f);
    Shader shader("main");

    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glfwSetKeyCallback(window.getWindow(), [](auto window, auto key, auto scancode, auto action, auto mods) {
//        _sceneHandler->keyInput(key, action);
        std::cout << "Key: " << key << std::endl;

        if (action != GLFW_RELEASE) {
            switch (key) {
                case GLFW_KEY_F2:
                    editMode = !editMode;
                    break;
            }
            if (editMode) {
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
        }
    });

    static float mX, mY;
    glfwSetMouseButtonCallback(window.getWindow(), [](auto window, auto button, auto action, auto mods) {
       if (action != GLFW_RELEASE) {

           if (editMode && !map.selectPalette(button, mX, mY)) {
               auto pos = screenCoordToTilePos(mX, mY, camera.pos);
               switch (button) {
                   case GLFW_MOUSE_BUTTON_LEFT:
                       map.placePalette(pos);
                       break;
                   case GLFW_MOUSE_BUTTON_RIGHT:
                       map.removePalette(pos);
                       break;
               }
           }
       }
       /*else {
            topbarTransparent.release();
        }*/

       std::cout << "X: " << mX << "Y: " << mY << std::endl;
    });
    glfwSetCursorPosCallback(window.getWindow(), [](auto window, auto xpos, auto ypos) {
        mX = xpos;
        mY = ypos;
        //topbarTransparent.move(mX, mY);
    });

    // Run the game
    bool running = true;
    while(running)
    {
        if (glfwWindowShouldClose(window.getWindow())) {
            running = false;
            break;
        }
        glfwPollEvents();
        glClear(GL_COLOR_BUFFER_BIT);

        // Render start
        map.render(camera, shader);

        if (editMode && map.selectedSprite >= 0)
            map.palette.at(map.selectedSprite).render(mX, mY, shader);

        // Render end
        glfwSwapBuffers(window.getWindow());
    }

    shader.destroy();
    map.destroy();

    return 0;
}
