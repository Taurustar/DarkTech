#ifndef SQLITECONNECTOR_H
#define SQLITECONNECTOR_H
#include "..\engine\engine.h"
#include "savedGame.h"
#include "Achievement.h"
#include "sqlite3.h"
#include <string.h>

class SQLiteConnector
{
    public:
        SQLiteConnector();
        virtual ~SQLiteConnector();
        bool createGame(savedGame saved);
        bool deleteGame(char *name);
        vector<savedGame> listGames();
        savedGame getGame(char* name);
        Achievement getAch(char* name);
        vector<Achievement> listAchievements();
        bool createAchievement(Achievement saved);
    private:
        const char* sentence;
        char a[21];
        sqlite3 *db;
        sqlite3_stmt* stmt_result;
        //bool findGame(savedGame save);
        int msg;
        bool dbConnect();
        void dbDisconnect();
        const char* next;
        char* error;
};

#endif // SQLITECONNECTOR_H
