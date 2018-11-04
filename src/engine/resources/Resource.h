//
// Created by Maksym Maisak on 4/11/18.
//

#ifndef SAXION_Y2Q1_CPP_RESOURCES_H
#define SAXION_Y2Q1_CPP_RESOURCES_H

#include <memory>
#include <string>
#include <SFML/Graphics.hpp>
#include "HashedString.h"

namespace en {

    namespace internal {

        template<typename TResource, typename DefaultLoader = void>
        class ResourceInternal {

        public:
            template<typename TLoader = DefaultLoader, typename... Args>
            std::shared_ptr<TResource> get(Args&&... args) {

                if (m_resource) return m_resource;
                m_resource = std::move(TLoader{}.load(std::forward<Args>(args)...));
            }

        private:
            inline static std::shared_ptr<TResource> m_resource;
        };
    }

    template<typename TResource>
    class Resource : internal::ResourceInternal<TResource> {};

    struct FontLoader {
        std::shared_ptr<sf::Font> load(const std::string& filename) {
            auto fontPtr = std::make_shared<sf::Font>();
            bool didLoadFont = fontPtr->loadFromFile(filename);
            assert(didLoadFont);
            return fontPtr;
        }
    };

    template<>
    class Resource<sf::Font> : internal::ResourceInternal<sf::Font, FontLoader> {};
}

#endif //SAXION_Y2Q1_CPP_RESOURCES_H
