#ifndef _PROCESS_H_
#define _PROCESS_H_

#include <unistd.h>

#include "public.h"

namespace Process
{

pid_t Fork();

std::string ProcessName();

pid_t ProcessId();

}/* end of Process */

#endif//_PROCESS_H_
