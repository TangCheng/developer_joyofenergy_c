#include "price_plan_service.h"

#include <stdlib.h>

static int calculate_average_reading(struct price_plan_service* service) {
  int sum = 0;
  size_t readings_count = electricity_reading_repo_get_count(service->reading_repo);
  for (size_t i = 0; i < readings_count; ++i) {
    struct electricity_reading* reading = electricity_reading_repo_load(service->reading_repo, i);
    sum += reading->power;
  }
  return (int)(((double)sum + 0.5) / readings_count);
}

static time_t calculate_time_elapsed(struct price_plan_service* service) {
  size_t readings_count = electricity_reading_repo_get_count(service->reading_repo);
  time_t first = electricity_reading_repo_load(service->reading_repo, 0)->at;
  time_t last = electricity_reading_repo_load(service->reading_repo, readings_count - 1)->at;
  return last - first;
}

static int calculate_cost(struct price_plan_service* service, struct price_plan* pricePlan) {
  double average = calculate_average_reading(service);
  size_t seconds_elapsed = calculate_time_elapsed(service);

  int consumed_watt = average * 3600 / seconds_elapsed;
  int cost_in_cents = consumed_watt * pricePlan->centsPerKWH / 10;
  return cost_in_cents;
}

size_t price_plan_service_compare_all(struct price_plan_service* service, struct plan_charge* results, size_t count) {
  size_t readings_count = electricity_reading_repo_get_count(service->reading_repo);

  if (readings_count == 0) {
    return 0;
  }

  for (size_t i = 0; i < service->plans_count; ++i) {
    results[i].plan = service->plans[i].name;
    results[i].charge = calculate_cost(service, &service->plans[i]);
  }
  return service->plans_count;
}

int compare_charge(const void* a, const void* b) {
  const struct plan_charge* x = (const struct plan_charge*)a;
  const struct plan_charge* y = (const struct plan_charge*)b;
  return x->charge - y->charge;
}

size_t price_plan_service_recommend(struct price_plan_service* service, struct plan_charge* results, size_t limit) {
  size_t readings_count = electricity_reading_repo_get_count(service->reading_repo);

  if (readings_count == 0) {
    return 0;
  }

  struct plan_charge charges[service->plans_count];
  for (size_t i = 0; i < service->plans_count; ++i) {
    charges[i].plan = service->plans[i].name;
    charges[i].charge = calculate_cost(service, &service->plans[i]);
  }
  qsort(charges, service->plans_count, sizeof(charges[0]), compare_charge);
  size_t count = service->plans_count > limit ? limit : service->plans_count;
  for (size_t i = 0; i < count; ++i) {
    results[i].plan = charges->plan;
    results[i].charge = charges[i].charge;
  }
  return count;
}
