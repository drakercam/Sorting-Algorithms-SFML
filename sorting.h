#ifndef SORTING_H
#define SORTING_H

#include <iostream>
#include <vector>
#include <random>
#include <SFML/Graphics.hpp>

class SortingAlgs 
{
    private:
        void SelectionSort();
        void InsertionSort();
        void BubbleSort();

        // init will handle initialization
        void Init(unsigned int size);

        std::vector<int> data;
        unsigned int size;

        // state variables for bubblesort
        unsigned int currentI;
        unsigned int currentJ;
        bool isSorted;

    public:
        SortingAlgs(unsigned int size);
        ~SortingAlgs();

        void Update();
        void Draw(sf::RenderWindow &window);

};

#endif