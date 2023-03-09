/**
 * Copyright (c) 2020-2023 Governikus GmbH & Co. KG, Germany
 */
import QtQuick 2.15
import Governikus.Global 1.0
import Governikus.View 1.0
import Governikus.Style 1.0
import Governikus.Type.ApplicationModel 1.0

GListView {
	id: listView

	readonly property string helpTopic: "helpLicenseinformation"

	activeFocusOnTab: true
	displayMarginBeginning: Constants.pane_padding
	displayMarginEnd: Constants.pane_padding
	model: ApplicationModel.getLicenseText()

	delegate: GText {
		Accessible.ignored: text === ""
		text: model.modelData
		textStyle: Style.text.normal
		width: listView.width - Constants.pane_padding

		FocusFrame {
		}
	}

	Keys.onDownPressed: {
		do {
			listView.incrementCurrentIndex();
		} while (currentItem.text === "")
	}
	Keys.onUpPressed: {
		do {
			listView.decrementCurrentIndex();
		} while (currentItem.text === "")
	}
}
