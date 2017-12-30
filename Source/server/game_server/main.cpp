

#include <iostream>  
#include "address.pb.h"  


using namespace std;  
using namespace tutorial;  

int main()  
{  
	Person person;  

	person.set_name("flamingo");     
	person.set_id(18);     

	cout<<person.name()<<endl;  
	//cout<<person.age()<<endl;  


	system("pause");  
	return 0;  
}  