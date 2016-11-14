#pragma once

//Needs to be used everywhere to have consistent scale with Irrlicht
#define WORLD_UNIT_SCALE	10.0f
//Total map size
#define MAP_SIZE			(52.0f * WORLD_UNIT_SCALE)
#define FAR_VALUE			(10000.0f)
#define ORIGIN_POS			(core::vector3df(MAP_SIZE/2, 0.0f, MAP_SIZE/2))
#define ORIGIN_CAM_POS		(core::vector3df(MAP_SIZE/2, 500.0f, MAP_SIZE/2))
#define WATER_HEIGHT		10.0f
