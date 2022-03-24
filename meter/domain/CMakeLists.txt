add_library(domain INTERFACE)
target_include_directories(domain INTERFACE ..)
target_link_libraries(meter PUBLIC domain)