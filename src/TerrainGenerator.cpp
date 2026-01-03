#include "../includes/TerrainGenerator.h"

#define LACUNARITY 2.0
#define PERSISTENCE 0.3

TerrainGenerator::TerrainGenerator() : sprite(texture) {}

float TerrainGenerator::getFractalNoise(float x, float y, int octaves, float persistence, float lacunarity) {

    float total_noise = 0;
    float amplitude = 1.0;
    float frequency = 1.0;
    float max_value = 0;

    for (int i = 0; i < octaves; i++) {

        total_noise += perlinNoise.noise(x * frequency, y * frequency) * amplitude;
        max_value += amplitude;
        amplitude *= persistence;
        frequency *= lacunarity;

    }

    return total_noise / max_value;

}

void TerrainGenerator::createImage(int width, int height, int octaves, float frequency) {

    Image image({static_cast<unsigned int>(width), static_cast<unsigned int>(height)}, sf::Color::Black);

    for (int i = 0; i < width; i ++) {
        for (int j = 0; j < height; j ++) {

            float val = getFractalNoise(i * frequency, j * frequency, octaves, PERSISTENCE, LACUNARITY);
            image.setPixel({static_cast<unsigned int>(i), static_cast<unsigned int>(j)}, perlinNoise.getColor(val));

        }

    }

    bool ok = texture.loadFromImage(image);

    if (!ok) {

        std::cout << "Erreur chargement texture !" << std::endl;

    }
    else {std::cout << "Pas d'erreur texture" << std::endl;}
    sprite.setTexture(texture, true);

}

void TerrainGenerator::draw(RenderWindow& window) {

    window.draw(sprite);

}