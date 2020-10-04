#include <iostream>
#include <string>
#include <windows.h>
#include <fstream>
#include <ctime>
#include <vector>
#include <algorithm>
#include <iterator>
#include <conio.h>
#include <iomanip>


using namespace std;

struct User
{
	string login;
	string password;
	bool role;

};

struct Air_Ticket
{
	string flight_number; //flight_number
	string bus_type;//planetype
	string destination;//arivepoint
	
	int departure_hour;
	int departure_min;
	int arrival_hour;
	int arrival_min;

	int departure_month;
	int departure_day;
	int arrival_month;
	int arrival_day;

	int buscap;//planecap
	int businessquantity;
	int businesscost;
	int economquantity;
	int economcost;
};


void FillUsers(vector <User>& Vec_of_users);
void FillTickets(vector <Air_Ticket>& Vec_of_tickets);
bool Authorization(vector <User> Vec_of_users);
void ShowUsersFile(vector <User>& Vec_of_users);
void ShowTicketsFile(vector <Air_Ticket>& Vec_of_tickets);
void EncryptByStars(string& pass);


/////////////////Работа с аккаунтами//////////////////
void WorkWithAccounts(vector <User> Vec_of_users);
void ShowAccounts(vector <User>& Vec_of_users);
void DeleteAccount(vector <User>& Vec_of_users);
void EditingAccounts(vector <User>& Vec_of_users);
void AddUser(vector <User>& Vec_of_users);
//////////////////////////////////////////////////////
void SectionOfFlightInfo(vector <Air_Ticket> Vec_of_tickets);
void SectionOfInfoEditing(vector <Air_Ticket> Vec_of_tickets);
void ShowFlights(vector <Air_Ticket> Vec_of_tickets);
void AddFlights(vector <Air_Ticket>& Vec_of_tickets);
void EditFlightInfo(vector <Air_Ticket>& Vec_of_tickets);
void DeleteFlights(vector <Air_Ticket>& Vec_of_tickets);
void InfoProcessing(vector <Air_Ticket> Vec_of_tickets);
void CreateNewFile(vector <User>& Vec_of_users, vector <Air_Ticket>& Vec_of_tickets);
void OpenFile();
void DeleteFile();
void SearchFlightInfo(vector <Air_Ticket> Vec_of_tickets);
void Sorting(vector <Air_Ticket> Vec_of_products);

const bool SortByPoint(const Air_Ticket RHS, const Air_Ticket LHS);
const bool SortByBusinessCost(const Air_Ticket RHS, const Air_Ticket LHS);
const bool SortByEconomCost(const Air_Ticket RHS, const Air_Ticket LHS);

void Individual(vector <Air_Ticket> Vec_of_tickets);


///////////////////////////////////
void AdministratorsSection(vector <User> Vec_of_users, vector <Air_Ticket> Vec_of_tickets);
int MenuOfAdministrator();
void UsersSection(vector <Air_Ticket> Vec_of_tickets);
int MenuOfUser();
void SectionOfFiles(vector <User> Vec_of_users, vector <Air_Ticket> Vec_of_tickets);
int Protection(int& InputValue, int Left_limit, int Right_limit);


//полезные мелочи 
const string FILE_OF_ACCOUNTS = "accounts.txt"; //Имя файла для хранения аккаунтов
const string FILE_OF_INFO_ABOUT_TICKETS = "tickets.txt";//Имя файла для хранения данных о рейсах 
const string MAIN_ADMINS_LOGIN = "karen"; //Имя гланого администратора, которого невозможно удалить 
const string MAIN_ADMINS_PASSWORD = "7780901"; //пароль главного администратора


int main()
{
	//setlocale(LC_ALL, "Russian");
	int f, InputValue;
	while (true)
	{
		std::cout << "\n\t\t\t\t\t*******************************************************" << endl
			<< "\t\t\t\t\t*Welcome to app for finding flight!*" << endl
			<< "\t\t\t\t\t*******************************************************" << endl;
		std::cout << "\n\t\t\t\t\t\t\t*******************"
			<< "\n\t\t\t\t\t\t\t*0.Exit.         * \n\t\t\t\t\t\t\t*1.Entrance .*" << endl
			<< "\t\t\t\t\t\t\t*******************" << endl;
		std::cout << "\n\t\t\t\t\t\t\t    Your choice: ";
		f = Protection(InputValue, 0, 1);
		system("cls");
		switch (f) {
		case 0: exit(0);
		case 1:
			vector <User> Vec_of_users;
			vector <Air_Ticket> Vec_of_tickets;
			bool Role;
			ShowTicketsFile(Vec_of_tickets);//вызываем фунцуию считывания данных о продуктах из файла в вектор. Если файл отсутствует - создаём новый
			ShowUsersFile(Vec_of_users);//аналогично, только для файла, хранящего информацию о пользователях
			while (true)
			{


				Role = Authorization(Vec_of_users);//в зависимости от возвращаемого значения(0/1) открываются полнамочия администратора или обычного пользователя
				if (Role == 1)
				{
					AdministratorsSection(Vec_of_users, Vec_of_tickets);//секция администратора
				}
				else
				{
					UsersSection(Vec_of_tickets);//секция пользователя
				}
			}

		}



	}

	system("pause");
	return 0;
}



void FillUsers(vector <User>& Vec_of_users)
{
	ifstream fin(FILE_OF_ACCOUNTS, ios::in);
	ofstream fout(FILE_OF_ACCOUNTS, ios::out);
	if (Vec_of_users.size() == 0)//ПРОВЕРКА НА ПУСТОТУ ФАЙЛА//занимае количество байтов!
	{
		User temp;
		temp.login = MAIN_ADMINS_LOGIN;
		temp.password = MAIN_ADMINS_PASSWORD;
		temp.role = 1;
		Vec_of_users.push_back(temp);
		fout << Vec_of_users.at(0).login << "\t"
			<< Vec_of_users.at(0).password << "\t"
			<< Vec_of_users.at(0).role;
	}
	else
	{
		for (int i = 0; i < Vec_of_users.size(); i++)
		{
			if (i != 0 && i != Vec_of_users.size()) fout << endl;
			fout << Vec_of_users.at(i).login << "\t"
				<< Vec_of_users.at(i).password << "\t"
				<< Vec_of_users.at(i).role;
		}
	}
	fout.close();
}

void ShowUsersFile(vector<User>& Vec_of_users)
{
	ifstream fin(FILE_OF_ACCOUNTS, ios::in);
	if (!fin.is_open()) FillUsers(Vec_of_users);//ПРОВЕРКА НА СУЩЕСТВОВАНИЕ/ПУСТОТУ ФАЙЛА
	else
	{
		User temp;
		while (!fin.eof())
		{
			fin >> temp.login >> temp.password >> temp.role;
			Vec_of_users.push_back(temp);
		}
	}
	fin.close();


}

