#include <iostream>
#include <fstream>
#include <vector>
#include <iomanip>
using namespace std;

string filename = "Clients.txt";
struct Client
{
    string AccountNumber;
    string pin;
    string name;
    string phone;
    int salary;
    bool MarkForDelet = false;
};
vector<string> Split(string s, string del = "#//#")
{
    vector<string> vWords;
    string word = "";
    int pos = 0;
    while ((pos = s.find(del)) != std::string::npos)
    {
        word = s.substr(0, pos);
        if (word != "")
        {
            vWords.push_back(word);
        }
        s.erase(0, pos + del.length());
    }
    if (s != "")
    {
        vWords.push_back(s);
    }
    return vWords;
}
Client Read()
{
    Client c;
    cout << "Enter your AccountNumber ";
    getline(cin >> ws, c.AccountNumber);
    cout << "Enter your Pin ";
    getline(cin, c.pin);
    cout << "Enter your Name ";
    getline(cin, c.name);
    cout << "Enter your Phone ";
    getline(cin, c.phone);
    cout << "Enter your salary ";
    cin >> c.salary;
    return c;
}
string ConvertClientToLine(Client c, string del = "#//#")
{
    string s = "";
    s += c.AccountNumber + del;
    s += c.pin + del;
    s += c.name + del;
    s += c.phone + del;
    s += to_string(c.salary);
    return s;
}
Client ConvertStringToClient(string s)
{
    Client c;
    vector<string> Wordas = Split(s);
    c.AccountNumber = Wordas[0];
    c.pin = Wordas[1];
    c.name = Wordas[2];
    c.phone = Wordas[3];
    c.salary = stod(Wordas[4]);
    return c;
}
void print(Client c)
{

    cout << "| " << setw(15) << left << c.AccountNumber;
    cout << "| " << setw(10) << left << c.pin;
    cout << "| " << setw(40) << left << c.name;
    cout << "| " << setw(12) << left << c.phone;
    cout << "| " << setw(12) << left << c.salary;
}
void AddLineToFile(string filename, string line)
{
    fstream file;
    file.open(filename, ios::out | ios::app);
    if (file.is_open())
    {
        file << line << endl;
    }
    file.close();
}
void AddClient()
{
    AddLineToFile("Clients.txt", ConvertClientToLine(Read()));
}
void PrintClientCard(Client Client)
{
    cout << "\nThe following are the client details:\n";
    cout << "-----------------------------------------------";
    cout << "\nAccout Number: " << Client.AccountNumber;
    cout << "\nPin Code     : " << Client.pin;
    cout << "\nName         : " << Client.name;
    cout << "\nPhone        : " << Client.phone;
    cout << "\nAccount Balance: " << Client.salary;
    cout << "\n-----------------------------------------------";
}
vector<Client> LoadDataFromFile(string filename)
{
    fstream file;
    vector<Client> vClient;
    file.open(filename, ios::in);
    string line;
    if (file.is_open())
    {
        while (getline(file, line))
        {
            Client c = ConvertStringToClient(line);
            vClient.push_back(c);
        }
        file.close();
    }
    return vClient;
}
void PrintClient(vector<Client> Clients)
{
    cout << "\n\t\t\t\t\tClient List (" << Clients.size() << ") Client(s).";
    cout << "\n_______________________________________________________";
    cout << "_________________________________________\n"
         << endl;
    cout << "| " << setw(15) << left << "AccountNumber";
    cout << "| " << setw(10) << left << "pin";
    cout << "| " << setw(40) << left << "name";
    cout << "| " << setw(12) << left << "phone";
    cout << "| " << setw(12) << left << "salary";
    cout << "\n_______________________________________________________";
    cout << "_________________________________________\n"
         << endl;
    for (Client c : Clients)
    {
        print(c);
        cout << endl;
    }
    cout << "\n_______________________________________________________";
    cout << "_________________________________________\n"
         << endl;
}
// this find my idea
Client Find(string item, string filename)
{
    vector<Client> Vclients;
    Vclients = LoadDataFromFile(filename);
    for (Client c : Vclients)
    {
        if (item == c.AccountNumber)
        {
            return c;
        }
    }
}
// this find is better
bool Find(string Account, Client &client)
{
    vector<Client> Clients = LoadDataFromFile("Clients.txt");
    for (Client c : Clients)
    {
        if (c.AccountNumber == Account)
        {
            client = c;
            return true;
        }
    }

    return false;
}
bool Find(string AccountNumber, vector<Client> vClient, Client &client)
{
    vClient = LoadDataFromFile("Clients.txt");
    for (Client c : vClient)
    {
        if (AccountNumber == c.AccountNumber)
        {
            client = c;
            return true;
        }
    }
    return false;
}
bool Mark(string AccountNumber, vector<Client> &vCleint)
{

    for (Client &c : vCleint)
    {
        if (AccountNumber == c.AccountNumber)
        {
            c.MarkForDelet = true;
            return true;
        }
    }
    return false;
}
vector<Client> SaveNewClients(string filename, vector<Client> vClient)
{
    fstream file;
    string dataline;
    file.open("Clients.txt", ios::out);
    if (file.is_open())
    {
        for (Client c : vClient)
        {
            if (c.MarkForDelet == false)
            {
                dataline = ConvertClientToLine(c);
                file << dataline << endl;
            }
        }
        file.close();
    }
    return vClient;
}
bool Delete(string AccountNumber, vector<Client> &vClient)

