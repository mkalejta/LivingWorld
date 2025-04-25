#pragma once
#include "Plant.h"
#include <fstream>

class Grass : public Plant {
public:
    Grass(Position pos);
    Grass(int power, Position pos);
    char draw() const override;
    void action() override;
    void collision(Organism* other) override;
    void grow() override;
    
    void serialize(fstream& file) const override;
    void deserialize(fstream& file) override;
};
