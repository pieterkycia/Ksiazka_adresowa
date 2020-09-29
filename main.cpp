#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <cstdlib>
#include <windows.h>
#include <cstdio>
#include "Users.h"
#include "Persons.h"

using namespace std;

void loadUsersFromFile(vector <User> &users);
void saveUserDataToFile(vector <User> &users);
void showUsers(vector <User> &users);
void registerNewUser(vector <User> &users);
void changeUserPassword(vector <User> &users);
void loggedUserMenu(vector <User> &users, int loggedUserId);
int logInUser(vector <User> &users);

///////////////////////////////////////////////////////////////////
string loadLine();
string separateLine(string &line);
void addPerson(vector <Person> &persons);
void editPerson(vector <Person> &persons);
void deletePerson(vector <Person> &persons);
void showPersonByName(vector <Person> &persons);
void showPersonByLastName(vector <Person> &persons);
void showAllPersons(vector <Person> &persons);
void loadPersonFromFile(vector <Person> &persons, int loggedUserId);
void savePersonDataToFile(Person &newPerson, string option);

int main() {
    vector <User> users;
    loadUsersFromFile(users);
    int loggedUserId = 0;
    int menuChoice;
    while (1) {
        cout << "-----MENU-----" << endl << endl;
        cout << "1. Logowanie" << endl;
        cout << "2. Rejestracja" << endl;
        cout << "3. Koniec programu" << endl;
        cin >> menuChoice;

        switch (menuChoice) {
        case 1:
            loggedUserId = logInUser(users);
            if (loggedUserId > 0) {
                loggedUserMenu(users, loggedUserId);
            } else {
                cout << endl << "Bledny login lub haslo!!!" << endl << endl;
                system("pause");
                system("cls");
            }
            break;
        case 2:
            registerNewUser(users);
            system("pause");
            system("cls");
            break;
        case 3:
            cout << "Koniec programu!!!" << endl;
            exit(0);
        default :
            cout << "Nie ma takiej opcji w menu!!!" << endl << endl;
            system("pause");
            system("cls");
        }
    }
    return 0;
}

string separateLine(string &line) {
    if (line == "") {
        return "pusty";
    }
    int separatorPosition = line.find("|", 0);
    string newWord = line.substr(0, separatorPosition);
    line.erase(0, separatorPosition + 1);
    return newWord;
}

string loadLine() {
    string lineToLoad = "";
    cin.sync();
    getline(cin, lineToLoad);
    if (lineToLoad == "") {
        return "pusty";
    }
    return lineToLoad;
}

void addPerson(vector <Person> &persons) {
    Person newPerson;
    newPerson.addNewPerson();

    savePersonDataToFile(newPerson, "addPerson");
    persons.push_back(newPerson);
}

void editPerson(vector <Person> &persons) {
    vector <Person> ::iterator vectorBegin = persons.begin();
    vector <Person> ::iterator vectorEnd = persons.end();
    int option, id;

    if (persons.empty() == false) {
        cout << endl << "Podaj id adresata: ";
        cin >> id;

        for (vectorBegin; vectorBegin != vectorEnd; vectorBegin++) {
            if (vectorBegin->getId() == id) {
                break;
            } else if ((vectorBegin->getId() != id) && (vectorBegin >= vectorEnd - 1)) {
                cout << "Nie ma adresata o takim id!!!" << endl;
                return;
            }
        }
        do {
            system("cls");
            cout << "-----MENU EDYCYJNE-----" << endl << endl;
            cout << "1. Edytuj imie" << endl;
            cout << "2. Edytuj nazwisko" << endl;
            cout << "3. Edytuj numer telefonu" << endl;
            cout << "4. Edytuj e-mail" << endl;
            cout << "5. Edytuj adres" << endl;
            cout << "6. Zapisz zmiany i wroc do menu" << endl;
            cin >> option;
            cin.sync();

            switch (option) {
            case 1:
                cout << endl << "Podaj nowe imie: ";
                vectorBegin->setName(loadLine());
                cout << endl << "Zmieniono imie!!!" << endl << endl;
                system("pause");
                break;
            case 2:
                cout << endl << "Podaj nowe nazwisko: ";
                vectorBegin->setLastName(loadLine());
                cout << endl << "Zmieniono nazwisko!!!" << endl << endl;
                system("pause");
                break;
            case 3:
                cout << endl << "Podaj nowy numer telefonu: ";
                vectorBegin->setPhoneNumber(loadLine());
                cout << endl << "Zmieniono numer telefonu!!!" << endl << endl;
                system("pause");
                break;
            case 4:
                cout << endl << "Podaj nowy e-mail: ";
                vectorBegin->setEmail(loadLine());
                cout << endl << "Zmieniono e-mail!!!" << endl << endl;
                system("pause");
                break;
            case 5:
                cout << endl << "Podaj nowy adres: ";
                vectorBegin->setAddress(loadLine());
                cout << endl << "Zmieniono adres!!!" << endl << endl;
                system("pause");
                break;
            case 6:
                break;
            default :
                cout << endl << "Nie ma takiej opcji w menu!!!" << endl << endl;
                system("pause");
            }
        } while (option != 6);
        savePersonDataToFile(*vectorBegin, "editPerson");
    } else {
        cout << endl << "Ksiazka adresowa jest pusta!!!" << endl << endl;
    }
}

