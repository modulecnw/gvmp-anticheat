#include <vendor/math/SimpleMath.h>
#include <Windows.h>
#include <stdio.h> 
#include <string> 
#include <sstream> 
#include <iostream>

using namespace DirectX::SimpleMath;


static std::wstring asciiDecode(const std::string& s)
{
	std::wostringstream    w;
	wchar_t                c;

	for (size_t i = 0; i < s.length(); i++) {
		mbtowc(&c, &s[i], 1);
		w << c;
	}
	return w.str();
}

class CViewPort
{
public:
	char pad_0x0000[0x100]; //0x0000

	Matrix m_viewMatrix; //0x0100 
	Matrix m_projectionMatrix; //0x0140 
	char pad_0x0180[0xCC]; //0x0180
	Matrix m_viewProj; //0x024C 
	char pad_0x028C[0x1F8]; //0x028C

}; //Size=0x0484
static CViewPort* m_viewPort;
class GameViewMatrices;
class CPlayerInfo;
class CPlayers;
class CInventory;
class CWeaponManager;
class CObjectWrapper;
class CObject;
class CVehicleManager;
class CAttacker;
class CVehicleHandling;
class CVehicleColorOptions;
class CVehicleColors;
class CBoneManager;
class CModelInfo;
class CPedClothing;
class CNetGamePlayer;

inline unsigned int hash_string(std::string str)
{
	size_t len = str.size();
	unsigned int hash, i;
	for (hash = i = 0; i < len; ++i)
	{
		hash += tolower(str[i]);
		hash += (hash << 10);
		hash ^= (hash >> 6);
	}
	hash += (hash << 3);
	hash ^= (hash >> 11);
	hash += (hash << 15);
	return hash;
}
/*
typedef struct PVector3
{
	float x;
	DWORD _paddingx;
	float y;
	DWORD _paddingy;
	float z;
	DWORD _paddingz;

	PVector3(float x, float y, float z) :
		x(x), y(y), z(z),
		_paddingx(0), _paddingy(0), _paddingz(0)
	{
	}
	PVector3() noexcept : PVector3(0.f, 0.f, 0.f) {}
};
*/

/* CLASSES USED FROM PHANTOMCHEATS */

class CNetGamePlayer
{
public:
	char pad_0000[16]; //0x0000
	void* pCNonPhysicalPlayerData; //0x0010
	char pad_0018[21]; //0x0018
	int8_t m_PlayerID; //0x002D
	char pad_002E[122]; //0x002E
	CPlayerInfo* pCPlayerInfo; //0x00A8
}; //Size: 0x00B0

#include <string>
using namespace std;

class CRagePool;
class CRagePlayerPool;
class CRemotePlayer;

class CRagePool
{
public:
	CRagePlayerPool* PlayerPool; //0x0000 
	char pad_0x0008[0x38]; //0x0008

}; //Size=0x0040

class CRagePlayerPool
{
public:
	CRemotePlayer* N0000000B; //0x0000 
	char pad_0x0008[0x10]; //0x0008

}; //Size=0x0018


class CPedLink
{
public:
	char pad_0x0000[0x18]; //0x0000
	CObject* pPed; //0x0018 
	char pad_0x0020[0x28]; //0x0020

}; //Size=0x0048

class CRemotePlayer
{
public:
	char pad_0x0000[0x8]; //0x0000
	WORD Id; //0x0008 
	char pad_0x000A[0x7E]; //0x000A
	CPedLink* pPedLink; //0x0088 
	char pad_0x0090[0x378]; //0x0090

}; //Size=0x0408

class CObjectNavigation
{
public:
	char pad_0x0000[0x30]; //0x0000
	Vector3 Rotation; //0x0030 
	char pad_0x003C[0x14]; //0x003C
	Vector3 Position; //0x0050 
	char pad_0x005C[0x24]; //0x005C
}; //Size=0x0080


enum Bones {
	HEAD = 0x796E,
	NECK = 0x9995,
	RIGHT_HAND = 0xDEAD,
	RIGHT_FOREARM = 0x6E5C,
	RIGHT_UPPER_ARM = 0x9D4D,
	RIGHT_CLAVICLE = 0x29D2,

	LEFT_HAND = 0x49D9,
	LEFT_FOREARM = 0xEEEB,
	LEFT_UPPER_ARM = 0xB1C5,
	LEFT_CLAVICLE = 0xFCD9,

	PELVIS = 0x2E28,
	SPINE_ROOT = 0xE0FD,
	SPINE0 = 0x60F2,
	SPINE1 = 0x60F0,
	SPINE2 = 0x60F1,
	SPINE3 = 0x60F2,

	RIGHT_TOE = 0x512D,
	RIGHT_FOOT = 0xCC4D,
	RIGHT_CALF = 0x9000,
	RIGHT_THIGH = 0xCA72,
	LEFT_TOE = 0x083C,
	LEFT_FOOT = 0x3779,
	LEFT_CALF = 0xF9BB,
	LEFT_THIGH = 0xE39F
};

#define IsValidPtr(x) (x && !IsBadReadPtr(&x, sizeof(void*) && x != nullptr && x > nullptr))

class CReplayInterfaceVehicle
{
private:
	class VehicleHandle
	{
	public:
		CVehicleManager* vehicle; //0x0000 
		__int32 handle; //0x0008
		char _pad0[0x4];
	};//Size=0x0588

	class CVehicleList
	{
	public:
		VehicleHandle vehicles[0x100];//0x0000 
	};//Size=0x0490

public:
	char _0x0000[0x180];
	CVehicleList* vehicle_list; //0x0180
	__int32 max_vehicles; //0x0188 
	char _0x010C[0x4];
	__int32 number_of_vehicles; //0x0190 
	char _0x0114[0x34];

	CVehicleManager* get_vehicle(int index)
	{
		if (index <= 0xFF && IsValidPtr(vehicle_list) && IsValidPtr(vehicle_list->vehicles[index].vehicle))
			return (vehicle_list->vehicles[index].vehicle);
		else
			return nullptr;
	}
};

class CPickup
{
public:
	char pad_0x0000[0x30]; //0x0000
	CObjectNavigation* pCNavigation; //0x0030 
	char pad_0x0038[0x58]; //0x0038
	Vector3 v3VisualPos; //0x0090 
	char pad_0x009C[0x3F4]; //0x009C
	__int32 iValue; //0x0490 
	char pad_0x0494[0xC4]; //0x0494

}; //Size=0x0558

class CPickupHandle
{
public:
	CPickup* pCPickup; //0x0000 
	__int32 iHandle; //0x0008 
	char pad_0x000C[0x4]; //0x000C

}; //Size=0x0010

class CPickupList
{
public:
	CPickupHandle pickups[73]; //0x0000 

}; //Size=0x0490

class CPickupInterface
{
public:
	char pad_0x0000[0x100]; //0x0000
	CPickupList* pCPickupList; //0x0100 
	__int32 iMaxPickups; //0x0108 
	char pad_0x010C[0x4]; //0x010C
	__int32 iCurPickups; //0x0110 

	CPickup* get_pickup(int index)
	{
		if (IsValidPtr(pCPickupList) && IsValidPtr(pCPickupList->pickups[index].pCPickup) && pCPickupList->pickups[index].iHandle)
			return (pCPickupList->pickups[index].pCPickup);
		else
			return nullptr;
	}
}; //Size=0x0114

class CObjectInterface
{
private:
	class CObjectHandle
	{
	public:
		CObject* pCObject; //0x0000 
		__int32 iHandle; //0x0008 
		char pad_0x000C[0x4]; //0x000C

	}; //Size=0x0010

	class CObjectList
	{
	public:
		CObjectHandle ObjectList[3200]; //0x0000 

	}; //Size=0x8FC0

public:
	char pad_0x0000[0x158]; //0x0000
	CObjectList* pCObjectList; //0x0158 
	__int32 iMaxObjects; //0x0160 
	char pad_0x0164[0x4]; //0x0164
	__int32 iCurObjects; //0x0168 
	char pad_0x016C[0x5C]; //0x016C

	CObject* get_object(int index)
	{
		if (IsValidPtr(pCObjectList) && IsValidPtr(pCObjectList->ObjectList[index].pCObject) && pCObjectList->ObjectList[index].iHandle)
			return (pCObjectList->ObjectList[index].pCObject);
		else
			return nullptr;
	}


}; //Size=0x01C8

class CVehicleColors
{
public:
	char pad_0x0000[0xA4]; //0x0000
	BYTE btPrimaryBlue; //0x00A4 
	BYTE btPrimaryGreen; //0x00A5 
	BYTE btPrimaryRed; //0x00A6 
	BYTE btPrimaryAlpha; //0x00A7 
	BYTE btSecondaryBlue; //0x00A8 
	BYTE btSecondaryGreen; //0x00A9 
	BYTE btSecondaryRed; //0x00AA 
	BYTE btSecondaryAlpha; //0x00AB 

