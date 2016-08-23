/** Example 012 Terrain Rendering

This tutorial will briefly show how to use the terrain renderer of Irrlicht. It
will also show the terrain renderer triangle selector to be able to do
collision detection with terrain.

Note that the Terrain Renderer in Irrlicht is based on Spintz'
GeoMipMapSceneNode, lots of thanks go to him. DeusXL provided a new elegant
simple solution for building larger area on small heightmaps -> terrain
smoothing.

In the beginning there is nothing special. We include the needed header files
and create an event listener to listen if the user presses a key: The 'W' key
switches to wireframe mode, the 'P' key to pointcloud mode, and the 'D' key
toggles between solid and detail mapped material.
*/

#ifdef _MSC_VER
#pragma comment(lib, "Irrlicht.lib")
#endif

#include "Core.h"

int main()
{
	Core core;

	if (core.initIrrlicht() != 0)
		return 1;

	if (core.initModules() != 0)
		return 1;

	if (core.run() != 0)
		return 1;

	return 0;
}
