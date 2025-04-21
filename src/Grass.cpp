#include "../include/Grass.h"

Grass::Grass(Position pos) : Plant(1, pos) 
{
    setSpecies("g");
}

Grass::Grass(int power, Position pos) : Plant(power, pos) 
{
    setSpecies("g");
}

char Grass::draw() const {
    return 'g';
}

void Grass::action() {
    // np. brak ruchu
}

void Grass::collision(Organism* other) {
    this->kill(); // trawa zostaje zjedzona
}
