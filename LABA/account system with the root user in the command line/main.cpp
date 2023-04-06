#include <iostream>
#include <fstream>
#include <cstring>
#include <Windows.h>
using namespace std;

struct User
{
    string username;
    int password_length;
    string password;
    bool is_blocked = 0;
    bool has_password_restrictions = 0;
};

void addUserToFile(User user)
{
    ofstream file("accounts.txt", ios::app);
    int password_length = user.password.length();
    if (file.is_open())
    {
        file << user.username << endl;
        file << password_length << endl;
        file << user.password << endl;
        file << user.is_blocked << endl;
        file << user.has_password_restrictions << endl;
        file.close();
        cout << "The account has been successfully added to the file." << endl;
    }
    else
    {
        cout << "Error opening file." << endl;
    }
}

User getUserFromFile1(User user)
{
    ifstream file("accounts.txt");
    User temp;

    while (file >> temp.username >> temp.password_length >> temp.password >> temp.is_blocked >> temp.has_password_restrictions)
    {
    	
        if (temp.username == user.username && temp.password == user.password)
        {
            return temp;
        }
        
    }

    // якщо акаунт не знайдено, повертаємо порожню структуру
    User empty_user = {"", 0, "", false, false};
    return empty_user;
}

string search(User user)
{
    ifstream file("accounts.txt");
    User temp;
    while (file >> temp.username >> temp.password_length >> temp.password >> temp.is_blocked >> temp.has_password_restrictions)
    {
        if (temp.username == user.username)
            return temp.username;   
    }
    // якщо акаунт не знайдено, повертаємо порожню структуру
    return "NULL";
}

void updateUserInFile(User user)
{
    ifstream infile("accounts.txt");
    ofstream outfile("temp.txt");
    int password_length = user.password.length();
    string line;
    bool user_found = false;
    int counter = 0;
    if (infile.is_open() && outfile.is_open())
    {
        // Зчитуємо дані з файлу та записуємо оновлені дані в новий файл
        while (getline(infile, line))
        {
            if (line == user.username)
            {
                user_found = true;
                outfile << user.username << endl;
                outfile << password_length << endl;
                outfile << user.password << endl;
                outfile << user.is_blocked << endl;
                outfile << user.has_password_restrictions << endl;
                cout << "The account has been successfully updated." << endl;
                counter = 4;
            }
            else
            {
                if (counter == 0)
                {

                    outfile << line << endl;
                }
                else
                {
                    counter = counter - 1;
                }
            }
        }

        infile.close();
        outfile.close();

        // Перейменовуємо тимчасовий файл на оригінальний
        if (user_found)
        {
            if (remove("accounts.txt") != 0)
            {
                cout << "Error deleting original file." << endl;
                return;
            }
            if (rename("temp.txt", "accounts.txt") != 0)
            {
                cout << "Error renaming temporary file." << endl;
                return;
            }
        }
        else
        {
            cout << "User not found in the file." << endl;
            remove("temp.txt");
        }
    }
    else
    {
        cout << "Error opening files." << endl;
    }
}

void displayAllUsers()
{
    ifstream file("accounts.txt");
    string line;

    if (file.is_open())
    {
        int counter = 5;
        while (getline(file, line))
        {
            cout << line << " ";
            counter = counter - 1;
            if (counter == 0)
            {
                counter = 5;
                cout << endl;
            }
        }
        file.close();
    }
    else
    {
        cout << "Error opening file." << endl;
    }
}

bool hasNoRepeatingCharacters(string str) {
    for (int i = 1; i < str.length(); i++) {
        if (str[i] == str[i - 1]) {
            return false;
        }
    }
    return true;
}