void FillTickets(vector <Air_Ticket>& Vec_of_tickets)
{
	ofstream fout(FILE_OF_INFO_ABOUT_TICKETS, ios::out); //Открыли файл с данными о продуктах для записи 
	fout << endl;
	Air_Ticket temp;
	if (Vec_of_tickets.size() == 0)//ПРОВЕРКА НА ПУСТОТУ ФАЙЛА
	{
		int kol;
		std::cout << "Input count of flights for filling base: ";
		cin >> kol;
		for (int i = 0; i < kol; i++)
		{
			if (i != 0 && i != kol) fout << endl;
			std::cout << " Enter information: " << endl;
			std::cout << "Number of flight: ";
			cin >> temp.flight_number;
			std::cout << "Type of bus: ";
			cin >> temp.bus_type;
			std::cout << "Destination point: ";
			cin >> temp.destination;
			std::cout << "Departure date(day.month) ";
			scanf_s("%d%*c%d", &temp.departure_day, &temp.departure_month);
			std::cout << "Enter departure time(hours:minutes)" << endl;
			scanf_s("%d%*c%d", &temp.departure_hour, &temp.departure_min);
			std::cout << "Arrival date(day.month) ";
			scanf_s("%d%*c%d", &temp.arrival_day, &temp.arrival_month);
			std::cout << "Enter arrival time(hours:minutes)" << endl;
			scanf_s("%d%*c%d", &temp.arrival_hour, &temp.arrival_min);

			while (true) {
				std::cout << "Bus capacity: ";
				cin >> temp.buscap;
				if (temp.buscap < 0) {
					std::cout << "Bus capacity must be positive! " << endl;
				}
				else {
					break;
				}
			}

			while (true)
			{
				std::cout << "Quantity of remaining business tickets: ";
				cin >> temp.businessquantity;
				if (temp.businessquantity > temp.buscap) {
					std::cout << "Quantity of remaining business tickets must be less than bus capacity! Try again" << endl;
				}
				else if (temp.businessquantity < 0) {
					std::cout << "Quantity of remaining business tickets mustn't be negative: " << endl;
				}

				else {
					break;
				}
			}

			while (true)
			{
				std::cout << "Cost of business ticket: $";
				cin >> temp.businesscost;
				if (temp.businesscost < 0) {
					std::cout << "Cost of business ticket must be positive!" << endl;
				}
				else {
					break;
				}

			}
			while (true)
			{
				std::cout << "Quantity of remaining econom tickets:  ";
				cin >> temp.economquantity;
				if (temp.economquantity > temp.buscap) {
					std::cout << "Quantity of remaining econom tickets must be less than bus capacity! Try again " << endl;
				}
				else if (temp.economquantity < 0) {
					std::cout << "Quantity of remaining business tickets mustn't be negative: " << endl;
				}

				else if (temp.economquantity + temp.businessquantity > temp.buscap) {
					std::cout << "Sum of quantities mustn't be more than bus capacity! " << endl;
				}

				else {
					break;
				}
			}
			while (true)
			{
				std::cout << "Cost of econom ticket: $";
				cin >> temp.economcost;
				if (temp.economcost < 0) {
					std::cout << "Cost of econom ticket must be positive!!" << endl;
				}
				else {
					break;
				}

			}

			Vec_of_tickets.push_back(temp);
			fout << temp.flight_number << "\t"
				<< temp.bus_type << "\t"
				<< temp.destination << "\t"
				<<temp.departure_day<<"."
				<< temp.departure_month << "\t"
				<< temp.departure_hour << ":"
				<<temp.departure_min<<"\t"
				<< temp.arrival_day << "\t"
				<< temp.arrival_month << "\t"
				<< temp.arrival_hour << ":"
				<< temp.arrival_min << "\t"		
				<< temp.buscap << "\t"
				<< temp.businessquantity << "\t"
				<< temp.businesscost << "\t"
				<< temp.economquantity << "\t"
				<< temp.economcost << "\t";

		}
		std::cout << "*******************Sucsses input of data!*******************" << endl;

	}
	else
	{

		for (int i = 0; i < Vec_of_tickets.size(); i++)
		{
			if (i != 0 && i != Vec_of_tickets.size())
				fout << endl;
			fout << Vec_of_tickets.at(i).flight_number << "\t"
				<< Vec_of_tickets.at(i).bus_type << "\t"
				<< Vec_of_tickets.at(i).destination << "\t"

				<< Vec_of_tickets.at(i).departure_day << "."
				<< Vec_of_tickets.at(i).departure_month << "\t"
				<< Vec_of_tickets.at(i).departure_hour << ":"
				<< Vec_of_tickets.at(i).departure_min << "\t"
				<< Vec_of_tickets.at(i).arrival_day << "\t"
				<< Vec_of_tickets.at(i).arrival_month << "\t"
				<< Vec_of_tickets.at(i).arrival_hour << ":"
				<< Vec_of_tickets.at(i).arrival_min << "\t"

				<< Vec_of_tickets.at(i).buscap << "\t"
				<< Vec_of_tickets.at(i).businessquantity << "\t"
				<< Vec_of_tickets.at(i).businesscost << "\t"
				<< Vec_of_tickets.at(i).economquantity << "\t"
				<< Vec_of_tickets.at(i).economcost << "\t";
		}
	}
	fout.close();
	system("pause");
	system("cls");
}

void ShowTicketsFile(vector <Air_Ticket>& Vec_of_tickets)
{
	ifstream fin(FILE_OF_INFO_ABOUT_TICKETS, ios::in);
	if (!fin.is_open())
	{
		std::cout << "\t\t\t\t\t\t\t\t*************************************************" << endl
			<< "\t\t\t\t\t\t\t\t*Fill base of tickets in admin mode!*" << endl
			<< "\t\t\t\t\t\t\t\t*************************************************" << endl;

	}
	else
	{
		Air_Ticket temp;
		char a;
		while (true)
		{
			fin >> temp.flight_number
				>> temp.bus_type
				>> temp.destination
				>>temp.departure_day
				>>a
				>> temp.departure_month
				>>temp.departure_hour
				>>a
				>>temp.departure_min
				>> temp.buscap
				>> temp.businessquantity
				>> temp.businesscost
				>> temp.economquantity
				>> temp.economcost;

				

			if (fin.eof()) break;
			Vec_of_tickets.push_back(temp);
		}
	}
	fin.close();
}



bool Authorization(vector <User> Vec_of_users)
{
	while (true)
	{
		int i;
		string log, pass, result;
		std::cout << "\t\t\t\t\tAuthorization!" << endl << "\t\t\t\t\tLogin:";
		cin >> log;
		for (i = 0; i < Vec_of_users.size(); i++)
		{
			if (log == Vec_of_users.at(i).login)
			{
				std::cout << "\t\t\t\t\tPassword:";
				EncryptByStars(pass);
				if (pass == Vec_of_users.at(i).password)
				{
					system("cls");
					return Vec_of_users.at(i).role;
				}

			}

		}
		std::cout << "Input error. press any key to continue";
		system("pause");
		system("cls");
	}

}

int MenuOfAdministrator()
{
	int choice, InputValue;
	while (true)
	{
		std::cout << "\n\t\t\t\t\t**********************************" << endl
			<< "\t\t\t\t\t*Welcom, Admin!*" << endl
			<< "\t\t\t\t\t**********************************" << endl;
		std::cout << "\n\t\t\t\t\tMenu:" << endl
			<< "\t\t\t\t\t0.Exit" << endl
			<< "\t\t\t\t\t1.Create database" << endl
			<< "\t\t\t\t\t2.Manage of user" << endl
			<< "\t\t\t\t\t3.Work with data file" << endl
			<< "\t\t\t\t\t4.Work with data" << endl
			<< "\t\t\t\t\tYour choice: ";

		choice = Protection(InputValue, 0, 4);
		if (InputValue == 0)
		{
			return choice;
			break;
		}
	}
}

