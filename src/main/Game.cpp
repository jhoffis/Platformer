#include <src/engine/utils/Timer.h>
#include "src/Player.h"


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
    static Camera::Cam camera{};
    //nk_init_fixed(&ctx, calloc(1, MAX_MEMORY), MAX_MEMORY, &font);

    map.create("GrassTiles.png", 24.0f);
    player.create("Character.png", 24.0f);
    player.x = 6;
    player.y = 3;
    Shader shader("main");

    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glfwSetKeyCallback(window.getWindow(), [](auto window, auto key, auto scancode, auto action, auto mods) {
        std::cout << "Key: " << key << std::endl;

        if (action != GLFW_RELEASE) {
            /*
             * GLOBAL KEYS
             */
            switch (key) {
                case GLFW_KEY_F2:
                    editMode = !editMode;
                    break;
                case GLFW_KEY_F3:
                    map.save();
                    break;
            }
        }

        if (editMode) {
            /*
             * EDIT KEYS
             */
            switch (key) {
                case GLFW_KEY_UP:
                    camera.position.y += 0.1;
                    break;
                case GLFW_KEY_DOWN:
                    camera.position.y -= 0.1;
                    break;
                case GLFW_KEY_LEFT:
                    camera.position.x += 0.1;
                    break;
                case GLFW_KEY_RIGHT:
                    camera.position.x -= 0.1;
                    break;
            }
        } else {
            /*
             * PLAY KEYS
             */
            switch (key) {
                case GLFW_KEY_A:
                    player.setLeft(action != GLFW_RELEASE);
                    break;
                case GLFW_KEY_D:
                    player.setRight(action != GLFW_RELEASE);
                    break;
                case GLFW_KEY_LEFT_SHIFT:
                    player.run = action != GLFW_RELEASE;
                    break;
                case GLFW_KEY_SPACE:
                    if (action != GLFW_RELEASE) {
                        if (!player.jumping && player.velocityY == 0) {
                            player.jump();
                        }
                    } else if (player.velocityY > 0){
                        player.velocityY = 0;
                    }
                    if (action == GLFW_RELEASE) {
                        player.jumping = false;
                    }
                    break;
            }

        }
    });

    static float mX, mY;
    glfwSetMouseButtonCallback(window.getWindow(), [](auto window, auto button, auto action, auto mods) {
       if (action != GLFW_RELEASE) {

           if (editMode && !map.selectPalette(button, mX, mY)) {
               auto pos = screenCoordToTilePos(mX, mY, camera.position);
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
    Timer::nowDelta();
    bool running = true;
    while(running)
    {
        if (glfwWindowShouldClose(window.getWindow())) {
            running = false;
            break;
        }
        glfwPollEvents();
        glClear(GL_COLOR_BUFFER_BIT);

        double delta = Timer::nowDelta();
        player.tick(delta);

        // Render start
        map.render(camera, shader);

        if (editMode) {
            if (map.selectedSprite >= 0)
                map.palette.at(map.selectedSprite).render(mX, mY, shader, false);
        } else {
            auto playerPos = realTilePos(player.x, player.y);
            camera.position.x = 1.0 - playerPos.x - Sprite::realTileWidth / 2.0;
            camera.position.y = 1.0 - playerPos.y - Sprite::realTileHeight / 2.0;
        }

        player.render(camera, shader);

        // Render end
        glfwSwapBuffers(window.getWindow());

        std::this_thread::sleep_for(std::chrono::milliseconds(10));
    }

    shader.destroy();
    map.destroy();

    return 0;
}