	void SetColor(BYTE p1, BYTE p2, BYTE p3, BYTE p5, BYTE p6, BYTE p7) {
		btPrimaryRed = p1;
		btPrimaryGreen = p2;
		btPrimaryBlue = p3;

		btSecondaryRed = p5;
		btSecondaryGreen = p6;
		btSecondaryBlue = p7;
	}

}; //Size=0x00AC

class CVehicleColorOptions
{
public:
	char pad_0x0000[0x20]; //0x0000
	CVehicleColors* CVehicleColor; //0x0020 

}; //Size=0x0028

class CCameraInterface
{
public:
	char pad_0x0000[0x248]; //0x0000

}; //Size=0x0248


static DWORD OFFvehSpeed = 0xB30;

class CModelInfo
{
public:
	char pad_0000[24]; //0x0000
	uint32_t Hash; //0x0018
	char pad_001C[20]; //0x001C
	Vector3 MinDim; //0x0030
	char pad_003C[4]; //0x003C
	Vector3 MaxDim; //0x0040
	char pad_004C[588]; //0x004C
	char Name[24]; //0x0298
	char pad_02A0[688]; //0x02A0
}; //Size: 0x0550

class CVehicleManager
{
public:
	char pad_0x0000[0x20]; //0x0000
	CModelInfo* ModelInfo; //0x0020 
	char pad_0x0028[0x8]; //0x0028
	CObjectNavigation* _ObjectNavigation; //0x0030 
	char pad_0x0038[0x10]; //0x0038
	CVehicleColorOptions* VehicleColorOptions; //0x0048 
	char pad_0x0050[0x40]; //0x0050
	Vector3 fPosition; //0x0090 
	char pad_0x009C[0x1E4]; //0x009C
	float fHealth; //0x0280 
	char pad_0x0284[0x1C]; //0x0284
	float fHealthMax; //0x02A0 
	char pad_0x02A4[0x4]; //0x02A4
	char pad_0x02F0[0x648]; //0x02F0
	CVehicleHandling* VehicleHandling; //0x0938 
	char pad_0x0940[0x31C]; //0x0940
	float fGravity; //0x0C5C 
	char pad_0x0C60[0x3EC]; //0x0C60
}; //Size=0x104C

class CWeaponName
{
public:
	char Name[20];
};

static DWORD OFFrecoil = 0x2E8;
static DWORD OFFspread = 0x84;
static DWORD OFFspread2 = 0x124;

class CWeaponInfo
{
public:
	char pad_0000[96]; //0x0000
	void* _AmmoInfo; //0x0060 //70
	char pad_0068[12]; //0x0068
	float Spread; //0x0074 //84
	char pad_0078[56]; //0x0078
	float Damage; //0x00B0 
	char pad_00B4[36]; //0x00B4
	float MinImpulse; //0x00D8 
	float MaxImpulse; //0x00DC
	char pad_00E0[52]; //0x00E0F
	float Velocity; //0x0114 
	int32_t BulitsPerShoot; //0x0118 
	float MultiBulitSpread; //0x011C 
	char pad_0120[12]; //0x0120
	float ReloadTimeMultiplier; //0x012C
	char pad_0130[4]; //0x0130
	float TimeToShoot; //0x0134 //144
	char pad_0138[404]; //0x0138
	//float RecoilFirstPerson; //0x02CC 
	char pad_02D0[8]; //0x02D0
	float RecoilThirdPerson; //0x02D8 //2E8
	char pad_02DC[772]; //0x02DC
	char* szWeaponName; //0x05E0 //5F0
	char pad_05E8[40]; //0x05E8


	//void SetCurrentAmmo(int32_t ammo) {
	//	if (IsValidPtr(_AmmoInfo)) {
	//	const DWORD64 ptr1 = reinterpret_cast<DWORD64>(_AmmoInfo);
	//		const DWORD64 ptr2 = *reinterpret_cast<DWORD64*>(ptr1 + 0x8);
	//		if (ptr2) {
	//			const DWORD64 ptr3 = *reinterpret_cast<DWORD64*>(ptr2 + 0x0);
	//			if (ptr3) {
	//				*(int32_t*)(ptr3 + 0x18) = 9999;
	//			}
	//		}
	//	}
	//}

	float get_spread() {
		return (*reinterpret_cast<float*>((char*)this + 0x88));
	}

	float get_velocity() {
		return (*reinterpret_cast<float*>((char*)this + 0x118));
	}
	float get_range() {
		return (*reinterpret_cast<float*>((char*)this + 0x28C));
	}

	std::string get_weapon_name() {
		CWeaponName* WeaponName = *reinterpret_cast<CWeaponName**>((char*)this + 0x5F0);
		if (IsValidPtr(WeaponName) && WeaponName->Name && *WeaponName->Name)
			return &WeaponName->Name[0];
		else
			return "UNARMED"; //Doing Animation...
	}

	//0x1D4 = Visual shoot animation radius
}; //Size: 0x0610
static CWeaponInfo* m_pCWeaponInfo = nullptr;
static CWeaponInfo m_CWeapon;

class CWeaponManager
{
public:
	char pad_0000[32]; //0x0000
	CWeaponInfo* _WeaponInfo; //0x0020
	char pad_0028[96]; //0x0028
	void* _CurrentWeapon; //0x0088
	char pad_0090[272]; //0x0090
	Vector3 Aiming_at_Cord; //0x01A0
	char pad_01AC[4]; //0x01AC
	Vector3 Last_Impact_Cord; //0x01B0
	char pad_01BC[44]; //0x01BC

	DWORD get_hash() {
		return (*reinterpret_cast<DWORD*>((char*)this + 0x18));
	}
}; //Size: 0x01E8

static DWORD64 Inf_Ammo = 0x0;
static DWORD InsideVehOffset = 0x14F3;


static DWORD OFFinVeh = 0xE52;
static DWORD OFFvehMgr = 0xD30;
static DWORD OFFweaponMgr = 0x10D8;
static DWORD OFFplayerInfoMgr = 0x10C8;
static DWORD OFFarmour = 0x14E0;
static DWORD OFFnoGravity = 0x1100;
static DWORD OFFpedType = 0x10B8;

class CPlayerBones {
public:
	Vector3 HEAD;
	Vector3 NECK;

	Vector3 RIGHT_HAND;
	Vector3 RIGHT_FOREARM;
	Vector3 RIGHT_UPPER_ARM;
	Vector3 RIGHT_CLAVICLE;

	Vector3 LEFT_HAND;
	Vector3 LEFT_FOREARM;
	Vector3 LEFT_UPPER_ARM;
	Vector3 LEFT_CLAVICLE;

	Vector3 PELVIS;
	Vector3 SPINE_ROOT;
	Vector3 SPINE0;
	Vector3 SPINE1;
	Vector3 SPINE2;
	Vector3 SPINE3;

	Vector3 RIGHT_TOE;
	Vector3	RIGHT_FOOT;
	Vector3	RIGHT_CALF;
	Vector3	RIGHT_THIGH;

	Vector3	LEFT_TOE;
	Vector3	LEFT_FOOT;
	Vector3	LEFT_CALF;
	Vector3	LEFT_THIGH;
};

/*
LineOneBegin = GetOffsetFromEntityInWorldCoords(pPed, -0.3, -0.3, -0.9)
			LineOneEnd = GetOffsetFromEntityInWorldCoords(pPed, 0.3, -0.3, -0.9)
			LineTwoBegin = GetOffsetFromEntityInWorldCoords(pPed, 0.3, -0.3, -0.9)
			LineTwoEnd = GetOffsetFromEntityInWorldCoords(pPed, 0.3, 0.3, -0.9)
			LineThreeBegin = GetOffsetFromEntityInWorldCoords(pPed, 0.3, 0.3, -0.9)
			LineThreeEnd = GetOffsetFromEntityInWorldCoords(pPed, -0.3, 0.3, -0.9)
			LineFourBegin = GetOffsetFromEntityInWorldCoords(pPed, -0.3, -0.3, -0.9)

			TLineOneBegin = GetOffsetFromEntityInWorldCoords(pPed, -0.3, -0.3, 0.8)
			TLineOneEnd = GetOffsetFromEntityInWorldCoords(pPed, 0.3, -0.3, 0.8)
			TLineTwoBegin = GetOffsetFromEntityInWorldCoords(pPed, 0.3, -0.3, 0.8)
			TLineTwoEnd = GetOffsetFromEntityInWorldCoords(pPed, 0.3, 0.3, 0.8)
			TLineThreeBegin = GetOffsetFromEntityInWorldCoords(pPed, 0.3, 0.3, 0.8)
			TLineThreeEnd = GetOffsetFromEntityInWorldCoords(pPed, -0.3, 0.3, 0.8)
			TLineFourBegin = GetOffsetFromEntityInWorldCoords(pPed, -0.3, -0.3, 0.8)

			ConnectorOneBegin = GetOffsetFromEntityInWorldCoords(pPed, -0.3, 0.3, 0.8)
			ConnectorOneEnd = GetOffsetFromEntityInWorldCoords(pPed, -0.3, 0.3, -0.9)
			ConnectorTwoBegin = GetOffsetFromEntityInWorldCoords(pPed, 0.3, 0.3, 0.8)
			ConnectorTwoEnd = GetOffsetFromEntityInWorldCoords(pPed, 0.3, 0.3, -0.9)
			ConnectorThreeBegin = GetOffsetFromEntityInWorldCoords(pPed, -0.3, -0.3, 0.8)
			ConnectorThreeEnd = GetOffsetFromEntityInWorldCoords(pPed, -0.3, -0.3, -0.9)
			ConnectorFourBegin = GetOffsetFromEntityInWorldCoords(pPed, 0.3, -0.3, 0.8)
			ConnectorFourEnd = GetOffsetFromEntityInWorldCoords(pPed, 0.3, -0.3, -0.9)
			*/


