#include "stable_headers.h"
#include "network_server_simple.h"
#include "handler.h"


namespace hilife
{
	ACE_Reactor *network_server_simple::g_reactor;

	typedef ACE_Acceptor <Logging_Handler, ACE_SOCK_ACCEPTOR> Logging_Acceptor;

	network_server_simple::network_server_simple(void)
	{
		g_reactor=0;
	}

	network_server_simple::~network_server_simple(void)
	{
	}

	int network_server_simple::run()
	{
		// Create the reactor we'll register our event handler derivatives with.
		ACE_NEW_RETURN (g_reactor,
						ACE_Reactor,
						1);

		// Create the acceptor that will listen for client connetions
		Logging_Acceptor peer_acceptor;

		/* Notice how similar this is to the open() call in Tutorial 1.  I
			read ahead when I created that one so that it would come out this
			way...  */
		if (peer_acceptor.open (ACE_INET_Addr (3333),
								g_reactor) == -1)
			ACE_ERROR_RETURN ((LM_ERROR,
							"%p\n",
							"open"),
							-1);

		/* Here's the easiest way to respond to signals in your application.
			Simply construct an ACE_Sig_Action object with a "C" function and
			the signal you want to capture.  As you might expect, there is
			also a way to register signal handlers with a reactor but we take
			the easy-out here.  */
		//ACE_Sig_Action sa ((ACE_SignalHandler) handler, SIGINT);

		ACE_DEBUG ((LM_DEBUG,
					"(%P|%t) starting up server logging daemon\n"));

		// Perform logging service until the signal handler receives SIGINT.
		while (1)
			g_reactor->handle_events ();

		// Close the acceptor so that no more clients will be taken in.
		peer_acceptor.close();

		// Free up the memory allocated for the reactor.
		delete g_reactor;

		ACE_DEBUG ((LM_DEBUG,
					"(%P|%t) shutting down server logging daemon\n"));
		return 0;

	}

	
	#if defined (ACE_HAS_EXPLICIT_TEMPLATE_INSTANTIATION)
	template class ACE_Acceptor <Logging_Handler, ACE_SOCK_ACCEPTOR>;
	template class ACE_Svc_Handler<ACE_SOCK_STREAM, ACE_NULL_SYNCH>;
	#elif defined (ACE_HAS_TEMPLATE_INSTANTIATION_PRAGMA)
	#pragma instantiate ACE_Acceptor <Logging_Handler, ACE_SOCK_ACCEPTOR>
	#pragma instantiate ACE_Svc_Handler<ACE_SOCK_STREAM, ACE_NULL_SYNCH>
	#endif /* ACE_HAS_EXPLICIT_TEMPLATE_INSTANTIATION */
}