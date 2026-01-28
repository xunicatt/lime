#include <errno.h>
#include <clime/clime.h>
#include <stdio.h>
#include <string.h>

LimeHttpResponse* helloworld(const LimeHttpRequest* request) {
  (void)request;
  LimeHttpResponse* resp = LimeHttpResponseCreateFromBody("Hello, World!");
  return resp;
}

int main(void) {
  int exit = 0;
  LimeHttpRouter* router = LimeHttpRouterCreate();
  LimeHttpServer* server = LimeHttpServerCreate(router);

  LimeHttpRouterAdd(router, "/", LIME_HTTP_METHOD_GET, helloworld);

  if (LimeHttpServerRun(server) < 0) {
    printf("ERROR: %s\n", strerror(errno));
    exit = 1;
  }

  LimeHttpServerDestroy(server);
  LimeHttpRouterDestroy(router);
  return exit;
}
