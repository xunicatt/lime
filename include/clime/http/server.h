#ifndef CLIME_HTTP_SERVER_H
#define CLIME_HTTP_SERVER_H

#include <stddef.h>
#include <stdint.h>

#include "router.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct LimeHttpServer LimeHttpServer;

LimeHttpServer* LimeHttpServerCreate(LimeHttpRouter*);
LimeHttpServer* LimeHttpServerCreateWithWorkers(LimeHttpRouter*, const size_t workers);
void LimeHttpServerSetPort(LimeHttpServer*, const uint16_t port);
uint16_t LimeHttpServerGetPort(LimeHttpServer*);
void LimeHttpServerSetAddrs(LimeHttpServer*, const char* addrs);
const char* LimeHttpServerGetAddrs(LimeHttpServer*);
int LimeHttpServerRun(LimeHttpServer*);
void LimeHttpServerDestroy(LimeHttpServer*);

#ifdef __cplusplus
}
#endif

#endif // CLIME_HTTP_ROUTER_H
