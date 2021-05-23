#include <iostream> //input output Stream
#include <string>	//Used for using string type or built in string functions
#include <fstream>//used for file handling
#include<conio.h>  //include getch and putch etc functions declaration
void menu();	//menu declared
void account(int option);  //Parametrized function declared Prototype
using namespace std;
string AccountType[] = {"", "CHECKINGS", "SAVINGS"}; // Account will hold three options which are inside this array
string response;	//Global Scope variable
string authenticatedUsers[]={"Krauss","Hitchens","Dawkins","Christopher","Jasim"}; //Authenticated Users
string authenticatedPasswords[]={"Uol","Dell","Richard","Hitchens","Farrukh"};	  //Authenticated Passwords
int AccountDetails[] = {1234,100,600}; //default values -->>1234 is pin number -->>100 is balance -->>600 is savings acconunt balance

bool authenticatedPin(int Pin) { //Parametrized function with bool return type only true or false can be returned by the function
	if (Pin == AccountDetails[0]) { //check applied to pin User can only continue if he enters 1234
		return true; 
	} else {
		return false;	//if wrong it will return false
	}
}
//Check Confirmation applied after every action done by user-->>User response will be granted after every transaction
bool proceed(string response) {
	if(response =="y" || response == "Y"){
		return true;
	} else if(response == "n" || response == "N"){
		string exit;
		cout << "\n\n\n\t Thank you for banking with us.";
		cin >> exit;
		return false;
	}
	
}
class AccountSettings {
		int type;		// Account type
		int balance;	// Account balance
	public:
		AccountSettings(int type) { //One Parametrized Constructor
			// type 1 = checkings
			// type 2 = savings
			this->type = type;
			this->balance = AccountDetails[this->type];
		}
		int getWithdraw() { //if the user wants to withdraw amount -->>It will input the amount.
			int withdrawAmount;
			cout << "Please enter amount to withdrawn:\n " << endl;
			cin >> withdrawAmount;

			// get account type -->> 1 or 2
			if(withdrawAmount <= this->balance){
				int AccountBalance = this->balance -= withdrawAmount; //Subtract the withdraw amount from the total amount and display Withdraw amount
				cout << "Dispensing... ";
				cout << "Rs."<< withdrawAmount << endl;
				
				// Update the account balance
				AccountDetails[this->type] = AccountBalance;
				getBalance();

			} else {
				cout << "Insufficent funds" << endl;
				getBalance();
			}
			return 0;
		}
		//If the user wants to submit some money
		int getDeposit() {
			int depositAmount;
			cout << "Please enter an amount to deposit:\n" << endl;
			cin >> depositAmount;

			int AccountBalance = this->balance += depositAmount;

			// update the account balance
			AccountDetails[this->type] = AccountBalance;

			cout << "\tRs." << depositAmount << " was deposited into your account";
			getBalance();
			 
			return 0;
		}
		//In case if the user wants to transfer some money
		int getTransfer() {
			int AmountTransfer;
			int TransferTo = this->type== 1 ? 2 : 1; //	Teranry operator applied then to select one options from one option at one time

			cout << "Enter amount to transfer to your "<< AccountType[TransferTo] << " account."<< endl;
			cin >>  AmountTransfer;
			/*if amount that user want to transfer is less than the current balance
				Then minus the total balance from the amount user entered to transfer .*/
			if(AmountTransfer <= AccountDetails[this->type]) {
				// update the current account balance in the selected account
				int NewBalance = this->balance -= AmountTransfer;
				AccountDetails[this->type] = NewBalance;

				// Set the new transfered amount to transfered account
				int TransferedAmount = AccountDetails[TransferTo] += AmountTransfer;
				AccountDetails[TransferTo] = TransferedAmount;

				cout << "Rs." << AmountTransfer << " has been transfered to your "<< AccountType[TransferTo] << " account." << endl;
				getBalance();

			} else {
				cout << "Insuffient funds." << endl;
				getBalance();
			}

			return 0;
		}
		//This method will every time you do an transaction it will ask for confirmation and after being done it will show you remaining balance
		int getBalance() {
			string confirmBalance;
			// get the account type, and return balance
			cout << "Would you like to check your "<< AccountType[this->type] << " account balance? (y/n)\n" << endl;
			cin >> confirmBalance;
			if(confirmBalance=="y" || confirmBalance=="Y"){
				cout << "Your account balance is: Rs." << this->balance << endl;
			} 
			
			cout << "\n\nWould you like to continue (y/n)?\n";
			cin >> response;

			if (proceed(response)) {
				account(this->type); // return to account menu
			}

			return 0;
		}
};
class LoginInfo{	//This class contains login information and will save the user login to system
public:			
	string loginInfo(){
		ofstream fileHandling;
		string name,password;
		cout<<"Enter your Name:"<<endl;
		getline(cin,name);
	if(name==authenticatedUsers[0]||name==authenticatedUsers[1]||name==authenticatedUsers[2]||name==authenticatedUsers[3]||name==authenticatedUsers[4]){
				char c=' '; 
			cout<<"Enter Password :"<<endl;
			while(c!=13){
				c=getch();
				if(c!=13){
				password+=c;
				cout<<"*";
				} 	
			}
		}else{
			cout<<"\nInvalid name.!\n";
			return 0; //In case if the name is entered unauthenticated Console will terminate
		}
		if(password==authenticatedPasswords[0]){
			menu();
		}else if(password==authenticatedPasswords[1]){
			menu();
		}else if(password==authenticatedPasswords[2]){
			menu();
		}else if(password==authenticatedPasswords[3]){
			menu();
		}else if(password==authenticatedPasswords[4]){
			menu();
		}else{
			cout<<"\n------------------\nInvalid Password.!\n------------------\n"<<endl;
			return 0;
		}
			/*	if(name==authenticatedUsers[0]){
				password=authenticatedPasswords[0];
			}else if(name==authenticatedUsers[1]){
				password=authenticatedPasswords[1];
			}else if(name==authenticatedUsers[2]){
				password=authenticatedPasswords[2];
			}else if(name==authenticatedUsers[3]){
				password=authenticatedPasswords[3];
			}else if(name==authenticatedUsers[4]){
				password=authenticatedPasswords[4];
			}else{
				cout<<"Invalid Password.!"<<endl;
				return 0;
			} */
		fileHandling.open("GeneratedDataBase.txt",ios::out);
		ofstream ofObject;
		fileHandling<<name<<" : ";
		fileHandling<<password;
		fileHandling.close();
		menu();
	}
}; 
void account(int option) {
		// account option = 1 (checkings)
		// account option = 2 (savings)
			cout << "\n\n" <<AccountType[option] << "--\n\t1. Check balance" //Display Menu by selecting items from the global scope array
				<<"\n\t2. Withdraw from " << AccountType[option] 
				<<"\n\t3. Deposit to " << AccountType[option] 
				<<"\n\t4. Transfer " 
				<<"\n\t5. --Return to Menu." << endl;

		// Pass in account type
		AccountSettings Account(option); //Here the option is passed in to Account Settings Parametrized Constructor -->>Checkings or Savings

		int selectMenu;
		cin >> selectMenu; //Input option from menu
		
		switch(selectMenu){ //According to input from user Following Functionality will be performed
			case 1:
				cout << Account.getBalance();
				break;
			case 2: 
				cout << Account.getWithdraw();
				break;
			case 3: 
				cout << Account.getDeposit();
				break;
			case 4:
				cout << Account.getTransfer();
				break;
			case 5:
				menu(); // return to main menu
				break;
			default:
				cout << "Would you like to continue (y/n)\n";
				cin >> response;
				proceed(response);
			
				if (proceed(response)) {
					menu(); // return to main menu
				} 
				break;
		}
}

