#pragma once
#include "Vertex.h"
#include "SpriteBatch.h"
#include "GLTexture.h"

#include <glm/glm.hpp>

#include <functional>

namespace SPH {



	class Particle2D {
	public:
		glm::vec2 pos = glm::vec2(0.0f);
		glm::vec2 velocity = glm::vec2(0.0f);
		Color color;
		float life = 1.0f;
		float width = 0.0f;
	};

	inline void defaultParticleUpdate(Particle2D& particle, float deltaTime) {
		particle.pos += particle.velocity * deltaTime;
	}

	class ParticleBatch2D
	{
	public:
		ParticleBatch2D();
		~ParticleBatch2D();

		void init(int maxParticles, float decayRate, GLTexture texture, std::function<void(Particle2D&, float)> updateFunc = defaultParticleUpdate);

		void update(float deltaTime);

		void draw(SpriteBatch* spriteBatch);

		void addParticle(const glm::vec2& position, const glm::vec2 velocity, const Color color, float width);

	private:
		int findFreeParticle(); 

		int m_maxParticles = 0;
		int m_lastFreeParticle = 0;
		float m_decayRate = 0.1f;

		std::function<void(Particle2D&, float)> m_updateFunc;
		Particle2D* m_particles = nullptr;
		GLTexture m_texture;

	};



}