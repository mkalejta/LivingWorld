#pragma once
#include "Plant.h"

class Guarana : public Plant {
public:
    Guarana(Position pos);
    Guarana(int power, Position pos);
    char draw() const override;
    void action() override;
    void collision(Organism* other) override;
    void grow() override;

    void serialize(fstream& file) const override;
};
