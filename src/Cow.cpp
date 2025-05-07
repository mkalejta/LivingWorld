#include "../include/Cow.h"
#include "../include/Plant.h"
#include "../include/Wolf.h"
#include "../include/Guarana.h"
#include "../include/Grass.h"
#include <iostream>
#include <cstdlib>

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

void Cow::action(World& world) {
    int dx = (rand() % 3) - 1; // Losowy ruch w zakresie -1, 0, 1
    int dy = (rand() % 3) - 1;

    Position newPos = getPosition();
    newPos.move(dx, dy);

    // Sprawdź, czy nowa pozycja jest w granicach świata
    if (world.isPositionOnWorld(newPos.getX(), newPos.getY())) {
        setPosition(newPos);
    }
}

void Cow::collision(Organism* other, World& world) {
    Grass* grass = dynamic_cast<Grass*>(other);
    if (grass) {
        grass->kill(); // Grass zostaje zjedzony
        setPower(getPower() + 1); // Cow zyskuje +1 do power
        return;
    }

    Guarana* guarana = dynamic_cast<Guarana*>(other);
    if (guarana) {
        guarana->kill(); // Guarana zostaje zjedzona
        setPower(getPower() + 3); // Cow zyskuje +3 do power
        return;
    }

    if (other->isPredator()) {
        this->kill(); // Cow zostaje zabita przez drapieżnika
    }
}

void Cow::sound() const {
    std::cout << "Cow sound!" << std::endl;
}

void Cow::serialize(fstream& file) const {
    Organism::serialize(file); // Wywołanie serializacji klasy bazowej
}

void Cow::reproduce(World& world) {
    if (getPower() >= getPowerToReproduce()) {
        vector<Position> freePositions = world.getVectorOfFreePositionsAround(getPosition());
        if (!freePositions.empty()) {
            Position newPos = freePositions[rand() % freePositions.size()];
            Cow* offspring = new Cow(*this); // Użycie konstruktora kopiującego
            offspring->setPosition(newPos);
            offspring->setPower(getPower() / 2); // Ustawienie połowy siły
            setPower(getPower() / 2); // Rodzic traci połowę siły
            world.addOrganism(offspring);
        }
    }
}

