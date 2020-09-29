#include <iostream>
#include "Users.h"

using namespace std;

User::User() {}
User::~User() {}

int User::globalUserId = 0;
int User::globalLoggedUserId = 0;

void User::setGlobalLoggedUserId() {
    globalLoggedUserId = id;
}

int User::getGlobalLoggedUserId() {
    return globalLoggedUserId;
}

void User::setGlobalUserId() {
    globalUserId = id;
}

int User::getGlobalUserId() {
    return globalUserId;
}

void User::setUserData() {
    cin.sync();
    cout << "Podaj login: ";
    cin >> login;
    cout << "Podaj haslo: ";
    cin >> password;
}

bool User::checkUserLoginAndPassword(User & userToLog) {
    if(login == userToLog.login && password == userToLog.password) {
        return true;
    } else {
        return false;
    }
}

void User::setUserDataFromFile(string dataInLine) {
    id = atoi(separateLine(dataInLine).c_str());
    login = separateLine(dataInLine);
    password = separateLine(dataInLine);
}

string User::getUserDataInLine() {
    string userDataInLine;
    userDataInLine = to_string(id) + "|" + login + "|" + password + "|";
    return userDataInLine;
}

void User::setLogin(string newLogin) {
    login = newLogin;
}

void User::setPassword(string newPassword) {
    password = newPassword;
}

void User::setId() {
    id = globalUserId + 1;
    globalUserId++;
}

string User::getLogin() {
    return login;
}

string User::getPassword() {
    return password;
}

int User::getId() {
    return id;
}
