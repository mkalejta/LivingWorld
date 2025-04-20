#include "Grass.h"

Grass::Grass(Position pos) : Plant(0, pos) 
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
    // np. rozprzestrzenianie się
}

void Grass::collision(Organism* other) {
    // trawa nie walczy, zostaje zjedzona
    setPower(0);
}
