project(ComparisonLib)

set(SOURCE_FILES
        pch.h
        MainFrame.cpp MainFrame.h
        ViewHome.cpp ViewHome.h
        ViewComparison.cpp ViewComparison.h
        )

find_package(wxWidgets COMPONENTS core base xrc html xml REQUIRED)
include(${wxWidgets_USE_FILE})

add_library(${PROJECT_NAME} STATIC ${SOURCE_FILES})

target_link_libraries(${PROJECT_NAME} ${wxWidgets_LIBRARIES})
target_precompile_headers(${PROJECT_NAME} PRIVATE pch.h)




