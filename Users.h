#include <iostream>
#include <vector>

using namespace std;

string separateLine(string &line);

class User {
    string login, password;
    int id;
    static int globalUserId;
    static int globalLoggedUserId;

public:
    User();
    ~User();

    void setGlobalLoggedUserId();
    int getGlobalLoggedUserId();
    void setGlobalUserId();
    int getGlobalUserId();
    void setUserData();
    void setUserDataFromFile(string dataInLine);
    string getUserDataInLine();
    bool checkUserLoginAndPassword(User & userToLog);

    void setLogin(string newLogin);
    void setPassword(string newPassword);
    void setId();

    string getLogin();
    string getPassword();
    int getId();
};
