#include "../include/Animal.h"

Animal::Animal(int power, Position position, int birthTurn) : Organism(power, position, birthTurn)
{
	setSpecies("A");
}

Animal::Animal(int power, Position position) : Organism(power, position)
{
	setSpecies("A");
}

Animal::Animal() : Organism()
{
	setSpecies("A");
}


