/**
 * Copyright (c) 2016-2023 Governikus GmbH & Co. KG, Germany
 */

#include "SettingsModel.h"

#include "AppSettings.h"
#include "HistorySettings.h"
#include "LanguageLoader.h"
#include "Service.h"

#include <QQmlEngine>

#ifdef Q_OS_ANDROID
	#include <QJniObject>
#endif


using namespace governikus;


SettingsModel::SettingsModel()
	: QObject()
	, mAdvancedSettings(false)
	, mIsStartedByAuth(false)
	, mShowBetaTesting(true)
{
	const auto& settings = Env::getSingleton<AppSettings>()->getHistorySettings();
	connect(&settings, &HistorySettings::fireEnabledChanged, this, &SettingsModel::fireHistoryEnabledChanged);

	connect(Env::getSingleton<AppUpdateDataModel>(), &AppUpdateDataModel::fireAppUpdateDataChanged, this, &SettingsModel::fireAppUpdateDataChanged);

	const auto& generalSettings = Env::getSingleton<AppSettings>()->getGeneralSettings();

	connect(&generalSettings, &GeneralSettings::fireShowInAppNotificationsChanged, this, &SettingsModel::fireShowInAppNotificationsChanged);
	connect(&generalSettings, &GeneralSettings::fireDeveloperOptionsChanged, this, &SettingsModel::fireDeveloperOptionsChanged);
	connect(&generalSettings, &GeneralSettings::fireProxyChanged, this, &SettingsModel::fireUseCustomProxyChanged);

#ifdef Q_OS_ANDROID
	mIsStartedByAuth = QJniObject::callStaticMethod<jboolean>("com/governikus/ausweisapp2/MainActivity", "isStartedByAuth");
#endif
}


QString SettingsModel::getLanguage() const
{
	return LanguageLoader::getLocaleCode();
}


void SettingsModel::setLanguage(const QString& pLanguage)
{
	if (getLanguage() != pLanguage)
	{
		auto& settings = Env::getSingleton<AppSettings>()->getGeneralSettings();
		settings.setLanguage(QLocale(pLanguage).language());
		// do not emit fireLanguageChanged here! The AppController will emit this!
	}
}


void SettingsModel::onTranslationChanged()
{
	Q_EMIT fireLanguageChanged();
}


bool SettingsModel::isAdvancedSettings() const
{
	return mAdvancedSettings;
}


void SettingsModel::setAdvancedSettings(bool pEnabled)
{
	if (mAdvancedSettings != pEnabled)
	{
		mAdvancedSettings = pEnabled;
		Q_EMIT fireAdvancedSettingsChanged();
	}
}


bool SettingsModel::isDeveloperOptions() const
{
	return Env::getSingleton<AppSettings>()->getGeneralSettings().isDeveloperOptions();
}


void SettingsModel::setDeveloperOptions(bool pEnable)
{
	if (isDeveloperOptions() != pEnable)
	{
		auto& settings = Env::getSingleton<AppSettings>()->getGeneralSettings();
		settings.setDeveloperOptions(pEnable);
	}
}


bool SettingsModel::isDeveloperMode() const
{
	return Env::getSingleton<AppSettings>()->getGeneralSettings().isDeveloperMode();
}


void SettingsModel::setDeveloperMode(bool pEnable)
{
	if (isDeveloperMode() != pEnable)
	{
		auto& settings = Env::getSingleton<AppSettings>()->getGeneralSettings();
		settings.setDeveloperMode(pEnable);
	}
}


bool SettingsModel::useSelfauthenticationTestUri() const
{
	return Env::getSingleton<AppSettings>()->getGeneralSettings().useSelfAuthTestUri();
}


void SettingsModel::setUseSelfauthenticationTestUri(bool pUse)
{
	if (useSelfauthenticationTestUri() != pUse)
	{
		auto& settings = Env::getSingleton<AppSettings>()->getGeneralSettings();
		settings.setUseSelfauthenticationTestUri(pUse);
	}
}


QString SettingsModel::getServerName() const
{
	return Env::getSingleton<AppSettings>()->getRemoteServiceSettings().getServerName();
}


