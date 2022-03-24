#ifndef DEVELOPER_JOYOFENERGY_C_MOCK_ENDPOINT_H
#define DEVELOPER_JOYOFENERGY_C_MOCK_ENDPOINT_H

#include <stdbool.h>

#include "hal/endpoint.h"

#define ENDPOINT_BUFFER_DATA_SIZE 1024
#define ENDPOINT_IN_BUFFERS 100
#define ENDPOINT_OUT_BUFFERS 100

struct buffer {
  size_t size;
  char data[ENDPOINT_BUFFER_DATA_SIZE];
};

struct endpoint_mock {
  struct buffer in_buffers[ENDPOINT_IN_BUFFERS];
  size_t in_buffers_length;
  struct buffer out_buffers[ENDPOINT_OUT_BUFFERS];
  size_t out_buffers_length;
};

#ifdef __cplusplus
extern "C" {
#endif

static inline void endpoint_mock_init(struct endpoint_mock* mock) {
  mock->in_buffers_length = 0;
  mock->out_buffers_length = 0;
}

const struct buffer endpoint_mock_receive(struct endpoint_mock* mock);
bool endpoint_mock_send(struct endpoint_mock* endpoint, const void* data, size_t size);

#ifdef __cplusplus
}
#endif
#endif  // DEVELOPER_JOYOFENERGY_C_MOCK_ENDPOINT_H
