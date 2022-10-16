// pch.cpp: 与预编译标头对应的源文件

#include "pch.h"

// 默认 Low - Level I / O 实现，文件包扩展名为
CAkFilePackageLowLevelIOBlocking g_lowLevelIO;

// 当使用预编译的头时，需要使用此源文件，编译才能成功。

DLLEXPORT bool InitMemoryManager()
{
	AkMemSettings memSettings;
	AK::MemoryMgr::GetDefaultSettings(memSettings);

	if (AK::MemoryMgr::Init(&memSettings) != AK_Success)
	{
		assert(!"Could not create the memory manager.");
		return false;
	}
	return true;
}

DLLEXPORT bool InitStreamManager()
{
	AkStreamMgrSettings stmSettings;
	AK::StreamMgr::GetDefaultSettings(stmSettings);

	if (!AK::StreamMgr::Create(stmSettings))
	{
		assert(!"Could not create the Streaming Manager.");
		return false;
	}

	AkDeviceSettings deviceSettings;
	AK::StreamMgr::GetDefaultDeviceSettings(deviceSettings);

	if (g_lowLevelIO.Init(deviceSettings) != AK_Success)
	{
		assert(!"Could not create the streaming device and Low-Level I/O system.");
		return false;
	}

	return true;
}

DLLEXPORT bool InitSoundEngine()
{
	AkInitSettings initSettings;
	AkPlatformInitSettings platformInitSettings;

	AK::SoundEngine::GetDefaultInitSettings(initSettings);
	AK::SoundEngine::GetDefaultPlatformInitSettings(platformInitSettings);

	if (AK::SoundEngine::Init(&initSettings, &platformInitSettings) != AK_Success)
	{
		assert(!"Could not initialize the Sound Engine.");
		return false;
	}

	return true;
}

DLLEXPORT bool InitMusicEngine()
{
	AkMusicSettings musicSettings;
	AK::MusicEngine::GetDefaultInitSettings(musicSettings);

	if (AK::MusicEngine::Init(&musicSettings) != AK_Success)
	{
		assert(!"Could not initialize the Music Engine.");
		return false;
	}

	return true;
}

DLLEXPORT bool InitSpatialAudio()
{
	AkSpatialAudioInitSettings saSettings;

	if (AK::SpatialAudio::Init(saSettings) != AK_Success) {
		assert(!"Could not initialize the Spatial Audio.");
		return false;
	}
	return true;
}

#ifndef AK_OPTIMIZED
DLLEXPORT bool InitCommunication()
{
	AkCommSettings commSettings;
	AK::Comm::GetDefaultInitSettings(commSettings);

	if (AK::Comm::Init(commSettings) != AK_Success)
	{
		assert(!"Could not initialize communication.");
		return false;
	}

	return true;
}

DLLEXPORT void TermCommunication()
{
	AK::Comm::Term();
}

#endif // AK_OPTIMIZED

DLLEXPORT void TermMusicEngine()
{
	AK::MusicEngine::Term();
}



DLLEXPORT void TermSoundEngine()
{
	AK::SoundEngine::Term();
}

DLLEXPORT void TermStreamManager()
{
	g_lowLevelIO.Term();

	if (AK::IAkStreamMgr::Get())
	{
		AK::IAkStreamMgr::Get()->Destroy();
	}
}

DLLEXPORT void TermMemoryManager()
{
	AK::MemoryMgr::Term();
}

DLLEXPORT void SetBankPath(const AkOSChar* bankPath)
{
	g_lowLevelIO.SetBasePath(bankPath);
}

DLLEXPORT void SetCurrLang(const AkOSChar* currLang)
{
	AK::StreamMgr::SetCurrentLanguage(currLang);
}

DLLEXPORT AKRESULT LoadBank_ID(AkBankID bankID)
{
	return AK::SoundEngine::LoadBank(bankID);
}

DLLEXPORT AKRESULT LoadBank_Name(const char* bankName, AkBankID& out_bankID)
{
	return AK::SoundEngine::LoadBank(bankName, out_bankID);
}

DLLEXPORT AKRESULT UnloadBank_ID(AkBankID bankID, const void* pInMemoryBankPtr)
{
	return AK::SoundEngine::UnloadBank(bankID, pInMemoryBankPtr);
}

DLLEXPORT AKRESULT UnloadBank_Name(const char* bankName, const void* pInMemoryBankPtr)
{
	return AK::SoundEngine::UnloadBank(bankName, pInMemoryBankPtr);
}

DLLEXPORT AKRESULT RegisterGameObj(AkGameObjectID objID)
{
	return AK::SoundEngine::RegisterGameObj(objID);
}

DLLEXPORT AKRESULT RegisterNamedGameObj(AkGameObjectID objID, const char* objName)
{
	return AK::SoundEngine::RegisterGameObj(objID, objName);
}

DLLEXPORT AKRESULT UnregisterGameObj(AkGameObjectID objID)
{
	return AK::SoundEngine::UnregisterGameObj(objID);
}

