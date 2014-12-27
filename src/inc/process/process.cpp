#include "process.h"
#include <iostream>


using namespace std;

pid_t Fork(void)
{
	pid_t	pid = fork();
	if ( -1 == pid )
		cout << "fork error" << endl;
	return pid;
}