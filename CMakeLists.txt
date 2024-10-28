#	SPDX-FileCopyrightText: 2024 zawa-ch.
#	SPDX-License-Identifier: GPL-3.0-only
cmake_minimum_required(VERSION 3.16)

project(stress-progress
	VERSION 0.1.0
	HOMEPAGE_URL https://github.com/zawa-ch/stress-progress
	LANGUAGES CXX
)
set(${PROJECT_NAME}_AUTHOR "2024 zawa-ch.")
set(${PROJECT_NAME}_LICENSE "GNU GPL version 3.0")

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets LinguistTools)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets LinguistTools)

configure_file(src/applicationdomain.hpp.in src/applicationdomain.hpp)

set(TS_FILES
	i18n/ja_JP.ts
)

set(PROJECT_SOURCES
	src/completedialog.hpp
	src/main.cpp
	src/mainwindow.cpp
	src/mainwindow.h
	src/mainwindow.ui
	src/progressdata.hpp
	src/progressdialog.cpp
	src/progressdialog.hpp
	src/progresswidget.cpp
	src/progresswidget.hpp
	src/versiondialog.hpp
)

file(MAKE_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/i18n)
configure_file(i18n.qrc ${CMAKE_CURRENT_BINARY_DIR} COPYONLY)
set_source_files_properties(${TS_FILES} PROPERTIES OUTPUT_LOCATION "i18n")

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
	qt_create_translation(QM_FILES ${CMAKE_SOURCE_DIR} ${TS_FILES})
	qt_add_executable(stress-progress MANUAL_FINALIZATION ${PROJECT_SOURCES} ${QM_FILES})
# Define target properties for Android with Qt 6 as:
#    set_property(TARGET stress-progress APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
#                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation

else()
	if(ANDROID)
		add_library(stress-progress SHARED ${PROJECT_SOURCES})
# Define properties for Android with Qt 5 after find_package() calls as:
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
	else()
		add_executable(stress-progress ${PROJECT_SOURCES} ${CMAKE_CURRENT_BINARY_DIR}/i18n.qrc)
	endif()
	qt5_add_translation(QM_FILES ${TS_FILES})
endif()

target_link_libraries(stress-progress PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)
target_include_directories(stress-progress
	PRIVATE
	$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src>
	$<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}/src>
)

# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
if(${QT_VERSION} VERSION_LESS 6.1.0)
	set(BUNDLE_ID_OPTION MACOSX_BUNDLE_GUI_IDENTIFIER com.example.stress-progress)
endif()
set_target_properties(stress-progress PROPERTIES
	${BUNDLE_ID_OPTION}
	MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
	MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
	MACOSX_BUNDLE TRUE
	WIN32_EXECUTABLE TRUE
)

include(GNUInstallDirs)
install(TARGETS stress-progress
	BUNDLE DESTINATION .
	LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
	RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

if(QT_VERSION_MAJOR EQUAL 6)
	qt_finalize_executable(stress-progress)
endif()
