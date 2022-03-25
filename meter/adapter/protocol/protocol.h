#ifndef DEVELOPER_JOYOFENERGY_C_PROTOCOL_H
#define DEVELOPER_JOYOFENERGY_C_PROTOCOL_H

#include <stdint.h>

enum message_type {
  MESSAGE_INVALID = 0,
  MESSAGE_READINGS_READ,
  MESSAGE_PRICE_PLAN_COMPARE_ALL,
  MESSAGE_PRICE_PLAN_RECOMMEND,
  MESSAGE_LAST_WEEK_USAGE_COST_READ,
};

struct message_head {
  uint32_t size;
  uint32_t type;
  char payload[0];
};

#define MESSAGE_PAYLOAD_LENGTH 1024

struct message {
  struct message_head head;
  char payload[MESSAGE_PAYLOAD_LENGTH];
};

#define MESSAGE_LENGTH (MESSAGE_PAYLOAD_LENGTH + sizeof(struct message_head))

#endif  // DEVELOPER_JOYOFENERGY_C_PROTOCOL_H
