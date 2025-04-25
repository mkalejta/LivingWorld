#include "Guarana.h"
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

void Guarana::action() {
    // np. brak ruchu
}

void Guarana::collision(Organism* other) {
    // Guarana zwiększa siłę organizmu który ją "zjada"
    other->setPower(other->getPower() + 1);
    this->kill();
}

void Guarana::grow() {
    if (getPower() < 5) {
        if (rand() % 100 < 15) {
            setPower(getPower() + 1);
            std::cout << "Guarana has grown! New power: " << getPower() << std::endl;
        }
    }
}