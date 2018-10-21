//
// Created by Maksym Maisak on 14/10/18.
//

#include <cmath>
#include <iostream>
#include <algorithm>
#include "ParticleSystem.h"
#include "MyMath.h"
#include "GameTime.h"

void ParticleSystem::draw(sf::RenderTarget& renderTarget) {

    if (!m_pDrawable) return;

    for (std::size_t i = 0; i < m_numActiveParticles; ++i) {

        renderTarget.draw(
            *m_pDrawable,
            sf::RenderStates(sf::BlendAlpha, m_particles.at(i).transform, nullptr, nullptr)
        );
    }
}

void ParticleSystem::update(float dt) {

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

    if (m_numActiveParticles >= m_maxNumParticles) {
        destroyOldestParticle();
    } else if (m_particles.size() <= m_numActiveParticles) {
        m_particles.emplace_back();
    }

    Particle& particle = m_particles.at(m_numActiveParticles);

    particle.transform = m_Entity.getGlobalTransform();
    particle.transform.translate(en::randomInCircle(m_settings.emissionRadius));
    particle.timeToDestroy = GameTime::now() + m_settings.particleLifetime;

    particle.velocity = m_settings.startVelocity + en::randomInCircle(m_settings.startVelocityRandomness);

    return m_numActiveParticles++;
}

void ParticleSystem::updateParticle(ParticleIndex i, float dt) {

    Particle& particle = m_particles.at(i);

    if (GameTime::now() >= particle.timeToDestroy) {
        destroyParticle(i);
        return;
    }

    sf::Transform& transform = particle.transform;
    transform.translate(particle.velocity * dt);

    /*sf::Vector2f viewSize = getEntity()->getEngine()->getWindow().getView().getSize();
    sf::Vector2f position = transform.transformPoint(0, 0);

    if (position.y < 0) transform.translate(0, viewSize.y);
    else if (position.y > viewSize.y) transform.translate(0, -viewSize.y);

    if (position.x < 0) transform.translate(viewSize.x, 0);
    else if (position.x > viewSize.x) transform.translate(-viewSize.x, 0);*/
}

void ParticleSystem::destroyParticle(ParticleIndex i) {

    assert(m_numActiveParticles > 0);
    m_numActiveParticles -= 1;

    std::swap(m_particles.at(i), m_particles.at(m_numActiveParticles));

    // For safety. Can just remove to improve performance, as long as everything gets reinitialized when emitting.
    m_particles.at(m_numActiveParticles) = {};
}

void ParticleSystem::destroyOldestParticle() {

    auto it = std::min_element(m_particles.begin(), m_particles.end(), [](Particle& a, Particle& b){return a.timeToDestroy < b.timeToDestroy;});
    auto index = static_cast<ParticleIndex>(std::distance(m_particles.begin(), it));
    destroyParticle(index);
}