DLLEXPORT AKRESULT UnregisterAllGameObj()
{
	return AK::SoundEngine::UnregisterAllGameObj();
}

DLLEXPORT AkPlayingID PostEvent_ID(AkUniqueID eventID,
	AkGameObjectID objectID, 
	AkUInt32 uFlags /*= 0*/, 
	//AkCallbackFunc pCallback /*= nullptr*/, 
	void* pCookie /*= nullptr*/, 
	AkUInt32 cExternals /*= 0*/, 
	//AkExternalSourceInfo* pExternalSources /*= nullptr*/, 
	AkPlayingID playingID /*= AK_INVALID_PLAYING_ID */)
{
	return AK::SoundEngine::PostEvent(eventID, objectID, uFlags, nullptr/*pCallback*/, 
		pCookie, cExternals, nullptr/*pExternalSources*/, playingID);
}

DLLEXPORT AkPlayingID PostEvent_Name(const char* eventName,
	AkGameObjectID objectID, 
	AkUInt32 uFlags /*= 0*/, 
	//AkCallbackFunc pCallback /*= nullptr*/, 
	void* pCookie /*= nullptr*/, 
	AkUInt32 cExternals /*= 0*/, 
	//AkExternalSourceInfo* pExternalSources /*= nullptr*/, 
	AkPlayingID playingID /*= AK_INVALID_PLAYING_ID */)
{
	return AK::SoundEngine::PostEvent(eventName, objectID, uFlags, nullptr/*pCallback*/,
		pCookie, cExternals, nullptr/*pExternalSources*/, playingID);
}

DLLEXPORT AKRESULT ExecuteActionOnEvent_ID(AkUniqueID eventID, 
	AK::SoundEngine::AkActionOnEventType eActonType, 
	AkGameObjectID objID, AkTimeMs transitionDuration, 
	AkCurveInterpolation eFadeCurve, AkPlayingID playingID)
{
	return AK::SoundEngine::ExecuteActionOnEvent(eventID,
		eActonType, objID, transitionDuration, eFadeCurve, playingID);
}

DLLEXPORT AKRESULT ExecuteActionOnEvent_Name(const char* eventName, 
	AK::SoundEngine::AkActionOnEventType eActonType, 
	AkGameObjectID objID, AkTimeMs transitionDuration, 
	AkCurveInterpolation eFadeCurve, AkPlayingID playingID)
{
	return AK::SoundEngine::ExecuteActionOnEvent(eventName,
		eActonType, objID, transitionDuration, eFadeCurve, playingID);
}

DLLEXPORT AKRESULT RenderAudio()
{
	return AK::SoundEngine::RenderAudio();
}

DLLEXPORT AKRESULT PrepareEvent_ID(AK::SoundEngine::PreparationType preparationType, AkUniqueID* eventIDs, AkUInt32 numOfEvent)
{
	return AK::SoundEngine::PrepareEvent(preparationType, eventIDs, numOfEvent);
}

DLLEXPORT AKRESULT PrepareEvent_Name(AK::SoundEngine::PreparationType preparationType, const char** eventNames, AkUInt32 numOfEvent)
{
	return AK::SoundEngine::PrepareEvent(preparationType, eventNames, numOfEvent);
}

DLLEXPORT AKRESULT PrepareGameSyncs_ID(AK::SoundEngine::PreparationType preparationType, AkGroupType gameSyncType, AkUInt32 groupID, AkUInt32* gameSyncIDs, AkUInt32 numOfSyncs)
{
	return AK::SoundEngine::PrepareGameSyncs(preparationType, gameSyncType, groupID, gameSyncIDs, numOfSyncs);
}

DLLEXPORT AKRESULT PrepareGameSyncs_Name(AK::SoundEngine::PreparationType preparationType, AkGroupType gameSyncType, const char* groupName, const char** gameSyncNames, AkUInt32 numOfSyncs)
{
	return AK::SoundEngine::PrepareGameSyncs(preparationType, gameSyncType, groupName, gameSyncNames, numOfSyncs);
}

DLLEXPORT AKRESULT SetDefaultListeners(const AkGameObjectID* listenerObjs, AkUInt32 numOfListeners)
{
	return AK::SoundEngine::SetDefaultListeners(listenerObjs, numOfListeners);
}

DLLEXPORT AKRESULT SetListeners(AkGameObjectID emitterObj, const AkGameObjectID* listenerOjbs, AkUInt32 numOfListeners)
{
	return AK::SoundEngine::SetListeners(emitterObj, listenerOjbs, numOfListeners);
}

DLLEXPORT AKRESULT SetPosition(AkGameObjectID objID, AkReal32 posX, AkReal32 posY, AkReal32 posZ, AkReal32 oriFrontX, AkReal32 oriFrontY, AkReal32 oriFrontZ, AkReal32 oriTopX, AkReal32 oriTopY, AkReal32 oriTopZ)
{
	AkTransform transform;
	transform.Set(posX, posY, posZ, oriFrontX, oriFrontY, oriFrontZ, oriTopX, oriTopY, oriTopZ);
	return AK::SoundEngine::SetPosition(objID, transform);
}