{
    Client c;
    if (Find(AccountNumber, vClient, c))
    {
        PrintClientCard(c);
        char Answer = 'n';
        cout << "\nAre you sure to delete? ";
        cin >> Answer;
        if (Answer == 'y' || Answer == 'Y')
        {
            Mark(AccountNumber, vClient);
            SaveNewClients("Clients.txt", vClient);

            vClient = LoadDataFromFile("Clients.txt");
            cout << "\nAccept ";
            return true;
        }
    }
    else
        cout << "Client whith " << AccountNumber << " is not found ";
    return false;
}
Client ChangeData(string AccountNumber)
{
    Client c;
    c.AccountNumber = AccountNumber;
    cout << "\nEnter Pin? ";
    getline(cin >> ws, c.pin);
    cout << "Enter Name? ";
    getline(cin, c.name);
    cout << "Enter Phone? ";
    getline(cin, c.phone);
    cout << "Enter AccountBalance? ";
    cin >> c.salary;
    return c;
}
bool Update(string AccountNumber, vector<Client> &vClient)
{
    Client c;
    char answer = 'n';
    if (Find(AccountNumber, vClient, c))
    {
        PrintClientCard(c);
        cout << "\nDo want to update? ";
        cin >> answer;
        if (answer == 'y' || answer == 'Y')
        {
            for (Client &c : vClient)
            {
                if (AccountNumber == c.AccountNumber)
                {
                    c = ChangeData(AccountNumber);
                    break;
                }
            }
            SaveNewClients("Clients.txt", vClient);
            cout << "Accept ";
            return true;
        }
    }
    cout << "\n\nClient is not find";
    return false;
}
string Read_Account_Number()
{
    string s;
    cout << "\nEnter Acoount Number: ";
    cin >> s;
    return s;
}

/////////////////////////Functions that do the Main Menue Opreations///////////////////////////////////
enum enMainMenueOptions
{
    eListClients = 1,
    eAddNewClient = 2,
    eDeleteClient = 3,
    eUpdateClient = 4,
    eFindClient = 5,
    eTransactions = 6,
    eExit = 7
};
short ReadMainMenueOption()
{
    cout << "Choose what do you want to do? [1 to 7]? ";
    short Choice = 0;
    cin >> Choice;

    return Choice;
}
void MainMenue(); ////////singtuer/////////////
void goBack()
{
    cout << "\n\nPress any key to go to Main Menie...";
    system("pause>0");
    MainMenue();
}
void ShowClients()
{
    system("cls");
    vector<Client> vClient = LoadDataFromFile(filename);
    PrintClient(vClient);
}
void Add_Client()
{
    system("cls");
    cout << "Adding Client:\n";
    char c = 'n';
    do
    {
        AddClient();
        cout<<"-----------------------------------\n";
        cout << "Do you want add more? ";
        cin >> c;
    } while (c == 'y' || c == 'Y');

}
void Delete_Client()
{
    system("cls");
    vector<Client> vClients = LoadDataFromFile(filename);
    char c = 'n';
    do
    {
        Delete(Read_Account_Number(), vClients);
        cout << "Do want to delete more? ";
        cin >> c;
    } while (c == 'y' || c == 'Y');
}
void Updat_Client()
{
    system("cls");
    cout << "Editing Page: \n\n";
    vector<Client> vClient = LoadDataFromFile(filename);
    Update(Read_Account_Number(), vClient);
}
void Find_Client()
{
    system("cls");
    cout << "Finding Screen\n\n";
    string Account = Read_Account_Number();
    vector<Client> vClient = LoadDataFromFile(filename);
    Client c;
    if (Find(Account, vClient, c))
        PrintClientCard(c);
    else
        cout << "Client with [" << Account << "] is not found! ";
}
void Exit()
{
    system("cls");
    cout << "----------------------------";
    cout << "\nProgram End \n";
    cout << "----------------------------";
    system("pause>0");
}
/////////////Tarnsactins Page///////////////////////////

