#ifndef HANDLER_H
#define HANDLER_H

#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include "sorting.h"

class Handler 
{

    private:
        sf::Vector2u screenSize;
        sf::Vector2u windowSize;
        sf::Vector2i windowPos;
        sf::RenderWindow window;

        sf::Font font;
        sf::Text choiceText;

        sf::Sprite leftArrow;
        sf::Sprite rightArrow;
        sf::Sprite chooseButton;
        sf::Texture cB;
        sf::Texture arrow;
        int choiceIndex;
        bool chosen;

        SortingAlgs* algs;

        sf::Clock clock;
        float dt;

        std::string choice;
        std::vector<std::string> choices;

        void Init();
        void Update();
        void Draw();
        void DrawChoices();
        void Run();
        void LoadTextures();

        // for getting user-input for visualization selection
        void GetUserSelection();

        sf::Vector2u getScreenResolution();


    public:
        Handler();
        ~Handler();

        void Loop();

        // getters/setters
        sf::Clock getClock() const { return clock; }
        float getDeltaTime() const { return dt; }
        void setDeltaTime(const float deltaTime) { dt = deltaTime; }
};

#endif