void deletePerson(vector <Person> &persons) {
    vector <Person> ::iterator vectorBegin = persons.begin();
    vector <Person> ::iterator vectorEnd = persons.end();
    int id;
    char option;

    if (persons.empty() == false) {
        cout << endl << "Podaj id adresata: ";
        cin >> id;

        for (vectorBegin; vectorBegin != vectorEnd; vectorBegin++) {
            if (vectorBegin->getId() == id) {
                break;
            } else if (vectorBegin >= vectorEnd - 1) {
                cout << endl << "Nie ma adresata o takim id!!!" << endl << endl;
                return;
            }
        }
        cout << endl << "Czy na pewno chcesz usunac adresata o id = " << vectorBegin->getId() << " <t/n>: ";
        cin >> option;
        if (option == 't' || option == 'T') {
            if (vectorBegin->getId() == vectorBegin->getGlobalPersonId()) {
                vectorBegin->setGlobalPersonId(vectorBegin->getId() - 1);
            }
            savePersonDataToFile(*vectorBegin, "deletePerson");
            persons.erase(vectorBegin);
        } else {
            cout << endl << "Nie wprowadzono zmian!!!" << endl << endl;
        }
    } else {
        cout << endl << "Ksiazka adresowa jest pusta!!!" << endl << endl;
    }
}

void showPersonByName(vector <Person> &persons) {
    vector <Person> ::iterator vectorBegin = persons.begin();
    vector <Person> ::iterator vectorEnd = persons.end();
    bool nameWasFound = false;
    string nameToShow;

    if (persons.empty() == false) {
        cout << endl << "Podaj imie: ";
        nameToShow = loadLine();

        for (vectorBegin; vectorBegin != vectorEnd; vectorBegin++) {
            if (vectorBegin->getName() == nameToShow) {
                vectorBegin->showPersonData();
                nameWasFound = true;
            }
        }
        if (nameWasFound == false) {
            cout << endl << "Nie ma osoby o takim imieniu!!!" << endl;
        }
        cout << endl;
    } else {
        cout << endl << "Ksiazka adresowa jest pusta!!!" << endl << endl;
    }
}

void showPersonByLastName(vector <Person> &persons) {
    vector <Person> ::iterator vectorBegin = persons.begin();
    vector <Person> ::iterator vectorEnd = persons.end();
    bool lastNameWasFound = false;
    string lastNameToShow;

    if (persons.empty() == false) {
        cout << endl << "Podaj nazwisko: ";;
        lastNameToShow = loadLine();

        for (vectorBegin; vectorBegin != vectorEnd; vectorBegin++) {
            if (vectorBegin->getLastName() == lastNameToShow) {
                vectorBegin->showPersonData();
                lastNameWasFound = true;
            }
        }
        if (lastNameWasFound == false) {
            cout << endl << "Nie ma osoby o takim nazwisku!!!" << endl;
        }
        cout << endl;
    } else {
        cout << endl << "Ksiazka adresowa jest pusta!!!" << endl << endl;
    }
}

