import QtQuick
import QtQuick.Controls

ApplicationWindow {
	id: mainWindow
	width: 1000
	height: 700
	visible: true
	title: qsTr("QuickWire")

	menuBar: MenuBar {
		Menu {
			title: qsTr("&File")
			Action {
				text: "&Quit"
				shortcut: "Ctrl-Q"
				onTriggered: mainWindow.close()
			}
		}
	}
}
