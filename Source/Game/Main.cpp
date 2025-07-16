#include "Math/Math.h"
#include "Math/Vector2.h"
#include "Math/Vector3.h"
#include "Core/Random.h"
#include "Core/Time.h"
#include "Audio/AudioSystem.h"
#include "Renderer/Renderer.h"
#include "Renderer/Model.h"
#include "Input/InputSystem.h"

#include <iostream>
#include <vector>

int main(int argc, char* argv[]) {
    
	// Intialize engine systems
    viper::Time time;

    viper::Renderer renderer;
    renderer.Initialize();
    renderer.CreateWindow("Viper Engine", 1280, 1024);

    viper::InputSystem input;
    input.Initialize();
    
	// Initialize audio system
    viper::AudioSystem audio;
	audio.Initialize();

    std::vector<viper::vec2> points{
        { -5, -5 },
        {  5, -5 },
        {  5,  5 },
        { -5,  5 },
        { -5, -5 },
    };

    viper::Model model{ points, { 0, 0, 1} };

    // Initialize sounds
    audio.AddSound("bass.wav", "base");
    audio.AddSound("snare.wav", "snare");
    audio.AddSound("clap.wav", "clap");
    audio.AddSound("cowbell.wav", "cowbell");
    audio.AddSound("close-hat.wav", "close-hat");
    audio.AddSound("open-hat.wav", "open-hat");

	// Create stars
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

        if (input.GetKeyPressed(SDL_SCANCODE_ESCAPE)) { quit = true; }

        if (input.GetMouseButtonPressed(viper::InputSystem::MouseButton::Left)) {
            points.push_back(input.GetMousePosition());
        }

        if (input.GetMouseButtonDown(viper::InputSystem::MouseButton::Left)) {
            viper::vec2 position = input.GetMousePosition();
            if (points.empty()) points.push_back(position);
            else if ((position - points.back()).Length() > 10) points.push_back(position);
        }

        // Update input system
        audio.Update();
        input.Update();

        // Play drum sounds
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
		viper::vec3 color{ 0, 0, 0};

        renderer.SetColor(color.r, color.g, color.b);
        renderer.Clear();

        model.Draw(renderer, input.GetMousePosition(), time.GetTime(), 10.0f);

		// Draw stars
        viper::vec2 speed{ -140.0f, 0.0f };
        float length = speed.Length();

        for (auto& star : stars) {
            star += speed * time.GetDeltaTime();

            if (star[0] > 1280) star[0] = 0;
            if (star[0] < 0) star[0] = 1280;

            renderer.SetColor((uint8_t)viper::random::getRandomInt(256), viper::random::getRandomInt(256), viper::random::getRandomInt(256));
            renderer.DrawPoint(star.x, star.y);
        }
        /*
        for (int i = 0; i < (int)points.size() - 1; i++) {
            renderer.SetColor(viper::random::getRandomInt(0, 256), viper::random::getRandomInt(0, 256), viper::random::getRandomInt(0, 256));
            renderer.DrawLine(points[i].x, points[i].y, points[i + 1].x, points[i + 1].y);
        }

        for (int i = 0; i < (int)points.size() - 1; i++) {
            renderer.SetColor(viper::random::getRandomInt(0, 256), viper::random::getRandomInt(0, 256), viper::random::getRandomInt(0, 256));
            renderer.DrawLine(points[i].x, points[i].y, points[i + 1].x, points[i + 1].y);
        }

        
        for (int i = 0; i < 10; i++) {
            renderer.SetColor(viper::random::getRandomInt(0, 256), viper::random::getRandomInt(0, 256), viper::random::getRandomInt(0, 256));
            renderer.DrawLine(viper::random::getRandomFloat() * 1280, viper::random::getRandomFloat() * 1024, viper::random::getRandomFloat() * 1280, viper::random::getRandomFloat() * 1024);
        }

        for (int i = 0; i < 20; i++) {
            renderer.SetColor(viper::random::getRandomInt(0, 256), viper::random::getRandomInt(0, 256), viper::random::getRandomInt(0, 256));
            renderer.DrawPoint(viper::random::getRandomFloat() * 1280, viper::random::getRandomFloat() * 1280);
        }

        renderer.SetColor(viper::random::getRandomInt(0, 256), viper::random::getRandomInt(0, 256), viper::random::getRandomInt(0, 256));
        renderer.DrawPoint(v.x, v.y);
        */

        renderer.Present();
    }
    renderer.Shutdown();
	audio.Shutdown();

    return 0;
}