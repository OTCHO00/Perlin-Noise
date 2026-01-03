#include <random>
#include <iostream>
#include <imgui.h>
#include <imgui-SFML.h>
#include <SFML/Graphics.hpp>

#include "../includes/TerrainGenerator.h"

using namespace sf;

#define WIDTH 1000
#define HEIGHT 800
#define OCTAVE 2
#define FREQUENCY 0.005

int main() {

    int seed = static_cast<unsigned int>(time(nullptr));
    RenderWindow Window(VideoMode({WIDTH, HEIGHT}), "Perlin Noise");
    TerrainGenerator t;

    ImGui::SFML::Init(Window);
    Clock deltaClock;

    t.createImage(WIDTH, HEIGHT, OCTAVE, FREQUENCY);

    int octaves = OCTAVE;
    float frequency = FREQUENCY;

    while (Window.isOpen()) {

        while (auto eventOpt = Window.pollEvent()) {

            Event& event = *eventOpt;
            ImGui::SFML::ProcessEvent(Window, event);

            if (eventOpt->is<Event::Closed>()) {

                Window.close();

            }

        }    

        ImGui::SFML::Update(Window, deltaClock.restart());

        ImGui::Begin("Perlin Noise Settings");
        ImGui::SliderInt("Seed", &seed, 0, 200);
        ImGui::SliderInt("Octaves", &octaves, 0, 10);
        ImGui::SliderFloat("Frequency", &frequency, 0.001f, 0.05f);

        if (ImGui::Button("Generate")) {

            t.setSeed(static_cast<unsigned int>(seed));
            t.createImage(WIDTH, HEIGHT, octaves, frequency);

        }

        ImGui::End();

        Window.clear();

        t.draw(Window);

        ImGui::SFML::Render(Window);

        Window.display();

    }

    ImGui::SFML::Shutdown();

    return 0;

}