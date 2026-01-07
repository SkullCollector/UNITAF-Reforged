class UTF_UNITAF_FrameworkHostClass : SCR_GameModeEditorClass
{
};

class UTF_UNITAF_FrameworkHost : SCR_GameModeEditor
{
	
	protected ref UTF_ServerORBATManager m_ORBATManager;
	protected ref UTF_HTTPService m_HTTP;

	protected int m_OrbatID = -1;
	protected bool m_Initialised = false;

	// --------------------------------------------------
	override void OnGameStart()
	{
		super.OnGameStart();

		Print("[UTF_ORBAT] Server starting ORBAT framework");

		m_HTTP = new UTF_HTTPService();
		m_ORBATManager = new UTF_ServerORBATManager(m_HTTP);

		UTF_ResolveOrbatID();
		UTF_InitialiseFramework();
	}

	// --------------------------------------------------
	protected void UTF_ResolveOrbatID()
	{
		// Scenario parameter
		// @TODO: figure out how parameters work
		// if (UTF_TryGetScenarioOrbatID(m_OrbatID))
		// {
		// 	PrintFormat("[UTF_ORBAT] ORBAT ID from scenario param: %1", m_OrbatID);
		// 	return;
		// }

		// Server config file
		if (UTF_ServerConfig.UTF_TryLoadOrbatID(m_OrbatID))
		{
			PrintFormat("[UTF_ORBAT] ORBAT ID from config file: %1", m_OrbatID);
			return;
		}

		// Admin command later
		Print("[UTF_ORBAT] No ORBAT ID resolved at startup; manual input required");
		m_OrbatID = -1;
	}

	// --------------------------------------------------
	protected void UTF_InitialiseFramework()
	{
		if (m_OrbatID <= 0)
		{
			Print("[UTF_ORBAT] Framework initialised WITHOUT ORBAT");
			m_Initialised = true;
			return;
		}

		PrintFormat("[UTF_ORBAT] Fetching ORBAT %1", m_OrbatID);
		m_ORBATManager.UTF_FetchORBAT(m_OrbatID);
		m_Initialised = true;
	}

	// --------------------------------------------------
	// Admin command entrypoint
	void UTF_AdminSetOrbat(int newOrbatID)
	{
		PrintFormat("[UTF_ORBAT] Admin override ORBAT → %1", newOrbatID);
		m_OrbatID = newOrbatID;
		m_ORBATManager.UTF_FetchORBAT(m_OrbatID);
	}
}