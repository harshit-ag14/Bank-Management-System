#include <iostream>
#include <fstream>
#include <cctype>
#include <iomanip>
#include <time.h>
#include <stdlib.h>
using namespace std;
class account
{
        int accountnumber;
        char name[50];
        int deposit;
        char type;

public:
        void create_account();
        void show_account();
        void modify_account();
        void deposit_funds(int);
        void draw_funds(int);
        void get_report();
        int get_accountnumber();
        int get_funds();
        char get_accounttype();
};

void account::create_account()
{
        accountnumber = rand();
        cout << "\n\t\tThe account Number is : " << accountnumber<<endl;
        cout << "\n\t\tEnter The Name of The account Holder : ";
        cin.ignore();
        cin.getline(name, 50);
        cout << "\n\t\tEnter account type (C-Current/S-Saving): ";
        cin >> type;
        type = toupper(type);
        cout << "\n\t\tEnter The Initial amount(500 or more for Saving and 1000 or more for current ): ";
        cin >> deposit;
        cout << "\n\t\tAccount Created Successfully...";
}

void account::show_account()
{
        cout << "\n\t\tAccount Number: " << accountnumber;
        cout << "\n\t\tAccount Holder Name: " << name;
        cout << "\n\t\tType of Account: " << type;
        cout << "\n\t\tBalance amount: " << deposit;
}

void account::modify_account()
{
        cout << "\n\t\tAccount Number: " << accountnumber;
        cout << "\n\t\tModify Account Holder Name: ";
        cin.ignore();
        cin.getline(name, 50);
        cout << "\n\t\tModify Type of Account: ";
        cin >> type;
        type = toupper(type);
}

void account::deposit_funds(int x)
{
        deposit += x;
}

void account::draw_funds(int x)
{
        deposit -= x;
}

void account::get_report()
{
        cout << accountnumber << setw(10) << " " << name << setw(10) << " " << type << setw(6) << deposit << endl;
}

int account::get_accountnumber()
{
        return accountnumber;
}

int account::get_funds()
{
        return deposit;
}

char account::get_accounttype()
{
        return type;
}

void write_account();
void display_sp(int);
void modify_account(int);
void delete_account(int);
void display_all();
void deposit_withdraw(int, int);

int main()
{
        srand(time(0));
        char opt;
        int num;
        for (;;)
        {
				cout << "\n\n";
                cout << "\n\t\tBank Management System";
                cout << "\n\t\t----------------------------------";
                cout << "\n\t\t1.Create New Account";
                cout << "\n\t\t2.Deposit Money";
                cout << "\n\t\t3.Withdraw Money";
                cout << "\n\t\t4.Check Balance";
                cout << "\n\t\t5.View All Account Holder List";
                cout << "\n\t\t6.Close an Account";
                cout << "\n\t\t7.Modify an Account";
                cout << "\n\t\t8.Exit the Program";
                cout << "\n\t\tOption: ";
                cin >> opt;
                system("cls");
                switch (opt)
                {
                case '1':
                        write_account();
                        break;
                case '2':
                        cout << "\n\t\tEnter The account No. : ";
                        cin >> num;
                        deposit_withdraw(num, 1);
                        break;
                case '3':
                        cout << "\n\t\tEnter The account No. : ";
                        cin >> num;
                        deposit_withdraw(num, 2);
                        break;
                case '4':
                        cout << "\n\t\tEnter The account No. : ";
                        cin >> num;
                        display_sp(num);
                        break;
                case '5':
                        display_all();
                        break;
                case '6':
                        cout << "\n\t\tEnter The account No. : ";
                        cin >> num;
                        delete_account(num);
                        break;
                case '7':
                        cout << "\n\t\tEnter The account No. : ";
                        cin >> num;
                        modify_account(num);
                        break;
                case '8':
                        cout << "\n\t\tThanks for using Bank Management System";
                        break;
                default:
                        cout << "\n\n\tInvalid Option\n";
                }
                cin.ignore();
                cin.get();
                if (opt == '8')
                {
                	break;
				}    
        }
        return 0;
}

void write_account()
{
        account ac;
        ofstream outFile;
        outFile.open("account.dat", ios::binary | ios::app);
        ac.create_account();
        outFile.write(reinterpret_cast<char *>(&ac), sizeof(account));
        outFile.close();
}

