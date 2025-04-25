#pragma once
#include "Organism.h"

using namespace std;

class Animal : public Organism
{
	public:
		Animal(int power, Position position);
		Animal();
		using Organism::Organism;
		virtual ~Animal() = default;
		virtual void sound() const = 0;
};

