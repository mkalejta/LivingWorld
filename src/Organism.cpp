#include "../include/Organism.h"
#include <iostream>


Organism::Organism(int power, Position position)
    : power(power), position(position)
{
    setSpecies("O");
}

Organism::Organism(int power, Position position, int birthTurn)
    : power(power), position(position), birth_turn(birthTurn), death_turn(-1)
{
    setSpecies("O");
}

Organism::Organism(const Organism& other)
    : power(other.power),
      position(other.position),
      species(other.species),
      powerToReproduce(other.powerToReproduce),
      ancestors(other.ancestors),
      alive(other.alive),
      justBorn(true)
{}

Organism::Organism(Organism&& other) noexcept
    : power(std::move(other.power)), position(std::move(other.position)),
      species(std::move(other.species)),
      powerToReproduce(std::move(other.powerToReproduce)),
      ancestors(std::move(other.ancestors)),
      alive(std::move(other.alive)) {}

Organism& Organism::operator=(const Organism& other) {
    if (this != &other) {
        power = other.power;
        position = other.position;
        species = other.species;
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

void Organism::addAncestor(int birthTurn, int deathTurn, Organism* ancestor) {
    ancestors.push_back({birthTurn, deathTurn, ancestor});
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
    file.write((char*)&birth_turn, sizeof(int));
}

void Organism::move(int dx, int dy) {
    position.move(dx, dy);
}

string Organism::toString() const {
    return species + " at (" + to_string(position.getX()) + ", " + to_string(position.getY()) + ")" 
           + " with power " + to_string(power);
}

void Organism::kill(int currentTurn) {
    alive = false;
    death_turn = currentTurn;
}
