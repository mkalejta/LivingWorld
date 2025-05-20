#include "../include/Toadstool.h"
#include <iostream>

Toadstool::Toadstool(Position pos) : Plant(3, pos)
{
    setSpecies("T");
}

Toadstool::Toadstool(int power, Position pos) : Plant(power, pos)
{
    setSpecies("T");
}

char Toadstool::draw() const {
    return 'T';
}

void Toadstool::action(World& world) {
    // Muchomor nie wykonuje ruchu
}

void Toadstool::collision(Organism* other, World& world) {
    // Zabija organizm, który go zje
    other->kill();
    this->kill();
}

void Toadstool::grow(World& world) {
    // 5% szans na rozprzestrzenienie się na wolne pole obok
    if (rand() % 100 < 5) {
        vector<Position> free = world.getVectorOfFreePositionsAround(getPosition());
        if (!free.empty()) {
            Position newPos = free[rand() % free.size()];
            Toadstool* offspring = new Toadstool(3, newPos);
            world.addOrganism(offspring);
        }
    }
}

void Toadstool::serialize(fstream& file) const {
    Plant::serialize(file);
}