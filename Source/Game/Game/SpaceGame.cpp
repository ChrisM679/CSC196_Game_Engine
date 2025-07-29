#include "SpaceGame.h"
#include "Framework/Scene.h"
#include "Core/Random.h"
#include "Math/Vector2.h"
#include "Renderer/Model.h"
#include "Renderer/Renderer.h"
#include "Input/InputSystem.h"
#include "Engine.h"
#include "Player.h"
#include "Enemy.h"
#include "../GameData.h"

#include <vector>

bool SpaceGame::Initialize()
{
    m_scene = std::make_unique<viper::Scene>(this);

    m_titleFont = std::make_unique<viper::Font>();
	m_titleFont->Load("Assets/MetalLord.ttf", 128);

	m_uiFont = std::make_unique<viper::Font>();
	m_uiFont->Load("Assets/MetalLord.ttf", 48);

    return true;
}

void SpaceGame::Update(float dt)
{
    switch (m_gameState)
    {
    case SpaceGame::GameState::Initialize:
        m_gameState = GameState::StartGame;
        break;

    case SpaceGame::GameState::Title:
        if (viper::GetEngine().GetInput().GetKeyPressed(SDL_SCANCODE_SPACE)) {
            m_gameState = GameState::StartGame;
        }
        break;

    case SpaceGame::GameState::StartGame:
        m_score = 0;
        m_lives = 3;
        m_gameState = GameState::StartRound;
        break;

    case SpaceGame::GameState::StartRound:
    {
        // create player
        std::shared_ptr<viper::Model> model = std::make_shared<viper::Model>(GameData::shipPoints, viper::vec3{ 0.0f, 0.4f, 1.0f });
        viper::Transform transform{ viper::vec2{ viper::GetEngine().GetRenderer().GetWidth() * 0.5f, viper::GetEngine().GetRenderer().GetHeight() * 0.5f }, 0, 5 };
        auto player = std::make_unique<Player>(transform, model);
        player->speed = 1500.0f;
        player->rotationRate = 180.0f;
        player->damping = 1.5f;
        player->name = "player";
        player->tag = "player";

        m_scene->AddActor(std::move(player));
        m_gameState = GameState::Game;
    }
    break;
    case SpaceGame::GameState::Game:
        m_enemySpawnTimer -= dt;
        if (m_enemySpawnTimer <= 0) {
            m_enemySpawnTimer = 4;

            // create enemies
            std::shared_ptr<viper::Model> enemyModel = std::make_shared<viper::Model>(GameData::enemyPoints, viper::vec3{ viper::random::getReal(), viper::random::getReal(), viper::random::getReal() });
            viper::Transform transform{ viper::vec2{ viper::random::getReal() * viper::GetEngine().GetRenderer().GetWidth(), viper::random::getReal() * viper::GetEngine().GetRenderer().GetHeight() }, 0, 10 };
            std::unique_ptr<Enemy> enemy = std::make_unique<Enemy>(transform, enemyModel);
            enemy->damping = 0.2f;
            enemy->speed = (viper::random::getReal() * 800) + 500;
            enemy->tag = "enemy";
            m_scene->AddActor(std::move(enemy));
        }

        break;
    case SpaceGame::GameState::PlayerDead:
        m_lives--;
        if (m_lives == 0) m_gameState = GameState::GameOver;
        else {
            m_gameState = GameState::StartRound;
        }
        break;
    case SpaceGame::GameState::GameOver:
        break;
    default:
        break;
    }

    m_scene->Update(viper::GetEngine().GetTime().GetDeltaTime());
}

void SpaceGame::Draw()
{
    m_scene->Draw(viper::GetEngine().GetRenderer());
}

void SpaceGame::Shutdown()
{
    //
}