void SettingsModel::setServerName(const QString& name)
{
	auto& settings = Env::getSingleton<AppSettings>()->getRemoteServiceSettings();
	settings.setServerName(name);
	Q_EMIT fireDeviceNameChanged();
}


void SettingsModel::removeTrustedCertificate(const QString& pFingerprint)
{
	Env::getSingleton<AppSettings>()->getRemoteServiceSettings().removeTrustedCertificate(pFingerprint);
}


int SettingsModel::removeHistory(const QString& pPeriodToRemove)
{
	auto& settings = Env::getSingleton<AppSettings>()->getHistorySettings();
	int removedItemCount = settings.deleteSettings(Enum<TimePeriod>::fromString(pPeriodToRemove, TimePeriod::UNKNOWN));
	return removedItemCount;
}


bool SettingsModel::getPinPadMode() const
{
	return Env::getSingleton<AppSettings>()->getRemoteServiceSettings().getPinPadMode();
}


void SettingsModel::setPinPadMode(bool pPinPadMode)
{
	auto& settings = Env::getSingleton<AppSettings>()->getRemoteServiceSettings();
	settings.setPinPadMode(pPinPadMode);
}


bool SettingsModel::isHistoryEnabled() const
{
	const auto& settings = Env::getSingleton<AppSettings>()->getHistorySettings();
	return settings.isEnabled();
}


void SettingsModel::setHistoryEnabled(bool pEnabled)
{
	if (isHistoryEnabled() != pEnabled)
	{
		auto& settings = Env::getSingleton<AppSettings>()->getHistorySettings();
		settings.setEnabled(pEnabled);
	}
}


int SettingsModel::removeEntireHistory()
{
	auto& settings = Env::getSingleton<AppSettings>()->getHistorySettings();
	return settings.deleteSettings(TimePeriod::ALL_HISTORY);
}


bool SettingsModel::isUseScreenKeyboard() const
{
	return Env::getSingleton<AppSettings>()->getGeneralSettings().isUseScreenKeyboard();
}


void SettingsModel::setUseScreenKeyboard(bool pUseScreenKeyboard)
{
	if (isUseScreenKeyboard() != pUseScreenKeyboard)
	{
		auto& settings = Env::getSingleton<AppSettings>()->getGeneralSettings();
		settings.setUseScreenKeyboard(pUseScreenKeyboard);
		Q_EMIT fireScreenKeyboardChanged();
	}
}


bool SettingsModel::isVisualPrivacy() const
{
	return Env::getSingleton<AppSettings>()->getGeneralSettings().isVisualPrivacy();
}


void SettingsModel::setVisualPrivacy(bool pVisualPrivacy)
{
	if (isVisualPrivacy() != pVisualPrivacy)
	{
		auto& settings = Env::getSingleton<AppSettings>()->getGeneralSettings();
		settings.setVisualPrivacy(pVisualPrivacy);
		Q_EMIT fireScreenKeyboardChanged();
	}
}


bool SettingsModel::isShuffleScreenKeyboard() const
{
	return Env::getSingleton<AppSettings>()->getGeneralSettings().isShuffleScreenKeyboard();
}


void SettingsModel::setShuffleScreenKeyboard(bool pShuffleScreenKeyboard)
{
	if (isShuffleScreenKeyboard() != pShuffleScreenKeyboard)
	{
		auto& settings = Env::getSingleton<AppSettings>()->getGeneralSettings();
		settings.setShuffleScreenKeyboard(pShuffleScreenKeyboard);
		Q_EMIT fireScreenKeyboardChanged();
	}
}


bool SettingsModel::isEnableCanAllowed() const
{
	return Env::getSingleton<AppSettings>()->getGeneralSettings().isEnableCanAllowed();
}


void SettingsModel::setEnableCanAllowed(bool pEnableCanAllowed)
{
	if (isEnableCanAllowed() != pEnableCanAllowed)
	{
		auto& settings = Env::getSingleton<AppSettings>()->getGeneralSettings();
		settings.setEnableCanAllowed(pEnableCanAllowed);
		Q_EMIT fireCanAllowedChanged();
	}
}


