//
// Created by Maksym Maisak on 14/10/18.
//

#ifndef SAXION_Y2Q1_CPP_PARTICLESYSTEM_H
#define SAXION_Y2Q1_CPP_PARTICLESYSTEM_H

#include "Engine.h"

class ParticleSystem : public Entity, public Draw, public Update {

public:
    struct Settings {

        float emissionRadius = 128.f;
        sf::Time emissionInterval = sf::milliseconds(1);
        sf::Time particleLifetime = sf::milliseconds(1000);
        sf::Vector2f startVelocity = {-100, 0};
        float startVelocityRandomness = 10.f;
    };

    virtual void draw(sf::RenderTarget& renderTarget);
    virtual void update(float dt);

    const Settings& getSettings() const;
    void setSettings(const Settings& settings);

    const std::shared_ptr<sf::Drawable>& getDrawable() const;
    void setDrawable(const std::shared_ptr<sf::Drawable>& pDrawable);

    const bool getIsEmissionActive() const;
    void setIsEmissionActive(bool isEmissionActive);

private:
    struct Particle {
        sf::Transform transform;
        sf::Time timeToDestroy;
        sf::Vector2f velocity;
    };
    using ParticleIndex = std::size_t;

    const ParticleIndex DEFAULT_PARTICLES_CAPACITY = 2048;
    std::vector<Particle> m_particles {DEFAULT_PARTICLES_CAPACITY};
    ParticleIndex m_numActiveParticles = 0;

    bool m_isEmissionActive = true;
    sf::Clock m_emissionTimer;

    std::shared_ptr<sf::Drawable> m_pDrawable;
    Settings m_settings = {};

    ParticleIndex emitParticle();
    void updateParticle(ParticleIndex particleIndex, float dt);
    void destroyParticle(ParticleIndex particleIndex);
};



#endif //SAXION_Y2Q1_CPP_PARTICLESYSTEM_H