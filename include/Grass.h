#pragma once
#include "Plant.h"
#include <fstream>
#include "World.h"

class Grass : public Plant {
public:
    Grass(Position pos);
    Grass(int power, Position pos);
    char draw() const override;
    void action(World& world) override;
    void collision(Organism* other, World& world) override;
    void reproduce(World& world) override;
    void grow() override;
    
    void serialize(fstream& file) const override;
};
