#include <random>
#include <iostream>
#include <SFML/Graphics.hpp>

#include "../includes/TerrainGenerator.h"

using namespace sf;

#define WIDTH 1000
#define HEIGHT 800

int main() {

    RenderWindow Window(VideoMode({WIDTH, HEIGHT}), "Perlin Noise");
    TerrainGenerator t;

    t.createImage(WIDTH, HEIGHT);

    while (Window.isOpen()) {

        while (auto event = Window.pollEvent()) {

            if (event->is<Event::Closed>()) {

                Window.close();

            }

        }    

        Window.clear();

        t.draw(Window);

        Window.display();

    }

    return 0;

}