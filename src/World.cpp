#include "World.h"
#include "Game.h" //not good but no choice.. include loop otherwise (if including Game.h in header)

namespace RPG
{

    vector<int> splitMaskLine(string line)
    {
        vector<int> values;
        string delim = ",";

        auto start = 0U;
        auto end = line.find(delim);
        while (end != string::npos)
        {
            values.push_back(stoi(line.substr(start, end - start)));
            start = end + delim.length();
            end = line.find(delim, start);
        }
        values.push_back(stoi(line.substr(start, end)));
        return values;
    }

    World::World(string worldName, Location* spawnLoc) : worldName(worldName), spawnLocation(spawnLoc)
    {
        cout << "New world loaded [" << worldName << "] -> Spawn: " << *spawnLoc << endl;
        initMap();
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

    void World::initMap()
    {
        string texturePath = "textures/map/mapv2.png";
        if (!gameMapTexture.loadFromFile(texturePath))
        {
            cout << "Failed to load the \""+texturePath+"\" texture";
            gameMapTexture.create(1280, 768);
        }
        gameMap.setTexture(gameMapTexture);
        gameMap.setTextureRect(IntRect(0, 0, 1280, 768));
        //Collisions
        string yLine;
        ifstream collideFile ("textures/map/colisions.txt");
        if (collideFile.is_open())
        {
            int y = 0;
            while (getline(collideFile,yLine))
            {
                int x = 0;
                for(int i : splitMaskLine(yLine))
                {
                    mask[y][x] = i;
                    x++;
                }
                y++;
            }
            collideFile.close();
        }
    }

    void World::drawMap(RenderTarget& screen)
    {
        screen.draw(gameMap);
    }

    int World::collideWith(RectangleShape& rect)
    {
        if(rect.getPosition().x < 0 || rect.getPosition().y < 0)
            return 1;
        int x = rect.getPosition().x/32;
        int y = (rect.getPosition().y+rect.getSize().y)/32;
        if(x>=39||y>=24)
        {
            return 1;
        }
        int myx = mask[y][x];
        if(myx>4)//0-4 arent consumable items (void, wall, houses)
        {
            Game::instance->print(static_cast<ostringstream*>(&(ostringstream() << "Consumed item with ID " << myx << " at tile location (" << x << "," << y << ")"))->str(), true);
            mask[y][x] = 0; //remove item after consumed
        }
        return myx;
    }
}
