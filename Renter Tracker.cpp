//Renter Tracker
//By Wyatt Giles, Brandan Ivie, Tanner Davis
#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <algorithm>
#include <ctime>
using namespace std;
void read ();
void write ();
void newwrite ();
void sortFile();
int main(){
	
  	//declare variable
  	int menuOption = 0;
  	int exitVar = 1;

	//begin loop
	do {
		//display menu and get option
		cout << endl;
		cout << "1 Add to the file " << endl;
		cout << "2 Create a new file" << endl;
		cout << "3 Read the file" << endl;
		cout << "4 End Program " << endl;
		cout << "Enter menu option: ";
		cin >> menuOption;
		cout << endl;
		//clears the buffer so getline() can be used
		cin.ignore();
		
		//Call the menuoption functions.
		//Switch Statement to Choose How to Proceed
		
		switch (menuOption){
			case 1:
				read();
				break;
			case 2:
				write();
				break;
			case 3:
				newwrite();
				break;
			case 4:
				exitVar = 0;
				break;
			default:
				cout << "Incorrect Opption" << endl;
				break;
		}	//end switch
//Start While loop
	} while (exitVar != 0); //end do while loop
	sortFile();
	return 0;
}//end main function
void read (){
	string file = "";
	cout << "What file do you want to read?" << endl;
	cin >> file;
	{
		time_t currentTime;
		struct tm *localTime;

		time( &currentTime );                   // Get the current time
		localTime = localtime( &currentTime );  // Convert the current time to the local time

		int Day    = localTime->tm_mday;
		int Month  = localTime->tm_mon + 1;
		int Year   = localTime->tm_year + 1900;

		std::cout << "And the current date is: " << Day << "/" << Month << "/" << Year << std::endl;
	}
	 
}//end read function
void write (){
	cout << "What is the file name?" << endl;

	 
}//end write function
void newwrite (){
	string filename = "";
	string test = "";
	cout << "What is the new file's name?" << endl;
	cin >> filename;
	fstream file;
	file.open(filename, ios::app);
	cin >> test;
	file << test << endl;
	file.close();
	fstream textfile;
	textfile.open("Text", ios::app);
	textfile << filename << endl;
	textfile.close();
	
}
void sortFile(){
	//declares the items and fstreams
	fstream fileRead;
	fstream fileWrite;
	vector<string> store;
	vector<int> x;
	int date = 0;
	int count = 0;
	string dateC = "";
	string dateY = "";
	string dateM = "";
	string dateD = "";
	string notes = "";
	string countS = "";
	
	fileRead.open("Calendar.txt");//opens the file
	//retrieves first line in text
	getline(fileRead >> ws, dateM, '/');
	getline(fileRead >> ws, dateD, '/');
	getline(fileRead >> ws, dateY, '|');
	getline(fileRead >> ws, notes);
	while (!fileRead.eof()) {
		//dropes extra space off the end of the year
		dateC = dateY.substr(0,4);
		//converts the counter to a string so it can be appended on to the end of the date variable to be called later
		if(count < 10){
			countS = "0" + to_string(count);
		}else if(count < 100){
			countS = to_string(count);
		}
		//adds the rest of the information to be sorted
		dateC += dateM + dateD + countS;
		//converet the string into a int
		istringstream(dateC) >> date;
		//stores information to vectors
		x.push_back(date);
		store.push_back(notes);
		//retrieves next line in text document
		getline(fileRead >> ws, dateM, '/');
		getline(fileRead >> ws, dateD, '/');
		getline(fileRead >> ws, dateY, '|');
		getline(fileRead >> ws, notes);
		count += 1;//A counter to keep track of which line from the text document is beign retrieved
	}//end while loop
	fileRead.close();//closes the file
	fileWrite.open("Calendar.txt");//reopens the file to be overwriten
	//sorts the array with the dates in it
	sort(x.begin(), x.end());
	//take the sorted data and write it to the code in date order
	for(int i = 0; i < x.size(); i += 1){
		//accesses the information to be broken up
		date = x[i];
		//starts break up of data to be used
		//converts the integer to a string
		countS = to_string(date);
		//breaks string into the day month and year
		dateY = countS.substr(0,4);
		dateM = countS.substr(4,2);
		dateD = countS.substr(6,2);
		//connects the date to the rest of the file
		countS = countS.substr(8,2);
		istringstream(countS) >> count;//convert back to a int
		//calls the title and notes of the event
		notes = store[count];
		//writes the entries back onto the file
		fileWrite << dateM << "/" << dateD << "/" << dateY << " | " << notes << '\n';
	}//end for loop
	fileWrite.close();//closes the text file
}//end sortFile
