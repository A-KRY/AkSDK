// pch.h: 这是预编译标头文件。
// 下方列出的文件仅编译一次，提高了将来生成的生成性能。
// 这还将影响 IntelliSense 性能，包括代码完成和许多代码浏览功能。
// 但是，如果此处列出的文件中的任何一个在生成之间有更新，它们全部都将被重新编译。
// 请勿在此处添加要频繁更新的文件，这将使得性能优势无效。

#pragma once
#ifndef PCH_H
#define PCH_H

#define DLLEXPORT extern "C" __declspec(dllexport)

// 添加要在此处预编译的标头
#include "framework.h"

// Release 时取消下行注释以完全停用assert
//#define NDEBUG
#include <cassert>

// 异常处理
#include <stdexcept>

// Memory Manager Interface
#include "AK/SoundEngine/Common/AkMemoryMgr.h"

// Default Memory Manager
#include "AK/SoundEngine/Common/AkModule.h"

// Streaming Manager Interface
#include "AK/SoundEngine/Common/IAkStreamMgr.h"

// 线程定义
#include "AK/Tools/Common/AkPlatformFuncs.h"

// Low-Level I/O 实现实例
#include "AkFilePackageLowLevelIOBlocking.h"
#include "AkDefaultIOHookBlocking.h"
#include "AkFileHelpers.h"

// Sound Engine
#include "AK/SoundEngine/Common/AkSoundEngine.h"

// Music Engine
#include "AK/MusicEngine/Common/AkMusicEngine.h"

// Spatial Audio
#include "AK/SpatialAudio/Common/AkSpatialAudio.h"

// 通信模块，Release版本不需要
#ifndef AK_OPTIMIZED
#include "AK/Comm/AkCommunication.h"
#endif // AK_OPTIMIZED

// AK 类型
#include "AK/SoundEngine/Common/AkTypes.h"


// C++/CLI 类

