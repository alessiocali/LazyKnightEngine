#pragma once
#include <lazye/lazye.h>

#include <lazye/graphics/sprite.h>

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>

#include <string>

namespace lazye
{
    /**
     *  @brief A Sprite implementation based on the SFML framework
     */
    class SFMLSprite : public Sprite
    {
    public:
        SFMLSprite(const std::string& spritePath);

        virtual void SetPosition(const Vector2f& position) override;
        virtual void SetRotation(Radians rotation) override;

        inline const sf::Sprite& GetSFMLSprite() const { return m_SFMLSprite; }

    private:
        sf::Texture m_Texture;
        sf::Sprite m_SFMLSprite;

        void LoadSprite(const std::string& spritePath);
    };
}