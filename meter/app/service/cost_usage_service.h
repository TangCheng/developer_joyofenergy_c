#ifndef DEVELOPER_JOYOFENERGY_C_ELECTRICITY_COST_USAGE_SERVICE_H
#define DEVELOPER_JOYOFENERGY_C_ELECTRICITY_COST_USAGE_SERVICE_H

#include "domain/electricity_reading_repo.h"

struct cost_usage_service {
  struct bsp* bsp;
  struct electricity_reading_repo* reading_repo;
};

static inline void cost_usage_service_init(struct cost_usage_service* service, struct bsp* bsp,
                                           struct electricity_reading_repo* repo) {
  service->bsp = bsp;
  service->reading_repo = repo;
}

uint32_t cost_usage_service_get_last_week_cost(struct cost_usage_service* service);

#endif // DEVELOPER_JOYOFENERGY_C_ELECTRICITY_COST_USAGE_SERVICE_H
