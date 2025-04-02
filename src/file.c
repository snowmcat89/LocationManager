#include "LOG_LLC_BIBLIO.h"
#include "file.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

void ExtraireLogInfoDuFichier(const char *filename)
{
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        printf("\t\t  Erreur : Impossible d'ouvrir le fichier '%s'.\n", filename);
        return;
    }
    printf("\t\t  Fichier '%s' ouvert avec succès !\n", filename);
    printf("\t\t  +------------+------------+------------+-----------------+------------+------------+\n");
    printf("\t\t  | %-10s | %-10s | %-10s | %-15s | %-10s | %-10s |\n", 
           "ID", "Superficie", "Distance", "Quartier", "Occupé", "Type");
    printf("\t\t  +------------+------------+------------+-----------------+------------+------------+\n");

    char line[1024];
    int count = 0;
    int countLogementsExistants = 0;
    int countLogementsNonAlloues = 0;
    while (fgets(line, sizeof(line), file)) {
        Logement logement;
        char quartier[50];
        char type[20];
        char occupeStr[6];

        int result = sscanf(line, "%d %d %d %49s %5s %19s",
                            &logement.informationsDuLogement.id,
                            &logement.informationsDuLogement.superficie,
                            &logement.informationsDuLogement.distanceACommune,
                            quartier,
                            occupeStr,
                            type);

        if (result == 6) {
            logement.informationsDuLogement.occupe = (strcmp(occupeStr, "true") == 0);

            logement.informationsDuLogement.quartier = strdup(quartier);
            logement.informationsDuLogement.typeDulogement = strdup(type);

            int etat = NouveauLogement(logement.informationsDuLogement, false);
            if (etat == 1)
            {
                countLogementsExistants++;
                continue;
            
            }else if (etat == 2)
            {
                countLogementsNonAlloues++;
                continue;
            }else
            {
                printf("\t\t  | %-10d | %-10d | %-10d | %-15s | %-10s | %-10s |\n",
                    logement.informationsDuLogement.id,
                    logement.informationsDuLogement.superficie,
                    logement.informationsDuLogement.distanceACommune,
                    logement.informationsDuLogement.quartier,
                    logement.informationsDuLogement.occupe ? "Oui" : "Non",
                    logement.informationsDuLogement.typeDulogement);
                count++;
            }
        } else {
            printf("\t\t  Erreur : Échec de l'analyse de la ligne. Champs %d analysés au lieu de 6.\n", result);
            printf("\t\t  Ligne ignorée : %s\n", line);
        }
    }
    printf("\t\t  +------------+------------+------------+-----------------+------------+------------+\n");
    if (count >= 1 && countLogementsExistants == 0 && countLogementsNonAlloues == 0)
    {
        printf("\t\t  %d logements créés avec succès.\n", count);
    }else if(count == 0 && countLogementsExistants >= 1 && countLogementsNonAlloues == 0)
    {
        printf("\t\t  %d logements existent déja.\n", countLogementsExistants);
    }else if(count == 0 && countLogementsExistants == 0 && countLogementsNonAlloues >= 1) 
    {
        printf("\t\t  %d logements non alloues (Probleme du memoire).\n", countLogementsNonAlloues);
    }else{
        printf("\t\t  %d logements créés avec succès.\n", count);
        printf("\t\t  %d logements existent déja.\n", countLogementsExistants);
        printf("\t\t  %d logements non alloues (Probleme du memoire).\n", countLogementsNonAlloues);
    }
    fclose(file);
}
void ExtraireLocataireInfoDuFichier(const char *filename)
{
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        printf("\t\t  Erreur : Impossible d'ouvrir le fichier '%s'.\n", filename);
        return;
    }
    printf("\t\t  Fichier '%s' ouvert avec succès !\n", filename);
    printf("\t\t  +------------+-----------------+-----------------+-----------------+\n");
    printf("\t\t  | %-10s | %-15s | %-15s | %-15s |\n", 
           "ID", "Nom", "Prénom", "Téléphone");
    printf("\t\t  +------------+-----------------+-----------------+-----------------+\n");

    char line[1024];
    int count = 0;
    int countLocatairesExistants = 0;
    int countLocatairesNonAlloues = 0;
    while (fgets(line, sizeof(line), file)) {
        Locataire locataire;
        char nom[15];
        char prenom[15];
        char telephone[13];

        int result = sscanf(line, "%d %14s %14s %12s",
                            &locataire.informationsDuLocataire.id,
                            nom,
                            prenom,
                            telephone);

        if (result == 4) {
            locataire.informationsDuLocataire.nom = strdup(nom);
            locataire.informationsDuLocataire.prenom = strdup(prenom);
            locataire.informationsDuLocataire.tel = strdup(telephone);

            int etat = NouveauLocataire(locataire.informationsDuLocataire, false);
            if (etat == 1)
            {
                countLocatairesExistants++;
                continue;
            }else if (etat == 2)
            {
                countLocatairesNonAlloues++;
                continue;
            }else
            {
                printf("\t\t  | %-10d | %-15s | %-15s | %-15s |\n",
                    locataire.informationsDuLocataire.id,
                    locataire.informationsDuLocataire.nom,
                    locataire.informationsDuLocataire.prenom,
                    locataire.informationsDuLocataire.tel);
                count++;
            }
        } else {
            printf("\t\t  Erreur : Échec de l'analyse de la ligne. Champs %d analysés au lieu de 4.\n", result);
            printf("\t\t  Ligne ignorée : %s\n", line);
        }
    }
    printf("\t\t  +------------+-----------------+-----------------+-----------------+\n");
    if (count >= 1 && countLocatairesExistants == 0 && countLocatairesNonAlloues == 0)
    {
        printf("\t\t  %d locataires créés avec succès.\n", count);
    }else if(count == 0 && countLocatairesExistants >= 1 && countLocatairesNonAlloues == 0)
    {
        printf("\t\t  %d locataires existent déja.\n", countLocatairesExistants);
    }else if(count == 0 && countLocatairesExistants == 0 && countLocatairesNonAlloues >= 1) 
    {
        printf("\t\t  %d locataires non alloues (Probleme du memoire).\n", countLocatairesNonAlloues);
    }else{
        printf("\t\t  %d locataires créés avec succès.\n", count);
        printf("\t\t  %d locataires existent déja.\n", countLocatairesExistants);
        printf("\t\t  %d locataires non alloues (Probleme du memoire).\n", countLocatairesNonAlloues);
    }
    fclose(file);
}
void ExtraireLocationInfoDuFichier(const char *filename)
{
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        printf("\t\t  Erreur : Impossible d'ouvrir le fichier '%s'.\n", filename);
        return;
    }
    printf("\t\t  Fichier '%s' ouvert avec succès !\n", filename);
    printf("\t\t  +------------+------------+-----------------+-----------------+\n");
    printf("\t\t  | %-10s | %-10s | %-15s | %-15s |\n", 
           "ID Log", "ID Loc", "Date Début", "Date Fin");
    printf("\t\t  +------------+------------+-----------------+-----------------+\n");

    char line[1024];
    int count = 0;
    int countLocationsExistants = 0;
    int countLocationsNonAlloues = 0;
    while (fgets(line, sizeof(line), file)) {
        Location location;
        char dateDebut[11];
        char dateFin[11];

        int result = sscanf(line, "%d %d %10s %10s",
                            &location.informationsDuLocation.idlog,
                            &location.informationsDuLocation.idloc,
                            dateDebut,
                            dateFin);

        if (result == 4) {
            location.informationsDuLocation.dateDebut = strdup(dateDebut);
            location.informationsDuLocation.dateFin = strdup(dateFin);

            int etat = NouvelleLocation(location.informationsDuLocation, false);
            if (etat == 1)
            {
                countLocationsExistants++;
                continue;
            }else if (etat == 2)
            {
                countLocationsNonAlloues++;
                continue;
            }else{    
                printf("\t\t  | %-10d | %-10d | %-15s | %-15s |\n",
                    location.informationsDuLocation.idlog,
                    location.informationsDuLocation.idloc,
                    location.informationsDuLocation.dateDebut,
                    location.informationsDuLocation.dateFin);
                count++;
            }
        } else {
            printf("\t\t  Erreur : Échec de l'analyse de la ligne. Champs %d analysés au lieu de 4.\n", result);
            printf("\t\t  Ligne ignorée : %s\n", line);
        }
    }
    printf("\t\t  +------------+------------+-----------------+-----------------+\n");
    if (count >= 1 && countLocationsExistants == 0 && countLocationsNonAlloues == 0)
    {
        printf("\t\t  %d locations créés avec succès.\n", count);
    }else if(count == 0 && countLocationsExistants >= 1 && countLocationsNonAlloues == 0)
    {
        printf("\t\t  %d locations existent déja.\n", countLocationsExistants);
    }else if(count == 0 && countLocationsExistants == 0 && countLocationsNonAlloues >= 1) 
    {
        printf("\t\t  %d locations non alloues (Probleme du memoire).\n", countLocationsNonAlloues);
    }else{
        printf("\t\t  %d locations créés avec succès.\n", count);
        printf("\t\t  %d locations existent déja.\n", countLocationsExistants);
        printf("\t\t  %d locations non alloues (Probleme du memoire).\n", countLocationsNonAlloues);
    }
    fclose(file);
}