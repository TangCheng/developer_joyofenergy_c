add_library(mocks)
target_sources(mocks PRIVATE clock.c endpoint.c metrology.c bsp.c electricity_reading_repo.c)
target_include_directories(mocks PUBLIC ..)
target_link_libraries(mocks PUBLIC hal)