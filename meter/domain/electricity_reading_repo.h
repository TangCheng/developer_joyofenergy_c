#ifndef DEVELOPER_JOYOFENERGY_C_ELECTRICITY_READING_REPO_H
#define DEVELOPER_JOYOFENERGY_C_ELECTRICITY_READING_REPO_H

#include "electricity_reading.h"

#ifdef __cplusplus
extern "C" {
#endif

struct electricity_reading_repo;

size_t electricity_reading_repo_save(struct electricity_reading_repo* repo, struct electricity_reading* reading);
size_t electricity_reading_repo_get_count(struct electricity_reading_repo* repo);
struct electricity_reading* electricity_reading_repo_load(struct electricity_reading_repo* repo, int reading_id);

#ifdef __cplusplus
}
#endif

#endif // DEVELOPER_JOYOFENERGY_C_ELECTRICITY_READING_REPO_H