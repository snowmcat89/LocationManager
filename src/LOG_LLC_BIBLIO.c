#include "LOG_LLC_BIBLIO.h"
#include "lists.h"
#include "table.h"

#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <limits.h>
#include <float.h>

#define TYPE_NUM 4

PLogement teteLogementActive = NULL;
PLocataire teteLocataireActive = NULL;
PLocation teteLocationActive = NULL;
PLoyer teteLoyer = NULL;

PLogement teteLogementArchive = NULL;
PLocataire teteLocataireArchive = NULL;
PLocation teteLocationArchive = NULL;

PLocation teteLocationTrieeStudio = NULL;
PLocation teteLocationTrieeF2 = NULL;
PLocation teteLocationTrieeF3 = NULL;
PLocation teteLocationTrieeF4 = NULL;

PAnneeDonnees teteAnneeDonnees = NULL;

int GetLocIDByLogID(int idlog)
{
	PLocation locationTemporaire = teteLocationActive;

	if (locationTemporaire != NULL && locationTemporaire->informationsDuLocation.idlog == idlog)
	{
		return locationTemporaire->informationsDuLocation.idloc;
	}

	while (locationTemporaire != NULL && locationTemporaire->informationsDuLocation.idlog != idlog)
	{
		locationTemporaire = locationTemporaire->locationSuivante;
	}

	if (locationTemporaire == NULL)
	{
		return -1;
	}

	return locationTemporaire->informationsDuLocation.idloc;
}
int GetLogIDByLocID(int idloc)
{
	PLocation locationTemporaire = teteLocationActive;

	if (locationTemporaire != NULL && locationTemporaire->informationsDuLocation.idloc == idloc)
	{
		return locationTemporaire->informationsDuLocation.idlog;
	}

	while (locationTemporaire != NULL && locationTemporaire->informationsDuLocation.idloc != idloc)
	{
		locationTemporaire = locationTemporaire->locationSuivante;
	}

	if (locationTemporaire == NULL)
	{
		return -1;
	}

	return locationTemporaire->informationsDuLocation.idlog;
}
float RetLogLoyerByLogID(int idlog)
{
    PLogement logementTemp = teteLogementActive;

    while (logementTemp != NULL)
    {
        if (logementTemp->informationsDuLogement.id == idlog)
        {
            return logementTemp->informationsDuLogement.loyer;
        }
        logementTemp = logementTemp->logementSuivant;
    }
    return -1;
}
char *RetLogTypeByLogID(int idlog)
{
	PLogement logementTemp = teteLogementActive;

    while (logementTemp != NULL)
    {
        if (logementTemp->informationsDuLogement.id == idlog)
        {
            return logementTemp->informationsDuLogement.typeDulogement;
        }
        logementTemp = logementTemp->logementSuivant;
    }
    return "Undefined";
}
void ModifierEtatOccupationLog(int idlog, bool occupe)
{
	PLogement logementTemporaire = teteLogementActive;

	if (logementTemporaire != NULL && logementTemporaire->informationsDuLogement.id == idlog)
	{
		teteLogementActive->informationsDuLogement.occupe = occupe;
		return;
	}

	while (logementTemporaire != NULL && logementTemporaire->informationsDuLogement.id != idlog)
	{
		logementTemporaire = logementTemporaire->logementSuivant;
	}

	if (logementTemporaire == NULL)
	{
		return;
	}

	logementTemporaire->informationsDuLogement.occupe = occupe;
	if (occupe == true)
	{
		printf("Le logement est devenu occupé !\n");
	}else{
		printf("Le logement est devenu non occupé !\n");
	}
}

void ListerLogements(PLogement teteLogement)
{
	if (teteLogementActive == NULL)
	{
		printf("Aucun logement disponible !\n");
		return;
	}

	PLogement dernierLogement = teteLogement;
	char *headers[] = {"ID", "Superficie (m²)", "Quartier", "Loyer (DA)", "Distance (m)", "Occupé?", "Type"};
	int columnCount = sizeof(headers)/sizeof(char *);
	Table table = NewTable(headers, columnCount);
	while (dernierLogement != NULL)
	{
		char id[10];
		char superficie[10];
		char loyer[10];
		char distanceACommune[10];

		itoa(dernierLogement->informationsDuLogement.id, id, 10);
		itoa(dernierLogement->informationsDuLogement.superficie, superficie, 10);
		sprintf(loyer, "%.2f", dernierLogement->informationsDuLogement.loyer);
		itoa(dernierLogement->informationsDuLogement.distanceACommune, distanceACommune, 10);

		char *row[] = {id,
					   superficie,
				       dernierLogement->informationsDuLogement.quartier,
					   loyer,
					   distanceACommune,
					   dernierLogement->informationsDuLogement.occupe ? "Oui": "Non",
					   dernierLogement->informationsDuLogement.typeDulogement};

		AddRow(&table, row);
		dernierLogement = dernierLogement->logementSuivant;
	}

	if (table.rowCount >= 1)
	{
		PrintTable(&table);
		printf("Nombre total des logements disponbiles: %d\n", table.rowCount);
		free(table.columnWidths);
	}else
	{
		printf("Aucun logement disponible !\n");
	}
}
void ListerLocataires(PLocataire teteLocataire)
{
	if (teteLocataireActive == NULL)
	{
		printf("Aucun locataire disponible !\n");
		return;
	}

	PLocataire dernierLocataire = teteLocataire;
	char *headers[] = {"ID", "Nom", "Prenom", "Telephone"};
	int columnCount = sizeof(headers)/sizeof(char *);
	Table table = NewTable(headers, columnCount);
	while (dernierLocataire != NULL)
	{
		char id[10];

		itoa(dernierLocataire->informationsDuLocataire.id, id, 10);

		char *row[] = {id,
					   dernierLocataire->informationsDuLocataire.nom,
					   dernierLocataire->informationsDuLocataire.prenom,
					   dernierLocataire->informationsDuLocataire.tel};

		AddRow(&table, row);
		dernierLocataire = dernierLocataire->locataireSuivant;
	}

	if (table.rowCount >= 1)
	{
		PrintTable(&table);
		printf("Nombre total des locataires disponbiles: %d\n", table.rowCount);
		free(table.columnWidths);
	}else
	{
		printf("Aucun locataire disponible !\n");
	}
}
void ListerLocations(PLocation teteLocation)
{
	if (teteLocationActive == NULL)
	{
		printf("Aucun location disponible !\n");
		return;
	}

	PLocation derniereLocation = teteLocation;
	char *headers[] = {"ID Logement", "ID Locataire", "Date debut", "Date fin"};
	int columnCount = sizeof(headers)/sizeof(char *);
	Table table = NewTable(headers, columnCount);
	while (derniereLocation != NULL)
	{
		char idlog[10];
		char idloc[10];

		itoa(derniereLocation->informationsDuLocation.idlog, idlog, 10);
		itoa(derniereLocation->informationsDuLocation.idloc, idloc, 10);

		char *row[] = {idlog,
					   idloc,
					   derniereLocation->informationsDuLocation.dateDebut,
					   derniereLocation->informationsDuLocation.dateFin};

		AddRow(&table, row);
		derniereLocation = derniereLocation->locationSuivante;
	}

	if (table.rowCount >= 1)
	{
		PrintTable(&table);
		printf("Nombre total des loations disponbiles: %d\n", table.rowCount);
		free(table.columnWidths);
	}else
	{
		printf("Aucune location disponible !\n");
	}
}

