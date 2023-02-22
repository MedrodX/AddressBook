#include <iostream>
#include <windows.h>
#include <string>
#include <cstdlib>
#include <fstream>
#include <vector>
#include <sstream>
#include <algorithm>

using namespace std;

struct Friend
{
    int id, idUser;
    string firstname, lastname, phoneNumber, email, fullAddress;
};

struct User
{
    int id;
    string name, password;
};

vector<string> split(const string &line, char separator)
{
    vector<string> result;
    stringstream ss(line);
    string token;
    while (getline(ss, token, separator))
    {
        result.push_back(token);
    }
    return result;
}

int getLineInFile(string fileNameTXT)
{
    int sumOfLine = 0;
    string line;
    ifstream file;
    file.open(fileNameTXT);
    if(file.good())
    {
        while(!file.eof())
        {
            getline(file, line);
            sumOfLine++;
        }
    }
    else
    {
        cout << "Brak pliku/blad otwarcia pliku " << fileNameTXT << endl;
        system("pause");
        file.close();
        return 0;
    }
    file.close();
    return sumOfLine;
}

void writeAddressToEndFile(Friend friends, string fileName)
{
    ofstream file;
    file.open(fileName, ios::app);
    if(file.good())
    {
        file << friends.id << "|";
        file << friends.idUser << "|";
        file << friends.firstname << "|";
        file << friends.lastname << "|";
        file << friends.phoneNumber << "|";
        file << friends.email << "|";
        file << friends.fullAddress << "|" << endl;
        file.close();
    }
    else
    {
        cout << "Blad pliku" << endl;
        system("pause");
    }
}

void writeUserToEndFile(User users)
{
    ofstream file;
    file.open( "Uzytkownicy.txt", ios::app);
    if(file.good())
    {
        file << users.id << "|";
        file << users.name << "|";
        file << users.password << "|" << endl;
        file.close();
    }

    else
    {
        cout << "Blad pliku Uzytkownicy.txt" << endl;
        system("pause");
    }
}

void saveFriendsToTempFile(vector<Friend> &friends, int idUser)
{
    fstream file;
    ofstream temp;
    file.open( "Adresaci.txt", ios::in);
    temp.open( "Temp.txt", ios::out);
    Friend temporary;
    string line = "";
    int sumOfLine = getLineInFile("Adresaci.txt");
    unsigned int j = 0;
    sumOfLine--;
    if(!file.eof())
    {
        for(int i = 0; i < sumOfLine; i++)
        {
            getline(file, line);
            vector<string> splited = split(line, '|');
            temporary.id = stoi(splited[0]);
            temporary.idUser = stoi(splited[1]);
            temporary.firstname = splited[2];
            temporary.lastname = splited[3];
            temporary.phoneNumber = splited[4];
            temporary.email = splited[5];
            temporary.fullAddress = splited[6];

            if(idUser != temporary.idUser)
            {
                temp << temporary.id << "|";
                temp << temporary.idUser << "|";
                temp << temporary.firstname << "|";
                temp << temporary.lastname << "|";
                temp << temporary.phoneNumber << "|";
                temp << temporary.email << "|";
                temp << temporary.fullAddress << endl;
            }
            else if(idUser == temporary.idUser && temporary.id == friends[j].id)
            {
                if(j < friends.size())
                {
                    temp << friends[j].id << "|";
                    temp << friends[j].idUser << "|";
                    temp << friends[j].firstname << "|";
                    temp << friends[j].lastname << "|";
                    temp << friends[j].phoneNumber << "|";
                    temp << friends[j].email << "|";
                    temp << friends[j].fullAddress << endl;
                    j++;
                }
            }
            else
            {
                continue;
            }
        }
    }
    else
    {
        cout << "Blad pliku" << endl;
        system("pause");
    }
    file.close();
    temp.close();

    remove("Adresaci.txt");
    rename("temp.txt","Adresaci.txt");
}

