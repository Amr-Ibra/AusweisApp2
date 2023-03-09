/**
 * Copyright (c) 2018-2023 Governikus GmbH & Co. KG, Germany
 */
import QtQuick 2.15
import QtTest 1.15

TestCase {
	id: testCase
	function createTestObject() {
		return createTemporaryQmlObject("import Governikus.WhiteListClient 1.0; WhiteListSurveyView {}", testCase);
	}
	function test_load() {
		let testObject = createTestObject();
		verify(testObject, "Object loaded");
	}

	name: "test_WhiteListSurveyView"
	visible: true
	when: windowShown
}
