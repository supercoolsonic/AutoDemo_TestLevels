#include "stdafx.h"
#include <cmath>

//LandTables
#include "LandTable\Act1.h"
#include "LandTable\Act2.h"
#include "LandTable\Act3.h"

//Objects
#include "ObjModels\Objects.h"

//Misc
#include "MiscFiles\StartPos.h"
#include "IniFile.hpp"

//Replacement Functions
#define ReplaceBINFile(a, b) helperFunctions.ReplaceFile("system\\" a ".BIN", "system\\" b ".BIN");


//Config Variables
/*
static bool ADSetFile = true;
*/

//Additional SADX Variables
DataArray(FogData, FogData_HedgehogHammer, 0x027C69C4, 3); //from PkR

DataPointer(int, DroppedFrames, 0x03B1117C);

//Additional SADX Functions
FunctionPointer(int, rand1, (), 0x6443BF);
DataPointer(int, FramerateSetting, 0x0389D7DC);

bool ChangeGeo = false;


//Null Code (Used for debugging purposes)
void __cdecl NullFunction(ObjectMaster *a1)
{
	return;
}
/*
PointerInfo pointers[] = {
	0
};
*/

void Init(const char *path, const HelperFunctions &helperFunctions)
{
	//Replacing BIN Files
	ReplaceBINFile("SET0000A", "SET0000A_AD");
	ReplaceBINFile("SET0000S", "SET0000S_AD");
	ReplaceBINFile("SET0001S", "SET0001S_AD");
	ReplaceBINFile("SET0002S", "SET0002S_AD");


	WriteData((LandTable**)0x97DA08, &landtable_0000006C); //Act 1
	//WriteData((LandTable**)0x97DA14, &landtable_0000006C); //Act 1
	WriteData((LandTable**)0x97DA0C, &landtable_00000120);
	WriteData((LandTable**)0x97DA10, &landtable_000002F8);

	//helperFunctions.RegisterStartPosition(Characters_Amy, amyTestLevel0);
}

extern "C"
{
	__declspec(dllexport) ModInfo SADXModInfo = { ModLoaderVer, &Init, NULL, 0, NULL, 0, NULL, 0, 0 };

	__declspec(dllexport) void cdecl Init()
	{
		for (int i = 0; i < 3; i++)
		{
			FogData_HedgehogHammer[i].Distance = 16000.0f;
			FogData_HedgehogHammer[i].Layer = 5000.0f;
		}
	}

	__declspec(dllexport) void __cdecl OnFrame()
	{
		if (EntityData1Ptrs[0] != nullptr && GetCharacterID(0) != 5 && ChangeGeo == false)
		{
			if (CurrentLevel == 0)
			{
				for (int i = 3; i < 74; i++)
				{
					collist_00000000[i].Flags = 0x0;
				}
				ChangeGeo = true;
			}
		}

		else if (!(GameState == 3 || GameState == 4 || GameState == 7 || GameState == 21) && EntityData1Ptrs[0] == nullptr && ChangeGeo == true)
		{
			collist_00000000[3].Flags = 0x80000000;
			collist_00000000[4].Flags = 0x40000041;
			collist_00000000[5].Flags = 0x40000001;
			collist_00000000[6].Flags = 0xC0000001;
			collist_00000000[7].Flags = 0xC0000001;

			for (int i = 8; i < 74; i++)
			{
				collist_00000000[i].Flags = 0x80000000;
			}
			ChangeGeo = false;
		}

		if (!EntityData1Ptrs[0] && CurrentLevel == 0 && (ControllerPointers[0]->HeldButtons & Buttons_L))
		{
			CurrentAct = 1;
		}
		else if (!EntityData1Ptrs[0] && CurrentLevel == 0 && (ControllerPointers[0]->HeldButtons & Buttons_R))
		{
			CurrentAct = 2;
			
		}
		else if (!EntityData1Ptrs[0] && CurrentLevel == 0 && (ControllerPointers[0]->HeldButtons & Buttons_X))
		{
			CurrentAct = 0;
		}
	}
}