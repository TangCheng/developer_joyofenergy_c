#ifndef DEVELOPER_JOYOFENERGY_C_PROTOCOL_H
#define DEVELOPER_JOYOFENERGY_C_PROTOCOL_H

#include <stdint.h>

enum message_type {
  MESSAGE_INVALID = 0,
  MESSAGE_READINGS_READ,
  MESSAGE_PRICE_PLAN_COMPARE_ALL,
  MESSAGE_PRICE_PLAN_RECOMMEND,
};

struct message_head {
  uint32_t size;
  uint32_t type;
  char payload[0];
};

struct message {
  struct message_head head;
  char payload[1024];
};

#endif  // DEVELOPER_JOYOFENERGY_C_PROTOCOL_H
