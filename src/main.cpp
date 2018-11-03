#include <SFML/Graphics.hpp>
#include <memory>
#include <algorithm>
#include <optional>
#include <vector>
#include <utils/CustomTypeIndex.h>
#include <GenerateAsteroidsSystem.h>
#include "Messaging.h"
#include "Engine.h"
#include "Actor.h"
#include "Transformable.h"
#include "Rigidbody.h"
#include "DrawInfo.h"

#include "RenderSystem.h"
#include "PhysicsSystem.h"
#include "DestroyByTimerSystem.h"
#include "WrapAroundScreenSystem.h"
#include "FlickerSystem.h"
#include "PlayerControlsSystem.h"
#include "BreakAsteroidSystem.h"
#include "PlayerDeathSystem.h"
#include "ShootSystem.h"
#include "DiagnosticsSystem.h"
#include "GenerateAsteroidsSystem.h"
#include "ScoreSystem.h"

#include "CustomTypeIndex.h"

#include "Collision.h"

#include "Factory.h"

using uint = unsigned int;

const uint Width  = 1600;
const uint Height = 1200;
const bool EnableVSync = true;

int main() {

    Engine engine(Width, Height, EnableVSync);

    {
        engine.addSystem<RenderSystem>();
        engine.addSystem<PhysicsSystem>();
        engine.addSystem<DestroyByTimerSystem>();

        engine.addSystem<PlayerControlsSystem>();
        engine.addSystem<ShootSystem>();
        engine.addSystem<WrapAroundScreenSystem>();
        engine.addSystem<BreakAsteroidSystem>();
        engine.addSystem<PlayerDeathSystem>();
        engine.addSystem<GenerateAsteroidsSystem>();

        engine.addSystem<ScoreSystem>();
        //engine.addSystem<FlickerSystem>();

        engine.addSystem<DiagnosticsSystem>();
    }

    game::makeMainLevel(engine);

    engine.run();

    return 0;
}
