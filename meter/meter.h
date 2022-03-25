#ifndef DEVELOPER_JOYOFENERGY_C_METER_H
#define DEVELOPER_JOYOFENERGY_C_METER_H

#include <stdbool.h>

#include "adapter/controller/router.h"
#include "adapter/schedule/schedule.h"

#ifdef __cplusplus
extern "C" {
#endif

struct meter {
  struct bsp* bsp;
  struct price_plan plans[5];
  size_t plans_count;
  struct electricity_reading_service reading_service;
  struct price_plan_service price_plan_service;
  struct cost_usage_service cost_usage_service;
  struct schedule schedule;
  struct router router;
};

int meter_init(struct meter* meter, struct bsp* bsp, struct electricity_reading_repo* repo);
bool meter_process(struct meter* meter);

#ifdef __cplusplus
}
#endif
#endif  // DEVELOPER_JOYOFENERGY_C_METER_H
