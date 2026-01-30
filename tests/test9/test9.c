#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <clime/clime.h>

static int generate_otp(void) {
  // INFO: to validate the output using test
  // the number has to be a static
  return 456123;
}

static LimeHttpResponse* get_otp(const LimeHttpRequest* req) {
  if (!LimeHttpRequestHasParam(req, "name")) {
    return LimeHttpResponseCreateFromStatusCode(
      LIME_HTTP_STATUS_CODE_BADREQUEST
    );
  }

  LimeJsonNodeObject* obj = LimeJsonNodeObjectCreate();
  LimeJsonNode* name =  LimeJsonNodeCreateFromString(
    LimeHttpRequestGetParam(req, "name")
  );

  // obj now owns name, no need to destroy name
  LimeJsonNodeObjectInsert(obj, "name", name);
  LimeJsonNodeObjectInsert(obj, "otp", LimeJsonNodeCreateFromInt(generate_otp()));

  // root now owns obj, no need to destroy obj
  LimeJsonNode* root = LimeJsonNodeCreateFromObject(obj);
  char* raw = LimeJsonEncode(root);
  LimeHttpResponse* resp = LimeHttpResponseCreateFromBody(raw);

  free(raw);
  // destroying the root destroys all the children
  LimeJsonNodeDestroy(root);

  return resp;
}

static LimeHttpResponse* validate_otp(const LimeHttpRequest* req) {
  char* error;

  LimeJsonNode* root = LimeJsonDecode(
    LimeHttpRequestGetBody(req),
    &error
  );

  if (root == NULL) {
    LimeHttpResponse* resp = LimeHttpResponseCreateFromBodyAndStatusCode(
      error,
      LIME_HTTP_STATUS_CODE_BADREQUEST
    );
    free(error);
    return resp;
  }

  // creates a new copy, we much destroy it later
  LimeJsonNodeObject* obj = LimeJsonNodeAsObject(root);
  LimeJsonNode* name_node = LimeJsonNodeObjectAt(obj, "name");
  if (!name_node ||
        (name_node && LimeJsonNodeGetType(name_node) != LIME_JSON_NODE_TYPE_STRING)
  ) {
    LimeJsonNodeObjectDestroy(obj);
    LimeJsonNodeDestroy(root);

    return LimeHttpResponseCreateFromStatusCode(
      LIME_HTTP_STATUS_CODE_BADREQUEST
    );
  }

  LimeJsonNode* otp_node = LimeJsonNodeObjectAt(obj, "otp");
  if (!otp_node ||
        (otp_node && LimeJsonNodeGetType(otp_node) != LIME_JSON_NODE_TYPE_INT)
  ) {
    LimeJsonNodeDestroy(name_node);
    LimeJsonNodeObjectDestroy(obj);
    LimeJsonNodeDestroy(root);

    return LimeHttpResponseCreateFromStatusCode(
      LIME_HTTP_STATUS_CODE_BADREQUEST
    );
  }

  int64_t otp = LimeJsonNodeAsInt64(otp_node);

  // destroy all the nodes and root
  LimeJsonNodeDestroy(otp_node);
  LimeJsonNodeDestroy(name_node);
  LimeJsonNodeObjectDestroy(obj);
  LimeJsonNodeDestroy(root);

  LimeJsonNodeObject* obj2 =  LimeJsonNodeObjectCreate();

  LimeJsonNodeObjectInsert(
    obj2, "msg",
    LimeJsonNodeCreateFromString(
      otp == generate_otp() ?
      "success" :
      "invalid otp"
    )
  );

  // root2 owns obj2
  LimeJsonNode* root2 = LimeJsonNodeCreateFromObject(obj2);
  char* raw2 = LimeJsonEncode(root2);
  LimeHttpResponse* resp = LimeHttpResponseCreateFromBody(
    raw2
  );

  free(raw2);
  // destroying the main root will destroy all the children
  LimeJsonNodeDestroy(root2);

  return resp;
}

int main(void) {
  LimeHttpRouter* router = LimeHttpRouterCreate();
  LimeHttpServer* server = LimeHttpServerCreate(router);

  LimeHttpRouterAdd(router, "/get-otp", LIME_HTTP_METHOD_GET, get_otp);
  LimeHttpRouterAdd(router, "/validate-otp", LIME_HTTP_METHOD_POST, validate_otp);

  if (LimeHttpServerRun(server) < 0) {
    printf("ERROR: %s", strerror(errno));
  }

  LimeHttpServerDestroy(server);
  LimeHttpRouterDestroy(router);
}
