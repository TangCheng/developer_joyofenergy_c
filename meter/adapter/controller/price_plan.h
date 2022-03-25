#ifndef DEVELOPER_JOYOFENERGY_C_ADAPTER_CONTROLLER_PRICE_PLAN_H
#define DEVELOPER_JOYOFENERGY_C_ADAPTER_CONTROLLER_PRICE_PLAN_H

#include "adapter/protocol/protocol.h"
#include "app/service/price_plan_service.h"

struct price_plan_controller {
  struct price_plan_service* service;
};

struct price_plan_compare_all_response {
  uint32_t plans_count;
  struct {
    char plan[256];
    uint32_t charge;
  } plans[5];
};

struct price_plan_recommend_request {
  uint32_t limit;
};

struct price_plan_recommend_response {
  uint32_t plans_count;
  struct {
    char plan[256];
    uint32_t charge;
  } plans[5];
};

static inline void price_plan_controller_init(struct price_plan_controller* controller, struct price_plan_service* service) {
  controller->service = service;
}

void price_plan_controller_compare_all(struct price_plan_controller* controller, const struct message* request, struct message* response);

void price_plan_controller_recommend(struct price_plan_controller* controller, const struct message* request, struct message* response);

#endif  // DEVELOPER_JOYOFENERGY_C_ADAPTER_CONTROLLER_PRICE_PLAN_H
