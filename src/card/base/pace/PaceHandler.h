/*!
 * PaceHandler.h
 *
 * \brief Handler for the PACE protocol. See TR-03110.
 *
 * \copyright Copyright (c) 2014 Governikus GmbH & Co. KG
 */

#pragma once

#include "asn1/PACEInfo.h"
#include "asn1/SecurityInfos.h"
#include "CardConnectionWorker.h"
#include "EnumHelper.h"
#include "pace/KeyAgreement.h"
#include "pace/KeyDerivationFunction.h"

#include <QByteArray>
#include <QSharedPointer>
#include <QString>

class test_PaceHandler;

namespace governikus
{
class PaceHandler
{
	friend class ::test_PaceHandler;

	private:
		const QSharedPointer<CardConnectionWorker> mCardConnectionWorker;
		QSharedPointer<KeyAgreement> mKeyAgreement;
		QSharedPointer<PACEInfo> mPaceInfo;
		QByteArray mIdIcc;
		QByteArray mEncryptionKey;
		QByteArray mMacKey;
		QByteArray mChat;
		QByteArray mCarCurr, mCarPrev;

		/*!
		 * \brief checks for implementation support
		 */
		bool isSupportedProtocol(const QSharedPointer<PACEInfo>& pPaceInfo) const;

		/*!
		 * \brief Perform initialization of the handler. During initialization the PACE protocol parameters to be used are determined.
		 * \param pEfCardAccess the card's EFCardAccess containing all supported protocol parameters
		 * \return the initialization result
		 */
		bool initialize(const QSharedPointer<const EFCardAccess>& pEfCardAccess);

		/*!
		 * \brief Transmit the MSE:Set AT command to the card.
		 * \param pPinId the PIN id to use, e.g. PIN, CAN or PUK
		 * \return false on any card errors
		 */
		bool transmitMSESetAT(PACE_PIN_ID pPinId);

		Q_DISABLE_COPY(PaceHandler)

	public:
		PaceHandler(const QSharedPointer<CardConnectionWorker>& pCardConnectionWorker);

		/*!
		 * \brief Performs the PACE protocol and establishes a PACE channel.
		 * \param pPinId the PIN id to use, e.g. PIN, CAN or PUK
		 * \param pPin the PIN value, e.g. "123456"
		 * \return false on any errors during establishment
		 */
		ReturnCode establishPaceChannel(PACE_PIN_ID pPinId, const QString& pPin);

		/*!
		 * \brief The certificate holder authorization template to be supplied to the card. May be empty
		 */
		void setChat(const QByteArray& pChat);

		/*!
		 * \brief During PACE protocol an encryption key is determined. This method returns this key.
		 * I. e. the output of KDF_enc according to TR-03110 Part 3 chapter A.2.3.
		 * \return the encryption key
		 */
		const QByteArray& getEncryptionKey() const;

		/*!
		 * \brief During PACE protocol a MAC key is determined. This method returns this key.
		 * I. e. the output of KDF_mac according to TR-03110 Part 3 chapter A.2.3.
		 * \return the MAC key
		 */
		const QByteArray& getMacKey() const;

		/*!
		 * \brief During PACE protocol a certificate authority reference (CAR) may be determined. This method returns this CAR.
		 * The CAR is determined, if a CHAT was supplied, \see setChat
		 * \return the card's CAR number 1
		 */
		const QByteArray& getCarCurr() const;

		/*!
		 * \brief During PACE protocol a certificate authority reference (CAR) may be determined. This method returns this CAR.
		 * The CAR is determined, if a CHAT was supplied, \see setChat
		 * \return the card's CAR number 2
		 */
		const QByteArray& getCarPrev() const;

		/*!
		 * \brief The IDicc is the card's compressed ephemeral public key.
		 * \return the card's compressed ephemeral public key
		 */
		const QByteArray& getIdIcc() const;

		/*!
		 * The used PACE protocol.
		 * \return the PACE protocol OID as string.
		 */
		QByteArray getPaceProtocol() const;
};

} /* namespace governikus */