void saveUsersToFile(vector<User> &users)
{
    ofstream file;
    file.open( "Uzytkownicy.txt", ios::app);
    file.close();
    file.open( "Uzytkownicy.txt", ios::out);
    if(file.good())
    {
        for(unsigned int i = 0; i < users.size(); i++)
        {
            file << users[i].id << "|";
            file << users[i].name << "|";
            file << users[i].password << "|" << endl;
        }
        file.close();
    }
    else
    {
        cout << "Blad pliku Uzytkownicy.txt" << endl;
        system("pause");
    }
}

void getFriendsFromFile(vector<Friend> &friends, int idUser, int &maxID)
{
    fstream file;

    file.open( "Adresaci.txt", ios::app);
    file.close();

    int sumOfLine = getLineInFile("Adresaci.txt");
    string line = "";
    Friend temporary;
    file.open( "Adresaci.txt", ios::in);
    if(file.good())
    {
        for(int i = 0; i < (sumOfLine - 1); i++)
        {
            getline(file, line);
            vector<string> splited = split(line, '|');

            temporary.id = stoi(splited[0]);
            maxID = stoi(splited[0]);
            temporary.idUser = stoi(splited[1]);
            if(temporary.idUser == idUser)
            {
                temporary.firstname = splited[2];
                temporary.lastname = splited[3];
                temporary.phoneNumber = splited[4];
                temporary.email = splited[5];
                temporary.fullAddress = splited[6];
                friends.push_back(temporary);
            }
            else
            {
                continue;
            }
        }
        file.close();
    }
    else
    {
        cout << "Nie wczytano pliku prawidlowo" << endl;
        system("pause");
        file.close();
    }
}

void getDataFromFile(vector<User> &users)
{
    fstream file;
    file.open("Uzytkownicy.txt", ios::app);
    file.close();
    int sumOfLine = getLineInFile("Uzytkownicy.txt");
    string line = "";

    file.open("Uzytkownicy.txt", ios::in);
    if(file.good())
    {
        User temporary;
        for(int i = 0; i < (sumOfLine - 1); i++)
        {
            getline(file, line);
            vector<string> splited = split(line, '|');
            temporary.id = stoi(splited[0]);
            temporary.name = splited[1];
            temporary.password = splited[2];

            users.push_back(temporary);
        }
        file.close();
    }
    else
    {
        cout << "Nie wczytano pliku Uzytkownicy.txt prawidlowo" << endl;
        system("pause");
        file.close();
    }
}

void registering(vector<User> &users)
{
    string name, password;
    User temporaryUser;
    system("CLS");
    cout << "Podaj nazwe uzytkownika:" << endl;
    cin >> temporaryUser.name;

    unsigned int i = 0;
    while(i < users.size())
    {
        if(users[i].name == temporaryUser.name)
        {
            cout << "Taki uzytkownik juz istnieje. Wpisz inna nazwe uzytkownika:" << endl;
            cin >> temporaryUser.name;
            i = 0;
        }
        else
        {
            i++;
        }
    }

    cout << "Podaj haslo:" << endl;
    cin >> temporaryUser.password;

    if(users.size() == 0)
    {
        temporaryUser.id = 1;
    }
    else
    {
        temporaryUser.id = users[users.size()-1].id + 1;
    }
    users.push_back(temporaryUser);
    writeUserToEndFile(temporaryUser);
    cout << "Uzytkownik zostal zapisany. Konto zalozone." << endl;
    system("pause");
}

int logging(vector<User> &users)
{
    string name, password;
    system("cls");
    cout << "Podaj nazwe uzytkownika: " << endl;
    cin >> name;

    unsigned int i = 0;
    while(i < users.size())
    {
        if(users[i].name == name)
        {
            for(int j = 0; j < 3; j++)
            {
                system("cls");
                cout << "Podaj haslo. Pozostalo prob: " << 3 - j <<endl;
                cin >> password;
                if(users[i].password == password)
                {
                    cout << "Udane logowanie." << endl;
                    system("pause");
                    return users[i].id;
                }
                else
                {
                    cout << "Podales nieprawidlowe haslo!" << endl;
                    system("pause");
                }
            }
            cout << "Podales bledne haslo trzykrotnie. Poczekaj 3 sekundy przed kolejna proba" << endl;
            Sleep(3000);
            return 0;
        }
        else
        {
            i++;
        }
    }
    cout << "Nie ma uzytkownika z takim loginem" << endl;
    system("pause");
    return 0;
}

