
set(APP_UT "app_test")

set(APP_UT_SRC
	${CMAKE_CURRENT_SOURCE_DIR}/utils_test.cpp
)


add_executable(${APP_UT} ${APP_UT_SRC})
target_link_libraries(${APP_UT}  CONAN_PKG::catch2 CONAN_PKG::spdlog ${CPP_EX_LIB})
target_include_directories(${APP_UT} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/../../app/inc)

add_test(NAME ${APP_UT} COMMAND ${APP_UT})