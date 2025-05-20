#pragma once
#include "Animal.h"
#include "World.h"

class Wolf : public Animal {
public:
    Wolf(Position pos);
    Wolf(int power, Position pos);
    char draw() const override;
    void action(World& world) override;
    void collision(Organism* other, World& world) override;
    bool isPredator() const override;
    void sound() const override;

    void serialize(fstream& file) const override;
};
