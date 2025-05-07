#pragma once

#include <vector>
#include <ctime>
#include "Organism.h"
#include "Position.h"

using namespace std;

struct GrassRegrowInfo {
    Position position;
    int turnsLeft;
};

class World
{
private:
	int worldX;
	int worldY;
	int turn = 0;
	vector<Organism*> organisms;
	char separator = '.';
	string getOrganismFromPosition(int x, int y);
	bool isPositionOnWorld(int x, int y);
	bool isPositionFree(Position position);
	std::vector<std::pair<Position, int>> grassToRegrow;

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

    void markGrassToRegrow(Position pos);
    void updateGrassRegrowth();
    void removeOrganism(Organism* org);

	Organism* getOrganismAt(Position pos) const;
	void removeDeadOrganisms();
	void sortOrganisms();

	void getOrganisms();
};

