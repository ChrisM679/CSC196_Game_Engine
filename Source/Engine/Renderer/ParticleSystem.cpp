#include "ParticleSystem.h"
#include "Renderer.h"

namespace viper {
	bool ParticleSystem::Initialize() {
		m_particles.resize(1000);

		return true;
	}

	void ParticleSystem::Shutdown() {
		m_particles.clear();
	}

	void ParticleSystem::Update(float dt) {
		for (auto& particle : m_particles) {
			if (particle.active) {
				particle.lifespan -= dt;
				if (particle.lifespan <= 0.0f) {
					particle.active = false;
					continue;
				}
				particle.position += particle.velocity * dt;
			}
		}
	}

	void ParticleSystem::Draw(class Renderer& renderer) {
		for (const auto& particle : m_particles) {
			if (particle.active) {
				renderer.SetColor(particle.color.r, particle.color.g, particle.color.b);
				renderer.DrawPoint(particle.position.x, particle.position.y);
			}
		}
	}

	void ParticleSystem::AddParticle(const Particle& particle) {
		Particle* Particle = GetFreeParticle();
		if (Particle) {
			*Particle = particle;
			Particle->active = true;
		}
	}

	Particle* ParticleSystem::GetFreeParticle() {
		for (auto& particle : m_particles) {
			if (!particle.active) {
				return &particle;
			}
		}
		return nullptr;
	}

}