class CPlayerOffsets {

public:
	Vector3 left_bottom;
	Vector3 right_bottom;
	Vector3 left_top;
	Vector3 right_top;

	Vector3 line_three_start;
	Vector3 line_three_end;
	Vector3 line_four_start;
	Vector3 tline_one_start;
	Vector3 tline_one_end;
	Vector3 tline_two_start;
	Vector3 tline_two_end;
	Vector3 tline_three_start;
	Vector3 tline_three_end;
	Vector3 tline_four_start;
	Vector3 connector_one_start;
	Vector3 connector_one_end;
	Vector3 connector_two_start;
	Vector3 connector_two_end;
	Vector3 connector_three_start;
	Vector3 connector_three_end;
	Vector3 connector_four_start;
	Vector3 connector_four_end;
};

class CObject
{
public:
	char pad_0x0000[0x2C]; //0x0000
	BYTE btInvisibleSP; //0x002C 
	char pad_0x002D[0x1]; //0x002D
	BYTE btFreezeMomentum; //0x002E 
	char pad_0x002F[0x1]; //0x002F
	CObjectNavigation* _ObjectNavigation; //0x0030 
	char pad_0x0038[0x58]; //0x0038
	Vector3 fPosition; //0x0090 
	char pad_0x009C[0xED]; //0x009C
	BYTE GodModeToggle; //0x0189 
	char pad_0x018A[0xF6]; //0x018A
	float HP; //0x0280 
	char pad_0x0284[0x1C]; //0x0284
	float MaxHP; //0x02A0 
	char pad_0x02A4[0x4]; //0x02A4
	CAttacker* CAttacker; //0x02A8 
	char pad_0x02B0[0x70]; //0x02B0
	Vector3 v3Velocity; //0x0320 
	char pad_0x032C[0x9FC]; //0x032C
	CVehicleManager* VehicleManager; //0x0D28 
	char pad_0x0D30[0x378]; //0x0D30
	BYTE btNoRagdoll; //0x10A8 
	char pad_0x10A9[0xF]; //0x10A9
	CPlayerInfo* PlayerInfo; //0x10B8 
	char pad_0x10C0[0x8]; //0x10C0
	CWeaponManager* WeaponManager; //0x10C8 
	char pad_0x10D0[0x31C]; //0x10D0
	BYTE btSeatBelt; //0x13EC 
	char pad_0x13ED[0xB]; //0x13ED
	BYTE btSeatbeltWindshield; //0x13F8 
	char pad_0x13F9[0x72]; //0x13F9
	BYTE btIsInVehicle; //0x146B 
	char pad_0x146C[0x44]; //0x146C
	float Armor; //0x14B0 
	char pad_0x14B4[0x3C]; //0x14B4
	CVehicleManager* VehicleManager2; //0x14F0 

	bool is_ped() {
		return get_model_info()->Hash == hash_string("mp_m_freemode_01") || get_model_info()->Hash == hash_string("mp_m_freemode_01");
	}

	CPlayerInfo* get_player_info() {
		return *reinterpret_cast<CPlayerInfo**>((char*)this + OFFplayerInfoMgr);
	}

	CWeaponManager* get_weapon_manager() {
		return *reinterpret_cast<CWeaponManager**>((char*)this + OFFweaponMgr);
	}

	CVehicleManager* get_vehicle_manager() {
		return *reinterpret_cast<CVehicleManager**>((char*)this + OFFvehMgr);
	}

	float get_health() {
		return std::abs(*reinterpret_cast<float*>((char*)this + 0x280) - 100);
	}

	float get_armor() {
		return (*(float*)((char*)this + 0x14E0));
	}

	unsigned int get_pedtype()
	{
		__int32 ped_type = *(__int32*)((char*)this + OFFpedType);

		return (ped_type << 11 >> 25);
	}

	CModelInfo* get_model_info() {
		return (*reinterpret_cast<CModelInfo**>((char*)this + 0x20));
	}

	CBoneManager* get_bone_manager() {
		return (*(CBoneManager**)((char*)this + 0x180));
	}

	__m128i get_head_pos() {
		return (*(__m128i*)((char*)this + 0x430));
	}

	__m128i get_neck_pos() {
		return (*(__m128i*)((char*)this + 0x4A0));
	}

	__m128i get_stomach_pos() {
		return (*(__m128i*)((char*)this + 0x4B0));
	}

	__m128i get_head_above() {
		return (*(__m128i*)((char*)this + 0x4E0));
	}

}; //Size=0x14F8

class CBoneManager
{
public:
	Vector4 vecTrans1; //0x0000 
	Vector4 vecTrans2; //0x0010 
	Vector4 vecTrans3; //0x0020 
	Vector4 fPosition; //0x0030 

};//Size=0x0040

class CAttacker
{
public:
	CObject* CPed0; //0x0000 
	char pad_0x0008[0x10]; //0x0008
	CObject* CPed1; //0x0018 
	char pad_0x0020[0x10]; //0x0020
	CObject* CPed2; //0x0030 

}; //Size=0x0038

class CWantedData
{
public:
	char pad_0x0000[0x1C]; //0x0000
	float fWantedCanChange; //0x001C 
	char pad_0x0020[0x10]; //0x0020
	Vector3 v3WantedCenterPos; //0x0030 
	char pad_0x003C[0x4]; //0x003C
	Vector3 v3WantedCenterPos2; //0x0040 
	char pad_0x004C[0x38]; //0x004C
	BYTE btFlag0; //0x0084 
	BYTE btFlag1; //0x0085 
	BYTE btFlag2; //0x0086 
	BYTE btFlag3; //0x0087 
	char pad_0x0088[0xC]; //0x0088
	DWORD dwWantedLevelFake; //0x0094 
	DWORD dwWantedLevel; //0x0098 

}; //Size=0x00AC

class CPlayerInfo
{
public:
	char pad_0x0000[0xA4]; //0x0000
	char N00000382[32]; //0x2A1AE9C0 
	char pad_0x00C4[0x7C0]; //0x00C4
	__int32 FakeWanted; //0x0884 
	__int32 RealWanted; //0x0888 
	char pad_0x088C[0x7C]; //0x088C

	std::string GetPlayerName() {
		return N00000382;
	}
	std::string GetPlayerName2() {
		return N00000382;
	}

	void SetWanted(int lvl) {
		FakeWanted = lvl; //Dirt
		RealWanted = lvl; //Dirt
	}
	__int32 GetWanted() {
		return RealWanted;
	}

}; //Size=0x0908


class CReplayInterfacePed
{
private:
	class CPedList
	{
	private:
		struct Ped
		{
			CObject* ped;
			char _pad0[0x8];

			__int32 get_handle() {
				return *reinterpret_cast<__int32*>((char*)this + 0x8);
			}
		};

	public:
		Ped peds[0x100];
	};

public:
	char _pad0[0x100];			// 0000 - 0100
	CPedList* ped_list;			// 0100 - 0108
	int max_peds;				// 0108 - 010C
	char _pad1[0x4];			// 010C - 0110
	int number_of_peds;		// 0110 - 0114

	void for_each_player(const std::function<void(CObject*, int)> fn)
	{
		for (auto index = 0; index < 0x100; ++index) {
			if (IsValidPtr(ped_list) && IsValidPtr(ped_list->peds[index].ped)) {
				auto entity = (ped_list->peds[index].ped);

				if (IsValidPtr(entity) && IsValidPtr(entity->_ObjectNavigation))
					fn(entity, index);
			}
		}
	}


	CObject* get_ped(int index)
	{
		if (IsValidPtr(ped_list) && IsValidPtr(ped_list->peds[index].ped))
			return (ped_list->peds[index].ped);
		else
			return NULL;
	}

	__int32 get_ped_handle(int index)
	{
		if (IsValidPtr(ped_list) && IsValidPtr(ped_list->peds[index].ped))
			return (ped_list->peds[index].get_handle());
		else
			return NULL;
	}
};

class CReplayInterface
{
public:
	void* game_interface;
	CCameraInterface* camera_interface;
	CReplayInterfaceVehicle* vehicle_interface;
	CReplayInterfacePed* ped_interface;
	CPickupInterface* pickup_interface;
	CObjectInterface* object_interface;
};

