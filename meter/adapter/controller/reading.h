#ifndef DEVELOPER_JOYOFENERGY_C_ADAPTER_CONTROLLER_READING_H
#define DEVELOPER_JOYOFENERGY_C_ADAPTER_CONTROLLER_READING_H

#include "adapter/protocol/protocol.h"
#include "app/service/electricity_reading_service.h"
#include "configuration.h"

struct readings_controller {
  struct electricity_reading_service* service;
};

static inline void readings_controller_init(struct readings_controller* controller,
                                            struct electricity_reading_service* service) {
  controller->service = service;
}

struct reading_message_response {
  uint32_t readings_count;
  struct electricity_reading readings[MAX_ELECTRICITY_READING_COUNT];
};

void reading_read(struct readings_controller* controller, const struct message* request, struct message* response);

#endif  // DEVELOPER_JOYOFENERGY_C_ADAPTER_CONTROLLER_READING_H
