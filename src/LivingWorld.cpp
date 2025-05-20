#include <iostream>
#include <thread>
#include <chrono>
#include "Position.h"
#include "Organism.h"
#include "Cow.h"
#include "Wolf.h"
#include "Sheep.h"
#include "Guarana.h"
#include "Grass.h"
#include "World.h"
#include "Toadstool.h"

using namespace std;

int main()
{
    // World test
    World world(10, 10);

    // Inicjalizacja organizmów
    // Owce
    Position posSheep1{2, 2};
    Sheep *sheep1 = new Sheep(posSheep1);
    world.addOrganism(sheep1);

    Position posSheep2{3, 3};
    Sheep *sheep2 = new Sheep(posSheep2);
    world.addOrganism(sheep2);

    // Krowy
    Position posCow1{5, 5};
    Cow *cow1 = new Cow(posCow1);
    world.addOrganism(cow1);

    Position posCow2{6, 6};
    Cow *cow2 = new Cow(posCow2);
    world.addOrganism(cow2);

    // Wilk
    Position posWolf{7, 7};
    Wolf *wolf = new Wolf(posWolf);
    world.addOrganism(wolf);

    // Trawy
    Position posGrass1{1, 1};
    Grass *grass1 = new Grass(posGrass1);
    world.addOrganism(grass1);

    Position posGrass2{2, 3};
    Grass *grass2 = new Grass(posGrass2);
    world.addOrganism(grass2);

    // Guarana
    Position posGuarana1{6, 2};
    Guarana *guarana1 = new Guarana(posGuarana1);
    world.addOrganism(guarana1);

    // Muchomor
    Position posToadstool1{8, 8};
    Toadstool *toadstool1 = new Toadstool(posToadstool1);
    world.addOrganism(toadstool1);

    // Wypisanie planszy
    cout << "Initial state:" << endl;
    cout << world.toString() << endl;
    world.getOrganisms();

    // Wykonanie 15 tur
    for (int i = 1; i <= 12; ++i)
    {
        cout << "Turn " << i << ":" << endl;
        world.makeTurn();
        cout << world.toString() << endl;

        // Zapis świata w turze 8
        if (i == 8)
        {
            cout << "Saving world at turn 8..." << endl;
            world.writeWorld("world.bin");
        }

        // Odczekanie 3 sekund przed kolejną turą
        this_thread::sleep_for(chrono::seconds(3));
    }

    // Wczytanie świata z pliku
    cout << "Loading world from file..." << endl;
    world.readWorld("world.bin");
    cout << "World loaded:" << endl;
    cout << world.toString() << endl;

    return 0;
}
