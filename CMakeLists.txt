cmake_minimum_required(VERSION 3.1)
project(SimpleSysexxer)

set(CMAKE_CXX_STANDARD 11)

set(TARGET simplesysexxer)
set(DEFINES __LINUX_ALSASEQ__)
set(RESOURCES
	binincludes/binincludes.qrc)

set(FORMS
	src/MainWindow.ui)
set(HEADERS
	src/MyMainWindow.h
	src/MidiIn.h
	src/MidiOut.h)
set(SOURCES
	src/main.cpp
	src/MyMainWindow.cpp
	src/MidiIn.cpp
	src/MidiOut.cpp)

find_package(ALSA REQUIRED)
if (ALSA_FOUND)
	if (NOT TARGET ALSA::ALSA)
		add_library(ALSA::ALSA UNKNOWN IMPORTED)
		set_target_properties(ALSA::ALSA PROPERTIES
			IMPORTED_LOCATION "${ALSA_LIBRARY}"
			INTERFACE_INCLUDE_DIRECTORIES "${ALSA_INCLUDE_DIRS}")
	endif()
endif()

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)
if (CMAKE_VERSION VERSION_LESS "3.7.0")
	set(CMAKE_INCLUDE_CURRENT_DIR ON)
endif()
find_package(Qt5 COMPONENTS Widgets REQUIRED)

add_executable(${TARGET} ${FORMS} ${HEADERS} ${SOURCES} ${RESOURCES})
target_compile_definitions(${TARGET} PRIVATE ${DEFINES})
target_link_libraries(${TARGET} ALSA::ALSA Qt5::Widgets)
