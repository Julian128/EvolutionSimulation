﻿#include <iostream>
#include <SFML/Graphics.hpp>
#include <cmath>
#include <time.h>
#include <vector>
#include <ctime>
#include <fstream>
#include "./src/helper.cpp"
#include "./src/settings.cpp"



using namespace sf;






class blobs : public CircleShape
{
public:

    std::vector<float> velocity = { 0, 0 };
    float reproduceCooldown;
    float attraction;
    float sight;
    float endurance;
    float age = 0;
    float maxAge;
    float gen = 0;

};


blobs heritage(blobs &a, blobs &b)
{
    blobs newBoi;

    newBoi.setRadius(a.getRadius() * 0.5 + b.getRadius() * 0.5);
    newBoi.setPosition(a.getPosition().x, a.getPosition().y);
    newBoi.setOrigin(newBoi.getRadius(), newBoi.getRadius());
    newBoi.velocity = { (a.velocity[0] + b.velocity[0]) / 2 + random(-0.2, 0.2), (a.velocity[1] + b.velocity[1]) / 2 + random(-0.1, 0.1) };
    newBoi.setFillColor(Color::Yellow);
    newBoi.reproduceCooldown = random(100, 200);
    newBoi.sight = bound((a.sight + b.sight) / 2 + random(-25, 25), 0, maxSight);
    newBoi.endurance = bound(((a.endurance + b.endurance) / 2 + random(-0.05, 0.05)), 0.75, 1.25);
    newBoi.gen = floor((a.gen + b.gen) / 2 + 1);
    newBoi.attraction = bound((a.attraction + b.attraction) / 2 + random(-0.02, 0.02), 0, 1);
    newBoi.maxAge = bound((a.maxAge + b.maxAge) / 2 + random(-6, 6), 200, maxAge);


    a.reproduceCooldown = random(50, 100);
    b.reproduceCooldown = random(50, 100);
    a.setRadius(a.getRadius() * 0.7);
    b.setRadius(b.getRadius() * 0.7);

    return newBoi;
}