int NouveauLogement(InformationsDuLogment informationsDuLogement, bool output)
{
	PLogement nouveauLogement = (PLogement)malloc(sizeof(Logement));
	if (nouveauLogement == NULL)
	{
		if (output == true) printf("Erreur d'allocation de mémoire.\n");
		return 2;
	}

	PLogement currentLogement = teteLogementActive;
    while (currentLogement != NULL)
    {
        if (currentLogement->informationsDuLogement.id == informationsDuLogement.id)
        {
			if (output == true) printf("Le logement avec ID: %d existe déjà !\n", informationsDuLogement.id);
            free(nouveauLogement);
            return 1;
        }
        currentLogement = currentLogement->logementSuivant;
    }

	nouveauLogement->informationsDuLogement = informationsDuLogement;
	nouveauLogement->informationsDuLogement.loyer = RetLoyer(RetTypeNombre(informationsDuLogement.typeDulogement), informationsDuLogement.superficie);
	nouveauLogement->logementSuivant = NULL;

	if (teteLogementActive == NULL)
	{
		teteLogementActive = nouveauLogement;
	}
	else
	{
		PLogement dernierLogement = teteLogementActive;

		while (dernierLogement->logementSuivant != NULL)
		{
			dernierLogement = dernierLogement->logementSuivant;
		}
		dernierLogement->logementSuivant = nouveauLogement;
	}
	MettreAJourLogements(false, RetTypeNombre(nouveauLogement->informationsDuLogement.typeDulogement));
	if (output == true) printf("Logement ajouté au liste active avec succès : ID %d\n", informationsDuLogement.id);
	return 0;
}
int NouveauLocataire(InformationsDuLocataire informationsDuLocataire, bool output)
{
	PLocataire nouveauLocataire = (PLocataire)malloc(sizeof(Locataire));
	if (nouveauLocataire == NULL)
	{
		if (output == true) printf("Erreur d'allocation de mémoire.\n");
		return 2;
	}

	PLocataire currentLocataire = teteLocataireActive;
    while (currentLocataire != NULL)
    {
        if (currentLocataire->informationsDuLocataire.id == informationsDuLocataire.id)
        {
            if (output == true) printf("Le locataire avec ID: %d existe déjà !\n", informationsDuLocataire.id);
            free(nouveauLocataire);
            return 1;
        }
        currentLocataire = currentLocataire->locataireSuivant;
    }

	nouveauLocataire->informationsDuLocataire = informationsDuLocataire;
	nouveauLocataire->locataireSuivant = NULL;
	
	if (teteLocataireActive == NULL)
	{
		teteLocataireActive = nouveauLocataire;
	}
	else
	{
		PLocataire dernierLocataire = teteLocataireActive;
		while (dernierLocataire->locataireSuivant != NULL)
		{
			dernierLocataire = dernierLocataire->locataireSuivant;
		}
		dernierLocataire->locataireSuivant = nouveauLocataire;
	}
	if (output == true) printf("Locataire ajouté au liste active avec succès : ID %d\n", informationsDuLocataire.id);
	return 0;
}
int NouvelleLocation(InformationsDuLocation informationsDuLocation, bool output)
{
	PLocation nouvelleLocation = (PLocation)malloc(sizeof(Location));
	if (nouvelleLocation == NULL)
	{
		if (output == true) printf("Erreur d'allocation de mémoire.\n");
		return 2;
	}

	PLocation currentLocation = teteLocationActive;
    while (currentLocation != NULL)
    {
        if (currentLocation->informationsDuLocation.idlog == informationsDuLocation.idlog && currentLocation->informationsDuLocation.idloc == informationsDuLocation.idloc)
        {
            if (output == true) printf("La location avec ID Locataire: %d, ID Logement: %d existe déjà !\n", informationsDuLocation.idloc, informationsDuLocation.idlog);
            free(nouvelleLocation);
            return 1;
        }
        currentLocation = currentLocation->locationSuivante;
    }

	nouvelleLocation->informationsDuLocation = informationsDuLocation;
	nouvelleLocation->locationSuivante = NULL;
	
	if (teteLocationActive == NULL)
	{
		teteLocationActive = nouvelleLocation;
	}
	else
	{
		PLocation derniereLocation = teteLocationActive;
		while (derniereLocation->locationSuivante != NULL)
		{
			derniereLocation = derniereLocation->locationSuivante;
		}
		derniereLocation->locationSuivante = nouvelleLocation;
	}
	if (output == true) printf("Location ajoutée au liste active avec succès !\n");
	return 0;
}
int NouveauLoyer(float loyer, bool output)
{
	PLoyer nouveauLoyer = (PLoyer)malloc(sizeof(Loyer));

	if (nouveauLoyer == NULL)
	{
		if (output == true) printf("Erreur d'allocation de mémoire.\n");
		return 2;
	}

	PLoyer currentLoyer = teteLoyer;
    while (currentLoyer != NULL)
    {
        if (currentLoyer->loyer == loyer)
        {
            if (output == true) printf("Le loyer %.2f existe déjà !\n", loyer);
            free(nouveauLoyer);
            return 1;
        }
        currentLoyer = currentLoyer->loyerSuivant;
    }

	nouveauLoyer->loyer = loyer;
	nouveauLoyer->loyerSuivant = NULL;

	if (teteLoyer == NULL)
	{
		teteLoyer = nouveauLoyer;
	}else
	{
		PLoyer dernierLoyer = teteLoyer;

		while (dernierLoyer->loyerSuivant != NULL)
		{
			dernierLoyer = dernierLoyer->loyerSuivant;
		}
		dernierLoyer->loyerSuivant = nouveauLoyer;
	}
	return 0;

	if (output == true) printf("Loyer ajoutée au liste avec succès !\n");
}

