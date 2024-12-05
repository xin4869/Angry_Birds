#ifndef SOUND_MANAGER_HPP
#define SOUND_MANAGER_HPP

#include <SFML/Audio.hpp>
#include <unordered_map>
#include <string>
#include <stdexcept>

class SoundManager
{
private:
    static std::unordered_map<std::string, sf::SoundBuffer*> sounds;
    static std::unordered_map<std::string, std::string> musicMap;  // <name, filePath>
    static sf::Music music;

public:
    /**
     * @brief Play music file. Stops current music.
     * @param name Name of music file. See initialization.
     * @return true if success
     */
    static bool playMusic(const std::string& name) {
        music.stop();
        if (musicMap.find(name) == musicMap.end()) return false;
        bool res = music.openFromFile(musicMap[name]);
        music.setLoop(true);
        music.play();
        return res;
    }

    static void stopMusic() {
        music.stop();
    }

    /**
     * @brief Set Music Volume
     * @param volume volume 0-100
     */
    static void setMusicVolume(float volume) {
        music.setVolume(volume);
    }

    static float getMusicVolume() {
        return music.getVolume();
    }

    static void loadSound(const std::string& name, const std::string& filePath)
    {
        sf::SoundBuffer* sound = new sf::SoundBuffer;
        if (!sound->loadFromFile(filePath))
        {
            delete sound;
            return;
        }
        sounds[name] = sound;
    }

    static const sf::SoundBuffer* getSound(const std::string& name)
    {
        auto it = sounds.find(name);
        if (it != sounds.end())
        {
            return it->second;
        }
        return nullptr;
        //throw std::runtime_error("Sound not found: " + name);
    }

    // Optional: Method to check if a sound exists
    static bool hasSound(const std::string& name)
    {
        return sounds.find(name) != sounds.end();
    }

