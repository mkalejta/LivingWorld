#pragma once
#include "Organism.h"

class Plant : public Organism
{
	public:
		Plant(int power, Position position);
		Plant();
		using Organism::Organism;
		virtual ~Plant() = default;
		virtual void grow() = 0;
};