bool SettingsModel::isSkipRightsOnCanAllowed() const
{
	return Env::getSingleton<AppSettings>()->getGeneralSettings().isSkipRightsOnCanAllowed();
}


void SettingsModel::setSkipRightsOnCanAllowed(bool pSkipRightsOnCanAllowed)
{
	if (isSkipRightsOnCanAllowed() != pSkipRightsOnCanAllowed)
	{
		auto& settings = Env::getSingleton<AppSettings>()->getGeneralSettings();
		settings.setSkipRightsOnCanAllowed(pSkipRightsOnCanAllowed);
		Q_EMIT fireCanAllowedChanged();
	}
}


bool SettingsModel::isSimulatorEnabled() const
{
	return Env::getSingleton<AppSettings>()->getGeneralSettings().isSimulatorEnabled();
}


void SettingsModel::setSimulatorEnabled(bool pEnabled)
{
	if (isSimulatorEnabled() != pEnabled)
	{
		auto& settings = Env::getSingleton<AppSettings>()->getGeneralSettings();
		settings.setSimulatorEnabled(pEnabled);
	}
}


UiModule SettingsModel::getStartupModule() const
{
	if (mIsStartedByAuth)
	{
		return UiModule::IDENTIFY;
	}

	const auto& generalSettings = Env::getSingleton<AppSettings>()->getGeneralSettings();
#if defined(Q_OS_ANDROID) || defined(Q_OS_IOS)
	return Enum<UiModule>::fromString(generalSettings.getStartupModule(), UiModule::DEFAULT);

#else
	return Enum<UiModule>::fromString(generalSettings.getStartupModule(), UiModule::TUTORIAL);

#endif
}


void SettingsModel::setStartupModule(UiModule pModule)
{
	if (getStartupModule() != pModule)
	{
		auto& settings = Env::getSingleton<AppSettings>()->getGeneralSettings();
		settings.setStartupModule(Enum<UiModule>::getName(pModule));
		Q_EMIT fireStartupModuleChanged();
	}
}


bool SettingsModel::isAutoStartAvailable() const
{
	return Env::getSingleton<AppSettings>()->getGeneralSettings().isAutoStartAvailable();
}


bool SettingsModel::isAutoStart() const
{
	return Env::getSingleton<AppSettings>()->getGeneralSettings().isAutoStart();
}


bool SettingsModel::autoStartIsSetByAdmin() const
{
	return Env::getSingleton<AppSettings>()->getGeneralSettings().autoStartIsSetByAdmin();
}


void SettingsModel::setAutoStart(bool pEnabled)
{
	if (isAutoStart() != pEnabled)
	{
		auto& settings = Env::getSingleton<AppSettings>()->getGeneralSettings();
		settings.setAutoStart(pEnabled);
		Q_EMIT fireAutoStartChanged();
	}
}


bool SettingsModel::requestStoreFeedback() const
{
#ifdef Q_OS_ANDROID
	const bool startedByAuth = QJniObject::callStaticMethod<jboolean>("com/governikus/ausweisapp2/MainActivity", "isStartedByAuth");
	if (startedByAuth)
	{
		return false;
	}
#endif

	return Env::getSingleton<AppSettings>()->getGeneralSettings().isRequestStoreFeedback();
}


void SettingsModel::hideFutureStoreFeedbackDialogs()
{
	Env::getSingleton<AppSettings>()->getGeneralSettings().setRequestStoreFeedback(false);
}


bool SettingsModel::isAutoCloseWindowAfterAuthentication() const
{
	return Env::getSingleton<AppSettings>()->getGeneralSettings().isAutoCloseWindowAfterAuthentication();
}


void SettingsModel::setAutoCloseWindowAfterAuthentication(bool pEnabled)
{
	if (isAutoCloseWindowAfterAuthentication() != pEnabled)
	{
		auto& settings = Env::getSingleton<AppSettings>()->getGeneralSettings();
		settings.setAutoCloseWindowAfterAuthentication(pEnabled);
		Q_EMIT fireAutoCloseWindowAfterAuthenticationChanged();
	}
}