class CPrimaryAmmoCount
{
public:
	char pad_0x0000[0x18]; //0x0000
	__int32 AmmoCount; //0x0018 
};//Size=0x0040

class CAmmoCount
{
public:
	CPrimaryAmmoCount* _PrimaryAmmoCount; //0x0000 
	char pad_0x0008[0x38]; //0x0008

};//Size=0x0040

class CAmmoInfo
{
public:
	char pad_0x0000[0x8]; //0x0000
	CAmmoCount* _AmmoCount; //0x0008 
	char pad_0x0010[0x18]; //0x0010
	__int32 AmmoMax; //0x0028 
	char pad_0x002C[0x40C]; //0x002C

}; //Size=0x0438

class CWeaponObject
{
public:
	char _0x0000[8];
	CAmmoInfo* m_pAmmoInfo; //0x0008 
	char _0x0010[16];
	__int32 m_iAmmo; //0x0020 
	char _0x0024[20];

};//Size=0x0038

class CInventory
{
public:
	char _0x0000[72];
	CWeaponObject** WeaponList; //0x0048 

	CWeaponObject* getWeapon(int index) {
		return (CWeaponObject*)WeaponList[index];
	}
};//Size=0x0050

class CObjectWrapper
{
public:
	char _0x0000[60];
	__int16 TeamId; //0x003C 
	char _0x0040[104];
	CPlayerInfo* playerInfo; //0x00A8 
	char _0x00B0[64];

	__int16 GetTeamId() {
		return TeamId;
	}

};//Size=0x00F0

class CPlayers
{
public:
	char _0x0000[376];
	__int32 numPlayersOnline; //0x0178 
	char _0x017C[4];
	CObjectWrapper* ObjectWrapperList[600]; //0x0180 

	CObject* getPlayer(int index) {
		//if (IsValidPtr(ObjectWrapperList[index]) && IsValidPtr(ObjectWrapperList[index]->playerInfo) && IsValidPtr(ObjectWrapperList[index]->playerInfo->pCPed))
		//	return ObjectWrapperList[index]->playerInfo->pCPed;
		//else
		return 0;
	}

	CPlayerInfo* getPlayerInfo(int index) {
		if (IsValidPtr(ObjectWrapperList[index]) && IsValidPtr(ObjectWrapperList[index]->playerInfo))
			return ObjectWrapperList[index]->playerInfo;
		return 0;
	}

	int GetNumPlayersOnline() {
		if (numPlayersOnline > 1 && numPlayersOnline <= 0x20)
			return numPlayersOnline;
		else
			return 0;
	}
};

class CWorld
{
public:
	char _0x0000[8];
	CObject* pLocalPlayer; //0x0008 

	CObject* get_local_player()
	{
		return IsValidPtr(pLocalPlayer) ? pLocalPlayer : nullptr;
	}

	bool is_main_menu_active()
	{
		return *reinterpret_cast<BYTE*>((char*)this + 0x238) ? true : false;
	}
};//Size=0x0016

class CWorldFactory {
public:
	CWorld* world;
};

class CGameCameraAngles;
class CCameraManagerAngles;
class CCameraAngles;
class CPlayerAngles;
class CPlayerCameraData;

class CCameraAngles
{
public:
	char pad_0x0000[0x2C0]; //0x0000
	CPlayerAngles* VehiclePointer1; //0x02C0 
	CPlayerAngles* VehiclePointer2; //0x02C8 
	char pad_0x02D0[0xF0]; //0x02D0
	CPlayerAngles* pMyFPSAngles; //0x03C0 
	char pad_0x03C8[0x10]; //0x03C8
	__int64 pTPSCamEDX; //0x03D8 
	char pad_0x03E0[0x60]; //0x03E0

}; //Size=0x0440

class CPlayerAngles
{
public:
	char pad_0x0000[0x10]; //0x0000
	CPlayerCameraData* CamData; //0x0010 
	char pad_0x0018[0x28]; //0x0018
	Vector3 CamRotFPS; //0x0040 
	char pad_0x004C[0x14]; //0x004C
	Vector3 CrosshairLocation; //0x0060 
	char pad_0x006C[0x24]; //0x006C
	float FOV; //0x0090 
	char pad_0x0094[0x33C]; //0x0094
	Vector3 CamRot; //0x03D0 
	char pad_0x03DC[0x64]; //0x03DC

	void SetRot(Vector3 set) {
		CamRot = set;
	}
	void SetRot2(Vector3 set) {
		CamRotFPS = set;
	}
}; //Size=0x0440

class CGameCameraAngles
{
public:
	CCameraManagerAngles* pMyCameraManagerAngles; //0x0000  
	char _0x0008[56];

};//Size=0x0040 

class CCameraManagerAngles
{
public:
	CCameraAngles* pMyCameraAngles; //0x0000  

	//void SetAim(Vector3 SetRot1, Vector3 SetRot2) {
	//	pMyCameraAngles->VehiclePointer1->CamRot = SetRot1;
	//	pMyCameraAngles->VehiclePointer2->CamRot = SetRot2;
	//}

};//Size=0x0008 


class CPlayerAnglesVehicle
{
public:
	char pad_0x0000[0x10]; //0x0000
	CPlayerCameraData* CamData; //0x0010 
	char pad_0x0018[0x48]; //0x0018
	Vector3 CrosshairLocation; //0x0060 
	char pad_0x006C[0x24]; //0x006C
	float FOV; //0x0090 
	char pad_0x0094[0x33C]; //0x0094
	Vector3 CamRot; //0x03D0 
	char pad_0x03DC[0x64]; //0x03DC

}; //Size=0x0440
static DWORD OffsetPadd = 0x60;


class CPlayerCameraData
{
public:
	char _0x0000[48];
	float Fov_Zoom; //0x0030 
	char _0x0034[36];
	__int32 m_ZoomState; //0x0058 1 = Normal, 0 = Zoom, 10000+ = FPS

};//Size=0x0548

class CVehicleHandling
{
public:
	char pad_0x0000[0xC]; //0x0000
	float fMass; //0x000C 
	char pad_0x0010[0x10]; //0x0010
	Vector3 v3CentreOfMassOffset; //0x0020 
	char pad_0x002C[0x4]; //0x002C
	Vector3 v3InertiaMult; //0x0030 
	char pad_0x003C[0x4]; //0x003C
	float fPercentSubmerged; //0x0040 
	char pad_0x0044[0x8]; //0x0044
	float fAcceleration; //0x004C 
	BYTE btInitialDriveGears; //0x0050 
	char pad_0x0051[0x3]; //0x0051
	float fDriveInertia; //0x0054 
	float fClutchChangeRateScaleUpShift; //0x0058 
	float fClutchChangeRateScaleDownShift; //0x005C 
	float fInitialDriveForce; //0x0060 
	char pad_0x0064[0x8]; //0x0064
	float fBrakeForce; //0x006C 
	char pad_0x0070[0x4]; //0x0070
	float fBrakeBiasFront; //0x0074 
	char pad_0x0078[0x4]; //0x0078
	float fHandBrakeForce; //0x007C 
	char pad_0x0080[0x8]; //0x0080
	float fTractionCurveMax; //0x0088 
	char pad_0x008C[0x4]; //0x008C
	float fTractionCurveMin; //0x0090 
	char pad_0x0094[0xC]; //0x0094
	float fTractionSpringDeltaMax; //0x00A0 
	char pad_0x00A4[0x4]; //0x00A4
	float fLowSpeedTractionLossMult; //0x00A8 
	float fCamberStiffnesss; //0x00AC 
	float fTractionBiasFront; //0x00B0 
	float fTwoMinus_fTractionBiasFront; //0x00B4 
	float fTractionLossMult; //0x00B8 
	float fSuspensionForce; //0x00BC 
	float fSuspensionCompDamp; //0x00C0 
	float fSuspensionReboundDamp; //0x00C4 
	float fSuspensionUpperLimit; //0x00C8 
	float fSuspensionLowerLimit; //0x00CC 
	char pad_0x00D0[0xC]; //0x00D0
	float fAntiRollBarForce; //0x00DC 
	char pad_0x00E0[0x8]; //0x00E0
	float fRollCentreHeightFront; //0x00E8 
	float fRollCentreHeightRear; //0x00EC 
	float fCollisionDamageMult; //0x00F0 
	float fWeaponDamageMult; //0x00F4 
	float fDeformationDamageMult; //0x00F8 
	float fEngineDamageMult; //0x00FC 
	float fPetrolTankVolume; //0x0100 
	float fOilVolume; //0x0104 
}; //Size=0x0108

