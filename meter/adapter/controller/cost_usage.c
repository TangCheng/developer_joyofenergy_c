#include "cost_usage.h"

void cost_usage_controller_read(struct cost_usage_controller* controller, const struct message* request, struct message* response) {
  uint32_t cost = cost_usage_service_get_last_week_cost(controller->service);
  struct cost_usage_response* result = (struct cost_usage_response*)response->payload;
  result->cost = cost;
}
