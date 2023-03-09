/**
 * Copyright (c) 2016-2023 Governikus GmbH & Co. KG, Germany
 */
import QtQuick 2.15
import QtQuick.Layouts 1.15
import Governikus.Global 1.0
import Governikus.Style 1.0

ListItem {
	property int totalHits: 0

	Accessible.description: qsTr("Click to remove category filter and show additional results.")
	Accessible.name: qsTr("%1 additional results in other categories").arg(totalHits)
	icon: Category.imageSource("all")
	showLinkIcon: false
	showSeparator: false
	text: qsTr("Additional results:") + ' ' + totalHits
}
