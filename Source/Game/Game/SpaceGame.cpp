#include "SpaceGame.h"
#include "Framework/Scene.h"
#include "Core/Random.h"
#include "Math/Vector2.h"
#include "Renderer/Model.h"
#include "Renderer/Renderer.h"
#include "Renderer/ParticleSystem.h"
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
	m_titleFont->Load("MetalLord.ttf", 128);

	m_uiFont = std::make_unique<viper::Font>();
	m_uiFont->Load("MetalLord.ttf", 48);

	m_titleText = std::make_unique<viper::Text>(m_titleFont);
	m_scoreText = std::make_unique<viper::Text>(m_uiFont);
	m_livesText = std::make_unique<viper::Text>(m_uiFont);

    return true;
}

void SpaceGame::Update(float dt)
{
    switch (m_gameState)
    {
    case SpaceGame::GameState::Initialize:
        m_gameState = GameState::Title;
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
		m_scene->RemoveAllActors();
        // create player
        std::shared_ptr<viper::Model> model = std::make_shared<viper::Model>(GameData::shipPoints, viper::vec3{ 0.0f, 0.4f, 1.0f });
        viper::Transform transform{ viper::vec2{ viper::GetEngine().GetRenderer().GetWidth() * 0.5f, viper::GetEngine().GetRenderer().GetHeight() * 0.5f }, 0, 5 };
        auto player = std::make_unique<Player>(transform, model);
        player->speed = 1500.0f;
        player->rotationRate = 180.0f;
        player->damping = 0.5f;
        player->name = "player";
        player->tag = "player";

        m_scene->AddActor(std::move(player));
        m_gameState = GameState::Game;
    }
    break;
    case SpaceGame::GameState::Game:
        m_enemySpawnTimer -= dt;
        if (m_enemySpawnTimer <= 0) {
            m_enemySpawnTimer = 10;

            // create enemies
            std::shared_ptr<viper::Model> enemyModel = std::make_shared<viper::Model>(GameData::enemyPoints, viper::vec3{ 1 , 1 , 1 });
            viper::Transform transform{ viper::vec2{ viper::random::getReal() * viper::GetEngine().GetRenderer().GetWidth(), viper::random::getReal() * viper::GetEngine().GetRenderer().GetHeight() }, 0, 10 };
            std::unique_ptr<Enemy> enemy = std::make_unique<Enemy>(transform, enemyModel);
            enemy->damping = 0.2f;
			enemy->fireTime = 3.0f;
            enemy->fireTimer = 5.0f;
            enemy->speed = (viper::random::getReal() * 200) + 300;
            enemy->tag = "enemy";
            m_scene->AddActor(std::move(enemy));
        }

        break;
    case SpaceGame::GameState::PlayerDead:
		m_stateTimer -= dt;
        if (m_stateTimer <= 0) {
            m_lives--;
            if (m_lives == 0) {
                m_gameState = GameState::GameOver;
				m_stateTimer = 3.0f;
            }
            else {
                m_gameState = GameState::StartRound;
            }
        }
        break;
    case SpaceGame::GameState::GameOver:
		m_stateTimer -= dt;
        if (m_stateTimer <= 0) {
            m_gameState = GameState::Title;
        }
        break;
    default:
        break;
    }

    m_scene->Update(viper::GetEngine().GetTime().GetDeltaTime());
}

void SpaceGame::Draw(viper::Renderer& renderer)
{
    if (m_gameState == GameState::Title) {
		m_titleText->Create(renderer, "PIT VIPER", viper::vec3{ 1.0f, 1.0f, 1.0f });
        m_titleText->Draw(renderer, 400, 400);
    }

    if (m_gameState == GameState::GameOver) {
        m_titleText->Create(renderer, "GAME OVER", viper::vec3{ 1.0f, 0.0f, 0.0f });
		m_titleText->Draw(renderer, 400, 400);
    }

	m_scoreText->Create(renderer, "Score: " + std::to_string(m_score), viper::vec3{ 1.0f, 1.0f, 1.0f });
	m_scoreText->Draw(renderer, 20, 20);

	m_livesText->Create(renderer, "Lives: " + std::to_string(m_lives), viper::vec3{ 1.0f, 1.0f, 1.0f });
	m_livesText->Draw(renderer, (float)renderer.GetWidth() - 100, (float)20);

    m_scene->Draw(renderer);

	viper::GetEngine().GetParticleSystem().Draw(renderer);
}

void SpaceGame::OnPlayerDeath()
{
	m_gameState = GameState::PlayerDead;
	m_stateTimer = 2.0f;
}

void SpaceGame::Shutdown()
{
    //
}
