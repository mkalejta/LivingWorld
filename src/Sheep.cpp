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
    setBirthTurn(0);
}

Sheep::Sheep(int power, Position pos, int birthTurn) : Animal(power, pos, birthTurn) 
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

void Sheep::collision(Organism* other, World& world) {}

void Sheep::sound() const {
    std::cout << "Sheep sound!" << std::endl;
}

void Sheep::serialize(fstream& file) const {
    Organism::serialize(file); // Wywołanie serializacji klasy bazowej
}

void Sheep::reproduce(World& world, std::set<Organism*>& alreadyReproduced) {
    setPowerToReproduce(2);
    
    if (isJustBorn()) return;
    
    for (Organism* org : world.getOrganismsList()) {
        if (org != this && org->getSpecies() == "S" &&
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

                Sheep* offspring = new Sheep(*this);
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
