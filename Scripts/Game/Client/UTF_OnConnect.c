class UTF_OnConnect
{
    // @TODO: get PlayerController from client context to call server
    // ORBAT data
    string m_playerGameName;
    string m_playerUTFName;

    void UTF_OnConnect()
    {
    }
    void UTF_OnConnect(ref string playerGameID, ref string playerGameName, ref string playerUTFName)
    {
        m_playerGameName = playerGameName;
        m_playerUTFName = playerUTFName;
    }

    void SetPlayerName(string m_playerUTFName)
    {
        // @TODO: look at Custom Name mod for API
    }

    void TeleportToRP()
    {
        // Teleport syntax
        SCR_Global.TeleportLocalPlayer(target.GetOrigin(), SCR_EPlayerTeleportedReason.DEFAULT);

    }

}