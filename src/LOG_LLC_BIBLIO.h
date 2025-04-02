#ifndef LOG_LLC_BIBLIO_H_
#define LOG_LLC_BIBLIO_H_

#include "lists.h"

#include <stdbool.h>

typedef struct Logement
{
    InformationsDuLogment informationsDuLogement; // Informations du logement
    struct Logement *logementSuivant; // Pointeur vers le noeud suivant
} Logement, *PLogement;
typedef struct Locataire
{
    InformationsDuLocataire informationsDuLocataire;
    struct Locataire *locataireSuivant;
} Locataire, *PLocataire;
typedef struct Location
{
    InformationsDuLocation informationsDuLocation;
    struct Location *locationSuivante;
} Location, *PLocation;
typedef struct Loyer
{
    float loyer;
    struct Loyer *loyerSuivant;
} Loyer, *PLoyer;
typedef struct QuartierCount
{
    char quartier[100];
    int count;
    struct QuartierCount *quartierSuivant;
} QuartierCount, *PQuartierCount;
typedef struct AnneeDonnees
{
    int annee;
    QuartierCount *quartiers;
    struct AnneeDonnees *anneeSuivante;
} AnneeDonnees, *PAnneeDonnees;

extern PLogement teteLogementActive;
extern PLocataire teteLocataireActive;
extern PLocation teteLocationActive;
extern PLoyer teteLoyer;

extern PLogement teteLogementArchive;
extern PLocataire teteLocataireArchive;
extern PLocation teteLocationArchive;

extern PLocation teteLocationTrieeStudio;
extern PLocation teteLocationTrieeF2;
extern PLocation teteLocationTrieeF3;
extern PLocation teteLocationTrieeF4;

extern PAnneeDonnees teteAnneeDonnees;

int GetLocIDByLogID(int idlog);
int GetLogIDByLocID(int idloc);
float RetLoyerByLogementID(int idlog);
char *RetLogTypeByLogID(int idlog);
void ModifierEtatOccupationLog(int idlog, bool occupe);

void ListerLogements(PLogement teteLogement);
void ListerLocataires(PLocataire teteLocataire);
void ListerLocations(PLocation teteLocation);

int NouveauLogement(InformationsDuLogment informationsDuLogement, bool output);
int NouveauLocataire(InformationsDuLocataire informationsDuLocataire, bool output);
int NouvelleLocation(InformationsDuLocation informationsDuLocation, bool output);
int NouveauLoyer(float loyer, bool output);

void SupprimerLogement(int idlog, bool output);
void SupprimerLogementEx(int idlog, bool output);
void SupprimerLocataire(int idloc, bool output);
void SupprimerLocataireEx(int idloc, bool output);
void SupprimerLocation(int idlog, int idloc, bool output);
void SupprimerLocationEx(int idlog, bool output);

void FreeLogementListe(PLogement *tete);
void FreeLocataireListe(PLocataire *tete);
void FreeLocationListe(PLocation *tete);
void FreeLoyerListe(PLoyer *tete);
void FreeAnneesDonnesListe(PAnneeDonnees *tete);
void FreeLinkedListes();

void AjouterLogementAListeArchive(PLogement logement, bool output);
void AjouterLocataireAListeArchive(PLocataire locataire, bool output);
void AjouterLocationAListeArchive(PLocation location, bool output);
void AjouterLocationAListeTrieeType(PLocation location, PLocation *teteLocationGereeType, bool output);
void AjouterLogementAListeTriee(PLogement logement, PLogement *teteLogement, bool output);

void ListerLogementsOccupesEtLibres(char* date);

void TrierLoyers();
PLocation FusionnerListesLocationsTriees();
PLocation TrierListeParLoyer(PLocation teteLocation);
void TrierLocationsParLoyer();

void ListerLocatairesParTypeEtSuperficie();
void ChercherLogementsProchesEtAbordables();

PAnneeDonnees TrouverOuCreerUneAnnee(PAnneeDonnees *teteAnneeDonnees, int annee);
PQuartierCount TrouverOuCreerUnQuartier(PQuartierCount *teteQuartierCount, const char *quartier);
void ConsulterHistoriqueLogementsEtLocationsParAnnee();
#endif