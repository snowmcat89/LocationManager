#include "lists.h"

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

TypeDuLogement typesDesLogements[] = {
    {1, "STUDIO"},
    {2, "F2"},
    {3, "F3"},
    {4, "F4"}
};
LogementsExistants logementsExistants = {0, 0, 0, 0};
LoyerDeBase loyersDeBase[] = {
    {"STUDIO", 15000},
    {"F2", 20000},
    {"F3", 30000},
    {"F4", 45000},
};
SuperficieMoyenne superficiesMoyennes[] = {
    {"STUDIO", 20},
    {"F2", 45},
    {"F3", 65},
    {"F4", 85}
};

const char* RetTypeLogement(int typeNombre)
{
    return typesDesLogements[typeNombre-1].type;
}
int RetTypeNombre(char* type)
{
    for (int i = 0; i < 4; i++)
    {
        if (strcasecmp(typesDesLogements[i].type, type) == 0) return typesDesLogements[i].typeNombre;
    }
}
int RetLoyerDeBase(char *type)
{
    for (int i = 0; i < 4; i++)
    {
        if (strcasecmp(loyersDeBase[i].type, type) == 0) return loyersDeBase[i].LB;
    }
}
int RetSuperficieMoyenne(char *type)
{
    for (int i = 0; i < 4; i++)
    {
        if (strcasecmp(superficiesMoyennes[i].type, type) == 0) return superficiesMoyennes[i].SM;
    }
}
float RetLoyer(int typeNombre, float superficie)
{
    int index = typeNombre-1;
    int loyer = loyersDeBase[index].LB+(superficie-superficiesMoyennes[index].SM)*800;
    return loyer;
}
void MettreAJourLogements(bool diminuer, int typeNombre)
{
    if (diminuer == true)
    {
        switch (typeNombre)
        {
            case 1:
            {
                logementsExistants.studio--;
                break;
            }
            case 2: 
            {
                logementsExistants.f2--;
                break;
            }
            case 3: 
            {
                logementsExistants.f3--;
                break;
            }
            case 4: 
            {
                logementsExistants.f4--;
                break;
            }
        }
    }else{
        switch (typeNombre)
        {
            case 1:
            {
                logementsExistants.studio++;
                break;
            }
            case 2: 
            {
                logementsExistants.f2++;
                break;
            }
            case 3: 
            {
                logementsExistants.f3++;
                break;
            }
            case 4: 
            {
                logementsExistants.f4++;
                break;
            }
        }
    }
}
Date StringToDate(char *dateStr)
{
    Date date = {0};
    
    if(dateStr[2] != '/' && dateStr[5] != '/'){ 
        return date;
    }
    char jour[3], mois[3], annee[5];
    
    strncpy(jour, &dateStr[0], 2);
    jour[2] = '\0';

    strncpy(mois, &dateStr[3], 2);
    mois[2] = '\0';

    strncpy(annee, &dateStr[6], 4);
    annee[4] = '\0';

    if (atoi(jour) > 31 || atoi(mois) > 12)
    {
        return date;
    }

    date.jour = atoi(jour);
    date.mois = atoi(mois);
    date.annee = atoi(annee);
    return date;
}
