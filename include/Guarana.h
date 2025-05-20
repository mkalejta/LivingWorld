#pragma once
#include "Plant.h"
#include "World.h"

class Guarana : public Plant {
public:
    Guarana(Position pos);
    Guarana(int power, Position pos);
    char draw() const override;
    void action(World& world) override;
    void collision(Organism* other, World& world) override;
    void grow(World& world) override;

    void serialize(fstream& file) const override;
};