/*
/// 3D vector.
public ref struct CLI_AkVector
{
	AkReal32		X;	///< X Position
	AkReal32		Y;	///< Y Position
	AkReal32		Z;	///< Z Position

	CLI_AkVector()
	{
		X = 0.0f;
		Y = 0.0f;
		Z = 0.0f;
	}

	CLI_AkVector(const CLI_AkVector% b)
	{
		X = b.X;
		Y = b.Y;
		Z = b.Z;
	}

	CLI_AkVector(AkVector b)
	{
		X = b.X;
		Y = b.Y;
		Z = b.Z;
	}

	CLI_AkVector operator=(AkVector b)
	{
		X = b.X;
		Y = b.Y;
		Z = b.Z;
		return *this;
	}

	CLI_AkVector operator=(CLI_AkVector b)
	{
		if (this != % b) 
		{
			X = b.X;
			Y = b.Y;
			Z = b.Z;
		}
		return *this;
	}

	inline CLI_AkVector operator+(const CLI_AkVector b)
	{
		CLI_AkVector v;

		v.X = X + b.X;
		v.Y = Y + b.Y;
		v.Z = Z + b.Z;

		return v;
	}

	inline void Zero()
	{
		X = 0; Y = 0; Z = 0;
	}

	AkVector ToAkVector()
	{
		AkVector a;
		a.X = X;
		a.Y = Y;
		a.Z = Z;
		return a;
	}
};

/// Position and orientation of game objects.
public ref class CLI_AkTransform
{
private:
	CLI_AkVector		orientationFront;	///< Orientation of the listener
	CLI_AkVector		orientationTop;		///< Top orientation of the listener
	CLI_AkVector		position;			///< Position of the listener
public:
	CLI_AkTransform()
	{
		
	}

	CLI_AkTransform(const CLI_AkTransform% transform)
	{
		orientationFront = transform.orientationFront;
		orientationTop = transform.orientationTop;
		position = transform.position;
	}

	AkTransform ToAkTransfrom()
	{
		AkTransform tf;
		tf.Set(position.X, position.Y, position.Z,
			orientationFront.X, orientationFront.Y, orientationFront.Z, 
			orientationTop.X, orientationTop.Y, orientationTop.Z);
		return tf;
	}

	//
	// Getters.
	//

	/// Get position vector.
	inline const CLI_AkVector Position()
	{
		return position;
	}

	/// Get orientation front vector.
	inline const CLI_AkVector OrientationFront()
	{
		return orientationFront;
	}

	/// Get orientation top vector.
	inline const CLI_AkVector OrientationTop()
	{
		return orientationTop;
	}

	//
	// Setters.
	//

	/// Set position and orientation. Orientation front and top should be orthogonal and normalized.
	inline void Set(
		const AkVector in_position,			///< Position vector.
		const AkVector in_orientationFront,	///< Orientation front
		const AkVector in_orientationTop		///< Orientation top
	)
	{
		position = in_position;
		orientationFront = in_orientationFront;
		orientationTop = in_orientationTop;
	}

	inline void Set(
		const CLI_AkVector in_position,			///< Position vector.
		const CLI_AkVector in_orientationFront,	///< Orientation front
		const CLI_AkVector in_orientationTop		///< Orientation top
	)
	{
		position = in_position;
		orientationFront = in_orientationFront;
		orientationTop = in_orientationTop;
	}

	/// Set position and orientation. Orientation front and top should be orthogonal and normalized.
	inline void Set(
		AkReal32 in_positionX,					///< Position x
		AkReal32 in_positionY,					///< Position y
		AkReal32 in_positionZ,					///< Position z
		AkReal32 in_orientFrontX,				///< Orientation front x
		AkReal32 in_orientFrontY,				///< Orientation front y
		AkReal32 in_orientFrontZ,				///< Orientation front z
		AkReal32 in_orientTopX,					///< Orientation top x
		AkReal32 in_orientTopY,					///< Orientation top y
		AkReal32 in_orientTopZ					///< Orientation top z
	)
	{
		position.X = in_positionX;
		position.Y = in_positionY;
		position.Z = in_positionZ;
		orientationFront.X = in_orientFrontX;
		orientationFront.Y = in_orientFrontY;
		orientationFront.Z = in_orientFrontZ;
		orientationTop.X = in_orientTopX;
		orientationTop.Y = in_orientTopY;
		orientationTop.Z = in_orientTopZ;
	}

	/// Set position.
	inline void SetPosition(
		const AkVector in_position			///< Position vector.
	)
	{
		position = in_position;
	}

	/// Set position.
	inline void SetPosition(
		AkReal32 in_x,							///< x
		AkReal32 in_y,							///< y
		AkReal32 in_z							///< z
	)
	{
		position.X = in_x;
		position.Y = in_y;
		position.Z = in_z;
	}

	/// Set orientation. Orientation front and top should be orthogonal and normalized.
	inline void SetOrientation(
		const AkVector in_orientationFront,	///< Orientation front
		const AkVector in_orientationTop		///< Orientation top
	)
	{
		orientationFront = in_orientationFront;
		orientationTop = in_orientationTop;
	}

	/// Set orientation. Orientation front and top should be orthogonal and normalized.
	inline void SetOrientation(
		AkReal32 in_orientFrontX,				///< Orientation front x
		AkReal32 in_orientFrontY,				///< Orientation front y
		AkReal32 in_orientFrontZ,				///< Orientation front z
		AkReal32 in_orientTopX,					///< Orientation top x
		AkReal32 in_orientTopY,					///< Orientation top y
		AkReal32 in_orientTopZ					///< Orientation top z
	)
	{
		orientationFront.X = in_orientFrontX;
		orientationFront.Y = in_orientFrontY;
		orientationFront.Z = in_orientFrontZ;
		orientationTop.X = in_orientTopX;
		orientationTop.Y = in_orientTopY;
		orientationTop.Z = in_orientTopZ;
	}
};
*/


/*
 *
 * 全局变量
 *
 */



/*
 *
 * 初始化各模块
 *
 */

// 初始化 Memory Manager
DLLEXPORT bool InitMemoryManager();

// 初始化 Streaming Manager
DLLEXPORT bool InitStreamManager();

// 初始化 Sound Engine
DLLEXPORT bool InitSoundEngine();

// 初始化 Music Engine
DLLEXPORT bool InitMusicEngine();

// 初始化 Spatial Audio
DLLEXPORT bool InitSpatialAudio();

// 初始化通信模块
#ifndef AK_OPTIMIZED
DLLEXPORT bool InitCommunication();
#endif // AK_OPTIMIZED

/*
 *
 * 终止各模块
 *
 */

// 终止通信模块
#ifndef AK_OPTIMIZED
DLLEXPORT void TermCommunication();
#endif // AK_OPTIMIZED

// 终止 Music Engine
DLLEXPORT void TermMusicEngine();

// 终止 Sound Engine
DLLEXPORT void TermSoundEngine();

// 终止 Streaming Manager
DLLEXPORT void TermStreamManager();

// 终止 Memory Manager
DLLEXPORT void TermMemoryManager();

/*
 *
 * Wwise 元素集成
 *
 */

// 设置 Sound Bank 路径
DLLEXPORT void SetBankPath(const AkOSChar* bankPath);

// 选择 Sound Bank 语言
DLLEXPORT void SetCurrLang(const AkOSChar* currLang);

// 加载 Sound Bank
DLLEXPORT AKRESULT LoadBank_ID(AkBankID bankID);

// 加载 Sound Bank 并返回散列的 Bank ID
DLLEXPORT AKRESULT LoadBank_Name(const char* bankName, AkBankID& out_bankID);

