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
        system("pause");
    }
}

void saveFriendsToFile(vector<Friend> &friends, int amountFriends)
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
        system("pause");
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
        system("pause");
        file.close();
        return 0;
    }
    file.close();
    return sumOfLine;
}

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

void getFriendsFromFile(vector<Friend> &friends)
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
    }
    else
    {
        cout << "Nie wczytano pliku prawidlowo" << endl;
        system("pause");
        file.close();
    }
}

int addFriend(vector<Friend> &friends, int amountFriends)
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

        temporarySaveToFile.id = friends[friends.size()-1].id + 1;
        friends.push_back(temporarySaveToFile);
        writeToEndFile(temporarySaveToFile);
        cout << "Poprawnie dodano nowego adresata" << endl;
        system("pause");
        return (amountFriends + 1);
    }
    else
    {
        cout << "Brak mozliwosci dodania nowych uzytkownikow. Pelna baza!" << endl;
        system("pause");
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
            system("pause");
        }
        else
        {
            cout << "Nie masz przyjaciol o takim imieniu :(" << endl;
            system("pause");
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
            system("pause");
        }
        else
        {
            cout << "Nie masz przyjaciol o takim nazwisku :(" << endl;
            system("pause");
        }
    }
    else if(choice == '3')
    {
        cout << "Powrot do menu glownego" << endl;
        system("pause");
    }
}

void viewAllFriends(vector<Friend> &friends, int amountFriends)
{
    if(amountFriends == 0)
    {
        cout << "Brak adresatow do wyswietlenia " << endl;
        system("pause");
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
        system("pause");
    }
}

int usunAdresata(vector<Friend> &friends, int amountFriends)
{
    if(amountFriends == 0)
    {
        cout << "Brak adresatow do usuniecia" << endl;
        system("pause");
        return amountFriends;
    }
    else
    {
        short ID = -1;
        int searchID = -1;
        char temporary;
        cout << "Podaj ID adresata do usuniecia: ";
        cin >> ID;

        for(int j = 0; j < friends.size(); j++)
        {
            if(friends[j].id == ID)
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
                    system("pause");
                    saveFriendsToFile(friends, amountFriends - 1);
                    return (amountFriends - 1);
                }
                default:
                {
                    cout << "Powrot do menu glownego" << endl;
                    system("pause");
                    return amountFriends;
                }
            }

        }
        else
        {
            cout << "Brak adresata do usuniecia, nastepuje powrot do menu glownego" << endl;
            system("pause");
            return amountFriends;
        }
    }
}

void edytujAdresata(vector<Friend> &friends, int amountFriends)
{
    if(amountFriends == 0)
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

        for(int j = 0; j < friends.size(); j++)
        {
            if(friends[j].id == ID)
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
            saveFriendsToFile(friends, amountFriends);
        }
        else
        {
            cout << "Nie ma takiej osoby w ksiazce adresowej" << endl;
            system("pause");
        }
    }
}

int main()
{
    vector<Friend> friends;
    int amountFriends = 0;
    char choice;
    getFriendsFromFile(friends);

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

        amountFriends = friends.size();

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
                break;
            }
            case '5':
            {
                edytujAdresata(friends, amountFriends);
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
                system("pause");
                break;
            }
        }
    }
    return 0;
}
