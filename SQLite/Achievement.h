#ifndef ACHIEVEMENT_H
#define ACHIEVEMENT_H
#include "../engine/engine.h"
#include "../shared/tools.h"
#include <string.h>

class Achievement
{
    public:
        Achievement();
        virtual ~Achievement();
        char* getId() {return id;}
        char* getName() {return name;}
        char* getStatus() {return status;}
        char* getDescription() {return description;}
        void setId(const char* a) { sprintf(id,a);}
        void setName(const char* a) { sprintf(name,a);}
        void setStatus(const char* a) { sprintf(status,a);}
        void setDescription(const char* a) { sprintf(description,a);}
    private:
        char id[1024];
        char name[1024];
        char description[1024];
        char status[1024];

};

#endif // ACHIEVEMENT_H
