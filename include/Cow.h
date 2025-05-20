#pragma once
#include "Animal.h"
#include "World.h"

class Cow : public Animal {
public:
    Cow(Position pos);
    Cow(int power, Position pos, int birthTurn);
    char draw() const override;
    void action(World& world) override;
    void collision(Organism* other, World& world) override;
    void reproduce(World& world, std::set<Organism*>& alreadyReproduced) override;
    void sound() const override;

    void serialize(fstream& file) const override;
};
