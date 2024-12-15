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
    /**
     * @brief Loads texture into memory
     * @param name Name the texture will be saved with
     * @param filePath path to texture file
     */
    static void loadTexture(const std::string& name, const std::string& filePath)
    {
        sf::Texture texture;
        if (!texture.loadFromFile(filePath))
        {
            // If loading fails, create a default texture
            std::cerr << "Failed to load texture: " << filePath << std::endl;
            texture.create(64, 64);
        }
        textures[name] = std::move(texture);
    }

    /**
     * @brief Gets a texture based on the saved name
     * @param name Name of the texture
     * @return const sf::Texture& the texture
     */
    static sf::Texture& getTexture(const std::string& name)
    {
        auto it = textures.find(name);
        if (it != textures.end())
        {
            return it->second;
        }
        return textures.begin()->second;  // default texture
        //throw std::runtime_error("Texture not found: " + name);
    }

    // Optional: Method to check if a texture exists
    static bool hasTexture(const std::string& name)
    {
        return textures.find(name) != textures.end();
    }

    /**
     * @brief Loads all necessary textures into memory
     */
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

        loadTexture("IceTriangleLeft","assets/textures/ice/triangleLeft.png");
        loadTexture("IceTriangleLeftDamaged1","assets/textures/ice/triangleLeft_1.png");
        loadTexture("IceTriangleLeftDamaged2","assets/textures/ice/triangleLeft_2.png");
        loadTexture("IceTriangleLeftDamaged3","assets/textures/ice/triangleLeft_3.png");

        loadTexture("IceTriangleRight","assets/textures/ice/triangleRight.png");
        loadTexture("IceTriangleRightDamaged1","assets/textures/ice/triangleRight_1.png");
        loadTexture("IceTriangleRightDamaged2","assets/textures/ice/triangleRight_2.png");
        loadTexture("IceTriangleRightDamaged3","assets/textures/ice/triangleRight_3.png");

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
        
        loadTexture("WoodTriangleLeft","assets/textures/wood/triangleLeft.png");
        loadTexture("WoodTriangleLeftDamaged1","assets/textures/wood/triangleLeft_1.png");
        loadTexture("WoodTriangleLeftDamaged2","assets/textures/wood/triangleLeft_2.png");
        loadTexture("WoodTriangleLeftDamaged3","assets/textures/wood/triangleLeft_3.png");

        loadTexture("WoodTriangleRight","assets/textures/wood/triangleRight.png");
        loadTexture("WoodTriangleRightDamaged1","assets/textures/wood/triangleRight_1.png");
        loadTexture("WoodTriangleRightDamaged2","assets/textures/wood/triangleRight_2.png");
        loadTexture("WoodTriangleRightDamaged3","assets/textures/wood/triangleRight_3.png");

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

        loadTexture("StoneTriangleLeft","assets/textures/stone/triangleLeft.png");
        loadTexture("StoneTriangleLeftDamaged1","assets/textures/stone/triangleLeft_1.png");
        loadTexture("StoneTriangleLeftDamaged2","assets/textures/stone/triangleLeft_2.png");
        loadTexture("StoneTriangleLeftDamaged3","assets/textures/stone/triangleLeft_3.png");

        loadTexture("StoneTriangleRight","assets/textures/stone/triangleRight.png");
        loadTexture("StoneTriangleRightDamaged1","assets/textures/stone/triangleRight_1.png");
        loadTexture("StoneTriangleRightDamaged2","assets/textures/stone/triangleRight_2.png");
        loadTexture("StoneTriangleRightDamaged3","assets/textures/stone/triangleRight_3.png");

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
       loadTexture("Pig1", "assets/textures/pig/normal/1.png");
       loadTexture("Pig2", "assets/textures/pig/normal/2.png");
       loadTexture("Pig3", "assets/textures/pig/normal/3.png");
       loadTexture("PigDamage1", "assets/textures/pig/damage/1.png");
       loadTexture("PigDamage2", "assets/textures/pig/damage/2.png");
       loadTexture("PigDamage3", "assets/textures/pig/damage/3.png");
       loadTexture("PigDamage4", "assets/textures/pig/damage/4.png");

       //////////////IRON PIG ////////////////////
       loadTexture("IronPig1", "assets/textures/iron_pig/normal/1.png");
       loadTexture("IronPig2", "assets/textures/iron_pig/normal/2.png");
       loadTexture("IronPig3", "assets/textures/iron_pig/normal/3.png");
       loadTexture("IronPigDamage1", "assets/textures/iron_pig/damage/1.png");
       loadTexture("IronPigDamage2", "assets/textures/iron_pig/damage/2.png");
       loadTexture("IronPigDamage3", "assets/textures/iron_pig/damage/3.png");
       loadTexture("IronPigDamage4", "assets/textures/iron_pig/damage/4.png");

       /////////////// NORMAL BIRD ////////////////////
       loadTexture("NormalBird1", "assets/textures/normal_bird/normal/1.png");
       loadTexture("NormalBird2", "assets/textures/normal_bird/normal/2.png");
       loadTexture("NormalBirdDead", "assets/textures/normal_bird/damage/1.png");

       ////////////////SPEED BIRD ////////////////////
       loadTexture("SpeedBird1", "assets/textures/speed_bird/normal/1.png");
       loadTexture("SpeedBird2", "assets/textures/speed_bird/normal/2.png");
       loadTexture("SpeedBird3", "assets/textures/speed_bird/normal/3.png");
       loadTexture("SpeedBird4", "assets/textures/speed_bird/normal/4.png");
       loadTexture("SpeedBirdDead", "assets/textures/speed_bird/damage/1.png");

       //////////////EXPLODE BIRD ////////////////////
       loadTexture("ExplodeBird1", "assets/textures/explode_bird/normal/1.png");
       loadTexture("ExplodeBird2", "assets/textures/explode_bird/normal/2.png");
       loadTexture("ExplodeBird3", "assets/textures/explode_bird/normal/3.png");
       loadTexture("ExplodeBird4", "assets/textures/explode_bird/normal/4.png");
       loadTexture("ExplodeBird5", "assets/textures/explode_bird/normal/5.png");
       loadTexture("ExplodeBird6", "assets/textures/explode_bird/normal/6.png");
       loadTexture("ExplodeBird7", "assets/textures/explode_bird/normal/7.png");
       loadTexture("ExplodeBird8", "assets/textures/explode_bird/normal/8.png");
       loadTexture("ExplodeBirdDead", "assets/textures/explode_bird/damage/1.png");

       //////////////BUTTONS//////////////////////////
       loadTexture("play_btn", "assets/textures/buttons/play.png");
       loadTexture("help_btn", "assets/textures/buttons/help.png");
       loadTexture("music_btn", "assets/textures/buttons/music.png");
       loadTexture("no_music_btn", "assets/textures/buttons/no_music.png");
       loadTexture("no_btn", "assets/textures/buttons/no.png");
       loadTexture("lvl1_btn", "assets/textures/buttons/lvl1.png");
       loadTexture("lvl2_btn", "assets/textures/buttons/lvl2.png");
       loadTexture("lvl3_btn", "assets/textures/buttons/lvl3.png");
       loadTexture("home_btn", "assets/textures/buttons/home.png");
       loadTexture("back_btn", "assets/textures/buttons/back.png");
       loadTexture("level_btn", "assets/textures/buttons/level.png");
       loadTexture("replay_btn", "assets/textures/buttons/replay.png");
       loadTexture("next_btn", "assets/textures/buttons/next.png");

       /////////////BACKGROUNDS////////////////////////
       loadTexture("home_bg", "assets/textures/backgrounds/background.png");
       loadTexture("help_bg", "assets/textures/backgrounds/help.png");
       loadTexture("level_bg", "assets/textures/backgrounds/level.png");
       loadTexture("level1_bg", "assets/textures/backgrounds/level1.png");
       loadTexture("level2_bg", "assets/textures/backgrounds/level2.png");
       loadTexture("level3_bg", "assets/textures/backgrounds/level3.png");
       loadTexture("win_bg", "assets/textures/backgrounds/win.png");
       loadTexture("lost_bg", "assets/textures/backgrounds/lost.png");

       //////////////ELEMENTS//////////////////////////
       loadTexture("star1", "assets/textures/elements/star1.png");
       loadTexture("star2", "assets/textures/elements/star2.png");
       loadTexture("star3", "assets/textures/elements/star3.png");
       loadTexture("slingshot1", "assets/textures/elements/slingshot_1.png");
       loadTexture("slingshot2", "assets/textures/elements/slingshot_2.png");
       loadTexture("slingshot3", "assets/textures/elements/slingshot_3.png");
       loadTexture("ground", "assets/textures/elements/ground.png");
       loadTexture("block_transparent", "assets/textures/elements/block_transparent.png");
       loadTexture("cloud", "assets/textures/elements/cloud.png");
       loadTexture("blast","assets/textures/elements/blast.png" );
       loadTexture("yellow_feathers", "assets/textures/elements/yellow_feathers.png");
       loadTexture("red_feathers", "assets/textures/elements/red_feathers.png");
       loadTexture("disappear", "assets/textures/elements/disappear.png");
    }

    TextureManager() = delete;
    TextureManager(const TextureManager&) = delete;
    TextureManager& operator=(const TextureManager&) = delete;

};

std::unordered_map<std::string, sf::Texture> TextureManager::textures = { {"", sf::Texture()} };  // default texture

#endif
