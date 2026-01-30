#include <clime/json/defs.h>
#include <clime/clime.h>
#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <cstring>
#include <lime/lime.h>

namespace json = lime::json;

#ifdef __cplusplus
extern "C" {
#endif

LimeJsonNode* LimeJsonNodeCreateFromNull(void) {
  LimeJsonNode* node = (LimeJsonNode*)malloc(sizeof(*node));
  node->handle = new json::Node{};
  return node;
}

LimeJsonNode* LimeJsonNodeCreateFromInt(const int value) {
  LimeJsonNode* node = (LimeJsonNode*)malloc(sizeof(*node));
  node->handle = new json::Node{ value };
  return node;
}

LimeJsonNode* LimeJsonNodeCreateFromInt64(const int64_t value) {
  LimeJsonNode* node = (LimeJsonNode*)malloc(sizeof(*node));
  node->handle = new json::Node{ value };
  return node;
}

LimeJsonNode* LimeJsonNodeCreateFromFloat(const double value) {
  LimeJsonNode* node = (LimeJsonNode*)malloc(sizeof(*node));
  node->handle = new json::Node{ value };
  return node;
}

LimeJsonNode* LimeJsonNodeCreateFromBool(const bool value) {
  LimeJsonNode* node = (LimeJsonNode*)malloc(sizeof(*node));
  node->handle = new json::Node{ value };
  return node;
}

LimeJsonNode* LimeJsonNodeCreateFromString(const char* value) {
  LimeJsonNode* node = (LimeJsonNode*)malloc(sizeof(*node));
  node->handle = new json::Node{ value };
  return node;
}

LimeJsonNode* LimeJsonNodeCreateFromArray(LimeJsonNodeArray* value) {
  LimeJsonNode* node = (LimeJsonNode*)malloc(sizeof(*node));
  node->handle = new json::Node{ std::move(*value->handle) };
  LimeJsonNodeArrayDestroy(value);
  return node;
}

LimeJsonNode* LimeJsonNodeCreateFromObject(LimeJsonNodeObject* value) {
  LimeJsonNode* node = (LimeJsonNode*)malloc(sizeof(*node));
  node->handle = new json::Node{ std::move(*value->handle) };
  LimeJsonNodeObjectDestroy(value);
  return node;
}

LimeJsonNodeType LimeJsonNodeGetType(LimeJsonNode* node) {
  return static_cast<LimeJsonNodeType>(node->handle->type());
}

int64_t LimeJsonNodeAsInt64(LimeJsonNode* node) {
  return node->handle->get<int64_t>();
}

double LimeJsonNodeAsFloat(LimeJsonNode* node) {
  return node->handle->get<double>();
}

bool LimeJsonNodeAsBool(LimeJsonNode* node) {
  return node->handle->get<bool>();
}

char* LimeJsonNodeAsString(LimeJsonNode* node) {
  const auto str = node->handle->get<std::string>();
  const char* cstr = str.c_str();
  return strdup(cstr);
}

LimeJsonNodeArray* LimeJsonNodeAsArray(LimeJsonNode* node) {
  LimeJsonNodeArray* array = (LimeJsonNodeArray*)malloc(sizeof(*array));
  array->handle = new json::Array{ node->handle->get<json::Array>() };
  return array;
}

LimeJsonNodeObject* LimeJsonNodeAsObject(LimeJsonNode* node) {
  LimeJsonNodeObject* obj = (LimeJsonNodeObject*)malloc(sizeof(*obj));
  obj->handle = new json::Object{ node->handle->get<json::Object>() };
  return obj;
}

char* LimeJsonNodeToString(LimeJsonNode* node) {
  const auto str = node->handle->to_string();
  const char* cstr = str.c_str();
  return strdup(cstr);
}

void LimeJsonNodeDestroy(LimeJsonNode* node) {
  delete node->handle;
  free(node);
}

LimeJsonNodeArray* LimeJsonNodeArrayCreate(void) {
  LimeJsonNodeArray* array = (LimeJsonNodeArray*)malloc(sizeof(*array));
  array->handle = new json::Array{};
  return array;
}

void LimeJsonNodeArrayPush(LimeJsonNodeArray* array, LimeJsonNode* node) {
  array->handle->emplace_back(std::move(*node->handle));
  LimeJsonNodeDestroy(node);
}

void LimeJsonNodeArrayPop(LimeJsonNodeArray* array) {
  array->handle->pop_back();
}

LimeJsonNode* LimeJsonNodeArrayAt(LimeJsonNodeArray* array, size_t index) {
  if (index >= array->handle->size()) {
    return NULL;
  }

  json::Node node = array->handle->at(index);
  LimeJsonNode* node2 = LimeJsonNodeCreateFromNull();
  *node2->handle = std::move(node);
  return node2;
}

size_t LimeJsonNodeArrayLength(LimeJsonNodeArray* array) {
  return array->handle->size();
}

void LimeJsonNodeArrayDestroy(LimeJsonNodeArray* array) {
  delete array->handle;
  free(array);
}

LimeJsonNodeObject* LimeJsonNodeObjectCreate(void) {
  LimeJsonNodeObject* obj = (LimeJsonNodeObject*)malloc(sizeof(*obj));
  obj->handle = new json::Object{};
  return obj;
}

void LimeJsonNodeObjectInsert(LimeJsonNodeObject* obj, const char* key, LimeJsonNode* value) {
  obj->handle->insert({ key, std::move(*value->handle) });
  LimeJsonNodeDestroy(value);
}

void LimeJsonNodeObjectRemove(LimeJsonNodeObject* obj, const char* key) {
  obj->handle->erase(key);
}

LimeJsonNode* LimeJsonNodeObjectAt(LimeJsonNodeObject* obj, const char* key) {
  if (!obj->handle->contains(key)) {
    return NULL;
  }

  const auto node = obj->handle->at(key);
  LimeJsonNode* node2 = LimeJsonNodeCreateFromNull();
  *node2->handle = std::move(node);
  return node2;
}

size_t LimeJsonNodeObjectLength(LimeJsonNodeObject* node) {
  return node->handle->size();
}

void LimeJsonNodeObjectDestroy(LimeJsonNodeObject* obj) {
  delete obj->handle;
  free(obj);
}

char* LimeJsonEncode(LimeJsonNode* node) {
  return LimeJsonNodeToString(node);
}

LimeJsonNode* LimeJsonDecode(const char* source, char** error) {
  const auto result = json::decode(source);
  if (!result) {
    const auto str = result.error();
    const char* cstr = str.c_str();
    *error = strdup(cstr);
    return NULL;
  }

  LimeJsonNode* node = LimeJsonNodeCreateFromNull();
  *node->handle = std::move(result.value());
  return node;
}

#ifdef __cplusplus
}
#endif
