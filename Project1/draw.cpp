#include <SFML/Graphics.hpp>
#include "Header.hpp"


int mandelbrot(double, double, int);
sf::Color getColor(int);

int main() {
    sf::RenderWindow window(sf::VideoMode(IMAGE_WIDTH, IMAGE_HEIGHT), "Mandelbrot");

    sf::Image image;
    image.create(IMAGE_WIDTH, IMAGE_HEIGHT, sf::Color(0, 0, 0));
    sf::Texture texture;
    sf::Sprite sprite;

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            switch (event.type) {
            case sf::Event::Closed:
                window.close();
                break;
            }
        }
        for (int x = 0; x < IMAGE_WIDTH; x++) {
            for (int y = 0; y < IMAGE_HEIGHT; y++) {
                double real = (x - IMAGE_WIDTH / 2.0) * zoom + offsetX;
                double imag = (y - IMAGE_HEIGHT / 2.0) * zoom + offsetY;
                int value = mandelbrot(real, imag, MAX);
                image.setPixel(x, y, getColor(value));
            }
        }
        texture.loadFromImage(image);
        sprite.setTexture(texture);

        window.clear();
        window.draw(sprite);
        window.display();

    }

    return 0;
}

int mandelbrot(double startReal, double startImag, int maximum) {
    int counter = 0;
    double zReal = startReal;
    double zImag = startImag;
    double nextRe;

    while (pow(zReal, 2.0) + pow(zImag, 2.0) <= 4.0 && counter <= maximum) {
        nextRe = pow(zReal, 2.0) - pow(zImag, 2.0) + startReal;
        zImag = 2.0 * zReal * zImag + startImag;
        zReal = nextRe;
        if (zReal == startReal && zImag == startImag) {
            return -1;
        }
        counter += 1;
    }

    if (counter >= maximum) {
        return -1;
    }
    else {
        return counter;
    }
}

sf::Color getColor(int iterations) {
    sf::Color result;
    if (iterations == -1) {
        result.r = 0;
        result.g = 0;
        result.b = 0;
    }
    else if (iterations == 0) {
        result.r = 255;
        result.g = 0;
        result.b = 0;
    }
    else {
        if (iterations < 16) {
            result.r = 16 * (16 - iterations);
            result.g = 0;
            result.b = 16 * iterations - 1;
        }
        else if (iterations < 32) {
            result.r = 0;
            result.g = 16 * (iterations - 16);
            result.b = 16 * (32 - iterations) - 1;
        }
        else if (iterations < 64) {
            result.r = 8 * (iterations - 32);
            result.g = 8 * (64 - iterations) - 1;
            result.b = 0;
        }
        else {
            result.r = 255 - (iterations - 64) * 4;
            result.g = 0;
            result.b = 0;
        }
    }

    return result;
}
