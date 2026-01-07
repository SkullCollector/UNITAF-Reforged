class UTF_ServerORBATManager
{
	ref UTF_HTTPService m_http;
	ref UTF_ORBATData m_orbat;
	ref UTF_ORBATGetCallback m_cb;

	void UTF_ServerORBATManager(UTF_HTTPService http)
	{
		m_http = http;
	}

    UTF_ORBATData GetORBAT()
    {
        return m_orbat;
    }

	// Fetch ORBAT data from remote service
	void UTF_FetchORBAT(int orbatID)
	{
		// @TODO: clarify actual API format
		string url = string.Format("%1/api/orbat/%2", "http:\/\/localhost:3000", orbatID);
		m_cb = new UTF_ORBATGetCallback(this, orbatID);
		m_http.ExecuteGet(url, m_cb);
	}

	void UTF_OnOrbatJson(int orbatID, string json)
	{
		SCR_JsonLoadContext ctx = new SCR_JsonLoadContext();
		if (!ctx.ImportFromString(json))
		{
			Print("[ORBAT] Failed to import JSON");
			return;
		}
	
		UTF_ORBATData data;
		if (!UTF_ParseORBAT(ctx, data))
		{
			Print("[ORBAT] Failed to parse ORBAT");
			return;
		}
	
		data.orbatID = orbatID;
		m_orbat = data;
	
		PrintFormat("[ORBAT] ORBAT %1 loaded successfully", orbatID);
	}

	bool UTF_ParseORBAT(SCR_JsonLoadContext ctx, out UTF_ORBATData outOrbat)
	{
		outOrbat = new UTF_ORBATData();

		if (ctx.DoesObjectExist("metadata"))
		{
			ctx.StartObject("metadata");
			UTF_ParseMetadata(ctx, outOrbat.metadata);
			ctx.EndObject();
		}

		if (ctx.DoesKeyExist("groups"))
        {
			int groupsCount;
            if(ctx.StartArray("groups", groupsCount)) {
				
	            for (int i = 0; i < groupsCount; i++)
	            {
	                ctx.StartObject();
	
	                UTF_GroupData group = new UTF_GroupData();
	                UTF_ParseGroup(ctx, group);
	                outOrbat.groups.Insert(group);
	
	                ctx.EndObject();
	            }
			}

            ctx.EndArray();
        }

		return true;
	}

    bool UTF_ParseMetadata(SCR_JsonLoadContext ctx, out UTF_Metadata outMetadata)
    {
        outMetadata = new UTF_Metadata();
        // @TODO: populate metadata fields once defined
        return true;
    }
	
	bool UTF_ParsePlayer(SCR_JsonLoadContext ctx, out UTF_PlayerData outPlayer);
	
	bool UTF_ParseRole(SCR_JsonLoadContext ctx, out UTF_RoleData outRole);

    bool UTF_ParseSlot(SCR_JsonLoadContext ctx, out UTF_SlotData outSlot)
    {
        outSlot = new UTF_SlotData();

        if (!outSlot) {
            Print("[UTF_ParseSlot] Failed to create UTF_SlotData instance.");
            return false;
        }

        ctx.ReadValue("player", outSlot.player);
        ctx.ReadValue("role", outSlot.role);
        ctx.ReadValue("isMA", outSlot.isMA);
        ctx.ReadValue("tierDifference", outSlot.tierDifference);
        ctx.ReadValue("isLocked", outSlot.isLocked);
        ctx.ReadValue("isVacant", outSlot.isVacant);
        ctx.ReadValue("loadout", outSlot.loadout);

        PrintFormat("[UTF_ParseSlot] Parsed slot for player: %1", outSlot.player.playerUTFName);

        return true;
    }

	void UTF_ParseGroup(SCR_JsonLoadContext ctx, UTF_GroupData group)
	{
		ctx.ReadValue("group", group.groupName);
	
		if (ctx.DoesKeyExist("radioFrequencies"))
		{
			int freqCount;
			ctx.StartArray("radioFrequencies", freqCount);
	
			group.radioFrequencies = new array<float>();
			for (int i = 0; i < freqCount; i++)
			{
				float f;
				ctx.ReadValue("radioFrequencies", f);
				group.radioFrequencies.Insert(f);
			}
	
			ctx.EndArray();
		}
	
		if (ctx.DoesKeyExist("slots"))
		{
			group.slots = new array<ref UTF_SlotData>();
	
			int slotCount;
			ctx.StartArray("slots", slotCount);
	
			for (int i = 0; i < slotCount; i++)
			{
				ctx.StartObject();
	
				UTF_SlotData slot = new UTF_SlotData();
				UTF_ParseSlot(ctx, slot);
				group.slots.Insert(slot);
	
				ctx.EndObject();
			}
	
			ctx.EndArray();
		}
	}

	void ApplyORBATtoPlayer(int playerID)
	{
		// @TODO: implement player ORBAT assignment
		// automatic, conditional assignment e.g. on-connect, on-respawn

	}

	void ApplyORBATtoAll(UTF_ORBATData data, bool nearRPrequired = true)
	{
		// @TODO: implement all-players ORBAT assignment
		// e.g. forced reset
		// only admin-commanded, never automated
	}
}