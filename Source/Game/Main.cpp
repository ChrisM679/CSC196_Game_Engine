#include "Math/Math.h"
#include "Math/Vector2.h"
#include "Math/Vector3.h"
#include "Math/Transform.h"
#include "Core/Random.h"
#include "Core/Time.h"
#include "Framework/Actor.h"
#include "Audio/AudioSystem.h"
#include "Renderer/Renderer.h"
#include "Renderer/Model.h"
#include "Input/InputSystem.h"
#include "Framework/Scene.h"
#include "Engine.h"
#include "Renderer/Font.h"
#include "Renderer/Text.h"

#include "Game/Player.h"
#include "Game/SpaceGame.h"

#include <iostream>
#include <vector>
#include <memory>

int main(int argc, char* argv[]) {

    viper::Font* font = new viper::Font();
    font->Load("arcadeclassic.ttf", 20);
    
	// Intialize engine
    viper::GetEngine().Initialize();

	//Initialize game
	std::unique_ptr<SpaceGame> game = std::make_unique<SpaceGame>();
	game->Initialize();

    // Initialize sounds
    viper::GetEngine().GetAudio().AddSound("bass.wav", "base");
    viper::GetEngine().GetAudio().AddSound("snare.wav", "snare");
    viper::GetEngine().GetAudio().AddSound("clap.wav", "clap");
    viper::GetEngine().GetAudio().AddSound("cowbell.wav", "cowbell");
    viper::GetEngine().GetAudio().AddSound("close-hat.wav", "close-hat");
    viper::GetEngine().GetAudio().AddSound("open-hat.wav", "open-hat");

    SDL_Event e;
    bool quit = false;
   
    while (!quit) {
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_EVENT_QUIT) {
                quit = true;
            }
        }

        if (viper::GetEngine().GetInput().GetKeyPressed(SDL_SCANCODE_ESCAPE)) { quit = true; }

        viper::Text* text = new viper::Text(font);
        text->Create(viper::GetEngine().GetRenderer(), "Hello World", viper::vec3{ 1, 1, 1 });

        /*
        if (viper::GetEngine().GetInput().GetMouseButtonPressed(viper::InputSystem::MouseButton::Left)) {
            points.push_back(viper::GetEngine().GetInput().GetMousePosition());
        }

        if (viper::GetEngine().GetInput().GetMouseButtonDown(viper::InputSystem::MouseButton::Left)) {
            viper::vec2 position = viper::GetEngine().GetInput().GetMousePosition();
            if (points.empty()) points.push_back(position);
            else if ((position - points.back()).Length() > 10) points.push_back(position);
        }
        */

        // Update input system
		viper::GetEngine().Update();
        game->Update();

        /*
        // Play drum sounds
        if (input.GetKeyDown(SDL_SCANCODE_Q)) audio.PlaySound("base");
        if (input.GetKeyDown(SDL_SCANCODE_W)) audio.PlaySound("snare");
        if (input.GetKeyDown(SDL_SCANCODE_E)) audio.PlaySound("clap");
        if (input.GetKeyDown(SDL_SCANCODE_R)) audio.PlaySound("cowbell");
        if (input.GetKeyDown(SDL_SCANCODE_T)) audio.PlaySound("close-hat");
        if (input.GetKeyDown(SDL_SCANCODE_Y)) audio.PlaySound("open-hat");
        */

		//if (input.GetKeyDown(SDL_SCANCODE_A)) transform.rotation -= viper::math::degToRad(90) * time.GetDeltaTime());
        //if (input.GetKeyDown(SDL_SCANCODE_D)) transform.rotation += viper::math::degToRad(90 * time.GetDeltaTime());

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

        viper::GetEngine().GetRenderer().SetColor(color.r, color.g, color.b);
        viper::GetEngine().GetRenderer().Clear();

        //model.Draw(renderer, input.GetMousePosition(), time.GetTime(), 10.0f);
		//model.Draw(renderer, transform);

		game->Draw();
        text->Draw(viper::GetEngine().GetRenderer(), 40.0f, 40.0f);

        // Create stars
        std::vector<viper::vec2> stars;
        for (int i = 0; i < 100; i++) {
            stars.push_back(viper::vec2{ viper::random::getRandomFloat() * 1280, viper::random::getRandomFloat() * 1024 });
        }

		// Draw stars
        viper::vec2 speed{ -140.0f, 0.0f };
        float length = speed.Length();

        for (auto& star : stars) {
            star += speed * viper::GetEngine().GetTime().GetDeltaTime();

            if (star[0] > 1280) star[0] = 0;
            if (star[0] < 0) star[0] = 1280;

            viper::GetEngine().GetRenderer().SetColor((uint8_t)viper::random::getRandomInt(256), viper::random::getRandomInt(256), viper::random::getRandomInt(256));
            viper::GetEngine().GetRenderer().DrawPoint(star.x, star.y);
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

        viper::GetEngine().GetRenderer().Present();
    }

	game->Shutdown();
    viper::GetEngine().Shutdown();

    return 0;
}