/*

#include <iostream>
#include <SFML/Graphics.hpp>
#include <cmath>
#include <time.h>
#include <vector>
#include <ctime>
#include <Windows.h>
using namespace sf;

float random(float Min, float Max)
{
    return ((float(rand()) / float(RAND_MAX)) * (Max - Min)) + Min;
}

float width = 2560 * 1;
float height = 1440 * 1;


class cre : public CircleShape
{
public:

    std::vector<float> velocity = { 0, 0 };
    float reproduceCooldown;
    int tribe_;
};


std::vector<cre> tribe(int num, std::vector<cre> vec)
{
    switch (num)
    {
    case 1:
    {
        for (int i = 0; i < vec.size(); i++)
        {
            vec[i].tribe_ = 1;
            vec[i].setRadius(random(18, 20));
            vec[i].setOrigin(vec[i].getRadius() + vec[i].getPosition().x, vec[i].getRadius() + vec[i].getPosition().y);
            vec[i].setPosition(random(5, width / 4), random(5, height / 4));
            vec[i].velocity = { random(-0.5, 0.5), random(-0.5, 0.5) };
            vec[i].setFillColor(Color::Blue);
            vec[i].reproduceCooldown = 100;

        }
        break;
    }
    case 2:
    {
        for (int i = 0; i < vec.size(); i++)
        {
            vec[i].tribe_ = 2;
            vec[i].setRadius(random(16, 18));
            vec[i].setOrigin(vec[i].getRadius(), vec[i].getRadius());
            vec[i].setPosition(random(width * 3 / 4, width - 5), random(5, height / 4));
            vec[i].velocity = { random(-0.75, 0.75), random(-0.75, 0.75) };
            vec[i].setFillColor(Color::Red);
            vec[i].reproduceCooldown = 90;
        }
        break;
    }
    case 3:
    {
        for (int i = 0; i < vec.size(); i++)
        {
            vec[i].tribe_ = 3;
            vec[i].setRadius(random(14, 16));
            vec[i].setOrigin(vec[i].getRadius(), vec[i].getRadius());
            vec[i].setPosition(random(5, width / 4), random(height * 3 / 4, height - 5));
            vec[i].velocity = { random(-1, 1), random(-1, 1) };
            vec[i].setFillColor(Color::Yellow);
            vec[i].reproduceCooldown = 80;
        }
        break;
    }
    case 4:
    {
        for (int i = 0; i < vec.size(); i++)
        {
            vec[i].tribe_ = 4;
            vec[i].setRadius(random(12, 14));
            vec[i].setOrigin(vec[i].getRadius(), vec[i].getRadius());
            vec[i].setPosition(random(width * 3 / 4, width - 5), random(height * 3 / 4, height - 5));
            vec[i].velocity = { random(-1.25, 1.25), random(-1.25, 1.25) };
            vec[i].setFillColor(Color::Magenta);
            vec[i].reproduceCooldown = 70;
        }
        break;
    }
    }
    return vec;
}


std::vector<cre> heritageTribe(int tri, std::vector<cre> vec, float rad, float x, float y, float vX1, float vX2, float vY1, float vY2, float cd1, float cd2)
{
    for (int i = 0; i < vec.size(); i++)
    {
        vec[i].tribe_ = tri;
        vec[i].setRadius(rad);
        vec[i].setOrigin(rad, rad);
        vec[i].setPosition(x, y);
        //vec[i].velocity = { vX, vY };
        //vec[i].setFillColor(color);
        //vec[i].reproduceCooldown = cd;
    }
    return vec;
}

int not_main()
{

    srand((unsigned)time(NULL));
    int framecounter = 0;

    RenderWindow window(VideoMode(width, height), "Evolution");
    window.setFramerateLimit(1000);

    std::vector<cre> base(10);
    std::vector<cre> baseSingle(1);

    std::vector<cre> boisA = tribe(1, base);
    std::vector<cre> boisB = tribe(2, base);
    std::vector<cre> boisC = tribe(3, base);
    std::vector<cre> boisD = tribe(4, base);
    boisA.insert(std::end(boisA), std::begin(boisB), std::end(boisB));
    boisA.insert(std::end(boisA), std::begin(boisC), std::end(boisC));
    boisA.insert(std::end(boisA), std::begin(boisD), std::end(boisD));
    std::vector<cre> bois = boisA;

    std::vector<cre> fruits(1);


    while (window.isOpen())
    {
        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
                window.close();
        }

        //WALL COLLISION
        for (int i = 0; i < bois.size(); i++)
        {
            if (bois[i].getPosition().x <= 10 || bois[i].getPosition().x >= width - 10) {
                bois[i].setPosition(bois[i].getPosition().x - bois[i].velocity[0], bois[i].getPosition().y - bois[i].velocity[1]);
                bois[i].velocity[0] = -bois[i].velocity[0];
            }
            if (bois[i].getPosition().y <= 10 || bois[i].getPosition().y >= height - 10) {
                bois[i].setPosition(bois[i].getPosition().x - bois[i].velocity[0], bois[i].getPosition().y - bois[i].velocity[1]);
                bois[i].velocity[1] = -bois[i].velocity[1];
            }

        }

        //HERITAGE
        //for (int i = 0; i < bois.size(); i++)
        //{
        //    for (int j = 0; j < bois.size(); j++)
        //    {
        //        if (i != j && bois[i].reproduceCooldown <= 0 && bois[j].reproduceCooldown <= 0 && bois[i].getFillColor() == bois[j].getFillColor() && pow(bois[i].getPosition().x - bois[j].getPosition().x, 2) + pow(bois[i].getPosition().y - bois[j].getPosition().y, 2) <= pow(bois[i].getRadius() + bois[j].getRadius(), 2))
        //        {

        //            //std::vector<cre> child = customTribe(bois[i].tribe_, baseSingle, (bois[i].getRadius() + bois[j].getRadius()) / 2); //FINISH FUNCTION INPUT VAR

        //            bois.push_back()

        //                //bois.insert(std::end(bois), std::begin(child), std::end(child));
        //                //bois[i].reproduceCooldown += random(50, 100);
        //                //bois[j].reproduceCooldown += random(50, 100);
        //                //bois[i].setRadius(bois[i].getRadius() * 0.7);
        //                //bois[j].setRadius(bois[j].getRadius() * 0.7);
        //                //std::cout << "New child!" << std::endl;


        //        }
        //    }
        //}
        //EATING FRUIT
        for (int i = 0; i < bois.size(); i++)
        {
            for (int j = 0; j < fruits.size(); j++)
            {
                if (pow(bois[i].getPosition().x - fruits[j].getPosition().x, 2) + pow(bois[i].getPosition().y - fruits[j].getPosition().y, 2) <= pow(bois[i].getRadius() + fruits[j].getRadius(), 2) && bois[i].getRadius() <= 30)
                {
                    fruits.erase(fruits.begin() + j);
                    if (bois[i].getRadius() >= 20)
                    {
                        bois[i].setRadius(bois[i].getRadius() + 1);
                        bois[i].setOrigin(bois[i].getRadius(), bois[i].getRadius());
                    }

                    else if (bois[i].getRadius() >= 10 && bois[i].getRadius() < 20)
                    {
                        bois[i].setRadius(bois[i].getRadius() + 2);
                        bois[i].setOrigin(bois[i].getRadius(), bois[i].getRadius());
                    }

                    else
                    {
                        bois[i].setRadius(bois[i].getRadius() + 3);
                        bois[i].setOrigin(bois[i].getRadius(), bois[i].getRadius());
                    }
                }
            }
        }

        //SPAWN FRUITS
        float num = random(0, 1);

        if (num > 0.99)
        {
            fruits.push_back(cre());

            fruits[fruits.size() - 1].setRadius(7);
            fruits[fruits.size() - 1].setPosition(random(0, width), random(0, height));
            fruits[fruits.size() - 1].setFillColor(Color::Green);
        }

        //HUNGER
        if (num > 0.995)

            for (int i = 0; i < bois.size(); i++)
            {
                bois[i].reproduceCooldown--;

                if (bois[i].getRadius() > 0)
                    bois[i].setRadius(bois[i].getRadius() - 0.1);
                else
                {
                    bois.erase(bois.begin() + i);
                    std::cout << "death" << std::endl;

                }
            }

        //SCOREBOARD
        if (framecounter % 5000 == 0)
        {
            int a = 0;
            int b = 0;
            int c = 0;
            int d = 0;
            for (int i = 0; i < bois.size(); i++)
            {
                if (bois[i].tribe_ == 1)
                    a++;
                else if (bois[i].tribe_ == 2)
                    b++;
                else if (bois[i].tribe_ == 3)
                    c++;
                else
                    d++;
            }
            std::cout << "Blue alive: " << a << std::endl;
            std::cout << "Red alive: " << b << std::endl;
            std::cout << "Yellow alive: " << c << std::endl;
            std::cout << "Magenta alive: " << d << std::endl << std::endl;

            a = 0;
            b = 0;
            c = 0;
            d = 0;

        }

        //MOVE
        for (int i = 0; i < bois.size(); i++)
            bois[i].move(bois[i].velocity[0], bois[i].velocity[1]);

        //DRAW
        window.clear(Color(100, 100, 100));

        for (int i = 0; i < bois.size(); i++)
            window.draw(bois[i]);
        for (int i = 0; i < fruits.size(); i++)
            window.draw(fruits[i]);

        window.display();

        framecounter++;
    }

    return 0;

}
*/