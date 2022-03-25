#ifndef DEVELOPER_JOYOFENERGY_C_ADAPTER_CONTROLLER_ROTER_H
#define DEVELOPER_JOYOFENERGY_C_ADAPTER_CONTROLLER_ROTER_H

#include <stdbool.h>

#include "adapter/controller/cost_usage.h"
#include "adapter/controller/price_plan.h"
#include "adapter/controller/reading.h"
#include "hal/endpoint.h"

struct router {
  struct electricity_reading_service* reading_service;
  struct price_plan_service* plan_service;
  struct cost_usage_service* cost_usage_service;
};

static inline void router_init(struct router* router,
                               struct electricity_reading_service* reading_service,
                               struct price_plan_service* plan_service,
                               struct cost_usage_service* cost_usage_service) {
  router->reading_service = reading_service;
  router->plan_service = plan_service;
  router->cost_usage_service = cost_usage_service;
}

bool router_process(struct router* router, struct endpoint* endpoint);

#endif // DEVELOPER_JOYOFENERGY_C_ADAPTER_CONTROLLER_ROTER_H