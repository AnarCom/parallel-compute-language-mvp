find_package(Boost REQUIRED COMPONENTS coroutine)
find_package(OpenSSL REQUIRED)

add_library(DistributedReactor config.cpp redis_client.cpp repository.cpp)

target_include_directories(DistributedReactor PUBLIC ${CMAKE_SOURCE_DIR} PRIVATE .)
target_link_libraries(DistributedReactor PUBLIC OpenSSL::SSL OpenSSL::Crypto Boost::boost ReactorCommon)