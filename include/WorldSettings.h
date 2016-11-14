#pragma once

#define WORLD_UNIT_SCALE	10.0f
#define MAP_SIZE			(4.0f * WORLD_UNIT_SCALE)
#define FAR_VALUE			(10000.0f)
#define ORIGIN_POS			(core::vector3df(MAP_SIZE/2, 0.0f, MAP_SIZE/2))
#define ORIGIN_CAM_POS		(core::vector3df(MAP_SIZE/2, -500.0f, MAP_SIZE/2))

//struct WorldSettings
//{
//	//Needs to be used everywhere to have consistent scale with Irrlicht
//	int WorldUnitScale = 100;
//	//Total map size
//	int MapSize = 512;
//
//	int FarValue = MapSize * WorldUnitScale;
//
//	int OriginX = (MapSize / 2) * WorldUnitScale;
//	int OriginY = 100 * WorldUnitScale;
//	int OriginZ = OriginX;
//};
