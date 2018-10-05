#include <SFML/Graphics.hpp>
#include <memory>
#include "Engine.h"
#include "SpriteRenderer.h"
#include "Player.h"

using uint = unsigned int;

const uint width  = 1600;
const uint height = 1200;

std::shared_ptr<Entity> makePlayer(Engine& engine) {

    auto pPlayer = engine.makeEntity<Player>();
    pPlayer->setPosition(width / 2, height * 3 / 4);

    auto pRenderer = engine.makeEntity<SpriteRenderer>("assets/player.png");
    pRenderer->setRotation(45);

    auto p = std::static_pointer_cast<Entity>(pRenderer);
    pPlayer->addChild(p);

    return pPlayer;
}

int main() {

    Engine engine(width, height);

    std::shared_ptr<Entity> pEntity = engine.makeEntity();
    engine.destroy(pEntity.get());

    auto pPlayer = makePlayer(engine);

    //engine.makeEntity<>();
    //engine.makeEntity<>();
    //engine.makeEntity<>();

    engine.run();

    return 0;
}
