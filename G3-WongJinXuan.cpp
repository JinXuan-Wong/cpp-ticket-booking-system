#include <iostream>
#include <iomanip>
#include <windows.h>  
#include <string>
#include <cctype>
#include <cstring>
#include <cstdlib>
#include <cmath>
#define RED_TEXT "\033[1;31m"  //Code for red color output
#define TOTAL_TICKETS 170
using namespace std;

void login();
void printTitle();
void menu(bool* onGoing);
void seatDisplay();
void vipSeats();
void generalSeats();
void orderTicket();
double calculate();
void payment(double total, string* receiptMsg, string* payMethod);
void receipt(string* receiptMsg, string* payMethod);
void ticket();
bool validateQuantity(char category, int* seatsQuantity);
bool validateSeats(char category, int* seatsQuantity);
void salesReport();

int tickets_sold = 0;
int cust_num = 0;
const string ticketType[2] = { "VIP", "General" };
const double ticketPrice[2] = { 788.90, 259.90 };
const int VIPROW = 3, VIPCOL = 10;
const int GENROW = 7, GENCOL = 20;
int vipAvailib = VIPROW * VIPCOL;
int generalAvailib = GENROW * GENCOL;
int currentVIPAmount = 0;
int currentGenAmount = 0;
bool currentVIPSeats[VIPROW][VIPCOL] = { false };  //array storing current seats chosen by user
bool currentGenSeats[GENROW][GENCOL] = { false };
double currentTotal;
bool vipSeatsReserv[VIPROW][VIPCOL] = { false };	//boolean array to indicate seats being reserved or not
bool genSeatsReserv[GENROW][GENCOL] = { false };

int main()
{
	bool onGoing = true;
	login();
	do {
		system("CLS");
		currentVIPAmount = 0;
		currentGenAmount = 0;
		currentTotal = 0;			//clear all data for new customer
		for (int row = 0; row < VIPROW; ++row) {
			for (int col = 0; col < VIPCOL; ++col) {
				currentVIPSeats[row][col] = false;		//initialize all seats chosen to empty (false)
			};
		};
		for (int row = 0; row < GENROW; ++row) {
			for (int col = 0; col < GENCOL; ++col) {
				currentGenSeats[row][col] = false;
			};
		};
		menu(&onGoing);
		cout << "\n\n\n";
	} while (tickets_sold < TOTAL_TICKETS && onGoing); //continue loop system until sold out or being quit

	cout << setw(80) << "Thank you for using this ticketing system." << endl;
	cout << setw(68) << "Have a nice day !!" << endl;
	cout << "\n\n\n";

	return 0;
}

void login() {
	printTitle();
	string username = "user1";
	string password = "password";
	string usernameInput, pswInput;
	cout << setw(77) << "Cool Play Concert Ticketing System" << endl;
	cout << setw(80) << "=========================================" << endl;
	cout << setw(64) << "Login Page" << endl;
	cout << setw(80) << "=========================================" << endl;
	cout << "\n\n\n";

	do {
		cout << setw(65) << "Enter username: ";
		getline(cin, usernameInput);
		if (username != usernameInput) {
			cout << setw(77) << "Invalid username. Please reenter." << endl;
		}
	} while (username != usernameInput);			//validation for correct username
	do {
		cout << setw(65) << "Enter password: ";
		getline(cin, pswInput);
		if (pswInput != password) {
			cout << setw(70) << "Wrong password. Try again." << endl;
		}
	} while (pswInput != password);					//validation for correct password
}

void printTitle() {
	cout << "\n\n";
	cout << setw(90) << " ___                  _       ___   _                 " << endl;
	cout << setw(90) << "(  _`\\               (_ )    (  _`\\(_ )               " << endl;
	cout << setw(90) << "| ( (_)   _      _    | |    | |_) )| |    _ _  _   _ " << endl;
	cout << setw(90) << "| |  _  /'_`\\  /'_`\\  | |    | ,__/'| |  /'_` )( ) ( )" << endl;
	cout << setw(90) << "| (_( )( (_) )( (_) ) | |    | |    | | ( (_| || (_) |" << endl;
	cout << setw(90) << "(____/'`\\___/'`\\___/'(___)   (_)   (___)`\\__,_)`\\__, |" << endl;
	cout << setw(90) << "                                               ( )_| |" << endl;
	cout << setw(90) << "                                               `\\___/'" << endl;
	cout << "\n\n";
}

