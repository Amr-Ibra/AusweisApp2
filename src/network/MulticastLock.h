/**
 * Copyright (c) 2019-2023 Governikus GmbH & Co. KG, Germany
 */

#pragma once

namespace governikus
{

class MulticastLock
{
	private:
		void invokeJniMethod(const char* const pMethodName);

	public:
		MulticastLock();
		~MulticastLock();
};


} // namespace governikus
