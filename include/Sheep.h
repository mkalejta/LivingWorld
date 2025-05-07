#pragma once
#include "Animal.h"

class Sheep : public Animal {
public:
    Sheep(Position pos);
    Sheep(int power, Position pos);
    char draw() const override;
    void action() override;
    void collision(Organism* other) override;
    void sound() const override;

    void serialize(fstream& file) const override;
};
