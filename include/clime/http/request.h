#ifndef CLIME_HTTP_REQUEST_H
#define CLIME_HTTP_REQUEST_H

#include <stdbool.h>

#include "methods.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct LimeHttpRequest LimeHttpRequest;

LimeHttpRequest* LimeHttpRequestCreate(void);
LimeHttpMethod LimeHttpRequestGetMethod(LimeHttpRequest*);
const char* LimeHttpRequestGetUrl(LimeHttpRequest*);
bool LimeHttpRequestHasParam(LimeHttpRequest*, const char* key);
const char* LimeHttpRequestGetParam(LimeHttpRequest*, const char* key);
bool LimeHttpRequestHasHeader(LimeHttpRequest*, const char* key);
const char* LimeHttpRequestGetHeader(LimeHttpRequest*, const char* key);
const char* LimeHttpRequestGetBody(LimeHttpRequest*);
void LimeHttpRequestDestroy(LimeHttpRequest*);

#ifdef __cplusplus
}
#endif

#endif // CLIME_HTTP_REQUEST_H