void showAllPersons(vector <Person> &persons) {
    vector <Person> ::iterator vectorBegin = persons.begin();
    vector <Person> ::iterator vectorEnd = persons.end();

    if (persons.empty() == false) {
        for (vectorBegin; vectorBegin != vectorEnd; vectorBegin++) {
            vectorBegin->showPersonData();
        }
        cout << endl;
    } else {
        cout << endl << "Ksiazka adresowa jest pusta!!!" << endl << endl;
    }
}

void loadPersonFromFile(vector <Person> &persons, int loggedUserId) {
    Person loadPerson;
    loadPerson.setGlobalLoggedUserId(loggedUserId);
    string lineLoaded;
    ifstream readFromFile("Adresaci.txt");

    if (readFromFile.good() == true) {
        cin.sync();
        while (getline(readFromFile, lineLoaded)) {
            loadPerson.setPersonData(lineLoaded);
            loadPerson.setGlobalPersonId(loadPerson.getId());
            if (loadPerson.getUserId() == loggedUserId) {
                persons.push_back(loadPerson);
            }
        }
        readFromFile.close();
    } else {
        cout << endl << "Blad otwarcia pliku!!! Prawdopodobnie plik \"Adresaci.txt\" nie istnieje!!!" << endl;
        cout << "Zostanie utworzony nowy plik o nazwie \"Adresaci.txt\"" << endl << endl;

        readFromFile.clear();
        ofstream createFile("Adresaci.txt");
        createFile.close();
        system("pause");
        system("cls");
    }
}

void savePersonDataToFile(Person &newPerson, string option) {
    ofstream saveToFile("Tymczasowy_Adresaci.txt");
    ifstream readFromFile("Adresaci.txt");
    string lineLoaded, copyLine;
    int personId = 0;

    if ((saveToFile.good() == true) && (readFromFile.good() == true)) {
        while (getline(readFromFile, lineLoaded)) {
            copyLine = lineLoaded;
            personId = atoi(separateLine(copyLine).c_str());
            if (personId == newPerson.getId() && option == "editPerson") {
                saveToFile << newPerson.getPersonDataInLine() << endl;
            } else if ((personId == newPerson.getId()) && (option == "deletePerson")) {
                continue;
            } else {
                saveToFile << lineLoaded << endl;
            }
        }
        if (option == "addPerson") {
            saveToFile << newPerson.getPersonDataInLine() << endl;
        }
        cout << endl << "Zapisano zmiany!!!" << endl << endl;
        saveToFile.close();
        readFromFile.close();
        if (remove("Adresaci.txt") == 0) {
            if (rename("Tymczasowy_Adresaci.txt", "Adresaci.txt") == 0) {
                cout << "Pomyslnie zastapiono plik Adresaci.txt" << endl << endl;
            } else {
                cout << "Nie zmieniono nazwy pliku Tymczasowy_Adresaci.txt" << endl << endl;
            }
        } else {
            cout << "Nie usunieto pliku!!! Zmiany nie sa zapisane!!!" << endl << endl;
        }
    } else {
        cout << endl << "Blad zapisu do pliku" << endl << endl;
        saveToFile.clear();
        readFromFile.clear();
    }
}

/////////////////////////////////////////////////////////////////////////
void loadUsersFromFile(vector <User> &users) {
    User loadUser;
    string lineLoaded;
    ifstream readFromFile("Uzytkownicy.txt");

    if (readFromFile.good() == true) {
        cin.sync();
        while (getline(readFromFile, lineLoaded)) {
            loadUser.setUserDataFromFile(lineLoaded);
            loadUser.setGlobalUserId();
            users.push_back(loadUser);
        }
        readFromFile.close();
    } else {
        cout << endl << "Blad otwarcia pliku!!! Prawdopodobnie plik \"Uzytkownicy.txt\" nie istnieje!!!" << endl;
        cout << "Zostanie utworzony nowy plik o nazwie \"Uzytkownicy.txt\"" << endl << endl;

        readFromFile.clear();
        system("pause");
        system("cls");
    }
}

