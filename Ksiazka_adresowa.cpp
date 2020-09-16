#include <iostream>
#include <windows.h>
#include <cstdlib>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

struct Person {
    string name, lastName, phoneNumber, email, address;
    int id;
};

string loadLine();
string separateLine(string &line);
void addPerson(vector <Person> &persons);
void editPerson(vector <Person> &persons);
void deletePerson(vector <Person> &persons);
void showPersonByName(vector <Person> &persons);
void showPersonByLastName(vector <Person> &persons);
void showAllPersons(vector <Person> &persons);
void showPersonData(vector <Person> &persons, vector <Person> ::iterator personNumber);
void loadDataFromFile(vector <Person> &persons);
void saveDataToFile(vector <Person> &persons);
void overwriteFile(vector <Person> &persons);

int main() {
    int menuChoice;
    vector <Person> persons;

    loadDataFromFile(persons);

    while (1) {
        cout << "-----KSIAZKA ADRESOWA-----" << endl << endl;
        cout << "1. Dodaj adresata" << endl;
        cout << "2. Wyszukaj po imieniu" << endl;
        cout << "3. Wyszukaj po nazwisku" << endl;
        cout << "4. Wyswietl wszystkich adresatow" << endl;
        cout << "5. Usun adresata" << endl;
        cout << "6. Edytuj adresata" << endl;
        cout << "9. Zakoncz program" << endl;
        cout << "Twoj wybor: ";
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
            break;
        case 6:
            editPerson(persons);
            break;
        case 9:
            system("cls");
            cout << endl << "Koniec programu!!! Do widzenia!!!" << endl;
            exit(0);
        default :
            cout << endl << "Nie ma takiej opcji w Menu!!! Sprobuj ponownie!!!";
            system("pause");
        }
        system("cls");
    }
    return 0;
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

string separateLine(string &line) {
    if (line == "") {
        return "pusty";
    }
    int separatorPosition = line.find("|", 0);
    string newWord = line.substr(0, separatorPosition);
    line.erase(0, separatorPosition + 1);

    return newWord;
}

void addPerson(vector <Person> &persons) {
    vector <Person> ::iterator vectorBegin = persons.begin();
    vector <Person> ::iterator vectorEnd = persons.end();
    Person newPerson;
    cout << endl;
    if (vectorBegin == vectorEnd) {
        newPerson.id = 1;
    } else {
        newPerson.id = (vectorEnd - 1)->id + 1;
    }
    cout << "Podaj imie: ";
    newPerson.name = loadLine();
    cout << "Podaj nazwisko: ";
    newPerson.lastName = loadLine();
    cout << "Podaj nr. telefonu: ";
    newPerson.phoneNumber = loadLine();
    cout << "Podaj adres e-mail: ";
    newPerson.email = loadLine();
    cout << "Podaj adres: ";
    newPerson.address = loadLine();

    persons.push_back(newPerson);
    saveDataToFile(persons);
}

