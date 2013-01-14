#include "pinger.h"

#include <string.h>
#include <iostream>

using namespace std;

const string GET_STATUS_FLAG     = "-s";
const string GET_ALL_STATUS_FLAG = "-sa";
const string FORCE_FLAG          = "-f";
const string FORCE_ALL_FLAG      = "-fa";
const string TIMEOUT_FLAG        = "-t";
const string TIMEOUT_ALL_FLAG    = "-ta";
const string ADD_HOST_FLAG       = "-a";
const string REMOVE_HOST_FLAG    = "-r";


void f_getStatusForHost(char * server, char * host, bool force) {

	CLIENT *client = clnt_create(server, PINGER, PINGER_VERS_1, "udp");

	if(client != NULL) {
		
		hostStatus *result;

		if(force) {
			result = forcepinghost_1(host, client);
		} else {
			result = gethoststate_1(host, client);
		}
		
		if(result != NULL) {
			cout << "Host \"" << result->host.host << "\" status: ";

			if(result->status == SLEEP)
				cout << "sleep." << endl;
			else if(result->status == AVAILIBLE)
				cout << "availible." << endl;
			else
				cout << "unknown." << endl;
		} else {
			cout << "Error." << endl;
		}

		clnt_destroy(client);
	} else {
		cout << "Can't connect to server." << endl;
	}
}

void f_getStatusForAll(char * server, bool force) {

	CLIENT *client = clnt_create(server, PINGER, PINGER_VERS_1, "udp");

	if(client != NULL) {
		
		hostsList *list;

		if(force) {
			list = forcepingallhosts_1(NULL, client);
		} else {
			list = getallhoststates_1(NULL, client);
		}
		
		if(list != NULL) {
			
			if(list->hostsList_len == 0) {
				cout << "Host list is empty." << endl;
				return;
			}
	
			hostStatus *h = list->hostsList_val;

			for(int i = 0; i < list->hostsList_len; i++) {				
				cout << "Host " << h->host.host << " status: ";

				if(h->status == SLEEP)
					cout << "sleep." << endl;
				else if(h->status == AVAILIBLE)
					cout << "availible." << endl;
				else
					cout << "unknown." << endl;
				
				h++;
			}
		} else {
			cout << "Error." << endl;
		}

		clnt_destroy(client);
	} else {
		cout << "Can't connect to server." << endl;
	}
}

void f_setTimeoutForHost(char * server, char * host, timeout duration) {

	CLIENT *client = clnt_create(server, PINGER, PINGER_VERS_1, "udp");

	if(client != NULL) {

		hostInfo h;
		h.duration = duration;
		strcpy(h.host, host);

		sethosttimeout_1(&h, client);

		clnt_destroy(client);
	} else {
		cout << "Can't connect to server." << endl;
	}
}

void f_setTimeoutForAll(char * server, timeout duration) {

	CLIENT *client = clnt_create(server, PINGER, PINGER_VERS_1, "udp");

	if(client != NULL) {

		setglobaltimeout_1(&duration, client);

		clnt_destroy(client);
	} else {
		cout << "Can't connect to server." << endl;
	}
}

void f_addHost(char * server, char * host, timeout duration = STANDART_TIMEOUT) {

	CLIENT *client = clnt_create(server, PINGER, PINGER_VERS_1, "udp");

	if(client != NULL) {

		hostInfo h;
		h.duration = duration;
		strcpy(h.host, host);

		addhost_1(&h, client);

		clnt_destroy(client);
	} else {
		cout << "Can't connect to server." << endl;
	}
}

void f_removeHost(char * server, char * host) {

	CLIENT *client = clnt_create(server, PINGER, PINGER_VERS_1, "udp");

	if(client != NULL) {

		remotehost_1(host, client);

		clnt_destroy(client);
	} else {
		cout << "Can't connect to server." << endl;
	}
}

void showHelp(char * progName) {

	cout << endl << "Pinger help:" << endl;
	cout << "Use: " << progName << " <server> <cmd> <args>" << endl << endl;

	cout << "Command list:" << endl;

	cout << "-s <host>" << endl; 
	cout << "       get host status" << endl << endl;

	cout << "-sa    get all hosts statuses" << endl << endl;

	cout << "-f <host>" << endl; 
	cout << "       force host ping and get status" << endl << endl;

	cout << "-fa    force all hosts ping and get statuses" << endl << endl;

	cout << "-t <host> <timeout>"  << endl;
	cout << "       set timeout for host (in sec)" << endl << endl;

	cout << "-ta <timeout>"  << endl;
	cout << "       set timeout for all hosts (in sec)" << endl << endl;

	cout << "-a <host> [timeout]"  << endl;
	cout << "       add host to server (with timeout (in sec) - optional)" << endl << endl;

	cout << "-r <host>"  << endl;
	cout << "       remove host from server" << endl;
}

void showIncorrectArgError(char * progName) {
	cout << "Incorrect arguments.\nUse " << progName << " for look help." << endl;
}

int main(int argc, char* argv[]) {
	
	if(argc == 1) {
		showHelp(argv[0]);

	} else {
		if(argc == 3) {

			if(GET_ALL_STATUS_FLAG.compare(argv[2]) == 0) {
				f_getStatusForAll(argv[1], false);

			} else if(FORCE_ALL_FLAG.compare(argv[2]) == 0) {
				f_getStatusForAll(argv[1], true);

			} else {
				showIncorrectArgError(argv[0]);
			}
		} else if(argc == 4) {

			if(GET_STATUS_FLAG.compare(argv[2]) == 0) {
				f_getStatusForHost(argv[1], argv[3], false);

			} else if(FORCE_FLAG.compare(argv[2]) == 0) {
				f_getStatusForHost(argv[1], argv[3], true);

			} else if(TIMEOUT_ALL_FLAG.compare(argv[2]) == 0) {
				f_setTimeoutForAll(argv[1], atoi(argv[3]));

			} else if(ADD_HOST_FLAG.compare(argv[2]) == 0) {
				f_addHost(argv[1], argv[3]);

			} else if(REMOVE_HOST_FLAG.compare(argv[2]) == 0) {
				f_removeHost(argv[1], argv[3]);

			} else {
				showIncorrectArgError(argv[0]);
			}			
		} else if(argc == 5) {

			if(ADD_HOST_FLAG.compare(argv[2]) == 0) {
				f_addHost(argv[1], argv[3], atoi(argv[4]));

			} else if(TIMEOUT_FLAG.compare(argv[2]) == 0) {
				f_setTimeoutForHost(argv[1], argv[3], atoi(argv[4]));

			} else {
				showIncorrectArgError(argv[0]);
			}
		} else {
			showIncorrectArgError(argv[0]);
		}
	}
	return 0;
}