void menu(bool* onGoing) {
	char menuOpt;

	printTitle();
	cout << setw(80) << "Welcome to concert ticketing system for " << endl;
	cout << setw(80) << "-----------------------------------------" << endl;
	cout << setw(68) << "Cool Play Concert" << endl;
	cout << setw(80) << "-----------------------------------------" << endl;
	cout << "\n\n";
	cout << setw(67) << "1 -- Seat display" << endl;
	cout << setw(67) << "2 -- Order ticket" << endl;
	cout << setw(67) << "3 -- Sales report" << endl;
	cout << setw(67) << "4 -- Close system" << endl;
	cout << "\n";
	cout << setw(67) << "Select an option: ";
	cin >> menuOpt;

	while (menuOpt != '1' && menuOpt != '2' && menuOpt != '3' && menuOpt != '4') {
		cout << setw(80) << "Invalid option, please enter again (1/2/3/4): ";
		cin >> menuOpt;
	}										//validation for correct menu option
	switch (menuOpt) {
	case '1':
		system("CLS");
		seatDisplay();
		break;
	case '2':
		system("CLS");
		orderTicket();
		break;
	case '3':
		system("CLS");
		salesReport();
		break;
	case '4':
		system("CLS");
		*onGoing = false;	//quit program
	};
	cout << "\n\n\n";
}

void seatDisplay() {
	char category;
	char action;

	cout << "\n\n";
	cout << setw(90) << "   _______       __                                  " << endl;
	cout << setw(90) << " /   ------.   / ._`_                                " << endl;
	cout << setw(90) << "|  /         ~--~    \\                               " << endl;
	cout << setw(90) << "| |             __    `.____________________ _^-----^" << endl;
	cout << setw(90) << "| |  I=|=======/--\\=========================| o o o |" << endl;
	cout << setw(90) << "\\ |  I=|=======\\__/=========================|_o_o_o_|" << endl;
	cout << setw(90) << " \\|                   /                       ~    ~ " << endl;
	cout << setw(90) << "   \\       .---.    .                                " << endl;
	cout << setw(90) << "     -----'     ~~''                                 " << endl << "\n\n";

	cout << setw(80) << "-----------------------------------------" << endl;
	cout << setw(67) << "Seats Display" << endl;
	cout << setw(80) << "-----------------------------------------" << endl << "\n";
	cout << setw(68) << "1 -- General Seats" << endl;
	cout << setw(64) << "2 -- VIP Seats" << endl;
	cout << setw(69) << "3 -- Overall Layout" << endl << "\n";
	cout << setw(65) << "Choose a category: ";
	cin >> category;

	while (category != '1' && category != '2' && category != '3') {
		cout << setw(82) << "Invalid input. Please enter again (1/2/3): ";
		cin >> category;
	}							//validation for correct category option

	if (category == '1') {
		cout << "\n";
		cout << setw(80) << "-----------------------------------------" << endl;
		cout << setw(70) << "General Seats Layout" << endl;
		cout << setw(80) << "-----------------------------------------" << endl;
		generalSeats();
	}
	else if (category == '2') {
		cout << "\n";
		cout << setw(80) << "-----------------------------------------" << endl;
		cout << setw(66) << "VIP Seats Layout" << endl;
		cout << setw(80) << "-----------------------------------------" << endl;
		vipSeats();
	}
	else {
		cout << "\n\n";
		cout << setw(91) << "-------------------------------------------------------------" << endl;
		cout << setw(30) << "|" << setw(62) << "|" << endl;
		cout << setw(30) << "|" << setw(62) << "|" << endl;
		cout << setw(30) << "|" << setw(32) << "Stage" << setw(30) << "|" << endl;
		cout << setw(30) << "|" << setw(62) << "|" << endl;
		cout << setw(30) << "|" << setw(62) << "|" << endl;
		cout << setw(91) << "-------------------------------------------------------------" << endl;
		vipSeats();
		generalSeats();
	}
	cout << "\n\n";
	cout << setw(67) << "1 -- Back to menu" << endl;
	cout << setw(71) << "2 -- Proceed to order" << endl;
	cout << setw(67) << "Choose an option: ";
	cin >> action;
	while (action != '1' && action != '2') {
		cout << setw(82) << "Invalid input. Please enter again (1/2): ";
		cin >> action;			//validation for corect action option
	};

	if (action == '2') {
		system("CLS");
		orderTicket();		//proceed to order
	};						//else auto loop back to menu() in main()
}


void generalSeats() {
	cout << "\n\n";
	for (int i = 0; i < GENROW; ++i) {
		cout << "\t\t";
		for (int j = 1; j <= GENCOL; ++j) {
			if (genSeatsReserv[i][j - 1]) {		//if already reserved (true)
				cout << RED_TEXT << "[" << char('A' + i) << j << "]" << "\033[0m";  //display red seats
			}
			else {
				cout << "[" << char('A' + i) << j << "]";	//else display normal color
			};
			if (j == 5 || j == 15) {
				cout << "   ";			//layout of seats: 5 columns left, 10 middle, 5 right
			}
		};
		cout << endl;
	};
}

void vipSeats() {
	cout << "\n\n";
	for (int i = 0; i < VIPROW; ++i) {
		cout << "\t\t\t\t\t";
		for (int j = 1; j <= VIPCOL; ++j) {
			if (vipSeatsReserv[i][j - 1]) {		//if already reserved (true)
				cout << RED_TEXT << "[" << char('A' + i) << j << "]" << "\033[0m";
			}
			else {
				cout << "[" << char('A' + i) << j << "]";
			};
		};
		cout << endl;
	};
}

