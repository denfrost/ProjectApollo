// Copyright 2020-2021 Russ 'trdwll' Treadwell <trdwll.com>. All Rights Reserved.

#include "Core/SteamUserStats.h"

#include "SteamBridgeUtils.h"

USteamUserStats::USteamUserStats()
{
	OnGlobalAchievementPercentagesReadyCallback.Register(this, &USteamUserStats::OnGlobalAchievementPercentagesReady);
	OnGlobalStatsReceivedCallback.Register(this, &USteamUserStats::OnGlobalStatsReceived);
	OnLeaderboardFindResultCallback.Register(this, &USteamUserStats::OnLeaderboardFindResult);
	OnLeaderboardScoresDownloadedCallback.Register(this, &USteamUserStats::OnLeaderboardScoresDownloaded);
	OnLeaderboardScoreUploadedCallback.Register(this, &USteamUserStats::OnLeaderboardScoreUploaded);
	OnLeaderboardUGCSetCallback.Register(this, &USteamUserStats::OnLeaderboardUGCSet);
	OnNumberOfCurrentPlayersCallback.Register(this, &USteamUserStats::OnNumberOfCurrentPlayers);
	OnUserAchievementIconFetchedCallback.Register(this, &USteamUserStats::OnUserAchievementIconFetched);
	OnUserAchievementStoredCallback.Register(this, &USteamUserStats::OnUserAchievementStored);
	OnUserStatsReceivedCallback.Register(this, &USteamUserStats::OnUserStatsReceived);
	OnUserStatsStoredCallback.Register(this, &USteamUserStats::OnUserStatsStored);
	OnUserStatsUnloadedCallback.Register(this, &USteamUserStats::OnUserStatsUnloaded);
}

USteamUserStats::~USteamUserStats()
{
	OnGlobalAchievementPercentagesReadyCallback.Unregister();
	OnGlobalStatsReceivedCallback.Unregister();
	OnLeaderboardFindResultCallback.Unregister();
	OnLeaderboardScoresDownloadedCallback.Unregister();
	OnLeaderboardScoreUploadedCallback.Unregister();
	OnLeaderboardUGCSetCallback.Unregister();
	OnNumberOfCurrentPlayersCallback.Unregister();
	OnUserAchievementIconFetchedCallback.Unregister();
	OnUserAchievementStoredCallback.Unregister();
	OnUserStatsReceivedCallback.Unregister();
	OnUserStatsStoredCallback.Unregister();
	OnUserStatsUnloadedCallback.Unregister();
}

FSteamAPICall USteamUserStats::DownloadLeaderboardEntries(FSteamLeaderboard SteamLeaderboard, ESteamLeaderboardDataRequest LeaderboardDataRequest, int32 RangeStart, int32 RangeEnd) const
{
	return SteamUserStats()->DownloadLeaderboardEntries(SteamLeaderboard, (ELeaderboardDataRequest)LeaderboardDataRequest, RangeStart, RangeEnd);
}

FSteamAPICall USteamUserStats::FindOrCreateLeaderboard(const FString& LeaderboardName, ESteamLeaderboardSortMethod LeaderboardSortMethod, ESteamLeaderboardDisplayType LeaderboardDisplayType) const
{
	return SteamUserStats()->FindOrCreateLeaderboard(TCHAR_TO_UTF8(*LeaderboardName), (ELeaderboardSortMethod)LeaderboardSortMethod, (ELeaderboardDisplayType)LeaderboardDisplayType);
}

bool USteamUserStats::GetAchievementAndUnlockTime(const FString& Name, bool& bAchieved, FDateTime& UnlockTime) const
{
	uint32 TmpTime;
	bool bResult = SteamUserStats()->GetAchievementAndUnlockTime(TCHAR_TO_UTF8(*Name), &bAchieved, &TmpTime);
	UnlockTime = FDateTime::FromUnixTimestamp(TmpTime);
	return bResult;
}

bool USteamUserStats::GetDownloadedLeaderboardEntry(FSteamLeaderboardEntries SteamLeaderboardEntries, int32 index, FSteamLeaderboardEntry& LeaderboardEntry, TArray<int32>& Details, int32 DetailsMax) const
{
	Details.SetNum(DetailsMax);
	LeaderboardEntry_t TmpEntry;
	bool bResult = SteamUserStats()->GetDownloadedLeaderboardEntry(SteamLeaderboardEntries, index, &TmpEntry, Details.GetData(), DetailsMax);
	LeaderboardEntry = TmpEntry;
	return bResult;
}

int32 USteamUserStats::GetGlobalStatHistoryFloat(const FString& StatName, TArray<float>& Data, int32 Size) const
{
	TArray<double> TmpData;
	int32 result = SteamUserStats()->GetGlobalStatHistory(TCHAR_TO_UTF8(*StatName), TmpData.GetData(), Size);
	for (const auto& LData : TmpData)
	{
		Data.Add((float)LData);
	}
	return result;
}

int32 USteamUserStats::GetMostAchievedAchievementInfo(FString& Name, float& Percent, bool& bAchieved) const
{
	TArray<char> TmpName;
	int32 result = SteamUserStats()->GetMostAchievedAchievementInfo(TmpName.GetData(), 1024, &Percent, &bAchieved);
	Name = UTF8_TO_TCHAR(TmpName.GetData());
	return  result;
}

