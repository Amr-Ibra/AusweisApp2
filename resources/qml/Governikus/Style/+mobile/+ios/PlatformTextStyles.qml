/**
 * Copyright (c) 2019-2023 Governikus GmbH & Co. KG, Germany
 */
import QtQuick 2.15

QtObject {
	readonly property var tutorial_content: TextStyle {
		textFamily: "Charter"
		textSize: Style.dimens.normal_font_size
	}
	readonly property var tutorial_content_highlight: TextStyle {
		bold: true
		textFamily: "Charter"
		textSize: Style.dimens.normal_font_size
	}
	readonly property var tutorial_header: TextStyle {
		textFamily: "Charter"
		textSize: Style.dimens.tutorial_header_font_size
	}
	readonly property var tutorial_header_accent: TextStyle {
		italic: true
		textFamily: "Charter"
		textSize: Style.dimens.tutorial_header_font_size
	}
	readonly property var tutorial_header_highlight: TextStyle {
		bold: true
		textFamily: "Charter"
		textSize: Style.dimens.tutorial_header_font_size
	}
	readonly property var tutorial_header_secondary: TextStyle {
		textFamily: "Charter"
		textSize: Style.dimens.header_font_size
	}
	readonly property var tutorial_header_secondary_highlight: TextStyle {
		bold: true
		textFamily: "Charter"
		textSize: Style.dimens.header_font_size
	}
	readonly property var tutorial_title_highlight: TextStyle {
		bold: true
		textSize: Style.dimens.tutorial_title_font_size
	}
}
