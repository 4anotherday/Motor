rem copia las dlls implicitas a bin
xcopy ..\..\dependencies\Ogre\Build32\bin\debug\OgreMain_d.dll ..\..\bin\ /s /d /y
xcopy ..\..\dependencies\Ogre\Build32\bin\release\OgreMain.dll ..\..\bin\ /s /d /y
xcopy ..\..\dependencies\Ogre\Build32\bin\release\zlib.dll ..\..\bin\ /s /d /y
xcopy ..\..\dependencies\Ogre\Build32\bin\debug\OgreRTShaderSystem_d.dll ..\..\bin\ /s /d /y
xcopy ..\..\dependencies\Ogre\Build32\bin\release\OgreRTShaderSystem.dll ..\..\bin\ /s /d /y
xcopy ..\..\dependencies\Ogre\Build32\bin\release\OgreOverlay.dll ..\..\bin\ /s /d /y
xcopy ..\..\dependencies\Ogre\Build32\bin\debug\OgreOverlay_d.dll ..\..\bin\ /s /d /y

rem copia las dlls explicitas de los plugins a bin\Ogre[Debug/Release]
xcopy ..\..\dependencies\Ogre\Build32\bin\debug\Codec_STBI_d.dll ..\..\bin\OgreDEBUG\ /s /d /y
xcopy ..\..\dependencies\Ogre\Build32\bin\debug\RenderSystem_Direct3d11_d.dll ..\..\bin\OgreDEBUG\ /s /d /y
xcopy ..\..\dependencies\Ogre\Build32\bin\release\Codec_STBI.dll ..\..\bin\OgreRELEASE\ /s /d /y
xcopy ..\..\dependencies\Ogre\Build32\bin\release\RenderSystem_Direct3d11.dll ..\..\bin\OgreRELEASE\ /s /d /y
