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
    int id;
    string firstname, lastname, phoneNumber, email, fullAddress;
};

void writeToEndFile(Friend friends)
{
    ofstream file;
    file.open( "INOUT.txt", std::ios::app);
    if(file.good())
    {
        file << friends.id << "|";
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
        Sleep(1500);
    }
}

void saveFriendsToFile(vector<Friend> friends, int amountFriends)
{
    ofstream file;
    file.open( "INOUT.txt", std::ios::out);
    if(file.good())
    {
        for(int i = 0; i < amountFriends; i++)
        {
            file << friends[i].id << "|";
            file << friends[i].firstname << "|";
            file << friends[i].lastname << "|";
            file << friends[i].phoneNumber << "|";
            file << friends[i].email << "|";
            file << friends[i].fullAddress << "|" << endl;
        }
        file.close();
    }
    else
    {
        cout << "Blad pliku" << endl;
        Sleep(500);
    }
}

int getLineInFile ()
{
    int sumOfLine = 0;
    string line;
    ifstream file;
    file.open("INOUT.txt");
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
        cout << "Brak pliku/blad otwarcia pliku" << endl;
        Sleep(500);
        file.close();
        return 0;
    }
    file.close();
    return sumOfLine;
}

vector<string> split(const string& line, char separator)
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

int getFriendsFromFile(vector<Friend> &friends)
{
    fstream file;
    int sumOfLine = getLineInFile();
    int amountFriends = sumOfLine - 1;
    string line = "";
    Friend temporary;

    file.open( "INOUT.txt", std::ios::in);
    if(file.good())
    {
        for(int i = 0; i < amountFriends; i++)
        {
            getline(file, line);
            vector<string> splited = split(line, '|');

            temporary.id = stoi(splited[0]);
            temporary.firstname = splited[1];
            temporary.lastname = splited[2];
            temporary.phoneNumber = splited[3];
            temporary.email = splited[4];
            temporary.fullAddress = splited[5];

            friends.push_back(temporary);
        }
        file.close();
        return amountFriends;
    }
    else
    {
        cout << "Nie wczytano pliku prawidlowo" << endl;
        Sleep(1500);
        file.close();
        return 0;
    }
}

int addFriend(vector<Friend> &friends, int amountFriends)
{
    string temporary;
    Friend temporarySaveToFile;
    system("CLS");
    if(amountFriends < 1000)
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
        temporarySaveToFile.id = amountFriends + 1;

        friends.push_back(temporarySaveToFile);
        writeToEndFile(temporarySaveToFile);

        cout << "Poprawnie dodano nowego adresata" << endl;
        Sleep(1500);
        return friends[amountFriends].id;
    }
    else
    {
        cout << "Brak mozliwosci dodania nowych uzytkownikow. Pelna baza!" << endl;
        Sleep(500);
        return 1000;
    }
}

void searchFriends(vector<Friend> &friends, int amountFriends)
{
    string temporary;
    char choice;
    short sum = 0;
    system("CLS");
    cout << "1. Wyszukaj po imieniu" << endl;
    cout << "2. Wyszukaj po nazwisku" << endl;
    cout << "3. Powrot do menu glownego" << endl;
    cin >> choice;

    if(choice == '1')
    {
        cout << "Podaj imie do wyszukania: ";
        cin >> temporary;
        for(int i = 0; i < amountFriends; i++)
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
            Sleep(2000);
        }
        else
        {
            cout << "Nie masz przyjaciol o takim imieniu :(" << endl;
            Sleep(500);
        }
    }
    else if(choice == '2')
    {
        cout << "Podaj nazwisko do wyszukania: ";
        cin >> temporary;
        for(int i = 0; i < amountFriends; i++)
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
            Sleep(1000);
        }
        else
        {
            cout << "Nie masz przyjaciol o takim nazwisku :(" << endl;
            Sleep(1000);
        }
    }
    else if(choice == '3')
    {
        cout << "Powrot do menu glownego" << endl;
        Sleep(1000);
    }
}

void viewAllFriends(vector<Friend> &friends, int amountFriends)
{
    if(amountFriends == 0)
    {
        cout << "Brak adresatow do wyswietlenia " << endl;
        Sleep(500);
    }
    else
    {
        for(int i = 0; i < amountFriends; i++)
        {
            if(friends[i].id != 0)
            {
                cout <<"Dane adresata: "<< friends[i].id << " " << friends[i].firstname << " " << friends[i].lastname << " " <<friends[i].phoneNumber << " " << friends[i].email << " " <<friends[i].fullAddress << endl;
            }
        }
        Sleep(1000);
    }
}

