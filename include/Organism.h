#pragma once
#include <string>
#include <utility>
#include <vector>
#include <fstream>
#include "Position.h"
#include "World.h"
#include <set>

class Organism;
class World;

using namespace std;

struct AncestorInfo {
    int birth_turn;
    int death_turn;
    Organism* ancestor_ptr;
};

class Organism
{
private:
    int power;
    Position position;
    string species;
    int powerToReproduce; // Minimalna siła do rozmnażania
    int birth_turn = -1;
    int death_turn = -1;

protected:
    vector<AncestorInfo> ancestors; // (birth_turn, death_turn)
    bool alive = true;
    bool justBorn = false;

public:
    Organism(int power, Position position);
    Organism(int power, Position position, int brithTurn);
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

    void addAncestor(int birthTurn, int deathTurn, Organism* ancestor);
    void setAncestors(const vector<AncestorInfo>& ancestors) { this->ancestors = ancestors; }
    vector<AncestorInfo>& getAncestors() { return ancestors; }
    const vector<AncestorInfo>& getAncestors() const { return ancestors; }

    int getBirthTurn() const { return birth_turn; }
    void setBirthTurn(int turn) { birth_turn = turn; }
    int getDeathTurn() const { return death_turn; }
    void setDeathTurn(int turn) { death_turn = turn; }

    bool isJustBorn() const { return justBorn; }
    void setJustBorn(bool val) { justBorn = val; }

    string toString() const;
    bool isAlive() const { return alive; }
    void kill() { alive = false; }
    void kill(int currentTurn);

    virtual void move(int dx, int dy);
    virtual char draw() const = 0;
    virtual void action(World& world) = 0;
    virtual void collision(Organism* other, World& world) = 0;
    virtual bool isPredator() const { return false; };
    virtual void reproduce(World& world, std::set<Organism*>& alreadyReproduced) {};
    virtual void grow(World& world) {};

    // Serializacja
    virtual void serialize(fstream& file) const;
};