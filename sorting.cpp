#include "sorting.h"

SortingAlgs::SortingAlgs(unsigned int size)
{
    Init(size);
}

SortingAlgs::~SortingAlgs()
{
}

void SortingAlgs::Init(unsigned int size)
{
    this->size = size;

    // we want to build the vector here randomly given a size, we'll set the range between 1 and 1000
    std::random_device ranDev;
    std::mt19937 gen(ranDev());
    std::uniform_int_distribution<int> dist(1, 720);

    for (unsigned int i = 0; i < this->size; ++i) {
        int rn = dist(gen);
        data.push_back(rn);
    }

    isSorted = false;
    currentI = 0, currentJ = 0;

    // print each element to know it works
    for (unsigned int i = 0; i < this->size; ++i)
    {
        std::cout << "[" << data[i] << "] ";
        
        if (i % 10 == 0 && i != 0)
        {
            std::cout << std::endl << std::endl;
        }
    }
}

void SortingAlgs::Update()
{
    // bubble sort algorithm
    if (isSorted)
    {
        std::cout << std::endl << "sorted" << std::endl;
        return;
    }

    if (currentJ < size - currentI - 1)
    {
        if (data[currentJ] > data[currentJ+1])
        {
            std::swap(data[currentJ], data[currentJ+1]);
        }
        ++currentJ;
    }
    else
    {
        currentJ = 0;
        ++currentI;

        if (currentI >= size - 1) 
        {
            isSorted = true;
        }
    }
}

void SortingAlgs::Draw(sf::RenderWindow &window)
{
    float rectangleWidth = static_cast<float>(window.getSize().x)  / size;

    for (unsigned int i = 0; i < size; ++i)
    {
        sf::RectangleShape rectangle;
        rectangle.setSize(sf::Vector2f(rectangleWidth-1, static_cast<float>(data[i])));
        rectangle.setPosition(i * rectangleWidth, window.getSize().y - data[i]);

        if (i == currentJ || i == currentJ + 1)
        {
            rectangle.setFillColor(sf::Color::Red);
        }
        else
        {
            rectangle.setFillColor(sf::Color::Green);
        }

        std::cout << "drawing rectangle" << i << std::endl;
        window.draw(rectangle);
    }
}

void SortingAlgs::SelectionSort()
{
    int i = 0;
    while (i < size)
    {
        int pos = i;

        for (int j = i + 1; j < size; ++j)
        {
            if (data[pos] > data[j])
            {
                pos = j;
            }
        }

        int temp = data[pos];
        data[pos] = data[i];
        data[i] = temp;
        ++i;
    }
}

void SortingAlgs::InsertionSort()
{
    for (int i = 0; i < size; ++i)
    {
        int j = i;

        while (j > 0 && data[j] < data[j - 1])
        {
            int temp = data[j];
            data[j] = data[j-1];
            data[j-1] = temp;
        }
        --j;
    }
}