#include "meter.h"

#include "configuration.h"

int meter_init(struct meter* meter, struct bsp* bsp, struct electricity_reading_repo* repo) {
  meter->bsp = bsp;
  meter->plans_count = price_plans(meter->plans, sizeof(meter->plans) / sizeof(meter->plans[0]));
  electricity_reading_service_init(&meter->reading_service, bsp, repo);
  price_plan_service_init(&meter->price_plan_service, repo, meter->plans, meter->plans_count);
  schedule_init(&meter->schedule, &meter->reading_service, bsp);
  router_init(&meter->router, &meter->reading_service, &meter->price_plan_service);
  return 0;
}

bool meter_process(struct meter* meter) {
  while (!router_process(&meter->router, bsp_endpoint(meter->bsp)))
    ;
  return schedule_process(&meter->schedule);
}