void AdministratorsSection(vector <User> Vec_of_users, vector <Air_Ticket> Vec_of_tickets)
{
	while (true)
	{
		int choice_of_admin = MenuOfAdministrator();
		switch (choice_of_admin)
		{
		case 0: system("cls"); main(); break;
		case 1: if (Vec_of_tickets.size() == 0)
		{
			FillTickets(Vec_of_tickets);
		}
			  else {
			std::cout << "Database is exist!" << endl;
			system("pause");
			system("cls");
		}
			  break;
		case 2: system("cls"); WorkWithAccounts(Vec_of_users);
			break;
		case 3: system("cls"); SectionOfFiles(Vec_of_users, Vec_of_tickets);
			break;
		case 4: system("cls"); SectionOfFlightInfo(Vec_of_tickets);
			break;

		}
	}
}

void WorkWithAccounts(vector <User> Vec_of_users)
{
	int choice, InputValue;
	system("cls");
	while (true)
	{
		while (true)
		{
			std::cout << "\n\t\t\t\t\t******************************************************" << endl
				<< "\t\t\t\t\t*Welcome to section of working with accounts*" << endl
				<< "\t\t\t\t\t******************************************************" << endl
				<< "\t\t\t\t\tMenu:" << endl
				<< "\t\t\t\t\t0.Exit from this section" << endl
				<< "\t\t\t\t\t1.Preview all accounts" << endl
				<< "\t\t\t\t\t2.Edit account" << endl
				<< "\t\t\t\t\t3.Delete account" << endl
				<< "\t\t\t\t\t4.Add account" << endl
				<< "\t\t\t\t\tYour choice:";
			choice = Protection(InputValue, 0, 4);
			if (InputValue == 0)
			{
				break;
			}
		}
		switch (choice)
		{
		case 0:system("cls"); return;
		case 1:ShowAccounts(Vec_of_users);
			break;
		case 2:EditingAccounts(Vec_of_users);
			break;
		case 3:DeleteAccount(Vec_of_users);
			break;
		case 4:AddUser(Vec_of_users);
			break;
		}
	}
}

void ShowAccounts(vector <User>& Vec_of_users)
{
	std::cout << "***********************************************************************************************************************" << endl;
	for (int i = 0; i < Vec_of_users.size(); i++)
	{
		std::cout << (i + 1) << "-account:"
			<< "Login: " << Vec_of_users.at(i).login << "   "
			<< "Password: " << Vec_of_users.at(i).password << "   "
			<< ": " << Vec_of_users.at(i).role << "   " << endl;
	}
	system("pause");
	system("cls");
}
void DeleteAccount(vector <User>& Vec_of_users)
{
	int Delete, InputValue, limit, choice, i;
	string name;
	bool rol;


	User t;
	t.login = name;

	/////////////////////////////////////////////////////
	while (true)
	{
		ShowAccounts(Vec_of_users);
		std::cout << "Enter user id or 0, if you want exit.";
		Delete = Protection(InputValue, 0, Vec_of_users.size());
		if (InputValue == 0)
		{
			break;
		}
	}
	if (Delete == 0)
	{
		return;
	}
	Delete--;
	std::cout << "***********************************************************************************************************************" << endl;
	std::cout << "Are you sure you want to remove the user?(1 - yes, 2 - no)\n";
	cin >> choice;

	if (choice == 1)
	{
		i = Delete;
		if (Vec_of_users.at(i).login == MAIN_ADMINS_LOGIN) {
			std::cout << "\tThe removal was unsuccessful, you can't delete main admin\n";
			std::cout << "***********************************************************************************************************************" << endl;
			return;
		}
		else {
			std::cout << "***********************************************************************************************************************" << endl;
			Vec_of_users.erase(Vec_of_users.begin() + Delete);
			system("cls");
			std::cout << "============================" << endl
				<< "The removal was successful!" << endl
				<< "============================" << endl;
			system("pause");
		}
	}

	else if (choice == 2) {
		std::cout << "\tCancellation of removal\n";
		std::cout << "***********************************************************************************************************************" << endl;
		return;
	}

	FillUsers(Vec_of_users);
}

void EditingAccounts(vector <User>& Vec_of_users)
{
	int edition, newRole, InputValue;
	string newLogin, newPass;
	while (true)
	{
		std::cout << "***********************************************************************************************************************" << endl;
		std::cout << "Enter account id for editing: ";
		edition = Protection(InputValue, 0, Vec_of_users.size());
		if (InputValue == 0)
		{
			break;
		}
	}
	if (edition == 0)
	{
		return;
	}
	for (int i = 0; i < Vec_of_users.size(); i++)
	{
		if (i == (edition - 1))
		{
			std::cout << "Enter new username: ";
			cin >> newLogin;
			for (int i = 0; i < Vec_of_users.size(); i++)
			{
				if (Vec_of_users.at(i).login == newLogin)
				{
					std::cout << "\n\tOne of the users has already taken this username!\n  ";
					EditingAccounts(Vec_of_users); return;
				}
			}
			Vec_of_users.at(i).login = newLogin;
			std::cout << "Enter new password: ";
			cin >> newPass;
			Vec_of_users.at(i).password = newPass;
			std::cout << "Enter your new access code: ";
			cin >> newRole;
			Vec_of_users.at(i).role = newRole;
			break;
		}
	}
	system("cls");
	std::cout << "\n\t\t\t\t\t\t**********************************" << endl
		<< "\t\t\t\t\t\t*The account is successfully changed!*" << endl
		<< "\t\t\t\t\t\t**********************************" << endl;
	system("pause");
	system("cls");
	FillUsers(Vec_of_users);
}
void AddUser(vector <User>& Vec_of_users)
{
	string name, pass;
	bool rol;
	std::cout << "Login: ";
	cin >> name;
	for (int i = 0; i < Vec_of_users.size(); i++)
	{
		if (Vec_of_users.at(i).login == name)
		{
			std::cout << "\n\tOne of the users has already taken this username!\n  ";
			AddUser(Vec_of_users); return;
		}
	}
	std::cout << "Password : ";
	cin >> pass;
	std::cout << "Access code : ";
	cin >> rol;
	User t;
	t.login = name;
	t.password = pass;
	t.role = rol;
	Vec_of_users.push_back(t);
	system("pause");
	system("cls");
	std::cout << "***********************************************************************************************************************" << endl;
	std::cout << "\n\tThe account is added successfully.\n";
	FillUsers(Vec_of_users);
}