void saveUserDataToFile(vector <User> &users) {
    vector <User> ::iterator vectorBegin = users.begin();
    vector <User> ::iterator vectorEnd = users.end();
    ofstream saveToFile("Uzytkownicy.txt");

    if (saveToFile.good() == true) {
        for (vectorBegin; vectorBegin != vectorEnd; vectorBegin++) {
            saveToFile << vectorBegin->getUserDataInLine() << endl;
        }
        cout << endl << "Zapisano zmiany!!!" << endl << endl;
        saveToFile.close();
    } else {
        cout << endl << "Blad zapisu do pliku o nazwie \"Uzytkownicy.txt\"" << endl << endl;
        saveToFile.clear();
    }
}

void registerNewUser(vector <User> &users) {
    vector <User> ::iterator vectorBegin = users.begin();
    vector <User> ::iterator vectorEnd = users.end();
    User newUser;
    cout << "Podaj login: ";
    newUser.setLogin(loadLine());

    for (vectorBegin; vectorBegin != vectorEnd; vectorBegin++) {
        if (newUser.getLogin() == vectorBegin->getLogin()) {
            cout << endl << "Podany login jest zajety!!!" << endl << endl;
            return;
        }
    }
    cout << "Podaj haslo: ";
    newUser.setPassword(loadLine());
    newUser.setId();
    users.push_back(newUser);
    saveUserDataToFile(users);
}

void changeUserPassword(vector <User> &users) {
    vector <User> ::iterator vectorBegin = users.begin();
    vector <User> ::iterator vectorEnd = users.end();

    for (vectorBegin; vectorBegin != vectorEnd; vectorBegin++) {
        if (vectorBegin->getId() == vectorBegin->getGlobalLoggedUserId()) {
            cout << "Podaj nowe haslo: ";
            vectorBegin->setPassword(loadLine());
            saveUserDataToFile(users);
            break;
        }
    }
}

int logInUser(vector <User> &users) {
    vector <User> ::iterator vectorBegin = users.begin();
    vector <User> ::iterator vectorEnd = users.end();
    User userToLog;

    userToLog.setUserData();

    for (vectorBegin; vectorBegin != vectorEnd; vectorBegin++) {
        if (vectorBegin->checkUserLoginAndPassword(userToLog) == true) {
            vectorBegin->setGlobalLoggedUserId();
            return vectorBegin->getId();
        }
    }
    return 0;
}

void loggedUserMenu(vector <User> &users, int loggedUserId) {
    cout << endl << "Zalogowano!!!" << endl << endl;
    system("pause");
    system("cls");

    int menuChoice;
    vector <Person> persons;

    loadPersonFromFile(persons, loggedUserId);
    system("cls");
    while (1) {
        cout << "-----KSIAZKA ADRESOWA-----" << endl << endl;
        cout << "1. Dodaj adresata" << endl;
        cout << "2. Wyszukaj po imieniu" << endl;
        cout << "3. Wyszukaj po nazwisku" << endl;
        cout << "4. Wyswietl wszystkich adresatow" << endl;
        cout << "5. Usun adresata" << endl;
        cout << "6. Edytuj adresata" << endl;
        cout << "7. Zmien haslo" << endl;
        cout << "8. Wyloguj sie" << endl;
        cin >> menuChoice;

        switch (menuChoice) {
        case 1:
            addPerson(persons);
            system("pause");
            break;
        case 2:
            showPersonByName(persons);
            system("pause");
            break;
        case 3:
            showPersonByLastName(persons);
            system("pause");
            break;
        case 4:
            showAllPersons(persons);
            system("pause");
            break;
        case 5:
            deletePerson(persons);
            system("pause");
            break;
        case 6:
            editPerson(persons);
            system("pause");
            break;
        case 7: {
            changeUserPassword(users);
            system("pause");
            break;
        }
        case 8:
            cout << "Wylogowano!!!" << endl << endl;
            system("pause");
            system("cls");
            return;
        default :
            cout << "Nie ma takiej opcji w Menu!!!" << endl << endl;
            system("pause");
        }
        system("cls");
    }
}
