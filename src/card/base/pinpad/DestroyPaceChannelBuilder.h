/**
 * Copyright (c) 2015-2023 Governikus GmbH & Co. KG, Germany
 */

/*!
 * \brief Data object for creation of card command DestroyPACEChannel
 */

#pragma once

#include "apdu/CommandApdu.h"

#include <QByteArray>


namespace governikus
{

class DestroyPaceChannelBuilder
{
	public:
		/**
		 * Defined in pcsc10_v2.02.08_amd1.1
		 */
		[[nodiscard]] QByteArray createCommandData() const;

		/**
		 * Defined in BSI-TR-03119_V1_pdf
		 */
		[[nodiscard]] CommandApdu createCommandDataCcid() const;
};


}  // namespace governikus
