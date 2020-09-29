#include <iostream>
#include "Persons.h"

using namespace std;

Person::Person() {}

Person::~Person() {}

int Person::globalId = 0;
int Person::globalLoggedUserId = 0;

void Person::addNewPerson() {
    cin.sync();
    cout << "Podaj imie: ";
    getline(cin, name);
    cout << "Podaj nazwisko: ";
    getline(cin, lastName);
    cout << "Podaj nr. telefonu: ";
    getline(cin, phoneNumber);
    cout << "Podaj adres e-mail: ";
    getline(cin, email);
    cout << "Podaj adres: ";
    getline(cin, address);
    userId = globalLoggedUserId;
    id = globalId + 1;
    globalId++;
}

string Person::getPersonDataInLine() {
    string personDataInLine;
    personDataInLine = to_string(id) + "|" + to_string(userId) + "|" + name + "|" + lastName + "|" + phoneNumber + "|" + email + "|" + address + "|";
    return personDataInLine;
}

void Person::setGlobalLoggedUserId(int loggedUserId) {
    globalLoggedUserId = loggedUserId;
}

void Person::setGlobalPersonId(int setId) {
    globalId = setId;
}

int Person::getGlobalPersonId() {
    return globalId;
}

void Person::setPersonData(string dataInLine) {
    id = atoi(separateLine(dataInLine).c_str());
    userId = atoi(separateLine(dataInLine).c_str());
    name = separateLine(dataInLine);
    lastName = separateLine(dataInLine);
    phoneNumber = separateLine(dataInLine);
    email = separateLine(dataInLine);
    address = separateLine(dataInLine);
}

void Person::showPersonData() {
    cout << endl;
    cout << "Id:       " << id << endl;
    cout << "User Id:  " << userId << endl;
    cout << "Imie:     " << name << endl;
    cout << "Nazwisko: " << lastName << endl;
    cout << "Telefon:  " << phoneNumber << endl;
    cout << "E-mail:   " << email << endl;
    cout << "Adres:    " << address << endl;
}

void Person::setName(string newName) {
    name = newName;
}

void Person::setLastName(string newLastName) {
    lastName = newLastName;
}

void Person::setPhoneNumber(string newPhoneNumber) {
    phoneNumber = newPhoneNumber;
}

void Person::setEmail(string newEmail) {
    email = newEmail;
}

void Person::setAddress(string newAddress) {
    address = newAddress;
}

string Person::getName() {
    return name;
}
string Person::getLastName() {
    return lastName;
}

int Person::getId() {
    return id;
}

int Person::getUserId() {
    return userId;
}
