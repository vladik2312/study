#include <iostream>
#include <ctime>
#include <string>
#include <chrono>

using namespace std;
using namespace chrono;
bool win = false;
int counter = 0;
auto start_time = steady_clock::now();
string generate(int leght, int settings)
{
    char rand_password;

    string password = "";
    switch (settings)
    {
    case (1):
        for (int i = 0; i < leght; i++)
        {
            rand_password = 33 + rand() % (128 - 33);
            password = password + rand_password;
        }
        break;
    case (2):
        for (int i = 0; i < leght; i++)
        {
            rand_password = 48 + rand() % (80);

            if (57 < (int)rand_password && (int)rand_password < 65 || 90 < (int)rand_password && (int)rand_password < 97)
            {
                i = i - 1;
            }
            else
            {
                password = password + rand_password;
            }
        }
        break;
    case (3):
        for (int i = 0; i < leght; i++)
        {
            rand_password = 48 + rand() % (10);
            password = password + rand_password;
        }
        break;
    }
    return password;
}
void generateStringsset(string prefix, int length, string pass)
{
    if (!win)
    {
        if (length == 0)
        { // якщо довжина стрінгу дорівнює 0, то виводимо стрінг на екран
            if (prefix == pass)
            {
                cout << "win" << endl
                     << "the number of retrieved passwords :" << counter << endl;
                counter = 0;
                win = true;
            }
        }
        else
        { // інакше генеруємо всі можливі комбінації
            for (char c = 48; c <= 58; c++)
            {
                string newPrefix = prefix + c;                   // додаємо символ до стрінгу
                generateStringsset(newPrefix, length - 1, pass); // викликаємо функцію рекурсивно зі стрінгом меншої довжини
            }
            counter++;
        }
    }
}
void generateStrings(string prefix, int length, string pass)
{
    if (!win)
    {
        if (length == 0)
        { // якщо довжина стрінгу дорівнює 0, то виводимо стрінг на екран
            if (prefix == pass)
            {
                cout << "win" << endl
                     << "the number of retrieved passwords :" << counter << endl;
                counter = 0;
                win = true;
            }
        }
        else
        { // інакше генеруємо всі можливі комбінації
            for (char c = 33; c <= 126; c++)
            {
                string newPrefix = prefix + c;                // додаємо символ до стрінгу
                generateStrings(newPrefix, length - 1, pass); // викликаємо функцію рекурсивно зі стрінгом меншої довжини
            }
            counter++;
        }
    }
}

int main()
{
    srand(time(0));
    string password;

    int set;
    cout << "1.all characters " << endl
         << "2.only letters and numbers" << endl
         << "3.only numbers" << endl
         << "4.my pass" << endl;
    cin >> set;
    if (0 > set || set > 4)
        set = 1;
    if (set == 4)
    {
        cout << "Enter password: ";
        cin >> password;
    }
    else
    {
        int length;
        cout << "Size of random password" << endl;
        cin >> length;

        password = generate(length, set);
    }

    cout << "youe pass is :" << password << endl;

    start_time = steady_clock::now();
    if (set == 3)
    {
        generateStringsset("", password.length(), password);
    }
    else
    {

        generateStrings("", password.length(), password);
    }
    auto end_time = steady_clock::now();

    auto elapsed_seconds = duration_cast<milliseconds>(end_time - start_time).count(); // отримуємо кількість секунд між початком і кінцем відліку

   cout << "Elapsed time: " << elapsed_seconds << " miliseconds" << endl; // виводимо час, що пройшов

    return 0;
}

/*
    for (char i = 0;i<127;i++){
cout<<i<<"  number  "<< (int)i<<endl;
    }*/
