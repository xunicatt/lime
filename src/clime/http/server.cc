#include <cstdlib>
#include <lime/lime.h>
#include <clime/clime.h>
#include <clime/http/defs.h>

#ifdef __cplusplus
extern "C" {
#endif

LimeHttpServer* LimeHttpServerCreate(LimeHttpRouter* router) {
  LimeHttpServer* server = (LimeHttpServer*)malloc(sizeof(*server));
  server->handle = new lime::http::Server{ *router->handle };
  return server;
}

LimeHttpServer* LimeHttpServerCreateWithWorkers(
  LimeHttpRouter* router,
  const size_t max_workers
) {
  LimeHttpServer* server = (LimeHttpServer*)malloc(sizeof(*server));
  server->handle = new lime::http::Server{
    *router->handle,
    max_workers
  };
  return server;
}

void LimeHttpServerSetPort(
  LimeHttpServer* server,
  const uint16_t port
) {
  server->handle->port(port);
}

uint16_t LimeHttpServerGetPort(LimeHttpServer* server) {
  return server->handle->port();
}

void LimeHttpServerSetAddrs(
  LimeHttpServer* server,
  const char* addrs
) {
  server->handle->addrs(addrs);
}

const char* LimeHttpServerGetAddrs(LimeHttpServer* server) {
  return server->handle->addrs().c_str();
}

int LimeHttpServerRun(LimeHttpServer* server) {
  return server->handle->run();
}

void LimeHttpServerDestroy(LimeHttpServer* server) {
  delete server->handle;
  free(server);
}

#ifdef __cplusplus
}
#endif
