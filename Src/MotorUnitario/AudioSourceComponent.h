#pragma once
#ifndef AUDIOSOURCECOMPONENT_H
#define AUDIOSOURCECOMPONENT_H

#include "Component.h"
#include <string>

class AudioSource;
class Transform;

class AudioSourceComponent: public Component
{
public:
	/// <summary>
	/// Default constructor of the class
	/// </summary>
	AudioSourceComponent(GameObject* gameObject);
	/// <summary>
	/// Constructor of the class in the case we want to create a unique sound 
	/// </summary>
	/// <param name="route">c </param>
	AudioSourceComponent(GameObject* gameObject, std::string const& route);
	/// <summary>
	/// Destructor of the class 
	/// </summary>
	~AudioSourceComponent();

	/// <summary>
	/// Initializes the component, called once at the start of the execution
	/// </summary>
	virtual void start();
	/// <summary>
	/// Update the component
	/// </summary>
	virtual void update();
	/// <summary>
	/// Called each frame after update. 
	/// </summary>
	virtual void lateUpdate();
	/// <summary>
	/// Create an audio. You MUST change the route before create it.
	/// </summary>
	void createAudioInChannel();
	/// <summary>
	/// Play the audio with the id "id"
	/// </summary>
	/// <param name="id">Id audio</param>
	void playAudio(int id);
	/// <summary>
	/// Pause the entire channel
	/// </summary>
	void pauseChannel();
	/// <summary>
	/// Stop the entire channel
	/// </summary>
	void stopChannel();
	/// <summary>
	/// Sets the audio loop 
	/// </summary>
	/// <param name="id">Id audio</param>
	/// <param name="loop"> loop = 0 no loop; loop = -1 normal loop; loop = n the audio will repeat n times</param>
	void setAudioLoop(int id, int loop);
	/// <summary>
	/// Sets the option mono-stereo in the audio
	/// </summary>
	/// <param name="id">Id audio</param>
	/// <param name="stereo">If true audio will be stereo. Otherwise it will be mono</param>
	void setStereo(int id, bool stereo);
	/// <summary>
	/// Sets the audio directory route  
	/// </summary>
	float getVolumeChannel() const;
	/// <summary>
	/// Sets the audio volume  
	/// </summary>
	void setVolumeChannel(float v);
	/// <summary>
	/// Sets the audio directory route  
	/// </summary>
	/// <param name="route">FileRoute</param>
	void setRoute(std::string route) { _route = route; }
	/// <summary>
	/// Sets the anglesand attenuation levels of a 3D cone shape, for simulated occlusion which is based on direction.
	/// </summary>
	/// <param name="insideAngle">This is the angle spread within which the sound is unattenuated.</param>
	/// <param name="outsideAngle">This is the angle spread outside of which the sound is attenuated to its outsidevolume.</param>
	/// <param name="outsideVolume">Cone outside volume</param>
	void set3DConeSetting(float insideAngle, float outsideAngle, float outsideVolume);
	/// <summary>
	/// Sets the minimum and maximum audible distance for a 3D sound
	/// </summary>
	/// <param name="min">minimum distance</param>
	/// <param name="max">maximum distance</param>
	void set3DMinMaxDistanceChannel(float min, float max);

private:
	AudioSource* _audioSource;
	Transform* _tr;
	// Sound route
	std::string _route;
};

#endif AUDIOSOURCECOMPONENT_H