DLLEXPORT AKRESULT SetRTPCValue_ID(AkRtpcID rtpcID, 
	AkRtpcValue rtpcVal, AkGameObjectID objID,
	AkTimeMs valChangeDuration /*= 0*/, 
	AkCurveInterpolation eFadeCurve /*= AkCurveInterpolation_Linear*/, 
	bool bBypassInternalValueInterpolation /*= false*/)
{
	return AK::SoundEngine::SetRTPCValue(rtpcID, rtpcVal, objID, 
		valChangeDuration, eFadeCurve, bBypassInternalValueInterpolation);
}

DLLEXPORT AKRESULT SetRTPCValue_Name(const char* rtpcName, 
	AkRtpcValue rtpcVal, AkGameObjectID objID, 
	AkTimeMs valChangeDuration /*= 0*/, 
	AkCurveInterpolation eFadeCurve /*= AkCurveInterpolation_Linear*/, 
	bool bBypassInternalValueInterpolation /*= false*/)
{
	return AK::SoundEngine::SetRTPCValue(rtpcName, rtpcVal, objID,
		valChangeDuration, eFadeCurve, bBypassInternalValueInterpolation);
}

DLLEXPORT AKRESULT SetRTPCValueByPlayingID_ID(AkRtpcID rtpcID,
	AkRtpcValue rtpcVal, AkPlayingID playingID,
	AkTimeMs valChangeDuration /*= 0*/,
	AkCurveInterpolation eFadeCurve /*= AkCurveInterpolation_Linear*/,
	bool bBypassInternalValueInterpolation /*= false*/)
{
	return AK::SoundEngine::SetRTPCValueByPlayingID(rtpcID, rtpcVal, playingID,
		valChangeDuration, eFadeCurve, bBypassInternalValueInterpolation);
}

DLLEXPORT AKRESULT SetRTPCValuebyPlayingID_Name(const char* rtpcName,
	AkRtpcValue rtpcVal, AkPlayingID playingID,
	AkTimeMs valChangeDuration /*= 0*/,
	AkCurveInterpolation eFadeCurve /*= AkCurveInterpolation_Linear*/,
	bool bBypassInternalValueInterpolation /*= false*/)
{
	return AK::SoundEngine::SetRTPCValueByPlayingID(rtpcName, rtpcVal, playingID,
		valChangeDuration, eFadeCurve, bBypassInternalValueInterpolation);
}

DLLEXPORT AKRESULT ResetRTPCValue_ID(AkRtpcID rtpcID, AkGameObjectID objID, AkTimeMs valChangeDuration /*= 0*/, AkCurveInterpolation eFadeCurve /*= AkCurveInterpolation_Linear*/, bool bBypassInternalValueInterpolation /*= false*/)
{
	return AK::SoundEngine::ResetRTPCValue(rtpcID, objID, valChangeDuration,
		eFadeCurve, bBypassInternalValueInterpolation);
}

DLLEXPORT AKRESULT ResetRTPCValue_Name(const char* rtpcName, AkGameObjectID objID, AkTimeMs valChangeDuration /*= 0*/, AkCurveInterpolation eFadeCurve /*= AkCurveInterpolation_Linear*/, bool bBypassInternalValueInterpolation /*= false*/)
{
	return AK::SoundEngine::ResetRTPCValue(rtpcName, objID, valChangeDuration,
		eFadeCurve, bBypassInternalValueInterpolation);
}

DLLEXPORT AKRESULT SetState_ID(AkStateGroupID stateGroupID, AkStateID stateID)
{
	return AK::SoundEngine::SetState(stateGroupID, stateID);
}

DLLEXPORT AKRESULT SetState_Name(const char* stateGroupName, const char* stateName)
{
	return AK::SoundEngine::SetState(stateName, stateName);
}

DLLEXPORT AKRESULT SetSwitch_ID(AkSwitchGroupID switchGroupID, AkSwitchStateID switchStateID, AkGameObjectID objID)
{
	return AK::SoundEngine::SetSwitch(switchGroupID, switchStateID, objID);
}

DLLEXPORT AKRESULT SetSwitch_Name(const char* switchGroupName, const char* switchStateName, AkGameObjectID objID)
{
	return AK::SoundEngine::SetSwitch(switchGroupName, switchStateName, objID);
}

DLLEXPORT AKRESULT PostTrigger_ID(AkTriggerID triggerID, AkGameObjectID objID)
{
	return AK::SoundEngine::PostTrigger(triggerID, objID);
}

DLLEXPORT AKRESULT PostTrigger_Name(const char* triggerName, AkGameObjectID objID)
{
	return AK::SoundEngine::PostTrigger(triggerName, objID);
}