void orderTicket() {
	char category;
	char confirm;
	char repeat = 'Y';
	char back = 'N';
	int seatsQuantity;
	string payMethod = "";
	string receiptMsg = "";

	do {
		system("CLS");
		cout << "\n\n";
		cout << setw(80) << "-----------------------------------------" << endl;
		cout << setw(66) << "Ticket ordering" << endl;
		cout << setw(80) << "-----------------------------------------" << endl << "\n\n";
		cout << setw(45) << "No." << setw(15) << "Ticket Type" << setw(15) << "Price" << endl;
		cout << setw(80) << "-----------------------------------------" << endl;
		for (int i = 0; i < 2; ++i) {		//display tickets category and respective price from constant
			cout << setw(45) << i + 1 << setw(15) << ticketType[i] << fixed << setprecision(2) << setw(15) << ticketPrice[i] << endl;
		};
		cout << "\n\n";

		cout << setw(75) << "Please enter the category of ticket: ";
		cin >> category;
		while (category != '1' && category != '2') {
			cout << setw(79) << "Invalid input. Please enter again (1/2): ";
			cin >> category;		//validation for category option
		};
		if (category == '1' && vipAvailib == 0 || category == '2' && generalAvailib == 0) {		//case when all tickets for the chosen category had sold out
			cout << setw(83) << "Sorry, no tickets left for this category." << endl;
			cout << setw(70) << "Kindly order other category." << endl;
			cout << "\n\n\n";
			cout << setw(75) << "Press [Y] go back to menu ... ...";		//bring user back to menu
			cin >> back;
			while (toupper(back) != 'Y') {
				cout << setw(70) << "Enter [Y] only: ";
				cin >> back;
			};
			break;			//end do while
		}

		if (validateQuantity(category, &seatsQuantity) && validateSeats(category, &seatsQuantity)) { //validation for quantity and seats to buy (both return true)
			cout << setw(78) << "Do you want add ticket? (Y/N): ";
			cin >> repeat;
			while (toupper(repeat) != 'Y' && toupper(repeat) != 'N') {
				cout << setw(72) << "Invalid input. Only Y/N: ";
				cin >> repeat;		//validate input
			};
		}
	} while (toupper(repeat) == 'Y');

	if (toupper(back) != 'Y') {		//if not going back to menu, continue run the following statements
		system("CLS");
		currentTotal = calculate();		//calculation for total price to pay
		cout << setw(75) << "Confirm Payment? (Y/N): ";
		cin >> confirm;
		while (toupper(confirm) != 'Y' && toupper(confirm) != 'N') {
			cout << setw(75) << "Invalid input. Only Y/N: ";
			cin >> confirm;		//validate input
		};
		if (toupper(confirm) == 'Y') {
			payment(currentTotal, &receiptMsg, &payMethod);		//proceed to payment after confirm payment
			receipt(&receiptMsg, &payMethod);					//proceed to print receipt
			tickets_sold += currentVIPAmount;	//update data
			tickets_sold += currentGenAmount;
			cust_num += 1;
			ticket();	//generate ticket(s)
		}
		else {			//case when user does not confirm payment
			for (int row = 0; row < VIPROW; ++row) {		//set the seat chosen back to false
				for (int col = 0; col < VIPCOL; ++col) {
					if (currentVIPSeats[row][col]) {
						vipSeatsReserv[row][col] = false;
					}
				};
			};
			for (int row = 0; row < GENROW; ++row) {		//set the seat chosen back to false
				for (int col = 0; col < GENCOL; ++col) {
					if (currentGenSeats[row][col]) {
						genSeatsReserv[row][col] = false;
					}
				};
			};
			vipAvailib += currentVIPAmount;
			generalAvailib += currentGenAmount;
		};
	};
}

bool validateQuantity(char category, int* seatsQuantity) {
	int amount;
	int ticketAvailib;

	if (category == '1') {
		ticketAvailib = vipAvailib;
	}
	else {
		ticketAvailib = generalAvailib;
	};

	cout << "\n\n";
	do {
		cout << setw(76) << "Please enter amount of ticket to buy: ";
		cin >> amount;
		if (amount > ticketAvailib) {
			cout << setw(90) << "Sorry, not enough ticket. Please reduce your amount." << endl;
			cout << setw(48) << "There are " << ticketAvailib << " seat(s) left." << endl;
		}
		else if (amount <= 0)
		{
			cout << setw(78) << "Invalid input, must be positive integer." << endl;
		};
	} while (amount > ticketAvailib || amount <= 0);		//validation for valid amount

	if (category == '1') {			//update data
		currentVIPAmount += amount;
		vipAvailib -= amount;
	}
	else {
		currentGenAmount += amount;
		generalAvailib -= amount;
	}
	*seatsQuantity = amount;	//used in validateSeats()
	return true;
}

