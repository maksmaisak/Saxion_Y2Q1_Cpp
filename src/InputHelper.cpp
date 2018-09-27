//
// Created by Maksym Maisak on 27/9/18.
//

#include "InputHelper.h"

typedef sf::Keyboard Keys;

sf::Vector2f InputHelper::getMoveInput() {

    sf::Vector2f result;

    if (Keys::isKeyPressed(Keys::Right) || Keys::isKeyPressed(Keys::D)) result.x += 1.0f;
    if (Keys::isKeyPressed(Keys::Left ) || Keys::isKeyPressed(Keys::A)) result.x -= 1.0f;

    if (Keys::isKeyPressed(Keys::Up   ) || Keys::isKeyPressed(Keys::W)) result.y -= 1.0f;
    if (Keys::isKeyPressed(Keys::Down ) || Keys::isKeyPressed(Keys::S)) result.y += 1.0f;

    return result;
}