enum ePedType
{
	PEDTYPE_PLAYER_0,                // michael 
	PEDTYPE_PLAYER_1,                // franklin 
	PEDTYPE_NETWORK_PLAYER,            // mp character 
	PEDTYPE_PLAYER_2,                // trevor 
	PEDTYPE_CIVMALE,
	PEDTYPE_CIVFEMALE,
	PEDTYPE_COP,
	PEDTYPE_GANG_ALBANIAN,
	PEDTYPE_GANG_BIKER_1,
	PEDTYPE_GANG_BIKER_2,
	PEDTYPE_GANG_ITALIAN,
	PEDTYPE_GANG_RUSSIAN,
	PEDTYPE_GANG_RUSSIAN_2,
	PEDTYPE_GANG_IRISH,
	PEDTYPE_GANG_JAMAICAN,
	PEDTYPE_GANG_AFRICAN_AMERICAN,
	PEDTYPE_GANG_KOREAN,
	PEDTYPE_GANG_CHINESE_JAPANESE,
	PEDTYPE_GANG_PUERTO_RICAN,
	PEDTYPE_DEALER,
	PEDTYPE_MEDIC,
	PEDTYPE_FIREMAN,
	PEDTYPE_CRIMINAL,
	PEDTYPE_BUM,
	PEDTYPE_PROSTITUTE,
	PEDTYPE_SPECIAL,
	PEDTYPE_MISSION,
	PEDTYPE_SWAT,
	PEDTYPE_ANIMAL,
	PEDTYPE_ARMY
};

enum ExplosionTypes
{
	EXPLOSION_GRENADE,
	EXPLOSION_GRENADELAUNCHER,
	EXPLOSION_STICKYBOMB,
	EXPLOSION_MOLOTOV,
	EXPLOSION_ROCKET,
	EXPLOSION_TANKSHELL,
	EXPLOSION_HI_OCTANE,
	EXPLOSION_CAR,
	EXPLOSION_PLANE,
	EXPLOSION_PETROL_PUMP,
	EXPLOSION_BIKE,
	EXPLOSION_DIR_STEAM,
	EXPLOSION_DIR_FLAME,
	EXPLOSION_DIR_WATER_HYDRANT,
	EXPLOSION_DIR_GAS_CANISTER,
	EXPLOSION_BOAT,
	EXPLOSION_SHIP_DESTROY,
	EXPLOSION_TRUCK,
	EXPLOSION_BULLET,
	EXPLOSION_SMOKEGRENADELAUNCHER,
	EXPLOSION_SMOKEGRENADE,
	EXPLOSION_BZGAS,
	EXPLOSION_FLARE,
	EXPLOSION_GAS_CANISTER,
	EXPLOSION_EXTINGUISHER,
	EXPLOSION_PROGRAMMABLEAR,
	EXPLOSION_TRAIN,
	EXPLOSION_BARREL,
	EXPLOSION_PROPANE,
	EXPLOSION_BLIMP,
	EXPLOSION_DIR_FLAME_EXPLODE,
	EXPLOSION_TANKER,
	EXPLOSION_PLANE_ROCKET,
	EXPLOSION_VEHICLE_BULLET,
	EXPLOSION_GAS_TANK,
	EXPLOSION_BIRD_CRAP
};

enum WeaponHashes
{
	WEAPON_ADVANCEDRIFLE = 0xAF113F99,
	WEAPON_AIRSTRIKE_ROCKET = 0x13579279,
	WEAPON_ANIMAL = 0xF9FBAEBE,
	WEAPON_APPISTOL = 0x22D8FE39,
	WEAPON_ASSAULTRIFLE = 0xBFEFFF6D,
	WEAPON_ASSAULTSHOTGUN = 0xE284C527,
	WEAPON_ASSAULTSMG = 0xEFE7E2DF,
	WEAPON_TEC9 = 0xDB1AA450,
	WEAPON_DOUBLEBARRELED = 0xDB1AA450,
	WEAPON_BALL = 0x23C9F95C,
	WEAPON_BARBED_WIRE = 0x48E7B178,
	WEAPON_BAT = 0x958A4A8F,
	WEAPON_BLEEDING = 0x8B7333FB,
	WEAPON_BOTTLE = 0xF9E6AA4B,
	WEAPON_BRIEFCASE = 0x88C78EB7,
	WEAPON_BRIEFCASE_02 = 0x01B79F17,
	WEAPON_BULLPUPRIFLE = 0x7F229F94,
	WEAPON_COMPACTRIFLE = 0x624FE830,
	WEAPON_BULLPUPSHOTGUN = 0x9D61E50F,
	WEAPON_BZGAS = 0xA0973D5E,
	WEAPON_CARBINERIFLE = 0x83BF0278,
	WEAPON_COMBATMG = 0x7FD62962,
	WEAPON_PARACHUTE = 0xFBAB5776,
	WEAPON_COMBATPDW = 0xA3D4D34,
	WEAPON_COMBATPISTOL = 0x5EF9FEC4,
	WEAPON_COUGAR = 0x08D4BE52,
	WEAPON_CROWBAR = 0x84BD7BFD,
	WEAPON_DAGGER = 0x92A27487,
	WEAPON_DIGISCANNER = 0xFDBADCED,
	WEAPON_DROWNING = 0xFF58C4FB,
	WEAPON_DROWNING_IN_VEHICLE = 0x736F5990,
	WEAPON_ELECTRIC_FENCE = 0x92BD4EBB,
	WEAPON_EXHAUSTION = 0x364A29EC,
	WEAPON_EXPLOSION = 0x2024F4E8,
	WEAPON_FALL = 0xCDC174B0,
	WEAPON_FIRE = 0xDF8E89EB,
	WEAPON_FIREEXTINGUISHER = 0x060EC506,
	WEAPON_FIREWORK = 0x7F7497E5,
	WEAPON_FLARE = 0x497FACC3,
	WEAPON_FLAREGUN = 0x47757124,
	WEAPON_GARBAGEBAG = 0xE232C28C,
	WEAPON_GOLFCLUB = 0x440E4788,
	WEAPON_GRENADE = 0x93E220BD,
	WEAPON_GRENADELAUNCHER = 0xA284510B,
	WEAPON_GRENADELAUNCHER_SMOKE = 0x4DD2DC56,
	WEAPON_GUSENBERG = 0x61012683,
	WEAPON_HAMMER = 0x4E875F73,
	WEAPON_HANDCUFFS = 0xD04C944D,
	WEAPON_HEAVYPISTOL = 0xD205520E,
	WEAPON_HEAVYSHOTGUN = 0x3AABBBAA,
	WEAPON_HEAVYSNIPER = 0x0C472FE2,
	WEAPON_HELI_CRASH = 0x145F1012,
	WEAPON_HIT_BY_WATER_CANNON = 0xCC34325E,
	WEAPON_HOMINGLAUNCHER = 0x63AB0442,
	WEAPON_KNIFE = 0x99B507EA,
	WEAPON_KNUCKLE = 0xD8DF3C3C,
	WEAPON_MARKSMANPISTOL = 0xDC4DB296,
	WEAPON_MARKSMANRIFLE = 0xC734385A,
	WEAPON_MG = 0x9D07F764,
	WEAPON_HATCHET = 0xF9DCBF2D,
	WEAPON_FLASHLIGHT = 0x8BB05FD7,
	WEAPON_MACHINEPISTOL = 0xDB1AA450,
	WEAPON_MACHETE = 0xDD5DF8D9,
	WEAPON_SWITCHBLADE = 0xDFE37640,
	WEAPON_REVOLVER = 0xC1B3C3D1,
	WEAPON_MICROSMG = 0x13532244,
	WEAPON_MINIGUN = 0x42BF8A85,
	WEAPON_MOLOTOV = 0x24B17070,
	WEAPON_MUSKET = 0xA89CB99E,
	WEAPON_NIGHTSTICK = 0x678B81B1,
	WEAPON_PASSENGER_ROCKET = 0x166218FF,
	WEAPON_PETROLCAN = 0x34A67B97,
	WEAPON_PISTOL = 0x1B06D571,
	WEAPON_PISTOL50 = 0x99AEEB3B,
	WEAPON_PROXMINE = 0xAB564B93,
	WEAPON_PUMPSHOTGUN = 0x1D073A89,
	WEAPON_RAILGUN = 0x6D544C99,
	WEAPON_RAMMED_BY_CAR = 0x07FC7D7A,
	WEAPON_REMOTESNIPER = 0x33058E22,
	WEAPON_RPG = 0xB1CA77B1,
	WEAPON_RUN_OVER_BY_CAR = 0xA36D413E,
	WEAPON_SAWNOFFSHOTGUN = 0x7846A318,
	WEAPON_SMG = 0x2BE6766B,
	WEAPON_SMOKEGRENADE = 0xFDBC8A50,
	WEAPON_SNIPERRIFLE = 0x05FC3C11,
	WEAPON_SNOWBALL = 0x787F0BB,
	WEAPON_SNSPISTOL = 0xBFD21232,
	WEAPON_SPECIALCARBINE = 0xC0A3098D,
	WEAPON_STICKYBOMB = 0x2C3731D9,
	WEAPON_STINGER = 0x687652CE,
	WEAPON_STUNGUN = 0x3656C8C1,
	WEAPON_UNARMED = 0xA2719263,
	WEAPON_VEHICLE_ROCKET = 0xBEFDC581,
	WEAPON_VINTAGEPISTOL = 0x083839C4
};

