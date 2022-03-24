#ifndef DEVELOPER_JOYOFENERGY_C_ELECTRICITY_READING_SERVICE_H
#define DEVELOPER_JOYOFENERGY_C_ELECTRICITY_READING_SERVICE_H

#include "domain/electricity_reading.h"
#include "domain/electricity_reading_repo.h"
#include "hal/bsp.h"


struct electricity_reading_service {
  struct bsp* bsp;
  struct electricity_reading_repo * reading_repo;
};

static inline void electricity_reading_service_init(struct electricity_reading_service* service, struct bsp* bsp,
                                                    struct electricity_reading_repo* repo) {
  service->bsp = bsp;
  service->reading_repo = repo;
}

static inline size_t electricity_reading_service_get(struct electricity_reading_service* service,
                                                     struct electricity_reading* reading, size_t expected_count) {
  size_t copy_count = electricity_reading_repo_get_count(service->reading_repo);
  copy_count = copy_count > expected_count ? expected_count : copy_count;
  if (copy_count > 0) {
    for (int reading_id = 0; reading_id < copy_count; reading_id++) {
      reading[reading_id] = *electricity_reading_repo_load(service->reading_repo, reading_id);
    }
  }
  return copy_count;
}

static inline void electricity_reading_service_store(struct electricity_reading_service* service) {
  struct clock* clock = bsp_clock(service->bsp);
  struct metrology* metrology = bsp_metrology(service->bsp);
  struct electricity_reading reading;
  electricity_reading_init(&reading, clock_now(clock), metrology_get_power(metrology));
  electricity_reading_repo_save(service->reading_repo, &reading);
}

#endif  // DEVELOPER_JOYOFENERGY_C_ELECTRICITY_READING_SERVICE_H
