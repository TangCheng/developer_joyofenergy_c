#ifndef DEVELOPER_JOYOFENERGY_C_MOCK_ELECTRICITY_READING_REPO_MOCK_H
#define DEVELOPER_JOYOFENERGY_C_MOCK_ELECTRICITY_READING_REPO_MOCK_H

#include <assert.h>

#include "configuration.h"
#include "domain/electricity_reading_repo.h"

struct electricity_reading_repo_mock {
  struct electricity_reading readings[MAX_ELECTRICITY_READING_COUNT];
  size_t count;
};

void electricity_reading_repo_mock_init(struct electricity_reading_repo_mock *repo, size_t number) {
  assert(number <= MAX_ELECTRICITY_READING_COUNT);
  time_t now = time(NULL);
  for (size_t i = 0; i < number; ++i) {
    repo->readings[i].at = now - (number - i) * 3 * 60;
    repo->readings[i].power = 4000;
  }
  repo->count = number;
}

#endif // DEVELOPER_JOYOFENERGY_C_MOCK_ELECTRICITY_READING_REPO_MOCK_H