class CBlip
{
public:
	__int32 iID; //0x0000 
	__int8 iID2; //0x0004 
	char _0x0005[3];
	BYTE N000010FB; //0x0008 (80 = moves with player, some values will turn icon into map cursor and break it)
	char _0x0009[7];
	Vector3 v3Pos;
	char _0x001C[6];
	BYTE btFocused; //0x0022   (Focused? 0100 0000)
	char _0x0023[5];
	char* szMessage; //0x0028 If not null, contains the string of whatever the blip says when selected.
	char _0x0030[16];
	int iIcon; //0x0040
	char _0x0044[4];
	DWORD dwColor; //0x0048 (Sometimes works?)
	char _0x004C[4];
	float fScale; //0x0050 
	__int16 iRotation; //0x0054 Heading
	BYTE btInfoIDType; //0x0056 GET_BLIP_INFO_ID_TYPE
	BYTE btZIndex; //0x0057 
	BYTE btDisplay; //0x0058  Also Visibility 0010
	BYTE btAlpha; //0x0059
};//Size=0x005A

class CBlipList
{
public:
	CBlip* m_Blips[1500]; //0x0000 

};//Size=0x2F18

enum eBlipColor
{
	ColorWhite = 0,
	ColorRed = 1,
	ColorGreen = 2,
	ColorBlue = 3,
	ColorPlayer = 4,
	ColorYellow = 5,
	ColorPurple = 7,
	ColorVehicle = 38,
	ColorMichael = 42,
	ColorFranklin = 43,
	ColorTrevor = 44,
	ColorMissionRed = 49,
	ColorMissionVehicle = 54,
	ColorYellowMission = 66,
	ColorYellowMission2 = 60,
	ColorWaypoint = 84
};

enum eBlipSprite
{
	SpriteStandard = 1,
	SpriteBig = 2,
	SpritePoliceOfficer = 3,
	SpritePoliceArea = 4,
	SpriteSquare = 5,
	SpritePlayer = 6,
	SpriteNorth = 7,
	SpriteWaypoint = 8,
	SpriteBigCircle = 9,
	SpriteBigCircleOutline = 10,
	SpriteArrowUpOutlined = 11,
	SpriteArrowDownOutlined = 12,
	SpriteArrowUp = 13,
	SpriteArrowDown = 14,
	SpritePoliceHelicopterAnimated = 15,
	SpriteJet = 16,
	SpriteNumber1 = 17,
	SpriteNumber2 = 18,
	SpriteNumber3 = 19,
	SpriteNumber4 = 20,
	SpriteNumber5 = 21,
	SpriteNumber6 = 22,
	SpriteNumber7 = 23,
	SpriteNumber8 = 24,
	SpriteNumber9 = 25,
	SpriteNumber10 = 26,
	SpriteGTAOCrew = 27,
	SpriteGTAOFriendly = 28,
	SpriteLift = 36,
	SpriteRaceFinish = 38,
	SpriteSafehouse = 40,
	SpritePoliceOfficer2 = 41,
	SpritePoliceCarDot = 42,
	SpritePoliceHelicopter = 43,
	SpriteChatBubble = 47,
	SpriteGarage2 = 50,
	SpriteDrugs = 51,
	SpriteStore = 52,
	SpritePoliceCar = 56,
	SpritePolicePlayer = 58,
	SpritePoliceStation = 60,
	SpriteHospital = 61,
	SpriteHelicopter = 64,
	SpriteStrangersAndFreaks = 65,
	SpriteArmoredTruck = 66,
	SpriteTowTruck = 68,
	SpriteBarber = 71,
	SpriteLosSantosCustoms = 72,
	SpriteClothes = 73,
	SpriteTattooParlor = 75,
	SpriteSimeon = 76,
	SpriteLester = 77,
	SpriteMichael = 78,
	SpriteTrevor = 79,
	SpriteRampage = 84,
	SpriteVinewoodTours = 85,
	SpriteLamar = 86,
	SpriteFranklin = 88,
	SpriteChinese = 89,
	SpriteAirport = 90,
	SpriteBar = 93,
	SpriteBaseJump = 94,
	SpriteCarWash = 100,
	SpriteComedyClub = 102,
	SpriteDart = 103,
	SpriteFIB = 106,
	SpriteDollarSign = 108,
	SpriteGolf = 109,
	SpriteAmmuNation = 110,
	SpriteExile = 112,
	SpriteShootingRange = 119,
	SpriteSolomon = 120,
	SpriteStripClub = 121,
	SpriteTennis = 122,
	SpriteTriathlon = 126,
	SpriteOffRoadRaceFinish = 127,
	SpriteKey = 134,
	SpriteMovieTheater = 135,
	SpriteMusic = 136,
	SpriteMarijuana = 140,
	SpriteHunting = 141,
	SpriteArmsTraffickingGround = 147,
	SpriteNigel = 149,
	SpriteAssaultRifle = 150,
	SpriteBat = 151,
	SpriteGrenade = 152,
	SpriteHealth = 153,
	SpriteKnife = 154,
	SpriteMolotov = 155,
	SpritePistol = 156,
	SpriteRPG = 157,
	SpriteShotgun = 158,
	SpriteSMG = 159,
	SpriteSniper = 160,
	SpriteSonicWave = 161,
	SpritePointOfInterest = 162,
	SpriteGTAOPassive = 163,
	SpriteGTAOUsingMenu = 164,
	SpriteLink = 171,
	SpriteMinigun = 173,
	SpriteGrenadeLauncher = 174,
	SpriteArmor = 175,
	SpriteCastle = 176,
	SpriteCamera = 184,
	SpriteHandcuffs = 188,
	SpriteYoga = 197,
	SpriteCab = 198,
	SpriteNumber11 = 199,
	SpriteNumber12 = 200,
	SpriteNumber13 = 201,
	SpriteNumber14 = 202,
	SpriteNumber15 = 203,
	SpriteNumber16 = 204,
	SpriteShrink = 205,
	SpriteEpsilon = 206,
	SpritePersonalVehicleCar = 225,
	SpritePersonalVehicleBike = 226,
	SpriteCustody = 237,
	SpriteArmsTraffickingAir = 251,
	SpriteFairground = 266,
	SpritePropertyManagement = 267,
	SpriteAltruist = 269,
	SpriteEnemy = 270,
	SpriteChop = 273,
	SpriteDead = 274,
	SpriteHooker = 279,
	SpriteFriend = 280,
	SpriteBountyHit = 303,
	SpriteGTAOMission = 304,
	SpriteGTAOSurvival = 305,
	SpriteCrateDrop = 306,
	SpritePlaneDrop = 307,
	SpriteSub = 308,
	SpriteRace = 309,
	SpriteDeathmatch = 310,
	SpriteArmWrestling = 311,
	SpriteAmmuNationShootingRange = 313,
	SpriteRaceAir = 314,
	SpriteRaceCar = 315,
	SpriteRaceSea = 316,
	SpriteGarbageTruck = 318,
	SpriteMotorCycle = 348,
	SpriteSafehouseForSale = 350,
	SpritePackage = 351,
	SpriteMartinMadrazo = 352,
	SpriteEnemyHelicopter = 353,
	SpriteBoost = 354,
	SpriteDevin = 355,
	SpriteMarina = 356,
	SpriteGarage = 357,
	SpriteGolfFlag = 358,
	SpriteHangar = 359,
	SpriteHelipad = 360,
	SpriteJerryCan = 361,
	SpriteMasks = 362,
	SpriteHeistSetup = 363,
	SpriteIncapacitated = 364,
	SpritePickupSpawn = 365,
	SpriteBoilerSuit = 366,
	SpriteCompleted = 367,
	SpriteRockets = 368,
	SpriteGarageForSale = 369,
	SpriteHelipadForSale = 370,
	SpriteMarinaForSale = 371,
	SpriteHangarForSale = 372,
	SpriteBusiness = 374,
	SpriteBusinessForSale = 375,
	SpriteRaceBike = 376,
	SpriteParachute = 377,
	SpriteTeamDeathmatch = 378,
	SpriteRaceFoot = 379,
	SpriteVehicleDeathmatch = 380,
	SpriteBarry = 381,
	SpriteDom = 382,
	SpriteMaryAnn = 383,
	SpriteCletus = 384,
	SpriteJosh = 385,
	SpriteMinute = 386,
	SpriteOmega = 387,
	SpriteTonya = 388,
	SpritePaparazzo = 389,
	SpriteCrosshair = 390,
	SpriteCreator = 398,
	SpriteCreatorDirection = 399,
	SpriteAbigail = 400,
	SpriteBlimp = 401,
	SpriteRepair = 402,
	SpriteTestosterone = 403,
	SpriteDinghy = 404,
	SpriteFanatic = 405,
	SpriteInformation = 407,
	SpriteCaptureBriefcase = 408,
	SpriteLastTeamStanding = 409,
	SpriteBoat = 410,
	SpriteCaptureHouse = 411,
	SpriteJerryCan2 = 415,
	SpriteRP = 416,
	SpriteGTAOPlayerSafehouse = 417,
	SpriteGTAOPlayerSafehouseDead = 418,
	SpriteCaptureAmericanFlag = 419,
	SpriteCaptureFlag = 420,
	SpriteTank = 421,
	SpriteHelicopterAnimated = 422,
	SpritePlane = 423,
	SpriteJet2 = 424,
	SpritePlayerNoColor = 425,
	SpriteGunCar = 426,
	SpriteSpeedboat = 427,
	SpriteHeist = 428,
	SpriteStopwatch = 430,
	SpriteDollarSignCircled = 431,
	SpriteCrosshair2 = 432,
	SpriteDollarSignSquared = 434,
};