void changePassword(int &idLoggedUser)
{
    vector<User> users;
    getDataFromFile(users);

    string password;
    cout << "Podaj nowe haslo: ";
    cin >> password;
    for (unsigned int i = 0; i < (users.size()); i++)
    {
        if(users[i].id == idLoggedUser)
        {
            users[i].password = password;
            cout << "Haslo zostalo zmienione" << endl;
            system("pause");
        }
    }
    saveUsersToFile(users);
}

void addFriend(vector<Friend> &friends, int idUser, int &maxID)
{
    string temporary;
    Friend temporarySaveToFile;
    system("CLS");
    if(friends.size() < 1000)
    {
        cout << "Podaj firstname adresata do dodania: ";
        cin >> temporarySaveToFile.firstname;
        cout << "Podaj nazwisko adresata do dodania: ";
        cin >> temporarySaveToFile.lastname;
        cout << "Podaj numer telefonu adresata do dodania: ";
        cin >> temporarySaveToFile.phoneNumber;
        cout << "Podaj email adresata do dodania: ";
        cin >> temporarySaveToFile.email;
        cout << "Podaj adres zamieszkania adresata do dodania: ";
        cin.sync();
        getline(cin, temporary);
        temporarySaveToFile.fullAddress = temporary;
        temporarySaveToFile.idUser = idUser;

        temporarySaveToFile.id = maxID + 1;
        maxID++;
        friends.push_back(temporarySaveToFile);
        writeAddressToEndFile(temporarySaveToFile, "Adresaci.txt");
        cout << "Poprawnie dodano nowego adresata" << endl;
        system("pause");
    }
    else
    {
        cout << "Brak mozliwosci dodania nowych uzytkownikow. Pelna baza!" << endl;
        system("pause");
    }
}

void searchFriends(vector<Friend> &friends)
{
    string temporary;
    char choice;
    short sum = 0;
    system("CLS");
    cout << "1. Wyszukaj po imieniu" << endl;
    cout << "2. Wyszukaj po nazwisku" << endl;
    cout << "3. Powrot do menu glownego" << endl;
    cin >> choice;
    switch(choice)
    {
    case '1':
    {
        cout << "Podaj imie do wyszukania: ";
        cin >> temporary;
        for(unsigned int i = 0; i < friends.size(); i++)
        {
            if(friends[i].firstname == temporary)
            {
                cout <<"Dane adresata: "<< friends[i].id << " " << friends[i].firstname << " " << friends[i].lastname << " " <<friends[i].phoneNumber << " " << friends[i].email << " " <<friends[i].fullAddress << endl;
                sum++;
            }
        }
        if(sum > 0)
        {
            cout << "Masz " << sum << " przyjaciol o takim imieniu!" << endl;
            system("pause");
        }
        else
        {
            cout << "Nie masz przyjaciol o takim imieniu :(" << endl;
            system("pause");
        }
        break;
    }
    case '2':
    {
        cout << "Podaj nazwisko do wyszukania: ";
        cin >> temporary;
        for(unsigned int i = 0; i < friends.size(); i++)
        {
            if(friends[i].lastname == temporary)
            {
                cout <<"Dane adresata: "<< friends[i].id << " " << friends[i].firstname << " " << friends[i].lastname << " " <<friends[i].phoneNumber << " " << friends[i].email << " " <<friends[i].fullAddress << endl;
                sum++;
            }
        }
        if(sum > 0)
        {
            cout << "Masz " << sum << " przyjaciol o takim nazwisku!" << endl;
            system("pause");
        }
        else
        {
            cout << "Nie masz przyjaciol o takim nazwisku :(" << endl;
            system("pause");
        }
        break;
    }
    case '3':
    {
        cout << "Powrot do menu glownego" << endl;
        system("pause");
        break;
    }
    default:
    {
        cout << "Wpisz poprawna wartosc, powrót do menu g³ownego" << endl;
        system("pause");
        break;
    }
    }
}

