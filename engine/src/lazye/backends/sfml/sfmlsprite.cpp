#include <lazye/backends/sfml/sfmlsprite.h>

#include <lazye/logger.h>

namespace lazye
{
    SFMLSprite::SFMLSprite(const std::string& spritePath)
    {
        LoadSprite(spritePath);
    }

    void SFMLSprite::SetPosition(const Vector2f& position)
    {
        m_SFMLSprite.setPosition(position[0], position[1]);
    }

    void SFMLSprite::SetRotation(Radians rotation)
    {
        m_SFMLSprite.setRotation(RadToDeg(rotation));
    }

    void SFMLSprite::LoadSprite(const std::string& spritePath)
    {
        if (!m_Texture.loadFromFile(spritePath))
        {
            Log(LogLevel::Error, "Cannot load sprite:");
            Log(LogLevel::Error, spritePath);
            return;
        }

        m_SFMLSprite.setTexture(m_Texture);
    }
}