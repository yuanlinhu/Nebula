

#include <iostream>  
#include "address.pb.h"  
#include <fstream>

using namespace std;  
using namespace tutorial;  

int main()  
{  
	Person person;  

	person.set_name("flamingo");     
	person.set_id(18);     

	cout<<person.name()<<endl;  
	//cout<<person.age()<<endl;  


	fstream output(argv[1], ios::out | ios::trunc | ios::binary);
	if (!person.SerializeToOstream(&output)) {
		cerr << "Failed to write address book."<<endl;
	}

	Person person1;
	


	system("pause");  
	return 0;  
}  