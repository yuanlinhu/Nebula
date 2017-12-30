


#include <iostream>
#include <winsock2.h>

#pragma  comment(lib,"ws2_32.lib")

#include <event2/bufferevent.h>  
#include <event2/buffer.h>  
#include <event2/listener.h>  
#include <event2/util.h>  
#include <event2/event.h> 

#include <boost/thread.hpp>

#include "address.pb.h"

using namespace std;

void Hello() {
	// 睡眠一秒以模拟数据处理。

	std::cout << "Hello, World!" << std::endl;
}



static void
echo_read_cb(struct bufferevent *bev, void *ctx)
{
        /* This callback is invoked when there is data to read on bev. */
        struct evbuffer *input = bufferevent_get_input(bev);
        struct evbuffer *output = bufferevent_get_output(bev);

		char msg[4096] = {0};
		bufferevent_read(bev, msg, 4096);

		std::string recvString = msg;

		tutorial::Person person;
		person.ParseFromString(recvString);

		printf("msg: <<id:[%d], name:[%s] \n", person.id(), person.name().c_str());

        /* Copy all the data from the input buffer to the output buffer. */
        //evbuffer_add_buffer(output, input);


		//cout<<""<<input->get
}

static void
echo_event_cb(struct bufferevent *bev, short events, void *ctx)
{
        if (events & BEV_EVENT_ERROR)
                perror("Error from bufferevent");
        if (events & (BEV_EVENT_EOF | BEV_EVENT_ERROR)) {
                bufferevent_free(bev);
        }
}

static void
accept_conn_cb(struct evconnlistener *listener,
    evutil_socket_t fd, struct sockaddr *address, int socklen,
    void *ctx)
{
        /* We got a new connection! Set up a bufferevent for it. */
        struct event_base *base = evconnlistener_get_base(listener);
        struct bufferevent *bev = bufferevent_socket_new(
                base, fd, BEV_OPT_CLOSE_ON_FREE);

        bufferevent_setcb(bev, echo_read_cb, NULL, echo_event_cb, NULL);

        bufferevent_enable(bev, EV_READ|EV_WRITE);
}

static void
accept_error_cb(struct evconnlistener *listener, void *ctx)
{
        struct event_base *base = evconnlistener_get_base(listener);
        int err = EVUTIL_SOCKET_ERROR();
        fprintf(stderr, "Got an error %d (%s) on the listener. "
                "Shutting down.\n", err, evutil_socket_error_to_string(err));

        event_base_loopexit(base, NULL);
}

int
main(int argc, char **argv)
{
	WORD sockVersion = MAKEWORD(2,2);         //请求2.2版本的WinSock库
	// 用于接收Wjndows Socket的结构信息
	WSADATA wsaData;                         
	if(WSAStartup(sockVersion, &wsaData)!=0){
		return -1;
	}

	//boost::thread hello_thread(Hello);


	struct event_base *base;
	struct evconnlistener *listener;
	struct sockaddr_in sin;

	int port = 9876;

	if (argc > 1) {
		port = atoi(argv[1]);
	}
	if (port<=0 || port>65535) {
		puts("Invalid port");
		return 1;
	}

	base = event_base_new();
	if (!base) {
		puts("Couldn't open event base");
		return 1;
	}

    memset(&sin, 0, sizeof(sin));
    sin.sin_family = AF_INET;
    sin.sin_addr.s_addr = htonl(0);
    sin.sin_port = htons(port);

	listener = evconnlistener_new_bind(base, accept_conn_cb, NULL,
		LEV_OPT_CLOSE_ON_FREE|LEV_OPT_REUSEABLE, -1,
		(struct sockaddr*)&sin, sizeof(sin));
	if (!listener) {
		perror("Couldn't create listener");
		return 1;
	}
	evconnlistener_set_error_cb(listener, accept_error_cb);

	printf("server start \n");

	event_base_dispatch(base);
        
	printf("server end \n");
	return 0;
}