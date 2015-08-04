#include "SQLiteConnector.h"
#include "savedGame.h"
#include "Achievement.h"

using namespace std;

SQLiteConnector::SQLiteConnector()
{
    //ctor
}

SQLiteConnector::~SQLiteConnector()
{
    dbDisconnect();
    //dtor
}

bool SQLiteConnector::dbConnect()
{
    msg = sqlite3_open("Darktech SaveSystem.sqlite",&db);
    if(msg!=SQLITE_OK)
    {
        return false;
    }
    return true;
}
void SQLiteConnector::dbDisconnect()
{
    sqlite3_close(db);
}

/*bool SQLiteConnector::findGame(savedGame saved)
{
    char sentence[256];
    if(dbConnect())
    {
        sprintf(sentence,"SELECT * FROM Profiles WHERE Name ='%s';",saved.getName());
        msg = sqlite3_prepare(db,sentence,strlen(sentence),&stmt_result,&next);
        if (msg != SQLITE_OK)
        {
            //cout << error << endl;
            return false;
        }
        if (sqlite3_step(stmt_result) == SQLITE_ROW)
        {
           return false;
        }
        dbDisconnect();
        return true;
    }
    return false;
}
*/

bool SQLiteConnector::createGame(savedGame saved)
{
    char sentence[256];
    if(dbConnect())
    {

            sprintf(sentence,"INSERT OR REPLACE INTO Profiles (Name, Map, Health) Values ('%s', '%s', '%s');",saved.getName(),saved.getMap(),saved.getHealth());
            msg = sqlite3_exec(db,sentence,NULL,NULL,&error);
            if (msg != SQLITE_OK)
            {
                //cout << error << endl;
                return false;
            }

       dbDisconnect();
       return true;
    }
    return false;
}

bool SQLiteConnector::createAchievement(Achievement saved)
{
    char sentence[256];
    if(dbConnect())
    {
            // sprintf(sentence,"UPDATE Achievements SET Ach_name='%s', Description='%s', Status='%s' WHERE Id='%s');",saved.getName(),saved.getDescription(),saved.getStatus(),saved.getId());
            sprintf(sentence,"INSERT OR REPLACE INTO Achievements (Id, Ach_name, Description, Status) Values ('%s', '%s', '%s', '%s');",saved.getId(),saved.getName(),saved.getDescription(),saved.getStatus());
            msg = sqlite3_exec(db,sentence,NULL,NULL,&error);
            if (msg != SQLITE_OK)
            {
                //cout << error << endl;
                return false;
            }

       dbDisconnect();
       return true;
    }
    return false;
}

bool SQLiteConnector::deleteGame(char *name)
{
    char sentence[256];
    if(dbConnect())
    {
        sprintf(sentence,"DELETE FROM Profiles WHERE Name='%s' ;",name);
        msg = sqlite3_exec(db,sentence,NULL,NULL,&error);
        if (msg != SQLITE_OK)
        {
            //cout << error << endl;
            return false;
        }
        dbDisconnect();
        return true;
    }
    return false;
}


int listGamesCallback(void *userdata, int argc, char **argv, char **azColName)
    {
        savedGame juego_guardado;
        vector<savedGame> *results;
        results = static_cast<vector<savedGame> *>(userdata);
        results->empty();
        char* col;
        savedGame compara;
        for(int i = 0; i< argc ; i++)
        {
            col = azColName[i];
            if(stricmp(col,"Name")== 0) juego_guardado.setName(argv[i]);
            else if(stricmp(col,"Map")== 0) juego_guardado.setMap(argv[i]);
            else if(stricmp(col,"Health")== 0) juego_guardado.setHealth(argv[i]);
        }
        results->add(juego_guardado);
        return 0;
    }

