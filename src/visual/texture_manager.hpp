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
        /////////////// ICE////////////////////
        loadTexture("IceCircleS","assets/textures/ice/circleS.png");
        loadTexture("IceCircleSDamaged1","assets/textures/ice/circleS_1.png");
        loadTexture("IceCircleSDamaged2","assets/textures/ice/circleS_2.png");
        loadTexture("IceCircleSDamaged3","assets/textures/ice/circleS_3.png");

        loadTexture("IceCircleM","assets/textures/ice/circleM.png");
        loadTexture("IceCircleMDamaged1","assets/textures/ice/circleM_1.png");
        loadTexture("IceCircleMDamaged2","assets/textures/ice/circleM_2.png");
        loadTexture("IceCircleMDamaged3","assets/textures/ice/circleM_3.png");

        loadTexture("IceSquare", "assets/textures/ice/square.png");
        loadTexture("IceSquareDamaged1", "assets/textures/ice/square_1.png");
        loadTexture("IceSquareDamaged2", "assets/textures/ice/square_2.png");
        loadTexture("IceSquareDamaged3", "assets/textures/ice/square_3.png");

        loadTexture("IceRect","assets/textures/ice/rect.png");
        loadTexture("IceRectDamaged1","assets/textures/ice/rect_1.png");
        loadTexture("IceRectDamaged2","assets/textures/ice/rect_2.png");
        loadTexture("IceRectDamaged3","assets/textures/ice/rect_3.png");

        loadTexture("IceRectS","assets/textures/ice/rectS.png");
        loadTexture("IceRectSDamaged1","assets/textures/ice/rectS_1.png");
        loadTexture("IceRectSDamaged2","assets/textures/ice/rectS_2.png");
        loadTexture("IceRectSDamaged3","assets/textures/ice/rectS_3.png");

        loadTexture("IceRectM","assets/textures/ice/rectM.png");
        loadTexture("IceRectMDamaged1","assets/textures/ice/rectM_1.png");
        loadTexture("IceRectMDamaged2","assets/textures/ice/rectM_2.png");
        loadTexture("IceRectMDamaged3","assets/textures/ice/rectM_3.png");

        loadTexture("IceRectL","assets/textures/ice/rectL.png");
        loadTexture("IceRectLDamaged1","assets/textures/ice/rectL_1.png");
        loadTexture("IceRectLDamaged2","assets/textures/ice/rectL_2.png");
        loadTexture("IceRectLDamaged3","assets/textures/ice/rectL_3.png");

        /////////////// WOOD////////////////////        
        loadTexture("WoodCircleS","assets/textures/wood/circleS.png");
        loadTexture("WoodCircleSDamaged1","assets/textures/wood/circleS_1.png");
        loadTexture("WoodCircleSDamaged2","assets/textures/wood/circleS_2.png");
        loadTexture("WoodCircleSDamaged3","assets/textures/wood/circleS_3.png");

        loadTexture("WoodCircleM","assets/textures/wood/circleM.png");
        loadTexture("WoodCircleMDamaged1","assets/textures/wood/circleM_1.png");
        loadTexture("WoodCircleMDamaged2","assets/textures/wood/circleM_2.png");
        loadTexture("WoodCircleMDamaged3","assets/textures/wood/circleM_3.png");

        loadTexture("WoodSquare", "assets/textures/wood/square.png");
        loadTexture("WoodSquareDamaged1", "assets/textures/wood/square_1.png");
        loadTexture("WoodSquareDamaged2", "assets/textures/wood/square_2.png");
        loadTexture("WoodSquareDamaged3", "assets/textures/wood/square_3.png");
        
        loadTexture("WoodRect","assets/textures/wood/rect.png");
        loadTexture("WoodRectDamaged1","assets/textures/wood/rect_1.png");
        loadTexture("WoodRectDamaged2","assets/textures/wood/rect_2.png");
        loadTexture("WoodRectDamaged3","assets/textures/wood/rect_3.png");

        loadTexture("WoodRectS","assets/textures/wood/rectS.png");
        loadTexture("WoodRectSDamaged1","assets/textures/wood/rectS_1.png");
        loadTexture("WoodRectSDamaged2","assets/textures/wood/rectS_2.png");
        loadTexture("WoodRectSDamaged3","assets/textures/wood/rectS_3.png");

        loadTexture("WoodRectM","assets/textures/wood/rectM.png");
        loadTexture("WoodRectMDamaged1","assets/textures/wood/rectM_1.png");
        loadTexture("WoodRectMDamaged2","assets/textures/wood/rectM_2.png");
        loadTexture("WoodRectMDamaged3","assets/textures/wood/rectM_3.png");

        loadTexture("WoodRectL","assets/textures/wood/rectL.png");
        loadTexture("WoodRectLDamaged1","assets/textures/wood/rectL_1.png");
        loadTexture("WoodRectLDamaged2","assets/textures/wood/rectL_2.png");
        loadTexture("WoodRectLDamaged3","assets/textures/wood/rectL_3.png");

