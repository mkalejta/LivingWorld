#include "../include/Organism.h"
#include <iostream>

Organism::Organism(int power, Position position)
{
    setPower(power);
    setPosition(position);
    setSpecies("O");
}

Organism::Organism(const Organism& other)
    : power(other.power),
      position(other.position),
      species(other.species),
      initiative(other.initiative),
      powerToReproduce(other.powerToReproduce),
      ancestors(other.ancestors),
      alive(other.alive) {}

Organism::Organism(Organism&& other) noexcept
    : power(std::move(other.power)), position(std::move(other.position)),
      species(std::move(other.species)),
      initiative(std::move(other.initiative)),
      powerToReproduce(std::move(other.powerToReproduce)),
      ancestors(std::move(other.ancestors)),
      alive(std::move(other.alive)) {}

Organism& Organism::operator=(const Organism& other) {
    if (this != &other) {
        power = other.power;
        position = other.position;
        species = other.species;
        initiative = other.initiative;
        powerToReproduce = other.powerToReproduce;
        ancestors = other.ancestors;
        alive = other.alive;
    }
    return *this;
}

Organism& Organism::operator=(Organism&& other) noexcept {
    if (this != &other) {
        power = std::move(other.power);
        position = std::move(other.position);
        species = std::move(other.species);
        initiative = std::move(other.initiative);
        powerToReproduce = std::move(other.powerToReproduce);
        ancestors = std::move(other.ancestors);
        alive = std::move(other.alive);
    }
    return *this;
}

int Organism::getPower() const {
    return this->power;
}

void Organism::setPower(int power) {
    this->power = power;
}

Position Organism::getPosition() const {
    return this->position;
}

void Organism::setPosition(Position position) {
    this->position = position;
}

string Organism::getSpecies() const {
    return this->species;
}

void Organism::setSpecies(string spec) {
    this->species = spec;
}

void Organism::addAncestor(int birthTurn, int deathTurn) {
    ancestors.emplace_back(birthTurn, deathTurn);
}

void Organism::serialize(fstream& file) const {
    file.write((char*)&power, sizeof(int));
    int x = position.getX();
    int y = position.getY();
    file.write((char*)&x, sizeof(int));
    file.write((char*)&y, sizeof(int));
    int speciesSize = species.size();
    file.write((char*)&speciesSize, sizeof(int));
    file.write(species.data(), speciesSize);
}

void Organism::move(int dx, int dy) {
    position.move(dx, dy);
}

string Organism::toString() const {
    return species + " at (" + to_string(position.getX()) + ", " + to_string(position.getY()) + ")" 
           + " with power " + to_string(power);
}
