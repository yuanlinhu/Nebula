

#include <iostream>  
#include "address.pb.h"  
#include <fstream>

using namespace std;  
using namespace tutorial;  

static string file_name = "./1.file";
void write_proto()
{
 	Person person;  
 
 	person.set_name("flamingo32345 eewwsd ");     
 	person.set_id(1234565);     
 
 	cout<<person.name()<<endl;  
	cout<<person.id()<<endl;  


 	fstream output(file_name.c_str(), ios::out | ios::trunc | ios::binary);
 	if (!person.SerializeToOstream(&output)) {
 		cerr << "Failed to write address book."<<endl;
 	}
}


void read_proto()
{
	Person person_read;

	{
		// Read the existing address book.
		fstream input(file_name.c_str(), ios::in | ios::binary);
		if (!person_read.ParseFromIstream(&input)) {
			cerr << "Failed to parse address book." << endl;
			return ;
		}
	}

	cout<<person_read.name()<<endl;  
	cout<<person_read.id()<<endl;  
}

int main()  
{  

	write_proto();
	read_proto();

// 	Person person;  
// 
// 	person.set_name("flamingo32345");     
// 	person.set_id(18);     
// 
// 	cout<<person.name()<<endl;  
	//cout<<person.age()<<endl;  


// 	fstream output("./1.file", ios::out | ios::trunc | ios::binary);
// 	if (!person.SerializeToOstream(&output)) {
// 		cerr << "Failed to write address book."<<endl;
// 	}

	//Person person1;
	

	tutorial::Person person_read;

	{
		// Read the existing address book.
		fstream input("./1.file", ios::in | ios::binary);
		if (!person_read.ParseFromIstream(&input)) {
			cerr << "Failed to parse address book." << endl;
			return -1;
		}
	}

	cout<<person_read.name()<<endl;  
	cout<<person_read.id()<<endl;  





	system("pause");  
	return 0;  
}  