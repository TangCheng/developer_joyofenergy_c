#include "meter.h"

#include "configuration.h"

static inline size_t price_plans(struct price_plan* plans, size_t count) {
  assert(count >= 3);
  strcpy(plans[0].name, MOST_EVIL_PRICE_PLAN_ID);
  strcpy(plans[0].supplier, DR_EVILS_DARK_ENERGY_ENERGY_SUPPLIER);
  plans[0].centsPerKWH = 10;
  strcpy(plans[1].name, RENEWABLES_PRICE_PLAN_ID);
  strcpy(plans[1].supplier, THE_GREEN_ECO_ENERGY_SUPPLIER);
  plans[1].centsPerKWH = 2;
  strcpy(plans[2].name, STANDARD_PRICE_PLAN_ID);
  strcpy(plans[2].supplier, POWER_FOR_EVERYONE_ENERGY_SUPPLIER);
  plans[2].centsPerKWH = 1;
  return 3;
}

int meter_init(struct meter* meter, struct bsp* bsp, struct electricity_reading_repo* repo) {
  meter->bsp = bsp;
  meter->plans_count = price_plans(meter->plans, sizeof(meter->plans) / sizeof(meter->plans[0]));
  electricity_reading_service_init(&meter->reading_service, bsp, repo);
  price_plan_service_init(&meter->price_plan_service, repo, meter->plans, meter->plans_count);
  schedule_init(&meter->schedule, &meter->reading_service, bsp);
  router_init(&meter->router, &meter->reading_service, &meter->price_plan_service, &meter->cost_usage_service);
  return 0;
}

bool meter_process(struct meter* meter) {
  while (!router_process(&meter->router, bsp_endpoint(meter->bsp)))
    ;
  return schedule_process(&meter->schedule);
}
