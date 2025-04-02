#ifndef LISTS_H_
#define LISTS_H_

#include <stdbool.h>
#include <stdlib.h>

typedef struct LogementsExistants{
    int studio;
    int f2;
    int f3;
    int f4;
}LogementsExistants,*PLogementsExistants;
typedef struct TypeDuLogement{
    const int typeNombre;
    const char* type;
} TypeDuLogement;
typedef struct InformationsDuLogment{
    int id;
    int superficie;
    char* quartier;
    float loyer;
    int distanceACommune;
    bool occupe;
    char* typeDulogement;
} InformationsDuLogment, *PInformationsDuLogment;
typedef struct InformationsDuLocataire{
    int id;
    char* nom;
    char* prenom; 
    char* tel;
} InformationsDuLocataire,*PInformationsDuLocataire;
typedef struct InformationsDuLocation{
    int idlog;
    int idloc;
    char *dateDebut;
    char *dateFin;
} InformationsDuLocation,*PInformationsDuLocation;
typedef struct 
{
    int jour;
    int mois;
    int annee;
} Date;
typedef struct
{
    char *type;
    int LB;
} LoyerDeBase;
typedef struct
{
    char *type;
    int SM;
} SuperficieMoyenne;

extern TypeDuLogement typesDesLogements[];
extern LogementsExistants logementsExistants;
extern LoyerDeBase loyersDeBase[];
extern SuperficieMoyenne superficiesMoyennes[];

const char* RetTypeLogement(int typeNombre);
int RetTypeNombre(char* type);
int RetLoyerDeBase(char *type);
int RetSuperficieMoyenne(char *type);
float RetLoyer(int typeNombre, float superficie);
void MettreAJourLogements(bool diminuer, int typeNombre);
Date StringToDate(char *date);
#endif