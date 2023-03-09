/**
 * Copyright (c) 2021-2023 Governikus GmbH & Co. KG, Germany
 */
import QtQuick 2.15
import QtQuick.Layouts 1.15
import Governikus.Global 1.0
import Governikus.PasswordInfoView 1.0
import Governikus.ResultView 1.0
import Governikus.Style 1.0
import Governikus.TitleBar 1.0
import Governikus.Type.PasswordType 1.0
import Governikus.Type.PersonalizationModel 1.0

ResultErrorView {
	id: root
	buttonText: PersonalizationModel.error ?
	//: LABEL ANDROID IOS
	qsTr("OK") :
	//: LABEL ANDROID IOS
	qsTr("Continue")
	errorCode: PersonalizationModel.error ? PersonalizationModel.statusCodeString : ""
	errorDescription: PersonalizationModel.error ? PersonalizationModel.errorText : ""
	header: PersonalizationModel.error ? PersonalizationModel.errorHeader : ""
	resultType: PersonalizationModel.error ? ResultView.Type.IsError : ResultView.Type.IsSuccess
	//: INFO ANDROID IOS Success message that the Smart-eID was created.
	text: PersonalizationModel.error ? PersonalizationModel.resultString : qsTr("You have successfully set up your Smart-eID.")

	//: LABEL ANDROID IOS
	title: qsTr("Set up Smart-eID")

	ColumnLayout {
		spacing: Constants.pane_spacing
		visible: !PersonalizationModel.error
		width: parent.width

		GText {
			Layout.fillWidth: true

			//: INFO ANDROID IOS Explanation text of the Smart-eID blocking code
			text: qsTr("Please write down your blocking code:")
		}
		GText {
			Layout.fillWidth: true
			horizontalAlignment: Text.AlignHCenter
			text: PersonalizationModel.blockingCode
			textStyle: Style.text.header_highlight
			visible: text !== ""
		}
		GText {
			Layout.fillWidth: true

			//: LABEL ANDROID IOS
			text: qsTr("You will shortly receive the blocking password and further information about your Smart-eID by letter.")
			visible: PersonalizationModel.blockingCode !== ""
		}
		GText {
			Layout.fillWidth: true
			//: INFO ANDROID IOS Placeholder (error) text if the Smart-eID setup finished successfully but for some reason no blocking code was retrieved
			text: qsTr("The Smart-eID setup finished successfully but no blocking code was retrieved. For security reasons, you should delete your Smart-eID and restart the setup.")
			textStyle: Style.text.normal_warning_highlight
			visible: PersonalizationModel.blockingCode === ""
		}
		MoreInformationLink {
			Layout.alignment: Qt.AlignHCenter
			text: infoData.linkText

			onClicked: push(passwordInfoView)
		}
		GText {
			Layout.fillWidth: true
			text: {
				switch (PersonalizationModel.remainingAttempts) {
				case 0:
					//: LABEL ANDROID IOS
					return qsTr("You have reached the allowed amount of Smart-eID setups for the current period. You may set up another Smart-eID with your ID card on %1.").arg(PersonalizationModel.restrictionDate);
				case 1:
					//: LABEL ANDROID IOS
					return qsTr("Attention: you may only set up <b><u>one</u></b> more Smart-eID with your ID card. Further setups may be carried out on %1.").arg(PersonalizationModel.restrictionDate);
				default:
					return "";
				}
			}
			textStyle: Style.text.normal_warning
			visible: text !== ""
		}
	}
	PasswordInfoData {
		id: infoData
		contentType: PasswordInfoContent.Type.SMART_BLOCKING_CODE
	}
	Component {
		id: passwordInfoView
		PasswordInfoView {
			infoContent: infoData
			titleBarColor: root.titleBarColor

			navigationAction: NavigationAction {
				action: NavigationAction.Action.Back

				onClicked: pop()
			}
		}
	}
}
