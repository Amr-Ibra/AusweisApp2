/**
 * Copyright (c) 2020-2023 Governikus GmbH & Co. KG, Germany
 */
import QtTest 1.15
import Governikus.Global 1.0

TestCase {
	id: testCase
	function createTestObject() {
		return createTemporaryQmlObject("import Governikus.InformationView 1.0; ReleaseNotesView {}", testCase);
	}
	function test_load() {
		let testObject = createTestObject();
		verify(testObject, "Object loaded");
	}

	name: "test_ReleaseNotesView"
	visible: true
	when: windowShown
}
