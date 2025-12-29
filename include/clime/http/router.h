#ifndef CLIME_HTTP_ROUTER_H
#define CLIME_HTTP_ROUTER_H

#include "response.h"
#include "request.h"
#include "methods.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef LimeHttpResponse(*LimeHttpRouteFunc)(const LimeHttpRequest);

typedef void* LimeHttpRouter;

LimeHttpRouter lime_http_router_create(void);
void lime_http_router_add(LimeHttpRouter, const char* path, const LimeHttpMethod method, const LimeHttpRouteFunc handler);
void lime_http_router_add_regex(LimeHttpRouter, const char* path, const LimeHttpMethod method, const LimeHttpRouteFunc handler);
void lime_http_router_destroy(LimeHttpRouter);

#ifdef __cplusplus
}
#endif

#endif // CLIME_HTTP_ROUTER_H
