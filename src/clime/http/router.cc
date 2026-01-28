#include <cstdlib>
#include <lime/lime.h>
#include <clime/clime.h>
#include <clime/http/defs.h>

#ifdef __cplusplus
extern "C" {
#endif

LimeHttpRouter* LimeHttpRouterCreate(void) {
  LimeHttpRouter* router = (LimeHttpRouter*)malloc(sizeof(*router));
  router->handle = new lime::http::Router{};
  return router;
}

void LimeHttpRouterAdd(
  LimeHttpRouter* router,
  const char* path,
  const LimeHttpMethod method,
  const LimeHttpRouteFunc handler
) {
  router->handle->add(
    path,
    static_cast<lime::http::Method>(method),
    [handler](const lime::http::Request& _req) {
      LimeHttpRequest* request = (LimeHttpRequest*)malloc(sizeof(*request));
      request->handle = &_req;
      LimeHttpResponse* response = handler(request);
      lime::http::Response _resp = *response->handle;
      LimeHttpResponseDestroy(response);
      free(request);
      return _resp;
    }
  );
}

void LimeHttpRouterAddRegex(
  LimeHttpRouter* router,
  const char* path,
  const LimeHttpMethod method,
  const LimeHttpRouteFunc handler
) {
  router->handle->add_regex(
    path,
    static_cast<lime::http::Method>(method),
    [handler](const lime::http::Request& _req) {
      LimeHttpRequest* request = (LimeHttpRequest*)malloc(sizeof(*request));
      request->handle = &_req;
      LimeHttpResponse* response = handler(request);
      lime::http::Response _resp = *response->handle;
      LimeHttpResponseDestroy(response);
      free(request);
      return _resp;
    }
  );
}

void LimeHttpRouterDestroy(LimeHttpRouter* router) {
  delete router->handle;
  free(router);
}

#ifdef __cplusplus
}
#endif