short Read_TransactoinPage()
{
    cout << "\nChoose What do you want to do? [1 to 4] ";
    short x = 0;
    cin >> x;
    return x;
}
void Show_Transactions();
void Go_Transaactions_Page()
{
    cout << "\nEnter any key to return to Transactins page....";
    system("pause>0");
    Show_Transactions();
}
bool Dipost(string AccountNumer, int Amount, vector<Client> &vClient)
{
    for (Client &c : vClient)
    {
        if (c.AccountNumber == AccountNumer)
        {
            c.salary += Amount;
            cout << "\n\nAccept, New Balance is: " << c.salary;
            return true;
        }
    }
    return false;
}
void Show_Diposit()
{
    system("cls");
    cout << "===========================";
    cout << "\n   Dipost Page \n";
    cout << "===========================";
    string Account = Read_Account_Number();
    vector<Client> vClient = LoadDataFromFile(filename);
    Client c;
    int Amount;
    char check = 'n';
    while (!Find(Account, vClient, c))
    {
        {
            cout << "The Account Number [" << Account << "] is wrong chnge the number: ";
            Account = Read_Account_Number();
        }
    }
    PrintClientCard(c);
    cout << "\nAdd Amount: ";
    cin >> Amount;
    cout << "\n\nAre you sure? ";
    cin >> check;
    if (check == 'y' || check == 'Y')
    {
        Dipost(Account, Amount, vClient);
        SaveNewClients(filename, vClient);
    }

    else
        cout << "\n\nClient Not Found";
}
int Count_Total(string filename, vector<Client> vClient)
{
    int Total = 0;
    for (Client c : vClient)
    {
        Total += c.salary;
    }
    return Total;
}
void Show_Total_Balance()
{
    system("cls");
    cout << "===========================";
    cout << "\n   Dipost Page \n";
    cout << "===========================\n";
    vector<Client> vClient = LoadDataFromFile(filename);
    PrintClient(vClient);

    cout << "                                Total is: " << Count_Total(filename, vClient) << endl;
}
void Show_Withdrow()
{
    system("cls");
    cout << "===========================";
    cout << "\n   Withdrow Page \n";
    cout << "===========================\n";
    vector<Client> vClient = LoadDataFromFile(filename);
    Client c;
    int Amount = 0;
    char sure = 'n';
    string Account = Read_Account_Number();
    while (!Find(Account, vClient, c))
    {
        cout << "The Account Number [" << Account << "] is wrong chnge the number: ";
        Account = Read_Account_Number();
    }
    PrintClientCard(c);
    cout << "\n\nAdd Withdrow Amount: ";
    cin >> Amount;
    while (Amount > c.salary)
    {
        cout << "\nYou Can not Do Whithdrow Because The Amoount is bigger than Balance.Change the Amount \n";
        cout << "Add Withdrow Amount: ";
        cin >> Amount;
    }

    cout << "\nAre You Sure? ";
    cin >> sure;
    if (sure == 'y' || sure == 'Y')
    {
        Dipost(Account, Amount * -1, vClient);
        SaveNewClients(filename, vClient);
    }

    else
        cout << "\n\nClient is not Found";
}

enum enTransaction
{
    enDeposit = 1,
    enWithdraw = 2,
    enTotalBalance = 3,
    enMainmenue = 4
};
void Opreations_Transactions(enTransaction Enum)
{
    switch (Enum)
    {
    case enTransaction::enDeposit:
        Show_Diposit();
        Go_Transaactions_Page();
        break;
    case enTransaction::enWithdraw:
        Show_Withdrow();
        Go_Transaactions_Page();
    case enTransaction::enTotalBalance:
        Show_Total_Balance();
        Go_Transaactions_Page();
    case enTransaction::enMainmenue:
        MainMenue();
    }
}
void Show_Transactions()
{
    system("cls");
    cout << "=============================";
    cout << "\nTransactions Menue\n";
    cout << "=============================\n";
    cout << "[1] Deposit.\n";
    cout << "[2] Withdraw.\n";
    cout << "[3] Total Balance.\n";
    cout << "[4] Mainmenue.\n";
    cout << "\n=============================";
    Opreations_Transactions((enTransaction)Read_TransactoinPage());
}
////////////////////Main Menue page/////////////////////////////
void Opearations(enMainMenueOptions Enum)
{
    switch (Enum)
    {
    case enMainMenueOptions::eListClients:
        ShowClients();
        goBack();
        break;

    case enMainMenueOptions::eAddNewClient:
        Add_Client();
        goBack();
        break;
    case enMainMenueOptions::eDeleteClient:
        Delete_Client();
        goBack();
        break;
    case enMainMenueOptions::eUpdateClient:
        Updat_Client();
        goBack();
        break;
    case enMainMenueOptions::eFindClient:
        Find_Client();
        goBack();
        break;
    case enMainMenueOptions::eTransactions:
        Show_Transactions();
    case enMainMenueOptions::eExit:
        Exit();
        break;
    }
}
void MainMenue()
{
    system("cls");
    cout << "=========================================\n";
    cout << "Main Menu\n";
    cout << "=========================================\n";
    cout << "[1] Show Client List.\n";
    cout << "[2] Add New Client.\n";
    cout << "[3] Delete Client.\n";
    cout << "[4] Update Client Info.\n";
    cout << "[5] Find Client.\n";
    cout << "[6] Transactions.\n";
    cout << "[7] Exit.\n";
    cout << "=========================================\n";
    Opearations((enMainMenueOptions)ReadMainMenueOption());
}

int main()
{
    MainMenue();
    return 0;
    system("pause>0");
}