void SectionOfFlightInfo(vector <Air_Ticket> Vec_of_tickets)
{

	string choice, result;
	while (true)
	{
		std::cout << "\n\t\t\t\t\t\t********************************************" << endl
			<< "\t\t\t\t\t\t*Welcome to the data management section*" << endl
			<< "\t\t\t\t\t\t********************************************" << endl
			<< "\t\t\t\t\t\t0.Exit from this section" << endl
			<< "\t\t\t\t\t\t1.Open edit mome" << endl
			<< "\t\t\t\t\t\t2.Open processing mode" << endl;
		cin >> choice;
		if (choice != "1" && choice != "2" && choice != "0")
		{
			std::cout << "Input error, press 0 to exit or any key to continue.";
			cin >> result;
			if (result == "0")
			{
				system("cls");
				return;
			}
		}
		else
		{
			if (choice == "1")
			{
				SectionOfInfoEditing(Vec_of_tickets);
			}
			else
			{
				if (choice == "2")
				{
					system("cls");
					InfoProcessing(Vec_of_tickets);
				}
				else system("cls");
				return;
			}
		}
	}
}

void SectionOfInfoEditing(vector <Air_Ticket> Vec_of_tickets)
{
	int choice, InputValue;
	while (true)
	{
		while (true)
		{
			std::cout << "\n\t\t\t\t\t\t*****************************************" << endl
				<< "\t\t\t\t\t\t*Welcome to edit mode*" << endl
				<< "\t\t\t\t\t\t*****************************************" << endl
				<< "\t\t\t\t\t\tMenu:" << endl
				<< "\t\t\t\t\t\t1.To view data" << endl
				<< "\t\t\t\t\t\t2.To add data" << endl
				<< "\t\t\t\t\t\t3.To edit data" << endl
				<< "\t\t\t\t\t\t4.To remove data" << endl
				<< "\t\t\t\t\t\t0.To exit from this section" << endl
				<< "\t\t\t\t\t\tYour choice:";
			choice = Protection(InputValue, 0, 4);
			if (InputValue == 0)
			{
				break;
			}
		}
		switch (choice)
		{
		case 0:system("cls"); return;
		case 1: ShowFlights(Vec_of_tickets);
			break;
		case 2: AddFlights(Vec_of_tickets);
			break;
		case 3: EditFlightInfo(Vec_of_tickets);
			break;
		case 4:DeleteFlights(Vec_of_tickets);
			break;
		}
	}
}



