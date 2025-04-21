#include "../include/Cow.h"
#include "../include/Plant.h"

Cow::Cow(Position pos) : Animal(6, pos)
{
    setSpecies("C");
}

Cow::Cow(int power, Position pos) : Animal(power, pos)
{
    setSpecies("C");
}

char Cow::draw() const {
    return 'C';
}

void Cow::action() {
    move(-1, 0); // przykładowy ruch    
}

void Cow::collision(Organism* other) {
    Plant* plant = dynamic_cast<Plant*>(other);
    if (plant && other->getPower() < this->getPower()) {
        other->kill();
    }
}
