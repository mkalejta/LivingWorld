#include "../include/Sheep.h"
#include "../include/Plant.h"
#include "../include/Wolf.h"

Sheep::Sheep(Position pos) : Animal(4, pos) 
{
    setSpecies("S");
}

Sheep::Sheep(int power, Position pos) : Animal(power, pos) 
{
    setSpecies("S");
}

char Sheep::draw() const {
    return 'S';
}

void Sheep::action() {
    move(0, 1); // przykładowy ruch
}

void Sheep::collision(Organism* other) {
    Plant* plant = dynamic_cast<Plant*>(other);
    if (plant && other->getPower() < this->getPower()) {
        other->kill();
    }

    if (other->isPredator()) {
        this->kill();
    }    
}
