#pragma once
#include "Animal.h"

class Wolf : public Animal {
public:
    Wolf(Position pos);
    Wolf(int power, Position pos);
    char draw() const override;
    void action() override;
    void collision(Organism* other) override;
    bool isPredator() const override;
    void sound() const override;

    void serialize(fstream& file) const override;
};