void editPerson(vector <Person> &persons) {
    vector <Person> ::iterator vectorBegin = persons.begin();
    vector <Person> ::iterator vectorEnd = persons.end();
    int option, id;

    if (vectorBegin != vectorEnd) {
        cout << endl << "Podaj id adresata: ";
        cin >> id;

        for (vectorBegin; vectorBegin < vectorEnd; vectorBegin++) {
            if (vectorBegin->id == id) {
                break;
            } else if ((vectorBegin->id != id) && (vectorBegin >= vectorEnd - 1)) {
                cout << "Nie ma adresata o takim id!!!" << endl;
                system("pause");
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
            cout << "Twoj wybor: ";
            cin >> option;
            cin.sync();

            switch (option) {
            case 1:
                cout << endl << "Podaj nowe imie: ";
                getline(cin, vectorBegin->name);
                cout << endl << "Zmieniono imie!!!" << endl << endl;
                system("pause");
                break;
            case 2:
                cout << endl << "Podaj nowe nazwisko: ";
                getline(cin, vectorBegin->lastName);
                cout << endl << "Zmieniono nazwisko!!!" << endl << endl;
                system("pause");
                break;
            case 3:
                cout << endl << "Podaj nowy numer telefonu: ";
                getline(cin, vectorBegin->phoneNumber);
                cout << endl << "Zmieniono numer telefonu!!!" << endl << endl;
                system("pause");
                break;
            case 4:
                cout << endl << "Podaj nowy e-mail: ";
                getline(cin, vectorBegin->email);
                cout << endl << "Zmieniono e-mail!!!" << endl << endl;
                system("pause");
                break;
            case 5:
                cout << endl << "Podaj nowy adres: ";
                getline(cin, vectorBegin->address);
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
        overwriteFile(persons);
    } else {
        cout << endl << "Ksiazka adresowa jest pusta!!!" << endl << endl;
        system("pause");
    }
}

void deletePerson(vector <Person> &persons) {
    vector <Person> ::iterator vectorBegin = persons.begin();
    vector <Person> ::iterator vectorEnd = persons.end();
    int id;
    char option;

    if (vectorBegin != vectorEnd) {
        cout << endl << "Podaj id adresata: ";
        cin >> id;

        for (vectorBegin; vectorBegin != vectorEnd; vectorBegin++) {
            if (vectorBegin->id == id) {
                break;
            } else if (vectorBegin >= vectorEnd - 1) {
                cout << endl << "Nie ma adresata o takim id!!!" << endl << endl;
                system("pause");
                return;
            }
        }
        cout << endl << "Czy na pewno chcesz usunac adresata o id = " << vectorBegin->id << " <t/n>: ";
        cin >> option;
        if (option == 't' || option == 'T') {
            persons.erase(vectorBegin);
            overwriteFile(persons);
        } else {
            cout << endl << "Nie wprowadzono zmian!!!" << endl << endl;
            system("pause");
        }
    } else {
        cout << endl << "Ksiazka adresowa jest pusta!!!" << endl << endl;
        system("pause");
    }
}

void showPersonByName(vector <Person> &persons) {
    vector <Person> ::iterator vectorBegin = persons.begin();
    vector <Person> ::iterator vectorEnd = persons.end();
    bool nameWasFound = false;
    string nameToShow;

    if (vectorBegin != vectorEnd) {
        cout << endl << "Podaj imie: ";
        nameToShow = loadLine();

        for (vectorBegin; vectorBegin != vectorEnd; vectorBegin++) {
            if (vectorBegin->name == nameToShow) {
                showPersonData(persons, vectorBegin);
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

    if (vectorBegin != vectorEnd) {
        cout << endl << "Podaj nazwisko: ";;
        lastNameToShow = loadLine();

        for (vectorBegin; vectorBegin != vectorEnd; vectorBegin++) {
            if (vectorBegin->lastName == lastNameToShow) {
                showPersonData(persons, vectorBegin);
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

    if (vectorBegin != vectorEnd) {
        for (vectorBegin; vectorBegin != vectorEnd; vectorBegin++) {
            showPersonData(persons, vectorBegin);
        }
        cout << endl;
    } else {
        cout << endl << "Ksiazka adresowa jest pusta!!!" << endl << endl;
    }
}

void showPersonData(vector <Person> &persons, vector <Person> ::iterator personNumber) {
    cout << endl;
    cout << "Id:       " << personNumber->id << endl;
    cout << "Imie:     " << personNumber->name << endl;
    cout << "Nazwisko: " << personNumber->lastName << endl;
    cout << "Telefon:  " << personNumber->phoneNumber << endl;
    cout << "E-mail:   " << personNumber->email << endl;
    cout << "Adres:    " << personNumber->address << endl;
}

void loadDataFromFile(vector <Person> &persons) {
    Person loadPerson;
    string lineLoaded;
    ifstream readFromFile("Ksiazka adresowa.txt");

    if (readFromFile.good() == true) {
        cin.sync();
        while (getline(readFromFile, lineLoaded)) {
            loadPerson.id = atoi(separateLine(lineLoaded).c_str());
            loadPerson.name = separateLine(lineLoaded);
            loadPerson.lastName = separateLine(lineLoaded);
            loadPerson.phoneNumber = separateLine(lineLoaded);
            loadPerson.email = separateLine(lineLoaded);
            loadPerson.address = separateLine(lineLoaded);

            persons.push_back(loadPerson);
        }
        readFromFile.close();
    } else {
        cout << endl << "Blad otwarcia pliku!!! Prawdopodobnie plik \"Ksiazka adresowa.txt\" nie istnieje!!!" << endl;
        cout << "Zostanie utworzony nowy plik o nazwie \"Ksiazka adresowa.txt\"" << endl << endl;

        readFromFile.clear();
        system("pause");
        system("cls");
    }
}

void saveDataToFile(vector <Person> &persons) {
    vector <Person> ::iterator vectorEnd = persons.end();
    ofstream saveToFile("Ksiazka adresowa.txt", ios::app);
    vectorEnd = vectorEnd - 1;

    if (saveToFile.good() == true) {
        saveToFile << vectorEnd->id << "|";
        saveToFile << vectorEnd->name << "|";
        saveToFile << vectorEnd->lastName << "|";
        saveToFile << vectorEnd->phoneNumber << "|";
        saveToFile << vectorEnd->email << "|";
        saveToFile << vectorEnd->address << "|" << endl;

        cout << endl << "Dodano osobe do ksiazki adresowej!!!" << endl << endl;
        saveToFile.close();
    } else {
        cout << endl << "Blad zapisu do pliku o nazwie \"Ksiazka adresowa.txt\"" << endl << endl;
        saveToFile.clear();
    }
}

void overwriteFile(vector <Person> &persons) {
    ofstream saveToFile("Ksiazka adresowa.txt");

    if (saveToFile.good() == true) {
        vector <Person> ::iterator vectorBegin = persons.begin();
        vector <Person> ::iterator vectorEnd = persons.end();

        for (vectorBegin; vectorBegin != vectorEnd; vectorBegin++) {
            saveToFile << vectorBegin->id << "|";
            saveToFile << vectorBegin->name << "|";
            saveToFile << vectorBegin->lastName << "|";
            saveToFile << vectorBegin->phoneNumber << "|";
            saveToFile << vectorBegin->email << "|";
            saveToFile << vectorBegin->address << "|" << endl;
        }
        saveToFile.close();
        cout << endl << "Zapisano zmiany!!!" << endl << endl;
        system("pause");
    } else {
        cout << endl << "Blad zapisu do pliku!!!" << endl << endl;
        saveToFile.clear();
    }
}
