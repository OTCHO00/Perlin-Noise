#include "../includes/PerlinNoise.h"

PerlinNoise::PerlinNoise(unsigned int seed) : generator(seed) {

    gradients = {{1, 1}, {-1, 1}, {1, -1}, {-1, -1}, {1, 0}, {-1, 0}, {0, 1}, {0, -1}, {1, 1}, {-1, 1}, {1, -1}, {-1, -1}};
    generatePermutation();

}

void PerlinNoise::generatePermutation() {

    for (int i = 0; i <= 255; i ++) {

        Perlin.push_back(i);

    }

    int size = Perlin.size();

    shuffle(Perlin.begin(), Perlin.end(), generator);

    Perlin.insert(Perlin.end(), Perlin.begin(), Perlin.begin() + size);

}


void PerlinNoise::setSeed(unsigned int seed) {

    generator.seed(seed);
    generatePermutation();

}

int PerlinNoise::hash(int x, int y) {

    int ix = (int)x & 255;
    int iy = (int)y & 255;

    return Perlin[Perlin[ix] + iy];

}

Vec2 PerlinNoise::distance(Vec2 point, Vec2 coin) {

    auto [pointX, pointY] = point;
    auto [coinX, coinY] = coin;

    Vec2 distance {pointX - coinX, pointY - coinY};
    
    return distance;

}

float PerlinNoise::scalaire(Vec2 gradient, Vec2 distance) {

    auto [gradientX, gradientY] = gradient;
    auto [distanceX, distanceY] = distance;

    return (gradientX * distanceX) + (gradientY * distanceY);


}

float PerlinNoise::fade(float t) {

    return t * t * t * (t * (t * 6 - 15) + 10);

}

float PerlinNoise::lerp(float a, float b, float t) {

    return a + t * (b - a);

}

float PerlinNoise::noise(float x, float y) {

    Vec2 point {x, y};

    int X = floor(x);
    int Y = floor(y);

    float xRel = x - X;
    float yRel = y - Y;

    float u = fade(xRel);
    float v = fade(yRel);

    int h0 = hash(X, Y);
    Vec2 grad0 = gradients[h0 % 12];
    Vec2 dist0 = {xRel, yRel};
    float dot0 = scalaire(grad0, dist0);

    int h1 = hash(X + 1, Y);
    Vec2 grad1 = gradients[h1 % 12];
    Vec2 dist1 = {xRel - 1.0f, yRel};
    float dot1 = scalaire(grad1, dist1);

    int h2 = hash(X, Y + 1);
    Vec2 grad2 = gradients[h2 % 12];
    Vec2 dist2 = {xRel, yRel - 1.0f};
    float dot2 = scalaire(grad2, dist2);

    int h3 = hash(X + 1, Y + 1);
    Vec2 grad3 = gradients[h3 % 12];
    Vec2 dist3 = {xRel - 1.0f, yRel - 1.0f};
    float dot3 = scalaire(grad3, dist3);

    float bas = lerp(dot0, dot1, u);
    float haut = lerp(dot2, dot3, u);

    float resultat = lerp(bas, haut, v);

    return resultat;

}

Color PerlinNoise::getColor(float noise) {

    if (noise < -0.60f) return Color(0, 0, 80);
    if (noise < -0.30f) return Color(0, 100, 200);
    if (noise < -0.10f) return Color(220, 210, 140);
    if (noise < 0.25f) return Color(50, 180, 50);
    if (noise < 0.50f) return Color(20, 120, 20);
    if (noise < 0.75f) return Color(130, 130, 130);
    
    return Color(255, 255, 255);

}