void viewAllFriends(vector<Friend> &friends)
{
    if(friends.size() == 0)
    {
        cout << "Brak adresatow do wyswietlenia " << endl;
        system("pause");
    }
    else
    {
        for(unsigned int i = 0; i < friends.size(); i++)
        {
            if(friends[i].id != 0)
            {
                cout <<"Dane adresata: "<< friends[i].id << " " << friends[i].firstname << " " << friends[i].lastname << " " <<friends[i].phoneNumber << " " << friends[i].email << " " <<friends[i].fullAddress << endl;
            }
        }
        system("pause");
    }
}

void deleteAddress(vector<Friend> &friends, int &idUser, int &maxID)
{
    if(friends.size() == 0)
    {
        cout << "Brak adresatow do usuniecia" << endl;
        system("pause");
    }
    else
    {
        short ID = -1;
        int searchID = -1;
        char temporary;
        cout << "Podaj ID adresata do usuniecia: ";
        cin >> ID;

        for(unsigned int j = 0; j < friends.size(); j++)
        {
            if(friends[j].idUser == idUser && friends[j].id == ID)
            {
                searchID = j;
            }
        }

        if(searchID != -1)
        {
            cout <<"Dane adresata: "<< friends[searchID].id << " " << friends[searchID].firstname << " " << friends[searchID].lastname << " " <<friends[searchID].phoneNumber << " " << friends[searchID].email << " " <<friends[searchID].fullAddress << endl;
            cout << "Czy na pewno chcesz usunac adresata - wcisnij 't'" << endl;
            cin >> temporary;
            switch(temporary)
            {
            case 't':
            {
                friends.erase(remove_if(friends.begin(), friends.end(), [&](Friend const &oneFriend)
                {
                    return oneFriend.id == ID;
                }), friends.end());
                cout << "Poprawnie usunieto osobe z ksiazki" <<endl;
                saveFriendsToTempFile(friends, idUser);
                friends.clear();
                getFriendsFromFile(friends, idUser, maxID);
            }
            default:
            {
                cout << "Powrot do menu glownego" << endl;
                system("pause");
            }
            }
        }
        else
        {
            cout << "Brak adresata do usuniecia, nastepuje powrot do menu glownego" << endl;
            system("pause");
        }
    }
}

