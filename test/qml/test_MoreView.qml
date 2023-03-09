/**
 * Copyright (c) 2017-2023 Governikus GmbH & Co. KG, Germany
 */
import QtTest 1.15

TestCase {
	id: parent
	function test_load_MoreView() {
		var item = createTemporaryQmlObject("
			import Governikus.MoreView 1.0;
			MoreView {}
			", parent);
		item.destroy();
	}

	name: "ModuleImportTest"
}
