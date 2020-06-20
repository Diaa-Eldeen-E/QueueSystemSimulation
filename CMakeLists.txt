# Queue system simulation project build configuration

cmake_minimum_required(VERSION 3.1)


set(ProjName qSim)

project(${ProjName})



# ------------------------ Building ---------------------------------------

# Soruce variable

set(EXE_SOURCES 
	src/main.cpp
	src/realQ.cpp
	src/Simulation.cpp
	src/stats.cpp
	src/UI.cpp
)

#Executables and links
add_executable(${ProjName} "${EXE_SOURCES}")

target_include_directories(${ProjName} PUBLIC
			"${PROJECT_SOURCE_DIR}/include" )



# -------------------------------------------------------------------------------------