void ShowFlights(vector <Air_Ticket> Vec_of_tickets)
{
	std::cout << "***********************************************************************************************************************" << endl
		<< "List of voyages:" << endl;

	for (int i = 0; i < Vec_of_tickets.size(); i++)
	{
		std::cout << "************************************************************************************************************************\n"
			<< i + 1 << ") "
			<< "№ of voyages \t" << Vec_of_tickets.at(i).flight_number << endl
			<< "Bus type: \t" << Vec_of_tickets.at(i).bus_type << endl
			<< "Destination:\t" << Vec_of_tickets.at(i).destination << endl
			<< "Date of departure:\t" << Vec_of_tickets.at(i).departure_day<<"."<< Vec_of_tickets.at(i).departure_month<< endl
			<< "Departure time:\t" << Vec_of_tickets.at(i).departure_hour << ":" << Vec_of_tickets.at(i).departure_min << endl
			<< "Date of arrival:\t" << Vec_of_tickets.at(i).arrival_day << "." << Vec_of_tickets.at(i).arrival_month << endl
			<< "Arrival time:\t" << Vec_of_tickets.at(i).arrival_hour << ":" << Vec_of_tickets.at(i).arrival_min << endl
			<< "Capacity of bus:\t" << Vec_of_tickets.at(i).buscap << endl
			<< "Quantity of tickets (bussiness):\t" << Vec_of_tickets.at(i).businessquantity << endl
			<< "$ (bussiness):\t" << Vec_of_tickets.at(i).businesscost << endl
			<< "Quantity of tickets (eco):\t" << Vec_of_tickets.at(i).economquantity << endl
			<< "$ (eco):\t" << Vec_of_tickets.at(i).economcost << endl
			<< "\n**********************************************************************************************************************" << endl;
	}
	system("pause");
	system("cls");
}
void AddFlights(vector <Air_Ticket>& Vec_of_tickets)
{
	string flight_number, bus_type, destination;
	int  buscap, businessquantity, businesscost, economquantity, economcost,departure_day,departure_month,departure_min,departure_hour,
		arrival_day, arrival_month, arrival_min, arrival_hour;
	std::cout << " Enter information: " << endl;
	std::cout << "Number of flight: ";
	cin >> flight_number;
	std::cout << "Type of bus: ";
	cin >> bus_type;
	std::cout << "Destination: ";
	cin >> destination;
	std::cout << "Departure date(day.month) ";
	scanf_s("%d%*c%d", &departure_day, &departure_month);
	std::cout << "Enter departure time(hours:minutes)" << endl;
	scanf_s("%d%*c%d", &departure_hour, &departure_min);
	std::cout << "Arrival date(day.month) ";
	scanf_s("%d%*c%d", &arrival_day, &arrival_month);
	std::cout << "Enter arrival time(hours:minutes)" << endl;
	scanf_s("%d%*c%d", &arrival_hour, &arrival_min);
	while (true) {
		std::cout << "Capacity of bus: ";
		cin >> buscap;
		if (buscap < 0) {
			std::cout << "Bus capacity must be positive!" << endl;
		}
		else {
			break;
		}
	}

	while (true)
	{
		std::cout << "Quantity of remaining business tickets must be less than bus capacity! Try again: ";
		cin >> businessquantity;
		if (businessquantity > buscap) {
			std::cout << "Quantity of business tickets must be less than bus capacity! Try again" << endl;
		}
		else if (businessquantity < 0) {
			std::cout << "Quantity of remaining business tickets mustn't be negative! Try again!" << endl;
		}

		else {
			break;
		}
	}

	while (true)
	{
		std::cout << "Cost of business ticket!: $";
		cin >> businesscost;
		if (businesscost < 0) {
			std::cout << "Cost of business ticket must be positive!" << endl;
		}
		else {
			break;
		}

	}
	while (true)
	{
		std::cout << "Quantity of remaining econom tickets: ";
		cin >> economquantity;
		if (economquantity > buscap) {
			std::cout << "Quantity of econom tickets must be less than bus capacity! Try again " << endl;
		}
		else if (economquantity < 0) {
			std::cout << "Quantity of remaining econom tickets mustn't be negative! Try again!" << endl;
		}

		else if (economquantity + businessquantity > buscap) {
			std::cout << "Sum of quantities mustn't be more than bus capacity!" << endl;
		}

		else {
			break;
		}
	}
	while (true)
	{
		std::cout << "Cost of business ticket: $";
		cin >> economcost;
		if (economcost < 0) {
			std::cout << "Cost of business ticket must be positive!" << endl;
		}
		else {
			break;
		}

	}


	Air_Ticket temp;
	temp.flight_number = flight_number;
	temp.bus_type = bus_type;
	temp.destination = destination;
	temp.departure_day = departure_day;
	temp.departure_month = departure_month;
	temp.departure_hour = departure_hour;
	temp.departure_min = departure_min;

	temp.arrival_day = arrival_day;
	temp.arrival_month = arrival_month;
	temp.arrival_hour = arrival_hour;
	temp.arrival_min = arrival_min;

	
	temp.buscap = buscap;
	temp.businessquantity = businessquantity;
	temp.businesscost = businesscost;
	temp.economquantity = economquantity;
	temp.economcost = economcost;
	Vec_of_tickets.push_back(temp);
	system("pause");
	system("cls");
	std::cout << "***********************************************************************************************************************" << endl;
	std::cout << "                                    New flight added successfully.\n";
	std::cout << "***********************************************************************************************************************" << endl;
	FillTickets(Vec_of_tickets);
}
void EditFlightInfo(vector <Air_Ticket>& Vec_of_tickets)
{
	string flight_number, bus_type, destination;
	int  buscap, businessquantity, businesscost, economquantity, economcost, departure_day, departure_month, departure_min, departure_hour,
		arrival_day, arrival_month, arrival_min, arrival_hour, edit;
	ShowFlights(Vec_of_tickets);
	std::cout << "Enter number of flight: ";
	cin >> edit;
	for (int i = 0; i < Vec_of_tickets.size(); i++)
	{
		if (i == (edit - 1))
		{
			std::cout << "****************************************Enter the edited flight information:****************************************\n";
			std::cout << "Number of flight: ";
			cin >> flight_number;
			std::cout << "Bus type: ";
			cin >> bus_type;
			std::cout << "Destination: ";
			cin >> destination;
			std::cout << "Departure date(day.month) ";
			scanf_s("%d%*c%d", &departure_day, &departure_month);
			std::cout << "Enter departure time(hours:minutes)" << endl;
			scanf_s("%d%*c%d", &departure_hour, &departure_min);
			std::cout << "Arrival date(day.month) ";
			scanf_s("%d%*c%d", &arrival_day, &arrival_month);
			std::cout << "Enter arrival time(hours:minutes)" << endl;
			scanf_s("%d%*c%d", &arrival_hour, &arrival_min);

			
			while (true) {
				std::cout << "Capacity of bus: ";
				cin >> buscap;
				if (buscap < 0) {
					std::cout << "Capacity of bus must be positive! " << endl;
				}
				else {
					break;
				}
			}

			while (true)
			{
				std::cout << "Quantity of remaining business tickets: ";
				cin >> businessquantity;
				if (businessquantity > buscap) {
					std::cout << "Business class remaining tickets can't be more than the capacity of the bus! Try again" << endl;
				}
				else if (businessquantity < 0) {
					std::cout << "Quantity of remaining business tickets mustn't be negative!" << endl;
				}

				else {
					break;
				}
			}

			while (true)
			{
				std::cout << "Cost of bussiness tickets: $";
				cin >> businesscost;
				if (businesscost < 0) {
					std::cout << "Cost of business ticket must be positive" << endl;
				}
				else {
					break;
				}

			}
			while (true)
			{
				std::cout << "Quantity of remaining econom tickets: ";
				cin >> economquantity;
				if (economquantity > buscap) {
					std::cout << "Econom class remaining tickets can't be more than the capacity of the bus! Try again " << endl;
				}
				else if (economquantity < 0) {
					std::cout << "Quantity of remaining business tickets mustn't be negative!" << endl;
				}

				else if (economquantity + businessquantity > buscap) {
					std::cout << "Sum of quantities mustn't be more than bus capacity!554" << endl;
				}

				else {
					break;
				}
			}
			while (true)
			{
				std::cout << "Cost of econonic ticket: $";
				cin >> economcost;
				if (economcost < 0) {
					std::cout << "Cost of business ticket must be positive!" << endl;
				}
				else {
					break;
				}

			}
			Vec_of_tickets.at(i).flight_number = flight_number;
			Vec_of_tickets.at(i).bus_type = bus_type;
			Vec_of_tickets.at(i).destination = destination;
			Vec_of_tickets.at(i).departure_day = departure_day;
			Vec_of_tickets.at(i).departure_month = departure_month;
			Vec_of_tickets.at(i).departure_hour = departure_hour;
			Vec_of_tickets.at(i).departure_min = departure_min;

			Vec_of_tickets.at(i).arrival_day = arrival_day;
			Vec_of_tickets.at(i).arrival_month = arrival_month;
			Vec_of_tickets.at(i).arrival_hour = arrival_hour;
			Vec_of_tickets.at(i).arrival_min = arrival_min;

			
			Vec_of_tickets.at(i).buscap = buscap;
			Vec_of_tickets.at(i).businessquantity = businessquantity;
			Vec_of_tickets.at(i).businesscost = businesscost;
			Vec_of_tickets.at(i).economquantity = economquantity;
			Vec_of_tickets.at(i).economcost = economcost;
			

		}
	}
	system("cls");
	std::cout << "***********************************************************************************************************************" << endl;
	std::cout << "                                     Flight information changed successfully.\n";
	std::cout << "***********************************************************************************************************************" << endl;
	FillTickets(Vec_of_tickets);
}
void DeleteFlights(vector <Air_Ticket>& Vec_of_tickets)
{
	int Delete, choice;
	ShowFlights(Vec_of_tickets);

	std::cout << "Number of ticket:";
	cin >> Delete;
	Delete--;
	std::cout << "***********************************************************************************************************************" << endl;
	std::cout << "Are you sure you want to delete information of this flight?(1 - yes, 2 - no)\n";
	cin >> choice;
	if (choice == 1)
	{
		std::cout << "***********************************************************************************************************************" << endl;
		Vec_of_tickets.erase(Vec_of_tickets.begin() + Delete);
		system("cls");
		std::cout << "***********************************************************************************************************************" << endl;
		std::cout << "                                    Deleted!\n";
		std::cout << "***********************************************************************************************************************" << endl;
	}
	else if (choice == 2)
	{
		std::cout << "\tCancellation of removal\n";
		std::cout << "***********************************************************************************************************************" << endl;
		return;
	}
	FillTickets(Vec_of_tickets);
}

void InfoProcessing(vector <Air_Ticket> Vec_of_tickets)
{
	int choice, InputValue;
	while (true)
	{
		while (true)
		{
			std::cout << "\n\t\t\t\t\t\t************************************" << endl
				<< "\t\t\t\t\t\t*Welcome to processing mode*" << endl
				<< "\t\t\t\t\t\t************************************"
				<< "                                               Menu:" << endl
				<< "\t\t\t\t\t\t0.Exit from this section" << endl
				<< "\t\t\t\t\t\t1.Search right flight " << endl
				<< "\t\t\t\t\t\t2.Search" << endl
				<< "\t\t\t\t\t\t3.Sort" << endl
				<< "\t\t\t\t\t\tYour choice: ";
			choice = Protection(InputValue, 0, 3);
			if (InputValue == 0)
			{
				break;
			}
		}
		switch (choice)
		{
		case 0: system("cls");
			return;
		case 1: Individual(Vec_of_tickets);
			break;
		case 2: SearchFlightInfo(Vec_of_tickets);
			break;
		case 3: Sorting(Vec_of_tickets);
			break;
		}
	}
}


////////////////////////////////////////////////////////////

void UsersSection(vector <Air_Ticket> Vec_of_tickets)
{
	while (true)
	{
		int choice_of_user = MenuOfUser();
		switch (choice_of_user)
		{
		case 0: system("cls"); main(); break;
		case 1: ShowFlights(Vec_of_tickets);
			break;
		case 2: Individual(Vec_of_tickets);
			break;
		case 3: Sorting(Vec_of_tickets);
			break;
		case 4: SearchFlightInfo(Vec_of_tickets);
			break;
		}
	}
}

