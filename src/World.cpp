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

void World::makeTurn() {
    srand(time(0));
    vector<Organism*> currentOrganisms = organisms;

    for (Organism* org : currentOrganisms) {
        if (find(organisms.begin(), organisms.end(), org) == organisms.end())
            continue;

        org->action(); // organizm wykonuje swój ruch (zmienia pozycję)

        Position newPos = org->getPosition();

        // Sprawdzamy, czy coś jest na nowej pozycji
        Organism* other = getOrganismAt(newPos);

        // Możemy trafić sami na siebie, więc sprawdzamy wskaźniki
        if (other != nullptr && other != org) {
            org->collision(other);
        }
    }

    removeDeadOrganisms(); 
    updateGrassRegrowth();
    turn++;
}


void World::writeWorld(string fileName)
{
    fstream my_file;
    my_file.open(fileName, ios::out | ios::binary);
    if (my_file.is_open()) {
        my_file.write((char*)&this->worldX, sizeof(int));
        my_file.write((char*)&this->worldY, sizeof(int));
        my_file.write((char*)&this->turn, sizeof(int));
        int orgs_size = this->organisms.size();
        my_file.write((char*)&orgs_size, sizeof(int));
        for (int i = 0; i < orgs_size; i++) {
            int data;
            data = this->organisms[i]->getPower();
            my_file.write((char*)&data, sizeof(int));
            data = this->organisms[i]->getPosition().getX();
            my_file.write((char*)&data, sizeof(int));
            data = this->organisms[i]->getPosition().getY();
            my_file.write((char*)&data, sizeof(int));
            string s_data = this->organisms[i]->getSpecies();
            int s_size = s_data.size();
            my_file.write((char*)&s_size, sizeof(int));
            my_file.write(s_data.data(), s_data.size());
        }
        my_file.close();
    }
}

void World::readWorld(string fileName)
{
    fstream my_file;
    my_file.open(fileName, ios::in | ios::binary);
    if (my_file.is_open()) {
        int result;
        my_file.read((char*)&result, sizeof(int));
        this->worldX = (int)result;
        my_file.read((char*)&result, sizeof(int));
        this->worldY = (int)result;
        my_file.read((char*)&result, sizeof(int));
        this->turn = (int)result;
        my_file.read((char*)&result, sizeof(int));
        int orgs_size = (int)result;

        for (int i = 0; i < orgs_size; i++) {
            int power;
            my_file.read((char*)&result, sizeof(int));
            power = (int)result;

            int pos_x;
            my_file.read((char*)&result, sizeof(int));
            pos_x = (int)result;
            int pos_y;
            my_file.read((char*)&result, sizeof(int));
            pos_y = (int)result;
            Position pos{ pos_x, pos_y };

            int s_size;
            my_file.read((char*)&result, sizeof(int));
            s_size = (int)result;

            string species;
            species.resize(s_size);
            my_file.read((char*)&species[0], s_size);

            Organism* org = nullptr;
            if (species == "Wolf") org = new Wolf(power, pos);
            else if (species == "Sheep") org = new Sheep(power, pos);
            else if (species == "Cow") org = new Cow(power, pos);
            else if (species == "Guarana") org = new Guarana(power, pos);
            else if (species == "Grass") org = new Grass(power, pos);

            if (org) organisms.push_back(org);
        }
        my_file.close();
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

void World::markGrassToRegrow(Position pos) {
    grassToRegrow.push_back({pos, 2}); // odrodzenie za 2 tury
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


