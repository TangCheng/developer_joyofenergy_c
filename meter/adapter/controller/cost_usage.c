#include "cost_usage.h"

#include "adapter/protocol/protocol.h"

struct message cost_usage_controller_read(struct cost_usage_controller* controller, const struct message* request) {
  uint32_t cost = cost_usage_service_get_last_week_cost(controller->service);

  struct message response;
  response.head.type = MESSAGE_LAST_WEEK_USAGE_COST_READ;
  struct cost_usage_response* result = (struct cost_usage_response*)response.payload;
  result->cost = cost;

  return response;
}
