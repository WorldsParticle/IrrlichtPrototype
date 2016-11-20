#pragma once

// All of this is a proof of our inapttitude to settle a correct architecture
// please take time to remove into correspondant modules

// Generic
#define WP_TEXTURE_SIZE 512
#define WP_WORLD_SCALE  100.0f

// Camera
#define WP_CAM_FARVALUE     (WP_WORLD_SCALE * 1000.0f)
#define WP_CAM_EXPLO_SPEED  0.5f
#define WP_CAM_DEV_SPEED    (WP_CAM_EXPLO_SPEED * 20)

// Map (one node = one heightmap)
#define WP_MAP_NODE_SIZE    (WP_TEXTURE_SIZE * 2)  // More *2, more presition from the generator
#define WP_MAP_NODE_NUMBER  1 // Let to 1 until clipping implémented
#define WP_MAP_SIZE         (WP_MAP_NODE_SIZE * WP_MAP_NODE_NUMBER)

// Terrain (size in irrlicht unit, or should be)
#define WP_TERRAIN_NODE_SIZE      (WP_MAP_NODE_SIZE * WP_WORLD_SCALE)
#define WP_TERRAIN_SIZE           (WP_MAP_SIZE * WP_WORLD_SCALE)

// Sea
#define WP_SEA_TILE_SIZE        (WP_TEXTURE_SIZE * 2 * 2 * 2)
#define WP_SEA_SIZE             (WP_TERRAIN_SIZE * 2 * 2 * 2)
#define WP_SEA_HEIGHT           (WP_WORLD_SCALE * 10.0f)
