#include "../include/Grass.h"
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

void Grass::action() {
    // np. brak ruchu
}

void Grass::collision(Organism* other) {
    this->kill(); // trawa zostaje zjedzona
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

