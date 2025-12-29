#include <cstring>
#include <stdlib.h>
#include <lime/lime.h>
#include <clime/clime.h>

#ifdef __cplusplus
extern "C" {
#endif

LimeHttpResponse lime_http_response_create_from_body(const char* body) {
  return new lime::http::Response { body };
}

LimeHttpResponse lime_http_response_create_from_status_code(const LimeHttpStatusCode status_code) {
  return new lime::http::Response { static_cast<lime::http::StatusCode>(status_code) };
}

LimeHttpResponse lime_http_response_create_from_body_and_status_code(const char* body, const LimeHttpStatusCode status_code) {
  return new lime::http::Response { body, static_cast<lime::http::StatusCode>(status_code) };
}

void lime_http_response_append_header(LimeHttpResponse _resp, const char* id, const char* value) {
  auto resp = (lime::http::Response*)_resp;
  resp->append_header(id, value);
}

void lime_http_response_set_body(LimeHttpResponse _resp, const char* body) {
  auto resp = (lime::http::Response*)_resp;
  resp->set_body(body);
}

void lime_http_response_set_status_code(LimeHttpResponse _resp, const LimeHttpStatusCode status_code) {
  auto resp = (lime::http::Response*)_resp;
  resp->set_code(static_cast<lime::http::StatusCode>(status_code));
}

char* lime_http_response_to_string(LimeHttpResponse _resp) {
  auto resp = (lime::http::Response*)_resp;
  const std::string str = resp->to_string();
  char* cstr = (char*)malloc((str.length() + 1) * sizeof(char));
  strcpy(cstr, str.c_str());
  return cstr;
}

void lime_http_response_destroy(LimeHttpResponse _resp) {
  auto resp = (lime::http::Response*)_resp;
  delete resp;
}

#ifdef __cplusplus
}
#endif
