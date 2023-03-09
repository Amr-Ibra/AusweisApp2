/**
 * Copyright (c) 2014-2023 Governikus GmbH & Co. KG, Germany
 */

/*!
 * \brief Parser for provider configuration files
 */

#pragma once

#include "CallCost.h"
#include "ProviderConfigurationInfo.h"

#include <QByteArray>
#include <QJsonArray>
#include <QOperatingSystemVersion>
#include <QString>


namespace governikus
{
class ProviderConfigurationParser
{
	friend class ::test_ProviderConfigurationParser;

	private:
		static QVector<ProviderConfigurationInfo> parseProvider(const QByteArray& pData, const QOperatingSystemVersion& pCurrentOS);

		ProviderConfigurationParser() = delete;
		~ProviderConfigurationParser() = delete;

	public:
		static QMap<QString, CallCost> parseCallCosts(const QByteArray& pData);
		static QVector<ProviderConfigurationInfo> parseProvider(const QByteArray& pData);
};


} // namespace governikus
