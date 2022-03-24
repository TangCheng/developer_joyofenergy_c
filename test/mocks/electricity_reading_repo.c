#include "electricity_reading_repo.h"

#include <assert.h>

static inline struct electricity_reading_repo_mock* mock(struct electricity_reading_repo* repo) {
  return (struct electricity_reading_repo_mock*)repo;
}

size_t electricity_reading_repo_save(struct electricity_reading_repo* repo, struct electricity_reading* reading)
{
  assert(mock(repo)->count < 1024);
  mock(repo)->readings[mock(repo)->count] = *reading;
  mock(repo)->count++;
}

size_t electricity_reading_repo_get_count(struct electricity_reading_repo* repo)
{
  return mock(repo)->count;
}

struct electricity_reading* electricity_reading_repo_load(struct electricity_reading_repo* repo, int reading_id)
{
  assert(reading_id < mock(repo)->count);
  return &mock(repo)->readings[reading_id];
}