enum IntersectOptions {
	IntersectEverything = -1,
	IntersectMap = 1,
	IntersectMissionEntityAndTrain = 2,
	IntersectPeds1 = 4,
	IntersectPeds2 = 8,
	IntersectVehicles = 10,
	IntersectObjects = 16,
	IntersectVegetation = 256
};

enum eRockstarEvent
{
	REVENT_SCRIPT_ARRAY_DATA_VERIFY_EVENT,
	REVENT_REQUEST_CONTROL_EVENT,
	REVENT_GIVE_CONTROL_EVENT,
	REVENT_WEAPON_DAMAGE_EVENT,
	REVENT_REQUEST_PICKUP_EVENT,
	REVENT_REQUEST_MAP_PICKUP_EVENT,
	REVENT_GAME_CLOCK_EVENT,
	REVENT_GAME_WEATHER_EVENT,
	REVENT_RESPAWN_PLAYER_PED_EVENT,
	REVENT_GIVE_WEAPON_EVENT,
	REVENT_REMOVE_WEAPON_EVENT,
	REVENT_REMOVE_ALL_WEAPONS_EVENT,
	REVENT_VEHICLE_COMPONENT_CONTROL_EVENT,
	REVENT_FIRE_EVENT,
	REVENT_EXPLOSION_EVENT,
	REVENT_START_PROJECTILE_EVENT,
	REVENT_ALTER_WANTED_LEVEL_EVENT,
	REVENT_CHANGE_RADIO_STATION_EVENT,
	REVENT_RAGDOLL_REQUEST_EVENT,
	REVENT_PLAYER_TAUNT_EVENT,
	REVENT_PLAYER_CARD_STAT_EVENT,
	REVENT_DOOR_BREAK_EVENT,
	REVENT_SCRIPTED_GAME_EVENT,
	REVENT_REMOTE_SCRIPT_INFO_EVENT,
	REVENT_REMOTE_SCRIPT_LEAVE_EVENT,
	REVENT_MARK_AS_NO_LONGER_NEEDED_EVENT,
	REVENT_CONVERT_TO_SCRIPT_ENTITY_EVENT,
	REVENT_SCRIPT_WORLD_STATE_EVENT,
	REVENT_INCIDENT_ENTITY_EVENT,
	REVENT_CLEAR_AREA_EVENT,
	REVENT_CLEAR_RECTANGLE_AREA_EVENT,
	REVENT_NETWORK_REQUEST_SYNCED_SCENE_EVENT,
	REVENT_NETWORK_START_SYNCED_SCENE_EVENT,
	REVENT_NETWORK_UPDATE_SYNCED_SCENE_EVENT,
	REVENT_NETWORK_STOP_SYNCED_SCENE_EVENT,
	REVENT_GIVE_PED_SCRIPTED_TASK_EVENT,
	REVENT_GIVE_PED_SEQUENCE_TASK_EVENT,
	REVENT_NETWORK_CLEAR_PED_TASKS_EVENT,
	REVENT_NETWORK_START_PED_ARREST_EVENT,
	REVENT_NETWORK_START_PED_UNCUFF_EVENT,
	REVENT_NETWORK_SOUND_CAR_HORN_EVENT,
	REVENT_NETWORK_ENTITY_AREA_STATUS_EVENT,
	REVENT_NETWORK_GARAGE_OCCUPIED_STATUS_EVENT,
	REVENT_PED_CONVERSATION_LINE_EVENT,
	REVENT_SCRIPT_ENTITY_STATE_CHANGE_EVENT,
	REVENT_NETWORK_PLAY_SOUND_EVENT,
	REVENT_NETWORK_STOP_SOUND_EVENT,
	REVENT_NETWORK_PLAY_AIRDEFENSE_FIRE_EVENT,
	REVENT_NETWORK_BANK_REQUEST_EVENT,
	REVENT_REQUEST_DOOR_EVENT,
	REVENT_NETWORK_TRAIN_REQUEST_EVENT,
	REVENT_NETWORK_TRAIN_REPORT_EVENT,
	REVENT_NETWORK_INCREMENT_STAT_EVENT,
	REVENT_MODIFY_VEHICLE_LOCK_WORD_STATE_DATA,
	REVENT_REQUEST_PHONE_EXPLOSION_EVENT,
	REVENT_REQUEST_DETACHMENT_EVENT,
	REVENT_KICK_VOTES_EVENT,
	REVENT_GIVE_PICKUP_REWARDS_EVENT,
	REVENT_NETWORK_CRC_HASH_CHECK_EVENT,
	REVENT_BLOW_UP_VEHICLE_EVENT,
	REVENT_NETWORK_SPECIAL_FIRE_EQUIPPED_WEAPON,
	REVENT_NETWORK_RESPONDED_TO_THREAT_EVENT,
	REVENT_NETWORK_SHOUT_TARGET_POSITION,
	REVENT_VOICE_DRIVEN_MOUTH_MOVEMENT_FINISHED_EVENT,
	REVENT_PICKUP_DESTROYED_EVENT,
	REVENT_UPDATE_PLAYER_SCARS_EVENT,
	REVENT_NETWORK_CHECK_EXE_SIZE_EVENT,
	REVENT_NETWORK_PTFX_EVENT,
	REVENT_NETWORK_PED_SEEN_DEAD_PED_EVENT,
	REVENT_REMOVE_STICKY_BOMB_EVENT,
	REVENT_NETWORK_CHECK_CODE_CRCS_EVENT,
	REVENT_INFORM_SILENCED_GUNSHOT_EVENT,
	REVENT_PED_PLAY_PAIN_EVENT,
	REVENT_CACHE_PLAYER_HEAD_BLEND_DATA_EVENT,
	REVENT_REMOVE_PED_FROM_PEDGROUP_EVENT,
	REVENT_REPORT_MYSELF_EVENT,
	REVENT_REPORT_CASH_SPAWN_EVENT,
	REVENT_ACTIVATE_VEHICLE_SPECIAL_ABILITY_EVENT,
	REVENT_BLOCK_WEAPON_SELECTION,
	REVENT_NETWORK_CHECK_CATALOG_CRC,
	REVENT_END
};

enum eExplosionTag
{
	EXP_TAG_DONTCARE = -1,
	EXP_TAG_GRENADE,
	EXP_TAG_GRENADELAUNCHER,
	EXP_TAG_STICKYBOMB,
	EXP_TAG_MOLOTOV,
	EXP_TAG_ROCKET,
	EXP_TAG_TANKSHELL,
	EXP_TAG_HI_OCTANE,
	EXP_TAG_CAR,
	EXP_TAG_PLANE,
	EXP_TAG_PETROL_PUMP,
	EXP_TAG_BIKE,
	EXP_TAG_DIR_STEAM,
	EXP_TAG_DIR_FLAME,
	EXP_TAG_DIR_WATER_HYDRANT,
	EXP_TAG_DIR_GAS_CANISTER,
	EXP_TAG_BOAT,
	EXP_TAG_SHIP_DESTROY,
	EXP_TAG_TRUCK,
	EXP_TAG_BULLET,
	EXP_TAG_SMOKEGRENADELAUNCHER,
	EXP_TAG_SMOKEGRENADE,
	EXP_TAG_BZGAS,
	EXP_TAG_FLARE,
	EXP_TAG_GAS_CANISTER,
	EXP_TAG_EXTINGUISHER,
	EXP_TAG_PROGRAMMABLEAR,
	EXP_TAG_TRAIN,
	EXP_TAG_BARREL,
	EXP_TAG_PROPANE,
	EXP_TAG_BLIMP,
	EXP_TAG_DIR_FLAME_EXPLODE,
	EXP_TAG_TANKER,
	EXP_TAG_PLANE_ROCKET,
	EXP_TAG_VEHICLE_BULLET,
	EXP_TAG_GAS_TANK,
	EXP_TAG_BIRD_CRAP,
	EXP_TAG_RAILGUN,
	EXP_TAG_BLIMP2,
	EXP_TAG_FIREWORK,
	EXP_TAG_SNOWBALL,
	EXP_TAG_PROXMINE,
	EXP_TAG_VALKYRIE_CANNON,
	EXP_TAG_AIR_DEFENCE,
	EXP_TAG_PIPEBOMB,
	EXP_TAG_VEHICLEMINE,
	EXP_TAG_EXPLOSIVEAMMO,
	EXP_TAG_APCSHELL,
	EXP_TAG_BOMB_CLUSTER,
	EXP_TAG_BOMB_GAS,
	EXP_TAG_BOMB_INCENDIARY,
	EXP_TAG_BOMB_STANDARD,
	EXP_TAG_TORPEDO,
	EXP_TAG_TORPEDO_UNDERWATER,
	EXP_TAG_BOMBUSHKA_CANNON,
	EXP_TAG_BOMB_CLUSTER_SECONDARY,
	EXP_TAG_HUNTER_BARRAGE,
	EXP_TAG_HUNTER_CANNON,
	EXP_TAG_ROGUE_CANNON,
	EXP_TAG_MINE_UNDERWATER,
	EXP_TAG_ORBITAL_CANNON,
	EXP_TAG_BOMB_STANDARD_WIDE,
	EXP_TAG_EXPLOSIVEAMMO_SHOTGUN,
	EXP_TAG_OPPRESSOR2_CANNON,
	EXP_TAG_MORTAR_KINETIC,
	EXP_TAG_VEHICLEMINE_KINETIC,
	EXP_TAG_VEHICLEMINE_EMP,
	EXP_TAG_VEHICLEMINE_SPIKE,
	EXP_TAG_VEHICLEMINE_SLICK,
	EXP_TAG_VEHICLEMINE_TAR,
	EXP_TAG_SCRIPT_DRONE,
	EXP_TAG_RAYGUN,
	EXP_TAG_BURIEDMINE,
	EXP_TAG_SCRIPT_MISSILE
};

