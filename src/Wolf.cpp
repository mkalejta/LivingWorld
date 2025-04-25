#include "../include/Wolf.h"
#include <iostream>

Wolf::Wolf(Position pos) : Animal(10, pos) 
{
    setSpecies("W");
}

Wolf::Wolf(int power, Position pos) : Animal(power, pos) 
{
    setSpecies("W");
}

char Wolf::draw() const {
    return 'W';
}

void Wolf::action() {
    move(1, 0); // przykładowy ruch
}

void Wolf::collision(Organism* other) {
    Animal* animal = dynamic_cast<Animal*>(other);
    std::cout << animal->getPower() << std::endl;
    std::cout << this->getPower() << std::endl;
    std::cout << animal << std::endl;
    if (animal && other->getPower() < this->getPower()) {
        // zjada inne zwierzęta słabsze od siebie
        other->kill();
    }
}

bool Wolf::isPredator() const {
    return true;
}

void Wolf::sound() const {
    std::cout << "Wolf sound!" << std::endl;
}
