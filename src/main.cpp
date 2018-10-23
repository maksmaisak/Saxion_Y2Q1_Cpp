#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Shape.hpp>
#include <memory>
#include <algorithm>
#include <optional>
#include <systems/WrapAroundScreenSystem.h>
#include "Engine.h"
#include "Actor.h"
#include "Transformable.h"

#include "RenderSystem.h"
#include "PhysicsSystem.h"
#include "WrapAroundScreenSystem.h"
#include "FlickerSystem.h"

#include "Factory.h"
#include "Rigidbody.h"

using uint = unsigned int;

const uint WIDTH  = 1600;
const uint HEIGHT = 1200;

const uint NUM_ASTEROIDS = 10;

int main() {

    Engine engine(WIDTH, HEIGHT);
    engine.addSystem<RenderSystem>();
    engine.addSystem<PhysicsSystem>();
    engine.addSystem<WrapAroundScreenSystem>();
    //engine.addSystem<FlickerSystem>();

    EntityRegistry& registry = engine.getRegistry();

    {
        Entity entity = registry.makeEntity();
        registry.add<en::Transformable>(entity);
        registry.add<std::shared_ptr<sf::Drawable>>(entity, std::make_shared<sf::CircleShape>(10.f, 20));
        auto& rb = registry.add<Rigidbody>(entity);
        rb.velocity = {100.f, 800.f};
        rb.radius = 10.f;
        //registry.destroy(entity);
    }

    game::makePlayer(engine);
    for (int i = 0; i < NUM_ASTEROIDS; ++i) {
        game::makeAsteroid(engine);
    }

    engine.run();

    return 0;
}
