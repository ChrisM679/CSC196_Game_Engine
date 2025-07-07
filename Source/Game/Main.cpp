#include "Math/Math.h"
#include "Math/Vector2.h" // Ensure this header is included for Vector2 definition
#include "Core/Random.h"
#include <SDL3/SDL.h>
#include <iostream>
#include <Renderer/Renderer.h>

int main(int argc, char* argv[]) {
    viper::Renderer renderer;

    renderer.Initialize();
    renderer.CreateWindow("Viper Engine", 1280, 1024);

    SDL_Event e;
    bool quit = false;

    Vector2<float> v(30, 40); // Specify the template type for Vector2

    while (!quit) {
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_EVENT_QUIT) {
                quit = true;
            }
        }

        renderer.SetColor(0, 0, 0);
        renderer.Clear();

        for (int i = 0; i < 10; i++) {
            renderer.SetColor(viper::random::getRandomInt(0, 256), viper::random::getRandomInt(0, 256), viper::random::getRandomInt(0, 256));
            renderer.DrawLine(viper::random::getRandomFloat() * 1280, viper::random::getRandomFloat() * 1280, viper::random::getRandomFloat() * 1280, viper::random::getRandomFloat() * 1280);
        }

        for (int i = 0; i < 20; i++) {
            renderer.SetColor(viper::random::getRandomInt(0, 256), viper::random::getRandomInt(0, 256), viper::random::getRandomInt(0, 256));
            renderer.DrawPoint(viper::random::getRandomFloat() * 1280, viper::random::getRandomFloat() * 1280);
        }

        renderer.SetColor(viper::random::getRandomInt(0, 256), viper::random::getRandomInt(0, 256), viper::random::getRandomInt(0, 256));
        renderer.DrawPoint(v.x, v.y);

        renderer.Present();
    }

    renderer.Shutdown();

    return 0;
}