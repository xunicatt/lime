#ifndef CLIME_HTTP_METHODS_H
#define CLIME_HTTP_METHODS_H

#ifdef __cplusplus
extern "C" {
#endif

typedef enum {
  LIME_HTTP_METHOD_GET = 0,
  LIME_HTTP_METHOD_POST,
  LIME_HTTP_METHOD_PUT,
  LIME_HTTP_METHOD_DELETE,
} LimeHttpMethod ;

const char* lime_http_method_to_string(const LimeHttpMethod);

#ifdef __cplusplus
}
#endif

#endif // CLIME_HTTP_METHODS_H