void display_sp(int n)
{
        account ac;
        bool flag = false;
        ifstream inFile;
        inFile.open("account.dat", ios::binary);
        if (!inFile)
        {
                cout << "\n\t\tFile couldn't be opened.";
                return;
        }
        cout << "\n\t\tBALANCE DETAILS\n";

        while (inFile.read(reinterpret_cast<char *>(&ac), sizeof(account)))
        {
                if (ac.get_accountnumber() == n)
                {
                        ac.show_account();
                        flag = true;
                }
        }
        inFile.close();
        if (flag == false)
        {
        	cout << "\n\t\tAccount number does not exist.";
		}
}

void modify_account(int n)
{
        bool found = false;
        account ac;
        fstream File;
        File.open("account.dat", ios::binary | ios::in | ios::out);
        if (!File)
        {
                cout << "\n\t\tFile couldn't be opened.";
                return;
        }
        while (!File.eof() && found == false)
        {
                File.read(reinterpret_cast<char *>(&ac), sizeof(account));
                if (ac.get_accountnumber() == n)
                {
                        ac.show_account();
                        cout << "\n\t\tEnter new account details: " << endl;
                        ac.modify_account();
                        int pos = (-1) * static_cast<int>(sizeof(account));
                        File.seekp(pos, ios::cur);
                        File.write(reinterpret_cast<char *>(&ac), sizeof(account));
                        cout << "\n\t\tRecord Updated.";
                        found = true;
                }
        }
        File.close();
        if (found == false)
        {
        	cout << "\n\t\tRecord Not Found.";
		}
}

void delete_account(int n)
{
        account ac;
        ifstream inFile;
        ofstream outFile;
        inFile.open("account.dat", ios::binary);
        if (!inFile)
        {
                cout << "\n\t\tFile couldn't be opened.";
                return;
        }
        outFile.open("Temp.dat", ios::binary);
        inFile.seekg(0, ios::beg);
        while (inFile.read(reinterpret_cast<char *>(&ac), sizeof(account)))
        {
                if (ac.get_accountnumber() != n)
                {
                        outFile.write(reinterpret_cast<char *>(&ac), sizeof(account));
                }
        }

        inFile.close();
        outFile.close();
        remove("account.dat");
        rename("Temp.dat", "account.dat");
        cout << "\n\t\tRecord Deleted.";
}

void display_all()
{
        int bankPassword = 12345, Password;
        cout << "\n\t\tEnter the Bank Password: ";
        cin >> Password;
        if (Password == bankPassword)
        {
                account ac;
                ifstream inFile;
                inFile.open("account.dat", ios::binary);
                if (!inFile)
                {
                        cout << "\n\t\tFile couldn't be opened.";
                        return;
                }

                cout << "\n\n\t\tACCOUNT HOLDER LIST\n\n";
                cout << "====================================================\n";
                cout << "Account No.      Name           Type         Balance\n";
                cout << "====================================================\n";
                while (inFile.read(reinterpret_cast<char *>(&ac), sizeof(account)))
                {
                        ac.get_report();
                }
                inFile.close();
        }
        else 
		{
                cout << "\n\t\tPlease enter the correct password.\n";
        }
}

void deposit_withdraw(int n, int option)
{
        int amt;
        bool found = false;
        account ac;
        fstream File;
        File.open("account.dat", ios::binary | ios::in | ios::out);
        if (!File)
        {
                cout << "\n\t\tFile couldn't be opened.";
                return;
        }
        while (!File.eof() && found == false)
        {
                File.read(reinterpret_cast<char *>(&ac), sizeof(account));
                if (ac.get_accountnumber() == n)
                {
                        ac.show_account();
                        if (option == 1)
                        {
                                cout << "\n\n\t\tDEPOSIT AMOUNT ";
                                cout << "\n\t\tEnter the amount to be deposited: ";
                                cin >> amt;
                                ac.deposit_funds(amt);
                        }
                        if (option == 2)
                        {
                                cout << "\n\n\t\tWITHDRAW AMOUNT ";
                                cout << "\n\t\tEnter The amount to be withdraw: ";
                                cin >> amt;
                                int bal = ac.get_funds() - amt;
                                if ((bal < 500 && ac.get_accounttype() == 'S') || (bal < 1000 && ac.get_accounttype() == 'C'))
                                {
                                	cout << "\n\t\tInsufficience balance";
								}
                                else
                                {
                                	ac.draw_funds(amt);
								}
                        }
                        int pos = (-1) * static_cast<int>(sizeof(ac));
                        File.seekp(pos, ios::cur);
                        File.write(reinterpret_cast<char *>(&ac), sizeof(account));
                        cout << "\n\t\tRecord Updated.";
                        found = true;
                }
        }
        File.close();
        if (found == false)
        {
        	cout << "\n\t\tRecord Not Found.";
		}
}
