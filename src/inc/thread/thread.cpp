#include "thread.h"

#include <string.h>
#include <sys/syscall.h>
#include <sys/prctl.h>
#include <unistd.h>


__thread char m_name[64] = {"unknown"};

void Thread::OnRun()
{
      ::prctl( PR_SET_NAME, m_name );
}

void Thread::Name( const char* name )
{
      strncpy( m_name, name, sizeof(m_name) );
}

const char* Thread::Name() const
{
      return m_name;
}

int32 Thread::Key()
{
      return ::syscall( SYS_gettid );
}
