#include "Math/Math.h"
#include "Math/Vector2.h"
#include "Core/Random.h"
#include "Core/Time.h"
#include "Audio/AudioSystem.h"
#include "Renderer/Renderer.h"
#include "Input/InputSystem.h"

#include <iostream>
#include <vector>

int main(int argc, char* argv[]) {
    viper::Time time;
    viper::Renderer renderer;

    std::vector<viper::vec2> points;
    renderer.Initialize();
    renderer.CreateWindow("Viper Engine", 1280, 1024);

    viper::AudioSystem audio;
	audio.Initialize();

    viper::InputSystem input;
    input.Initialize();

    // Initialize sounds
    audio.AddSound("bass.wav", "base");
    audio.AddSound("snare.wav", "snare");
    audio.AddSound("clap.wav", "clap");
    audio.AddSound("cowbell.wav", "cowbell");
    audio.AddSound("close-hat.wav", "close-hat");
    audio.AddSound("open-hat.wav", "open-hat");

    std::vector<viper::vec2> stars;
    for (int i = 0; i < 100; i++) {
        stars.push_back(viper::vec2{ viper::random::getRandomFloat() * 1280, viper::random::getRandomFloat() * 1024 });
    }

    SDL_Event e;
    bool quit = false;
   
    while (!quit) {
        time.Tick();
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_EVENT_QUIT) {
                quit = true;
            }
        }

        if (input.GetKeyDown(SDL_SCANCODE_ESCAPE)) {
            quit = true;
		}

        // Update input system
        audio.Update();
        input.Update();

        if (input.GetMouseButtonPressed(viper::InputSystem::MouseButton::Left)) {
            points.push_back(input.GetMousePosition());
        }

        if (input.GetMouseButtonDown(viper::InputSystem::MouseButton::Left)) {
            viper::vec2 position = input.GetMousePosition();
            if (points.empty()) points.push_back(position);
            else if ((position - points.back()).Length() > 10) points.push_back(position);
        }

        if (input.GetKeyDown(SDL_SCANCODE_Q)) audio.PlaySound("base");
        if (input.GetKeyDown(SDL_SCANCODE_W)) audio.PlaySound("snare");
        if (input.GetKeyDown(SDL_SCANCODE_E)) audio.PlaySound("clap");
        if (input.GetKeyDown(SDL_SCANCODE_R)) audio.PlaySound("cowbell");
        if (input.GetKeyDown(SDL_SCANCODE_T)) audio.PlaySound("close-hat");
        if (input.GetKeyDown(SDL_SCANCODE_Y)) audio.PlaySound("open-hat");

        /*
        if (input.GetKeyPressed(SDL_SCANCODE_A)) {
            std::cout << "A key is pressed!" << std::endl;
        }

        viper::vec2 mouse = input.GetMousePosition();
        std::cout << "Mouse Position: (" << mouse.x << ", " << mouse.y << ")" << std::endl;

        if (input.GetMouseButtonPressed()) {
            std::cout << "Left mouse button pressed!" << std::endl;
        }
        */

		// Clear the renderer
        renderer.SetColor(0, 0, 0);
        renderer.Clear();

		// Draw stars
        viper::vec2 speed{ 140.0f, 0.0f };
        float length = speed.Length();

        for (auto& star : stars) {
            star = star * time.GetDeltaTime();

            if (star.x > 1280) star[0] = 0;
            if (star.x > 0) star[0] = 1280;

            renderer.SetColor(255, 255, 255);
            renderer.DrawPoint(star.x, star.y);
        }

        for (int i = 0; i < (int)points.size() - 1; i++) {
            renderer.SetColor(viper::random::getRandomInt(0, 256), viper::random::getRandomInt(0, 256), viper::random::getRandomInt(0, 256));
            renderer.DrawLine(points[i].x, points[i].y, points[i + 1].x, points[i + 1].y);
        }

        for (int i = 0; i < (int)points.size() - 1; i++) {
            renderer.SetColor(viper::random::getRandomInt(0, 256), viper::random::getRandomInt(0, 256), viper::random::getRandomInt(0, 256));
            renderer.DrawLine(points[i].x, points[i].y, points[i + 1].x, points[i + 1].y);
        }

        /*for (int i = 0; i < 10; i++) {
            renderer.SetColor(viper::random::getRandomInt(0, 256), viper::random::getRandomInt(0, 256), viper::random::getRandomInt(0, 256));
            renderer.DrawLine(viper::random::getRandomFloat() * 1280, viper::random::getRandomFloat() * 1024, viper::random::getRandomFloat() * 1280, viper::random::getRandomFloat() * 1024);
        }

        for (int i = 0; i < 20; i++) {
            renderer.SetColor(viper::random::getRandomInt(0, 256), viper::random::getRandomInt(0, 256), viper::random::getRandomInt(0, 256));
            renderer.DrawPoint(viper::random::getRandomFloat() * 1280, viper::random::getRandomFloat() * 1280);
        }

        renderer.SetColor(viper::random::getRandomInt(0, 256), viper::random::getRandomInt(0, 256), viper::random::getRandomInt(0, 256));
        renderer.DrawPoint(v.x, v.y);*/

        renderer.Present();
    }
    renderer.Shutdown();
	audio.Shutdown();

    return 0;
}