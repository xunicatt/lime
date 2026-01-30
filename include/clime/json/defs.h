#ifndef CLIME_JSON_DEFS_H
#define CLIME_JSON_DEFS_H

#include <lime/lime.h>

#ifdef __cplusplus
extern "C" {
#endif

struct LimeJsonNodeArray {
  lime::json::Array* handle;
};

struct LimeJsonNodeObject {
  lime::json::Object* handle;
};

struct LimeJsonNode {
  lime::json::Node* handle;
};

#ifdef __cplusplus
}
#endif

#endif // CLIME_JSON_DEFS_H
