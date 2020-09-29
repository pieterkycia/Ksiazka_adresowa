#include <iostream>

using namespace std;

string separateLine(string &line);

class Person {
    string name, lastName, phoneNumber, email, address;
    int id, userId;
    static int globalId;
    static int globalLoggedUserId;
public:
    Person();
    ~Person();

    void addNewPerson();
    string getPersonDataInLine();
    void setGlobalLoggedUserId(int loggedUserId);
    void setGlobalPersonId(int setId);
    int getGlobalPersonId();
    void setPersonData(string dataInLine);
    void showPersonData();

    void setName(string newName);
    void setLastName(string newLastName);
    void setPhoneNumber(string newPhoneNumber);
    void setEmail(string newEmail);
    void setAddress(string newAddress);
    string getName();
    string getLastName();
    int getId();
    int getUserId();
};
