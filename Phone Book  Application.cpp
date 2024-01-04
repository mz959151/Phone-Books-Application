
#include <iostream>
#include <fstream>
#include <string>
#include<cctype>

using namespace std;

const int MAX_NAMES = 100;

const string PHONEBOOK_FILENAME = "phonebook.txt";


struct Person
{
	string name;
	string phone;


	Person()
	{
		name = "";
		phone = "";
	}

	bool Matches(string x)
	{
		
	   

		return (name.find(x) != string::npos);
	}

   

};

void ReadAllPeople(Person people[], int &num_people)
{
	ifstream fin;
	fin.open(PHONEBOOK_FILENAME.c_str(), ios::app);
	if (fin.fail())
	{
		cout << "Unable to open file " << PHONEBOOK_FILENAME << endl;
		return;
	}

	int i = 0;
	getline(fin, people[i].name);
	while (!fin.eof() && i < MAX_NAMES)
	{
		getline(fin, people[i].phone);
	   
		i++;

		if (i < MAX_NAMES)
			getline(fin, people[i].name);
	}

	num_people = i;

	fin.close();
}

void SaveToFile(const Person people[], int num_people)
{
	ofstream fout;

	fout.open(PHONEBOOK_FILENAME.c_str());

	for(int i = 0; i < num_people; i++)
	{
		fout << people[i].name<<endl;
		fout <<people[i].phone<<endl;
	}
   
}

void AppendToFile(Person person)
{
	ofstream fin;
	fin.open(PHONEBOOK_FILENAME.c_str(),ios::app);

	fin << person.name<<endl;
	fin <<person.phone<<endl;

   
	fin.close();



   
}



void AddName(Person people[], int &num_people)
{
	Person person;
   

	cout <<"\nEnter a name to be added: ";
	getline(cin, person.name);
   
	cout <<"Enter the person's number: ";
	getline(cin, person.phone);

	for(int i = 0; i < num_people; i++)
	{
		if( i + 1  == num_people)
			people[num_people] = person;
	}
	num_people++;

   
	AppendToFile(person);
	cout <<"\n\nName has been added. "<<endl;

   

   
   
}


void ChangePhone(Person people[], int num_people)
{
	Person person;
	int count;

	cout <<"Enter name to change: ";
	getline(cin, person.name);


	for(count = 0; count < num_people; count++)
	{
		if(people[count].Matches(person.name))
		{	cout <<endl<< people[count].name<<endl;

		cout <<"Current number"<<people[count].phone;

		cout << "\nNew number: ";
		getline(cin, people[count].phone);

		SaveToFile(people,num_people);

		cout <<"\n\nNew number Saved.";   

		return;

		}

	}

	if(count = num_people)
		cout <<"\nName not found.";


}



void FindName(Person people[], int num_people)
{
   
}


void ListAllNames(const Person people[], int num_people)
{
	cout << "\n\nAll records:\n";
	for (int i = 0; i < num_people; i++)
		cout << people[i].name << " - " << people[i].phone << endl;
}

 main()
{
	Person people[MAX_NAMES];
	int num_people;

	
	ReadAllPeople(people, num_people);

	char choice;

	do
	{
		cout << "\n\nA - Add a name and phone number\n";
		cout << "C - Change a phone number\n";
		cout << "F - Find a name\n";
		cout << "L - List all names\n";
		cout << "Q - Quit\n\n";
		cout << "Choice? ";
		cin >> choice;
		cin.get();   // Read EOL

		choice = toupper(choice);

		switch(choice)
		{
			case 'A':	AddName(people, num_people);		break;
			case 'C':	ChangePhone(people, num_people);	break;
			case 'F':	FindName(people, num_people);		break;
			case 'L':	ListAllNames(people, num_people);	break;
		}
	} while (choice != 'Q' && choice != 'q');
}

