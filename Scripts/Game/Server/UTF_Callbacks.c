class ORBATGetCallback : RestCallback
{
	ref ServerORBATManager m_manager;
	string m_orbatID;
	
	void ORBATGetCallback(ref ServerORBATManager manager, string orbatID)
	{
		m_manager = manager;
		m_orbatID = orbatID;
	}
	
	override void SetOnSuccess(RestCallback cb)
	{
		string data = cb.GetData();
		int dataSize = data.Length();
		PrintFormat("[OrbatGetCallback] Got ORBAT %1 (size %2)", m_orbatId, dataSize);
		m_manager.orbatJSON(m_orbatID, data);
	}
	
	override void SetOnError(RestCallback cb)
	{
		// @TODO: look at possible error codes first
		
		if (cb.GetRestResult() == ERestResult.EREST_ERROR_TIMEOUT)
		{
			// @TODO: Handle error caused by request timeout
		}
	}
}