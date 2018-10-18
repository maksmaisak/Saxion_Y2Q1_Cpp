#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Shape.hpp>
#include <memory>
#include "Engine.h"

#include "Factory.h"

using uint = unsigned int;

const uint WIDTH  = 1600;
const uint HEIGHT = 1200;

const uint NUM_ASTEROIDS = 10;

int main() {

    Engine engine(WIDTH, HEIGHT);

    std::shared_ptr<Entity> pEntity = engine.makeEntity();
    engine.destroy(*pEntity);

    game::makePlayer(engine);

    for (int i = 0; i < NUM_ASTEROIDS; ++i) {
        game::makeAsteroid(engine);
    }

    engine.run();

    return 0;
}
