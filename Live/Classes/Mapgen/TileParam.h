#pragma once

struct TileParam
{	
	enum Biome{Water, Beach, Forest};
	
	float height;
	Biome biome;

	// TODO: Generate values for humidity and temperature for more sophisticated biomes
	float humidity;
	float temperature;
};
