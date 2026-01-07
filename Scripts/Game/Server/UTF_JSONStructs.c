class UTF_LoadoutData : JsonApiStruct
{
	// @TODO: figure out loadout structure
	void UTF_LoadoutData()
	{
	}
}

class UTF_PlayerData : JsonApiStruct
{
	string playerReforgerUID;
	string playerSteamUID;
	string playerUTFID;
	string playerUTFName;
	string playerRank;

	void UTF_()
	{
		RegV("reforgerUID");
		RegV("steamUID");
		RegV("UTFID");
		RegV("UTFName");
		RegV("rank");
	}
}

class UTF_RoleData : JsonApiStruct
{
    string roleName;
    int roleID;

    void UTF_RoleData()
    {
        RegV("roleName");
        RegV("roleID");
    }
}

class UTF_SlotData : JsonApiStruct
{
    ref UTF_PlayerData player;
	ref UTF_RoleData role;
    int tierDifference;
	bool isMA;
	bool isLocked;
	bool isVacant;
	ref UTF_LoadoutData loadout;

	void UTF_SlotData()
    {
		RegV("player");
		RegV("role");
		RegV("isMA");
		RegV("tierDifference");
		RegV("isLocked");
		RegV("isVacant");
		RegV("loadout");
    }
}

class UTF_GroupData : JsonApiStruct
{
	string groupName;
    ref array<ref UTF_SlotData> slots;
	ref array<float> radioFrequencies;

	void UTF_GroupData()
	{
		RegV("group");
        RegV("slots");
		RegV("radioFrequencies");
	}
}

class UTF_Metadata : JsonApiStruct
{
    // @TODO: decide if any metadata makes sense to include
	void UTF_Metadata()
	{
	}
}

class UTF_ORBATData : JsonApiStruct
{
    int orbatID;                
    int revision;               // incremented on each change
    string lastUpdate;          // ISO 8601 format
	string startTime;           // ISO 8601 format
    string missionName;
    int factionId;
    string fieldLeader;
	string intelligenceOfficer;
	string serverAdmin;
	ref array<ref UTF_GroupData> groups;
	ref UTF_Metadata metadata;
	
	void UTF_ORBATData()
	{
		groups = new array<ref UTF_GroupData>();
		metadata = new UTF_Metadata();
		
        RegV("orbatID");
        RegV("revision");
        RegV("lastUpdate");
		RegV("startTime");
        RegV("missionName");
        RegV("factionId");
        RegV("intelligenceOfficer");
        RegV("fieldLeader");
        RegV("serverAdmin");
		RegV("groups");
		RegV("metadata");
	}
}