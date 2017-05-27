#include <iostream>

#include <event2/event.h>

#include "player.h"

using namespace std;



int main()
{
    Player player;
	int result = player.add(3, 5);
    cout<<"result = "<<result<<endl;
    event_base* base = event_base_new();

    return 0;
}
