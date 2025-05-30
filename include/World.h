#pragma once
#include <vector>
#include <ctime>
#include "Organism.h"
#include "Position.h"

// Deklaracja wstępna klasy Organism
class Organism;

using namespace std;

class World
{
private:
	int worldX;
	int worldY;
	int turn = 0;
	vector<Organism*> organisms;
	char separator = '.';
	string getOrganismFromPosition(int x, int y);
	bool isPositionFree(Position position);
	
public:
	World(int worldX, int worldY);
	World() : World(6, 6) {};
	~World();

	int getWorldX();
	void setWorldX(int worldX);
	int getWorldY();
	void setWorldY(int worldY);

	int getTurn();
	
	void addOrganism(Organism *organism);
	vector<Position> getVectorOfFreePositionsAround(Position position);
	void makeTurn();

	void writeWorld(string fileName);
	void readWorld(string fileName);
	
	string toString();

    void removeOrganism(Organism* org);

	Organism* getOrganismAt(Position pos) const;
	void removeDeadOrganisms();
	void sortOrganisms();

	void getOrganisms();

	bool isPositionOnWorld(int x, int y);

    vector<Organism*>& getOrganismsList() { return organisms; };
	const vector<Organism*>& getOrganismsList() const { return organisms; };

	void clear();
	int getCurrentTurn() const { return turn; };

    void updateAncestorsDeathTurn(Organism* deadOrganism, int deathTurn);
};

