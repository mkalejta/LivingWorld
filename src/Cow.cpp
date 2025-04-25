#include "../include/Cow.h"
#include "../include/Plant.h"
#include "../include/Wolf.h"
#include <iostream>

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

    if (other->isPredator()) {
        this->kill();
    }    
}

void Cow::sound() const {
    std::cout << "Cow sound!" << std::endl;
}

void Cow::serialize(fstream& file) const {
    Organism::serialize(file); // Wywołanie serializacji klasy bazowej
}

void Cow::deserialize(fstream& file) {
    Organism::deserialize(file); // Wywołanie deserializacji klasy bazowej
}