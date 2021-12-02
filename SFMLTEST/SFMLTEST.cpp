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

void readPoint(Point pt) {//Lit les informations d'un points, été utile avant
    std::cout << "id:" << pt.id() << " | x=" << pt.X() << " y=" << pt.Y() << std::endl;
}

std::vector<Point> massCreatePoint(std::string relPath) {//Creer plein de point selon un fichier
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

std::vector<Point> massMovePoint(std::string relPath, std::vector<Point> points) {//Bouge tout les points selon un fichier
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

float randInRange(float min, float max) {
    float res = 0;
    if (min < max) {
       res = rand() / ((RAND_MAX + 1u) / max) + min;
    }
    else {
        cerr << "Le minimum ne peut être supérieur au maximum" << endl;
    }
    return res;
}

int main()
{
    srand(std::time(nullptr));//initialisation du random
    Clock clock;
    Clock minuteur;
    Font font;
    if (!font.loadFromFile("ARIAL.TTF"))
        cerr << "could not load font from file" << endl;
    int screenSizeX = 1200;
    int screenSizeY = 800;

    
    vector<RectangleShape> shapes; //Vecteur des formes de fonds

    RectangleShape square(Vector2f(800, 800)); //Carée ou se déplace les boules
    square.setFillColor(Color(0, 0, 0));
    RectangleShape timerBack(Vector2f(100, 50)); //Fond de la clock
    timerBack.setFillColor(Color(255, 255, 255));

    RenderWindow window(sf::VideoMode(screenSizeX, screenSizeY), "SFML works!");

    //vector<Point> points = massCreatePoint("Point/initial.txt"); // vecteur de point pour générer les boules selon un fichier
    //vector<CircleShape> circles; 

    //On creez un vecteur de boule et on y stock 100 boules de position et de couleur aléatoire
    vector<Boule> boules;
    float ballSize = 5.f;
    for (int i = 0; i < 100; i++)
    {

        Color color(randInRange(0, 255), randInRange(0, 255), randInRange(0, 255));
        CircleShape shape(ballSize);
        //circles.push_back(shape);
        //circles[i].setFillColor(Color(randomR, randomG, randomB));
        //circles[i].setPosition(points[i].X() - ballSize, points[i].Y() - ballSize);

        Boule ball(i, randInRange(10,780), randInRange(10,780), ballSize, color, randInRange(-5,10), randInRange(-5,10), 0, 0);
        boules.push_back(ball);
    }

    square.setPosition(Vector2f(0,0));
    timerBack.setPosition(Vector2f(950, 50));

    shapes.push_back(square);
    shapes.push_back(timerBack);

    Text text("Hello world", font);//servira pour afficher la clock
    text.setCharacterSize(24);
    text.setFillColor(Color(255, 0, 255));
    text.setPosition(950, 50);

    sf::Text tdisp("",font); // Servira à écrire du texte manuellement
    tdisp.setPosition(Vector2f(820, 100));
    tdisp.setCharacterSize(24);
    tdisp.setFillColor(Color(255, 0, 0));

    
    
    clock.restart();

    //initalisation des variables pour event
    sf::Event event;
    bool isFocusLost = false;
    std::string texte;

    Time currentMinuteur;
    Time lastTime;
    

    //
    //DRAW
    //
    while (window.isOpen())
    {
        while (window.pollEvent(event))
        {
            switch (event.type)
            {
            case (Event::LostFocus):
                lastTime += minuteur.getElapsedTime();
                isFocusLost = true;
                break;
            case(Event::GainedFocus):
                minuteur.restart();
                
                isFocusLost = false;
                break;
            case(Event::Closed):
                window.close();
                break;
            case(Event::TextEntered):
                if (event.text.unicode != '\b' && texte.size() <= 28) {
                    texte += event.text.unicode;
                    tdisp.setString(texte);
                }
                
                cout << texte << endl;
                break;
            case(Event::KeyPressed):
                if (event.key.code == Keyboard::Backspace) {
                    if (texte.size() > 0) {
                        texte.pop_back();
                        tdisp.setString(texte);
                        cout << texte << endl;
                    }
                }
                    
                break;
            default:
                break;
            }
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear(Color(52, 52, 52));
        
        for (int i = 0; i < shapes.size(); i++)
        {
            window.draw(shapes[i]);
        }
        
        if (!isFocusLost)
            currentMinuteur = minuteur.getElapsedTime() + lastTime;// - (lastTime - minuteur.getElapsedTime());
        //lastTime.Zero;
        
        text.setString(to_string(currentMinuteur.asMilliseconds()));
        window.draw(text);
        window.draw(tdisp);
                   
        for (int i = 0; i < boules.size(); i++)
        {
            window.draw(boules[i].projection);
        }
        Time elapsed1 = clock.getElapsedTime();
        Time max = sf::milliseconds(10);
        Time microsec = microseconds(elapsed1.asMicroseconds());
        
            
        
        if (!isFocusLost) {
            if (microsec >= max) {
                for (int i = 0; i < boules.size(); i++)
                {
                    boules[i].move();
                    for (int j = 0; j < boules.size(); j++) {
                        if (boules[i].isColliding(boules[j]) && i!=j) {

                            boules[i].projection.setFillColor(Color(randInRange(0,255), randInRange(0, 255), randInRange(0, 255)));
                            boules[j].projection.setFillColor(Color(randInRange(0,255), randInRange(0, 255), randInRange(0, 255)));


                            boules[i]._Vx = -boules[i]._Vx;
                            boules[i]._Vy = -boules[i]._Vy;
                            boules[j]._Vx = -boules[j]._Vx;
                            boules[j]._Vy = -boules[j]._Vy;

                            /*if (boules[i]._XP < 1 && boules[i]._XP >-1  && boules[i]._YP < 1 && boules[i]._YP > -1) {
                                boules[i]._Vx = randInRange(-5, 10);
                                boules[i]._Vy = randInRange(-5, 10);
                            }
                            if (boules[j]._XP < 1 && boules[j]._XP >-1 && boules[j]._YP < 1 && boules[j]._YP > -1) {
                                boules[j]._Vx = randInRange(-5, 10);
                                boules[j]._Vy = randInRange(-5, 10);
                            }*/
                        }
                    }
                }
            }
        }

        window.display();
        
        
    }
    return 0;
}