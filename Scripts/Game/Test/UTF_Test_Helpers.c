static string PickRandom(RandomGenerator rng, array<string> values)
{
	return values[rng.RandInt(0, values.Count())];
}

static bool Chance(RandomGenerator rng, float probability)
{
	return rng.RandFloat01() < probability;
}