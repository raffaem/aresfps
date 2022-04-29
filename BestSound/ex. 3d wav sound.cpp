#include <iostream>
#include <string>
#include <conio.h>
#include <direct.h>

#include "bestsound.hpp"
#pragma comment(lib,"debug\\bestsound.lib")

#include <irrlicht.h>
#pragma comment(lib,"irrlicht.lib")

class audio_class{
public:
	BestSound::AudioDevice* device;
	BestSound::Listener listener;
	BestSound::Sound sound;
	BestSound::Source source;
}audio;

class{
public:
	irr::IrrlichtDevice* device;
	irr::scene::ISceneNode* listener_node;
	irr::scene::ISceneNode* source_node;
	irr::video::IVideoDriver* driver;
	irr::scene::ISceneManager* smgr;
	irr::scene::ICameraSceneNode* camera;
}video;

class MyEventReceiver_class:public irr::IEventReceiver{
public:
	virtual bool OnEvent(irr::SEvent event) {
		if(event.EventType==irr::EET_KEY_INPUT_EVENT&&
			event.KeyInput.Key==irr::KEY_ESCAPE) {
			video.device->closeDevice();
		}
		return false;
	}
}event_receiver;

BestSound::Vector IrrVecToBSVec(irr::core::vector3df v) {
	return BestSound::Vector::Vector(v.X,v.Y,v.Z);
}

void AudioUpdate() {
	audio.listener.SetPosition(
		IrrVecToBSVec(
			video.camera->getPosition()
		)
		);
}

int main(int argc, char *argv[])
{
	//sposta nella cartella attuale
	std::string filename(argv[0]);
	int pos=filename.find_last_of('\\');

	if(pos<0) {
		std::cout<<"invalid argv0 "+filename;
		system("pause");
		exit(-1);
	}

	filename.erase(pos,filename.size()-1);
	_chdir(filename.c_str());
	std::cout<<"working directory: "+filename;
	//end

	//INITIALIZING VIDEO
	video.device=irr::createDevice(irr::video::EDT_OPENGL);
	video.driver=video.device->getVideoDriver();
	video.smgr=video.device->getSceneManager();
	video.camera=video.smgr->addCameraSceneNodeFPS();
	video.source_node=video.smgr->addCubeSceneNode();
	video.source_node->setMaterialFlag(irr::video::EMF_LIGHTING,false);

	video.device->setEventReceiver(&event_receiver);

	//INITIALIZING AUDIO
	audio.device=BestSound::createAudioDevice(argc,argv);
	bool value=audio.device->OpenSound(
		"sound.wav",
		audio.sound,
		audio.source);

	if(value==false) {
		printf("error, file not found");
		system("pause");
		exit(-1);
	}
	
	audio.source.SetPosition(
		IrrVecToBSVec(
		video.source_node->getPosition()
		));
	audio.source.SetLoopMode(true);
	audio.source.SetVolume(1.0f);

	audio.source.SetRolloff(1.0f);//default 1
	audio.source.SetReferenceDistance(3000.0);//default 3000.0 
	audio.source.SetMaxDistance(4000.0f);//default 4000.0

	//audio.source.SetVelocity(IrrVecToBSVec(irr::core::vector3df(0,5.0f,0)));

	audio.source.Play();

	//LOOP
	AudioUpdate();

	while(video.device->run()){
		AudioUpdate();

		video.driver->beginScene(true,true,irr::video::SColor(0,0,0,0));
		video.smgr->drawAll();
		video.driver->endScene();
	}

    video.device->drop();
	return 0;
}
