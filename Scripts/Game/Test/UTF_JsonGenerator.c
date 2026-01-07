static UTF_PlayerData GeneratePlayer(
	RandomGenerator rng,
	FuzzUIDRegistry registry
)
{
	UTF_PlayerData p = new UTF_PlayerData();

	p.playerReforgerUID = registry.GenerateUID();
	p.playerSteamUID = string.Format(
		"STEAM-%1",
		rng.RandIntInclusive(100000, 999999)
	);
	p.playerUTFID = string.Format(
		"UTF-%1",
		rng.RandIntInclusive(1000, 9999)
	);
	p.playerUTFName = string.Format(
		"User_%1",
		rng.RandIntInclusive(100, 999)
	);

	array<string> ranks = {
		"Private",
		"Corporal",
		"Sergeant",
		"Lieutenant"
	};

	p.playerRank = PickRandom(rng, ranks);

	return p;
}

static UTF_SlotData GenerateSlot(
	RandomGenerator rng,
	FuzzUIDRegistry registry
)
{
	UTF_SlotData slot = new UTF_SlotData();

	slot.isVacant = Chance(rng, 0.35);

	if (slot.isVacant)
	{
		slot.isLocked = Chance(rng, 0.2);
		slot.player = null;
	}
	else
	{
		slot.isLocked = false;
		slot.player = GeneratePlayer(rng, registry);
	}

	slot.isMA = Chance(rng, 0.1);
	slot.tierDifference = rng.RandIntInclusive(-1, 2);
	slot.loadout = null;

	// Role
	slot.role = new UTF_RoleData();
	slot.role.roleName = PickRandom(
		rng,
		{ "Squad Leader", "Rifleman", "Medic", "Autorifleman" }
	);
	slot.role.roleID = rng.RandIntInclusive(1, 100);

	return slot;
}

static UTF_ORBATData GenerateFuzzORBAT(
	int orbatID,
	int groupCount,
	int slotsPerGroup,
	int seed = 0
)
{
	RandomGenerator rng = new RandomGenerator();

	if (seed != 0)
		rng.SetSeed(seed);

	FuzzUIDRegistry registry = new FuzzUIDRegistry(rng);

	UTF_ORBATData orbat = new UTF_ORBATData();
	orbat.orbatID = orbatID;
	orbat.revision = rng.RandIntInclusive(1, 20);
	orbat.lastUpdate = "2026-01-01T18:00:00Z";
	orbat.startTime = "2026-01-01T19:00:00Z";
	orbat.missionName = string.Format("TEST_OP_%1", seed);
	orbat.factionId = rng.RandIntInclusive(1, 69);
	orbat.fieldLeader = "AUTO_FL";
	orbat.intelligenceOfficer = "AUTO_INTEL";
	orbat.serverAdmin = "AUTO_ADMIN";

	// Generate groups with slots
	orbat.groups = new array<ref UTF_GroupData>();
	for (int g = 0; g < groupCount; g++)
	{
		UTF_GroupData group = new UTF_GroupData();
		group.groupName = string.Format("GROUP_%1", g + 1);

		// Radio frequencies
		group.radioFrequencies = new array<float>();
		int freqCount = rng.RandIntInclusive(1, 3);
		for (int f = 0; f < freqCount; f++)
			group.radioFrequencies.Insert(rng.RandFloatXY(30.0, 80.0));

		// Slots
		group.slots = new array<ref UTF_SlotData>();
		for (int s = 0; s < slotsPerGroup; s++)
		{
			UTF_SlotData slot = new UTF_SlotData();

			slot.isVacant = Chance(rng, 0.35);

			if (slot.isVacant)
			{
				slot.isLocked = Chance(rng, 0.2);
				slot.player = null;
			}
			else
			{
				slot.isLocked = false;
				slot.player = GeneratePlayer(rng, registry);
			}

			slot.isMA = Chance(rng, 0.1);
			slot.tierDifference = rng.RandIntInclusive(-2, 4);
			slot.loadout = null;

			// Role
			slot.role = new UTF_RoleData();
			slot.role.roleName = PickRandom(rng, {  "Squad Leader", 
                                                    "Rifleman", 
                                                    "Medic", 
                                                    "Autorifleman",
                                                    "Grenadier",
                                                    "AT Specialist",
                                                    "Marksman" });
			slot.role.roleID = rng.RandIntInclusive(1, 100);

			group.slots.Insert(slot);
		}

		orbat.groups.Insert(group);
	}

	return orbat;
}

static string GenerateFuzzORBATJson(int seed)
{
	RandomGenerator rng = new RandomGenerator();
	rng.SetSeed(seed);

	int orbatID   = rng.RandIntInclusive(1000, 9999);
	int slotCount = rng.RandIntInclusive(10, 40);
	int groupCount = rng.RandIntInclusive(3, 6);

	UTF_ORBATData orbat = GenerateFuzzORBAT(
		orbatID,
		slotCount,
		groupCount,
		seed
	);

	SCR_JsonSaveContext ctx = new SCR_JsonSaveContext();
	if (!ctx.Write(orbat))
	{
		Print("[TEST] JSON serialisation failed");
		return string.Empty;
	}

	string json = ctx.ExportToString();
	Print(string.Format("[TEST] Seed: %1", seed));
	Print(json);

	return json;
}