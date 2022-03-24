#ifndef DEVELOPER_JOYOFENERGY_C_PRICE_PLAN_SERVICE_H
#define DEVELOPER_JOYOFENERGY_C_PRICE_PLAN_SERVICE_H

#include "domain/electricity_reading_repo.h"
#include "domain/price_plan.h"

struct price_plan_service {
  struct electricity_reading_repo* reading_repo;
  struct price_plan* plans;
  size_t plans_count;
};

static inline void price_plan_service_init(struct price_plan_service* service,
                                           struct electricity_reading_repo* reading_repo,
                                           struct price_plan* plans, size_t plans_count) {
  service->reading_repo = reading_repo;
  service->plans = plans;
  service->plans_count = plans_count;
}

struct plan_charge {
  const char* plan;
  int charge;
};

size_t price_plan_service_compare_all(struct price_plan_service* service, struct plan_charge* results, size_t count);

size_t price_plan_service_recommend(struct price_plan_service* service, struct plan_charge* results, size_t limit);

#endif  // DEVELOPER_JOYOFENERGY_C_PRICE_PLAN_SERVICE_H
