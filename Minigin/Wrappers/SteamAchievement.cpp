#include <Windows.h>
#include "SteamAchievement.h"
#include "Components/ScoreComponent.h"

amu::CSteamAchievements::CSteamAchievements(Achievement_t* Achievements, int NumAchievements) :
    m_iAppID(0),
    m_bInitialized(false),
    m_CallbackUserStatsReceived(this, &CSteamAchievements::OnUserStatsReceived),
    m_CallbackUserStatsStored(this, &CSteamAchievements::OnUserStatsStored),
    m_CallbackAchievementStored(this, &CSteamAchievements::OnAchievementStored)	
{
    m_iAppID = SteamUtils()->GetAppID();
    m_pAchievements = Achievements;
    m_iNumAchievements = NumAchievements;
    RequestStats();
}

void amu::CSteamAchievements::Notify(EventType eventType, amu::Subject* subjectPtr)
{
	switch (eventType)
	{
	case EventType::PacmanEat:
		if (m_OneGameWon)
		{
			return;
		}
		int tempScore{ subjectPtr->GetSubjectOwner()->GetComponent<amu::ScoreComponent>()->GetScore() };
		if (tempScore >= 50)
		{
			m_OneGameWon = true;
			SetAchievement("ACH_WIN_ONE_GAME");
		}
		break;
	}

}

bool amu::CSteamAchievements::RequestStats()
{
	// Is Steam loaded? If not we can't get stats.
	if (NULL == SteamUserStats() || NULL == SteamUser())
	{
		return false;
	}
	// Is the user logged on?  If not we can't get stats.
	if (!SteamUser()->BLoggedOn())
	{
		return false;
	}
	// Request user stats.
	return SteamUserStats()->RequestCurrentStats();
}

bool amu::CSteamAchievements::SetAchievement(const char* ID)
{
	// Have we received a call back from Steam yet?
	if (m_bInitialized)
	{
		SteamUserStats()->SetAchievement(ID);
		return SteamUserStats()->StoreStats();
	}
	// If not then we can't set achievements yet
	return false;
}

void amu::CSteamAchievements::OnUserStatsReceived(UserStatsReceived_t* pCallback)
{
	// we may get callbacks for other games' stats arriving, ignore them
	if (m_iAppID == static_cast<int64>(pCallback->m_nGameID))
	{
		if (k_EResultOK == pCallback->m_eResult)
		{
			OutputDebugString("Received stats and achievements from Steam\n");
			m_bInitialized = true;

			// load achievements
			for (int iAch = 0; iAch < m_iNumAchievements; ++iAch)
			{
				Achievement_t& ach = m_pAchievements[iAch];

				SteamUserStats()->GetAchievement(ach.m_pchAchievementID, &ach.m_bAchieved);
				_snprintf_s(ach.m_rgchName, sizeof(ach.m_rgchName), _TRUNCATE, "%s",
					SteamUserStats()->GetAchievementDisplayAttribute(ach.m_pchAchievementID, "name"));
				_snprintf_s(ach.m_rgchDescription, sizeof(ach.m_rgchDescription), _TRUNCATE, "%s",
					SteamUserStats()->GetAchievementDisplayAttribute(ach.m_pchAchievementID, "desc"));
				;
			}
		}
		else
		{
			char buffer[128];
			_snprintf_s(buffer, 128, _TRUNCATE, "RequestStats - failed, %d\n", pCallback->m_eResult);
			OutputDebugString(buffer);
		}
	}
}

void amu::CSteamAchievements::OnUserStatsStored(UserStatsStored_t* pCallback)
{
	// we may get callbacks for other games' stats arriving, ignore them
	if (m_iAppID == static_cast<int64>(pCallback->m_nGameID))
	{
		if (k_EResultOK == pCallback->m_eResult)
		{
			OutputDebugString("Stored stats for Steam\n");
		}
		else
		{
			char buffer[128];
			_snprintf_s(buffer, 128, _TRUNCATE, "StatsStored - failed, %d\n", pCallback->m_eResult);
			OutputDebugString(buffer);
		}
	}
}

void amu::CSteamAchievements::OnAchievementStored(UserAchievementStored_t* pCallback)
{
	// we may get callbacks for other games' stats arriving, ignore them
	if (m_iAppID == static_cast<int64>(pCallback->m_nGameID))
	{
		OutputDebugString("Stored Achievement for Steam\n");
	}
}