bool validateSeats(char category, int* seatsQuantity) {
	char chRow;
	int seatRow, seatCol;

	cout << "\n\n";
	if (category == '1') {
		vipSeats();
	}
	else {
		generalSeats();
	};
	cout << "\n\n";

	for (int i = 1; i <= *seatsQuantity; i++) {		//looping times based on quantity of seats validated
		cout << setw(70) << "Please enter seat code " << i << ": ";
		cin >> chRow >> seatCol;			//input e.g. A12 , B3,  G20
		seatRow = toupper(chRow) - 'A';		//convert to integer for seats array handling

		if (category == '1') {
			while (seatRow < 0 || seatRow >= VIPROW || seatCol <= 0 || seatCol > VIPCOL || vipSeatsReserv[seatRow][seatCol - 1]) {
				if (vipSeatsReserv[seatRow][seatCol - 1]) {		//seats reserved (true)
					cout << setw(83) << "Seat not available, choose another: ";
				}
				else {
					cout << setw(86) << "Invalid seat code, please enter again: ";
				};
				cin >> chRow >> seatCol;
				seatRow = toupper(chRow) - 'A';
			};
			vipSeatsReserv[seatRow][seatCol - 1] = true;		//update seats currently chosen to seats reserved
			currentVIPSeats[seatRow][seatCol - 1] = true;
		}
		else {
			while (seatRow < 0 || seatRow >= GENROW || seatCol <= 0 || seatCol > GENCOL || genSeatsReserv[seatRow][seatCol - 1]) {
				if (genSeatsReserv[seatRow][seatCol - 1]) {
					cout << setw(83) << "Seat not available, choose another: ";
				}
				else {
					cout << setw(86) << "Invalid seat code, please enter again: ";
				};
				cin >> chRow >> seatCol;
				seatRow = toupper(chRow) - 'A';
			};
			genSeatsReserv[seatRow][seatCol - 1] = true;
			currentGenSeats[seatRow][seatCol - 1] = true;
		};
	};
	*seatsQuantity = 0; //set back to zero in case adding order
	return true;		//validation succeed
}

double calculate() {
	double total;
	cout << "\n\n\n";
	cout << right << setw(50) << "Ticket Category" << setw(20) << "Price/ticket" << setw(15) << "Quantity" << setw(15) << "Amount" << endl;
	cout << setw(101) << "*******************************************************************" << endl;
	cout << fixed << setprecision(2);
	if (currentVIPAmount != 0) {
		cout << setw(50) << ticketType[0] << setw(20) << ticketPrice[0] << setw(15) << currentVIPAmount << setw(15) << currentVIPAmount * ticketPrice[0] << endl;
	};
	if (currentGenAmount != 0) {
		cout << setw(50) << ticketType[1] << setw(20) << ticketPrice[1] << setw(15) << currentGenAmount << setw(15) << currentGenAmount * ticketPrice[1] << endl;
	}
	total = currentVIPAmount * ticketPrice[0] + currentGenAmount * ticketPrice[1];
	cout << setw(101) << "--------------------------------------------------------------------" << endl;
	cout << setw(69) << "Total payment: RM " << fixed << setprecision(2) << total << endl;
	cout << setw(101) << "--------------------------------------------------------------------" << endl;
	cout << "\n\n";

	return total;
}

void payment(double total, string* receiptMsg, string* payMethod) {
	char method;
	cout << "\n\n";
	cout << setw(80) << "-----------------------------------------" << endl;
	cout << setw(67) << "Payment Section" << endl;
	cout << setw(80) << "-----------------------------------------" << endl << "\n\n";
	cout << setw(71) << "1 -- Credit/Debit Card" << endl;
	cout << setw(58) << "2 -- Cash" << endl;
	cout << setw(62) << "3 -- E-Wallet" << endl << "\n";
	cout << setw(66) << "Choose a payment method: ";
	cin >> method;

	while (method != '1' && method != '2' && method != '3') {
		cout << setw(81) << "Invalid input. Please enter again (1/2/3): ";
		cin >> method;			//validation for input option
	};

	if (method == '1') {
		char creditNum[20];
		int mm, yy;
		string name;
		*payMethod = "Credit / Debit Card";
		cout << "\n";
		cout << setw(78) << "Enter credit card number (no space): ";
		cin >> creditNum;
		while (strlen(creditNum) != 16) {	//validation: only allow 16-digits number
			cout << setw(92) << "Invalid credit card number. Only 16 digits allowed." << endl;
			cout << setw(78) << "Enter credit card number (no space): ";
			cin >> creditNum;
		}
		cout << "\n";
		cout << setw(59) << "Expiry Date (MM): ";
		cin >> mm;
		while (mm < 1 || mm > 12) {
			cout << setw(77) << "Please enter a valid month (1 - 12)." << endl;
			cout << setw(59) << "Expiry Date (MM): ";
			cin >> mm;
		}
		cout << setw(62) << "Expiry Date (MM/YY): " << mm << "/";
		cin >> yy;
		while (yy < 24 || yy > 28) {
			cout << setw(77) << "Please enter a valid year (24 - 28)." << endl;
			cout << setw(62) << "Expiry Date (MM/YY): " << mm << "/";
			cin >> yy;
		}
		cout << "\n";
		cin.ignore();
		cout << setw(61) << "Enter name on card: ";
		getline(cin, name);

		*receiptMsg = "Card Payment Ref: ";		//add card number to extra receipt output
		*receiptMsg += creditNum;

		cout << "\n\n";
		cout << setw(67) << "Transaction successful." << endl;
	}
	else if (method == '2') {
		double cashPaid;
		*payMethod = "Cash";
		cout << setw(66) << "Enter cash paid (RM): ";
		cin >> cashPaid;
		while (cashPaid < 0 || cashPaid < total) {		//validation: cannot be negative / less then total payment
			if (cashPaid < 0) {
				cout << setw(70) << "Please enter a positive value." << endl;
			}
			else {
				cout << setw(63) << "Payment not enough." << endl;
				cout << setw(60) << "Pay more RM" << fixed << setprecision(2) << total - cashPaid << endl;
			}
			cout << setw(66) << "Enter cash paid (RM): ";
			cin >> cashPaid;
		}
		if (cashPaid > total) {		//display balance to return if cash paid more than total
			cout << setw(60) << "Balance: RM " << fixed << setprecision(2) << cashPaid - total << endl;
		}
		cout << "\n\n";
		cout << setw(60) << "Payment succeed." << endl;

		*receiptMsg = "Balance\t: RM ";			//add balance return to extra receipt output
		int integerPart = cashPaid - total;		//solve double into appropriate string
		*receiptMsg += to_string(integerPart);
		*receiptMsg += "." + to_string((int)round((cashPaid - total - integerPart) * 100));
	}
	else {
		*payMethod = "E-Wallet";
		cout << "\n\n";
		cout << setw(66) << "Transaction successful." << endl;
	};
}

