#include "GraphicsEngine.h"
#include <OgreRoot.h>
#include <SDL.h>
#include <SDL_video.h>
#include <SDL_syswm.h>
#include "Exceptions.h"
#include <OgreFileSystemLayer.h>
#include <OgreConfigFile.h>
#include <OgreGpuProgramManager.h>
#include <OgreSceneNode.h>

#include "OgreShaderGenerator.h"
#include "RTSSDefaultTechniqueListener.h"
#include "OgreRTShaderSystem.h"
#include "OgreShaderExPerPixelLighting.h"

#include "Camera.h"
#include <OgreEntity.h>
#include <OgreSceneNode.h>
#include <OgreRenderWindow.h>
#include <OgreViewport.h>
#include <OgreOverlayManager.h>
#include <OgreOverlaySystem.h>

#include <iostream>	//Testing

std::unique_ptr<GraphicsEngine> GraphicsEngine::instance = nullptr;

GraphicsEngine::GraphicsEngine() :_root(nullptr), _window(nullptr), _sceneManager(nullptr), _sdlWindow(nullptr),
_mFSLayer(nullptr), _mShaderGenerator(nullptr), alredyInitialized(false)
{
}

GraphicsEngine::~GraphicsEngine()
{
}

GraphicsEngine* GraphicsEngine::getInstance()
{
	return instance.get();
}

void GraphicsEngine::CreateInstance()
{
	if (instance.get() == nullptr) {
		instance.reset(new GraphicsEngine());
	}
}

bool GraphicsEngine::initializeRenderEngine()
{
	if (alredyInitialized) return false;
	initRoot();
	initWindow();
	setup();
	alredyInitialized = false;
	return true;
}

void GraphicsEngine::initRoot()
{
	_mFSLayer = new Ogre::FileSystemLayer("MotorUnitario");

	std::string pluginsPath;
	pluginsPath = _mFSLayer->getConfigFilePath("plugins.cfg");

	_mSolutionPath = pluginsPath;    // IG2: a�adido para definir directorios relativos al de la soluci�n
	_mSolutionPath.erase(_mSolutionPath.find_last_of("\\") + 1, _mSolutionPath.size() - 1);
	_mFSLayer->setHomePath(_mSolutionPath);   // IG2: para los archivos de configuraci�n ogre. (en el bin de la solubi�n)
	_mSolutionPath.erase(_mSolutionPath.find_last_of("\\") + 1, _mSolutionPath.size() - 1);   // IG2: Quito /bin

#ifdef _DEBUG
	_root = new Ogre::Root("OgreDEBUG/pluginsDEBUG.cfg", "OgreDEBUG/ogreDEBUG.cfg");
#else //RELEASE
	_root = new Ogre::Root("OgreRELEASE/pluginsRELEASE.cfg", "OgreRELEASE/ogreRELEASE.cfg");
#endif
}

void GraphicsEngine::initWindow() {
	_root->restoreConfig();
	_overlaySystem = new Ogre::OverlaySystem();
	_root->initialise(false);
	Ogre::NameValuePairList params;
	Ogre::ConfigOptionMap configuracion = _root->getRenderSystem()->getConfigOptions();

	SDL_Init(SDL_INIT_EVERYTHING);

	SDL_SysWMinfo wmInfo;
	SDL_VERSION(&wmInfo.version);

	Uint32 flags = SDL_WINDOW_ALLOW_HIGHDPI | SDL_WINDOW_RESIZABLE;
	std::string nombre = "Prueba";

	_sdlWindow = SDL_CreateWindow(nombre.c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 1280, 720, flags);
	SDL_GetWindowSize(_sdlWindow, &_width, &_height);

	if (SDL_GetWindowWMInfo(_sdlWindow, &wmInfo) == SDL_FALSE) {
		throw EGraphicEngine("Error creating window");
	}

	params["FSAA"] = configuracion["FSAA"].currentValue;
	params["vsync"] = configuracion["VSync"].currentValue;
	params["gamma"] = configuracion["sRGB Gamma Conversion"].currentValue;
	params["externalWindowHandle"] = std::to_string(size_t(wmInfo.info.win.window));

	_window = _root->createRenderWindow("PruebaOgre", 1920, 1080, false, &params);

	setWindowGrab(false);
}

