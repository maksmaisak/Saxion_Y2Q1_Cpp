#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Shape.hpp>
#include <memory>
#include <algorithm>
#include "Engine.h"
#include "Asteroid.h"
#include "DrawableRenderer.h"

#include "Factory.h"

using uint = unsigned int;

const uint WIDTH  = 1600;
const uint HEIGHT = 1200;

const uint NUM_ASTEROIDS = 10;

int main() {

    Engine engine(WIDTH, HEIGHT);

    {
        std::shared_ptr<Entity> pEntity = engine.makeEntity();
        engine.destroy(*pEntity);
    }

    auto pPlayer = game::makePlayer(engine);

    for (int i = 0; i < NUM_ASTEROIDS; ++i) {
        game::makeAsteroid(engine);
    }

    std::size_t count = 0;
    for (auto& pEntity : engine.with<Asteroid, DrawableRenderer>()) {
        ++count;
    }
    std::cout << count << " entities with Asteroid and DrawableRenderer" << std::endl;

    engine.run();

    return 0;
}
