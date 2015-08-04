#include "..\engine\engine.h"
#include "..\SQLite\SQLiteConnector.h"
#include "..\SQLite\savedGame.h"
#include "game.h"

namespace game
{

void saveGameFPS(char *pname)
{
    if(!*pname) sprintf(pname,"Autosave");
    savedGame legame = savedGame();
    SQLiteConnector connector = SQLiteConnector();
    legame.setName(pname);
    legame.setMap(const_cast<char *>(game::getclientmap()));
    legame.setHealth("100");
    connector.createGame(legame);
}

COMMAND(saveGameFPS, "s");
}
