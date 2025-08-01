#pragma once
#include "../Math/Vector2.h"
#include "../Math/Vector3.h"
#include <vector>

namespace viper {
	struct Particle {
		bool active{ false };
		float lifespan = 1;

		vec2 position;
		vec2 velocity;
		vec3 color;
	};

	class ParticleSystem {
	public:
		ParticleSystem() = default;

		bool Initialize();
		void Shutdown();

		void Update(float dt);
		void Draw(class Renderer& renderer);

		void AddParticle(const Particle& particle);

	private:
		Particle* GetFreeParticle();

	private:
		std::vector<Particle> m_particles;
	};
}