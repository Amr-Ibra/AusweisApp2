/**
 * Copyright (c) 2019-2023 Governikus GmbH & Co. KG, Germany
 */

#pragma once

#include "DiagnosisModel.h"
#include "Env.h"
#include "context/DiagnosisContext.h"
#include "controller/DiagnosisController.h"

#include <QAbstractListModel>
#include <QScopedPointer>
#include <QSharedPointer>
#include <QUrl>


namespace governikus
{

class SelfDiagnosisModel
	: public QObject
{
	Q_OBJECT
	friend class Env;

	Q_PROPERTY(QAbstractListModel * sectionsModel READ getSectionsModel CONSTANT)
	Q_PROPERTY(bool running READ isRunning NOTIFY fireRunningChanged)

	private:
		QSharedPointer<DiagnosisContext> mDiagnosisContext;
		DiagnosisModel mDiagnosisModel;
		QScopedPointer<DiagnosisController> mDiagnosisController;

		SelfDiagnosisModel();
		~SelfDiagnosisModel() override = default;

		bool isRunning() const;

	public:
		[[nodiscard]] QAbstractListModel* getSectionsModel();
		Q_INVOKABLE void startController();
		Q_INVOKABLE void stopController();
		Q_INVOKABLE void saveToFile(const QUrl& pFilename) const;
		[[nodiscard]] Q_INVOKABLE QString getCreationTime() const;

	public Q_SLOTS:
		void onTranslationChanged();

	Q_SIGNALS:
		void fireSectionContentModelChanged();
		void fireCurrentSectionChanged();
		void fireRunningChanged();
};

} // namespace governikus
