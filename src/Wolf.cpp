#include "../include/Wolf.h"

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
    if (animal && other->getPower() < this->getPower()) {
        // zjada inne zwierzęta słabsze od siebie
        other->setPower(0);
    }
}
