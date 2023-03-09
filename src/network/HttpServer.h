/**
 * Copyright (c) 2016-2023 Governikus GmbH & Co. KG, Germany
 */

/*!
 * \brief Provide a HTTP server.
 */

#pragma once

#include "HttpRequest.h"
#include "PortFile.h"

#include <QMetaMethod>
#include <QStringList>
#include <QTcpServer>
#include <QVector>

namespace governikus
{

class HttpServer
	: public QObject
{
	Q_OBJECT

	private:
		QVector<QTcpServer*> mServer;
		PortFile mPortFile;

		void shutdown();
		void bindAddresses(quint16 pPort, const QVector<QHostAddress>& pAddresses);
		bool checkReceiver(const QMetaMethod& pSignal, HttpRequest* pRequest);

	public:
		static quint16 cPort;
		static QVector<QHostAddress> cAddresses;
		static QString getDefault();

		explicit HttpServer(quint16 pPort = HttpServer::cPort,
				const QVector<QHostAddress>& pAddresses = HttpServer::cAddresses);
		~HttpServer() override;

		[[nodiscard]] QStringList boundAddresses() const;
		[[nodiscard]] bool isListening() const;
		[[nodiscard]] quint16 getServerPort() const;
		void rebind(quint16 pPort = 0, const QVector<QHostAddress>& pAddresses = HttpServer::cAddresses);

	private Q_SLOTS:
		void onNewConnection();
		void onMessageComplete(HttpRequest* pRequest);

	Q_SIGNALS:
		void fireNewHttpRequest(const QSharedPointer<HttpRequest>& pRequest);
		void fireNewWebSocketRequest(const QSharedPointer<HttpRequest>& pRequest);
		void fireRebound();
};

} // namespace governikus
