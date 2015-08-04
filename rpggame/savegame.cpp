#include "..\engine\engine.h"
#include "rpg.h"
#include "..\SQLite\SQLiteConnector.h"
#include "..\SQLite\savedGame.h"

namespace game
{

void saveGame(char *pname, char *php)
{
    if(*php)
    {
    savedGame legame = savedGame();
    SQLiteConnector connector = SQLiteConnector();
    legame.setName(pname);
    legame.setMap(const_cast<char *>(game::getclientmap()));
    legame.setHealth(php);
    connector.createGame(legame);
    }
    else
    {
    savedGame legame = savedGame();
    SQLiteConnector connector = SQLiteConnector();
    legame.setName(pname);
    legame.setMap(const_cast<char *>(game::getclientmap()));
    legame.setHealth("100");
    connector.createGame(legame);
    }
}
COMMAND(saveGame, "ss");
}
