#include "../include/World.h"
#include <fstream>
#include <algorithm>
#include <iostream>
#include "Wolf.h"
#include "Sheep.h"
#include "Cow.h"
#include "Guarana.h"
#include "Grass.h"

using namespace std;

string World::getOrganismFromPosition(int x, int y)
{   
    for (Organism* org : organisms)
        if (org->getPosition().getX() == x && org->getPosition().getY() == y)
            return org->getSpecies();
    return "";
}

bool World::isPositionOnWorld(int x, int y)
{
    return (x >= 0 && y >= 0 && x < getWorldX() && y < getWorldY());
}

bool World::isPositionFree(Position position) {
    return this->getOrganismFromPosition(position.getX(), position.getY()).empty();
}

vector<Position> World::getVectorOfFreePositionsAround(Position position)
{   
    int pos_x = position.getX(), pos_y = position.getY();
    vector<Position> result;
    for(int x = -1; x < 2; ++x)
        for (int y = -1; y < 2; ++y)
            if ((x != 0 || y != 0) && 
                isPositionOnWorld(pos_x + x, pos_y + y)) {
                result.push_back(Position(pos_x + x, pos_y + y));
            }
    auto iter = remove_if(result.begin(), result.end(),
        [this](Position pos) {return !isPositionFree(pos); });
    result.erase(iter, result.end());

    return result;
}

World::World(int worldX, int worldY)
{
    setWorldX(worldX);
    setWorldY(worldY);
}

World::~World() {
    for (Organism* org : organisms) {
        delete org;
    }
    organisms.clear();
}

int World::getWorldX()
{
    return this->worldX;
}

void World::setWorldX(int worldX)
{
    this->worldX = worldX;
}

int World::getWorldY()
{
    return this->worldY;
}

void World::setWorldY(int worldY)
{
    this->worldY = worldY;
}

int World::getTurn()
{
    return this->turn;
}

void World::addOrganism(Organism* organism)
{
    this->organisms.push_back(organism);
}

void World::removeOrganism(Organism* org) {
    // Jeśli organizm to trawa, zaznacz pozycję do regeneracji
    Grass* grass = dynamic_cast<Grass*>(org);
    if (grass != nullptr) {
        markGrassToRegrow(grass->getPosition());
    }

    // Usuń z wektora organisms
    auto it = std::find(organisms.begin(), organisms.end(), org);
    if (it != organisms.end()) {
        organisms.erase(it);
    }

    delete org;
}

void World::markGrassToRegrow(Position pos) {
    grassToRegrow.push_back({pos, 3}); // odrodzenie za 2 tury
}

void World::updateGrassRegrowth() {
    for (auto it = grassToRegrow.begin(); it != grassToRegrow.end();) {
        it->second--;
        if (it->second <= 0) {
            // Odrodzenie trawy w danej pozycji
            addOrganism(new Grass(it->first));
            it = grassToRegrow.erase(it);
        } else {
            ++it;
        }
    }
}

Organism* World::getOrganismAt(Position pos) const {
    for (Organism* o : organisms) {
        if (o->getPosition() == pos)
            return o;
    }
    return nullptr;
}

void World::removeDeadOrganisms() {
    auto it = organisms.begin();
    while (it != organisms.end()) {
        if (!(*it)->isAlive()) {
            Grass* grass = dynamic_cast<Grass*>(*it);
            if (grass != nullptr) {
                markGrassToRegrow(grass->getPosition());
            }
            delete *it;
            it = organisms.erase(it);
        } else {
            ++it;
        }
    }
}

void World::sortOrganisms() {
    std::sort(organisms.begin(), organisms.end(),
        [](Organism* a, Organism* b) {
            return a->getPower() > b->getPower();
        });
}

void World::makeTurn() {
    sortOrganisms();

    vector<Organism*> currentOrganisms = organisms;

    for (Organism* org : currentOrganisms) {
        // Jeśli organizm już nie istnieje (umarł lub zniknął)
        if (find(organisms.begin(), organisms.end(), org) == organisms.end())
            continue;

        org->action();

        Position newPos = org->getPosition();
        Organism* other = getOrganismAt(newPos);

        if (other != nullptr && other != org && other->isAlive()) {
            org->collision(other);
        }
    }

    removeDeadOrganisms(); 
    updateGrassRegrowth(); 
    turn++;
}


void World::writeWorld(string fileName) {
    fstream file(fileName, ios::out | ios::binary);
    if (file.is_open()) {
        file.write((char*)&worldX, sizeof(int));
        file.write((char*)&worldY, sizeof(int));
        file.write((char*)&turn, sizeof(int));
        int orgsSize = organisms.size();
        file.write((char*)&orgsSize, sizeof(int));
        for (Organism* org : organisms) {
            org->serialize(file);
        }
        file.close();
    }
}

void World::readWorld(string fileName) {
    fstream file(fileName, ios::in | ios::binary);
    if (file.is_open()) {
        int orgsSize;
        file.read((char*)&worldX, sizeof(int));
        file.read((char*)&worldY, sizeof(int));
        file.read((char*)&turn, sizeof(int));
        file.read((char*)&orgsSize, sizeof(int));
        organisms.clear();

        for (int i = 0; i < orgsSize; ++i) {
            string species;
            int speciesSize;
            file.read((char*)&speciesSize, sizeof(int));
            species.resize(speciesSize);
            file.read(&species[0], speciesSize);

            int x, y;
            file.read((char*)&x, sizeof(int));
            file.read((char*)&y, sizeof(int));
            Position pos(x, y);

            Organism* org = nullptr;
            if (species == "g") org = new Grass(pos);
            else if (species == "G") org = new Guarana(pos);
            else if (species == "W") org = new Wolf(pos);
            else if (species == "S") org = new Sheep(pos);
            else if (species == "C") org = new Cow(pos);

            if (org) {
                org->deserialize(file);
                organisms.push_back(org);
            }
        }
        file.close();
    }
}

string World::toString()
{
    string result = "\nturn: " + to_string(getTurn()) + "\n";
    string spec;

    for (int wY = 0; wY < getWorldY(); ++wY) {
        for (int wX = 0; wX < getWorldX(); ++wX) {
            spec = getOrganismFromPosition(wX, wY);
            if (spec != "")
                result += spec;
            else
                result += separator;
        };
        result += "\n";
    }
    return result;
}