void GraphicsEngine::setup()
{
	_sceneManager = _root->createSceneManager();
	_sceneManager->addRenderQueueListener(_overlaySystem);
	_oveMng = Ogre::OverlayManager::getSingletonPtr();

	_locateResources(_resourcesPath);
	_initialiseRTShaderSystem();
	_loadResources();

	//These elements are created so that it is posible to have multiple viewports
	//that can render on top of each other
	//This default viewport will be the first one to render something and will be the only one who will
	//clear the color buffer.
	//The rest of the viewports will only overwrite the depth buffer so that it is posible to have more than
	//one been rendered at the same time
	_defaultCamera = _sceneManager->createCamera("DefaultCamera");
	_defaultViewport = _window->addViewport(_defaultCamera);
	_defaultViewport->setMaterialScheme(Ogre::RTShader::ShaderGenerator::DEFAULT_SCHEME_NAME);
	_defaultViewport->setDimensions(0, 0, 0, 0);
	_defaultViewport->setBackgroundColour(Ogre::ColourValue::Blue);

	//_sceneManager->setShadowTechnique(Ogre::ShadowTechnique::SHADOWTYPE_TEXTURE_MODULATIVE);
	//_sceneManager->setShadowColour(Ogre::ColourValue(0.0, 0.0, 0.0));
}

void GraphicsEngine::shutdown()
{
	_mShaderGenerator->removeSceneManager(_sceneManager);
	_sceneManager->destroyCamera(_defaultCamera);
	_window->removeAllViewports();
	_root->destroySceneManager(_sceneManager);

	destroyRTShaderSystem();

	if (_mFSLayer != nullptr) {
		delete _mFSLayer;
		_mFSLayer = nullptr;
	}

	if (_sdlWindow != nullptr) {
		SDL_DestroyWindow(_sdlWindow);
		_sdlWindow = nullptr;
	}
}

void GraphicsEngine::_locateResources(std::string const& path) {
	// load resource paths from config file
	Ogre::ConfigFile cf;

	Ogre::String resourcesPath = _mFSLayer->getConfigFilePath(path);
	if (Ogre::FileSystemLayer::fileExists(resourcesPath))
	{
		cf.load(resourcesPath);
	}
	else
	{
		Ogre::ResourceGroupManager::getSingleton().addResourceLocation(
			Ogre::FileSystemLayer::resolveBundlePath(_mSolutionPath + "\\media"),
			"FileSystem", Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME);
	}

	Ogre::String sec, type, arch;
	// go through all specified resource groups
	Ogre::ConfigFile::SettingsBySection_::const_iterator seci;
	for (seci = cf.getSettingsBySection().begin(); seci != cf.getSettingsBySection().end(); ++seci) {
		sec = seci->first;
		const Ogre::ConfigFile::SettingsMultiMap& settings = seci->second;
		Ogre::ConfigFile::SettingsMultiMap::const_iterator i;

		// go through all resource paths
		for (i = settings.begin(); i != settings.end(); i++)
		{
			type = i->first;
			arch = Ogre::FileSystemLayer::resolveBundlePath(i->second);
			Ogre::ResourceGroupManager::getSingleton().addResourceLocation(arch, type, sec);
		}
	}

	sec = Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME;
	const Ogre::ResourceGroupManager::LocationList genLocs = Ogre::ResourceGroupManager::getSingleton().getResourceLocationList(sec);

	OgreAssert(!genLocs.empty(), ("Resource Group '" + sec + "' must contain at least one entry").c_str());

	arch = genLocs.front().archive->getName();
	type = genLocs.front().archive->getType();

	// Add locations for supported shader languages
	if (Ogre::GpuProgramManager::getSingleton().isSyntaxSupported("glsles"))
	{
		Ogre::ResourceGroupManager::getSingleton().addResourceLocation(arch + "/materials/programs/GLSLES", type, sec);
	}
	else if (Ogre::GpuProgramManager::getSingleton().isSyntaxSupported("glsl"))
	{
		Ogre::ResourceGroupManager::getSingleton().addResourceLocation(arch + "/materials/programs/GLSL120", type, sec);

		if (Ogre::GpuProgramManager::getSingleton().isSyntaxSupported("glsl150"))
		{
			Ogre::ResourceGroupManager::getSingleton().addResourceLocation(arch + "/materials/programs/GLSL150", type, sec);
		}
		else
		{
			Ogre::ResourceGroupManager::getSingleton().addResourceLocation(arch + "/materials/programs/GLSL", type, sec);
		}

		if (Ogre::GpuProgramManager::getSingleton().isSyntaxSupported("glsl400"))
		{
			Ogre::ResourceGroupManager::getSingleton().addResourceLocation(arch + "/materials/programs/GLSL400", type, sec);
		}
	}
	else if (Ogre::GpuProgramManager::getSingleton().isSyntaxSupported("hlsl"))
	{
		Ogre::ResourceGroupManager::getSingleton().addResourceLocation(arch + "/materials/programs/HLSL", type, sec);
	}

	std::string mRTShaderLibPath = arch + "/RTShaderLib";
	std::string mVolumeShaderPath = arch + "/ShadowVolume";
	Ogre::ResourceGroupManager::getSingleton().addResourceLocation(mRTShaderLibPath + "/materials", type, sec);

	if (Ogre::GpuProgramManager::getSingleton().isSyntaxSupported("glsles"))
	{
		Ogre::ResourceGroupManager::getSingleton().addResourceLocation(mRTShaderLibPath + "/GLSL", type, sec);
		Ogre::ResourceGroupManager::getSingleton().addResourceLocation(mRTShaderLibPath + "/GLSLES", type, sec);
	}
	else if (Ogre::GpuProgramManager::getSingleton().isSyntaxSupported("glsl"))
	{
		Ogre::ResourceGroupManager::getSingleton().addResourceLocation(mRTShaderLibPath + "/GLSL", type, sec);
	}
	else if (Ogre::GpuProgramManager::getSingleton().isSyntaxSupported("hlsl"))
	{
		Ogre::ResourceGroupManager::getSingleton().addResourceLocation(mRTShaderLibPath + "/HLSL", type, sec);
	}
}

