class FuzzUIDRegistry
{
	protected ref set<string> m_UIDs;
	protected ref RandomGenerator m_Rng;

	void FuzzUIDRegistry(RandomGenerator rng)
	{
		m_UIDs = new set<string>();
		m_Rng = rng;
	}

	string GenerateUID()
	{
		string uid;
		while (m_UIDs.Contains(uid)) {
			uid = string.Format(
				"REF-%1",
				m_Rng.RandIntInclusive(100000, 999999)
			);
		}

		m_UIDs.Insert(uid);
		return uid;
	}
}