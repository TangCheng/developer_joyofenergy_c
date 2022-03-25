#include "router.h"

#include "adapter/protocol/protocol.h"

void default_handle(void* controller, const struct message* request, struct message* response) {
}

typedef void (*handle_func)(void* controller, const struct message* request, struct message* response);

static struct message router_protocol_handle(struct router* router, const struct message* request) {
  struct readings_controller readings;
  readings_controller_init(&readings, router->reading_service);
  struct price_plan_controller price_plan;
  price_plan_controller_init(&price_plan, router->plan_service);
  struct cost_usage_controller cost_usage;
  cost_usage_controller_init(&cost_usage, router->cost_usage_service);

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
      break;
    case MESSAGE_LAST_WEEK_USAGE_COST_READ:
      handler = &cost_usage;
      func = (handle_func)cost_usage_controller_read;
      break;
    case MESSAGE_INVALID:
    default:
      break;
  }

  struct message response;
  response.head.type = request->head.type;
  func(handler, request, &response);
  return response;
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
