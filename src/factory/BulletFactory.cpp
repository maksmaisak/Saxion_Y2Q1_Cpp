//
// Created by Maksym Maisak on 25/10/18.
//

#include "Factory.h"
#include <SFML/Graphics.hpp>
#include "Engine.h"

#include "Rigidbody.h"
#include "Bullet.h"
#include "DestroyTimer.h"
#include "GameTime.h"

namespace game {

    Entity makeBullet(Engine& engine, const sf::Vector2f& position, const sf::Vector2f& velocity) {

        EntityRegistry& registry = engine.getRegistry();
        Entity e = registry.makeEntity();

        registry.add<en::Transformable>(e).setPosition(position);

        auto& rb = registry.add<Rigidbody>(e);
        rb.velocity = velocity;
        rb.invMass = 1.f / 0.01f;

        registry.add<std::shared_ptr<sf::Drawable>>(e, std::make_shared<sf::CircleShape>(10.f, 20));
        registry.add<Bullet>(e);
        registry.add<DestroyTimer>(e, {GameTime::now() + sf::seconds(2.f)});

        return e;
    }
}