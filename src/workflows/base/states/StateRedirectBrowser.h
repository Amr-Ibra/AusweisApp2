/**
 * Copyright (c) 2014-2023 Governikus GmbH & Co. KG, Germany
 */

/*!
 * \brief Send a redirect to the browser.
 */

#pragma once

#include "AbstractState.h"
#include "ECardApiResult.h"
#include "GenericContextContainer.h"
#include "context/AuthContext.h"

#include <http_parser.h>


class test_StateRedirectBrowser;


namespace governikus
{

class StateRedirectBrowser
	: public AbstractState
	, public GenericContextContainer<AuthContext>
{
	Q_OBJECT
	friend class StateBuilder;
	friend class ::test_StateRedirectBrowser;

	private:
		explicit StateRedirectBrowser(const QSharedPointer<WorkflowContext>& pContext);

		void reportCommunicationError();
		void sendErrorPage(http_status pStatus);
		bool sendRedirect(const QUrl& pRedirectAddress, const ECardApiResult& pResult);
		void run() override;

};

} // namespace governikus
