project(ComparisonLib)


set(SOURCE_FILES
        pch.h
        MainFrame.cpp MainFrame.h
        EssayView.cpp
        EssayView.h
        EssayManager.cpp
        EssayManager.h
        Essay.cpp
        Essay.h
        Pair.cpp
        Pair.h
        AnalysisView.cpp
        AnalysisView.h
)


find_package(wxWidgets COMPONENTS core base xrc html xml REQUIRED)
include(${wxWidgets_USE_FILE})

# Add the path to the Rcpp include directory
#include_directories("C:/Users/Toazt/AppData/Local/Temp/Rtmpcd2mkG/downloaded_packages")

# Set the path to the downloaded packages directory
# R headers
#include_directories(/usr/include/R)
#include_directories(C:/ProgramData/Microsoft/WindowsStart Menu/Programs/R)

# Rcpp headers
#include_directories("C:/Users/Toazt/CLionProjects/Paired-Comparison-Program/Rcpp/include")
# find R headers
#execute_process (
#        COMMAND bash -c "R CMD config --cppflags | sed s/-I//g"
#        OUTPUT_VARIABLE rInclude
#        OUTPUT_STRIP_TRAILING_WHITESPACE
#)

# find Rcpp headers
#execute_process (
#        COMMAND bash -c "Rscript -e 'Rcpp:::CxxFlags()' | sed s/-I//g | sed 's/.\\(.*\\)/\\1/' | sed 's/\\(.*\\)./\\1/'"
#        OUTPUT_VARIABLE rcppInclude
#)

#INCLUDE_DIRECTORIES("${rInclude} ${rcppInclude}")
#include_directories("../${Rcpp}/include")

add_library(${PROJECT_NAME} STATIC ${SOURCE_FILES})


target_link_libraries(${PROJECT_NAME} ${wxWidgets_LIBRARIES})
target_precompile_headers(${PROJECT_NAME} PRIVATE pch.h)