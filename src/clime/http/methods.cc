#include <clime/clime.h>

#ifdef __cplusplus
extern "C" {
#endif

const char* LimeHttpMethodToString(const LimeHttpMethod m) {
  switch (m) {
    case LIME_HTTP_METHOD_GET: return "GET";
    case LIME_HTTP_METHOD_POST: return "POST";
    case LIME_HTTP_METHOD_PUT: return "PUT";
    case LIME_HTTP_METHOD_DELETE: return "DELETE";
    default: return "";
  }
}

#ifdef __cplusplus
}
#endif
