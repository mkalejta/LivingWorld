#pragma once
#include <string>
#include <utility>
#include <vector>
#include "Position.h"

using namespace std;

class Organism
{
private:
	int power;
	Position position;
	string species;
protected:
	vector<pair<int, int>> ancestors; // (birth_turn, death_turn)
public:
	Organism(int power, Position position);
	Organism() : power(0), position(0, 0), species("O") {};
	// Konstruktor kopiujący
    Organism(const Organism& other);
    // Konstruktor przenoszący
    Organism(Organism&& other) noexcept;
    // Operator przypisania kopiujący
    Organism& operator=(const Organism& other);
    // Operator przypisania przenoszący
    Organism& operator=(Organism&& other) noexcept;
    // Destruktor
    virtual ~Organism();

	int getPower();
	void setPower(int power);
	Position getPosition();
	void setPosition(Position position);
	string getSpecies();
	void setSpecies(string spec);

	void addAncestor(int birthTurn, int deathTurn);

	string toString();

	virtual void move(int dx, int dy);

};