    static void loadAllSounds(){
        // possibly make a loop here? these are generated anyway

        // birds
        loadSound("bird 01 collision a1", "assets/audio/bird 01 collision a1.wav");
        loadSound("bird 01 collision a2", "assets/audio/bird 01 collision a2.wav");
        loadSound("bird 01 collision a3", "assets/audio/bird 01 collision a3.wav");
        loadSound("bird 01 collision a4", "assets/audio/bird 01 collision a4.wav");
        loadSound("bird 01 flying", "assets/audio/bird 01 flying.wav");
        loadSound("bird 01 select", "assets/audio/bird 01 select.wav");
        loadSound("bird 02 collision a1", "assets/audio/bird 02 collision a1.wav");
        loadSound("bird 02 collision a2", "assets/audio/bird 02 collision a2.wav");
        loadSound("bird 02 collision a3", "assets/audio/bird 02 collision a3.wav");
        loadSound("bird 02 collision a4", "assets/audio/bird 02 collision a4.wav");
        loadSound("bird 02 collision a5", "assets/audio/bird 02 collision a5.wav");
        loadSound("bird 02 flying", "assets/audio/bird 02 flying.wav");
        loadSound("bird 02 select", "assets/audio/bird 02 select.wav");
        loadSound("bird 03 collision a1", "assets/audio/bird 03 collision a1.wav");
        loadSound("bird 03 collision a2", "assets/audio/bird 03 collision a2.wav");
        loadSound("bird 03 collision a3", "assets/audio/bird 03 collision a3.wav");
        loadSound("bird 03 collision a4", "assets/audio/bird 03 collision a4.wav");
        loadSound("bird 03 collision a5", "assets/audio/bird 03 collision a5.wav");
        loadSound("bird 03 flying", "assets/audio/bird 03 flying.wav");
        loadSound("bird 03 select", "assets/audio/bird 03 select.wav");
        loadSound("bird 04 collision a1", "assets/audio/bird 04 collision a1.wav");
        loadSound("bird 04 collision a2", "assets/audio/bird 04 collision a2.wav");
        loadSound("bird 04 collision a3", "assets/audio/bird 04 collision a3.wav");
        loadSound("bird 04 collision a4", "assets/audio/bird 04 collision a4.wav");
        loadSound("bird 04 flying", "assets/audio/bird 04 flying.wav");
        loadSound("bird 04 select", "assets/audio/bird 04 select.wav");
        loadSound("bird 05 collision a1", "assets/audio/bird 05 collision a1.wav");
        loadSound("bird 05 collision a2", "assets/audio/bird 05 collision a2.wav");
        loadSound("bird 05 collision a3", "assets/audio/bird 05 collision a3.wav");
        loadSound("bird 05 collision a4", "assets/audio/bird 05 collision a4.wav");
        loadSound("bird 05 collision a5", "assets/audio/bird 05 collision a5.wav");
        loadSound("bird 05 flying", "assets/audio/bird 05 flying.wav");
        loadSound("bird 05 select", "assets/audio/bird 05 select.wav");
        loadSound("bird destroyed", "assets/audio/bird destroyed.wav");
        loadSound("bird shot-a1", "assets/audio/bird shot-a1.wav");
        loadSound("bird shot-a2", "assets/audio/bird shot-a2.wav");
        loadSound("bird shot-a3", "assets/audio/bird shot-a3.wav");

        // ice
        loadSound("ice light collision a2", "assets/audio/ice light collision a2.wav");
        loadSound("ice light collision a1", "assets/audio/ice light collision a1.wav");
        loadSound("ice light collision a3", "assets/audio/ice light collision a3.wav");
        loadSound("ice light collision a4", "assets/audio/ice light collision a4.wav");
        loadSound("ice light collision a5", "assets/audio/ice light collision a5.wav");
        loadSound("ice light collision a6", "assets/audio/ice light collision a6.wav");
        loadSound("ice light collision a7", "assets/audio/ice light collision a7.wav");
        loadSound("ice light collision a8", "assets/audio/ice light collision a8.wav");
        
        // pigs
        loadSound("piglette damage a4", "assets/audio/piglette damage a4.wav");
        loadSound("piglette damage a7", "assets/audio/piglette damage a7.wav");
        loadSound("piglette destroyed", "assets/audio/piglette destroyed.wav");
        
        // rock
        loadSound("rock collision a1", "assets/audio/rock collision a1.wav");
        loadSound("rock collision a2", "assets/audio/rock collision a2.wav");
        loadSound("rock collision a3", "assets/audio/rock collision a3.wav");
        loadSound("rock collision a4", "assets/audio/rock collision a4.wav");
        loadSound("rock collision a5", "assets/audio/rock collision a5.wav");
        loadSound("rock damage a1", "assets/audio/rock damage a1.wav");
        loadSound("rock damage a2", "assets/audio/rock damage a2.wav");
        loadSound("rock damage a3", "assets/audio/rock damage a3.wav");
        loadSound("rock destroyed a1", "assets/audio/rock destroyed a1.wav");
        loadSound("rock destroyed a2", "assets/audio/rock destroyed a2.wav");
        loadSound("rock destroyed a3", "assets/audio/rock destroyed a3.wav");
        loadSound("rock rolling", "assets/audio/rock rolling.wav");
        
        // misc
        loadSound("chainsaw", "assets/audio/chainsaw.wav");
        loadSound("slingshot streched", "assets/audio/slingshot streched.wav");
        loadSound("special boost", "assets/audio/special boost.wav");
        loadSound("tnt box explodes", "assets/audio/tnt box explodes.wav");
        
        // wood
        loadSound("wood collision a1", "assets/audio/wood collision a1.wav");
        loadSound("wood collision a2", "assets/audio/wood collision a2.wav");
        loadSound("wood collision a3", "assets/audio/wood collision a3.wav");
        loadSound("wood collision a4", "assets/audio/wood collision a4.wav");
        loadSound("wood collision a5", "assets/audio/wood collision a5.wav");
        loadSound("wood collision a6", "assets/audio/wood collision a6.wav");
        loadSound("wood damage a1", "assets/audio/wood damage a1.wav");
        loadSound("wood damage a2", "assets/audio/wood damage a2.wav");
        loadSound("wood damage a3", "assets/audio/wood damage a3.wav");
        loadSound("wood destroyed a1", "assets/audio/wood destroyed a1.wav");
        loadSound("wood destroyed a2", "assets/audio/wood destroyed a2.wav");
        loadSound("wood destroyed a3", "assets/audio/wood destroyed a3.wav");
        loadSound("wood rolling", "assets/audio/wood rolling.wav");
    }

    ~SoundManager()
    {
        for (auto i: sounds)
        {
            delete i.second;
        }
    }

    SoundManager() = delete;
    SoundManager(const SoundManager&) = delete;
    SoundManager& operator=(const SoundManager&) = delete;

};

std::unordered_map<std::string, sf::SoundBuffer*> SoundManager::sounds;
sf::Music SoundManager::music;
std::unordered_map<std::string, std::string> SoundManager::musicMap = {
    { "Theme song", "assets/audio/Angry Birds Theme.flac" },
    { "Forest ambient", "assets/audio/Ambient White Dryforest.ogg" }
};

#endif