void SupprimerLogement(int idlog, bool output)
{
	PLogement logementTemporaire = teteLogementActive, logementPrecedent = NULL;

	if (logementTemporaire != NULL && logementTemporaire->informationsDuLogement.id == idlog)
	{
		teteLogementActive = logementTemporaire->logementSuivant;
		MettreAJourLogements(true, RetTypeNombre(logementTemporaire->informationsDuLogement.typeDulogement));
		free(logementTemporaire);
		if (output == true) printf("Le logement est supprimé avec succès !\n");
		return;
	}

	while (logementTemporaire != NULL && logementTemporaire->informationsDuLogement.id != idlog)
	{
		logementPrecedent = logementTemporaire;
		logementTemporaire = logementTemporaire->logementSuivant;
	}

	if (logementTemporaire == NULL)
	{
		if (output == true) printf("Le logement n'est pas trouvé !\n");
		return;
	}

	logementPrecedent->logementSuivant = logementTemporaire->logementSuivant;
	AjouterLogementAListeArchive(logementTemporaire, true);
	MettreAJourLogements(true, RetTypeNombre(logementTemporaire->informationsDuLogement.typeDulogement));
	free(logementTemporaire);
	if (output == true) printf("Le logement est supprimé avec succès !\n");
}
void SupprimerLogementEx(int idlog, bool output)
{
	int idloc = GetLocIDByLogID(idlog);
	SupprimerLogement(idlog, true);
	SupprimerLocataire(idloc, output);
	SupprimerLocation(idlog, idloc, output);
}
void SupprimerLocataire(int idloc, bool output)
{
	PLocataire locataireTemporaire = teteLocataireActive, locatairePrecedent = NULL;

	if (locataireTemporaire != NULL && locataireTemporaire->informationsDuLocataire.id == idloc)
	{
		teteLocataireActive = locataireTemporaire->locataireSuivant;
		free(locataireTemporaire);
		if (output == true) printf("Le locataire est supprimé avec succès !\n");
		return;
	}

	while (locataireTemporaire != NULL && locataireTemporaire->informationsDuLocataire.id != idloc)
	{
		locatairePrecedent = locataireTemporaire;
		locataireTemporaire = locataireTemporaire->locataireSuivant;
	}

	if (locataireTemporaire == NULL)
	{
		if (output == true) printf("Le locataire n'est pas trouvé !\n");
		return;
	}

	locatairePrecedent->locataireSuivant = locataireTemporaire->locataireSuivant;
	AjouterLocataireAListeArchive(locataireTemporaire, true);
	free(locataireTemporaire);
	if (output == true) printf("Le locataire est supprimé avec succès !\n");
}
void SupprimerLocataireEx(int idloc, bool output)
{
	int idlog = GetLogIDByLocID(idloc);
	SupprimerLocataire(idloc, true);
	SupprimerLocation(idlog, idloc, output);
	ModifierEtatOccupationLog(idlog, false);
}
void SupprimerLocation(int idlog, int idloc, bool output)
{
	PLocation locationTemporaire = teteLocationActive, locationPrecedente = NULL;

	if (locationTemporaire != NULL && (locationTemporaire->informationsDuLocation.idlog == idlog && locationTemporaire->informationsDuLocation.idloc == idloc))
	{
		teteLocationActive = teteLocationActive->locationSuivante;
		free(locationTemporaire);
		if (output == true) printf("La location est supprimé avec succès !\n");
		return;
	}

	while (locationTemporaire != NULL && (locationTemporaire->informationsDuLocation.idlog != idlog && locationTemporaire->informationsDuLocation.idloc != idloc))
	{
		locationPrecedente = locationTemporaire;
		locationTemporaire = locationTemporaire->locationSuivante;
	}

	if (locationTemporaire == NULL)
	{
		if (output == true) printf("La location n'est pas trouvé !\n");
		return;
	}

	locationPrecedente->locationSuivante = locationTemporaire->locationSuivante;
	AjouterLocationAListeArchive(locationTemporaire, true);
	free(locationTemporaire);
	if (output == true) printf("La location est supprimé avec succès !\n");
}
void SupprimerLocationEx(int idlog, bool output)
{
	int idloc = GetLocIDByLogID(idlog);
	SupprimerLocation(idlog, idloc, true);
	SupprimerLocataire(idloc, output);
	ModifierEtatOccupationLog(idlog, false);
}

