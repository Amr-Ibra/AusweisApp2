/**
 * Copyright (c) 2021-2023 Governikus GmbH & Co. KG, Germany
 */

/*!
 * \brief Command APDU for SecureMessaging
 */

#pragma once

#include "CommandApdu.h"
#include "SecureMessagingApdu.h"

namespace governikus
{

/*!
 * Command APDU for Secure Messaging as defined in
 * TR-03110-3
 */
class SecureMessagingCommand
	: public SecureMessagingApdu
{
	Q_DISABLE_COPY(SecureMessagingCommand)

	private:
		QSharedPointer<SM_PROTECTED_LE> mExpectedLength;
		QSharedPointer<SM_CHECKSUM> mChecksum;

	public:
		explicit SecureMessagingCommand(const CommandApdu& pApdu);

		/*!
		 * Returns the expected length.
		 */
		[[nodiscard]] int getExpectedLength() const;

		/*!
		 * Returns the encoded ASN.1 object containing the expected length.
		 */
		[[nodiscard]] QByteArray getExpectedLengthObjectEncoded() const;

		/*!
		 * Returns the cryptographic checsum.
		 */
		[[nodiscard]] QByteArray getMac() const;
};


}  // namespace governikus
