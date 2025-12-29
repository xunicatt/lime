#include <lime/lime.h>
#include <clime/clime.h>

#ifdef __cplusplus
extern "C" {
#endif

LimeHttpMethod lime_http_request_get_method(LimeHttpRequest _req) {
  auto req = (lime::http::Request*)_req;
  return static_cast<LimeHttpMethod>(req->method);
}

const char* lime_http_request_get_url(LimeHttpRequest _req) {
  auto req = (lime::http::Request*)_req;
  return req->url.c_str();
}

bool lime_http_request_has_param(LimeHttpRequest _req, const char* key) {
  auto req = (lime::http::Request*)_req;
  return req->params.contains(key);
}

const char* lime_http_request_get_param(LimeHttpRequest _req, const char* key) {
  if (!lime_http_request_has_param(_req, key)) {
    return NULL;
  }

  auto req = (lime::http::Request*)_req;
  return req->params.at(key).c_str();
}

bool lime_http_request_has_header(LimeHttpRequest _req, const char* key) {
  auto req = (lime::http::Request*)_req;
  return req->header.contains(key);
}

const char* lime_http_request_get_header(LimeHttpRequest _req, const char* key) {
  if (!lime_http_request_has_param(_req, key)) {
      return NULL;
    }

  auto req = (lime::http::Request*)_req;
    return req->header.at(key).c_str();
}

const char* lime_http_request_get_body(LimeHttpRequest _req) {
  auto req = (lime::http::Request*)_req;
  return req->body.c_str();
}

#ifdef __cplusplus
}
#endif