void FreeLogementListe(PLogement *tete)
{
    if (!tete || !*tete) return;

    PLogement current = *tete;
    PLogement suivant;

    while (current != NULL) {
        suivant = current->logementSuivant;

        free(current->informationsDuLogement.quartier);
        free(current->informationsDuLogement.typeDulogement);

        free(current);
        current = suivant;
    }

    suivant = NULL;
}
void FreeLocataireListe(PLocataire *tete)
{
    if (!tete || !*tete) return;

    PLocataire current = *tete;
    PLocataire suivant;

    while (current != NULL) {
        suivant = current->locataireSuivant;

        free(current->informationsDuLocataire.nom);
        free(current->informationsDuLocataire.prenom);
        free(current->informationsDuLocataire.tel);

        free(current);
        current = suivant;
    }

    suivant = NULL;
}
void FreeLocationListe(PLocation *tete)
{
    if (!tete || !*tete) return;

    PLocation current = *tete;
    PLocation suivant;

    while (current != NULL) {
        suivant = current->locationSuivante;

        free(current->informationsDuLocation.dateDebut);
        free(current->informationsDuLocation.dateFin);

        free(current);
        current = suivant;
    }

    suivant = NULL;
}
void FreeLoyerListe(PLoyer *tete)
{
    if (!tete || !*tete) return;

    PLoyer current = *tete;
    PLoyer suivant;

    while (current != NULL) {
        suivant = current->loyerSuivant;

        free(current);
        current = suivant;
    }

    suivant = NULL;
}
void FreeAnneesDonnesListe(PAnneeDonnees *tete)
{
    if (!tete || !*tete) return;

    PAnneeDonnees current = *tete;
    PAnneeDonnees suivant;

    while (current != NULL) {
        suivant = current->anneeSuivante;

        free(current);
        current = suivant;
    }

    suivant = NULL;
}
void FreeLinkedListes()
{
	FreeLogementListe(&teteLogementActive);
	FreeLogementListe(&teteLogementArchive);
	FreeLocataireListe(&teteLocataireActive);
	FreeLocataireListe(&teteLocataireArchive);
	FreeLocationListe(&teteLocationActive);
	FreeLocationListe(&teteLocationArchive);
	FreeLocationListe(&teteLocationTrieeStudio);
	FreeLocationListe(&teteLocationTrieeF2);
	FreeLocationListe(&teteLocationTrieeF3);
	FreeLocationListe(&teteLocationTrieeF4);
	FreeLoyerListe(&teteLoyer);
	FreeAnneesDonnesListe(&teteAnneeDonnees);
}

void AjouterLogementAListeArchive(PLogement logement, bool output)
{
	PLogement nouveauLogement = (PLogement)malloc(sizeof(Logement));

	if (nouveauLogement == NULL)
	{
		if (output == true) printf("Erreur d'allocation de mémoire.\n");
		return;
	}

	PLogement currentLogement = teteLogementArchive;
    while (currentLogement != NULL)
    {
        if (currentLogement->informationsDuLogement.id == logement->informationsDuLogement.id)
        {
            if (output == true) printf("Le logement avec ID: %d existe déjà dans la liste archive !\n", logement->informationsDuLogement.id);
            free(nouveauLogement);
            return;
        }
        currentLogement = currentLogement->logementSuivant;
    }

	nouveauLogement->informationsDuLogement = logement->informationsDuLogement;
	nouveauLogement->logementSuivant = NULL;

	if (teteLogementArchive == NULL)
	{
		teteLogementArchive = nouveauLogement;
	}else{
		PLogement dernierLogement = teteLogementArchive;
		while (dernierLogement->logementSuivant != NULL)
		{
			if (dernierLogement->informationsDuLogement.id == logement->informationsDuLogement.id)
			{
				if (output == true) printf("Le logement avec ID: %d, existe déjà !\n", dernierLogement->informationsDuLogement.id);
				return;
			}
			dernierLogement = dernierLogement->logementSuivant;
		}
		dernierLogement->logementSuivant = nouveauLogement;
	}
	if (output == true) printf("Logement ajouté au liste archive avec succès : ID %d\n", logement->informationsDuLogement.id);
}
void AjouterLocataireAListeArchive(PLocataire locataire, bool output)
{
	PLocataire nouveauLocataire = (PLocataire)malloc(sizeof(Locataire));

	if (nouveauLocataire == NULL)
	{
		if (output == true) printf("Erreur d'allocation de mémoire.\n");
		return;
	}

	PLocataire currentLocataire = teteLocataireArchive;
    while (currentLocataire != NULL)
    {
        if (currentLocataire->informationsDuLocataire.id == locataire->informationsDuLocataire.id)
        {
            if (output == true) printf("Le locataire avec ID: %d existe déjà dans la liste archive !\n", locataire->informationsDuLocataire.id);
            free(nouveauLocataire);
            return;
        }
        currentLocataire = currentLocataire->locataireSuivant;
    }

	nouveauLocataire->informationsDuLocataire = locataire->informationsDuLocataire;
	nouveauLocataire->locataireSuivant = NULL;

	if (teteLocataireArchive == NULL)
	{
		teteLocataireArchive = nouveauLocataire;
	}else{
		PLocataire dernierLocataire = teteLocataireArchive;
		while (dernierLocataire->locataireSuivant != NULL)
		{
			if (dernierLocataire->informationsDuLocataire.id == locataire->informationsDuLocataire.id)
			{
				if (output == true) printf("Le locataire avec ID: %d, existe déjà !\n", dernierLocataire->informationsDuLocataire.id);
				return;
			}
			dernierLocataire = dernierLocataire->locataireSuivant;
		}
		dernierLocataire->locataireSuivant = nouveauLocataire;
	}
	if (output == true) printf("Locataire ajouté au liste archive avec succès !\n", locataire->informationsDuLocataire.id);
}
void AjouterLocationAListeArchive(PLocation location, bool output)
{
	PLocation nouvelleLocation = (PLocation)malloc(sizeof(Location));

	if (nouvelleLocation == NULL)
	{
		if (output == true) printf("Erreur d'allocation de mémoire.\n");
		return;
	}

	PLocation currentLocation = teteLocationArchive;
    while (currentLocation != NULL)
    {
        if ((currentLocation->informationsDuLocation.idlog == location->informationsDuLocation.idlog) && (currentLocation->informationsDuLocation.idloc == location->informationsDuLocation.idloc))
        {
            if (output == true) printf("La location avec ID Locataire: %d, ID Logement: %d existe déjà dans la liste archive !\n", location->informationsDuLocation.idloc, location->informationsDuLocation.idlog);
            free(nouvelleLocation);
            return;
        }
        currentLocation = currentLocation->locationSuivante;
    }

	nouvelleLocation->informationsDuLocation = location->informationsDuLocation;
	nouvelleLocation->locationSuivante = NULL;

	if (teteLocationActive == NULL)
	{
		teteLocationArchive = nouvelleLocation;
	}else{
		PLocation derniereLocation = teteLocationArchive;
		while (derniereLocation->locationSuivante != NULL)
		{
			if (derniereLocation->informationsDuLocation.idloc == location->informationsDuLocation.idloc && derniereLocation->informationsDuLocation.idloc == location->informationsDuLocation.idlog)
			{
				if (output == true) printf("La location existe déjà !\n");
				return;
			}
			derniereLocation = derniereLocation->locationSuivante;
		}
		derniereLocation->locationSuivante = nouvelleLocation;
	}
	if (output == true) printf("Location ajoutée au liste archive avec succès !\n");
}
void AjouterLocationAListeTrieeType(PLocation location, PLocation *teteLocationGereeType, bool output)
{
    PLocation nouvelleLocation = (PLocation)malloc(sizeof(Location));
    if (nouvelleLocation == NULL)
    {
        if (output == true) printf("Erreur d'allocation de mémoire.\n");
        return;
    }

	PLocation currentLocation = *teteLocationGereeType;
    while (currentLocation != NULL)
    {
        if ((currentLocation->informationsDuLocation.idlog == location->informationsDuLocation.idlog) && (currentLocation->informationsDuLocation.idloc == location->informationsDuLocation.idloc))
        {
            if (output == true) printf("La location avec ID Locataire: %d, ID Logement: %d existe déjà !\n", location->informationsDuLocation.idloc, location->informationsDuLocation.idlog);
            free(nouvelleLocation);
            return;
        }
        currentLocation = currentLocation->locationSuivante;
    }

    nouvelleLocation->informationsDuLocation = location->informationsDuLocation;
    nouvelleLocation->locationSuivante = NULL;

    if (*teteLocationGereeType == NULL)
    {
        *teteLocationGereeType = nouvelleLocation;
    }
    else
    {
        PLocation derniereLocation = *teteLocationGereeType;
        while (derniereLocation->locationSuivante != NULL)
        {
            derniereLocation = derniereLocation->locationSuivante;
        }
        derniereLocation->locationSuivante = nouvelleLocation;
    }
    if (output == true) printf("Location ajoutée au liste triée avec succès !\n");
}
void AjouterLogementAListeTriee(PLogement logement, PLogement *teteLogement, bool output)
{
    PLogement nouveauLogement = (PLogement)malloc(sizeof(Logement));
    if (nouveauLogement == NULL)
    {
        if (output == true) printf("Erreur d'allocation de mémoire.\n");
        return;
    }

	
	PLogement currentLogement = teteLogementArchive;
    while (currentLogement != NULL)
    {
        if (currentLogement->informationsDuLogement.id == logement->informationsDuLogement.id)
        {
            if (output == true) printf("Le logement avec ID: %d existe déjà dans la liste archive  !\n", logement->informationsDuLogement.id);
            free(nouveauLogement);
            return;
        }
        currentLogement = currentLogement->logementSuivant;
    }

    nouveauLogement->informationsDuLogement = logement->informationsDuLogement;
    nouveauLogement->logementSuivant = NULL;

    if (*teteLogement == NULL)
    {
        *teteLogement = nouveauLogement;
    }
    else
    {
        PLogement dernierLogement = *teteLogement;
        while (dernierLogement->logementSuivant != NULL)
        {
            dernierLogement = dernierLogement->logementSuivant;
        }
        dernierLogement->logementSuivant = nouveauLogement;
    }
    if (output == true) printf("Logement ajoutée au liste triée temporaire avec succès !\n");
}

