class SlotData
{
	string playerGameID;
	string playerUTFName;
	string callSign;
	//string role;
	//string loadoutID;
}

class ORBATData
{
	// @TODO: decide if ORBAT ID needs to be string
	// "felt" like it when concatenating URLs but unsure
	string orbatID;
	array<ref SlotData> slots;
	ref map metadata;
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
		
		// @TODO: memoise data and separate this call?
		ApplyORBAT(data);
	}
	
	ORBATData ParseORBAT(SCR_JsonLoadContext ctx)
	{
		ORBATData data = new ORBATData();
		data.slots = new array <ref SlotData>();
		data.metadata = new map();
		
		// Handle metadata
		// @TODO: figure out what metadata to include from endpoint
		string name;
		ctx.ReadString("name", name);
		data.metadata.Set("name", name);
		data.metadata.Set("slotsCount", slotsCount);
		
		// Handle slots
		// @TODO: Handle slots
		for (int i = 0; i < metadata.slotsCount; i++) {
			SCR_JsonLoadContext slotCtx = ctx.StartArray("slots", i); // PROBABLY WRONG
			SlotData slot = new SlotData();
			slot.playerGameID = slotCtx.ReadString("playerGameID");
			slot.playerUTFName = slotCtx.ReadString("playerUTFName");
			slot.callSign = slotCtx.ReadString("callSign");
			data.slots.Insert(slot);
		}
		
		
	}
	
}