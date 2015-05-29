#include "xml.h"
#include <stdlib.h>
#include "tinyxml.h"
#include "global.h"



namespace XML
{

char	ip[32]			= {0};
int32	port			= 3000;
char	log_file[128]	= {0};
char	log_name[32]	= {0};
uint32	log_level		= 0;

bool LoadSeverCfg( const char* filename )
{
	TiXmlDocument doc( filename );
	if ( !doc.LoadFile() )
	{
		ERROR( "Load XML[%s], fail!", filename );
		return false;
	}

	TiXmlElement* root = doc.RootElement();
	TiXmlElement* server = root->FirstChildElement("server");
	if ( server )
	{
		TiXmlElement* server_info = server->FirstChildElement("ip");
		if ( server_info )
			strcpy( ip, server_info->GetText() );

		server_info = server->FirstChildElement("port");
		if ( server_info )
			port = atoi( server_info->GetText() );
	}

	TiXmlElement* log = root->FirstChildElement("log");
	if ( log )
	{
		TiXmlElement* log_info = log->FirstChildElement("file_name");
		if ( log_info )
			strcpy( log_file, log_info->GetText() );

		log_info = log->FirstChildElement("name");
		if ( log_info )
			strcpy( log_name, log_info->GetText() );

		log_info = log->FirstChildElement("level");
		if ( log_info )
			log_level = atoi( log_info->GetText() );
	}

	return true;
}

bool Load()
{
	return LoadSeverCfg( "../../doc/config/test.xml" );
}

}