#include "handler.h"

Handler::Handler()
{
    // the init function will handle initialization
    Init();
}

Handler::~Handler()
{
    // delete any dynamically allocated memory here
    delete algs;
}

void Handler::Init() 
{
    // ----------- Center game window upon launch ----------------------
    screenSize = getScreenResolution();
    windowSize = sf::Vector2u(1280, 720);

    windowPos = sf::Vector2i(
        static_cast<int>((screenSize.x - windowSize.x) / 2),
        static_cast<int>((screenSize.y - windowSize.y) / 2)
    );

    window.create(sf::VideoMode(windowSize.x, windowSize.y), "Sorting Algorithms");

    window.setPosition(windowPos);
    // -----------------------------------------------------------------

    window.setVerticalSyncEnabled(true);

    choices.push_back("BubbleSort   ");
    choices.push_back("InsertionSort");
    choices.push_back("SelectionSort");
    choices.push_back("To Be Implemented");
    chosen = false;
    choiceIndex = 0;

    LoadTextures();

    algs = new SortingAlgs(720);
}

void Handler::LoadTextures()
{
    // --- Load textures and font ---
    if (!arrow.loadFromFile("textures/ARROW_SPRITE.png"))
        std::cerr << "Failed to load arrow texture." << std::endl;
    if (!cB.loadFromFile("textures/CHOOSE_SPRITE.png"))
        std::cerr << "Failed to load choose button texture." << std::endl;
    if (!font.loadFromFile("textures/ARCADECLASSIC.TTF"))
        std::cerr << "Failed to load font." << std::endl;

    // --- Set textures for sprites ---
    leftArrow.setTexture(arrow);
    rightArrow.setTexture(arrow);
    chooseButton.setTexture(cB);

    // --- Set up the text ---
    choice = choices[0];
    choiceText.setFont(font);
    choiceText.setString(choice);
    choiceText.setCharacterSize(64);
    choiceText.setFillColor(sf::Color::White);
    choiceText.setStyle(sf::Text::Bold);
    choiceText.setOutlineColor(sf::Color::Black);

    // --- Set scale factors ---
    // These scales assume your textures are sized appropriately.
    leftArrow.setScale(4.0f, 4.0f);
    rightArrow.setScale(4.0f, 4.0f);
    chooseButton.setScale(4.0f, 4.0f);

    // --- Set rotations ---
    // Left arrow should point left, right arrow should point right.
    leftArrow.setRotation(-90.0f);
    rightArrow.setRotation(90.0f);

    // --- Set origins ---
    // For the arrows, we set the origin so that positioning them relative to the text is easy.
    // Left arrow: set origin to its right-center.
    sf::FloatRect leftBounds = leftArrow.getLocalBounds();
    leftArrow.setOrigin(leftBounds.width, leftBounds.height / 2.0f);
    
    // Right arrow: set origin to its left-center.
    sf::FloatRect rightBounds = rightArrow.getLocalBounds();
    rightArrow.setOrigin(0, rightBounds.height / 2.0f);

    // Center the text by setting its origin to its center.
    sf::FloatRect textBounds = choiceText.getLocalBounds();
    choiceText.setOrigin(textBounds.left + textBounds.width / 2.0f,
                           textBounds.top + textBounds.height / 2.0f);
    
    // For the choose button, set its origin to the center.
    sf::FloatRect buttonBounds = chooseButton.getLocalBounds();
    chooseButton.setOrigin(buttonBounds.width / 2.0f, buttonBounds.height / 2.0f);

    // --- Compute positions ---
    float windowWidth = 1280.0f;
    float windowHeight = 720.0f;

    // Define a vertical position for the top group (arrows and text)
    // Adjust this value to control vertical placement.
    float groupY = windowHeight / 2.0f - 50.0f;

    // Margin between text and arrows.
    float horizontalMargin = 20.0f;
    // Vertical margin between the top group and the choose button.
    float verticalMargin = 30.0f;

    // Center the text horizontally.
    choiceText.setPosition(windowWidth / 2.0f, groupY);

    // Position left arrow to the left of the text.
    // We place it so that its right edge (because of its origin) is a margin away from the text's left edge.
    leftArrow.setPosition(choiceText.getPosition().x - textBounds.width / 2.0f - horizontalMargin,
    groupY + textBounds.height / 2.0f + buttonBounds.height / 2.0f + verticalMargin);
    
    // Position right arrow to the right of the text.
    // Its left edge (because of its origin) is a margin away from the text's right edge.
    rightArrow.setPosition(choiceText.getPosition().x + textBounds.width / 2.0f + horizontalMargin,
    groupY + textBounds.height / 2.0f + buttonBounds.height / 2.0f + verticalMargin);

    // Position the choose button below the top group (text plus arrows).
    chooseButton.setPosition(windowWidth / 2.0f, groupY + textBounds.height / 2.0f + 2 * (buttonBounds.height / 2.0f) + verticalMargin );

}



