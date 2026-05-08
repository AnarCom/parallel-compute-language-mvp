find_package(Boost REQUIRED COMPONENTS coroutine)
find_package(OpenSSL)

add_library(DistributedReactor impl.cpp)

target_include_directories(DistributedReactor PUBLIC ${OPENSSL_INCLUDE_DIR} ${Boost_INCLUDE_DIRS} ${CMAKE_SOURCE_DIR})
target_link_libraries(DistributedReactor PUBLIC OpenSSL::SSL ReactorCommon)