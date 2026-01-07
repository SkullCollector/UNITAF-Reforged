class UTF_ServerConfig
{
    // better to use file name for ORBAT ID?
    // that would need changing every op, but is easy,
    // whereas reading config lines might allow dual-ORBAT ops
	static const string CONFIG_PATH = "$profile:orbat.conf";

	static bool UTF_TryLoadOrbatID(out int orbatID)
	{
		FileHandle fh = FileIO.OpenFile(CONFIG_PATH, FileMode.READ);
		if (!fh)
			return false;

		string line;
		if (!fh.ReadLine(line))
		{
			fh.Close();
			return false;
		}

		fh.Close();
		orbatID = line.ToInt();
		return (orbatID > 0);
	}
}