void ListerLogementsOccupesEtLibres(char *date)
{
	if (teteLogementActive == NULL)
	{
		printf("Aucun logement disponible.\n");
		return;
	}

	char *headers[] = {"ID", "Occupé", "Superficie (m²)", "Quartier", "Distance", "Loyer (DA)", "DateDuLiberation"};
	int columnCount = sizeof(headers)/sizeof(char *);
	Table table = NewTable(headers, columnCount);
	PLogement dernierLogement = teteLogementActive;
	if (dernierLogement == NULL)
	{
		printf("Aucun logement disponible !\n");
		return;
	}

	while (dernierLogement != NULL)
	{
		if (dernierLogement->informationsDuLogement.occupe == true)
		{
			PLocation derniereLocation = teteLocationActive;
			if (derniereLocation == NULL)
			{
				printf("Aucune location disponible !\n");
				return;
			}
			while (derniereLocation != NULL)
			{
				if (derniereLocation->informationsDuLocation.idlog == dernierLogement->informationsDuLogement.id)
				{
                    Date date1 = StringToDate(derniereLocation->informationsDuLocation.dateFin);
					Date date2 = StringToDate(date);
					if ((date1.annee != 0 && date1.mois != 0 && date1.jour != 0) && (date2.annee != 0 && date2.mois != 0 && date2.jour != 0))
					{
						if ((date1.annee == date2.annee && date1.mois == date2.mois && date1.jour == date2.jour) || ((date1.annee - date2.annee)*365 + (date1.mois - date2.mois)*30 + (date1.jour - date2.jour)) < 0)
						{
							char idStr[10];
							char superficieStr[10];
							char loyerStr[10];
							char distanceStr[10];
							itoa(dernierLogement->informationsDuLogement.id, idStr, 10);
							itoa(dernierLogement->informationsDuLogement.superficie, superficieStr, 10);
							itoa(dernierLogement->informationsDuLogement.distanceACommune, distanceStr, 10);
							sprintf(loyerStr, "%.2f", dernierLogement->informationsDuLogement.loyer);
							
							char *row[] = {
								idStr,
								dernierLogement->informationsDuLogement.occupe ? "Oui" : "Non",
								superficieStr,
								dernierLogement->informationsDuLogement.quartier,
								distanceStr,
								loyerStr,
								derniereLocation->informationsDuLocation.dateFin
							};
							AddRow(&table, row);
						}
					}else
					{
						printf("Veuillez saisir une date valide, à la forme: JJ/MM//AAAAA, JJ<=31/MM<=12!\n");
						return;
					}
				}
				derniereLocation = derniereLocation->locationSuivante;
			}
		}
		dernierLogement = dernierLogement->logementSuivant;
	}

	if (table.rowCount >= 1)
	{
		PrintTable(&table);
		printf("Nombre total des resultats trouvés: %d", table.rowCount);
	}else{
		printf("Aucun resultat trouvé !\n");
	}
	free(table.columnWidths);
}

