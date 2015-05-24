#include <iostream>
#include <stdlib.h>
#include <stdio.h>

#include "tinyxml.h"
#include "public.h"
#include "net/server_app.h"


#define SERVER_PORT 3000
int32 port = 0;
char ip[64] = "127.0.0.1";

using namespace std;

void Init()
{
	TiXmlDocument doc( "doc/config/test.xml" );
	if ( !doc.LoadFile() )
	{
		cout << "xml load fail " << endl;
		exit( -1 );
	}

	TiXmlElement* root = doc.RootElement();
	TiXmlElement* first = root->FirstChildElement("server");
	if ( first )
	{
		TiXmlElement* second = first->FirstChildElement("ip");
		if ( second )
			strcpy( ip, second->GetText() );

		second = first->FirstChildElement("port");
		if ( second )
			port = atoi( second->GetText() );
	}
}

int main( int argc, char* argv[] )
{
	ServerAppPtr server = new ServerApp();
	server->Init( argc, argv );
	server->Start();
}