int main()
{

    srand((unsigned)time(NULL));
    int framecounter = 0;

    RenderWindow window(VideoMode(width, height), "Evolution");
    window.setFramerateLimit(frameRate);

    std::vector<blobs> bois(population);
    std::vector<blobs> fruits;

    for (int i = 0; i < bois.size(); i++)
    {
        bois[i].setRadius(random(15, 20));
        bois[i].setPosition(random(0, width), random(0, height));
        bois[i].setOrigin(bois[i].getRadius(), bois[i].getRadius());
        bois[i].setFillColor(Color::Blue);

        bois[i].velocity = { random(-1, 1), random(-1, 1) };
        bois[i].reproduceCooldown = random(50, 100);
        bois[i].attraction = random(0, 1);
        bois[i].sight = random(0, maxSight);
        bois[i].endurance = random(0.75, 1.25);
        bois[i].maxAge = random(200, maxAge);
    }



    while (window.isOpen())
    {
        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
                window.close();
        }
        float num = random(0, 1);

        //WALL COLLISION
        for (int i = 0; i < bois.size(); i++)
        {
            if (bois[i].getPosition().x <= 10 || bois[i].getPosition().x >= width - 10)
            {
                bois[i].setPosition(bois[i].getPosition().x - bois[i].velocity[0], bois[i].getPosition().y - bois[i].velocity[1]);
                bois[i].velocity[0] = -bois[i].velocity[0];
            }
            if (bois[i].getPosition().y <= 10 || bois[i].getPosition().y >= height - 10)
            {
                bois[i].setPosition(bois[i].getPosition().x - bois[i].velocity[0], bois[i].getPosition().y - bois[i].velocity[1]);
                bois[i].velocity[1] = -bois[i].velocity[1];
            }
        }

        //SNAKE STYLE
        /*        if (bois[i].getPosition().x <= 10)
                {
                    bois[i].setPosition(bois[i].getPosition().x + width - 20, bois[i].getPosition().y);
                }
                if (bois[i].getPosition().x >= width - 10)
                {
                    bois[i].setPosition(bois[i].getPosition().x - width + 20, bois[i].getPosition().y);
                }
                if (bois[i].getPosition().y <= 10)
                {
                    bois[i].setPosition(bois[i].getPosition().x, bois[i].getPosition().y + height - 20);
                }
                if (bois[i].getPosition().y >= height - 10)
                {
                    bois[i].setPosition(bois[i].getPosition().x, bois[i].getPosition().y - height + 20);
                }
            }*/

        //BODY COLLISION
        //for (int i = 0; i < bois.size(); i++)
        //{
        //    for (int j = 0; j < bois.size(); j++)
        //    {
        //        if (i != j && pow(bois[i].getPosition().x - bois[j].getPosition().x, 2) + pow(bois[i].getPosition().y - bois[j].getPosition().y, 2) <= pow(bois[i].getRadius() + bois[j].getRadius(), 2))
        //        {
        //            //only one collision to happen
        //            bois[i].setPosition(bois[i].getPosition().x - 2*bois[i].velocity[0], bois[i].getPosition().y - 2*bois[i].velocity[1]);
        //            bois[j].setPosition(bois[j].getPosition().x - 2*bois[j].velocity[0], bois[j].getPosition().y - 2*bois[j].velocity[1]);

        //            double a = bois[i].velocity[0];
        //            double b = bois[j].velocity[0];
        //            double c = bois[i].velocity[1];
        //            double d = bois[j].velocity[1];
        //            bois[i].velocity[0] = b;
        //            bois[i].velocity[1] = a;
        //            bois[j].velocity[0] = d;
        //            bois[j].velocity[1] = c;
        //        }
        //    }
        //}

        //HERITAGE
        for (int i = 0; i < bois.size(); i++)
        {
            for (int j = 0; j < bois.size(); j++)
            {
                if (pow((bois[i].attraction * bois[j].attraction), 5) / 5 >= num)
                {
                    if (i != j && bois[i].reproduceCooldown <= 0 && bois[j].reproduceCooldown <= 0 && pow(bois[i].getPosition().x - bois[j].getPosition().x, 2) + pow(bois[i].getPosition().y - bois[j].getPosition().y, 2) <= pow(bois[i].getRadius() + bois[j].getRadius(), 2))
                    {
                        bornCounter++;
                        timeframeBorn++;
                        bois.push_back(heritage(bois[i], bois[j]));
                    }

                }
            }
        }

        //SPAWN FRUITS
        if (num > bound(fruitSpawnChance - sqrt(fruits.size()) * 0.003, 0.95, 0.99))
        {
            blobs newFruit;

            newFruit.setRadius(7);
            newFruit.setPosition(random(0, width), random(0, height));
            newFruit.setOrigin(7, 7);

            if (framecounter % 2 == 0)
                newFruit.setFillColor(Color::Green);
            else
                newFruit.setFillColor(Color::Black);

            fruits.push_back(newFruit);

        }


        //LOOKING FOR FOOD
            for (int i = 0; i < bois.size(); i++)
            {
                for (int j = 0; j < fruits.size(); j++)
                {
                    if (bois[i].getRadius() < 30 && pythagoras(bois[i].getPosition().x - fruits[j].getPosition().x, bois[i].getPosition().y - fruits[j].getPosition().y) < bois[i].sight)
                    {
                        float vel = sqrt(pow((bois[i].velocity[0]), 2) + pow((bois[i].velocity[1]), 2));
                        float dx = (fruits[j].getPosition().x - bois[i].getPosition().x);
                        float dy = (fruits[j].getPosition().y - bois[i].getPosition().y);
                        float distance = pythagoras(dx, dy);

                        bois[i].velocity[0] = dx / distance * vel;
                        bois[i].velocity[1] = dy / distance * vel;
                    }
                }
            }


        //EATING FRUIT & SLOW & COLOR CHANGE
        for (int i = 0; i < bois.size(); i++)
        {
            for (int j = 0; j < fruits.size(); j++)
            {
                if (pow(bois[i].getPosition().x - fruits[j].getPosition().x, 2) + pow(bois[i].getPosition().y - fruits[j].getPosition().y, 2) <= pow(bois[i].getRadius() + fruits[j].getRadius(), 2) && bois[i].getRadius() <= 30)
                {
                    fruits.erase(fruits.begin() + j);
                    {

                        if (bois[i].getRadius() >= 30)
                        {
                            bois[i].setRadius(bois[i].getRadius() + 0.1);
                            bois[i].setOrigin(bois[i].getRadius(), bois[i].getRadius());
                            bois[i].velocity[0] *= 0.995;
                            bois[i].velocity[1] *= 0.995;
                        }

                        else if (bois[i].getRadius() >= 20 && bois[i].getRadius() < 30)
                        {
                            bois[i].setRadius(bois[i].getRadius() + 1);
                            bois[i].setOrigin(bois[i].getRadius(), bois[i].getRadius());
                            bois[i].velocity[0] *= pow(0.995, 10);
                            bois[i].velocity[1] *= pow(0.995, 10);
                        }

                        else if (bois[i].getRadius() >= 10 && bois[i].getRadius() < 20)
                        {
                            bois[i].setRadius(bois[i].getRadius() + 2);
                            bois[i].setOrigin(bois[i].getRadius(), bois[i].getRadius());
                            bois[i].velocity[0] *= pow(0.995, 20);
                            bois[i].velocity[1] *= pow(0.995, 20);
                        }

                        else
                        {
                            bois[i].setRadius(bois[i].getRadius() + 3);
                            bois[i].setOrigin(bois[i].getRadius(), bois[i].getRadius());
                            bois[i].velocity[0] *= pow(0.995, 30);
                            bois[i].velocity[1] *= pow(0.995, 30);
                        }
                    }
                }
            }

            if(bois[i].reproduceCooldown <= 0)
                bois[i].setFillColor(Color::Magenta);
            else if(bois[i].reproduceCooldown < 100 && bois[i].reproduceCooldown > 0)
                bois[i].setFillColor(Color::Blue);
        }


        //AGE & HUNGER
        if (num > hungerChance)
        {
            for (int i = 0; i < bois.size(); i++)
            {
                bois[i].age++;
                bois[i].reproduceCooldown--;
                if (bois[i].age > bois[i].maxAge)
                {
                    bois.erase(bois.begin() + i);
                    std::cout << "death by age" << std::endl;
                    deathAge++;
                    deathCounter++;
                    timeframeDeath++;
                    i--;
                }
            }

            for (int i = 0; i < bois.size(); i++)
            {


                if (bois[i].getRadius() > 0)
                {
                    bois[i].setRadius(bois[i].getRadius() - 0.1 * bois[i].endurance * pythagoras(bois[i].velocity[0], bois[i].velocity[1]));
                    bois[i].velocity[0] *= 1 / 0.995;
                    bois[i].velocity[1] *= 1 / 0.995;
                }
                else
                {
                    bois.erase(bois.begin() + i);
                    std::cout << "death by hunger" << std::endl;
                    deathHunger++;
                    deathCounter++;
                    timeframeDeath++;
                    i--;

                }

            }
        }

        if (framecounter % 10000 == 0)
        {
            timeframeDeath = 0;
            timeframeBorn = 0;

        }


        //SCOREBOARD & SAVING DATA
        if (framecounter % 500 == 0)
        {
            float avgGen = 0;
            float avgAge = 0;
            float avgVel = 0;
            float avgSight = 0;
            float avgEndurance = 0;
            float reproductionRate = 0;
            float avgAttraction = 0;
            float avgMaxAge = 0;

            for (int i = 0; i < bois.size(); i++)
            {

                avgGen += bois[i].gen;
                avgAge += bois[i].age;
                avgVel += sqrt(pow((bois[i].velocity[0]), 2) + pow((bois[i].velocity[1]), 2));              
                avgSight += bois[i].sight;
                avgEndurance += bois[i].endurance;
                avgAttraction += bois[i].attraction;
                avgMaxAge += bois[i].maxAge;
            }

            if (timeframeDeath == 0)
                reproductionRate = timeframeBorn;
            else
                reproductionRate = timeframeBorn / timeframeDeath;


            std::cout << "Population Count: " << bois.size() << std::endl;
            std::cout << "Average Velocity: " << avgVel / bois.size() << std::endl;
            std::cout << "Average Sight: " << avgSight / bois.size() << std::endl;
            std::cout << "Average Endurance: " << avgEndurance / bois.size() << std::endl;
            std::cout << "Total Newborns: " << bornCounter << std::endl;
            std::cout << "Total Deaths: " << deathCounter << std::endl;
            std::cout << "Average Age: " << avgAge / bois.size() << std::endl;
            std::cout << "Average Gen: " << avgGen / bois.size() << std::endl;
            std::cout << "Reproduction Rate: " << reproductionRate << std::endl;
            std::cout << "Average Attraction: " << avgAttraction / bois.size() << std::endl;
            std::cout << "Average maxAge: " << avgMaxAge / bois.size() << std::endl;
            std::cout << "deathAge / deathHunger: " << deathAge / deathHunger << std::endl << std::endl;

            std::ofstream log;
            log.open(logname, std::fstream::app);

            log << bois.size() << "," << avgVel / bois.size() << "," << avgSight / bois.size() << "," << avgEndurance / bois.size() << "," << avgAge / bois.size() << "," << avgGen / bois.size() << "," << reproductionRate << "," << avgAttraction / bois.size() << "," << fruits.size() << "," << "\n";


        }


        //MOUSECLICKS
        //for (int i = 0; i < bois.size(); i++)
        //{
        //    if (Mouse::isButtonPressed(Mouse::Left) && sqrt(pow(bois[i].getPosition().x - Mouse::getPosition(window).x, 2) + pow(bois[i].getPosition().y - Mouse::getPosition(window).y, 2)) <= 50)
        //    {
        //        std::cout << "boi: " << i << std::endl;
        //        Sleep(1);
        //    }
        //}


        //MOVE
        for (int i = 0; i < bois.size(); i++)
            bois[i].move(bois[i].velocity[0], bois[i].velocity[1]);


        framecounter++;

        //DRAW
        if (draw == true)
        {
            window.clear(Color(100, 100, 100));

            for (int i = 0; i < bois.size(); i++)
                window.draw(bois[i]);
            for (int i = 0; i < fruits.size(); i++)
                window.draw(fruits[i]);

            window.display();

        }
    }


}