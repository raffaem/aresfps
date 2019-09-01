//This file is a part of "BestSound", 3d cross-platform audio library
//Copyright (C) 2006 Mancuso Raffaele
//To view all terms and condition of use, see bestsound.hpp file in this directory

#include <iostream>
#include <string>
#include <conio.h>
#include <direct.h>
#include "bestsound.hpp"

#include <irrlicht.h>
#pragma comment(lib,"irrlicht.lib")

#pragma comment(lib,"debug\\BestSound.lib")

class audio_class{
public:
	BestSound::AudioDevice* device;
	BestSound::Listener listener;
	BestSound::SoundOggStream sound;
	BestSound::SoundOggStream sound2;
	BestSound::SourceOggStream source;
	BestSound::SourceOggStream source2;
}audio;

class{
public:
	irr::IrrlichtDevice* device;
	irr::scene::ISceneNode* listener_node;
	irr::scene::ISceneNode* source_node;
	irr::scene::ISceneNode* source2_node;
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

		if(event.EventType==irr::EET_KEY_INPUT_EVENT&&
			event.KeyInput.Key==irr::KEY_KEY_S&&
			event.KeyInput.PressedDown==false) {
			audio.source2.Play();
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
	video.source2_node=video.smgr->addCubeSceneNode();
	video.source2_node->setPosition(irr::core::vector3df(1000,0,0));
	video.source_node->setMaterialFlag(irr::video::EMF_LIGHTING,false);
	video.source2_node->setMaterialFlag(irr::video::EMF_LIGHTING,false);

	video.device->setEventReceiver(&event_receiver);

	//INITIALIZING AUDIO
	audio.device=BestSound::createAudioDevice(argc,argv);

	bool value=audio.device->OpenSoundOggStream(
		"sound.ogg",
		audio.sound,
		audio.source);
	if(value==false) {
		printf("error, file not found");
		system("pause");
		exit(-1);
	}

	value=audio.device->OpenSoundOggStream(
		audio.sound,
		audio.source2,
		audio.sound2);
	if(value==false) {
		printf("error, sound not already opened");
		system("pause");
		exit(-1);
	}
	
	audio.source.SetPosition(
		IrrVecToBSVec(
		video.source_node->getPosition()
		));

	audio.source2.SetPosition(
		IrrVecToBSVec(
		video.source2_node->getPosition()
		));

	audio.source.SetVolume(1.0f);
	audio.source.SetRolloff(1.0f);//default 1
	audio.source.SetReferenceDistance(250.0);//default 3000.0 
	audio.source.SetMaxDistance(500.0f);//default 4000.0
	audio.source.SetLoopMode(true);
	audio.source.Play();

	audio.source2.SetVolume(1.0f);
	audio.source2.SetRolloff(1.0f);//default 1
	//audio.source2.SetReferenceDistance(2000.0);//default 3000.0 
	audio.source2.SetMaxDistance(5000.0f);//default 4000.0
	audio.source2.SetLoopMode(true);
	audio.source2.Play();
	
	//LOOP
	AudioUpdate();

	while(video.device->run()){
		audio.device->Update();
		AudioUpdate();		

		//audio.source.update();

		video.driver->beginScene(true,true,irr::video::SColor(0,0,0,0));
		video.smgr->drawAll();
		video.driver->endScene();
	}

    video.device->drop();
	return 0;
}
