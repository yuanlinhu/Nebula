

#include <iostream>  
#include "address.pb.h"  
#include <fstream>


#include <winsock2.h>

#pragma  comment(lib,"ws2_32.lib")

#include <event2/bufferevent.h>  
#include <event2/buffer.h>  
#include <event2/listener.h>  
#include <event2/util.h>  
#include <event2/event.h> 

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

void cb_func(evutil_socket_t fd, short what, void *arg)
{
	const char *data = (const char *)arg;
	printf("Got an event on socket %d:%s%s%s%s [%s]",
		(int) fd,
		(what&EV_TIMEOUT) ? " timeout" : "",
		(what&EV_READ)    ? " read" : "",
		(what&EV_WRITE)   ? " write" : "",
		(what&EV_SIGNAL)  ? " signal" : "",
		data);
}

int main()  
{  

	WORD sockVersion = MAKEWORD(2,2);         //请求2.2版本的WinSock库
	// 用于接收Wjndows Socket的结构信息
	WSADATA wsaData;                         
	if(WSAStartup(sockVersion, &wsaData)!=0){
		return -1;
	}

	event_base* new_event_base = event_base_new();


	event* ev1 = event_new(new_event_base, -1, EV_TIMEOUT|EV_READ|EV_PERSIST, cb_func,
		(char*)"Reading event");

	struct timeval five_seconds = {5,0};

	event_add(ev1, &five_seconds);

	event_base_dispatch(new_event_base);


	system("pause");  
	return 0;  
}  