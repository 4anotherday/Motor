include(Platform/Apple-Clang-CXX)
if(NOT CMAKE_CXX_COMPILER_VERSION VERSION_LESS 4.2)
  set(CMAKE_CXX_SYSTEM_FRAMEWORK_SEARCH_FLAG "-iframework ")
else()
  unset(CMAKE_CXX_SYSTEM_FRAMEWORK_SEARCH_FLAG)
endif()