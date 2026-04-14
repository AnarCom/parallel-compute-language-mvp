find_package(Boost REQUIRED COMPONENTS coroutine)
find_package(OpenSSL)

add_library(DistributedReactor repository.cpp config.cpp)

target_include_directories(DistributedReactor PUBLIC ${CMAKE_SOURCE_DIR} PRIVATE . ${OPENSSL_INCLUDE_DIR} ${Boost_INCLUDE_DIRS})
target_link_libraries(DistributedReactor PUBLIC OpenSSL::SSL ReactorCommon)