int MenuOfUser()
{
	string result;
	int choice, InputValue;
	while (true) {
		std::cout << "\n\t\t\t\t\t\t*******************************************" << endl
			<< "\t\t\t\t\t\t*Welcome, Dear user*" << endl
			<< "\t\t\t\t\t\t*******************************************" << endl;
		std::cout << "\t\t\t\t\t\tMenu:" << endl
			<< "\t\t\t\t\t\t0.Exit" << endl
			<< "\t\t\t\t\t\t1.View data" << endl
			<< "\t\t\t\t\t\t2.Search right flight" << endl
			<< "\t\t\t\t\t\t3.Sort data" << endl
			<< "\t\t\t\t\t\t4.Search data" << endl
			<< "\t\t\t\t\t\tYour choice:";
		choice = Protection(InputValue, 0, 4);
		if (InputValue == 0) {
			return choice;
			break;
		}

	}
}

int Protection(int& InputValue, int Left_limit, int Right_limit)
{
#undef max;
	int number;
	cin >> number;
	if (cin.good() && (number >= Left_limit && number <= Right_limit))
	{
		InputValue = 0;
		return number;
	}
	else
	{
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		system("cls");
		std::cout << "***********************************************************************************************************************" << endl
			<< "\t\t\t******************************Input error, try again******************************" << endl
			<< "***********************************************************************************************************************" << endl;
		system("pause");
		system("cls");
	}
}

void SectionOfFiles(vector <User> Vec_of_users, vector <Air_Ticket> Vec_of_tickets)
{
	int choice, InputValue;
	while (true)
	{
		while (true)
		{

			std::cout << "\n\t\t\t\t\t\t********************************************" << endl
				<< "\t\t\t\t\t\t*Welome to section of working with files*" << endl
				<< "\t\t\t\t\t\t********************************************" << endl
				<< "\t\t\t\t\t\tMenu:" << endl
				<< "\t\t\t\t\t\t0.Exit from this section" << endl
				<< "\t\t\t\t\t\t1.Create file " << endl
				<< "\t\t\t\t\t\t2.Open file" << endl
				<< "\t\t\t\t\t\t3.Delete file" << endl
				<< "\t\t\t\t\t\tYour choice: ";
			choice = Protection(InputValue, 0, 4);
			if (InputValue == 0)
			{
				break;
			}
		}
		switch (choice)
		{
		case 0: system("cls"); return;
		case 1: CreateNewFile(Vec_of_users, Vec_of_tickets);
			break;
		case 2: OpenFile();
			break;
		case 3: DeleteFile();
			break;

		}
	}
}

void EncryptByStars(string& pass) {
	char ch = 0;
	while (true) {
		ch = _getch();
		if (ch == 13)
			break;
		if (ch == 8) {
			std::cout << (char)8 << ' ' << (char)8;
			if (!pass.empty())
				pass.pop_back();
		}
		else {
			std::cout << '*';
			pass += (char)ch;
		}
	}
	std::cout << '\n';
}

void CreateNewFile(vector <User>& Vec_of_users, vector <Air_Ticket>& Vec_of_tickets)
{
	string choice;
	std::cout << "Choose what type of file you want to create: " << endl
		<< "1.File with user data " << endl
		<< "2.File with flight data\n";
	while (true)
	{
		std::cout << "Your choice: ";
		cin >> choice;
		if (choice == "1" || choice == "2")
		{
			if (choice == "1")
			{
				ifstream fin(FILE_OF_ACCOUNTS, ios::in);
				if (fin.is_open())
				{
					std::cout << "Error of creation file! This file already exists. " << endl;
					return;
				}
				else
				{
					FillUsers(Vec_of_users);
					std::cout << " The user data file was created successfully. " << endl;
					return;
				}
			}
			else
			{
				ifstream fin(FILE_OF_INFO_ABOUT_TICKETS, ios::in);
				if (fin.is_open())
				{
					std::cout << "Error of creation file! This file already exists. " << endl;
					return;
				}
				else
				{
					FillTickets(Vec_of_tickets);
					std::cout << " The flight data file was created successfully. " << endl;
					return;
				}
			}
		}
		else std::cout << "Input error! Try again";

	}
	system("pause");
	system("cls");
}
void OpenFile()
{
	string choice;
	std::cout << "Choose what type of file you want to open: " << endl
		<< "1.File with user data " << endl
		<< "2.File with flight data\n";
	cin >> choice;
	if (choice == "1")system("notepad production.txt");
	else
	{
		if (choice == "2")system("notepad user.txt");
		else std::cout << "Input error!\nTry again.";
	}
	system("pause");
	system("cls");
}
void DeleteFile()
{

	int choice, choice1;
	std::cout << "Choose what type of file you want to remove: " << endl
		<< "1.File with user data " << endl
		<< "2.File with flight data\n";
	cin >> choice1;
	if (choice1 == 1 || choice1 == 2)
	{
		while (true) {
			std::cout << "Are you sure you want to delete the file?(1 - yes, 2 - no)\n";
			cin >> choice;
			if (choice == 1)
			{
				if (choice1 == 1)
				{
					if (remove("production.txt") != 0)
						std::cout << "Error of remove!" << endl;
					else
						std::cout << " The ticket data file was successfully deleted. " << endl;
					break;

				}
				else
				{
					if (remove("user.txt") != 0)
						std::cout << "Error of remove!" << endl;
					else
						std::cout << " The user data file was successfully deleted. " << endl;
					break;
				}
			}
			else if (choice == 2)
			{
				std::cout << "\tCancellation of removal\n";
				std::cout << "***********************************************************************************************************************" << endl;
				break;
				return;
			}

			else {
				std::cout << "Input error, try again" << endl;
			}
		}

	}
	else
	{
		std::cout << "Input error!\n";
		std::cout << "***********************************************************************************************************************" << endl;
		return;
	}
	system("pause");
	system("cls");
}


