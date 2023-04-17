#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <sys/time.h>

#include "screen.h"
#include "custom_code.h"

#define iWIDTH 640
#define iHEIGHT 480

/*
 * MAIN 
 */
int main() {
    sf::RenderWindow window(sf::VideoMode(iWIDTH, iHEIGHT), "SFML works!");
    sf::Texture image;
    sf::Sprite sprite;
    sf::Uint8 *pixels = new sf::Uint8[iWIDTH * iHEIGHT * 4];

    image.create(iWIDTH, iHEIGHT);
    sprite.setTexture (image);

    struct Screen screen = {.aPixels = pixels, .iWidth=iWIDTH, .iHeight=iHEIGHT};
   
    while (window.isOpen())
    {
        /* Check all window event triggered since last frame (takes about fixed 65 us) */
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        /* Clear the window (takes about fixed 120 us) */
        window.clear(sf::Color::Black);

        /* Draw (dependant on screen size) */
        customDraw (&screen);

        /* Update the pixels into the texture (dependant on screen size, about 5ns per pixel) */
        image.update(pixels);

        /* Draw the sprite from the texture (takes about fixed 150 us) */
        window.draw(sprite);

        /* End frame (takes about fixed 240 us) */
        window.display();
    }

    return 0;
}
