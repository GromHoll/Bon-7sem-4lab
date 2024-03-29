/*
 * Please do not edit this file.
 * It was generated using rpcgen.
 */

#ifndef _PINGER_H_RPCGEN
#define _PINGER_H_RPCGEN

#include <rpc/rpc.h>


#ifdef __cplusplus
extern "C" {
#endif


enum hostStateOptions {
	SLEEP = 0,
	AVAILIBLE = 1,
};
typedef enum hostStateOptions hostStateOptions;

typedef hostStateOptions hostState;

typedef long timeout;

typedef char hostName[16];

struct hostInfo {
	hostName host;
	timeout duration;
};
typedef struct hostInfo hostInfo;

struct hostStatus {
	hostInfo host;
	hostState status;
};
typedef struct hostStatus hostStatus;

typedef struct {
	u_int hostsList_len;
	hostStatus *hostsList_val;
} hostsList;
#define STANDART_TIMEOUT 60
#define MANUAL_FORCE_TIMEOUT 0

#define PINGER 200000
#define PINGER_VERS_1 1

#if defined(__STDC__) || defined(__cplusplus)
#define getHostState 0
extern  hostStatus * gethoststate_1(char *, CLIENT *);
extern  hostStatus * gethoststate_1_svc(char *, struct svc_req *);
#define getAllHostStates 1
extern  hostsList * getallhoststates_1(void *, CLIENT *);
extern  hostsList * getallhoststates_1_svc(void *, struct svc_req *);
#define forcePingHost 2
extern  hostStatus * forcepinghost_1(char *, CLIENT *);
extern  hostStatus * forcepinghost_1_svc(char *, struct svc_req *);
#define forcePingAllHosts 3
extern  hostsList * forcepingallhosts_1(void *, CLIENT *);
extern  hostsList * forcepingallhosts_1_svc(void *, struct svc_req *);
#define setHostTimeout 4
extern  void * sethosttimeout_1(hostInfo *, CLIENT *);
extern  void * sethosttimeout_1_svc(hostInfo *, struct svc_req *);
#define setGlobalTimeout 5
extern  void * setglobaltimeout_1(timeout *, CLIENT *);
extern  void * setglobaltimeout_1_svc(timeout *, struct svc_req *);
#define addHost 6
extern  void * addhost_1(hostInfo *, CLIENT *);
extern  void * addhost_1_svc(hostInfo *, struct svc_req *);
#define remoteHost 7
extern  void * remotehost_1(char *, CLIENT *);
extern  void * remotehost_1_svc(char *, struct svc_req *);
extern int pinger_1_freeresult (SVCXPRT *, xdrproc_t, caddr_t);

#else /* K&R C */
#define getHostState 0
extern  hostStatus * gethoststate_1();
extern  hostStatus * gethoststate_1_svc();
#define getAllHostStates 1
extern  hostsList * getallhoststates_1();
extern  hostsList * getallhoststates_1_svc();
#define forcePingHost 2
extern  hostStatus * forcepinghost_1();
extern  hostStatus * forcepinghost_1_svc();
#define forcePingAllHosts 3
extern  hostsList * forcepingallhosts_1();
extern  hostsList * forcepingallhosts_1_svc();
#define setHostTimeout 4
extern  void * sethosttimeout_1();
extern  void * sethosttimeout_1_svc();
#define setGlobalTimeout 5
extern  void * setglobaltimeout_1();
extern  void * setglobaltimeout_1_svc();
#define addHost 6
extern  void * addhost_1();
extern  void * addhost_1_svc();
#define remoteHost 7
extern  void * remotehost_1();
extern  void * remotehost_1_svc();
extern int pinger_1_freeresult ();
#endif /* K&R C */

/* the xdr functions */

#if defined(__STDC__) || defined(__cplusplus)
extern  bool_t xdr_hostStateOptions (XDR *, hostStateOptions*);
extern  bool_t xdr_hostState (XDR *, hostState*);
extern  bool_t xdr_timeout (XDR *, timeout*);
extern  bool_t xdr_hostName (XDR *, hostName);
extern  bool_t xdr_hostInfo (XDR *, hostInfo*);
extern  bool_t xdr_hostStatus (XDR *, hostStatus*);
extern  bool_t xdr_hostsList (XDR *, hostsList*);

#else /* K&R C */
extern bool_t xdr_hostStateOptions ();
extern bool_t xdr_hostState ();
extern bool_t xdr_timeout ();
extern bool_t xdr_hostName ();
extern bool_t xdr_hostInfo ();
extern bool_t xdr_hostStatus ();
extern bool_t xdr_hostsList ();

#endif /* K&R C */

#ifdef __cplusplus
}
#endif

#endif /* !_PINGER_H_RPCGEN */
