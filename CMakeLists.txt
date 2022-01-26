cmake_minimum_required( VERSION 3.22 )

project( MachineLearning )
set( CMAKE_CXX_STANDARD 20 )
set( CMAKE_CXX_STANDARD_REQUIRED True )
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${ADDITIONAL_CFLAGS} -g")

set( Executables 
	Main
	KMeansMetrics
	KNNMetrics
)

foreach( Executable ${Executables} )
	add_executable( ${Executable} "${CMAKE_CURRENT_SOURCE_DIR}/src/bin/${Executable}.cpp" )
	target_include_directories( ${Executable} 
		PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include"
		PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/src"
	)
endforeach( Executable ${Executables} )

add_subdirectory( vendor/catch )
add_executable( Test src/bin/Test.cpp )
target_link_libraries( Test PRIVATE Catch2::Catch2WithMain )
target_include_directories( Test 
	PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include"
	PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/src"
)