void SearchFlightInfo(vector <Air_Ticket> Vec_of_tickets)
{
	int Search, i = 0;
	while (true)
	{
		system("cls");
		std::cout << "*****************************************************Search flifht********************************************************\n"
			<< "1.Destination\n"
			<< "2.Number of flight\n"
			<< "0.EXIT.\n"
			<< "***********************************************************************************************************************\n\t"
			<< "Your choice: ";
		cin >> Search;
		switch (Search)
		{
		case 1:
		{
			string destination;
			system("cls");
			std::cout << "Enter city: ";
			cin >> destination;

			for (int i = 0; i < Vec_of_tickets.size(); i++)
			{
				if (Vec_of_tickets.at(i).destination == destination)
				{
					std::cout << "***********************************************************************************************************************\n"
						<< i + 1 << ") "
						<< "Number of flight \t" << Vec_of_tickets.at(i).flight_number << endl
						<< "Type of bus: \t" << Vec_of_tickets.at(i).bus_type << endl
						<< "Destination:\t" << Vec_of_tickets.at(i).destination << endl

						<< "Date of departure:\t" << Vec_of_tickets.at(i).departure_day<<"."<< Vec_of_tickets.at(i).departure_month << endl
						<< "Departure time:\t "<<Vec_of_tickets.at(i).departure_hour << ":"<< Vec_of_tickets.at(i).departure_min << endl
						<< "Date of arrival:\t"<<Vec_of_tickets.at(i).arrival_day << "."<< Vec_of_tickets.at(i).arrival_month << endl
						<< "Time of arrival:\t"<<Vec_of_tickets.at(i).arrival_hour << ":"<< Vec_of_tickets.at(i).arrival_min << "endl"

						<< "Capacity of bus:\t" << Vec_of_tickets.at(i).buscap << endl
						<< "Quantity of tickets(business):\t" << Vec_of_tickets.at(i).businessquantity << endl
						<< "$ (business):\t" << Vec_of_tickets.at(i).businesscost << endl
						<< "Quantity of tickets (econom):\t" << Vec_of_tickets.at(i).economquantity << endl
						<< "$ (econom):\t" << Vec_of_tickets.at(i).economcost << endl
						<< "\n************************************************************************************************************************" << endl;
				}
			}
			system("pause");
		}
		break;
		case 2:
		{
			string flight_number;
			system("cls");
			std::cout << "Enter number of flight: ";
			cin >> flight_number;
			for (int i = 0; i < Vec_of_tickets.size(); i++)
			{
				if (Vec_of_tickets.at(i).flight_number == flight_number)
				{
					std::cout << "***********************************************************************************************************************\n"
						<< i + 1 << ") "
						<< "Number of flight \t" << Vec_of_tickets.at(i).flight_number << endl
						<< "Type of bus: \t" << Vec_of_tickets.at(i).bus_type << endl
						<< "Destination:\t" << Vec_of_tickets.at(i).destination << endl
						<< "Date of departure:\t" << Vec_of_tickets.at(i).departure_day << "." << Vec_of_tickets.at(i).departure_month << endl
						<< "Departure time:\t " << Vec_of_tickets.at(i).departure_hour << ":" << Vec_of_tickets.at(i).departure_min << endl
						<< "Date of arrival:\t" << Vec_of_tickets.at(i).arrival_day << "." << Vec_of_tickets.at(i).arrival_month << endl
						<< "Time of arrival:\t" << Vec_of_tickets.at(i).arrival_hour << ":" << Vec_of_tickets.at(i).arrival_min << "endl"
						<< "Capacity of bus:\t" << Vec_of_tickets.at(i).buscap << endl
						<< "Quantity of tickets(business):\t" << Vec_of_tickets.at(i).businessquantity << endl
						<< "$ (business):\t" << Vec_of_tickets.at(i).businesscost << endl
						<< "Quantity of tickets (econom):\t" << Vec_of_tickets.at(i).economquantity << endl
						<< "$ (econom):\t" << Vec_of_tickets.at(i).economcost << endl
						<< "\n************************************************************************************************************************" << endl;
				}
			}
			system("pause");
		}
		break;

		case 0:
		{
			system("pause");
			system("cls");
			return;
		}
		}
	}
}

void Sorting(vector <Air_Ticket> Vec_of_tickets)
{
	int choice, InputValue;
	while (true)
	{
		while (true)
		{
			system("cls");
			std::cout << "***************************************************Сортировка данных***************************************************" << endl
				<< "1. Sort by destination" << endl
				<< "2. Sort by business class cost" << endl
				<< "3. Sort by econom class cost" << endl << endl
				<< "0.EXIT." << endl;
			std::cout << "************************************************************************************************************************" << endl;
			std::cout << "Your chice:";
			choice = Protection(InputValue, 0, 3);
			if (InputValue == 0)
			{
				break;
			}
		}
		if (choice == 1)
		{
			system("cls");
			sort(Vec_of_tickets.begin(), Vec_of_tickets.end(), SortByPoint);
			std::cout << "********************************************Sorting by destination********************************************" << endl;
			ShowFlights(Vec_of_tickets);
		}
		if (choice == 2)
		{
			system("cls");
			std::cout << "********************************************Sorting by business class cost*******************************************" << endl;
			sort(Vec_of_tickets.begin(), Vec_of_tickets.end(), SortByBusinessCost);
			ShowFlights(Vec_of_tickets);
		}
		if (choice == 3)
		{
			system("cls");
			std::cout << "*******************************************Sorting by econom class cost********************************************" << endl;
			sort(Vec_of_tickets.begin(), Vec_of_tickets.end(), SortByEconomCost);
			ShowFlights(Vec_of_tickets);
		}
		if (choice == 0)
		{
			break;
		}

	}
}
const bool SortByPoint(const Air_Ticket RHS, const Air_Ticket LHS)
{
	return LHS.destination > RHS.destination;
}
const bool SortByBusinessCost(const Air_Ticket RHS, const Air_Ticket LHS)
{
	return LHS.businesscost > RHS.businesscost;
}
const bool SortByEconomCost(const Air_Ticket RHS, const Air_Ticket LHS)
{
	return LHS.economcost < RHS.economcost;
}


