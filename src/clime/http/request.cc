#include <lime/lime.h>
#include <clime/clime.h>
#include <clime/http/defs.h>

#ifdef __cplusplus
extern "C" {
#endif

LimeHttpRequest* LimeHttpRequestCreate(void) {
  LimeHttpRequest* req = (LimeHttpRequest*)malloc(sizeof(*req));
  req->handle = new lime::http::Request{};
  return req;
}

LimeHttpMethod LimeHttpRequestGetMethod(const LimeHttpRequest* req) {
  return static_cast<LimeHttpMethod>(req->handle->method);
}

const char* LimeHttpRequestGetUrl(const LimeHttpRequest* req) {
  return req->handle->url.c_str();
}

bool LimeHttpRequestHasParam(const LimeHttpRequest* req, const char* key) {
  return req->handle->params.contains(key);
}

const char* LimeHttpRequestGetParam(const LimeHttpRequest* req, const char* key) {
  if (!LimeHttpRequestHasParam(req, key)) {
    return NULL;
  }

  return req->handle->params.at(key).c_str();
}

bool LimeHttpRequestHasHeader(const LimeHttpRequest* req, const char* key) {
  return req->handle->header.contains(key);
}

const char* LimeHttpRequestGetHeader(const LimeHttpRequest* req, const char* key) {
  if (!LimeHttpRequestHasParam(req, key)) {
      return NULL;
  }

  return req->handle->header.at(key).c_str();
}

const char* LimeHttpRequestGetBody(const LimeHttpRequest* req) {
  return req->handle->body.c_str();
}

void LimeHttpRequestDestroy(LimeHttpRequest* req) {
  delete req->handle;
  free(req);
}

#ifdef __cplusplus
}
#endif
