#ifndef DEVELOPER_JOYOFENERGY_C_ADAPTER_CONTROLLER_COST_USAGE_H
#define DEVELOPER_JOYOFENERGY_C_ADAPTER_CONTROLLER_COST_USAGE_H

#include <stdint.h>

#include "adapter/protocol/protocol.h"
#include "app/service/cost_usage_service.h"

struct cost_usage_controller {
  struct cost_usage_service* service;
};

static inline void cost_usage_controller_init(struct cost_usage_controller* controller,
                                              struct cost_usage_service* service) {
  controller->service = service;
}

struct cost_usage_response {
  uint32_t cost;
};

void cost_usage_controller_read(struct cost_usage_controller* controller, const struct message* request, struct message* response);

#endif // DEVELOPER_JOYOFENERGY_C_ADAPTER_CONTROLLER_COST_USAGE_H
