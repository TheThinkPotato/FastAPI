# CMakeList.txt : CMake project for FastAPI, include source and define
# project specific logic here.
#

# Add source to this project's executable.
set(ASIO_INCLUDE_DIR "D:/libs/asio/include")
include_directories(${ASIO_INCLUDE_DIR})


set(CROW_INCLUDE_DIR "D:/libs/Crow/include")
include_directories(${CROW_INCLUDE_DIR})

add_executable (FastAPI "FastAPI.cpp" "FastAPI.h")

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET FastAPI PROPERTY CXX_STANDARD 20)
endif()

# TODO: Add tests and install targets if needed.
