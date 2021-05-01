#include "AudioSourceComponent.h"
#include "MotorAudio/AudioSource.h"
#include "Transform.h"
#include "GameObject.h"
#include "Vector3.h"
#include "ComponentIDs.h"
#include "includeLUA.h"


AudioSourceComponent::AudioSourceComponent() : Component(ComponentId::AudioSource), _audioSource(nullptr), _tr(nullptr), _route()
{
	_audioSource = new AudioSource();
}

AudioSourceComponent::~AudioSourceComponent()
{
	delete _audioSource; _audioSource = nullptr;
}

void AudioSourceComponent::awake(luabridge::LuaRef &data)
{
	//if (LUAFIELDEXIST("Route")) 
	//{
		 
	//en la posicion 0 no hay nada, es "Route" en si
	for (int i = 1; i <= data["Route"].length(); ++i) {
		_route.push_back(data["Route"][i].cast<std::string>());
	}
	for(int i = 0; i < _route.size(); ++i)
		std::cout << "As: " << _route[i] << std::endl;
	//}
}

void AudioSourceComponent::start()
{
	_tr = static_cast<Transform*>(_gameObject->getComponent(ComponentId::Transform));
	float x = static_cast<float>(_tr->getPosition().getX());
	float y = static_cast<float>(_tr->getPosition().getY());
	float z = static_cast<float>(_tr->getPosition().getZ());
	_audioSource = new AudioSource(_route);
	_audioSource->setPosition(x, y, z);
}

void AudioSourceComponent::update()
{
	float x = static_cast<float>(_tr->getPosition().getX());
	float y = static_cast<float>(_tr->getPosition().getY());
	float z = static_cast<float>(_tr->getPosition().getZ());
	_audioSource->setPosition(x, y, z);
}

void AudioSourceComponent::lateUpdate()
{
	_audioSource->update();
}

void AudioSourceComponent::createAudioInChannel()
{
	_audioSource->createAudio();
}

void AudioSourceComponent::playAudio(int id)
{
	_audioSource->play(id);
}

void AudioSourceComponent::pauseChannel()
{
	_audioSource->pause();
}

void AudioSourceComponent::stopChannel()
{
	_audioSource->stop();
}

void AudioSourceComponent::setAudioLoop(int id, int loop)
{
	_audioSource->setLoop(id, loop);
}

void AudioSourceComponent::setStereo(int id, bool stereo)
{
	_audioSource->set3D(id, stereo);
}

float AudioSourceComponent::getVolumeChannel() const
{
	return _audioSource->getVolumeAudio();
}

void AudioSourceComponent::setVolumeChannel(float v)
{
	_audioSource->setVolumeAudio(v);
}

void AudioSourceComponent::set3DConeSetting(float insideAngle, float outsideAngle, float outsideVolume)
{
	_audioSource->set3DConeSettings(insideAngle, outsideAngle, outsideVolume);
}

void AudioSourceComponent::set3DMinMaxDistanceChannel(float min, float max)
{
	_audioSource->set3DMinMaxDistance(min, max);
}