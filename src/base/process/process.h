#ifndef _PROCESS_H_
#define _PROCESS_H_

#include <unistd.h>

#include "public.h"

namespace ProcFunc
{

pid_t Fork(void);

string ProcName();

pid_t ProcId();

}/* end of ProcFunc */

#endif//_PROCESS_H_
