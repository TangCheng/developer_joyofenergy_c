#ifndef DEVELOPER_JOYOFENERGY_C_SCHEDULE_H
#define DEVELOPER_JOYOFENERGY_C_SCHEDULE_H

#include "app/service/electricity_reading_service.h"
#include "hal/bsp.h"
#include "hal/clock.h"

#define READING_STORE_PERIOD_MINUTES 15
#define READING_STORE_PERIOD_SECONDES (READING_STORE_PERIOD_MINUTES * 60)

struct schedule {
  struct electricity_reading_service* reading_service;
  time_t last_time;
  struct bsp* bsp;
};

static inline void schedule_init(struct schedule* schedule, struct electricity_reading_service* service, struct bsp* bsp) {
  schedule->reading_service = service;
  schedule->bsp = bsp;
  schedule->last_time = clock_now(bsp_clock(schedule->bsp));
}

static inline bool schedule_process(struct schedule* schedule) {
  time_t now = clock_now(bsp_clock(schedule->bsp));
  time_t elapsed = now - schedule->last_time;
  schedule->last_time = now;
  if (elapsed >= READING_STORE_PERIOD_SECONDES) {
    electricity_reading_service_store(schedule->reading_service);
  }
  return true;
}

#endif  // DEVELOPER_JOYOFENERGY_C_SCHEDULE_H
