#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include "point.h"
#include "Boule.h"
#include <cmath>
#include <sstream>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <ctime>

using namespace std;
using namespace sf;

void readPoint(Point pt) {
    std::cout << "id:" << pt.id() << " | x=" << pt.X() << " y=" << pt.Y() << std::endl;
}

std::vector<Point> massCreatePoint(std::string relPath) {
    std::ifstream flux(relPath);
    std::vector<Point> points;
    if (flux)
    {
        std::string line;
        while (std::getline(flux, line))
        {
            std::stringstream linestream(line);
            std::string sId, sX, sY;
            getline(linestream, sId, ';');
            getline(linestream, sX, ';');
            getline(linestream, sY);
            Point buffer(std::stoi(sId), std::stoi(sX) / 10, std::stoi(sY) / 10);
            points.push_back(buffer);
        }
    }
    else
    {
        std::cout << "ERREUR: Impossible d'ouvrir le fichier en lecture." << std::endl;
    }
    return points;
}

std::vector<Point> massMovePoint(std::string relPath, std::vector<Point> points) {
    std::ifstream flux(relPath);
    if (flux)
    {
        std::string line;
        while (std::getline(flux, line))
        {
            std::stringstream linestream(line);
            std::string sX, sY, sId;
            getline(linestream, sId, ';');
            getline(linestream, sX, ';');
            getline(linestream, sY);
            points[std::stoi(sId)].move(std::stoi(sX), std::stoi(sY));
        }
    }
    else
    {
        std::cout << "ERREUR: Impossible d'ouvrir le fichier en lecture." << std::endl;
    }
    return points;
}

void massPrintPoint(vector<Point> points) {
    float ballSize = 5.f;
    vector<CircleShape> circles;
    for (int i = 0; i < points.size(); i++)
    {
        CircleShape shape(ballSize);
        circles.push_back(shape);
        circles[i].setFillColor(Color(255, 0, 255));
        circles[i].setPosition(points[i].X() - ballSize, points[i].Y() - ballSize);
    }
}

int main()
{
    Clock clock;
    Font font;
    font.loadFromFile("D:\\GetDossier\\ARIAL.TTF");

    Text text;

    text.setFont(font);

    text.setString("Hello world");
    text.setCharacterSize(24);
    text.setFillColor(Color(255,0,255));
    
    std::srand(std::time(nullptr));
    
    Point point(0, 5, 10);
    int screenSizeX = 1200;
    int screenSizeY = 800;

    vector<Point> points = massCreatePoint("Point/initial.txt");

    vector<RectangleShape> shapes;
    //massPrintPoint(points);

    
    
    RenderWindow window(sf::VideoMode(screenSizeX, screenSizeY), "SFML works!");
    float ballSize = 5.f;
    RectangleShape square(Vector2f(800, 800));
    
    RectangleShape timerBack(Vector2f(100, 50));
    

    square.setFillColor(Color(0, 0, 0));
    timerBack.setFillColor(Color(255, 255, 255));

    vector<CircleShape> circles;

    vector<Boule> boules;


    for (int i = 0; i < points.size(); i++)
    {
        int randomR = std::rand() / ((RAND_MAX + 1u) / 255);
        int randomG = std::rand() / ((RAND_MAX + 1u) / 255);
        int randomB = std::rand() / ((RAND_MAX + 1u) / 255);

        Color color(randomR, randomG, randomB);
        /*CircleShape shape(ballSize);
        circles.push_back(shape);
        circles[i].setFillColor(Color(randomR, randomG, randomB));
        circles[i].setPosition(points[i].X() - ballSize, points[i].Y() - ballSize);*/

        Boule ball(i, (rand() / ((RAND_MAX + 1u) / 780)), (rand() / ((RAND_MAX + 1u) / 780)), ballSize, color, (rand() / ((RAND_MAX + 1u) / 10) - 5), (rand() / ((RAND_MAX + 1u) / 10) - 5), 0, 0);
        boules.push_back(ball);
    }

    sf::CircleShape shape(ballSize);
    shape.setFillColor(Color(255, 0, 255));
    shape.setPosition(point.X() - ballSize, point.Y() - ballSize);

    square.setPosition(Vector2f(0,0));
    
    timerBack.setPosition(950, 50);

    shapes.push_back(square);
    shapes.push_back(timerBack);

    //
    //DRAW
    //
    clock.restart();
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear(Color(52,52,52));
        window.draw(text);
        for (int i = 0; i < shapes.size(); i++)
        {
            window.draw(shapes[i]);
        }
        /*for (int i = 0; i < circles.size(); i++)
        {
            window.draw(circles[i]);
        }*/
        for (int i = 0; i < boules.size(); i++)
        {
            window.draw(boules[i].projection);
        }
        Time elapsed1 = clock.getElapsedTime();
        Time max = sf::milliseconds(10);
        Time microsec = microseconds(elapsed1.asMicroseconds());
        if (microsec >= max) {
            for (int i = 0; i < boules.size(); i++)
            {
                boules[i].move();
            }
            clock.restart();
        }
        
        window.display();
    }
    return 0;
}