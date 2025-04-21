#include "Guarana.h"

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
    setPower(0); // Guarana ginie
}