void TrierLoyers()
{
	if (teteLoyer == NULL || teteLoyer->loyerSuivant == NULL)
	{
		return;
	}

	PLoyer dernierLoyer = teteLoyer;
	while (dernierLoyer != NULL)
	{
		PLoyer loyerTemporaire = teteLoyer;
		while (loyerTemporaire->loyerSuivant != NULL)
		{
			if (dernierLoyer->loyer > loyerTemporaire->loyer)
			{
				float temp = dernierLoyer->loyer;
				dernierLoyer->loyer = loyerTemporaire->loyer;
				loyerTemporaire->loyer = temp;
			}
			loyerTemporaire = loyerTemporaire->loyerSuivant;
		}
		dernierLoyer = dernierLoyer->loyerSuivant;
	}
}
PLocation FusionnerListesLocationsTriees()
{
    PLocation teteLocationTemporaire = NULL;

    PLocation derniereLocationStudio = teteLocationTrieeStudio;
    while (derniereLocationStudio != NULL)
    {
        AjouterLocationAListeTrieeType(derniereLocationStudio, &teteLocationTemporaire, false);
        derniereLocationStudio = derniereLocationStudio->locationSuivante;
    }

    PLocation derniereLocationF2 = teteLocationTrieeF2;
    while (derniereLocationF2 != NULL)
    {
        AjouterLocationAListeTrieeType(derniereLocationF2, &teteLocationTemporaire, false);
        derniereLocationF2 = derniereLocationF2->locationSuivante;
    }

    PLocation derniereLocationF3 = teteLocationTrieeF3;
    while (derniereLocationF3 != NULL)
    {
        AjouterLocationAListeTrieeType(derniereLocationF3, &teteLocationTemporaire, false);
        derniereLocationF3 = derniereLocationF3->locationSuivante;
    }

    PLocation derniereLocationF4 = teteLocationTrieeF4;
    while (derniereLocationF4 != NULL)
    {
        AjouterLocationAListeTrieeType(derniereLocationF4, &teteLocationTemporaire, false);
        derniereLocationF4 = derniereLocationF4->locationSuivante;
    }

    teteLocationTemporaire = TrierListeParLoyer(teteLocationTemporaire);
	return teteLocationTemporaire;
}
PLocation TrierListeParLoyer(PLocation teteLocation)
{
    if (teteLocation == NULL || teteLocation->locationSuivante == NULL)
    {
        return teteLocation;
    }

    bool swapped;
    PLocation current;
    PLocation previous = NULL;

    do
    {
        swapped = false;
        current = teteLocation;

        while (current->locationSuivante != previous)
        {
            float loyer1 = RetLogLoyerByLogID(current->informationsDuLocation.idlog);
            float loyer2 = RetLogLoyerByLogID(current->locationSuivante->informationsDuLocation.idlog);

            if (loyer1 < loyer2)
            {
                InformationsDuLocation temp = current->informationsDuLocation;
                current->informationsDuLocation = current->locationSuivante->informationsDuLocation;
                current->locationSuivante->informationsDuLocation = temp;

                swapped = true;
            }
            current = current->locationSuivante;
        }
        previous = current;
    } while (swapped);

    return teteLocation;
}
void TrierLocationsParLoyer()
{
	if (teteLocationActive == NULL)
	{
		printf("Aucune location disponible !\n");
		return;
	}

	for (int i = 1; i <= TYPE_NUM; i++)
	{
		teteLoyer = NULL;

		PLogement dernierLogement = teteLogementActive;
		while (dernierLogement != NULL)
		{
			if (strcmp(dernierLogement->informationsDuLogement.typeDulogement, RetTypeLogement(i)) == 0)
				NouveauLoyer(dernierLogement->informationsDuLogement.loyer, false);
			dernierLogement = dernierLogement->logementSuivant;
		}

		if (teteLoyer == NULL)
		{
			printf("Aucun logement du type: %s\n", RetTypeLogement(i));
			continue;
		}

		TrierLoyers();

		PLoyer dernierLoyer = teteLoyer;
		while (dernierLoyer != NULL)
		{
			PLogement dernierLogement = teteLogementActive;
			while (dernierLogement != NULL)
			{
				if (dernierLogement->informationsDuLogement.loyer == dernierLoyer->loyer)
				{
					PLocation derniereLocation = teteLocationActive;
					while (derniereLocation != NULL)
					{
						if (derniereLocation->informationsDuLocation.idlog == dernierLogement->informationsDuLogement.id)
						{
							if (strcmp(dernierLogement->informationsDuLogement.typeDulogement, "STUDIO") == 0) {
								AjouterLocationAListeTrieeType(derniereLocation, &teteLocationTrieeStudio, false);
							} else if (strcmp(dernierLogement->informationsDuLogement.typeDulogement, "F2") == 0) {
								AjouterLocationAListeTrieeType(derniereLocation, &teteLocationTrieeF2, false);
							} else if (strcmp(dernierLogement->informationsDuLogement.typeDulogement, "F3") == 0) {
								AjouterLocationAListeTrieeType(derniereLocation, &teteLocationTrieeF3, false);
							} else if (strcmp(dernierLogement->informationsDuLogement.typeDulogement, "F4") == 0) {
								AjouterLocationAListeTrieeType(derniereLocation, &teteLocationTrieeF4, false);
							}
						}
						derniereLocation = derniereLocation->locationSuivante;
					}
				}
				dernierLogement = dernierLogement->logementSuivant;
			}
			dernierLoyer = dernierLoyer->loyerSuivant;
		}
	}

	PLocation teteLocationTriee = FusionnerListesLocationsTriees();
	teteLocationActive = teteLocationTriee;

	printf("La liste initiale (teteLocationActive) après tri (Avec le loyer et le type de logement):\n");
	char *headers[] = {"ID Logement", "ID Locatiare", "Date debut", "Date Fin", "Loyer (DA)", "Type"};
	int columnCount = sizeof(headers)/sizeof(char *);
	Table table = NewTable(headers, columnCount);
	PLocation derniereLocation = teteLocationActive;
	while (derniereLocation != NULL)
	{
		char idlog[10];
		char idloc[10];
		char loyer[10];

		itoa(derniereLocation->informationsDuLocation.idlog, idlog, 10);
		itoa(derniereLocation->informationsDuLocation.idloc, idloc, 10);
		sprintf(loyer, "%.2f", RetLogLoyerByLogID(derniereLocation->informationsDuLocation.idlog));
		char *row[] = {idlog,
					  idloc,
					  derniereLocation->informationsDuLocation.dateDebut,
					  derniereLocation->informationsDuLocation.dateFin,
					  loyer,
					  RetLogTypeByLogID(derniereLocation->informationsDuLocation.idlog)
					};

		AddRow(&table, row);
		derniereLocation = derniereLocation->locationSuivante;
	}

	PrintTable(&table);
	free(table.columnWidths);
}

