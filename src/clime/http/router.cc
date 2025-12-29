#include <lime/lime.h>
#include <clime/clime.h>

#ifdef __cplusplus
extern "C" {
#endif

LimeHttpRouter lime_http_router_create(void) {
  return new lime::http::Router {};
}

void lime_http_router_add(LimeHttpRouter _router, const char* path, const LimeHttpMethod method, const LimeHttpRouteFunc handler) {
  auto router = (lime::http::Router*)_router;
  router->add(path, static_cast<lime::http::Method>(method), [handler](const lime::http::Request& req) {
    LimeHttpResponse _resp = handler((LimeHttpRequest*)&req);
    auto resp_ptr = (lime::http::Response*)_resp;
    auto resp = std::move(*resp_ptr);
    delete resp_ptr;
    return resp;
  });
}

void lime_http_router_add_regex(LimeHttpRouter _router, const char* path, const LimeHttpMethod method, const LimeHttpRouteFunc handler) {
  auto router = (lime::http::Router*)_router;
  router->add_regex(path, static_cast<lime::http::Method>(method), [handler](const lime::http::Request& req) {
    LimeHttpResponse _resp = handler((LimeHttpRequest*)&req);
    auto resp_ptr = (lime::http::Response*)_resp;
    auto resp = std::move(*resp_ptr);
    delete resp_ptr;
    return resp;
  });
}

void lime_http_router_destroy(LimeHttpRouter _router) {
  auto router = (lime::http::Router*)_router;
  delete router;
}

#ifdef __cplusplus
}
#endif
