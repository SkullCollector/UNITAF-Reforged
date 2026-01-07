modded class SCR_BaseGameMode
{
	override void OnGameStart()
	{
		super.OnGameStart();
		
		Print("[TEST] Server started, generating test ORBAT");

		GenerateFuzzORBATJson(1234);
	}
}