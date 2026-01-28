#include <cstdlib>
#include <cstring>
#include <stdlib.h>
#include <lime/lime.h>
#include <clime/clime.h>
#include <clime/http/defs.h>

#ifdef __cplusplus
extern "C" {
#endif

namespace http = lime::http;

LimeHttpResponse* LimeHttpResponseCreateFromBody(const char* body) {
  LimeHttpResponse* resp = (LimeHttpResponse*)malloc(sizeof(*resp));
  resp->handle = new http::Response { body };
  return resp;
}

LimeHttpResponse* LimeHttpResponseCreateFromStatusCode(
  const LimeHttpStatusCode status_code
) {
  LimeHttpResponse* resp = (LimeHttpResponse*)malloc(sizeof(*resp));
  resp->handle = new http::Response {
    static_cast<http::StatusCode>(status_code)
  };
  return resp;
}

LimeHttpResponse* LimeHttpResponseCreateFromBodyAndStatusCode(
  const char* body,
  const LimeHttpStatusCode status_code
) {
  LimeHttpResponse* resp = (LimeHttpResponse*)malloc(sizeof(*resp));
  resp->handle = new http::Response {
    body,
    static_cast<http::StatusCode>(status_code)
  };
  return resp;
}

void LimeHttpResponseAppendHeader(
  LimeHttpResponse* resp,
  const char* id,
  const char* value
) {
  resp->handle->append_header(id, value);
}

void LimeHttpResponseSetBody(LimeHttpResponse* resp, const char* body) {
  resp->handle->set_body(body);
}

void LimeHttpResponseSetStatusCode(
  LimeHttpResponse* resp,
  const LimeHttpStatusCode status_code
) {
  resp->handle->set_code(
    static_cast<http::StatusCode>(status_code)
  );
}

char* LimeHttpResponseToString(LimeHttpResponse* resp) {
  const std::string str = resp->handle->to_string();
  char* cstr = (char*)malloc((str.length() + 1) * sizeof(char));
  strcpy(cstr, str.c_str());
  return cstr;
}

void LimeHttpResponseDestroy(LimeHttpResponse* resp) {
  delete resp->handle;
  free(resp);
}

#ifdef __cplusplus
}
#endif
