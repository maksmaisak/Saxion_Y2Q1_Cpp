//
// Created by Maksym Maisak on 14/10/18.
//

#include <cmath>
#include <iostream>
#include "ParticleSystem.h"
#include "Math.h"
#include "Time.h"

void ParticleSystem::draw(sf::RenderTarget& renderTarget) {

    if (!m_pDrawable) return;

    for (std::size_t i = 0; i < m_numActiveParticles; ++i) {

        sf::RenderStates renderStates = m_particles.at(i).transform;
        renderStates.blendMode = sf::BlendNone;
        renderTarget.draw(*m_pDrawable, renderStates);
    }
}

void ParticleSystem::update(float dt) {

    std::cout << m_numActiveParticles << std::endl;

    if (m_isEmissionActive) {
        sf::Time timeSinceEmission = m_emissionTimer.getElapsedTime();

        if (timeSinceEmission > m_settings.emissionInterval) {
            do {
                timeSinceEmission -= m_settings.emissionInterval;
                updateParticle(emitParticle(), timeSinceEmission.asSeconds());
            } while (timeSinceEmission > m_settings.emissionInterval);
        }

        m_emissionTimer.restart();
    }

    for (ParticleIndex i = 0; i < m_numActiveParticles; ++i) {
        updateParticle(i, dt);
    }
}

const std::shared_ptr<sf::Drawable>& ParticleSystem::getDrawable() const {
    return m_pDrawable;
}

void ParticleSystem::setDrawable(const std::shared_ptr<sf::Drawable>& m_pDrawable) {
    ParticleSystem::m_pDrawable = m_pDrawable;
}

const ParticleSystem::Settings& ParticleSystem::getSettings() const {
    return m_settings;
}

void ParticleSystem::setSettings(const ParticleSystem::Settings& settings) {
    m_settings = settings;
}

const bool ParticleSystem::getIsEmissionActive() const {
    return m_isEmissionActive;
}

void ParticleSystem::setIsEmissionActive(bool isEmissionActive) {

    if (isEmissionActive && !m_isEmissionActive) m_emissionTimer.restart();

    m_isEmissionActive = isEmissionActive;
}

ParticleSystem::ParticleIndex ParticleSystem::emitParticle() {

    if (m_particles.size() <= m_numActiveParticles) {
        m_particles.emplace_back();
    }

    Particle& particle = m_particles.at(m_numActiveParticles);

    particle.transform
        .combine(getGlobalTransform())
        .translate(en::randomInCircle(m_settings.emissionRadius));

    particle.timeToDestroy = Time::now() + m_settings.particleLifetime;
    particle.velocity = m_settings.startVelocity + en::randomInCircle(m_settings.startVelocityRandomness);

    return m_numActiveParticles++;
}

void ParticleSystem::updateParticle(ParticleIndex i, float dt) {

    Particle& particle = m_particles.at(i);
    particle.transform.translate(particle.velocity * dt);

    if (Time::now() >= particle.timeToDestroy) {
        destroyParticle(i);
    }
}

void ParticleSystem::destroyParticle(ParticleIndex i) {

    m_numActiveParticles -= 1;

    std::swap(m_particles.at(i), m_particles.at(m_numActiveParticles));
    m_particles.at(m_numActiveParticles) = {};
}
