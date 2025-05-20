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

void Toadstool::grow() {
    // Muchomor nie rośnie
}

void Toadstool::reproduce(World& world) {
    if (getPower() >= getPowerToReproduce()) {
        vector<Position> freePositions = world.getVectorOfFreePositionsAround(getPosition());
        if (!freePositions.empty()) {
            Position newPos = freePositions[rand() % freePositions.size()];
            int halfPower = getPower() / 2;
            setPower(halfPower);
            Toadstool* offspring = new Toadstool(halfPower, newPos);
            world.addOrganism(offspring);
        }
    }
}

void Toadstool::serialize(fstream& file) const {
    Plant::serialize(file);
}