#include "router.h"

#include "adapter/protocol/protocol.h"

struct message default_handle(void* controller, const struct message* request) {
  struct message message = {0};
  return message;
}

typedef struct message (*handle_func)(void* controller, const struct message* request);

static struct message router_protocol_handle(struct router* router, const struct message* request) {
  struct readings_controller readings;
  readings_controller_init(&readings, router->reading_service);
  struct price_plan_controller price_plan;
  price_plan_controller_init(&price_plan, router->plan_service);

  void* handler = router;
  handle_func func = (handle_func)default_handle;
  switch (request->head.type) {
    case MESSAGE_READINGS_READ:
      handler = &readings;
      func = (handle_func)reading_read;
      break;
    case MESSAGE_PRICE_PLAN_COMPARE_ALL:
      handler = &price_plan;
      func = (handle_func)price_plan_controller_compare_all;
      break;
    case MESSAGE_PRICE_PLAN_RECOMMEND:
      handler = &price_plan;
      func = (handle_func)price_plan_controller_recommend;
    case MESSAGE_INVALID:
    default:
      break;
  }
  return func(handler, request);
}

bool router_process(struct router* router, struct endpoint* endpoint) {
  char buffer[MESSAGE_LENGTH];
  int rec = endpoint_receive(endpoint, buffer, sizeof(buffer));
  if (rec == 0) {
    return true;
  }
  struct message* request = (struct message*)buffer;
  struct message response = router_protocol_handle(router, request);
  endpoint_send(endpoint, &response, sizeof(response));
  return false;
}
