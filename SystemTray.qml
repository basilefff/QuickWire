import QtQuick
import Qt.labs.platform as Labs

Labs.SystemTrayIcon {
	id: root

	property bool mainWindowVisible: true

	signal quit
	signal toggleMainWindowVisible

	visible: true

	menu: Labs.Menu {
		Labs.MenuItem {
			text: root.mainWindowVisible ? qsTr("Hide") : qsTr("Show")

			onTriggered: root.toggleMainWindowVisible()
		}
		Labs.MenuItem {
			text: qsTr("Quit")

			onTriggered: root.quit()
		}
	}

	onActivated:
		reason => {
			if (reason === Labs.SystemTrayIcon.Trigger) {
				root.toggleMainWindowVisible()
			}
		}

	onToggleMainWindowVisible:
		mainWindowVisible = !mainWindowVisible
}
