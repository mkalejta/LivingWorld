#include <iostream>
#include "Position.h"
#include "Organism.h"
#include "Cow.h"
#include "Wolf.h"
#include "Sheep.h"
#include "Guarana.h"
#include "Grass.h"
#include "World.h"

using namespace std;

int main()
{	
	// World test
	World world(10, 10);

	// Trawa i krowa – test collision Cow–Grass
	Position posGrass1{ 5, 5 };
	Grass* grass1 = new Grass(posGrass1);
	world.addOrganism(grass1);

	Position posCow{ 6, 5 };
	Cow* cow = new Cow(posCow);
	world.addOrganism(cow);

	// Guarana i owca – test collision Sheep–Guarana
	Position posGuarana{ 2, 2 };
	Guarana* guarana = new Guarana(posGuarana);
	world.addOrganism(guarana);

	Position posSheep{ 2, 1 };
	Sheep* sheep = new Sheep(posSheep);
	world.addOrganism(sheep);

	// Wilk i owca – test collision Wolf–Sheep
	Position posSheep2{ 7, 5 };
	Sheep* sheep2 = new Sheep(posSheep2);
	world.addOrganism(sheep2);

	Position posWolf{ 6, 6 };
	Wolf* wolf = new Wolf(posWolf);
	world.addOrganism(wolf);

	// Wypisz planszę i wykonaj kilka tur
	cout << world.toString() << endl;

	world.makeTurn();
	cout << world.toString() << endl;

	world.makeTurn();
	cout << world.toString() << endl;

	// Zapisz stan
	world.writeWorld("world.bin");

	world.makeTurn();
	cout << world.toString() << endl;

	// Powrót do tury 2
	world.readWorld("world.bin");
	cout << "Powrót do tury 2:\n";
	cout << world.toString() << endl;

	return 0;
}
