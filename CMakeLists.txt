cmake_minimum_required(VERSION 3.14)

project(NMMedia LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")
set(Boost_USE_MULTITHREADED ON)

find_package(Threads REQUIRED)
find_package(OpenSSL REQUIRED)
find_package(Boost COMPONENTS system REQUIRED)
find_package(CURL)
find_package(QT NAMES Qt6 Qt5 COMPONENTS Core REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Core REQUIRED)
find_package(Qt6 REQUIRED COMPONENTS Network)


include_directories(/usr/local/include ${OPENSSL_INCLUDE_DIR} ${Boost_INCLUDE_DIR})
if (CURL_FOUND)
    include_directories(${CURL_INCLUDE_DIRS})
    add_definitions(-DHAVE_CURL)
endif()

include_directories(/usr/local/include/gq)

ADD_LIBRARY(gq SHARED IMPORTED)
set_property(TARGET gq PROPERTY
             IMPORTED_LOCATION /usr/local/lib/libgq.so)

         set(PROJECT_SOURCES
             main.cpp
             nmmediaparser.h
             nmmediaparser.cpp
             downloader.h
             downloader.cpp
             publicationbot.h
             publicationbot.cpp
             parsedpost.h
             parsedpost.cpp
             mediamanager.h
             mediamanager.cpp
             )


add_executable(NMMedia
  ${PROJECT_SOURCES}
)
target_link_libraries(NMMedia Qt${QT_VERSION_MAJOR}::Core Qt6::Network)
target_link_libraries(NMMedia gq )
target_link_libraries(NMMedia /usr/local/lib/libTgBot.a ${CMAKE_THREAD_LIBS_INIT} ${OPENSSL_LIBRARIES} ${Boost_LIBRARIES} ${CURL_LIBRARIES})
#target_link_libraries(NMMedia PRIVATE Qt6::Network)