enum PlateTextIndexs
{
	PLATE_BLUEONWHITE1,
	PLATE_YELLOWONBLACK,
	PLATE_YELLOWONBLUE,
	PLATE_BLUEONWHITE2,
	PLATE_BLUEONWHITE3,
	PLATE_YANKTON
};

enum VehicleModTypes
{
	MOD_SPOILER,
	MOD_FRONTBUMPER,
	MOD_REARBUMPER,
	MOD_SIDESKIRT,
	MOD_EXHAUST,
	MOD_CHASSIS, //Or roll cage
	MOD_GRILLE,
	MOD_HOOD,
	MOD_FENDER,
	MOD_RIGHTFENDER,
	MOD_ROOF,
	MOD_ENGINE,
	MOD_BRAKES,
	MOD_TRANSMISSION,
	MOD_HORNS,
	MOD_SUSPENSION,
	MOD_ARMOR,
	MOD_UNK17 = 17,
	MOD_TURBO = 18,
	MOD_UNK19 = 19,
	MOD_TIRESMOKE = 20,
	MOD_UNK21 = 21,
	MOD_XENONLIGHTS = 22,
	MOD_FRONTWHEELS = 23,
	MOD_BACKWHEELS = 24, //Bikes only

	// Benny's
	MOD_PLATEHOLDER = 25,
	MOD_VANITY_PLATES = 26,
	MOD_TRIM = 27,
	MOD_ORNAMENTS = 28,
	MOD_DASHBOARD = 29,
	MOD_DIAL = 30,
	MOD_DOOR_SPEAKER = 31,
	MOD_SEATS = 32,
	MOD_STEERINGWHEEL = 33,
	MOD_SHIFTER_LEAVERS = 34,
	MOD_PLAQUES = 35,
	MOD_SPEAKERS = 36,
	MOD_TRUNK = 37,
	MOD_HYDRULICS = 38,
	MOD_ENGINE_BLOCK = 39,
	MOD_AIR_FILTER = 40,
	MOD_STRUTS = 41,
	MOD_ARCH_COVER = 42,
	MOD_AERIALS = 43,
	//MOD_TRIM = 44,
	MOD_TANK = 45,
	MOD_WINDOWS = 46,
	MOD_UNK47 = 47,
	MOD_LIVERY = 48
};

enum HighEndWheels
{
	WHEEL_HIGHEND_STOCK = -1,
	WHEEL_HIGHEND_SHADOW,
	WHEEL_HIGHEND_HYPHER,
	WHEEL_HIGHEND_BLADE,
	WHEEL_HIGHEND_DIAMOND,
	WHEEL_HIGHEND_SUPAGEE,
	WHEEL_HIGHEND_CHROMATICZ,
	WHEEL_HIGHEND_MERCIECHLIP,
	WHEEL_HIGHEND_OBEYRS,
	WHEEL_HIGHEND_GTCHROME,
	WHEEL_HIGHEND_CHEETAHR,
	WHEEL_HIGHEND_SOLAR,
	WHEEL_HIGHEND_SPLITTEN,
	WHEEL_HIGHEND_DASHVIP,
	WHEEL_HIGHEND_LOZSPEEDTEN,
	WHEEL_HIGHEND_CARBONINFERNO,
	WHEEL_HIGHEND_CARBONSHADOW,
	WHEEL_HIGHEND_CARBONZ,
	WHEEL_HIGHEND_CARBONSOLAR,
	WHEEL_HIGHEND_CARBONCHEETAHR,
	WHEEL_HIGHEND_CARBONSRACER
};


class CWaterDataItem
{
public:
	__int16 iMinX; //0x0000 X Coord 1
	__int16 iMinY; //0x0002  Y Coord 1
	__int16 iMaxX; //0x0004 X Coord 2
	__int16 iMaxY; //0x0006 Y Coord 2
	__int8 iAlphaSW; //0x0008  (South West, default 26)
	__int8 iAlphaSE; //0x0009  (South East, default 26)
	__int8 iAlphaNW; //0x000A  (North West, default 26)
	__int8 iAlphaNE; //0x000B  (North East, default 26)
	char _0x000C[8]; // (Unknown, appear to be two floats?)
	float fHeight; //0x0014 (Z-Height, default 0.0)
	BYTE bHasLimitedDepth; //0x0018  (Second bit [binary 10] = On, gives the water quad an effective range of 6 z-points)
	char _0x0019[3]; // (Unknown)
};//Size=0x001C

class CWaterTune
{
public:
	DWORD dwWaterColor; //0x0000  Default: 0x1A00191C
	float fRippleScale; //0x0004  Default: 0.040000f
	float fOceanFoamScale; //0x0008  Default: 0.050000f
	float fSpecularFalloff; //0x000C  Default: 1118.000000f
	float fFodPierceIntensity; //0x0010  Default: 1.100000f
	float fRefractionBlend; //0x0014  Default: 0.700000f
	float fRefractionExponent; //0x0018  Default: 0.250000f
	float fWaterCycleDepth; //0x001C  Default: 10.000000f
	float fWaterCycleFade; //0x0020  Default: 50.000000f
	float fWaterLightningDepth; //0x0024  Default: 0.000000f
	float fWaterLightningFade; //0x0028  Default: 10.000000f
	float fDeepWaterModDepth; //0x002C  Default: 90.000000f
	float fDeepWaterModFade; //0x0030  Default: 80.000000f
	float fGodRaysLerpStart; //0x0034  Default: 0.000000f
	float fGodRaysLerpEnd; //0x0038  Default: 200.000000f
	float fDisturbFoamScale; //0x003C  Default: 0.050000f
	Vector2 vec2FogMin; //0x0040  Default: x = -4000.000000 y = -4000.000000
	Vector2 vec2FogMax; //0x0048  Default: x = 4500.000000 y= 8000.000000
};//Size=0x0050

struct n_ped_t {
	int32_t index;

	CObject* ped;
	CPlayerBones ped_bones;
	CPlayerOffsets ped_offsets;

	bool is_visible;
};

enum game_state_t
{
	playing,
	intro,
	unk,
	license,
	main_menu,
	load_online
};

enum class thread_state_t : std::uint32_t
{
	idle,
	running,
	killed,
	unk_3,
	unk_4,
};

class thread_context_t
{
public:
	std::uint32_t m_thread_id;
	std::uint32_t m_script_hash; // + 4 (program id)
	thread_state_t m_state; // + 8
	std::uint32_t m_instruction_pointer; // 0x0C
	std::uint32_t m_frame_pointer;       // 0x10
	std::uint32_t m_stack_pointer;       // 0x14
	float m_timer_a;                     // 0x18
	float m_timer_b;                     // 0x1C
	float m_timer_c;                     // 0x20
	char m_padding1[0x2C];               // 0x24
	std::uint32_t m_stack_size;          // 0x50
	char m_padding2[0x54];               // 0x54
};

template<typename type>
class array_collection
{
private:
	type* data;
	uint16_t	count;
	uint16_t	size;

public:
	type* begin()
	{
		return data;
	}

	type* end()
	{
		return (data + count);
	}

	type* at(uint16_t index)
	{
		return &data[index];
	}
};
