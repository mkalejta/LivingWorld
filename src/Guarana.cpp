#include "Guarana.h"
#include "Cow.h"
#include "Sheep.h"
#include <iostream>

Guarana::Guarana(Position pos) : Plant(2, pos) 
{
    setSpecies("G");
}

Guarana::Guarana(int power, Position pos) : Plant(power, pos) 
{
    setSpecies("G");
}

char Guarana::draw() const {
    return 'G';
}

void Guarana::action(World& world) {
    // np. brak ruchu
}

void Guarana::collision(Organism* other, World& world) {
    Cow* cow = dynamic_cast<Cow*>(other);
    Sheep* sheep = dynamic_cast<Sheep*>(other);

    if (cow || sheep) {
        other->setPower(other->getPower() + 3); // Zwiększ power o +3
        this->kill(); // Guarana zostaje zjedzona
    }
}

void Guarana::grow() {
    if (getPower() < 5) {
        if (rand() % 100 < 15) {
            setPower(getPower() + 1);
            std::cout << "Guarana has grown! New power: " << getPower() << std::endl;
        }
    }
}

void Guarana::serialize(fstream& file) const {
    Plant::serialize(file); // Wywołanie serializacji klasy bazowej
}

void Guarana::reproduce(World& world) {
    if (getPower() >= getPowerToReproduce()) {
        vector<Position> freePositions = world.getVectorOfFreePositionsAround(getPosition());
        if (!freePositions.empty()) {
            Position newPos = freePositions[rand() % freePositions.size()];
            int halfPower = getPower() / 2;
            setPower(halfPower);
            Guarana* offspring = new Guarana(halfPower, newPos);
            world.addOrganism(offspring);
        }
    }
}
