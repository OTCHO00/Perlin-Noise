#pragma once

#include <map>
#include <math.h>
#include <vector>
#include <random>
#include <algorithm>
#include <SFML/Graphics.hpp>

using namespace sf;
using namespace std;

struct Vec2 {

    float x, y;

};

class PerlinNoise {

    private:

        float dot0, dot1, dot2, dot3;

        vector<int> Perlin;
        vector<Vec2> gradients;      
        
        mt19937 generator;

    public:

        PerlinNoise(unsigned int seed = std::random_device{}());

        float fade(float t);

        int hash(int x, int y);

        void generatePermutation();

        Color getColor(float noise);

        float noise(float x, float y);

        void setSeed(unsigned int seed);

        Vec2 distance(Vec2 point, Vec2 coin);

        float lerp(float a, float b, float t);

        float scalaire(Vec2 gradient, Vec2 distance);

};