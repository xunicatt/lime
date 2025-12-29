#ifndef CLIME_HTTP_SERVER_H
#define CLIME_HTTP_SERVER_H

#include <stddef.h>
#include <stdint.h>

#include "router.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef void* LimeHttpServer;

LimeHttpServer lime_http_server_create(LimeHttpRouter);
LimeHttpServer lime_http_server_create_with_workers(LimeHttpRouter, const size_t);
void lime_http_server_set_port(LimeHttpServer, const uint16_t);
uint16_t lime_http_server_get_port(LimeHttpServer);
void lime_http_server_set_addrs(LimeHttpServer, const char*);
const char* lime_http_server_get_addrs(LimeHttpServer);
int lime_http_server_run(LimeHttpServer);
void lime_http_server_destroy(LimeHttpServer);

#ifdef __cplusplus
}
#endif

#endif // CLIME_HTTP_ROUTER_H