void ListerLocatairesParTypeEtSuperficie()
{
	if (teteLocataireActive == NULL)
	{
		printf("Aucun locataire disponible !\n");
		return;
	}

	if (teteLogementActive == NULL)
	{
		printf("Aucun logement disponible !\n");
		return;
	}
	for (int i = 1; i <= TYPE_NUM; i++)
	{
		char *headers[] = {"ID", "Nom", "Prenom", "Telephone", "Type", "Superficie (m²)"};
		int columnCount = sizeof(headers)/sizeof(char *);
		Table table = NewTable(headers, columnCount);
		PLogement dernierLogement = teteLogementActive;
		while (dernierLogement != NULL)
		{
			if (strcmp(dernierLogement->informationsDuLogement.typeDulogement, RetTypeLogement(i)) == 0)
			{
				if (dernierLogement->informationsDuLogement.superficie > RetSuperficieMoyenne(dernierLogement->informationsDuLogement.typeDulogement))
				{
					PLocataire dernierLocataire = teteLocataireActive;
					while (dernierLocataire != NULL)
					{
						if (dernierLocataire->informationsDuLocataire.id == GetLocIDByLogID(dernierLogement->informationsDuLogement.id))
						{
							char id[10];
							char superficie[10];

							itoa(dernierLocataire->informationsDuLocataire.id, id, 10);
							itoa(dernierLogement->informationsDuLogement.superficie, superficie, 10);

							char *row[] = {id,
											dernierLocataire->informationsDuLocataire.nom,
											dernierLocataire->informationsDuLocataire.prenom,
											dernierLocataire->informationsDuLocataire.tel,
											dernierLogement->informationsDuLogement.typeDulogement,
											superficie
							};

							AddRow(&table, row);
						}
						dernierLocataire = dernierLocataire->locataireSuivant;
					}
				}
			}
			dernierLogement = dernierLogement->logementSuivant;
		}

		printf("***********Type du logement: %s***********\n", RetTypeLogement(i));
		if (table.rowCount > 0)
		{
			PrintTable(&table);
			free(table.columnWidths);
		}else{
			printf("Aucun logement occupés du type: %s\n", RetTypeLogement(i));
		}
	}
}
void ChercherLogementsProchesEtAbordables() 
{
    if (teteLogementActive == NULL) {
        printf("Aucun logement disponible.\n");
        return;
    }

    float totalDistance = 0, totalLoyer = 0;
    int count = 0;
    PLogement current = teteLogementActive;

    while (current != NULL) {
        totalDistance += current->informationsDuLogement.distanceACommune;
        totalLoyer += current->informationsDuLogement.loyer;
        count++;
        current = current->logementSuivant;
    }

    float averageDistance = totalDistance / count;
    float averageLoyer = totalLoyer / count;

    printf("Moyenne: Distance = %.2f km, Loyer = %.2f DA\n", averageDistance, averageLoyer);

    printf("Logements proches (<= %.2f km) ET abordables (<= %.2f DA):\n", averageDistance, averageLoyer);
    current = teteLogementActive;
	PLogement teteLogementTemporaire = NULL;
    int results = 0;

    while (current != NULL) {
        if (current->informationsDuLogement.distanceACommune <= averageDistance&&
            current->informationsDuLogement.loyer <= averageLoyer) {
			printf("%d\n", current->informationsDuLogement.id);
			AjouterLogementAListeTriee(current, &teteLogementTemporaire, false);
            results++;
		}
        current = current->logementSuivant;
    }

    if (results == 0 || results == 1) {
        printf("Aucun résultat. Élargissement des critères (<= +10%% des moyennes)...\n");
        float relaxedAverageDistance = 1.1 * averageDistance;
        float relaxedAverageLoyer = 1.1 * averageLoyer;
        current = teteLogementActive;
		
        while (current != NULL) {
            if (current->informationsDuLogement.distanceACommune <= relaxedAverageDistance &&
                current->informationsDuLogement.loyer <= relaxedAverageLoyer) {
				AjouterLogementAListeTriee(current, &teteLogementTemporaire, false);
				results++;
            }
            current = current->logementSuivant;
        }
    }

	ListerLogements(teteLogementTemporaire);
    printf("Total trouvé: %d logement(s)\n", results);
}

