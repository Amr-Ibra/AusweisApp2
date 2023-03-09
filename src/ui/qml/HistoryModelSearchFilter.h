/**
 * Copyright (c) 2016-2023 Governikus GmbH & Co. KG, Germany
 */

/*!
 * \brief A filter to search the history model
 */

#pragma once

#include <QAbstractListModel>
#include <QPointer>
#include <QSortFilterProxyModel>

namespace governikus
{

class HistoryModelSearchFilter
	: public QSortFilterProxyModel
{
	Q_OBJECT

	private:
		QString mFilterString;

	protected:
		[[nodiscard]] bool filterAcceptsRow(int pSourceRow, const QModelIndex&) const override;

	public:
		Q_INVOKABLE void setFilterString(const QString& pFilterString);
};

} // namespace governikus