int listAchievementsCallback(void *userdata, int argc, char **argv, char **azColName)
    {
        Achievement juego_guardado;
        vector<Achievement> *results;
        results = static_cast<vector<Achievement> *>(userdata);
        results->empty();
        char* col;
        Achievement compara;
        for(int i = 0; i< argc ; i++)
        {
            col = azColName[i];
            if(stricmp(col,"Ach_name")== 0) juego_guardado.setName(argv[i]);
            else if(stricmp(col,"Status")== 0) juego_guardado.setStatus(argv[i]);
            else if(stricmp(col,"Description")== 0) juego_guardado.setDescription(argv[i]);
            else if(stricmp(col,"Id")==0) juego_guardado.setId(argv[i]);
        }
        results->add(juego_guardado);
        return 0;
    }

int listSpecificAchievementCallback(void *userdata, int argc, char **argv, char **azColName)
    {
        Achievement *results;
        results = static_cast<Achievement *>(userdata);
        char* col;
        for(int i = 0; i< argc-1 ; i++)
        {
            col = azColName[i];
            if(stricmp(col,"Ach_name")== 0) results->setName(argv[i]);
            else if(stricmp(col,"Status")== 0) results->setStatus(argv[i]);
            else if(stricmp(col,"Description")== 0) results->setDescription(argv[i]);
            else if(stricmp(col,"Id")==0) results->setId(argv[i]);
        }
        return 0;
    }


int listSpecificGameCallback(void *userdata, int argc, char **argv, char **azColName)
    {
        savedGame *results;
        results = static_cast<savedGame *>(userdata);
        char* col;
        for(int i = 0; i< argc ; i++)
        {
            col = azColName[i];

            if(stricmp(col,"Name")== 0) results->setName(argv[i]);
            else if(stricmp(col,"Map")== 0) results->setMap(argv[i]);
            else if(stricmp(col,"Health")== 0) results->setHealth(argv[i]);
        //    leProfile.setPositionX(atof(argv[3]));
        //    leProfile.setPositionY(atof(argv[4]));
        //    leProfile.setPositionZ(atof(argv[5]));
        }
        return 0;
    }

vector<savedGame> SQLiteConnector::listGames()
{
    vector<savedGame> profiles = vector<savedGame>();
    if(dbConnect())
    {
        sentence = "SELECT * FROM Profiles";
        msg = sqlite3_exec(db,sentence,listGamesCallback,reinterpret_cast<void*>(&profiles),&error);
        if (msg != SQLITE_OK)
        {
            //std::cout << error << std::endl;
            return profiles;
        }
        return profiles;
     }
     return profiles;
}

vector<Achievement> SQLiteConnector::listAchievements()
{
    vector<Achievement> profiles = vector<Achievement>();
    if(dbConnect())
    {
        sentence = "SELECT * FROM Achievements";
        msg = sqlite3_exec(db,sentence,listAchievementsCallback,reinterpret_cast<void*>(&profiles),&error);
        if (msg != SQLITE_OK)
        {
            //std::cout << error << std::endl;
            return profiles;
        }
        return profiles;
     }
     return profiles;
}

savedGame SQLiteConnector::getGame(char* name)
{
    savedGame eljuego;
    char sentence[256];
    if(dbConnect())
    {
        sprintf(sentence,"SELECT * FROM Profiles WHERE Name='%s' ;",name);
        msg = sqlite3_exec(db,sentence,listSpecificGameCallback,reinterpret_cast<void *>(&eljuego),&error);
        if (msg != SQLITE_OK)
        {
            //std::cout << error << std::endl;
            return eljuego;
        }

        return eljuego;
     }
     return eljuego;
}

Achievement SQLiteConnector::getAch(char* name)
{
    Achievement eljuego;
    char sentence[256];
    if(dbConnect())
    {
        sprintf(sentence,"SELECT * FROM Achievements WHERE Id='%s' ;",name);
        msg = sqlite3_exec(db,sentence,listSpecificAchievementCallback,reinterpret_cast<void *>(&eljuego),&error);
        if (msg != SQLITE_OK)
        {
            //std::cout << error << std::endl;
            return eljuego;
        }

        return eljuego;
     }
     return eljuego;
}
