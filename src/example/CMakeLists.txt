add_executable(readJson readJson.cpp)
target_link_libraries(readJson ${PROJECT_NAME}_share)
file(COPY
    readJson.json readJsonErr.json
    DESTINATION ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})

add_executable(useJson useJson.cpp)
target_link_libraries(useJson ${PROJECT_NAME}_share)