void Handler::Run()
{
    setDeltaTime(getClock().restart().asSeconds());

    sf::Event event;

    while(window.pollEvent(event))
    {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) 
        {
            event.type = sf::Event::Closed;
        }

        if (event.type == sf::Event::Closed) 
        { 
            window.close();
            std::cout << std::endl << "Closing window. Goodbye!" << std::endl;
        }
    }
    
    Update();
    Draw();
}

void Handler::Update()
{
    // update functionality to go here
    if (chosen)
    {
        algs->Update();
    }
    else
    {
        GetUserSelection();
    }
}

void Handler::Draw()
{
    window.clear();

    if (chosen)
    {
        algs->Draw(window);
    }
    else
    {
        DrawChoices();
    }

    window.display();
}

void Handler::DrawChoices()
{
    window.draw(leftArrow);
    window.draw(rightArrow);
    window.draw(chooseButton);
    window.draw(choiceText);
}

void Handler::Loop()
{
    while (window.isOpen()) 
    {
        Run();
    }
}

void Handler::GetUserSelection()
{

    static bool mouseHeld = false;
    
    if (!sf::Mouse::isButtonPressed(sf::Mouse::Left))
    {
        mouseHeld = false;
        return;
    }

    if (!mouseHeld)
    {
        sf::Vector2i mousePixelPos = sf::Mouse::getPosition(window);
        sf::Vector2f mouseWorldPos = window.mapPixelToCoords(mousePixelPos, window.getView());

        if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
        {
            // check if the mouse is within either the left arrow, right arrow, or the choose button
            if (leftArrow.getGlobalBounds().contains(mouseWorldPos))
            {
                choiceIndex -= 1;
                std::cout << "leftArrowPressed" << std::endl;

                std::cout << choiceIndex << std::endl;
                if (choiceIndex < 0)
                {
                    choiceIndex = 0;
                }

                choice = choices.at(choiceIndex);
                choiceText.setString(choice);
            }
            else if (rightArrow.getGlobalBounds().contains(mouseWorldPos))
            {
                choiceIndex += 1;
                std::cout << "rightArrowPressed" << std::endl;

                std::cout << choiceIndex << std::endl;
                if (choiceIndex >= choices.size())
                {
                    choiceIndex = choices.size() - 1;
                }

                choice = choices.at(choiceIndex);
                choiceText.setString(choice);
            }
            else if (chooseButton.getGlobalBounds().contains(mouseWorldPos))
            {
                std::cout << "chooseButtonPressed" << std::endl;
                chosen = true;
            }
            else
            {
                chosen = false;
            }

            mouseHeld = true;
        }
    }
}

sf::Vector2u Handler::getScreenResolution()
{
    sf::VideoMode desktop = sf::VideoMode::getDesktopMode();
    return sf::Vector2u(desktop.width, desktop.height);
}