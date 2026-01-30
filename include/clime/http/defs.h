#ifndef CLIME_HTTP_DEFS_H
#define CLIME_HTTP_DEFS_H

#include <lime/lime.h>

#ifdef __cplusplus
extern "C" {
#endif

  struct LimeHttpRequest {
    const lime::http::Request* handle;
  };

  struct LimeHttpResponse {
    lime::http::Response* handle;
  };

  struct LimeHttpRouter {
    lime::http::Router* handle;
  };

  struct LimeHttpServer {
    lime::http::Server* handle;
  };

#ifdef __cplusplus
}
#endif

#endif // LIME_HTTP_DEFS_H