void menu() { //Main Menu
	int option;
	cout << "\n\nMain Menu--" <<endl;
	cout << "\tPlease make a selection. " << endl;
	cout << "\t1. Checkings \n\t2. Savings \n\t3. Exit" << endl;
	cin >> option;
	switch(option){
		case 1: account(option); // checkings
			break;
		case 2: account(option); // savings
			break;
		case 3:
			cout<<"\nThanks for Banking with us.\n";
			break; //In case if the user press 3 Console will quit
		default:
			cout << "Would you like to continue (y/n)\n";
			cin >> response;
			proceed(response);
			
			if (proceed(response)) {
				menu();
			} 
			break;
	}
}
void transOutput(){ //trans Output function will create an stunning Console effect
		cout<<endl<<endl<<endl<<"\n\n\t\t\t\tThe University of Lahore"<<endl;
			cout<<"\n\t\t\t\tATM Machine/Simulator\n";
			cout<<"\n\t\t\t\tMade By: Jasim Farrukh.";
		    getch(); //Wait for the user to hit enter
		    cout<<endl;
		    system("CLS"); //clear the screen
		    cout<<"\n\n\n\xb2\xb2\xb2\xb2\xb2\xb2\xb2\xb2\xb2\xb2\xb2\xb2\xb2\xb2\xb2\xb2\xb2\xb2\xb2\xb2\xb2\xb2\xb2\xb2\xb2\xb2\xb2\xb2\xb2\xb2\xb2\xb2\xb2\xb2\xb2\xb2\xb2\xb2\xb2\xb2\xb2\xb2\xb2\xb2\xb2\xb2\xb2\xb2\xb2\xb2 ENTRY MENU \xb2\xb2\xb2\xb2\xb2\xb2\xb2\xb2\xb2\xb2\xb2\xb2\xb2\xb2\xb2\xb2\xb2\xb2\xb2\xb2\xb2\xb2\xb2\xb2\xb2\xb2\xb2\xb2\xb2\xb2\xb2\xb2\xb2\xb2\xb2\xb2\xb2\xb2\xb2\xb2\xb2\xb2\xb2\xb2\xb2\xb2\xb2\xb2\xb2\xb2\xb2\xb2\xb2\xb2\xb2\xb2\xb2\xb2"<<endl<<endl;
		    cout<<endl<<endl<<endl<<"\t\t\t\t\t\t   Press"<<endl<<endl<<"\t\t\t\t\t\t-> 1 Checkings"<<endl<<"\t\t\t\t\t\t-> 2 Savings"<<endl<<"\t\t\t\t\t\t-> 3 Exit"<<endl<<"\t\t\t\t\t\t";
   			cout<<endl<<endl<<"";
}
int main() {system("color f2"); //Change the Console color
	 transOutput();//Function called
	 authenticatedPin(AccountDetails[0]); 	//Default Pin Passed which is stored in Above Global Array
	 LoginInfo logObject; //Object created 
	 logObject.loginInfo();
		return 0; //Program ends successfully
}
