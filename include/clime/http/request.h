#ifndef CLIME_HTTP_REQUEST_H
#define CLIME_HTTP_REQUEST_H

#include <stdbool.h>

#include "methods.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct LimeHttpRequest LimeHttpRequest;

LimeHttpRequest* LimeHttpRequestCreate(void);
LimeHttpMethod LimeHttpRequestGetMethod(const LimeHttpRequest*);
const char* LimeHttpRequestGetUrl(const LimeHttpRequest*);
bool LimeHttpRequestHasParam(const LimeHttpRequest*, const char* key);
const char* LimeHttpRequestGetParam(const LimeHttpRequest*, const char* key);
bool LimeHttpRequestHasHeader(const LimeHttpRequest*, const char* key);
const char* LimeHttpRequestGetHeader(const LimeHttpRequest*, const char* key);
const char* LimeHttpRequestGetBody(const LimeHttpRequest*);
void LimeHttpRequestDestroy(LimeHttpRequest*);

#ifdef __cplusplus
}
#endif

#endif // CLIME_HTTP_REQUEST_H
