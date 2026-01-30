#ifndef CLIME_JSON_H
#define CLIME_JSON_H

#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef enum {
  LIME_JSON_NODE_TYPE_NULL = 0,
  LIME_JSON_NODE_TYPE_INT,
  LIME_JSON_NODE_TYPE_FLOAT,
  LIME_JSON_NODE_TYPE_BOOL,
  LIME_JSON_NODE_TYPE_STRING,
  LIME_JSON_NODE_TYPE_ARRAY,
  LIME_JSON_NODE_TYPE_OBJECT,
} LimeJsonNodeType;

typedef struct LimeJsonNodeArray LimeJsonNodeArray;
typedef struct LimeJsonNodeObject LimeJsonNodeObject;
typedef struct LimeJsonNode LimeJsonNode;

// LimeJsonNodeCreateFrom<Type> function returns a heap
// allocated object that must be freed using LimeJsonNodeDestroy()
// function if the object is not anchored to another parent object
// like LimeJsonNodeArray/LimeJsonNodeObject

LimeJsonNode* LimeJsonNodeCreateFromNull(void);
LimeJsonNode* LimeJsonNodeCreateFromInt(const int);
LimeJsonNode* LimeJsonNodeCreateFromInt64(const int64_t);
LimeJsonNode* LimeJsonNodeCreateFromFloat(const double);
LimeJsonNode* LimeJsonNodeCreateFromBool(const bool);
LimeJsonNode* LimeJsonNodeCreateFromString(const char*);

// LimeJsonNodeArray value is moved and owned, no need to call
// LimeJsonNodeArrayDestory
LimeJsonNode* LimeJsonNodeCreateFromArray(LimeJsonNodeArray*);

// LimeJsonNodeObject value is moved and owned, no need to call
// LimeJsonNodeObjectDestory
LimeJsonNode* LimeJsonNodeCreateFromObject(LimeJsonNodeObject*);

LimeJsonNodeType LimeJsonNodeGetType(LimeJsonNode*);

// Regardless of the type conversion user must
// call LimeJsonNodeDestroy. These conversions
// other than primitive types are allocated on
// the heap and created by copying the underneath values.
// So even after conversion the LimeJsonNode is still valid.

int64_t LimeJsonNodeAsInt64(LimeJsonNode*);
double LimeJsonNodeAsFloat(LimeJsonNode*);
bool LimeJsonNodeAsBool(LimeJsonNode*);

// free() must be called on the returned char*
// after use
char* LimeJsonNodeAsString(LimeJsonNode*);

// LimeJsonNodeArrayDestroy() must be called on the returned
// pointer after use.
LimeJsonNodeArray* LimeJsonNodeAsArray(LimeJsonNode*);

// LimeJsonNodeObjectDestroy() must be called on the returned
// pointer after use.
LimeJsonNodeObject* LimeJsonNodeAsObject(LimeJsonNode*);

// free() must be called on the returned char*
// after use
char* LimeJsonNodeToString(LimeJsonNode*);

// Deallocates the node with its childrens
void LimeJsonNodeDestroy(LimeJsonNode*);

LimeJsonNodeArray* LimeJsonNodeArrayCreate(void);

// LimeJsonNode value is moved and owned by the array, no need
// to call LimeJsonNodeDestroy
void LimeJsonNodeArrayPush(LimeJsonNodeArray*, LimeJsonNode*);

void LimeJsonNodeArrayPop(LimeJsonNodeArray*);

// If the index is out of bound, NULL will be returned.
// The returned value is heap allocated, the user must call
// LimeJsonNodeDestroy() after use to deallocate the object
LimeJsonNode* LimeJsonNodeArrayAt(LimeJsonNodeArray*, size_t);
size_t LimeJsonNodeArrayLength(LimeJsonNodeArray*);
void LimeJsonNodeArrayDestroy(LimeJsonNodeArray*);

LimeJsonNodeObject* LimeJsonNodeObjectCreate(void);

// LimeJsonNode value is moved and owned by the array, no need
// to call LimeJsonNodeDestroy
void LimeJsonNodeObjectInsert(LimeJsonNodeObject*, const char* key, LimeJsonNode*);

void LimeJsonNodeObjectRemove(LimeJsonNodeObject*, const char* key);

// If the key is not found, NULL will be returned.
// The returned value is heap allocated, the user must call
// LimeJsonNodeDestroy() after use to deallocate the object
LimeJsonNode* LimeJsonNodeObjectAt(LimeJsonNodeObject*, const char* key);

size_t LimeJsonNodeObjectLength(LimeJsonNodeObject*);
void LimeJsonNodeObjectDestroy(LimeJsonNodeObject*);

// free() must be called on the returned char*
// after use
char* LimeJsonEncode(LimeJsonNode* node);

// NULL will be returned if any kind of parsing error occurs. In
// such cases the error (passed by parameter) will store the heap allocated
// string that contains more info about the cause of the error. User must
// deallocate the error string after use.
//
// LimeJsonNodeDestroy() must be called on the returned pointer after use
//
// Usage:
//      char* error;
//      LimeJsonNode* node = LimeJsonDecode(source, &error);
//      if (node == NULL) {
//        // handle the error
//        // print the error string
//        printf(...., error);
//
//        free(error);
//
//        // rest of the code
//      }
LimeJsonNode* LimeJsonDecode(const char* source, char** error);

#ifdef __cplusplus
}
#endif

#endif // CLIME_JSON_H
