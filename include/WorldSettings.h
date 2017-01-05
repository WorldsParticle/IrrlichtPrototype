#pragma once

// All of this is a proof of our inapttitude to settle a correct architecture
// please take time to remove into correspondant modules

// Generic
#define WP_TEXTURE_SIZE 2046
#define WP_WORLD_SCALE  1.0f

// Map (one node = one heightmap)
#define WP_MAP_NODE_SIZE    (WP_TEXTURE_SIZE)  // More *2, more presition from the generator
#define WP_MAP_NODE_NUMBER  1 // Let to 1 until clipping implémented
#define WP_MAP_SIZE         (WP_MAP_NODE_SIZE * WP_MAP_NODE_NUMBER)

// Terrain (size in irrlicht unit, or should be)
#define WP_TERRAIN_SCALE        (WP_WORLD_SCALE * 50.0f)
#define WP_TERRAIN_NODE_SIZE    (WP_MAP_NODE_SIZE * WP_TERRAIN_SCALE)
#define WP_TERRAIN_SIZE         (WP_MAP_SIZE * WP_TERRAIN_SCALE)
#define WP_MOUNT_MIN_HEIGHT	(20 * WP_TERRAIN_SCALE)

// Sea
#define WP_SEA_TILE_SCALE       8.0f
#define WP_SEA_TILE_SIZE        (WP_TEXTURE_SIZE * WP_SEA_TILE_SCALE)
#define WP_SEA_SIZE             (WP_TERRAIN_SIZE * 2)
#define WP_SEA_HEIGHT           (WP_TERRAIN_SCALE * 255.0f / 5.0f) // Heightmap store height from 0 to 255

// Element
#define WP_ELEMENT_SCALE    (WP_WORLD_SCALE * 1.0f)

// Camera
#define WP_CAM_FARVALUE     (WP_TERRAIN_SIZE / 2)
#define WP_CAM_EXPLO_SPEED  0.5f
#define WP_CAM_DEV_SPEED    (WP_CAM_EXPLO_SPEED * 20)
#define WP_CAM_OFFSET		(WP_TERRAIN_SCALE) // Human height

// Sun
#define WP_SUN_COLOR        video::SColorf(0.9f, 0.8f, 0.7f) // ca fait l'affaire
#define WP_SUN_POSITION     core::vector3df(WP_SEA_SIZE, WP_TERRAIN_SCALE * 255.0f * 2.0f, -WP_SEA_SIZE) // inverser x/z pour nuit
#define WP_SUN_RADIUS       (WP_SEA_SIZE)
