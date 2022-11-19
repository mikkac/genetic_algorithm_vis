include_directories(inc)

set(CPP_EX_LIB_SRC
	${CMAKE_CURRENT_SOURCE_DIR}/src/configparser.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/src/environment.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/src/individual.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/src/utils.cpp
)

set(CPP_EX_LIB_INC
	${CMAKE_CURRENT_SOURCE_DIR}/inc/configparser.hpp
	${CMAKE_CURRENT_SOURCE_DIR}/inc/environment.hpp
	${CMAKE_CURRENT_SOURCE_DIR}/inc/individual.hpp
	${CMAKE_CURRENT_SOURCE_DIR}/inc/utils.hpp
)

add_library(${CPP_EX_LIB} ${CPP_EX_LIB_SRC} ${CPP_EX_LIB_INC})
target_include_directories(${CPP_EX_LIB} PUBLIC inc)
target_link_libraries(${CPP_EX_LIB} CONAN_PKG::cli11 CONAN_PKG::spdlog) 

qt_add_executable(${PROJECT_NAME} ${CMAKE_CURRENT_SOURCE_DIR}/main.cpp)
target_link_libraries(${PROJECT_NAME} PRIVATE ${CPP_EX_LIB} Qt6::Quick Qt6::Widgets)

qt_add_qml_module(${PROJECT_NAME}
    URI genetic_algorithm
    VERSION 1.0
    QML_FILES main.qml 
)
