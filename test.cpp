#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
#include "KThread.h"
#include <unistd.h>

using namespace std;

class Thread:public KThread{
public:
	void run()override
	{
		while(true)
		{
			cout<<"test"<<endl;
			usleep(500000);
		}
	}
};

int main()
{
	Thread t;
	t.start();
	cout<<t.getTid();
	return 0;
}

