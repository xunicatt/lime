#include <lime/lime.h>
#include <clime/clime.h>

#ifdef __cplusplus
extern "C" {
#endif

LimeHttpServer lime_http_server_create(LimeHttpRouter _router) {
  auto router = (lime::http::Router*)_router;
  return new lime::http::Server { *router };
}

LimeHttpServer lime_http_server_create_with_workers(LimeHttpRouter _router, const size_t max_workers) {
  auto router = (lime::http::Router*)_router;
  return new lime::http::Server { *router, max_workers };
}

void lime_http_server_set_port(LimeHttpServer _server, const uint16_t port) {
  auto server = (lime::http::Server*)_server;
  server->port(port);
}

uint16_t lime_http_server_get_port(LimeHttpServer _server) {
  auto server = (lime::http::Server*)_server;
  return server->port();
}

void lime_http_server_set_addrs(LimeHttpServer _server, const char* addrs) {
  auto server = (lime::http::Server*)_server;
  server->addrs(addrs);
}

const char* lime_http_server_get_addrs(LimeHttpServer _server) {
  auto server = (lime::http::Server*)_server;
  return server->addrs().c_str();
}

int lime_http_server_run(LimeHttpServer _server) {
  auto server = (lime::http::Server*)_server;
  return server->run();
}

void lime_http_server_destroy(LimeHttpServer _server) {
  auto server = (lime::http::Server*)_server;
  delete server;
}

#ifdef __cplusplus
}
#endif
