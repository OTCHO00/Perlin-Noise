#pragma once
#include "PerlinNoise.h"

#include <iostream>
#include <SFML/Graphics.hpp>

using namespace sf;

class TerrainGenerator {

    private:

        Texture texture;
        Sprite sprite;

        PerlinNoise perlinNoise;

    public:

        TerrainGenerator();

        void draw(RenderWindow& window);

        void createImage(int width, int height, int octaves, float frequency);

        float getFractalNoise(float x, float y, int octaves, float persistence, float lacunarity);

};