int32 USteamUserStats::GetNextMostAchievedAchievementInfo(int32 IteratorPrevious, FString& Name, float& Percent, bool& bAchieved) const
{
	TArray<char> TmpName;
	int32 result = SteamUserStats()->GetNextMostAchievedAchievementInfo(IteratorPrevious, TmpName.GetData(), 1024, &Percent, &bAchieved);
	Name = UTF8_TO_TCHAR(TmpName.GetData());
	return  result;
}

bool USteamUserStats::GetUserAchievementAndUnlockTime(FSteamID SteamIDUser, const FString& Name, bool& bAchieved, FDateTime& UnlockTime) const
{
	uint32 TmpTime;
	bool bResult = SteamUserStats()->GetUserAchievementAndUnlockTime(SteamIDUser, TCHAR_TO_UTF8(*Name), &bAchieved, &TmpTime);
	UnlockTime = FDateTime::FromUnixTimestamp(TmpTime);
	return bResult;
}

FSteamAPICall USteamUserStats::UploadLeaderboardScore(FSteamLeaderboard SteamLeaderboard, ESteamLeaderboardUploadScoreMethod LeaderboardUploadScoreMethod, int32 Score, const TArray<int32>& ScoreDetails) const
{
	return SteamUserStats()->UploadLeaderboardScore(SteamLeaderboard, (ELeaderboardUploadScoreMethod)LeaderboardUploadScoreMethod, Score, ScoreDetails.GetData(), ScoreDetails.Num());
}

void USteamUserStats::OnGlobalAchievementPercentagesReady(GlobalAchievementPercentagesReady_t* pParam)
{
	m_OnGlobalAchievementPercentagesReady.Broadcast(pParam->m_nGameID, (ESteamResult)pParam->m_eResult);
}

void USteamUserStats::OnGlobalStatsReceived(GlobalStatsReceived_t* pParam)
{
	m_OnGlobalStatsReceived.Broadcast(pParam->m_nGameID, (ESteamResult)pParam->m_eResult);
}

void USteamUserStats::OnLeaderboardFindResult(LeaderboardFindResult_t* pParam)
{
	m_OnLeaderboardFindResult.Broadcast(pParam->m_hSteamLeaderboard, pParam->m_bLeaderboardFound == 1);
}

void USteamUserStats::OnLeaderboardScoresDownloaded(LeaderboardScoresDownloaded_t* pParam)
{
	m_OnLeaderboardScoresDownloaded.Broadcast(pParam->m_hSteamLeaderboard, pParam->m_hSteamLeaderboardEntries, pParam->m_cEntryCount);
}

void USteamUserStats::OnLeaderboardScoreUploaded(LeaderboardScoreUploaded_t* pParam)
{
	m_OnLeaderboardScoreUploaded.Broadcast(pParam->m_bSuccess == 1, pParam->m_hSteamLeaderboard, pParam->m_nScore, pParam->m_bScoreChanged == 1, pParam->m_nGlobalRankNew, pParam->m_nGlobalRankPrevious);
}

void USteamUserStats::OnLeaderboardUGCSet(LeaderboardUGCSet_t* pParam)
{
	m_OnLeaderboardUGCSet.Broadcast((ESteamResult)pParam->m_eResult, pParam->m_hSteamLeaderboard);
}

void USteamUserStats::OnNumberOfCurrentPlayers(NumberOfCurrentPlayers_t* pParam)
{
	m_OnNumberOfCurrentPlayers.Broadcast(pParam->m_bSuccess == 1, pParam->m_cPlayers);
}

void USteamUserStats::OnUserAchievementIconFetched(UserAchievementIconFetched_t* pParam)
{
	m_OnUserAchievementIconFetched.Broadcast(pParam->m_nGameID.ToUint64(), UTF8_TO_TCHAR(pParam->m_rgchAchievementName), pParam->m_bAchieved, pParam->m_nIconHandle);
}

void USteamUserStats::OnUserAchievementStored(UserAchievementStored_t* pParam)
{
	m_OnUserAchievementStored.Broadcast(pParam->m_nGameID, pParam->m_bGroupAchievement, UTF8_TO_TCHAR(pParam->m_rgchAchievementName), pParam->m_nCurProgress, pParam->m_nMaxProgress);
}

void USteamUserStats::OnUserStatsReceived(UserStatsReceived_t* pParam)
{
	m_OnUserStatsReceived.Broadcast(pParam->m_nGameID, (ESteamResult)pParam->m_eResult, pParam->m_steamIDUser.ConvertToUint64());
}

void USteamUserStats::OnUserStatsStored(UserStatsStored_t* pParam)
{
	m_OnUserStatsStored.Broadcast(pParam->m_nGameID, (ESteamResult)pParam->m_eResult);
}

void USteamUserStats::OnUserStatsUnloaded(UserStatsUnloaded_t* pParam)
{
	m_OnUserStatsUnloaded.Broadcast(pParam->m_steamIDUser.ConvertToUint64());
}
