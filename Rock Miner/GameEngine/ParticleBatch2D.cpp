#include "ParticleBatch2D.h"

namespace SPH {

	ParticleBatch2D::ParticleBatch2D()
	{
	}


	ParticleBatch2D::~ParticleBatch2D() {
		delete[] m_particles; // Need to use delete[] when u allocate an array with []
	}

	void ParticleBatch2D::init(int maxParticles, float decayRate, GLTexture texture, std::function<void(Particle2D&, float)> updateFunc) {
		m_maxParticles = maxParticles;
		m_particles = new Particle2D[maxParticles];
		m_decayRate = decayRate;
		m_texture = texture;
		m_updateFunc = updateFunc;
	}

	void ParticleBatch2D::addParticle(const glm::vec2& position, const glm::vec2 velocity, const Color color, float width) {
		int particleID = findFreeParticle();

		auto& p = m_particles[particleID];

		p.life = 1.0f;
		p.pos = position;
		p.velocity = velocity;
		p.color = color;
		p.width = width;
	}

	void ParticleBatch2D::update(float deltaTime) {
		for (int i = 0; i < m_maxParticles; i++) {
			if (m_particles[i].life > 0.0f) {
				m_updateFunc(m_particles[i], deltaTime);
				m_particles[i].life -= m_decayRate * deltaTime;
			}
		}
	}

	void ParticleBatch2D::draw(SpriteBatch* spriteBatch) {
		glm::vec4 uvRect(0.0f, 0.0f, 1.0f, 1.0f);
		for (int i = 0; i < m_maxParticles; i++) {
			auto& p = m_particles[i];
			if (p.life > 0.0f) {
				glm::vec4 destRect(p.pos.x, p.pos.y, p.width, p.width);
				spriteBatch->render(destRect, uvRect, m_texture.id, 0.0f, p.color);
			}
		}
	}

	int ParticleBatch2D::findFreeParticle() {
		for (int i = m_lastFreeParticle; i < m_maxParticles; i++) {
			if (m_particles[i].life <= 0.0f) {
				m_lastFreeParticle = i;
				return i;
			}
		}

		for (int i = 0; i < m_lastFreeParticle; i++) {
			if (m_particles[i].life <= 0.0f) {
				m_lastFreeParticle = i;
				return i;
			}
		}

		return 0;
	}
}