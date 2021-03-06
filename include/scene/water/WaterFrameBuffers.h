#include <irrlicht.h>
#include "Configuration.h"

#include "WorldSettings.h"

using namespace irr;

// SHOULD BECOME A UNIQUE INSTANCE !!!!
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
	inline video::ITexture	*normalMap()
	{ return _normalMap; }
	inline video::ITexture	*refractionDepth()
	{ return _refractionDepth; }

private:

	const static core::stringc	DUDV_FILE;
	const static core::stringc  NORMAL_FILE;

	const static int	REFLECTION_WIDTH = WP_TEXTURE_SIZE;
	const static int	REFLECTION_HEIGHT = WP_TEXTURE_SIZE;
	const static int	REFRACTION_WIDTH = WP_TEXTURE_SIZE;
	const static int	REFRACTION_HEIGHT = WP_TEXTURE_SIZE;

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