void receipt(string* receiptMsg, string* payMethod) {
	char confirm;
	string seatRow, seatCol;
	cout << "\n\n";
	cout << setw(66) << "Print receipt? (Y/N): ";	//confirmation to print receipt
	cin >> confirm;
	while (toupper(confirm) != 'Y' && toupper(confirm) != 'N') {
		cout << setw(66) << "Invalid input. Only Y/N: ";
		cin >> confirm;
	};
	if (toupper(confirm) == 'Y') {
		system("CLS");
		//receipt variable: category, amount, seats, total price, payment method, invoice no., receiptMsg
		cout << "\n\n";
		cout << "\t ________________________________________________________________" << endl;
		cout << "\t| " << setw(64) << "|" << endl;
		cout << "\t| " << setw(53) << "+-----------------------------------------+" << setw(11) << "|" << endl;
		cout << "\t| " << setw(53) << "|    _____          __  ___  __           |" << setw(11) << "|" << endl;
		cout << "\t| " << setw(53) << "|   / ___/__  ___  / / / _ \\/ /__ ___ __  |" << setw(11) << "|" << endl;
		cout << "\t| " << setw(53) << "|  / /__/ _ \\/ _ \\/ / / ___/ / _ `/ // /  |" << setw(11) << "|" << endl;
		cout << "\t| " << setw(53) << "|  \\___/\\___/\\___/_/ /_/  /_/\\_,_/\\_, /   |" << setw(11) << "|" << endl;
		cout << "\t| " << setw(53) << "|                                /___/    |" << setw(11) << "|" << endl;
		cout << "\t| " << setw(53) << "+-----------------------------------------+" << setw(11) << "|" << endl;
		cout << "\t| " << setw(38) << " ** RECEIPT ** " << setw(26) << "|" << endl;
		cout << "\t| " << setw(64) << "|" << endl;
		cout << "\t| " << "\t\tInvoice number\t: INV000" << cust_num + 1 << setw(25) << "|" << endl;
		cout << "\t| " << "\t\tDate\t\t: 17/12/2023" << setw(22) << "|" << endl;
		cout << "\t|   " << "==========================================================" << setw(4) << "|" << endl;
		cout << "\t| " << setw(64) << "|" << endl;
		cout << "\t|   " << setw(20) << left << "Ticket category" << setw(10) << "Qty" << setw(15) << "Price (RM)"
			<< setw(15) << "Amount" << right << setw(2) << "|" << endl;
		if (currentVIPAmount != 0) {
			cout << "\t|   " << setw(20) << left << ticketType[0] << setw(10) << currentVIPAmount << setw(15) << ticketPrice[0]
				<< setw(15) << currentVIPAmount * ticketPrice[0] << right << setw(2) << "|" << endl;
		}
		if (currentGenAmount != 0) {
			cout << "\t|   " << setw(20) << left << ticketType[1] << setw(10) << currentGenAmount << setw(15) << ticketPrice[1]
				<< setw(15) << currentGenAmount * ticketPrice[1] << right << setw(2) << "|" << endl;
		}
		cout << "\t| " << setw(64) << "|" << endl;
		cout << "\t|\t\t" << "Seat(s) code\t: " << setw(32) << "|" << endl;
		for (int i = 0; i < VIPROW; ++i) {
			for (int j = 1; j <= VIPCOL; ++j) {			//output all seats currently chosen
				if (currentVIPSeats[i][j - 1]) {
					seatRow = "V" + string(1, char(i + 'A'));	//add 'V' in front of seat code to indicate vip seats
					seatCol = to_string(j);
					cout << "\t| " << "\t\t\t\t  " << setw(20) << left << seatRow + seatCol << right << setw(12) << "|" << endl;
				};
			};
		};
		for (int i = 0; i < GENROW; ++i) {
			for (int j = 1; j <= GENCOL; ++j) {
				if (currentGenSeats[i][j - 1]) {
					seatRow = string(1, char(i + 'A'));
					seatCol = to_string(j);
					cout << "\t| " << "\t\t\t\t  " << setw(20) << left << seatRow + seatCol << right << setw(12) << "|" << endl;
				};
			};
		};
		cout << "\t| " << setw(64) << "|" << endl;
		cout << "\t|   " << "----------------------------------------------------------" << setw(4) << "|" << endl;
		cout << "\t| " << "\t\tTotal Price\t: RM " << setw(20) << left << fixed << setprecision(2) << currentTotal << right << setw(9) << "|" << endl;
		cout << "\t| " << "\t\tPayment Method\t: " << setw(20) << left << *payMethod << right << setw(12) << "|" << endl;
		cout << "\t| " << "\t\t" << setw(40) << left << *receiptMsg << right << setw(10) << "|" << endl;
		cout << "\t| " << setw(64) << "|" << endl;
		cout << "\t ----------------------------------------------------------------" << endl;
		cout << "\n\n";
		cout << setw(50) << "Please take the receipt." << endl;
	};
	*receiptMsg = "";
	*payMethod = "";
}

