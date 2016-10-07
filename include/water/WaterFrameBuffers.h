#include <irrlicht.h>
#include "Configuration.h"

using namespace irr;

class WaterFrameBuffers
{
public:

	WaterFrameBuffers(scene::ISceneManager *smgr);
	~WaterFrameBuffers();

	void init();

	inline video::ITexture	*reflectionTexture()
	{ return _reflectionTexture; }
	inline video::ITexture	*refractionTexture()
	{ return _refractionTexture; }
	inline video::ITexture	*dudvMap()
	{ return _dudvMap; }

private:

	const static core::stringc	DUDV_FILE;
	
	const static int	REFLECTION_WIDTH = 1280;
	const static int	REFLECTION_HEIGHT = 720;
	const static int	REFRACTION_WIDTH = 320;
	const static int	REFRACTION_HEIGHT = 180;

	video::ITexture	*_reflectionFrameBuffer;  // Probably no need
	video::ITexture	*_reflectionTexture;
	video::ITexture	*_reflectionDepth; 				// No use for now

	video::ITexture	*_refractionFrameBuffer;  // Probably no need
	video::ITexture	*_refractionTexture;
	video::ITexture	*_refractionDepth;

	video::ITexture *_dudvMap;
	video::ITexture	*_normalMap;

	scene::ISceneManager	*_smgr;
};
