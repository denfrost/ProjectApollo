// Copyright 2020-2021 Russ 'trdwll' Treadwell <trdwll.com>. All Rights Reserved.

#include "Core/SteamApps.h"

#include "SteamBridgeUtils.h"

USteamApps::USteamApps()
{
	OnDlcInstalledCallback.Register(this, &USteamApps::OnDlcInstalled);
	OnFileDetailsResultCallback.Register(this, &USteamApps::OnFileDetailsResult);
	OnNewUrlLaunchParametersCallback.Register(this, &USteamApps::OnNewUrlLaunchParameters);
}

USteamApps::~USteamApps()
{
	OnDlcInstalledCallback.Unregister();
	OnNewUrlLaunchParametersCallback.Unregister();
}

bool USteamApps::BGetDLCDataByIndex(int32 DLC, int32& AppID, bool& bAvailable, FString& Name)
{
	if (DLC > GetDLCCount())
	{
		return false;
	}

	TArray<char> TempStr;
	bool bResult = SteamApps()->BGetDLCDataByIndex(DLC, (uint32*)&AppID, &bAvailable, TempStr.GetData(), MAX_int32);
	Name = UTF8_TO_TCHAR(TempStr.GetData());
	return bResult;
}

int32 USteamApps::GetAppInstallDir(int32 AppID, FString& Folder)
{
	const uint32 buffer = 1024 * 1024 * 10;
	TArray<char> TempPath;
	TempPath.SetNum(buffer);
	uint32 Length = SteamApps()->GetAppInstallDir(AppID, TempPath.GetData(), buffer);
	if (Length < 0)
	{
		return -1;
	}
	TempPath.SetNum(Length);
	Folder = UTF8_TO_TCHAR(TempPath.GetData());
	return Length;
}

bool USteamApps::GetCurrentBetaName(FString& Name)
{
	TArray<char> TempStr;
	bool bResult = SteamApps()->GetCurrentBetaName(TempStr.GetData(), 4096);
	Name = UTF8_TO_TCHAR(TempStr.GetData());
	return bResult;
}

int32 USteamApps::GetLaunchCommandLine(FString& CommandLine)
{
	TArray<char> TempStr;
	int32 res = SteamApps()->GetLaunchCommandLine(TempStr.GetData(), 2048);
	CommandLine = UTF8_TO_TCHAR(TempStr.GetData());
	return res;
}

void USteamApps::OnDlcInstalled(DlcInstalled_t* pParam)
{
	m_OnDlcInstalled.Broadcast((int32)pParam->m_nAppID);
}

void USteamApps::OnFileDetailsResult(FileDetailsResult_t* pParam)
{
	m_OnFileDetailsResult.Broadcast((ESteamResult)pParam->m_eResult, (int64)pParam->m_ulFileSize, UTF8_TO_TCHAR(pParam->m_FileSHA), (int32)pParam->m_unFlags);
}

void USteamApps::OnNewUrlLaunchParameters(NewUrlLaunchParameters_t* pParam)
{
	m_OnNewUrlLaunchParameters.Broadcast();
}
