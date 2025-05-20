#pragma once
#include "Plant.h"
#include "World.h"

class Toadstool : public Plant {
public:
    Toadstool(Position pos);
    Toadstool(int power, Position pos);
    char draw() const override;
    void grow(World& world) override;
    void action(World& world) override;
    void collision(Organism* other, World& world) override;

    void serialize(fstream& file) const override;
};