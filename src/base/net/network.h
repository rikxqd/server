#ifndef _NETWORK_H_
#define _NETWORK_H_

#include <map>
#include "utility/share_ptr.h"
#include "thread/thread_task.h"
#include "net/event_poller.h"
#include "net/endpoint.h"


namespace Net
{

class Network : public Thread::ThreadTask
{
public:
	Network();
	~Network();

	bool Init( std::string ip, uint16 port );

	void Start();

	void RegisteClient( EndpointPtr endpoint );

	void Stop();

	virtual void Process();

private:
	volatile mutable bool			m_running;
	EventPollerPtr					m_event_poller;
	EndpointPtr						m_endpoint;
	std::map<int32, EndpointPtr>	m_client_endpoints;
};

typedef SharePtr<Network> NetworkPtr;

}

#endif//_NETWORK_H_

