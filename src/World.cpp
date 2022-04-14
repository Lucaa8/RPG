#include "World.h"

namespace RPG
{
    World::World(string worldName, Location* spawnLoc) : worldName(worldName), spawnLocation(spawnLoc)
    {
        cout << "New world loaded [" << worldName << "] -> Spawn: " << *spawnLoc << endl;
    }

    World::~World()
    {
        delete spawnLocation;
    }

    string World::getWorldName() const
    {
        return worldName;
    }

    void World::setSpawnLocation(Location* loc)
    {
        cout << "Spawnpoint was moved from " << *spawnLocation;
        this->spawnLocation = loc;
        cout << " to " << *spawnLocation << endl;
    }

    void World::setSpawnLocation(double x, double y, double z)
    {
        setSpawnLocation(new Location(x,y,z));
    }

    Location* World::getSpawnLocation() const
    {
        return spawnLocation;
    }
}
