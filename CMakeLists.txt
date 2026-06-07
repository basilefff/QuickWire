cmake_minimum_required(VERSION 3.16)

project(QuickWire VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 REQUIRED COMPONENTS Quick)

qt_standard_project_setup(REQUIRES 6.8)

qt_add_executable(appQuickWire
	main.cpp
)

qt_add_qml_module(appQuickWire
	URI QuickWire
	QML_FILES
	Main.qml
	SystemTray.qml
)

target_link_libraries(appQuickWire
	PRIVATE Qt6::Quick
)

install(TARGETS appQuickWire)
