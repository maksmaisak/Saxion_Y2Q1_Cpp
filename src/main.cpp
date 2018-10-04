#include <SFML/Graphics.hpp>
#include "Engine.h"

int main() {

    Engine& engine = Engine::getInstance();

    std::shared_ptr<Entity> entity = engine.makeEntity();
    entity->destroy();

    engine.makeEntity();
    engine.makeEntity();
    engine.makeEntity();

    engine.run();

    return 0;
}