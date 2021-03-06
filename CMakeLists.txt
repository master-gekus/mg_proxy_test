cmake_minimum_required(VERSION 3.5)

project(mg_proxy_test LANGUAGES CXX)

find_package(Qt5 5.7 COMPONENTS Core Gui Widgets Network REQUIRED)

add_executable(${PROJECT_NAME} WIN32 MACOSX_BUNDLE
  main.cpp
  main_window.cpp
  main_window.h
  main_window.ui
  idle_handler.cpp
  idle_handler.h
  idle_handler_p.h
  utils.cpp
  utils.h
  options_dialog.cpp
  options_dialog.h
  options_dialog.ui
)

set_target_properties(${PROJECT_NAME} PROPERTIES
  CXX_STANDARD 11
  CXX_STANDARD_REQUIRED ON
  AUTOMOC ON
  AUTOUIC ON
  AUTORCC ON
  )

target_link_libraries(${PROJECT_NAME} PRIVATE
  Qt5::Core
  Qt5::Gui
  Qt5::Widgets
  Qt5::Network
  )

target_include_directories(${PROJECT_NAME} PRIVATE
  ${CMAKE_CURRENT_BINARY_DIR}
  )