//WIP
bool GraphicsEngine::_initialiseRTShaderSystem()
{
	if (Ogre::RTShader::ShaderGenerator::initialize())
	{
		// Grab the shader generator pointer.
		_mShaderGenerator = Ogre::RTShader::ShaderGenerator::getSingletonPtr();

		Ogre::String cachePath = _mFSLayer->getConfigFilePath("/Assets/ShaderCache");
		// Set shader cache path.
		_mShaderGenerator->setShaderCachePath(cachePath);

		// Set the scene manager.
		_mShaderGenerator->addSceneManager(_sceneManager);

		// Add a specialized sub-render (per-pixel lighting) state to the default scheme render state
		Ogre::RTShader::RenderState* pMainRenderState =
			_mShaderGenerator->createOrRetrieveRenderState(Ogre::RTShader::ShaderGenerator::DEFAULT_SCHEME_NAME).first;
		pMainRenderState->reset();

		//added
		/*_mTechniqueListener = new RTSSDefaultTechniqueListener(_mShaderGenerator);
		Ogre::MaterialManager::getSingleton().addListener(_mTechniqueListener);*/
		//Ogre::MaterialManager::getSingleton().

		return true;
	}

	return true;
}

void GraphicsEngine::_loadResources()
{
	try {
		Ogre::ResourceGroupManager::getSingleton().initialiseAllResourceGroups();
	}
	catch (Ogre::Exception e) { std::cout << e.what() << "\n"; }
}

void GraphicsEngine::destroyRTShaderSystem()
{
	// Restore default scheme.
	Ogre::MaterialManager::getSingleton().setActiveScheme(Ogre::MaterialManager::DEFAULT_SCHEME_NAME);

	// Unregister the Technique manager listener.
	if (_mTechniqueListener != nullptr)
	{
		Ogre::MaterialManager::getSingleton().removeListener(_mTechniqueListener);
		delete _mTechniqueListener;
		_mTechniqueListener = nullptr;
	}

	// Destroy RTShader system.
	if (_mShaderGenerator != nullptr)
	{
		Ogre::RTShader::ShaderGenerator::destroy();
		_mShaderGenerator = nullptr;
	}
}

void GraphicsEngine::render()
{
	try {
		_root->renderOneFrame();
	}
	catch (Ogre::Exception e) { std::cout << e.what() << "\n"; }
}

void GraphicsEngine::setWindowGrab(bool _grab)
{
	SDL_bool grab = SDL_bool(_grab);
	SDL_SetWindowGrab(_sdlWindow, grab);
	//SDL_SetRelativeMouseMode(grab);
	SDL_ShowCursor(true);
}

Ogre::Viewport* GraphicsEngine::setupViewport(Ogre::Camera* cam, int zOrder, float x, float y, float w, float h)
{
	Ogre::Viewport* vp = _window->addViewport(cam, zOrder, x, y, w, h);
	vp->setMaterialScheme(Ogre::RTShader::ShaderGenerator::DEFAULT_SCHEME_NAME);
	_mTechniqueListener = new RTSSDefaultTechniqueListener(_mShaderGenerator);
	Ogre::MaterialManager::getSingleton().addListener(_mTechniqueListener);
	vp->setClearEveryFrame(true, Ogre::FBT_DEPTH);
	return vp;
}

void GraphicsEngine::removeViewport(Ogre::Viewport* vp)
{
	_window->removeViewport(vp->getZOrder());
}

std::pair<int, int> GraphicsEngine::getWindowSize()
{
	SDL_GetWindowSize(_sdlWindow, &_width, &_height);
	return std::pair<int, int>(_width, _height);
}

void GraphicsEngine::addNode(const std::string& name, const std::string& parent)
{
	if (parent != "" && !_sceneManager->hasSceneNode(parent))
		throw SceneNodeException("Parent does not exist");

	Ogre::SceneNode* nodeParent = parent != "" ? _sceneManager->getSceneNode(parent) : _sceneManager->getRootSceneNode();
	nodeParent->createChildSceneNode(name);
}

void GraphicsEngine::removeNode(const std::string& name)
{
	Ogre::SceneNode* node = _sceneManager->getSceneNode(name, false);
	if (node != nullptr)
		node->getParentSceneNode()->removeAndDestroyChild(name);
}