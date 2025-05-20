#include "../include/Grass.h"
#include "../include/Cow.h"
#include "../include/Sheep.h"
#include <iostream>

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

void Grass::action(World& world) {
    // np. brak ruchu
}

void Grass::collision(Organism* other, World& world) {
    Cow* cow = dynamic_cast<Cow*>(other);
    Sheep* sheep = dynamic_cast<Sheep*>(other);

    if (cow || sheep) {
        this->kill(); // Grass zostaje zjedzony
    }
}

void Grass::grow() {
    if (getPower() < 5) {
        if (rand() % 100 < 15) {
            std::cout << "Grass has grown!" << std::endl;
        }
    }
}

void Grass::serialize(fstream& file) const {
    Plant::serialize(file); // Wywołanie serializacji klasy bazowej
}

void Grass::reproduce(World& world) {
    vector<Position> free = world.getVectorOfFreePositionsAround(getPosition());
    if (!free.empty()) {
        Position newPos = free[rand() % free.size()];
        int halfPower = getPower() / 2;
        setPower(halfPower);
        Grass* offspring = new Grass(halfPower, newPos);
        world.addOrganism(offspring);
    }
}
