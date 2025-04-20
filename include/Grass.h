#pragma once
#include "Plant.h"

class Grass : public Plant {
public:
    Grass(Position pos);
    Grass(int power, Position pos);
    char draw() const override;
    void action() override;
    void collision(Organism* other) override;
};
