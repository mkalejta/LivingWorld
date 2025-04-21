#include "../include/Organism.h"
#include <iostream>

Organism::Organism(int power, Position position)
{
	setPower(power);
	setPosition(position);
	setSpecies("O");
}

// Konstruktor kopiujący
Organism::Organism(const Organism& other)
    : power(other.power), position(other.position), species(other.species), ancestors(other.ancestors)
{}

// Konstruktor przenoszący
Organism::Organism(Organism&& other) noexcept
    : power(std::move(other.power)), position(std::move(other.position)),
	species(std::move(other.species)), ancestors(std::move(other.ancestors))
{}

// Operator przypisania kopiujący
Organism& Organism::operator=(const Organism& other) {
    if (this != &other) {
        power = other.power;
		position = other.position;
		species = other.species;
        ancestors = other.ancestors;
    }
    return *this;
}

// Operator przypisania przenoszący
Organism& Organism::operator=(Organism&& other) noexcept {
    if (this != &other) {
        power = std::move(other.power);
		position = std::move(other.position);
		species = std::move(other.species);
        ancestors = std::move(other.ancestors);
    }
    return *this;
}

int Organism::getPower()
{
	return this->power;
}

void Organism::setPower(int power)
{
	this->power = power;
}

Position Organism::getPosition()
{
	return this->position;
}

void Organism::setPosition(Position position)
{
	this->position = position;
}

string Organism::toString()
{
	return "{ species: " + this->getSpecies() + 
		", power: " + to_string(getPower()) + 
		", position: " + getPosition().toString() + "}";
}

void Organism::move(int dx, int dy)
{
	position.move(dx, dy);
}

string Organism::getSpecies()
{
	return this->species;
}

void Organism::setSpecies(string spec)
{
	this->species = spec;
}

void Organism::addAncestor(int birthTurn, int deathTurn) {
    ancestors.emplace_back(birthTurn, deathTurn);
}