void Individual(vector <Air_Ticket> Vec_of_tickets)// поиск подходящих рейсов
{
	int choice, economquantity, businessquantity, i, InputValue, kolek, kolbus, ekcost, buscost,
		xyz,departure_hour,departure_min,departure_day,departure_month,
		current_day,current_month,current_hour,current_min;
	string destination;

	i = 0;
	system("cls");
	std::cout << "Welcome to section of searching best flight. " << endl;
	ShowFlights(Vec_of_tickets);
	std::cout << "Enter destination, current time(hour:minutes), current date" << endl;
	cin >> destination;
	for (int i = 0; i < Vec_of_tickets.size(); i++)
	{
		if (destination == Vec_of_tickets.at(i).destination)
		{
			std::cout << "You choose flights that going to " << Vec_of_tickets.at(i).destination << endl;
		}
	}
	std::cout << "Let's find best flight for you" << endl;
	std::cout << "Enter planning departure time(hours:minutes)" << endl;
	scanf_s("%d%*c%d", &departure_hour, &departure_min);
	std::cout << "Enter planning departure date(day.month)" << endl;
	scanf_s("%d%*c%d", &departure_day, &departure_month);

	std::cout << "Enter current time(hours:minutes)" << endl;
	scanf_s("%d%*c%d", &current_hour, &current_min);
	std::cout << "Enter current date(day.month)" << endl;
	scanf_s("%d%*c%d", &current_day, &current_month);
	for (int i = 0; i < Vec_of_tickets.size(); i++)
	{
		if ((destination == Vec_of_tickets.at(i).destination) &&((departure_month > Vec_of_tickets.at(i).departure_month)&&((current_month<= Vec_of_tickets.at(i).arrival_month)||(current_day<= Vec_of_tickets.at(i).arrival_day)||(current_hour<= Vec_of_tickets.at(i).arrival_hour)||(current_min<= Vec_of_tickets.at(i).arrival_min))))
		{
			std::cout << "************************************************************************************************************************\n"
				
				<< "№ of voyages \t" << Vec_of_tickets.at(i).flight_number << endl
				<< "Bus type: \t" << Vec_of_tickets.at(i).bus_type << endl
				<< "Destination:\t" << Vec_of_tickets.at(i).destination << endl
				<< "Date of departure:\t" << Vec_of_tickets.at(i).departure_day << "." << Vec_of_tickets.at(i).departure_month << endl
				<< "Departure time:\t" << Vec_of_tickets.at(i).departure_hour << ":" << Vec_of_tickets.at(i).departure_min << endl
				<< "Date of arrival:\t" << Vec_of_tickets.at(i).arrival_day << "." << Vec_of_tickets.at(i).arrival_month << endl
				<< "Arrival time:\t" << Vec_of_tickets.at(i).arrival_hour << ":" << Vec_of_tickets.at(i).arrival_min << endl
				<< "Capacity of bus:\t" << Vec_of_tickets.at(i).buscap << endl
				<< "Quantity of tickets (bussiness):\t" << Vec_of_tickets.at(i).businessquantity << endl
				<< "$ (bussiness):\t" << Vec_of_tickets.at(i).businesscost << endl
				<< "Quantity of tickets (eco):\t" << Vec_of_tickets.at(i).economquantity << endl
				<< "$ (eco):\t" << Vec_of_tickets.at(i).economcost << endl
				<< "\n**********************************************************************************************************************" << endl;
			i++;
		}
		else if ((destination == Vec_of_tickets.at(i).destination) && ((departure_month == Vec_of_tickets.at(i).departure_month) && (departure_day > Vec_of_tickets.at(i).departure_day) && ((current_month <= Vec_of_tickets.at(i).arrival_month) || (current_day <= Vec_of_tickets.at(i).arrival_day) || (current_hour <= Vec_of_tickets.at(i).arrival_hour) || (current_min < Vec_of_tickets.at(i).arrival_min))))
		{
			std::cout << "************************************************************************************************************************\n"

				<< "№ of voyages \t" << Vec_of_tickets.at(i).flight_number << endl
				<< "Bus type: \t" << Vec_of_tickets.at(i).bus_type << endl
				<< "Destination:\t" << Vec_of_tickets.at(i).destination << endl
				<< "Date of departure:\t" << Vec_of_tickets.at(i).departure_day << "." << Vec_of_tickets.at(i).departure_month << endl
				<< "Departure time:\t" << Vec_of_tickets.at(i).departure_hour << ":" << Vec_of_tickets.at(i).departure_min << endl
				<< "Date of arrival:\t" << Vec_of_tickets.at(i).arrival_day << "." << Vec_of_tickets.at(i).arrival_month << endl
				<< "Arrival time:\t" << Vec_of_tickets.at(i).arrival_hour << ":" << Vec_of_tickets.at(i).arrival_min << endl
				<< "Capacity of bus:\t" << Vec_of_tickets.at(i).buscap << endl
				<< "Quantity of tickets (bussiness):\t" << Vec_of_tickets.at(i).businessquantity << endl
				<< "$ (bussiness):\t" << Vec_of_tickets.at(i).businesscost << endl
				<< "Quantity of tickets (eco):\t" << Vec_of_tickets.at(i).economquantity << endl
				<< "$ (eco):\t" << Vec_of_tickets.at(i).economcost << endl
				<< "\n**********************************************************************************************************************" << endl;
			i++;
		}
		else if ((destination == Vec_of_tickets.at(i).destination) && ((departure_month == Vec_of_tickets.at(i).departure_month) && (departure_day == Vec_of_tickets.at(i).departure_day) &&(departure_hour > Vec_of_tickets.at(i).departure_hour) && ((current_month <= Vec_of_tickets.at(i).arrival_month) || (current_day <= Vec_of_tickets.at(i).arrival_day) || (current_hour <= Vec_of_tickets.at(i).arrival_hour) || (current_min < Vec_of_tickets.at(i).arrival_min))))
		{
			std::cout << "************************************************************************************************************************\n"

				<< "№ of voyages \t" << Vec_of_tickets.at(i).flight_number << endl
				<< "Bus type: \t" << Vec_of_tickets.at(i).bus_type << endl
				<< "Destination:\t" << Vec_of_tickets.at(i).destination << endl
				<< "Date of departure:\t" << Vec_of_tickets.at(i).departure_day << "." << Vec_of_tickets.at(i).departure_month << endl
				<< "Departure time:\t" << Vec_of_tickets.at(i).departure_hour << ":" << Vec_of_tickets.at(i).departure_min << endl
				<< "Date of arrival:\t" << Vec_of_tickets.at(i).arrival_day << "." << Vec_of_tickets.at(i).arrival_month << endl
				<< "Arrival time:\t" << Vec_of_tickets.at(i).arrival_hour << ":" << Vec_of_tickets.at(i).arrival_min << endl
				<< "Capacity of bus:\t" << Vec_of_tickets.at(i).buscap << endl
				<< "Quantity of tickets (bussiness):\t" << Vec_of_tickets.at(i).businessquantity << endl
				<< "$ (bussiness):\t" << Vec_of_tickets.at(i).businesscost << endl
				<< "Quantity of tickets (eco):\t" << Vec_of_tickets.at(i).economquantity << endl
				<< "$ (eco):\t" << Vec_of_tickets.at(i).economcost << endl
				<< "\n**********************************************************************************************************************" << endl;
			i++;
		}
		else if ((destination == Vec_of_tickets.at(i).destination) && ((departure_month == Vec_of_tickets.at(i).departure_month) && (departure_day == Vec_of_tickets.at(i).departure_day) && (departure_hour == Vec_of_tickets.at(i).departure_hour) && (departure_min > Vec_of_tickets.at(i).departure_min) && ((current_month <= Vec_of_tickets.at(i).arrival_month) || (current_day <= Vec_of_tickets.at(i).arrival_day) || (current_hour <= Vec_of_tickets.at(i).arrival_hour) || (current_min < Vec_of_tickets.at(i).arrival_min))))
		{
			std::cout << "************************************************************************************************************************\n"

				<< "№ of voyages \t" << Vec_of_tickets.at(i).flight_number << endl
				<< "Bus type: \t" << Vec_of_tickets.at(i).bus_type << endl
				<< "Destination:\t" << Vec_of_tickets.at(i).destination << endl
				<< "Date of departure:\t" << Vec_of_tickets.at(i).departure_day << "." << Vec_of_tickets.at(i).departure_month << endl
				<< "Departure time:\t" << Vec_of_tickets.at(i).departure_hour << ":" << Vec_of_tickets.at(i).departure_min << endl
				<< "Date of arrival:\t" << Vec_of_tickets.at(i).arrival_day << "." << Vec_of_tickets.at(i).arrival_month << endl
				<< "Arrival time:\t" << Vec_of_tickets.at(i).arrival_hour << ":" << Vec_of_tickets.at(i).arrival_min << endl
				<< "Capacity of bus:\t" << Vec_of_tickets.at(i).buscap << endl
				<< "Quantity of tickets (bussiness):\t" << Vec_of_tickets.at(i).businessquantity << endl
				<< "$ (bussiness):\t" << Vec_of_tickets.at(i).businesscost << endl
				<< "Quantity of tickets (eco):\t" << Vec_of_tickets.at(i).economquantity << endl
				<< "$ (eco):\t" << Vec_of_tickets.at(i).economcost << endl
				<< "\n**********************************************************************************************************************" << endl;
			i++;
		}
	}

	

}