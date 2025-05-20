#pragma once
#include <string>
#include <utility>
#include <vector>
#include <fstream>
#include "Position.h"
#include "World.h"

class World;

using namespace std;

class Organism
{
private:
    int power;
    Position position;
    string species;
    int initiative; // Priorytet decydujący o kolejności ruchu
    int powerToReproduce; // Minimalna siła do rozmnażania

protected:
    vector<pair<int, int>> ancestors; // (birth_turn, death_turn)
    bool alive = true;

public:
    Organism(int power, Position position);
    Organism() : power(0), position(0, 0), species("O") {};
    Organism(const Organism& other);
    Organism(Organism&& other) noexcept;
    Organism& operator=(const Organism& other);
    Organism& operator=(Organism&& other) noexcept;
    virtual ~Organism() = default;

    int getPower() const;
    void setPower(int power);
    Position getPosition() const;
    void setPosition(Position position);
    string getSpecies() const;
    void setSpecies(string spec);
    int getPowerToReproduce() const { return powerToReproduce; }
    void setPowerToReproduce(int powerToReproduce) { this->powerToReproduce = powerToReproduce; }

    void addAncestor(int birthTurn, int deathTurn);

    string toString() const;
    bool isAlive() const { return alive; }
    void kill() { alive = false; }

    virtual void move(int dx, int dy);
    virtual char draw() const = 0;
    virtual void action(World& world) = 0;
    virtual void collision(Organism* other, World& world) = 0;
    virtual bool isPredator() const { return false; };
    virtual void reproduce(World& world) {};
    virtual void grow(World& world) {};

    // Serializacja
    virtual void serialize(fstream& file) const;
};