#pragma once
#ifndef GRAPHICSENGINE_H
#define GRAPHICSENGINE_H

#include <string>
#include <memory>

namespace Ogre {
	class Root;
	class RenderWindow;
	class SceneManager;
	class FileSystemLayer;
	class Viewport;
	class Camera;

	namespace RTShader {
		class ShaderGenerator;
	}
}

class RTSSDefaultTechniqueListener;
class SDL_Window;

class GraphicsEngine {
public:

	~GraphicsEngine();

	/// <summary>
	/// Returns the instance of GraphicsEngine, in case there is no such instance, it creates one and returns that one
	/// </summary>
	static GraphicsEngine* getInstance();
	GraphicsEngine& operator=(const GraphicsEngine&) = delete;
	GraphicsEngine(GraphicsEngine& other) = delete;

	/// <summary>
	/// This method initializes the Ogre Root
	/// </summary>
	void initRoot();

	/// <summary>
	/// This method loads the configuration and prepares the Ogre RenderWindow
	/// </summary>
	void initWindow();

	/// <summary>
	/// Sets up the Ogre scene
	/// </summary>
	void setup();

	/// <summary>
	/// Free all resources in this engine
	/// </summary>
	void shutdown();

	/// <summary>
	/// Restores default scheme, unregisters the technique manager listener and destroy RTSS
	/// </summary>
	void destroyRTShaderSystem();

	/// <summary>
	/// Render one frame
	/// </summary>
	void render();

	/// <summary>
	/// Loads a scene
	/// </summary>
	void loadScene();

	/// <summary>
	/// Config for the window grab
	/// </summary>
	void setWindowGrab(bool _grab);

	/// <summary>
	/// Sets the .cfg game file path
	/// </summary>
	/// <param name="pathName"></param>
	inline void setResourcePath(std::string const& pathName) { _resourcesPath = pathName; }

	/// <summary>
	/// Gets the Scene Manager
	/// </summary>
	inline Ogre::SceneManager* getSceneManager() { return _sceneManager; }

	/// <summary>
	/// Gets the Scene Manager
	/// </summary>
	inline Ogre::RenderWindow* getRenderWindow() { return _window; }

	/// <summary>
	/// Gets the Scene Manager
	/// </summary>
	inline Ogre::Viewport* getWindowViewPort() { return _viewPort; }

	Ogre::Viewport* setupViewport(Ogre::Camera* cam, int zOrder);

private:

	/// <summary>
	/// Contructor of the class
	/// </summary>
	GraphicsEngine();

	/// <summary>
	/// Locate all resources related to the path
	/// </summary>
	/// <param name="path"> Relative route to the resources.cfg</param>
	void _locateResources(std::string const& path);

	/// <summary>
	/// Load all the resources
	/// </summary>
	void _loadResources();

	/// <summary>
	/// Initialise RTSS
	/// </summary>
	bool _initialiseRTShaderSystem();

	static std::unique_ptr<GraphicsEngine> instance;
	Ogre::Root* _root;
	Ogre::RenderWindow* _window;
	Ogre::SceneManager* _sceneManager;
	Ogre::Viewport* _viewPort;
	Ogre::Camera* _defaultCamera;
	// File system abstraction layer
	Ogre::FileSystemLayer* _mFSLayer;
	// The Shader generator instance.
	Ogre::RTShader::ShaderGenerator* _mShaderGenerator;
	// Ogre Listener for RTSS-Shading Generation
	RTSSDefaultTechniqueListener* _mTechniqueListener;
	SDL_Window* _sdlWindow;
	// Relative path to solution folder
	std::string _mSolutionPath;
	// Path relative to RTShader folder
	std::string _mRTShaderLibPath;
	// Path relative to shadowVolume folder
	std::string _mVolumeShaderPath;
	// Resources path relative to user
	std::string _resourcesPath;
};

#endif /*GRAPHICSENGINE.h*/