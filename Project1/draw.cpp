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
    std::tuple<int, int, int> RGB;
    if (iterations == -1) {
        std::get<0>(RGB) = 0;
        std::get<1>(RGB) = 0;
        std::get<2>(RGB) = 0;
    }
    else if (iterations == 0) {
        std::get<0>(RGB) = 255;
        std::get<1>(RGB) = 0;
        std::get<2>(RGB) = 0;
    }
    else {
        if (iterations < 16) {
            std::get<0>(RGB) = 16 * (16 - iterations);
            std::get<1>(RGB) = 0;
            std::get<2>(RGB) = 16 * iterations - 1;
        }
        else if (iterations < 32) {
            std::get<0>(RGB) = 0;
            std::get<1>(RGB) = 16 * (iterations - 16);
            std::get<2>(RGB) = 16 * (32 - iterations) - 1;
        }
        else if (iterations < 64) {
            std::get<0>(RGB) = 8 * (iterations - 32);
            std::get<1>(RGB) = 8 * (64 - iterations) - 1;
            std::get<2>(RGB) = 0;
        }
        else {
            std::get<0>(RGB) = 255 - (iterations - 64) * 4;
            std::get<1>(RGB) = 0;
            std::get<2>(RGB) = 0;
        }
    }

    return sf::Color(std::get<0>(RGB), std::get<1>(RGB), std::get<2>(RGB));
}
