#pragma once

#include "RE/B/BSAtomic.h"
#include "RE/B/BSTArray.h"
#include "RE/B/BSTHashMap.h"
#include "RE/B/BSTSingleton.h"
#include "RE/N/NiSmartPointer.h"
#include "RE/T/TESObjectCell.h"
#include "RE/T/TES.h"

namespace RE
{
	class NiNode;

	struct GrassType
	{
		BSMultiStreamInstanceTriShape* typeShape;        // 00
		ModelDBHandle                  typeModelHandle;  // 08
	};
	static_assert(sizeof(GrassType) == 0x10);

	class BGSGrassManager : public BSTSingletonSDM<BGSGrassManager>
	{
	public:
		static BGSGrassManager* GetSingleton()
		{
			static REL::Relocation<BGSGrassManager**> singleton{ RELOCATION_ID(514292, 400452) };
			return *singleton;
		}

		void ToggleGrass()
		{
			using ToggleGrass = void (*)(void);
			REL::Relocation<ToggleGrass> func{ REL::RelocationID(0 /* SE TBD */, 22866) };
			return func();
		}

		void RemoveAllGrass()
		{
			return TES::GetSingleton()->RemoveAllGrass();
		}

		void CreateAllGrass()
		{
			return TES::GetSingleton()->CreateAllGrass();
		}

		void RemoveGrassInCell(TESObjectCELL* cell)
		{
			using RemoveGrassInCell = void (*)(BGSGrassManager*, TESObjectCELL*);
			REL::Relocation<RemoveGrassInCell> func{ REL::RelocationID(15207, 15375) };
			return func(this, cell);
		}

		void CreateGrassInCell(TESObjectCELL* cell)
		{
			return cell->GenerateGrass();
		}

		void CreateGrassInCell(RE::TESObjectCELL* cell, std::uint8_t* bytePtr)
		{
			using GrassFunc_t = __int64 (*)(RE::BGSGrassManager* mgr, RE::TESObjectCELL* cell, std::uint8_t* bytePtr);
			REL::Relocation<GrassFunc_t> func{ RELOCATION_ID(15204, 15372) };
			func(this, cell, bytePtr);
		}

		void ExecuteAllGrassTasks(RE::TESObjectCELL* cell, std::int64_t flag)
		{
			using GrassFunc2_t = std::int64_t (*)(RE::BGSGrassManager* mgr, RE::TESObjectCELL* cell, std::int64_t flag);
			REL::Relocation<GrassFunc2_t> func{ RELOCATION_ID(15209, 15377) };
			func(this, cell, flag);
		}

		// members
		bool                                       generateGrassDataFiles;  // 01
		std::uint8_t                               unk02;                   // 02
		std::uint16_t                              unk04;                   // 04
		std::uint32_t                              unk08;                   // 08
		std::uint32_t                              unk0C;                   // 0C
		BSTFixedHashMap<std::uint64_t, GrassType*> grassTypeMap;            // 10
		mutable BSReadWriteLock                    grassTypeLock;           // 38
		mutable BSNonReentrantSpinLock             grassShapeLock;          // 40
		std::uint32_t                              pad44;                   // 44
		BSTArray<BSMultiStreamInstanceTriShape*>   grassShapes;             // 48
		float                                      totalGrassRange;         // 60
		std::uint32_t                              pad64;                   // 64
		NiPointer<NiNode>                          grassNode;               // 68
		std::uint32_t                              grassEvalSize;           // 70
		std::uint32_t                              grassEvalSizeSquared;    // 74
		std::uint32_t                              grassPatchSize;          // 78
		std::uint32_t                              unk7C;                   // 7C
		std::uint16_t*                             instanceData;            // 80
		bool                                       enableGrass;             // 88
	};
	static_assert(sizeof(BGSGrassManager) == 0x90);
}
