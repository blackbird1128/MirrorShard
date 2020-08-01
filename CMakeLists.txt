cmake_minimum_required(VERSION 3.1...3.16)

project(MirrorShard)
add_executable(MirrorShards )
target_compile_features(MirrorShards PRIVATE cxx_std_17)



set( 
MIRROR_SRC
	src/*.cpp
	extern/*.h
	extern/lode/*.h
	extern/lode/*.cpp
	include/*.h
	include/*.hpp
)

file(
	GLOB
	MIRROR_FILES
	
	${MIRROR_SRC}
)
target_sources(MirrorShards PRIVATE ${MIRROR_FILES})
target_include_directories(MirrorShards PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include")
target_include_directories(MirrorShards PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/extern")
target_include_directories(MirrorShards PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/extern/lode")