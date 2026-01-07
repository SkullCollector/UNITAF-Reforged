class UTF_ORBATGetCallback : RestCallback
{
	ref UTF_ServerORBATManager m_manager;
	int m_orbatID;
	
	void UTF_ORBATGetCallback(UTF_ServerORBATManager manager, int orbatID)
	{
		m_manager = manager;
		m_orbatID = orbatID;
		
		SetOnSuccess(UTF_ORBATSetOnSuccess);
		SetOnError(UTF_ORBATSetOnError);
	}
	
	void UTF_ORBATSetOnSuccess(RestCallback cb)
	{
		string data = cb.GetData();
		int dataSize = data.Length();
		PrintFormat("[ORBAT Callback] Got ORBAT %1 (size %2)", m_orbatID, dataSize);
		m_manager.UTF_OnOrbatJson(m_orbatID, data);
	}
	
	void UTF_ORBATSetOnError(RestCallback cb)
	{
		// @TODO: look at possible error codes first
		
		if (cb.GetRestResult() == ERestResult.EREST_ERROR_TIMEOUT)
		{
			// @TODO: Handle error caused by request timeout
		}
	}
}