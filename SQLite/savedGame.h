#ifndef SAVEDGAME_H
#define SAVEDGAME_H
#include "..\engine\engine.h"
#include "..\shared\tools.h"
#include <string.h>

class savedGame
{
    public:
        savedGame();
        char* getName()
        {
             printf(name);
            return name;
        }
        char* getMap()
        {
            printf(mapname);
            return mapname;
        }
        char* getHealth() { return health;}
        void setName(const char* _name) { sprintf(name,_name); }
        void setMap(const char* _mapname) { sprintf(mapname, _mapname);}
        void setHealth(const char* _health) { sprintf(health, _health); }
        virtual ~savedGame();
    private:
        char name[1024];
        char mapname[1024];
        char health[1024];

};

#endif // SAVEDGAME_H
