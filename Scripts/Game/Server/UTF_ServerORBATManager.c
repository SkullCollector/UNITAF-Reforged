class LoadoutData : JsonApiStruct
{
	// @TODO: figure out loadout structure
	void LoadoutData()
	{
		
	}
}

class PlayerData : JsonApiStruct
{
	string playerUID;
	string playerUTFName;

	void PlayerData()
	{
		RegV("playerUID");
		RegV("playerUTFName");
	}
}

class SlotData : JsonApiStruct
{
	string callSign;
	string role;
	bool isMA;
	int tierDifference;
	bool isLocked;
	bool isVacant;
	PlayerData player;
	LoadoutData loadout;

	void SlotData()
    {
		RegV("callSign");
		RegV("role");
		RegV("isMA");
		RegV("tierDifference");
		RegV("isLocked");
		RegV("isVacant");
		RegV("player");
		RegV("loadout");
    }
}

class CallSignData : JsonApiStruct
{
	string callSign;
	float secondaryFrequency;
	float pogoFrequency;
	float primaryFrequency;
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
	string orbatID;
	string missionName;
	string description;
	string intelligenceOfficer;
	string fieldLeader;

	void Metadata()
	{
		RegV("orbatID");
		RegV("missionName");
		RegV("slotsCount");
		RegV("description");
		RegV("intelligenceOfficer");
		RegV("fieldLeader");
	}
}

class ORBATData : JsonApiStruct
{
	Metadata metadata;
	array<ref SlotData> slots;
	array<ref CallSignData> callSigns;
	
	void ORBATData()
	{
		RegV("metadata");
		RegV("slots");
		RegV("callSigns");
	}
}


class ServerORBATManager
{
	ref UTF_HTTPService m_http;
	ref map<int, ref ORBATData> m_cache;
	ref int m_orbatID;

	void ServerORBATManager(UTF_HTTPService http)
	{
		m_http = http;
		m_cache = new map<int, ref ORBATData>;
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

	static bool ParseORBAT(string json, out ORBATData outOrbat)
	{
		SCR_JsonLoadContext ctx = new SCR_JsonLoadContext();
		if (!ctx.ImportFromString(json))
			return false;

		outOrbat = new ORBATData();

		if (ctx.DoesObjectExist("metadata"))
		{
			ctx.StartObject("metadata");
			ParseMetadata(ctx, outOrbat.metadata);
			ctx.EndObject();
		}

		if (ctx.DoesKeyExist("slots"))
		{
			ctx.StartArray("slots");

			for (int i = 0; i < slots.Count(); i++)
			{
				ctx.StartObject();

				SlotData slot = new SlotData();
				ParseSlot(ctx, slot);
				outOrbat.slots.Insert(slot);

				ctx.EndObject();
			}

			ctx.EndArray();
		}

		if (ctx.DoesKeyExist("callSigns"))
		{
			ctx.StartArray("callSigns");

			for (int i = 0; i < callSigns.Count(); i++)
			{
				ctx.StartObject();

				CallSignData cs = new CallSignData();
				ParseCallSign(ctx, cs);
				outOrbat.callSigns.Insert(cs);

				ctx.EndObject();
			}

			ctx.EndArray();
		}

		return true;
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