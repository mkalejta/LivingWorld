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

void Guarana::grow(World& world) {
    // 10% szans na rozprzestrzenienie się na wolne pole obok
    if (rand() % 100 < 10) {
        vector<Position> free = world.getVectorOfFreePositionsAround(getPosition());
        if (!free.empty()) {
            Position newPos = free[rand() % free.size()];
            Guarana* offspring = new Guarana(2, newPos);
            world.addOrganism(offspring);
        }
    }
}

void Guarana::serialize(fstream& file) const {
    Plant::serialize(file); // Wywołanie serializacji klasy bazowej
}
