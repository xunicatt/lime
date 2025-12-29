#ifndef CLIME_HTTP_REQUEST_H
#define CLIME_HTTP_REQUEST_H

#include <stdbool.h>

#include "methods.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef void* LimeHttpRequest;

LimeHttpMethod lime_http_request_get_method(LimeHttpRequest);
const char* lime_http_request_get_url(LimeHttpRequest);
bool lime_http_request_has_param(LimeHttpRequest, const char* key);
const char* lime_http_request_get_param(LimeHttpRequest, const char* key);
bool lime_http_request_has_header(LimeHttpRequest, const char* key);
const char* lime_http_request_get_header(LimeHttpRequest, const char* key);
const char* lime_http_request_get_body(LimeHttpRequest);

#ifdef __cplusplus
}
#endif

#endif // CLIME_HTTP_REQUEST_H
