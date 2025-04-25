#pragma once
#include "Animal.h"

class Cow : public Animal {
public:
    Cow(Position pos);
    Cow(int power, Position pos);
    char draw() const override;
    void action() override;
    void collision(Organism* other) override;
    void sound() const override;

    void serialize(fstream& file) const override;
    void deserialize(fstream& file) override;
};
