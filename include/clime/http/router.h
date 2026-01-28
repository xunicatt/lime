#ifndef CLIME_HTTP_ROUTER_H
#define CLIME_HTTP_ROUTER_H

#include "response.h"
#include "request.h"
#include "methods.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef LimeHttpResponse*(*LimeHttpRouteFunc)(const LimeHttpRequest*);

typedef struct LimeHttpRouter LimeHttpRouter;

LimeHttpRouter* LimeHttpRouterCreate(void);
void LimeHttpRouterAdd(LimeHttpRouter*, const char* path, const LimeHttpMethod method, const LimeHttpRouteFunc handler);
void LimeHttpRouterAddRegex(LimeHttpRouter*, const char* path, const LimeHttpMethod method, const LimeHttpRouteFunc handler);
void LimeHttpRouterDestroy(LimeHttpRouter*);

#ifdef __cplusplus
}
#endif

#endif // CLIME_HTTP_ROUTER_H