void TrierAnnees()
{
	if (teteLoyer == NULL || teteLoyer->loyerSuivant == NULL)
	{
		return;
	}

	PAnneeDonnees derniereAnnee = teteAnneeDonnees;
	while (derniereAnnee != NULL)
	{
		PAnneeDonnees anneeTemporaire = teteAnneeDonnees;
		while (anneeTemporaire->anneeSuivante != NULL)
		{
			if (derniereAnnee->annee > anneeTemporaire->annee)
			{
				float tempAnnee = derniereAnnee->annee;
				PQuartierCount tempQuartiers = derniereAnnee->quartiers;
				derniereAnnee->annee = anneeTemporaire->annee;
				derniereAnnee->quartiers = anneeTemporaire->quartiers;
				anneeTemporaire->annee = tempAnnee;
				anneeTemporaire->quartiers = tempQuartiers;
			}
			anneeTemporaire = anneeTemporaire->anneeSuivante;
		}
		derniereAnnee = derniereAnnee->anneeSuivante;
	}
}
PAnneeDonnees TrouverOuCreerUneAnnee(PAnneeDonnees *teteAnneeDonnees, int annee)
{
    PAnneeDonnees currentAnnee = *teteAnneeDonnees;

    while (currentAnnee != NULL) {
        if (currentAnnee->annee == annee) {
            return currentAnnee;
        }
        if (currentAnnee->anneeSuivante == NULL) {
            break;
        }
        currentAnnee = currentAnnee->anneeSuivante;
    }

    PAnneeDonnees nouvelleAnnee = (PAnneeDonnees)malloc(sizeof(AnneeDonnees));
    if (nouvelleAnnee == NULL) {
        printf("Erreur d'allocation de mémoire.\n");
        return NULL;
    }
    nouvelleAnnee->annee = annee;
    nouvelleAnnee->quartiers = NULL;
    nouvelleAnnee->anneeSuivante = NULL;

    if (currentAnnee == NULL) {
        *teteAnneeDonnees = nouvelleAnnee;
    } else {
		PAnneeDonnees derniereAnnee = *teteAnneeDonnees;

		while (derniereAnnee->anneeSuivante != NULL)
		{
			derniereAnnee = derniereAnnee->anneeSuivante;
		}
		derniereAnnee->anneeSuivante = nouvelleAnnee;
		
	}

    return nouvelleAnnee;
}
PQuartierCount TrouverOuCreerUnQuartier(PQuartierCount *teteQuartierCount, const char *quartier)
{
    PQuartierCount currentQuartier = *teteQuartierCount;

    while (currentQuartier != NULL) {
        if (strcmp(currentQuartier->quartier, quartier) == 0) {
            return currentQuartier;
        }
        if (currentQuartier->quartierSuivant == NULL) {
            break;
        }
        currentQuartier = currentQuartier->quartierSuivant;
    }

    PQuartierCount nouveauQuartier = (PQuartierCount)malloc(sizeof(QuartierCount));
    if (nouveauQuartier == NULL) {
        printf("Erreur d'allocation de mémoire pour le quartier %s.\n", quartier);
        return NULL;
    }
	strncpy(nouveauQuartier->quartier, quartier, sizeof(nouveauQuartier->quartier) - 1);
	nouveauQuartier->quartier[sizeof(nouveauQuartier->quartier) - 1] = '\0';
    nouveauQuartier->count = 0;
    nouveauQuartier->quartierSuivant = NULL;

    if (currentQuartier == NULL) {
        *teteQuartierCount = nouveauQuartier;
    } else {
		PQuartierCount dernierQuartier = *teteQuartierCount;

		while (dernierQuartier->quartierSuivant != NULL)
		{
			dernierQuartier = dernierQuartier->quartierSuivant;
		}
		dernierQuartier->quartierSuivant = nouveauQuartier;
		
	}

    return nouveauQuartier;
}
void ConsulterHistoriqueLogementsEtLocationsParAnnee()
{
	if (teteLogementActive == NULL)
	{
		printf("Aucun logement disponible !\n");
	}

    if (teteLocationActive == NULL) {
        printf("Aucune location disponible !\n");
        return;
    }


    PLocation currentLocation = teteLocationActive;
    while (currentLocation != NULL) {
        Date dateDebut = StringToDate(currentLocation->informationsDuLocation.dateDebut);
        int annee = dateDebut.annee;

        PAnneeDonnees anneeDonnees = TrouverOuCreerUneAnnee(&teteAnneeDonnees, annee);

        PLogement logement = teteLogementActive;
        while (logement != NULL) {
            if (logement->informationsDuLogement.id == currentLocation->informationsDuLocation.idlog) {
                PQuartierCount quartierEntry = TrouverOuCreerUnQuartier(&anneeDonnees->quartiers, logement->informationsDuLogement.quartier);
                quartierEntry->count++;
                break;
            }
            logement = logement->logementSuivant;
        }

        currentLocation = currentLocation->locationSuivante;
    }
	
	TrierAnnees();

    PAnneeDonnees currentAnnee = teteAnneeDonnees;
    while (currentAnnee != NULL) {
		printf("---------------------------------------------------------------\n");
        printf("**************************Année:%d**************************\n", currentAnnee->annee);
		printf("Logements loués par quartier:\n");
        PQuartierCount currentQuartier = currentAnnee->quartiers;
        while (currentQuartier != NULL) {
            printf("\t- Quartier [%s]: %d logement(s)\n", currentQuartier->quartier, currentQuartier->count);
            currentQuartier = currentQuartier->quartierSuivant;
        }

		printf("\nLocations par type de logement:\n");
		for (int i = 1; i <= TYPE_NUM; i++)
		{
			int count = 0;
			PLogement dernierLogement = teteLogementActive;
			while (dernierLogement != NULL)
			{
				if (strcmp(dernierLogement->informationsDuLogement.typeDulogement, RetTypeLogement(i)) == 0)
				{
					PLocation derniereLocation = teteLocationActive;
					while (derniereLocation != NULL)
					{
						Date dateDebut = StringToDate(derniereLocation->informationsDuLocation.dateDebut);
						int annee = dateDebut.annee;
						if (annee == currentAnnee->annee)
						{
							if (dernierLogement->informationsDuLogement.id == derniereLocation->informationsDuLocation.idlog)
							{
								count++;
							}
						}
						derniereLocation = derniereLocation->locationSuivante;
					}
				}
				dernierLogement = dernierLogement->logementSuivant;
			}
			printf("\t- %s: %d locations\n", RetTypeLogement(i), count);
		}
        currentAnnee = currentAnnee->anneeSuivante;
    }
}
