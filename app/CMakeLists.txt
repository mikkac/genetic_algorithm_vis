include_directories(inc)

set(GEN_ALGO_LIB_SRC
    ${CMAKE_CURRENT_SOURCE_DIR}/src/algorithm_controller.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/algorithm_data_model.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/environment.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/individual.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/utils.cpp
)

set(GEN_ALGO_LIB_INC
    ${CMAKE_CURRENT_SOURCE_DIR}/inc/algorithm_controller.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/inc/algorithm_data_model.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/inc/environment.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/inc/individual.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/inc/utils.hpp
)

add_library(${GEN_ALGO_LIB} ${GEN_ALGO_LIB_SRC} ${GEN_ALGO_LIB_INC})
target_include_directories(${GEN_ALGO_LIB} PUBLIC inc)
target_link_libraries(${GEN_ALGO_LIB} CONAN_PKG::spdlog Qt6::Core)

qt_add_executable(${PROJECT_NAME} ${CMAKE_CURRENT_SOURCE_DIR}/main.cpp)
target_link_libraries(${PROJECT_NAME} PRIVATE ${GEN_ALGO_LIB} Qt6::Quick Qt6::Widgets)

qt_add_qml_module(${PROJECT_NAME}
    URI genetic_algorithm
    VERSION 1.0
    QML_FILES main.qml 
)
