#include <TGUI/TGUI.hpp>
#include <TGUI/Backend/SFML-Graphics.hpp>
#include <iostream>

#ifndef _AB_UI_
#define _AB_UI_

/**
 * @brief set of related UI elements to be displayed simultaneously
 * 
 */
class UIGroup
{
public:
    tgui::Group::Ptr group;

    UIGroup(){};
};


/**
 * @brief UI for the main menu screen
 * 
 */
class MainMenu : public UIGroup
{
public:
    tgui::Button::Ptr startButton;
    tgui::Button::Ptr quitButton;

    /**
     * @brief Construct a new Main Menu object
     * 
     * @param scale UI element scale
     */
    MainMenu(float scale=1);
    void startGame();
    void exitGame();
};

MainMenu::MainMenu(float scale)
{
    group = tgui::Group::create();
    
    startButton = tgui::Button::create("Play");
    startButton->setScale(scale);
    startButton->onPress([this]{ startGame(); });
    startButton->setOrigin(0.5f, 0.5f);
    startButton->setPosition("50%", "30%");
    group->add(startButton);
    
    quitButton = tgui::Button::create("Exit");
    quitButton->setScale(scale);
    quitButton->onPress([this]{ exitGame(); });
    quitButton->setOrigin(0.5f, 0.5f);
    quitButton->setPosition("50%", "50%");
    group->add(quitButton);
}

void MainMenu::startGame()
{
    std::cout << "Game started" << std::endl;
}

void MainMenu::exitGame()
{
    std::cout << "Exit game" << std::endl;
}


/**
 * @brief UI for the levels
 * 
 */
class LevelUI : public UIGroup
{
public:
    tgui::Label::Ptr scoreDisplay;
    tgui::Label::Ptr birdsLeft;

    /**
     * @brief Construct a new Level UI object
     * 
     * @param scale UI element scale
     */
    LevelUI(float scale);
    void setScore(float score);
    void setBirdsLeft(int birds);
};

LevelUI::LevelUI(float scale)
{
    group = tgui::Group::create();
    
    scoreDisplay = tgui::Label::create("0");
    scoreDisplay->setScale(scale);
    scoreDisplay->setOrigin(0.5f, 0.5f);
    scoreDisplay->setPosition("90%", "5%");
    group->add(scoreDisplay);
    
    birdsLeft = tgui::Label::create("-1");
    birdsLeft->setScale(scale);
    birdsLeft->setOrigin(0.5f, 0.5f);
    birdsLeft->setPosition("80%", "5%");
    group->add(birdsLeft);
}

void LevelUI::setScore(float score)
{
    scoreDisplay->setText(std::to_string(score));
}

void LevelUI::setBirdsLeft(int birds)
{
    birdsLeft->setText(std::to_string(birds));
}

#endif