/* 回调函数版本待补充 */
// 以 ID 卸载 Sound Bank
DLLEXPORT AKRESULT UnloadBank_ID(AkBankID bankID, const void* pInMemoryBankPtr);

// 以名称卸载 Sound Bank
DLLEXPORT AKRESULT UnloadBank_Name(const char* bankName, const void* pInMemoryBankPtr);

// 以 ID 注册 Game Object
DLLEXPORT AKRESULT RegisterGameObj(AkGameObjectID objID);

// 以 ID 注册 Game Object 并命名
DLLEXPORT AKRESULT RegisterNamedGameObj(AkGameObjectID objID, const char* objName);

// 注销 Game Object
DLLEXPORT AKRESULT UnregisterGameObj(AkGameObjectID objID);

// 注销所有 Game Object
DLLEXPORT AKRESULT UnregisterAllGameObj();

// 以 Event ID 发送 Event
DLLEXPORT AkPlayingID PostEvent_ID(AkUniqueID eventID,
	AkGameObjectID objectID,
	AkUInt32 uFlags = 0,
	//AkCallbackFunc pCallback = nullptr,
	void* pCookie = nullptr,
	AkUInt32 cExternals = 0,
	//AkExternalSourceInfo* pExternalSources = nullptr,
	AkPlayingID playingID = AK_INVALID_PLAYING_ID
);

// 以 Event 名称发送 Event
DLLEXPORT AkPlayingID PostEvent_Name(const char* eventName,
	AkGameObjectID objectID,
	AkUInt32 uFlags = 0,
	//AkCallbackFunc pCallback = nullptr,
	void* pCookie = nullptr,
	AkUInt32 cExternals = 0,
	//AkExternalSourceInfo* pExternalSources = nullptr,
	AkPlayingID playingID = AK_INVALID_PLAYING_ID
);

// Executes an action on all nodes that are referenced in the specified event in an action of type play.
// Using ID
DLLEXPORT AKRESULT ExecuteActionOnEvent_ID(AkUniqueID eventID, 
	AK::SoundEngine::AkActionOnEventType eActonType,
	AkGameObjectID objID, AkTimeMs transitionDuration,
	AkCurveInterpolation eFadeCurve, AkPlayingID playingID);

// Executes an action on all nodes that are referenced in the specified event in an action of type play.
// Using Name
DLLEXPORT AKRESULT ExecuteActionOnEvent_Name(const char* eventName,
	AK::SoundEngine::AkActionOnEventType eActonType,
	AkGameObjectID objID, AkTimeMs transitionDuration,
	AkCurveInterpolation eFadeCurve, AkPlayingID playingID);

// 渲染音频
DLLEXPORT AKRESULT RenderAudio();

// 准备事件
DLLEXPORT AKRESULT PrepareEvent_ID(AK::SoundEngine::PreparationType preparationType, 
	AkUniqueID* eventIDs, AkUInt32 numOfEvents);

DLLEXPORT AKRESULT PrepareEvent_Name(AK::SoundEngine::PreparationType preparationType, 
	const char** eventNames, AkUInt32 numOfEvents);

// 准备 Game Sync
DLLEXPORT AKRESULT PrepareGameSyncs_ID(AK::SoundEngine::PreparationType preparationType, 
	AkGroupType gameSyncType, AkUInt32 groupID, AkUInt32* gameSyncIDs, AkUInt32 numOfSyncs);

DLLEXPORT AKRESULT PrepareGameSyncs_Name(AK::SoundEngine::PreparationType preparationType, 
	AkGroupType gameSyncType, const char* groupName, const char** gameSyncNames, AkUInt32 numOfSyncs);

// 设置默认 Listener: 默认 Emitter 可被所有 Listener 听到
DLLEXPORT AKRESULT SetDefaultListeners(const AkGameObjectID* listenerObjs, AkUInt32 numOfListeners);

// 为 Emitter 设置 Listener
DLLEXPORT AKRESULT SetListeners(AkGameObjectID emitterObj, const AkGameObjectID* listenerObjs, AkUInt32 numOfListeners);

// 设置 Game Object 位置
DLLEXPORT AKRESULT SetPosition(AkGameObjectID objID, 
	AkReal32 posX, AkReal32 posY, AkReal32 posZ,
	AkReal32 oriFrontX, AkReal32 oriFrontY, AkReal32 oriFrontZ,
	AkReal32 oriTopX, AkReal32 oriTopY, AkReal32 oriTopZ);

