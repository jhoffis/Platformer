//#include <Libraries/Nuklear/nuklear.h>
//#include <iostream>
//#include <src/engine/io/Window.h>
#include <src/engine/utils/Timer.h>
//#include <src/scenes/SceneHandler.h>
//#include <vector>
#include "src/Sprite.h"


//void processInput(GLFWwindow *window)
//{
//    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
//        glfwSetWindowShouldClose(window, true);
//}
//struct nk_context ctx;

int main() {
    // Setup
    Window window(false, false);

    //nk_init_fixed(&ctx, calloc(1, MAX_MEMORY), MAX_MEMORY, &font);

    Sprite triangle(Shader("main"), 100, 100, 50, 50);
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);


    glfwSetKeyCallback(window.getWindow(), [](auto window, auto key, auto scancode, auto action, auto mods) {
//        _sceneHandler->keyInput(key, action);
        std::cout << "Key: " << key << std::endl;
    });

    static float x, y;
    glfwSetMouseButtonCallback(window.getWindow(), [](auto window, auto button, auto action, auto mods) {
       /* if (action != GLFW_RELEASE) {
            topbarTransparent.press(x, y);
        } else {
            topbarTransparent.release();
        }*/
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
        triangle.render();

        glfwSwapBuffers(window.getWindow());
    }

    return 0;
}
