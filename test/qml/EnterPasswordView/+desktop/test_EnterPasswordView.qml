/**
 * Copyright (c) 2020-2023 Governikus GmbH & Co. KG, Germany
 */
import QtTest 1.15
import Governikus.Type.PasswordType 1.0

TestCase {
	id: parent
	function test_load_EnterPasswordView(data) {
		var item = createTemporaryQmlObject("
			import Governikus.EnterPasswordView 1.0;
			EnterPasswordView {
				passwordType: %1
			}
			".arg(data.passwordType), parent);
		item.destroy();
	}
	function test_load_EnterPasswordView_data() {
		return [{
				"passwordType": PasswordType.PIN
			}, {
				"passwordType": PasswordType.CAN
			}, {
				"passwordType": PasswordType.PUK
			}, {
				"passwordType": PasswordType.REMOTE_PIN
			}];
	}

	visible: true
	when: windowShown
}