// 为 Game Object 设置多个位置
public ref class CLI_SetMultiPosition
{
private:
	AkUInt16 numOfPos;
	AkGameObjectID objID;
	int eMultiPosType;
	AkTransform* pPositions;
public:

	// 设置 AkTransform 的数量 即 pPosition 数组大小
	// 并为 pPosition 分配内存
	bool Init(AkGameObjectID id, AkUInt16 cnt, int eType)
	{
		if (cnt <= 0)
		{
			return false;
		}

		numOfPos = cnt;
		objID = id;
		eMultiPosType = eType;
		pPositions = new AkTransform[numOfPos];
		return true;
	}

	// 由 C# 迭代，手动设置角标 iter 与各值
	bool SetGridVal(AkUInt32 iter, AkReal32 posX, AkReal32 posY, AkReal32 posZ,
		AkReal32 oriFrontX, AkReal32 oriFrontY, AkReal32 oriFrontZ,
		AkReal32 oriTopX, AkReal32 oriTopY, AkReal32 oriTopZ)
	{
		if (iter >= 0 && iter < numOfPos)
		{
			return false;
		}

		pPositions[iter].Set(posX, posY, posZ,
			oriFrontX, oriFrontY, oriFrontZ,
			oriTopX, oriTopY, oriTopZ);
		return true;
	}

	// 应用设置
	int Set()
	{
		return AK::SoundEngine::SetMultiplePositions(objID, pPositions, numOfPos, (AK::SoundEngine::MultiPositionType)eMultiPosType);
	}
};

// 以 RTPC ID 设置 RTPC 值
DLLEXPORT AKRESULT SetRTPCValue_ID(AkRtpcID rtpcID, AkRtpcValue rtpcVal,
	AkGameObjectID objID, AkTimeMs valChangeDuration = 0,
	AkCurveInterpolation eFadeCurve = AkCurveInterpolation_Linear,
	bool bBypassInternalValueInterpolation = false);

// 以 RTPC名称 设置 RTPC 值
DLLEXPORT AKRESULT SetRTPCValue_Name(const char* rtpcName, AkRtpcValue rtpcVal,
	AkGameObjectID objID, AkTimeMs valChangeDuration = 0,
	AkCurveInterpolation eFadeCurve = AkCurveInterpolation_Linear,
	bool bBypassInternalValueInterpolation = false);

// 以 RTPC ID 和 Playing ID 设置 RTPC 值
DLLEXPORT AKRESULT SetRTPCValueByPlayingID_ID(AkRtpcID rtpcID, AkRtpcValue rtpcVal,
	AkPlayingID playingID, AkTimeMs valChangeDuration = 0,
	AkCurveInterpolation eFadeCurve = AkCurveInterpolation_Linear,
	bool bBypassInternalValueInterpolation = false);

// 以 RTPC名称 和 Playing ID 设置 RTPC 值
DLLEXPORT AKRESULT SetRTPCValuebyPlayingID_Name(const char* rtpcName, AkRtpcValue rtpcVal,
	AkPlayingID playingID, AkTimeMs valChangeDuration = 0,
	AkCurveInterpolation eFadeCurve = AkCurveInterpolation_Linear,
	bool bBypassInternalValueInterpolation = false);

// 以 RTPC ID 重置 RTPC 值
DLLEXPORT AKRESULT ResetRTPCValue_ID(AkRtpcID rtpcID, AkGameObjectID objID,
	AkTimeMs valChangeDuration = 0, AkCurveInterpolation eFadeCurve = AkCurveInterpolation_Linear,
	bool bBypassInternalValueInterpolation = false);

// 以 RTPC名称 重置 RTPC 值
DLLEXPORT AKRESULT ResetRTPCValue_Name(const char* rtpcName, AkGameObjectID objID,
	AkTimeMs valChangeDuration = 0, AkCurveInterpolation eFadeCurve = AkCurveInterpolation_Linear,
	bool bBypassInternalValueInterpolation = false);

// 以 ID 为 State Group 设置 State
DLLEXPORT AKRESULT SetState_ID(AkStateGroupID stateGroupID, AkStateID stateID);

// 以 名称 为 State Group 设置 State
DLLEXPORT AKRESULT SetState_Name(const char* stateGroupName, const char* stateName);

// 以 ID 为 Game Object 的 Switch Group 设置 Switch State
DLLEXPORT AKRESULT SetSwitch_ID(AkSwitchGroupID switchGroupID, 
	AkSwitchStateID switchStateID, AkGameObjectID objID);

// 以 名称 为 Game Object 的 Switch Group 设置 Switch
DLLEXPORT AKRESULT SetSwitch_Name(const char* switchGroupName,
	const char* switchStateName, AkGameObjectID objID);

// 以 ID 调用 触发器
DLLEXPORT AKRESULT PostTrigger_ID(AkTriggerID triggerID, AkGameObjectID objID);

// 以 名称 调用 触发器
DLLEXPORT AKRESULT PostTrigger_Name(const char* triggerName, AkGameObjectID objID);

#endif //PCH_H
