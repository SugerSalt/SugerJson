set(SOURCES
    JsonValue.cpp
    detail/JsonBool.cpp
    detail/JsonNumber.cpp
    detail/JsonString.cpp
    detail/JsonArray.cpp
    detail/JsonObject.cpp
    JsonError.cpp
    detail/tool.cpp
    JsonIterator.cpp
    JsonReader.cpp)

if(BUILD_SHARED_LIBS)
    set(SHARED_LIB ${PROJECT_NAME}_share)
    add_library(${SHARED_LIB} SHARED ${SOURCES})
    set_target_properties(${SHARED_LIB} PROPERTIES
        OUTPUT_NAME sugerjson
        VERSION ${PROJECT_VERSION}
        SOVERSION ${PROJECT_SOVERSION}
        POSITION_INDEPENDENT_CODE ${BUILD_SHARED_LIBS})
    target_include_directories(${SHARED_LIB} PUBLIC
        $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}/../../include>
        $<BUILD_INTERFACE:${PROJECT_BINARY_DIR}/include>
        )
    list(APPEND CMAKE_TARGETS ${SHARED_LIB})
endif()

if(BUILD_STATIC_LIBS)
    set(STATIC_LIB ${PROJECT_NAME}_static)
    add_library(${STATIC_LIB} STATIC ${SOURCES})
    set_target_properties(${STATIC_LIB} PROPERTIES
        OUTPUT_NAME sugerjson
        VERSION ${PROJECT_VERSION})
    target_include_directories(${STATIC_LIB} PUBLIC
        $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}/../../include>
        $<BUILD_INTERFACE:${PROJECT_BINARY_DIR}/include>
        )
    list(APPEND CMAKE_TARGETS ${STATIC_LIB})
endif()

if(BUILD_CMAKE_PACKAGE)
    set(INSTALL_EXPORT EXPORT sugerjson)
else()
    set(INSTALL_EXPORT)
endif()

install(TARGETS ${CMAKE_TARGETS} ${INSTALL_EXPORT}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR})

if(BUILD_EXAMPLE)
    add_subdirectory(example)
endif()