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
	
	void FetchORBAT(string orbatID)
	{
		// @TODO: clarify actual API format
		string url = string.Format("%1/api/orbat/%2", "http://localhost:3000", orbatID);
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
		
		ApplyORBAT(data);
	}
}