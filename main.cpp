#include <iostream>
#include <SFML/Graphics.hpp>
#include <cmath>
#include <time.h>
using namespace sf;

int main()
{
    int width = 2560;
    int height = 1300;

    RenderWindow window(VideoMode(width, height), "Stat Mechanics");
    window.setFramerateLimit(30);

int num_particles = 100;

std::vector<CircleShape> particles(0);
std::vector<double> vel_x(0);
std::vector<double> vel_y(0);

int size = 10;

CircleShape particle(size);
particle.setOrigin(size, size);


//RANDOMIZE
srand((unsigned)time(NULL));

for (int i = 0; i < num_particles; i++)
{
    //particle.setRadius(20);
    particle.setPosition(rand() % width, rand() % height);

    if (i % 2 == 0)
        particle.setFillColor(Color::Green);
    else
        particle.setFillColor(Color::Red);
    particles.push_back(CircleShape(particle));
}

for (int i = 0; i < num_particles / 2; i++)
{
    vel_x.push_back((float)rand() / RAND_MAX);
    vel_y.push_back((float)rand() / RAND_MAX);
}
for (int i = 0; i < num_particles / 2 - 1 / 2; i++)
{
    vel_x.push_back(-(float)rand() / RAND_MAX);
    vel_y.push_back(-(float)rand() / RAND_MAX);
}

int counter = 0;

while (window.isOpen())
{
    Event event;
    while (window.pollEvent(event))
    {
        if (event.type == Event::Closed)
            window.close();
    }

    //COLLISION
    for (int i = 0; i < particles.size(); i++)
    {
        if (particles[i].getPosition().x <= 10 || particles[i].getPosition().x >= width - 10) {
            particles[i].setPosition(particles[i].getPosition().x - vel_x[i], particles[i].getPosition().y - vel_y[i]);
            vel_x[i] = -vel_x[i];
        }
        if (particles[i].getPosition().y <= 10 || particles[i].getPosition().y >= height - 10) {
            particles[i].setPosition(particles[i].getPosition().x - vel_x[i], particles[i].getPosition().y - vel_y[i]);
            vel_y[i] = -vel_y[i];
        }

    }

    for (int i = 0; i < particles.size(); i++)
    {
        for (int j = 0; j < particles.size(); j++)
        {
            if (i != j && pow(particles[i].getPosition().x - particles[j].getPosition().x, 2) + pow(particles[i].getPosition().y - particles[j].getPosition().y, 2) <= pow(particles[i].getRadius() + particles[j].getRadius(), 2))
            {
                //only one collision to happen
                particles[i].setPosition(particles[i].getPosition().x - vel_x[i], particles[i].getPosition().y - vel_y[i]);
                particles[j].setPosition(particles[j].getPosition().x - vel_x[j], particles[j].getPosition().y - vel_y[j]);

                double a = vel_x[i];
                double b = vel_x[j];
                double c = vel_y[i];
                double d = vel_y[j];
                vel_x[i] = b;
                vel_x[j] = a;
                vel_y[i] = d;
                vel_y[j] = c;
                counter++;
                //std::cout << counter << std::endl;
            }
        }
    }
    //TEMP
    double ave_vel = 0;

    for (int i = 0; i < particles.size(); i++)
    {
    ave_vel = ave_vel + pow(vel_x[i] * vel_x[i] + vel_y[i] * vel_y[i], 0.5);

    }
    ave_vel = ave_vel / particles.size();

    double temp = 16 * 1.661e-27 * ave_vel * ave_vel / (3 * 1.38e-23);
    //std::cout << temp << std::endl;

    if (Keyboard::isKeyPressed(Keyboard::Up))
    {
        for (int i = 0; i < particles.size(); i++)
        {
            vel_x[i] = vel_x[i] * 1.01;
            vel_y[i] = vel_y[i] * 1.01;


        }
        std::cout << temp << std::endl;
    }

    if (Keyboard::isKeyPressed(Keyboard::Down))
    {
        for (int i = 0; i < particles.size(); i++)
        {
            vel_x[i] = vel_x[i] / 1.01;
            vel_y[i] = vel_y[i] / 1.01;


        }
        std::cout << temp << std::endl;
    }


    //GRAVITY
    if (Keyboard::isKeyPressed(Keyboard::G))
    {
        for (int i = 0; i < particles.size(); i++)
        {
            vel_y[i] = vel_y[i] ++;


        }
        std::cout << temp << std::endl;
    }


    //MOVE
    for (int i = 0; i < particles.size(); i++)
    {
        particles[i].move(vel_x[i], vel_y[i]);
    }


    //DRAW
    window.clear(Color(100, 100, 100));

    for (int i = 0; i < particles.size(); i++)
    {
        window.draw(particles[i]);


    }


    window.display();


    }
}