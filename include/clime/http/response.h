#ifndef CLIME_HTTP_RESPONSE_H
#define CLIME_HTTP_RESPONSE_H

#include "status.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct LimeHttpResponse LimeHttpResponse;

LimeHttpResponse* LimeHttpResponseCreateFromBody(const char* body);
LimeHttpResponse* LimeHttpResponseCreateFromStatusCode(const LimeHttpStatusCode status_code);
LimeHttpResponse* LimeHttpResponseCreateFromBodyAndStatusCode(const char*, const LimeHttpStatusCode status_code);
void LimeHttpResponseAppendHeader(LimeHttpResponse*, const char* id, const char* value);
void LimeHttpResponseSetBody(LimeHttpResponse*, const char* body);
void LimeHttpResponseSetStatusCode(LimeHttpResponse*, const LimeHttpStatusCode);
char* LimeHttpResponseToString(LimeHttpResponse*);
void LimeHttpResponseDestroy(LimeHttpResponse*);

#ifdef __cplusplus
}
#endif

#endif // CLIME_HTTP_RESPONSE_H
