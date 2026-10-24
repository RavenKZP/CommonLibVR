#pragma once

#include "RE/B/BSAtomic.h"
#include "RE/B/BSTArray.h"
#include "RE/B/BSTHashMap.h"
#include "RE/B/BSTSingleton.h"
#include "RE/N/NiSmartPointer.h"
#include "RE/T/TES.h"
#include "RE/T/TESObjectCell.h"

namespace RE
{
	class NiNode;

	struct GrassType
	{
		BSMultiStreamInstanceTriShape* typeShape;        // 00
		ModelDBHandle                  typeModelHandle;  // 08
	};
	static_assert(sizeof(GrassType) == 0x10);

	struct GrassTypeID
	{
	public:
		constexpr GrassTypeID() noexcept :
			GrassTypeID(0, 0, 0)
		{}

		constexpr GrassTypeID(FormID a_formID, std::int16_t a_x, std::int16_t a_y) noexcept :
			formID(a_formID),
			cellX(a_x),
			cellY(a_y)
		{}

		[[nodiscard]] constexpr bool operator==(const GrassTypeID&) const noexcept = default;

		// members
		FormID       formID;  // 00
		std::int16_t cellX;   // 04
		std::int16_t cellY;   // 06
	};
	static_assert(sizeof(GrassTypeID) == 0x8);

	template <>
	struct BSCRC32_<GrassTypeID>
	{
	public:
		[[nodiscard]] std::uint32_t operator()(const GrassTypeID& a_key) const noexcept
		{
			return detail::GenerateCRC32(
				std::span(
					reinterpret_cast<const std::uint8_t*>(std::addressof(a_key)),
					sizeof(GrassTypeID)));
		}
	};

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

		void CreateGrassInCell(TESObjectCELL* cell)
		{
			return cell->GenerateGrass();
		}

		void ExecuteAllGrassTasks(RE::TESObjectCELL* cell, std::int64_t flag)
		{
			using GrassFunc2_t = std::int64_t (*)(RE::BGSGrassManager* mgr, RE::TESObjectCELL* cell, std::int64_t flag);
			REL::Relocation<GrassFunc2_t> func{ RELOCATION_ID(15209, 15377) };
			func(this, cell, flag);
		}

		void AddCellGrass(TESObjectCELL* a_cell, volatile bool* a_cancel)
		{
			using func_t = decltype(&BGSGrassManager::AddCellGrass);
			static REL::Relocation<func_t> func{ RELOCATION_ID(15204, 15372) };
			func(this, a_cell, a_cancel);
		}

		bool AddCellGrassFromBuffer(TESObjectCELL* a_cell)
		{
			using func_t = decltype(&BGSGrassManager::AddCellGrassFromBuffer);
			static REL::Relocation<func_t> func{ RELOCATION_ID(15205, 15373) };
			return func(this, a_cell);
		}

		bool AddCellGrassFromFile(TESObjectCELL* a_cell)
		{
			using func_t = decltype(&BGSGrassManager::AddCellGrassFromFile);
			static REL::Relocation<func_t> func{ RELOCATION_ID(15206, 15374) };
			return func(this, a_cell);
		}

		void RemoveCellGrass(TESObjectCELL* a_cell)
		{
			using func_t = decltype(&BGSGrassManager::RemoveCellGrass);
			static REL::Relocation<func_t> func{ RELOCATION_ID(15207, 15375) };
			func(this, a_cell);
		}

		// members
		bool                                     generateGrassDataFiles;  // 01
		std::uint8_t                             unk02;                   // 02
		std::uint16_t                            unk04;                   // 04
		std::uint32_t                            unk08;                   // 08
		std::uint32_t                            unk0C;                   // 0C
		BSTFixedHashMap<GrassTypeID, GrassType*> grassTypeMap;            // 10
		mutable BSReadWriteLock                  grassTypeLock;           // 38
		mutable BSNonReentrantSpinLock           grassShapeLock;          // 40
		std::uint32_t                            pad44;                   // 44
		BSTArray<BSMultiStreamInstanceTriShape*> grassShapes;             // 48
		float                                    totalGrassRange;         // 60
		std::uint32_t                            pad64;                   // 64
		NiPointer<NiNode>                        grassNode;               // 68
		std::uint32_t                            grassEvalSize;           // 70
		std::uint32_t                            grassEvalSizeSquared;    // 74
		std::uint32_t                            grassPatchSize;          // 78
		std::uint32_t                            unk7C;                   // 7C
		std::uint16_t*                           instanceData;            // 80
		bool                                     enableGrass;             // 88
	};
	static_assert(sizeof(BGSGrassManager) == 0x90);
}