void ticket() {
	string seatRow, seatCol;
	char next;
	int queue = tickets_sold + 1;
	cout << "\n\n";
	cout << setw(100) << "-----------------------------------------" << endl;
	cout << setw(86) << "Tickets Generated" << endl;
	cout << setw(100) << "-----------------------------------------" << endl << "\n\n";

	//ticket variable: category, price, seat, queue no.
	for (int i = 0; i < VIPROW; ++i) {
		for (int j = 1; j <= VIPCOL; ++j) {
			if (currentVIPSeats[i][j - 1]) {	//if current seats chosen (true), print ticket for that seat
				seatRow = "V" + string(1, char(i + 'A'));	//add 'V' in front of seat code to indicate vip seats
				seatCol = to_string(j);
				queue -= 1;
				cout << "\n\n";
				cout << "\t\t _________________________________________________________________________________________________________________________" << endl;
				cout << "\t\t|" << "\t\t\t|" << " *VIP**VIP**VIP**VIP**VIP**VIP**VIP**VIP**VIP**VIP**VIP**VIP**VIP**VIP**VIP**VIP**VIP**VIP**VIP* |" << endl;
				cout << "\t\t| " << setw(10) << left << ticketType[0] << right << "\t\t|  " << setw(70) << "|" << " Venue :" << setw(18) << " |" << endl;
				cout << "\t\t| RM\t" << fixed << setprecision(2) << ticketPrice[0] << "\t\t|  " << "   \\  |  |  |   __| _ _|   __|           _|    |    |         " << setw(8) << " |" << setw(26) << " |" << endl;
				cout << "\t\t|" << "\t\t\t| " << "   |\\/ |  |  | \\__ \\   |   (        _ \\   _|     _|    \\    -_)" << setw(8) << "|" << " National Stadium" << setw(9) << " |" << endl;
				cout << "\t\t| **FREE T-SHIRT" << "\t| " << "  _|__|| \\_\\/| _|__/_|__| \\___||  \\__|/ _|     \\__| _| _| \\___| " << setw(8) << " | " << "Bukit Jalil" << setw(15) << "  | " << endl;
				cout << "\t\t| **FREE GLOW STICK" << "\t| " << "  \\__ \\  __ / __ | _|     /  _ | \\__ \\  " << setw(32) << " | " << "Kuala Lumpur" << setw(14) << "  | " << endl;
				cout << "\t\t|" << "\t\t\t| " << "  ____/ _|  _| _| ___| _|_\\ ___| ____/" << setw(33) << "|" << setw(26) << " |" << endl;
				cout << "\t\t| GATE\t" << "15A" << "\t\t| " << setw(71) << "|" << setw(26) << " |" << endl;
				cout << "\t\t| SEAT\t" << seatRow << seatCol << "\t\t| " << setw(50) << ">> COOLPLAY WORLD TOUR <<" << setw(21) << "|" << " Wednesday" << setw(16) << " |" << endl;
				cout << "\t\t|" << "\t\t\t| " << setw(55) << " _____                       _____ " << setw(16) << "|" << " December 22, 2023" << setw(8) << " |" << endl;
				cout << "\t\t|" << "\t\t\t| " << setw(55) << " ( ___ )---------------------( ___ )" << setw(16) << "|" << setw(26) << " |" << endl;
				cout << "\t\t| GATE Open 6.30pm " << "\t| " << setw(56) << "  |   |  _   _   ___   ____   |   |  " << setw(15) << "|" << "    __________________" << setw(4) << " |" << endl;
				cout << "\t\t|" << "\t\t\t| " << setw(54) << "|   | \\ ( ) / )_ _( )  _)\\  |   |" << setw(17) << "|" << "   | \" All MUSIC" << setw(7) << "|" << setw(3) << " |" << endl;
				cout << "\t\t|" << "\t\t\t| " << setw(54) << "|   |  )\\_/(  _| |_ | '__/  |   |" << setw(17) << "|" << "   |   IS BEAUTIFUL \" | " << setw(2) << " |" << endl;
				cout << "\t\t| Queue No. " << queue << "\t\t| " << setw(54) << "|   |   \\_/  )_____()_(     |   |" << setw(17) << "|" << "    ------------------" << setw(4) << " |" << endl;
				cout << "\t\t|" << "\t\t\t| " << setw(54) << "|___|                       |___|" << setw(17) << "|" << setw(26) << " |" << endl;
				cout << "\t\t|" << "\t\t\t| " << setw(55) << "(_____)---------------------(_____)" << setw(16) << "|" << " C  O  O  L  P  L  A  Y" << "  |" << endl;
				cout << "\t\t|" << "\t\t\t|" << " *VIP**VIP**VIP**VIP**VIP**VIP**VIP**VIP**VIP**VIP**VIP**VIP**VIP**VIP**VIP**VIP**VIP**VIP**VIP* |" << endl;
				cout << "\t\t -------------------------------------------------------------------------------------------------------------------------" << endl;

			};
		};
	};
	for (int i = 0; i < GENROW; ++i) {
		for (int j = 1; j <= GENCOL; ++j) {
			if (currentGenSeats[i][j - 1]) {
				seatRow = string(1, char(i + 'A'));
				seatCol = to_string(j);
				queue -= 1;
				cout << "\n\n";
				cout << "\t\t ________________________________________________________________________________________________________________________" << endl;
				cout << "\t\t| " << setw(10) << left << ticketType[1] << right << "\t\t| " << setw(45) << " **COOLPLAY WORLD TOUR** " << setw(25) << "|" << " Venue :" << setw(18) << "|" << endl;
				cout << "\t\t| RM\t" << fixed << setprecision(2) << ticketPrice[1] << "\t\t| " << "   __  __              _                 __   _    _                " << setw(2) << "|" << setw(26) << "|" << endl;
				cout << "\t\t|" << "\t\t\t|" << "   |  \\/  |            (_)               / _| | |  | |            " << setw(5) << "|" << " National Stadium" << setw(9) << "|" << endl;
				cout << "\t\t|" << "\t\t\t|" << "   | \\  / | _   _  ___  _   ___    ___  | |_  | |_ | |__    ___   " << setw(5) << "|" << " Bukit Jalil" << setw(14) << "|" << endl;
				cout << "\t\t|" << "\t\t\t|" << "   | |\\/| || | | |/ __|| | / __|  / _ \\ |  _| | __|| '_ \\  / _ \\  " << setw(5) << "|" << " Kuala Lumpur" << setw(13) << "|" << endl;
				cout << "\t\t|" << "\t\t\t|" << "   | |  | || |_| |\\__ \\| || (__  | (_) || |   | |_ | | | ||  __/" << setw(7) << "|" << setw(26) << "|" << endl;
				cout << "\t\t| GATE\t" << "15A" << "\t\t|" << "   |_|  |_| \\__,_||___/|_| \\___|  \\___/ |_|    \\__||_| |_| \\___|" << setw(7) << "|" << setw(26) << "|" << endl;
				cout << "\t\t| SEAT\t" << seatRow << seatCol << "\t\t|" << setw(71) << "|" << " Wednesday" << setw(16) << "|" << endl;
				cout << "\t\t|" << "\t\t\t|" << setw(55) << " _____         _                           " << setw(16) << "|" << " December 22, 2023" << setw(8) << "|" << endl;
				cout << "\t\t|" << "\t\t\t|" << setw(55) << " / ____|       | |                          " << setw(16) << "|" << setw(26) << "|" << endl;
				cout << "\t\t| GATE Open 7.00pm " << "\t|" << setw(55) << " | (___   _ __  | |__    ___  _ __  ___  ___ " << setw(16) << "|" << "    __________________" << setw(4) << "|" << endl;
				cout << "\t\t|" << "\t\t\t|" << setw(55) << "  \\___ \\ | '_ \\ | '_ \\  / _ \\| '__|/ _ \\/ __|" << setw(16) << "|" << "   | \" WHERE MEMORIES | " << setw(2) << "|" << endl;
				cout << "\t\t|" << "\t\t\t|" << setw(55) << "  ____) || |_) || | | ||  __/| |  |  __/\\__ \\" << setw(16) << "|" << "   |    ARE CREATED \" | " << setw(2) << "|" << endl;
				cout << "\t\t| Queue No. " << queue << "\t\t|" << setw(55) << " |_____/ | .__/ |_| |_| \\___||_|   \\___||___/" << setw(16) << "|" << "    ------------------" << setw(4) << "|" << endl;
				cout << "\t\t|" << "\t\t\t|" << setw(54) << "        | |                                " << setw(17) << "|" << setw(26) << "|" << endl;
				cout << "\t\t|" << "\t\t\t|" << setw(55) << "         |_|                                 " << setw(16) << "|" << " C  O  O  L  P  L  A  Y" << "  |" << endl;
				cout << "\t\t ------------------------------------------------------------------------------------------------------------------------" << endl;
			};
		};
	};
	cout << "\n\n\n";
	cout << setw(75) << "Press [Y] if done ... ...";
	cin >> next;
	while (toupper(next) != 'Y') {
		cout << setw(70) << "Enter [Y] only: ";
		cin >> next;
	};
}