//////////////////////////// STONE/////////////////////////////////
        loadTexture("StoneCircleS","assets/textures/stone/circleS.png");
        loadTexture("StoneCircleSDamaged1","assets/textures/stone/circleS_1.png");
        loadTexture("StoneCircleSDamaged2","assets/textures/stone/circleS_2.png");
        loadTexture("StoneCircleSDamaged3","assets/textures/stone/circleS_3.png");

        loadTexture("StoneCircleM","assets/textures/stone/circleM.png");
        loadTexture("StoneCircleMDamaged1","assets/textures/stone/circleM_1.png");
        loadTexture("StoneCircleMDamaged2","assets/textures/stone/circleM_2.png");
        loadTexture("StoneCircleMDamaged3","assets/textures/stone/circleM_3.png");

        loadTexture("StoneSquare", "assets/textures/stone/square.png");
        loadTexture("StoneSquareDamaged1", "assets/textures/stone/square_1.png");
        loadTexture("StoneSquareDamaged2", "assets/textures/stone/square_2.png");
        loadTexture("StoneSquareDamaged3", "assets/textures/stone/square_3.png");

        loadTexture("StoneRect","assets/textures/stone/rect.png");
        loadTexture("StoneRectDamaged1","assets/textures/stone/rect_1.png");
        loadTexture("StoneRectDamaged2","assets/textures/stone/rect_2.png");
        loadTexture("StoneRectDamaged3","assets/textures/stone/rect_3.png");

        loadTexture("StoneRectS","assets/textures/stone/rectS.png");
        loadTexture("StoneRectSDamaged1","assets/textures/stone/rectS_1.png");
        loadTexture("StoneRectSDamaged2","assets/textures/stone/rectS_2.png");
        loadTexture("StoneRectSDamaged3","assets/textures/stone/rectS_3.png");

        loadTexture("StoneRectM","assets/textures/stone/rectM.png");
        loadTexture("StoneRectMDamaged1","assets/textures/stone/rectM_1.png");
        loadTexture("StoneRectMDamaged2","assets/textures/stone/rectM_2.png");
        loadTexture("StoneRectMDamaged3","assets/textures/stone/rectM_3.png");

        loadTexture("StoneRectL","assets/textures/stone/rectL.png");
        loadTexture("StoneRectLDamaged1","assets/textures/stone/rectL_1.png");
        loadTexture("StoneRectLDamaged2","assets/textures/stone/rectL_2.png");
        loadTexture("StoneRectLDamaged3","assets/textures/stone/rectL_3.png");

       /////////////// PIG ////////////////////
       loadTexture("PigNormal", "assets/textures/pigs/normal.png");
       loadTexture("PigSmile", "assets/textures/pigs/smile.png");

       /////////////// NORMAL BIRD ////////////////////
       loadTexture("NormalBird1", "assets/textures/normal_bird/1.png");
       loadTexture("NormalBird2", "assets/textures/normal_bird/2.png");
       loadTexture("NormalBird3", "assets/textures/normal_bird/3.png");
       loadTexture("NormalBird4", "assets/textures/normal_bird/4.png");
       loadTexture("NormalBird5", "assets/textures/normal_bird/5.png");
       loadTexture("NormalBird6", "assets/textures/normal_bird/6.png");
       loadTexture("NormalBird7", "assets/textures/normal_bird/7.png");

    }

    TextureManager() = delete;
    TextureManager(const TextureManager&) = delete;
    TextureManager& operator=(const TextureManager&) = delete;

};

std::unordered_map<std::string, sf::Texture> TextureManager::textures;

#endif
