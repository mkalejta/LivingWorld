#include "../include/Sheep.h"
#include "../include/Plant.h"
#include "../include/Wolf.h"
#include "../include/Guarana.h"
#include "../include/Grass.h"
#include <iostream>
#include <cstdlib>

Sheep::Sheep(Position pos) : Animal(4, pos) 
{
    setSpecies("S");
}

Sheep::Sheep(int power, Position pos) : Animal(power, pos) 
{
    setSpecies("S");
}

char Sheep::draw() const {
    return 'S';
}

void Sheep::action(World& world) {
    int dx = (rand() % 3) - 1; // Losowy ruch w zakresie -1, 0, 1
    int dy = (rand() % 3) - 1;

    Position newPos = getPosition();
    newPos.move(dx, dy);

    // Sprawdź, czy nowa pozycja jest w granicach świata
    if (world.isPositionOnWorld(newPos.getX(), newPos.getY())) {
        setPosition(newPos);
    }
}

void Sheep::collision(Organism* other, World& world) {
    Grass* grass = dynamic_cast<Grass*>(other);
    if (grass) {
        grass->kill(); // Grass zostaje zjedzony
        setPower(getPower() + 1); // Sheep zyskuje +1 do power
        return;
    }

    Guarana* guarana = dynamic_cast<Guarana*>(other);
    if (guarana) {
        guarana->kill(); // Guarana zostaje zjedzona
        setPower(getPower() + 3); // Sheep zyskuje +3 do power
        return;
    }

    if (other->isPredator()) {
        this->kill(); // Sheep zostaje zabita przez drapieżnika
    }
}

void Sheep::sound() const {
    std::cout << "Sheep sound!" << std::endl;
}

void Sheep::serialize(fstream& file) const {
    Organism::serialize(file); // Wywołanie serializacji klasy bazowej
}

void Sheep::reproduce(World& world) {
    if (getPower() >= getPowerToReproduce()) {
        vector<Position> freePositions = world.getVectorOfFreePositionsAround(getPosition());
        if (!freePositions.empty()) {
            Position newPos = freePositions[rand() % freePositions.size()];
            Sheep* offspring = new Sheep(*this); // Użycie konstruktora kopiującego
            offspring->setPosition(newPos);
            offspring->setPower(getPower() / 2); // Ustawienie połowy siły
            setPower(getPower() / 2); // Rodzic traci połowę siły
            world.addOrganism(offspring);
        }
    }
}
