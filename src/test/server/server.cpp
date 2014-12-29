#include <iostream>
#include <stdlib.h>
#include <stdio.h>

#include "net/warp_socket.h"
#include "process/process.h"

#include "tinyxml.h"


#define SERVER_PORT 3000

using namespace std;

int main( int argc, char* argv[] )
{
      TiXmlDocument doc( "doc/config/test.xml" );
      if ( !doc.LoadFile() )
      {
            cout << "xml load fail " << endl;
            exit( -1 );
      }
      //doc.Print( stdout );
      //cout << doc;
      {
            //TiXmlPrinter printer;
            //doc.Accept( &printer );
            //fprintf( stdout, "%s", printer.CStr() );
      }
      
      {
            TiXmlElement* RootElement = doc.RootElement();
            cout << RootElement->Value() << endl;
            TiXmlElement* FirstPerson = RootElement->FirstChildElement();
            for ( ; NULL != FirstPerson ; FirstPerson = FirstPerson->NextSiblingElement() )
            {
                  cout << FirstPerson->Value() << endl;
                  TiXmlAttribute* id = FirstPerson->FirstAttribute();
                  for ( ; NULL != id ; id = id->Next() )
                  {
                        cout << id->Value() << endl;
                        cout << id->Name() << endl;
                  }
            }
            
      }
      
      /*{
            TiXmlNode* node = doc.FirstChild( "Root" );
            assert( node );
            TiXmlElement* todoElement = node->ToElement();
            assert( todoElement  );
		node = todoElement->FirstChildElement();
		assert( node );
		
		int32 port = 0;
		todoElement->Attribute( "port", &port );
		const char* ip = todoElement->Attribute( "ip" );
		printf( "%s:%d\n", ip, port );
      }*/
      
      return 0;
      
      SOCKFD ssock = Socket( AF_INET, SOCK_STREAM, 0 );
      if ( 0 > ssock )
            exit( -1 );
            
      struct sockaddr_in saddr= {0};
      saddr.sin_family        = AF_INET;
      saddr.sin_port          = htons( SERVER_PORT );
      saddr.sin_addr.s_addr   = htonl( INADDR_ANY );
      
      int32 res = Bind( ssock, (Address*)&saddr, sizeof saddr );
      if ( 0 > res )
            exit( -1 );
            
      res = Listen( ssock, 1024 );
      if ( 0 > res )
            exit( -1 );
            
      for ( ; ; )
      {
            struct sockaddr_in caddr = {0};
		socklen_t ca_len = sizeof(caddr);
		SOCKFD csock = Accept( ssock, (Address*)&caddr, &ca_len );

            pid_t childpid = Fork();
		if ( 0 == childpid ) 
		{
			close( ssock );
			// str_echo( csock );
			exit( 0 );
		}
		close( csock );
	}
            
      exit( 0 );
}