void editAddress(vector<Friend> &friends, int &idUser)
{
    if(friends.size() == 0)
    {
        cout << "Brak adresatow do edycji" << endl;
        system("pause");
    }
    else
    {
        string temporary;
        char choice;
        int ID, searchID = -1;
        system("CLS");
        cout << "Podaj ID adresata do edytowania: ";
        cin >> ID;

        for(unsigned int j = 0; j < friends.size(); j++)
        {
            if(friends[j].idUser == idUser && friends[j].id == ID)
            {
                searchID = j;
            }
        }

        if (searchID != -1)
        {
            cout << "Edycja dotyczy osoby :"<<endl;
            cout << friends[searchID].id << " " << friends[searchID].firstname << " " << friends[searchID].lastname << " " <<friends[searchID].phoneNumber << " " << friends[searchID].email << " " <<friends[searchID].fullAddress << endl << endl;
            cout << "1. Zmien imie adresata" << endl;
            cout << "2. Zmien nazwisko adresata" << endl;
            cout << "3. Zmien numer telefonu adresata" << endl;
            cout << "4. Zmien email adresata" << endl;
            cout << "5. Zmien adres zamieszkania adresata" << endl;
            cout << "6. Powrot do menu glownego" << endl;

            cin >> choice;
            cout << endl;
            switch(choice)
            {
                case '1':
                {
                    cout << "Podaj imie do zmiany: ";
                    cin >> temporary;
                    friends[searchID].firstname = temporary;
                    cout << "Dokonano poprawnej aktualizacji!"<<endl;
                    system("pause");
                    break;
                }
                case '2':
                {
                    cout << "Podaj nazwisko do zmiany: ";
                    cin >> temporary;
                    friends[searchID].lastname = temporary;
                    cout << "Dokonano poprawnej aktualizacji!"<<endl;
                    system("pause");
                    break;
                }
                case '3':
                {
                    cout << "Podaj numer telefonu do zmiany: ";
                    cin >> temporary;
                    friends[searchID].phoneNumber = temporary;
                    cout << "Dokonano poprawnej aktualizacji!"<<endl;
                    system("pause");
                    break;
                }
                case '4':
                {
                    cout << "Podaj email do zmiany: ";
                    cin >> temporary;
                    friends[searchID].email = temporary;
                    cout << "Dokonano poprawnej aktualizacji!"<<endl;
                    system("pause");
                    break;
                }

                case '5':
                {
                    cout << "Podaj adres do zmiany: ";
                    cin.sync();
                    getline(cin, temporary);
                    friends[searchID].fullAddress = temporary;
                    cout << "Dokonano poprawnej aktualizacji!"<<endl;
                    system("pause");
                    break;
                }

                case '6':
                {
                    cout << "Powrot do menu glownego!" << endl;
                    system("pause");
                    break;
                }

                default:
                {
                    cout << "Bledna opcja! Powrot do menu glownego" << endl;
                    system("pause");
                    break;
                }
            }
            saveFriendsToTempFile(friends, idUser);
        }
        else
        {
            cout << "Nie ma takiej osoby w ksiazce adresowej" << endl;
            system("pause");
        }
    }
}

void mainMenu(int &idLoggedUser)
{
    vector<Friend> friends;
    int check = idLoggedUser, maxID = 0;
    char choice;
    getFriendsFromFile(friends, idLoggedUser, maxID);

    while(1)
    {
        if(check == idLoggedUser)
        {
            system("cls");
            cout << "1. Dodaj adresata" << endl;
            cout << "2. Wyszukaj" << endl;
            cout << "3. Wyswietl wszystkich adresatow" << endl;
            cout << "4. Usun adresata" << endl;
            cout << "5. Edytuj adresata" << endl;
            cout << "8. Zmiana hasla" << endl;
            cout << "9. Wyloguj" << endl;
            cin >> choice;

            switch(choice)
            {
                case '1':
                {
                    addFriend(friends, idLoggedUser, maxID);
                    break;
                }
                case '2':
                {
                    searchFriends(friends);
                    break;
                }
                case '3':
                {
                    viewAllFriends(friends);
                    break;
                }
                case '4':
                {
                    deleteAddress(friends, idLoggedUser, maxID);
                    break;
                }
                case '5':
                {
                    editAddress(friends, idLoggedUser);
                    break;
                }
                case '8':
                {
                    changePassword(idLoggedUser);
                    break;
                }
                case '9':
                {
                    check = 0;
                    break;
                }
                default:
                {
                    cout << "Wpisz poprawna wartosc" << endl;
                    system("pause");
                    break;
                }
            }
        }
        else
        {
            cout << "Nastapi wylogowanie!" << endl;
            system("pause");
            break;
        }
    }
}

int main()
{
    vector<User> users;
    int idLoggedUser = 0;
    char choice;
    getDataFromFile(users);

    while(1)
    {
        if(idLoggedUser == 0 )
        {
            system("cls");
            cout << "1. Rejestracja" << endl;
            cout << "2. Logowanie" << endl;
            cout << "9. Zakoncz program" << endl;
            cin >> choice;
            switch(choice)
            {
            case '1':
            {
                registering(users);
                break;
            }
            case '2':
            {
                idLoggedUser = logging(users);
                if(idLoggedUser != 0)
                {
                    mainMenu(idLoggedUser);
                }
                idLoggedUser = 0;
                break;
            }
            case '9':
            {
                exit(0);
            }

            default:
            {
                cout << "Wpisz poprawna wartosc" << endl;
                system("pause");
                break;
            }
            }
        }
    }
    return 0;
}
