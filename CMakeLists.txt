cmake_minimum_required(VERSION 3.1.0)
project(cefqt1)

set(QT_REQUIRED 1)
set(DESIRED_QT_VERSION "4.8.3")
set(QT_USE_QTCORE 1)
set(QT_USE_QTGUI 1)
set(QT_USE_QTXML 1)

set(CEFROOTDIR "D:/proj/qts/cef/cef95/cef_binary_95.7.18+g0d6005e+chromium-95.0.4638.69_windows32")

# Uncomment if you want to see the commands that make runs
set(CMAKE_VERBOSE_MAKEFILE ON)

find_package(Qt4 4.8.2 REQUIRED QtCore QtGui QtXml QtNetwork QtTest)

if ( NOT ${Qt_QtCore_FOUND} )
  message(FATAL_ERROR "Package Qt component QtCore required, but not found!")
endif( NOT ${Qt_QtCore_FOUND} )

set(CMAKE_AUTOMOC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON) 
add_definitions(${QT_DEFINITIONS})

# List of paths to all include directories of 
# Qt4 QT_INCLUDE_DIR and QT_QTCORE_INCLUDE_DIR are
# always in this variable even if NOTFOUND,
# all other INCLUDE_DIRS are
# only added if they are found.
# You do not need to use this if you include QT_USE_FILE.
include_directories(${QT_INCLUDES})

if(MSVC)
SET(CMAKE_EXE_LINKER_FLAGS "/manifest:no")
endif()

set(CMAKE_CXX_STANDARD 17)
add_executable(cefqt1 WIN32
	main.cpp 
	simple_app.cc 
	simple_app.h 
	simple_handler.cc 
	simple_handler.h
	simple_handler_win.cc 
	update_events.h
	update_events.cc
	cefosrwidget.h
	cefosrwidget.cc 
    dialogbrowserwidget.cpp
    dialogbrowserwidget.h
	
    windowbrowserwidget.cpp
    windowbrowserwidget.h
	
    ${QT_RESOURCES}
    ${HEADERS_GENERATED}
    ${QT_RESOURCES_GENERATED}
    ${UIS_GENERATED}
)

target_compile_definitions(cefqt1 
		PRIVATE 
		NOMINMAX 
		UNICODE 
		WIN32_LEAN_AND_MEAN 
		WINVER=0x0601
		)
		
target_include_directories(cefqt1 
		PRIVATE 
		${CEFROOTDIR}
		${CEFROOTDIR}/include
		)
		

target_link_libraries(cefqt1
    ${QT_LIBRARIES}
    ${QT_QTCORE_LIBRARIES}
    ${QT_QTGUI_LIBRARIES}
    ${QT_QTMAIN_LIBRARY}
    ${QT_QTXML_LIBRARIES}
    ${QT_QTNETWORK_LIBRARIES}
    ${QT_QTTEST_LIBRARIES}
	${CEFROOTDIR}/Release/libcef.lib 
	${CEFROOTDIR}/Release/libcef_dll_wrapper.lib 
	gdi32.lib
	)