int usunAdresata(vector<Friend> &friends, int amountFriends)
{
    if(amountFriends == 0)
    {
        cout << "Brak adresatow do usuniecia" << endl;
        Sleep(500);
        return amountFriends;
    }
    else
    {
        short ID = -1;
        char temporary;
        cout << "Podaj ID adresata do usuniecia: ";
        cin >> ID;
        if(ID <= amountFriends && ID > 0)
        {
            cout <<"Dane adresata: "<< friends[ID-1].id << " " << friends[ID-1].firstname << " " << friends[ID-1].lastname << " " <<friends[ID-1].phoneNumber << " " << friends[ID-1].email << " " <<friends[ID-1].fullAddress << endl;
            cout << "Czy na pewno chcesz usunac adresata - wcisnij 't'" << endl;
            cin >> temporary;
            switch(temporary)
            {
                case 't':
                {
                    int i = ID - 1;
                    friends.erase(remove_if(friends.begin(), friends.end(), [&](Friend const &oneFriend)
                    {
                        return oneFriend.id == ID;
                    }), friends.end());

                    for(i; i < friends.size(); i++)
                    {
                        friends[i].id = friends[i].id - 1;
                    }
                    cout << "Poprawnie usunieto osobe z ksiazki" <<endl;
                    Sleep(500);
                    return (friends[i].id - 1);
                }
                default:
                {
                    cout << "Powrot do menu glownego" << endl;
                    Sleep(500);
                    return amountFriends;
                }
            }

        }
        else
        {
            cout << "Brak adresata do usuniecia, nastepuje powrot do menu glownego" << endl;
            Sleep(500);
            return amountFriends;
        }
    }
}

void edytujAdresata(vector<Friend> &friends, int amountFriends)
{
    if(amountFriends == 0)
    {
        cout << "Brak adresatow do edycji" << endl;
        Sleep(500);
    }
    else
    {
        string temporary;
        char choice;
        int ID;
        system("CLS");
        cout << "Podaj ID adresata do edytowania: ";
        cin >> ID;
        if (ID <= amountFriends)
        {
            cout << "Edycja dotyczy osoby :"<<endl;
            cout << friends[ID-1].id << " " << friends[ID-1].firstname << " " << friends[ID-1].lastname << " " <<friends[ID-1].phoneNumber << " " << friends[ID-1].email << " " <<friends[ID-1].fullAddress << endl << endl;
            cout << "1. Zmien imie adresata" << endl;
            cout << "2. Zmien nazwisko adresata" << endl;
            cout << "3. Zmien numer telefonu adresata" << endl;
            cout << "4. Zmien email adresata" << endl;
            cout << "5. Zmien adres zamieszkania adresata" << endl;
            cout << "6. Powrot do menu glownego" << endl;
            cin >> choice;
            switch(choice)
            {
                case '1':
                    {
                        cout << "Podaj imie do zmiany: ";
                        cin >> temporary;
                        friends[ID-1].firstname = temporary;
                        cout << "Dokonano poprawnej aktualizacji!";
                        Sleep(1000);
                        break;
                    }
                case '2':
                    {
                        cout << "Podaj nazwisko do zmiany: ";
                        cin >> temporary;
                        friends[ID-1].lastname = temporary;
                        cout << "Dokonano poprawnej aktualizacji!";
                        Sleep(1000);
                        break;
                    }
                case '3':
                    {
                        cout << "Podaj numer telefonu do zmiany: ";
                        cin >> temporary;
                        friends[ID-1].phoneNumber = temporary;
                        cout << "Dokonano poprawnej aktualizacji!";
                        Sleep(1000);
                        break;
                    }
                case '4':
                    {
                        cout << "Podaj email do zmiany: ";
                        cin >> temporary;
                        friends[ID-1].email = temporary;
                        cout << "Dokonano poprawnej aktualizacji!";
                        Sleep(1000);
                        break;
                    }

                case '5':
                    {
                        cout << "Podaj adres do zmiany: ";
                        cin.sync();
                        getline(cin, temporary);
                        friends[ID-1].fullAddress = temporary;
                        cout << "Dokonano poprawnej aktualizacji!";
                        Sleep(1000);
                        break;
                    }

                case '6':
                    {
                        cout << "Powrot do menu glownego!" << endl;
                        Sleep(1500);
                        break;
                    }

                default:
                    {
                        cout << "Bledna opcja! Powrot do menu glownego" << endl;
                        Sleep(500);
                        break;
                    }
            }
        }
        else
        {
            cout << "Nie ma takiej osoby w ksiazce adresowej" << endl;
            Sleep(1500);
        }
    }
}

int main()
{
    vector<Friend> friends;
    int amountFriends = 0;
    char choice;

    amountFriends = getFriendsFromFile(friends);

    while(1)
    {
        system("cls");
        cout << "1. Dodaj adresata" << endl;
        cout << "2. Wyszukaj" << endl;
        cout << "3. Wyswietl wszystkich adresatow" << endl;
        cout << "4. Usun adresata" << endl;
        cout << "5. Edytuj adresata" << endl;
        cout << "9. Zakoncz program" << endl;
        cin >> choice;

        switch(choice)
        {
            case '1':
            {
                amountFriends = addFriend(friends, amountFriends);
                break;
            }
            case '2':
            {
                searchFriends(friends, amountFriends);
                break;
            }
            case '3':
            {
                viewAllFriends(friends, amountFriends);
                break;
            }
            case '4':
            {
                amountFriends = usunAdresata(friends, amountFriends);
                saveFriendsToFile(friends, amountFriends);
                break;
            }
            case '5':
            {
                edytujAdresata(friends, amountFriends);
                saveFriendsToFile(friends, amountFriends);
                break;
            }
            case '9':
            {
                exit(0);
                break;
            }
            default:
            {
                cout << "Wpisz poprawna wartosc" << endl;
                Sleep(500);
                break;
            }
        }
    }
    return 0;
}
