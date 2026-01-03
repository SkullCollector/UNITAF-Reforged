class PlayerData : JsonApiStruct
{
	string playerGameID;
	string playerUTFName;
	int playerUTFid;

	void PlayerData()
	{
		RegV("playerGameID");
		RegV("playerUTFName");
		RegV("playerUTFid");
	}
}
class SlotData : JsonApiStruct
{
	PlayerData player;
	string callSign;
	string role;
	string loadoutID;
	bool isMA;
	int tierDiff;

	void SlotData()
    {
		RegV("player");
		RegV("callSign");
		RegV("role");
		RegV("loadoutID");
		RegV("isMA");
		RegV("tierDiff");
    }
}

class CallSignData : JsonApiStruct
{
	string callSign;
	double primaryFrequency;
	double secondaryFrequency;
	double pogoFrequency;
	array<ref CallSignData> subordinateCallsigns;

	void CallSignData()
	{
		RegV("callSign");
		RegV("subordinateCallsigns");
		RegV("primaryFrequency");
		RegV("secondaryFrequency");
		RegV("pogoFrequency");
	}
}

class Metadata : JsonApiStruct
{
	string missionName;
	string startTime;
	string factionId;
	string intelligenceOfficer;
	string fieldLeader;

	void Metadata()
	{
		RegV("missionName");
		RegV("startTime");
		RegV("factionId");
		RegV("intelligenceOfficer");
		RegV("fieldLeader");
	}
}

class ORBATData : JsonApiStruct
{
	int orbatID;
	Metadata metadata;
	array<ref SlotData> slots;
	array<ref CallSignData> callSigns;
	
	void ORBATData()
	{
		RegV("orbatID");
		RegV("metadata");
		RegV("slots");
		RegV("callSigns");
	}
}


class ServerORBATManager
{
	ref UTF_HTTPService m_http;
	ref map<string, ref ORBATData> m_cache;

	void ServerORBATManager(UTF_HTTPService http)
	{
		m_http = http;
		m_cache = new map<string, ref ORBATData>;
	}

	// Fetch ORBAT data from remote service
	// @TODO: 	separating individual slot fetches after initial ORBAT structure
	// 			to reduce JSON container size (because of large loadout data)
	void FetchORBAT(string orbatID)
	{
		// @TODO: clarify actual API format
		string url = string.Format("%1/api/orbat/%2", "http:\/\/localhost:3000", orbatID);
		ORBATGetCallback cb = new ORBATGetCallback(this, orbatID);
		m_http.ExecuteGet(url, cb);
	}

	void OnOrbatJson(string orbatID, string json)
	{
		SCR_JsonLoadContext ctx = new SCR_JsonLoadContext;
		ctx.LoadString(json);

		ORBATData data = ParseORBAT(ctx);
		data.orbatID = orbatID;
		m_cache.Set(orbatID, data);
	}

	ORBATData ParseORBAT(SCR_JsonLoadContext ctx)
	{
		ORBATData data = new ORBATData();
		data.orbatID = ctx.ReadString("orbatID");
		data.slots = new array<ref SlotData>();
		data.callSigns = new array<ref CallSignData>();
		data.metadata = new Metadata();

		// Handle metadata
		// @TODO: figure out what metadata to include from endpoint
		string name;
		ctx.ReadString("name", name);
		data.metadata.Set("name", name);
		data.metadata.Set("slotsCount", slotsCount);

		// Handle slots
		// @TODO: Handle slots
		for (int i = 0; i < metadata.slotsCount; i++) {
			SCR_JsonLoadContext slotCtx = ctx.StartArray(i); // PROBABLY WRONG
			SlotData slot = new SlotData();
			slot.playerGameID = slotCtx.ReadString("playerGameID");
			slot.playerUTFName = slotCtx.ReadString("playerUTFName");
			slot.callSign = slotCtx.ReadString("callSign");
			data.slots.Insert(slot);
		}

	}

	void ApplyORBATtoPlayer(int playerID)
	{
		// @TODO: implement player ORBAT assignment
		// mostly pseudocode:
		string playerGameID = BackendApi.GetPlayerIdentityId(playerID);
	}

	void ApplyORBATtoAll(ORBATData data, bool nearRPrequired = true)
	{
		// @TODO: implement all-players ORBAT assignment
		// e.g. forced reset
	}
}