#ifndef CLIME_HTTP_RESPONSE_H
#define CLIME_HTTP_RESPONSE_H

#include "status.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef void* LimeHttpResponse;

LimeHttpResponse lime_http_response_create_from_body(const char* body);
LimeHttpResponse lime_http_response_create_from_status_code(const LimeHttpStatusCode status_code);
LimeHttpResponse lime_http_response_create_from_body_and_status_code(const char*, const LimeHttpStatusCode status_code);
void lime_http_response_append_header(LimeHttpResponse, const char* id, const char* value);
void lime_http_response_set_body(LimeHttpResponse, const char* body);
void lime_http_response_set_status_code(LimeHttpResponse, const LimeHttpStatusCode);
char* lime_http_response_to_string(LimeHttpResponse);
void lime_http_response_destroy(LimeHttpResponse);

#ifdef __cplusplus
}
#endif

#endif // CLIME_HTTP_RESPONSE_H
