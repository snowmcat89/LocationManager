#include "LOG_LLC_BIBLIO.h"
#include "file.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

void MainMenu()
{
    system("cls");
    printf("/*****************************************************************************************\\\n");
    printf("|                                                                                         |\n");
    printf("|                             BIENVENUE CHEZ LOGEMENT MANAGER                             |\n");
    printf("|                                                                                         |\n");
    printf("\\*****************************************************************************************/\n");
    printf("                       Une mini application pour la gestion locative                        \n");
    printf("===========================================================================================\n");

    while (true)
    {
        printf("                                       [ MAIN MENU ]                                       \n");
        printf("-------------------------------------------------------------------------------------------\n");
        printf("  [1] Enregistrer des nouveaux logements, locataires ou locations Apartir d'un fichier .txt\n");
        printf("  [2] Supprimer un logement, un locataire ou une location                                  \n");
        printf("  [3] Lister tout les logements, les locataires ou les locations disponibles (Optionnel)     \n");
        printf("  [4] Lister tout les logements occupés et ceux qui seront libres à une date donnée        \n");
        printf("  [5] Trier la liste des locations selon le loyer (Descendant)                             \n");
        printf("  [6] Lister les locataires par type de logement et superficie supérieure à la moyenne     \n");
        printf("  [7] Lister les logements adorables et proches à la commune                               \n");
        printf("  [8] Consulter l'historique des logements et locations par année                          \n");
        printf("  [9] Quitter                                                                              \n");
        printf("-------------------------------------------------------------------------------------------\n");
        printf("\n\n  Veuillez entrer votre choix: ");
        int choix1 = 0;
        scanf("%d", &choix1);
        
        switch (choix1)
        {
            case 1:
            {
                printf("  Ton choix: Creation d'un {Logement, locataire ou location}\n\n");
                printf("-------------------------------------------------------------------------------------------\n");
                printf("\t  [1] Enregistrer des logements\n");
                printf("\t  [2] Enregistrer des locataires\n");
                printf("\t  [3] Enregistrer des locations\n");
                printf("\t  [4] Menu principale\n");
                printf("-------------------------------------------------------------------------------------------\n");
                printf("\n\n\t  Veuillez entrer votre choix: ");
                int choix2 = 0;
                scanf("%d", &choix2);
                switch (choix2)
                {
                    case 1:
                    {
                        printf("\t  Ton choix: Creation des logements (Apartir d'un fichier text)\n\n");
                        char cheminDuFichier[260];
                        printf("\t\t  Veuillez saisir le chemin du fichier à importer qui contient les logements [Par defaut: ./logements.txt]: ");
                        scanf(" %[^\n]", cheminDuFichier);

                        if (cheminDuFichier[0] == '\0') {
                            printf("\t\t  Chemin vide ! Utilisation du chemin par défaut: logements.txt\n");
                            strcpy(cheminDuFichier, "logements.txt");
                        } else {
                            printf("\t\t  Chemin saisi: %s\n", cheminDuFichier);
                        }
                
                        ExtraireLogInfoDuFichier(cheminDuFichier);
                        break;
                    }
                    case 2:
                    {
                        printf("\t  Ton choix: Creation des locataires (Apartir d'un fichier text)\n\n");
                        char cheminDuFichier[260];
                        printf("\t\t  Veuillez saisir le chemin du fichier à importer qui contient les locataires [Par defaut: ./locataires.txt]: ");
                        scanf(" %[^\n]", cheminDuFichier);

                        if (cheminDuFichier[0] == '\0') {
                            printf("\t\t  Chemin vide ! Utilisation du chemin par défaut: locataires.txt\n");
                            strcpy(cheminDuFichier, "locataires.txt");
                        } else {
                            printf("\t\t  Chemin saisi: %s\n", cheminDuFichier);
                        }
                
                        ExtraireLocataireInfoDuFichier(cheminDuFichier);
                        break;
                    }
                    case 3:
                    {
                        printf("\t  Ton choix: Creation des locations (Apartir d'un fichier text)\n\n");
                        char cheminDuFichier[260];
                        printf("\t\t  Veuillez saisir le chemin du fichier à importer qui contient les locations [Par defaut: ./locations.txt]: ");
                        scanf(" %[^\n]", cheminDuFichier);

                        if (cheminDuFichier[0] == '\0') {
                            printf("\t\t  Chemin vide ! Utilisation du chemin par défaut: locations.txt\n");
                            strcpy(cheminDuFichier, "locations.txt");
                        } else {
                            printf("\t\t  Chemin saisi: %s\n", cheminDuFichier);
                        }
                
                        ExtraireLocationInfoDuFichier(cheminDuFichier);
                        break;
                    }
                    case 4:
                        break;
                    default:
                        printf("\t  Veuillez saisir un choix valide\n");
                        break;
                }
                break;
            }
            case 2:
            {
                printf("  Ton choix: Suppression d'un {Logement, locataire ou location}\n\n");
                printf("-------------------------------------------------------------------------------------------\n");
                printf("\t  [1] Supprimer un logement\n");
                printf("\t  [2] Supprimer un locataire\n");
                printf("\t  [3] Supprimer une location\n");
                printf("\t  [4] Menu principale\n");
                printf("-------------------------------------------------------------------------------------------\n");
                printf("\n\n\t  Veuillez entrer votre choix: ");
                int choix2 = 0;
                scanf("%d", &choix2);
                switch (choix2)
                {
                    case 1:
                    {
                        printf("\t  Ton choix: Suppression d'un logement\n\n");
                        int id;

                        printf("\t\t  Veuillez entrer ID du logement: ");
                        scanf("%d", &id);
                        printf("\n");
                        SupprimerLogementEx(id, false);
                        break;
                    }
                    case 2:
                    {
                        printf("\t  Ton choix: Suppression d'un locataire\n\n");
                        int id;
                        printf("\t\t  Veuillez entrer ID du locataire: ");
                        scanf("%d", &id);
                        printf("\n");
                        SupprimerLocataireEx(id, false);
                        break;
                    }
                    case 3:
                    {
                        printf("\t  Ton choix: Suppression d'une location\n\n");
                        int id;

                        printf("\t\t  Veuillez entrer ID du logement: ");
                        scanf("%d", &id);
                        printf("\n");
                        SupprimerLocationEx(id, false);
                        break;
                    }
                    case 4:
                        break;
                    default:
                        printf("\t\t  Veuillez saisir un choix valide");
                        break;
                    }
                break;
            }
            case 3:
            {
                printf("  Ton choix: Lister les {Logements, locataires ou locations} disponibles\n\n");
                printf("-------------------------------------------------------------------------------------------\n");
                printf("\t  [1] Lister les logements disponibles\n");
                printf("\t  [2] Lister les locataires disponibles\n");
                printf("\t  [3] Lister les locations disponibles\n");
                printf("\t  [4] Menu principale\n");
                printf("-------------------------------------------------------------------------------------------\n");
                printf("\n\n\t  Veuillez entrer votre choix: ");
                int choix2;
                scanf("%d", &choix2);
                switch (choix2)
                {
                    case 1:
                    {
                        printf("\t  Ton choix: Lister tout les logements disponibles\n\n");
                        ListerLogements(teteLogementActive);
                        break;
                    }
                    case 2:
                    {
                        printf("\t  Ton choix: Lister tout les locataires disponibles\n\n");
                        ListerLocataires(teteLocataireActive);
                        break;
                    }
                    case 3:
                    {
                        printf("\t  Ton choix: Lister tout les locations disponibles\n\n");
                        ListerLocations(teteLocationActive);
                        break;
                    }
                    default:
                        printf("\t  Veuillez saisir un choix valide");
                        break;
                }
                break;
            }
            case 4:
            {
                printf("  Ton choix: Lister les logements qui seront libres à la date jj/mm/aaaa\n\n");

                char date[11];
                printf("\t  Veuillez entrer la date (JJ/MM/AAAA): ");
            
                while (getchar() != '\n');
                
                scanf("%10s", date);
                printf("\n\tDate saisie: %s\n", date);
            
                ListerLogementsOccupesEtLibres(date);
                break;
            }
            case 5:
            {
                printf("  Ton choix: Trier locations par loyer\n");
                TrierLocationsParLoyer();
                break;
            }
            case 6:
            {
                printf("  Ton choix: Lister locataires par type et superficie (Chercher)\n");
                ListerLocatairesParTypeEtSuperficie();
                break;
            }
            case 7:
            {
                printf("  Ton choix: Lister logement proches et adorables\n");
                ChercherLogementsProchesEtAbordables();
                break;
            }
            case 8:
            {
                printf("  Ton choix: Consulter l'historique des logements et locations par année\n");
                ConsulterHistoriqueLogementsEtLocationsParAnnee();
                break;
            }
            case 9:
                FreeLinkedListes();
                return;
            default:
                printf("  Veuillez saisir un choix valide\n");
                break;
        }
    }
}