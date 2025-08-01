#include "Enemy.h"
#include "Engine.h"
#include "Framework/Scene.h"
#include "Framework/Game.h"
#include "Renderer/Renderer.h"
#include "Renderer/Model.h"
#include "Core/Random.h"
#include "Renderer/ParticleSystem.h"
#include "Player.h"
#include "../Rocket.h"
#include "../GameData.h"
#include "Math/Vector3.h"

void Enemy::Update(float dt)
{
	Actor* player = m_scene->GetactorByName("player");
	if (player)
	{
		viper::vec2 direction{ 0, 0 };
		direction = player->m_transform.position - m_transform.position;
		direction = direction.Normalized();
		m_transform.rotation = viper::math::radToDeg(direction.Angle());
	}

	viper::vec2 force = viper::vec2{ 1,0 }.Rotate(viper::math::degToRad(m_transform.rotation)) * speed;
	velocity += force;

	m_transform.position.x = viper::math::wrap(m_transform.position.x, 0.0f, (float)viper::GetEngine().GetRenderer().GetWidth());
	m_transform.position.y = viper::math::wrap(m_transform.position.y, 0.0f, (float)viper::GetEngine().GetRenderer().GetHeight());

	fireTimer -= dt;
	if (fireTimer <= 0) {
		fireTimer = fireTime;

		std::shared_ptr<viper::Model> model = std::make_shared<viper::Model>(GameData::shipPoints, viper::vec3{ 0.0f, 1.0f, 1.0f });

		viper::Transform m_transform{ this->m_transform.position, this->m_transform.rotation, 2.0f };
		auto rocket = std::make_unique<Rocket>(m_transform, model);
		rocket->speed = 500.0f;
		rocket->lifespan = 1.5f;
		rocket->name = "rocket";
		rocket->tag = "enemy";

		m_scene->AddActor(std::move(rocket));
	}

	Actor::Update(dt);
}

void Enemy::OnCollision(Actor* other)
{
	if (tag != other->tag) {
		destroyed = true;
		m_scene->GetGame()->AddPoints(100);
		for (int i = 0; i < 100; i++) {
			viper::Particle particle;
			particle.position = m_transform.position;
			particle.velocity = viper::random::onUnitCircle() * viper::random::getReal(10.0f, 200.0f);
			particle.color = viper::vec3{ 1, 1, 1 };
			particle.lifespan = 2;
		}
	}
}
