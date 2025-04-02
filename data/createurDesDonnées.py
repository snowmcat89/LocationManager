import os

def pushData(data):
    match data:
        case 1:
            fixedinput = input("Quartier:").replace(" ","")
            info = [
                input("ID du logement: "),
                input("Superficie: "),
                input("Distance à commune: "),
                fixedinput,
                "false",
                input("Type du logement: ")
            ]
            with open("logements.txt", "a") as file:
                if os.stat("logements.txt").st_size != 0:
                    file.write("\n")
                file.write(" ".join(info))
        case 2:
            info = [
                input("ID du locataire: "),
                input("Nom: "),
                input("Prenom: "),
                "+213" + input("Telephone: ")
            ]
            with open("locataires.txt", "a") as file:
                if os.stat("locataires.txt").st_size != 0:
                    file.write("\n")
                file.write(" ".join(info))
        case 3:
            info = [
                input("ID du logement: "),
                input("ID du locataire: "),
                input("Date début (JJ/MM/AAAA): "),
                input("Date fin (JJ/MM/AAAA): ")
            ]
            with open("locations.txt", "a") as file:
                if os.stat("locations.txt").st_size != 0:
                    file.write("\n")
                file.write(" ".join(info))

while True:
    check_con = input("Do you want to continue? (Y/n): ").lower()
    if check_con in ["n", "no", "non"]:
        break
    
    print("""
Please choose one of these options:
    1 - Logement
    2 - Locataire
    3 - Location
    """)
    
    data = input("Your choice: ")
    pushData(int(data))