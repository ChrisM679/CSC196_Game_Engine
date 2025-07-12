#include "Math/Math.h"
#include "Math/Vector2.h"
#include "Core/Random.h"
#include "Core/Time.h"
#include <SDL3/SDL.h>
#include <iostream>
#include <Renderer/Renderer.h>
#include <vector>
#include <Input/InputSystem.h>
#include <fmod.hpp>

int main(int argc, char* argv[]) {
    viper::Time time;
    viper::Renderer renderer;

    std::vector<viper::vec2> points;
    renderer.Initialize();
    renderer.CreateWindow("Viper Engine", 1280, 1024);

    // create audio system
    FMOD::System* audio;
    FMOD::System_Create(&audio);

    void* extradriverdata = nullptr;
    audio->init(32, FMOD_INIT_NORMAL, extradriverdata);

    viper::InputSystem input;
    input.Initialize();

    SDL_Event e;
    bool quit = false;

    std::vector<viper::vec2> stars;
    for (int i = 0; i < 100; i++) {
        stars.push_back(viper::vec2{ viper::random::getRandomFloat() * 1280, viper::random::getRandomFloat() * 1024 });
    }
    
    FMOD::Sound* sound = nullptr;
    audio->createSound("test.wav", FMOD_DEFAULT, 0, &sound);

    std::vector<FMOD::Sound*> sounds;
    audio->createSound("bass.wav", FMOD_DEFAULT, 0, &sound);
    sounds.push_back(sound);

    audio->createSound("snare.wav", FMOD_DEFAULT, 0, &sound);
    sounds.push_back(sound);

    audio->createSound("clap.wav", FMOD_DEFAULT, 0, &sound);
    sounds.push_back(sound);

    audio->createSound("cowbell.wav", FMOD_DEFAULT, 0, &sound);
    sounds.push_back(sound);

    audio->createSound("close-hat.wav", FMOD_DEFAULT, 0, &sound);
    sounds.push_back(sound);

    audio->createSound("open-hat.wav", FMOD_DEFAULT, 0, &sound);
    sounds.push_back(sound);

    audio->playSound(sound, 0, false, nullptr);

    while (!quit) {
        time.Tick();
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_EVENT_QUIT) {
                quit = true;
            }
        }

        if (input.GetKeyDown(SDL_SCANCODE_Q) && !input.GetPrevKeyDown(SDL_SCANCODE_Q))
    {
        // play bass sound, vector elements can be accessed like an array with [#]
            if (!sounds.empty()) {
            audio->playSound(sounds[0], nullptr, false, nullptr);
			}
    }
        if (input.GetKeyDown(SDL_SCANCODE_W) && !input.GetPrevKeyDown(SDL_SCANCODE_W))
        {
        // play snare sound, vector elements can be accessed like an array with [#]
            if (sounds.size() > 1) {
                audio->playSound(sounds[1], nullptr, false, nullptr);
            }
        }
        if (input.GetKeyDown(SDL_SCANCODE_E) && !input.GetPrevKeyDown(SDL_SCANCODE_E))
		{
        // play clap sound, vector elements can be accessed like an array with [#]
            if (sounds.size() > 2) {
                audio->playSound(sounds[2], nullptr, false, nullptr);
            }
		}

		if (input.GetKeyDown(SDL_SCANCODE_R) && !input.GetPrevKeyDown(SDL_SCANCODE_R))
		{
         // play cowbell sound, vector elements can be accessed like an array with [#]
            if (sounds.size() > 3) {
                audio->playSound(sounds[3], nullptr, false, nullptr);
			}
		}
		if (input.GetKeyDown(SDL_SCANCODE_T) && !input.GetPrevKeyDown(SDL_SCANCODE_T))
            {
         // play close-hat sound, vector elements can be accessed like an array with [#]
            if (sounds.size() > 4) {
				audio->playSound(sounds[4], nullptr, false, nullptr);
                }
		}
		if (input.GetKeyDown(SDL_SCANCODE_Y) && !input.GetPrevKeyDown(SDL_SCANCODE_Y))
            {
         // play open-hat sound, vector elements can be accessed like an array with [#]
			if (sounds.size() > 5) {
				audio->playSound(sounds[5], nullptr, false, nullptr);
			}
		}

        if (input.GetKeyDown(SDL_SCANCODE_ESCAPE)) {
			quit = true;
    }
        audio->update();

		// Update input system
        input.Update();

        if (input.GetMouseButtonPressed(viper::InputSystem::MouseButton::Left)) {
            points.push_back(input.GetMousePosition());
        }

        if (input.GetMouseButtonDown(viper::InputSystem::MouseButton::Left)) {
            viper::vec2 position = input.GetMousePosition();
            if (points.empty()) points.push_back(position);
            else if ((position - points.back()).Length() > 10) points.push_back(position);
        }

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

    return 0;
}