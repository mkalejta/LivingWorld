#include "../include/Cow.h"
#include "../include/Plant.h"
#include "../include/Wolf.h"
#include "../include/Guarana.h"
#include "../include/Grass.h"
#include <iostream>
#include <cstdlib>
#include <set>

Cow::Cow(Position pos) : Animal(6, pos)
{
    setSpecies("C");
    setBirthTurn(0);
}

Cow::Cow(int power, Position pos, int birthTurn) : Animal(power, pos, birthTurn)
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

void Cow::collision(Organism* other, World& world) {}

void Cow::sound() const {
    std::cout << "Cow sound!" << std::endl;
}

void Cow::serialize(fstream& file) const {
    Organism::serialize(file); // Wywołanie serializacji klasy bazowej
}

void Cow::reproduce(World& world, std::set<Organism*>& alreadyReproduced) {
    setPowerToReproduce(3);

    for (Organism* org : world.getOrganismsList()) {
        if (org != this && org->getSpecies() == "C" &&
            getPosition().distance(org->getPosition()) == 1.0 &&
            alreadyReproduced.find(org) == alreadyReproduced.end()) {

            if (getPower() < getPowerToReproduce() || org->getPower() < org->getPowerToReproduce())
                continue;

            vector<Position> free = world.getVectorOfFreePositionsAround(getPosition());
            if (!free.empty()) {
                int halfPower1 = getPower() / 2;
                int halfPower2 = org->getPower() / 2;
                setPower(halfPower1);
                org->setPower(halfPower2);

                Cow* offspring = new Cow(*this);
                Position newPos = free[rand() % free.size()];
                offspring->setPosition(newPos);
                offspring->setBirthTurn(world.getCurrentTurn());

                offspring->setAncestors(this->getAncestors());
                offspring->addAncestor(this->getBirthTurn(), this->getDeathTurn(), this);
                offspring->addAncestor(org->getBirthTurn(), org->getDeathTurn(), org);


                world.addOrganism(offspring);

                alreadyReproduced.insert(this);
                alreadyReproduced.insert(org);
            }
            break;
        }
    }
}