int main()
{

    int meny = 0;
    int choice = 0;
    User user;
User temp;
    do
    {

        cout << "1. Add user" << endl;
        cout << "2. Verify the user" << endl;
        cout << "3. Exit the program" << endl;
        cout << "Select an option: ";
        cin >> choice;
		if (choice !=1 &&choice!=2&&choice!=3) choice = 3;
        if (choice == 1)
        {

            cout << "Enter username: ";
            cin >> user.username;
            cout << "Enter password: ";
            cin >> user.password;
            
			if (search(user) == "NULL")
            addUserToFile(user);
			else cout<< "this account has already been created"<< endl;
            
			
			
			system("pause");
            system("cls");
        }
        else if (choice == 2)
        {
            meny = 0;
            cout << "Enter username: ";
            cin >> user.username;
            cout << "Enter password: ";
            cin >> user.password;

            system("cls");

            if (getUserFromFile1(user).username != "")
            {

                if (user.username == "root")
                {
                    do
                    {
					 	temp = user;
                        cout << "User : " << user.username << endl;
                        cout << "1. Change password" << endl;
                        cout << "2. List of users" << endl;
                        cout << "3. Add zero user" << endl;
                        cout << "4. Ban" << endl;
                        cout << "5. Lock pass" << endl;
                        cout << "6. Log out" << endl;
                        cout << "Select an option: ";
                        cin >> meny;
                        

                        if (meny == 1)
                    {
                        char temp2[50];
                        temp = user;
                        cout << "Enter old password: ";
                        cin >> temp.password;
                        if (temp.password == user.password)
                        {

                            cout << "Enter  new password: ";
                            cin >> temp2;
                            cout << "confirm password: ";
                            cin >> temp.password;
                            if (temp2 == temp.password)
                            {
                                updateUserInFile(temp);
                                cout << "your pass is change" << endl;
                                system("pause");
                            }
                            else
                            {
                                cout << "try again" << endl;
                            }
                        }
                        else
                        {
                            cout << "error";
                        }
                        system("cls");
                    }

                    system("cls");
					
					if (meny == 2)
					{
						displayAllUsers();
						system("pause");
						system("cls");
						}
	

					if (meny == 3)
					{
						cout << "Enter username: ";
			            cin >> temp.username;
			            temp.password ="%$%";
			            addUserToFile(temp);
			            cout << "new user add sucsesfol"<<endl;
			            system("pause");
			            system("cls");
						
					}
					if (meny == 4){
						
						cout << "Select account :";
						cin >> temp.username;
						if (getUserFromFile1(temp).username!=""){
						
						temp = getUserFromFile1(temp);
						temp.is_blocked = !temp.is_blocked;
						updateUserInFile(temp);
						}
						else{
							cout << "account not found "<<endl;
						}
						system("pause");
						system("cls");
					}
					if (meny == 5){
						cout << "Select account :";
						cin >> temp.username;
						if (getUserFromFile1(temp).username!=""){
						
						temp = getUserFromFile1(temp);
						temp.has_password_restrictions = !temp.has_password_restrictions;
						updateUserInFile(temp);
						}
						else{
							cout << "account not found "<<endl;
						}
						system("pause");
						system("cls");	
					}		
					}while (meny != 6);
                
            }
            else
            {if (getUserFromFile1(user).is_blocked) {
						cout << " Accaunt is blocked"<<endl;
						system("pause");
						system("cls");
		   }else{
		   
			    do
                {
                    cout << "User : " << user.username << endl;
                    cout << "1. Change password" << endl;
                    cout << "2. Log out" << endl;
                    cout << "Select an option: ";
                    cin >> meny;
                    if (meny == 1)
                    {
                        char temp2[50];
                        User temp = user;
                        cout << "Enter old password: ";
                        cin >> temp.password;
                        if (temp.password == user.password)
                        {

                            cout << "Enter  new password: ";
                            cin >> temp2;
                            cout << "confirm password: ";
                            cin >> temp.password;
                            if (temp2 == temp.password)
                            {
                            	
                            	if(hasNoRepeatingCharacters(temp2)&&!user.has_password_restrictions){
                            	updateUserInFile(temp);
                                cout << "your pass is change" << endl;
                                user.password = temp.password;
                                system("pause");
								}else{

									cout << "This pass is blocked for you"<< endl;
									system("pause");
								}

                            }
                            else
                            {
                                cout << "try again" << endl;
                            }
                        }
                        else
                        {
                            cout << "error";
                        }
                        system("cls");
                    }


                    system("cls");
                } while (meny != 2);
            }
        }}
        else
        {
            cout << "The login or password is not valid" << endl;
            system("pause");
        	system("cls");
        }
    }
}
while (choice != 3)
    ;

return 0;
}
