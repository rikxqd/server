#ifndef _XML_H_
#define _XML_H_

#include "public.h"


namespace XML
{

extern char		ip[32];
extern int32	port;
extern char		log_file[128];
extern char		log_name[32];
extern uint32	log_level;

bool Load();

}

#endif//_GLOBAL_H_
