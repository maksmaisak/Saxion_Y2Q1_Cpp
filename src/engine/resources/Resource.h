//
// Created by Maksym Maisak on 4/11/18.
//

#ifndef SAXION_Y2Q1_CPP_RESOURCES_H
#define SAXION_Y2Q1_CPP_RESOURCES_H

#include <memory>
#include <type_traits>
#include <string>
#include <SFML/Graphics.hpp>
#include <iostream>
#include "HashedString.h"

namespace en {

    namespace internal {

        template<typename TResource, HashedString::hash_type Id, typename DefaultLoader = void>
        class ResourceInternal {

        public:
            /// Takes in parameters for the loader to use in case the resource is not present.
            template<typename TLoader = DefaultLoader, typename... Args>
            static std::shared_ptr<TResource> get(Args&&... args) {

                static_assert(!std::is_void_v<TLoader>, "Unspecified resource loader!");

                if (m_resource) return m_resource;

                std::cout << "(Re)loading" << std::endl;
                return m_resource = TLoader::load(std::forward<Args>(args)...);
            }

        private:
            inline static std::shared_ptr<TResource> m_resource = {};
        };
    }

    template<typename TResource, HashedString::hash_type Id>
    class Resource : public internal::ResourceInternal<TResource, Id> {};

    struct FontLoader {
        static std::shared_ptr<sf::Font> load(const std::string& filename) {

            auto fontPtr = std::make_shared<sf::Font>();
            bool didLoadFont = fontPtr->loadFromFile(filename);
            assert(didLoadFont);
            return fontPtr;
        }
    };

    template<HashedString::hash_type Id>
    class Resource<sf::Font, Id> : public internal::ResourceInternal<sf::Font, Id, FontLoader> {};
}

#endif //SAXION_Y2Q1_CPP_RESOURCES_H
