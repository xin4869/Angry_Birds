#ifndef VISUAL_TEXTURE_MANAGER_HPP
#define VISUAL_TEXTURE_MANAGER_HPP

#include <SFML/Graphics.hpp>
#include <unordered_map>
#include <string>
#include <stdexcept>

class TextureManager
{
private:
    static std::unordered_map<std::string, sf::Texture> textures;

public:
    static void loadTexture(const std::string& name, const std::string& filename)
    {
        sf::Texture texture;
        if (!texture.loadFromFile(filename))
        {
            // If loading fails, create a default texture
            texture.create(64, 64);
            // Optionally, fill with a color or pattern to indicate missing texture
        }
        textures[name] = std::move(texture);
    }

    static const sf::Texture& getTexture(const std::string& name)
    {
        auto it = textures.find(name);
        if (it != textures.end())
        {
            return it->second;
        }
        throw std::runtime_error("Texture not found: " + name);
    }

    // Optional: Method to check if a texture exists
    static bool hasTexture(const std::string& name)
    {
        return textures.find(name) != textures.end();
    }

    static void loadAllTextures(){
        loadTexture("IceCircle","assets/textures/ice/circle.png");
        loadTexture("IceRect","assets/textures/ice/rect.png");

        loadTexture("WoodCircle","assets/textures/wood/circle.png");
        loadTexture("WoodRect","assets/textures/wood/rect.png");

        loadTexture("StoneCircle","assets/textures/stone/circle.png");
        loadTexture("StoneRect","assets/textures/stone/rect.png");
    }

    TextureManager() = delete;
    TextureManager(const TextureManager&) = delete;
    TextureManager& operator=(const TextureManager&) = delete;

};

#endif