bool SettingsModel::isAutoUpdateAvailable() const
{
	return Env::getSingleton<AppSettings>()->getGeneralSettings().isAutoUpdateAvailable();
}


bool SettingsModel::isAutoUpdateCheck() const
{
	return Env::getSingleton<AppSettings>()->getGeneralSettings().isAutoUpdateCheck();
}


bool SettingsModel::autoUpdateCheckIsSetByAdmin() const
{
	return Env::getSingleton<AppSettings>()->getGeneralSettings().autoUpdateCheckIsSetByAdmin();
}


void SettingsModel::setAutoUpdateCheck(bool pAutoUpdateCheck)
{
	if (isAutoUpdateCheck() != pAutoUpdateCheck)
	{
		auto& settings = Env::getSingleton<AppSettings>()->getGeneralSettings();
		settings.setAutoUpdateCheck(pAutoUpdateCheck);
		Q_EMIT fireAutoUpdateCheckChanged();
	}
}


bool SettingsModel::isRemindUserToClose() const
{
	return Env::getSingleton<AppSettings>()->getGeneralSettings().isRemindUserToClose();
}


void SettingsModel::setRemindUserToClose(bool pRemindUser)
{
	if (isRemindUserToClose() != pRemindUser)
	{
		auto& settings = Env::getSingleton<AppSettings>()->getGeneralSettings();
		settings.setRemindUserToClose(pRemindUser);
		Q_EMIT fireRemindUserToCloseChanged();
	}
}


bool SettingsModel::isTransportPinReminder() const
{
	return Env::getSingleton<AppSettings>()->getGeneralSettings().isTransportPinReminder();
}


void SettingsModel::setTransportPinReminder(bool pTransportPinReminder)
{
	if (isTransportPinReminder() != pTransportPinReminder)
	{
		auto& settings = Env::getSingleton<AppSettings>()->getGeneralSettings();
		settings.setTransportPinReminder(pTransportPinReminder);
		Q_EMIT fireTransportPinReminderChanged();
	}
}


bool SettingsModel::isShowInAppNotifications() const
{

	return Env::getSingleton<AppSettings>()->getGeneralSettings().isShowInAppNotifications();
}


void SettingsModel::setShowInAppNotifications(bool pShowInAppNotifications)
{
	if (isShowInAppNotifications() != pShowInAppNotifications)
	{
		auto& settings = Env::getSingleton<AppSettings>()->getGeneralSettings();
		settings.setShowInAppNotifications(pShowInAppNotifications);
	}
}


void SettingsModel::updateAppcast()
{
	Env::getSingleton<Service>()->updateAppcast();
}


AppUpdateDataModel* SettingsModel::getAppUpdateData() const
{
	auto* dataModel = Env::getSingleton<AppUpdateDataModel>();
	QQmlEngine::setObjectOwnership(dataModel, QQmlEngine::CppOwnership);
	return dataModel;
}


QUrl SettingsModel::getCustomProxyUrl() const
{
	const auto& settings = Env::getSingleton<AppSettings>()->getGeneralSettings();
	QUrl url;
	switch (settings.getCustomProxyType())
	{
		case QNetworkProxy::Socks5Proxy:
			url.setScheme(QStringLiteral("socks5"));
			break;

		case QNetworkProxy::HttpProxy:
			url.setScheme(QStringLiteral("http"));
			break;

		default:
			url.setScheme(QStringLiteral("unknown"));
			break;
	}
	url.setHost(settings.getCustomProxyHost());
	url.setPort(settings.getCustomProxyPort());
	return url.toString();
}


bool SettingsModel::isCustomProxyAttributesPresent() const
{
	return Env::getSingleton<AppSettings>()->getGeneralSettings().customProxyAttributesPresent();
}


bool SettingsModel::isUseCustomProxy() const
{
	return Env::getSingleton<AppSettings>()->getGeneralSettings().useCustomProxy();
}


void SettingsModel::setUseCustomProxy(bool pUseCustomProxy)
{
	Env::getSingleton<AppSettings>()->getGeneralSettings().setUseCustomProxy(pUseCustomProxy);
}
