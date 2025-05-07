#include "../include/Wolf.h"
#include "../include/Cow.h"
#include "../include/Sheep.h"
#include <iostream>
#include <cstdlib>

Wolf::Wolf(Position pos) : Animal(10, pos) 
{
    setSpecies("W");
}

Wolf::Wolf(int power, Position pos) : Animal(power, pos) 
{
    setSpecies("W");
}

char Wolf::draw() const {
    return 'W';
}

void Wolf::action(World& world) {
    int dx = (rand() % 3) - 1; // Losowy ruch w zakresie -1, 0, 1
    int dy = (rand() % 3) - 1;

    // Skalowanie ruchu do 2 pól
    dx *= 2;
    dy *= 2;

    Position newPos = getPosition();
    newPos.move(dx, dy);

    // Sprawdź, czy nowa pozycja jest w granicach świata
    if (world.isPositionOnWorld(newPos.getX(), newPos.getY())) {
        setPosition(newPos);
    }
}

void Wolf::collision(Organism* other, World& world) {
    Cow* cow = dynamic_cast<Cow*>(other);
    Sheep* sheep = dynamic_cast<Sheep*>(other);

    if ((cow || sheep) && other->getPower() < this->getPower()) {
        other->kill(); // Wolf zjada Cow lub Sheep
        setPower(getPower() + 2); // Wolf zyskuje +2 do power
        return;
    }

    if (other->getPower() > this->getPower()) {
        this->kill(); // Wolf zostaje zabity przez silniejszy organizm
    }
}

bool Wolf::isPredator() const {
    return true;
}

void Wolf::sound() const {
    std::cout << "Wolf sound!" << std::endl;
}

void Wolf::serialize(fstream& file) const {
    Organism::serialize(file); // Wywołanie serializacji klasy bazowej
}

void Wolf::reproduce(World& world) {
    if (getPower() >= getPowerToReproduce()) {
        vector<Position> freePositions = world.getVectorOfFreePositionsAround(getPosition());
        if (!freePositions.empty()) {
            Position newPos = freePositions[rand() % freePositions.size()];
            Wolf* offspring = new Wolf(*this); // Użycie konstruktora kopiującego
            offspring->setPosition(newPos);
            offspring->setPower(getPower() / 2); // Ustawienie połowy siły
            setPower(getPower() / 2); // Rodzic traci połowę siły
            world.addOrganism(offspring);
        }
    }
}