void salesReport() {
	char next;
	int vipSold = VIPROW * VIPCOL - vipAvailib;
	int genSold = GENROW * GENCOL - generalAvailib;
	double vipProfit = vipSold * ticketPrice[0];
	double genProfit = genSold * ticketPrice[1];

	cout << setw(110) << "===================================================================================" << endl << endl;
	cout << setw(97) << " ____        _             ____                       _   " << endl;
	cout << setw(97) << "/ ___|  __ _| | ___  ___  |  _ \\ ___ _ __   ___  _ __| |_ " << endl;
	cout << setw(97) << "\\___ \\ / _` | |/ _ \\/ __| | |_) / _ \\ '_ \\ / _ \\| '__| __|" << endl;
	cout << setw(97) << " ___) | (_| | |  __/\\__ \\ |  _ <  __/ |_) | (_) | |  | |_ " << endl;
	cout << setw(97) << "|____/ \\__,_|_|\\___||___/ |_| \\_\\___| .__/ \\___/|_|   \\__|" << endl;
	cout << setw(97) << "                                    |_|                   " << endl;
	cout << setw(60) << "Date: 17 December 2023" << endl;
	cout << setw(61) << "Event: CoolPlay Concert" << endl;
	cout << setw(57) << "Sales Person: user1" << endl;
	cout << setw(110) << "----------------------------------------------------------------------------------" << endl;
	cout << "\n";

	cout << setw(90) << "+=======================================+" << endl;
	cout << setw(90) << "|____  __________  ___  _______  _______|" << endl;
	cout << setw(90) << "||  |  |__|__|__|\\ ||   [__|__|  |__[__ |" << endl;
	cout << setw(90) << "||__|__| \\| \\|__| \\||   ___|  |__|_____]|" << endl;
	cout << setw(90) << "+=======================================+" << endl << endl;
	cout << setw(108) << "   TypeSeat      | PRICE (RM) | TOTAL SEAT | SEAT LEFT | SEAT SOLD | PROFIT (RM)" << endl;
	cout << setw(108) << "-----------------|------------|------------|-----------|-----------|------------" << endl;
	cout << setw(72) << "      VIP        |     788.90 |         30 |" << setw(11) << vipAvailib << "|" << setw(11) << vipSold << "|" << setw(11) << fixed << setprecision(2) << vipProfit << endl;
	cout << setw(72) << "    GENERAL      |     250.90 |        140 |" << setw(11) << generalAvailib << "|" << setw(11) << genSold << "|" << setw(11) << fixed << setprecision(2) << genProfit << endl;
	cout << setw(108) << "--------------------------------------------------------------------------------" << endl;
	cout << setw(46) << " TOTAL PROFIT(RM)" << setw(61) << vipProfit + genProfit << endl;
	cout << setw(108) << "--------------------------------------------------------------------------------" << endl;
	cout << setw(52) << "Number of customer(s): " << cust_num << endl;
	cout << "\n";

	int data[2] = { vipSold, genSold }; //data for number of dots to be display (1 dot = 2 tickets)
	string higher = ticketType[0];
	string lower = ticketType[1];
	if (genSold > vipSold) {
		data[0] = genSold;
		data[1] = vipSold; //find highest data for bar chart
		higher = ticketType[1]; //let higher bar chart to be displayed first
		lower = ticketType[0];
	}
	for (int dot = data[0]; dot > 0; dot--) { //number of dots for highest bar chart
		cout << "\t\t\t\t\t";
		for (int bar = 0; bar < 2; bar++) { //number of bar for 2 categories
			if (data[bar] >= dot) {
				cout << setw(17) << "*";
			}
			else {
				cout << " ";
			}
		}
		cout << endl;
	}
	cout << "\t\t\t\t\t" << setw(18) << higher << setw(18) << lower << endl << endl;
	cout << setw(111) << "===================================================================================" << endl;
	cout << setw(55) << "Note that one * = 1 tickets" << endl;
	cout << "\n\n\n";
	cout << setw(75) << "Press [Y] back to menu : ";
	cin >> next;
	while (toupper(next) != 'Y') {
		cout << setw(70) << "Enter [Y] only: ";
		cin >> next;
	};
}