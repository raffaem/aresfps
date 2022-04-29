//This file is a part of "BestSound", 3d cross-platform audio library
//Copyright (C) 2006 Mancuso Raffaele
//To view all terms and condition of use, see bestsound.hpp file in this directory

#include "audiosource.hpp"
//#include "audiodevice.hpp"
#include "audioerror.hpp"

#include <efx.h>
#include <efx-creative.h>
#include <efx-util.h>
#include "audio_efx.hpp"

#include <iostream>
using namespace std;

BestSound::Source::Source() {
	this->source=0;
}

BestSound::Source::~Source() {
	if(this->source!=0)
		alDeleteSources(1, &this->source);
}

bool BestSound::Source::AttachSound(BestSound::Sound sound) {
	alSourcei(this->source, AL_BUFFER, sound.buffer);

	if(alutGetError()!=ALUT_ERROR_NO_ERROR)
		return false;

	return true;
}

void BestSound::Source::Play() {
  alSourcePlay(this->source);
}

void BestSound::Source::Stop() {
	alSourceStop(this->source);
}
void BestSound::Source::Pause(){
  alSourcePause(this->source);
}
void BestSound::Source::Rewind(){
	if(!this->IsPlaying()) {
		alSourceRewind(this->source);
		return;
	}
	else {
		alSourceStop(this->source);
		alSourcePlay(this->source);
		return;
	}
}

void BestSound::Source::SetVelocity(BestSound::Vector new_vel) {
	alSource3f(this->source, AL_VELOCITY, new_vel.x,new_vel.y,new_vel.z);
}

void BestSound::Source::SetPosition(BestSound::Vector new_pos) {
	alSource3f(this->source,AL_POSITION,new_pos.x,new_pos.y,new_pos.z);
}

void BestSound::Source::SetLoopMode(bool value) {

	if(value)
		alSourcei(this->source,AL_LOOPING,AL_TRUE);
	else
		alSourcei(this->source,AL_LOOPING,AL_FALSE);

}

void BestSound::Source::SetPitch(float pitch) {
	alSourcef(this->source,AL_PITCH,pitch);
}

void BestSound::Source::SetVolume(float gain) {
	alSourcef(this->source,AL_GAIN,gain);
}

bool BestSound::Source::IsPlaying() {

    ALenum state;
    
    alGetSourcei(source, AL_SOURCE_STATE, &state);
    
    return (state == AL_PLAYING);
}

void BestSound::Source::SetReferenceDistance(float value) {
	alSourcef(this->source, AL_REFERENCE_DISTANCE,value);
}
void BestSound::Source::SetMaxDistance(float value) {
	alSourcef(this->source,AL_MAX_DISTANCE,value);
}
void BestSound::Source::SetRolloff(float value) {
	alSourcef(this->source,AL_ROLLOFF_FACTOR,value);
}

//EFFECTS
//-------------------------------------------------------
//temp
bool SetEFXEAXReverbProperties(EFXEAXREVERBPROPERTIES *pEFXEAXReverb, ALuint uiEffect);

bool BestSound::Source::CreateReverbEffect(
	EAXREVERBPROPERTIES reverb_propietaries,
	BestSound::Effect& reverb) {

	EFXEAXREVERBPROPERTIES efxReverb;
	
	//crete the effect slot
	alGenAuxiliaryEffectSlots(1,&reverb.aux_effect_slot);
	if(alGetError()!=AL_NO_ERROR) {
		BestSound::SetError(BSERR_CANT_GEN_AUX_EFFECT_SLOT);
		return false;
	}
	//end of creation
	
	//create the effect
	alGenEffects(1,&reverb.effect);
	if(alGetError()!=AL_NO_ERROR) {
		BestSound::SetError(BSERR_CANT_GEN_EFFECT);
		return false;
	}
	//end of create
	
	//set effect type
	alEffecti(reverb.effect,AL_EFFECT_TYPE,AL_EFFECT_EAXREVERB);
	if(alGetError()!=AL_NO_ERROR) {
		BestSound::SetError(BSERR_CANT_SET_EFFECT_TYPE);
		return false;
	}

	//convert eax propietaries into efxeax propietaries
	ConvertReverbParameters(&reverb_propietaries,&efxReverb);

	//set efxeax propietaries into openal effect
	bool result=SetEFXEAXReverbProperties(&efxReverb, reverb.effect);
	if(result==false) {
		BestSound::SetError(BSERR_CANT_CONV_EFXEAX_REVERB_PROP);
		return false;
	}

	// Load Effect into Auxiliary Effect Slot
	alAuxiliaryEffectSloti(reverb.aux_effect_slot,
		AL_EFFECTSLOT_EFFECT, 
		reverb.effect);

	if(alGetError()!=AL_NO_ERROR) {
		BestSound::SetError(BSERR_CANT_LOAD_EFFECT_IN_AUX_EFFECT_SLOT);
		return false;
	}

	// Enable (non-filtered) Send from Source to Auxiliary 
	//Effect Slot

	alSource3i(this->source,
		AL_AUXILIARY_SEND_FILTER,
		reverb.aux_effect_slot,
		0,
		AL_FILTER_NULL);

	if(alGetError()!=AL_NO_ERROR){
		BestSound::SetError(BSERR_CANT_EN_SOURCE_TO_AUX_SEND);
		return false;
	}

	return true;
}

bool SetEFXEAXReverbProperties(EFXEAXREVERBPROPERTIES *pEFXEAXReverb, ALuint uiEffect)
{
	bool bReturn = false;

	if (pEFXEAXReverb)
	{
		// Clear AL Error code
		alGetError();

		alEffectf(uiEffect, AL_EAXREVERB_DENSITY, pEFXEAXReverb->flDensity);
		alEffectf(uiEffect, AL_EAXREVERB_DIFFUSION, pEFXEAXReverb->flDiffusion);
		alEffectf(uiEffect, AL_EAXREVERB_GAIN, pEFXEAXReverb->flGain);
		alEffectf(uiEffect, AL_EAXREVERB_GAINHF, pEFXEAXReverb->flGainHF);
		alEffectf(uiEffect, AL_EAXREVERB_GAINLF, pEFXEAXReverb->flGainLF);
		alEffectf(uiEffect, AL_EAXREVERB_DECAY_TIME, pEFXEAXReverb->flDecayTime);
		alEffectf(uiEffect, AL_EAXREVERB_DECAY_HFRATIO, pEFXEAXReverb->flDecayHFRatio);
		alEffectf(uiEffect, AL_EAXREVERB_DECAY_LFRATIO, pEFXEAXReverb->flDecayLFRatio);
		alEffectf(uiEffect, AL_EAXREVERB_REFLECTIONS_GAIN, pEFXEAXReverb->flReflectionsGain);
		alEffectf(uiEffect, AL_EAXREVERB_REFLECTIONS_DELAY, pEFXEAXReverb->flReflectionsDelay);
		alEffectfv(uiEffect, AL_EAXREVERB_REFLECTIONS_PAN, pEFXEAXReverb->flReflectionsPan);
		alEffectf(uiEffect, AL_EAXREVERB_LATE_REVERB_GAIN, pEFXEAXReverb->flLateReverbGain);
		alEffectf(uiEffect, AL_EAXREVERB_LATE_REVERB_DELAY, pEFXEAXReverb->flLateReverbDelay);
		alEffectfv(uiEffect, AL_EAXREVERB_LATE_REVERB_PAN, pEFXEAXReverb->flLateReverbPan);
		alEffectf(uiEffect, AL_EAXREVERB_ECHO_TIME, pEFXEAXReverb->flEchoTime);
		alEffectf(uiEffect, AL_EAXREVERB_ECHO_DEPTH, pEFXEAXReverb->flEchoDepth);
		alEffectf(uiEffect, AL_EAXREVERB_MODULATION_TIME, pEFXEAXReverb->flModulationTime);
		alEffectf(uiEffect, AL_EAXREVERB_MODULATION_DEPTH, pEFXEAXReverb->flModulationDepth);
		alEffectf(uiEffect, AL_EAXREVERB_AIR_ABSORPTION_GAINHF, pEFXEAXReverb->flAirAbsorptionGainHF);
		alEffectf(uiEffect, AL_EAXREVERB_HFREFERENCE, pEFXEAXReverb->flHFReference);
		alEffectf(uiEffect, AL_EAXREVERB_LFREFERENCE, pEFXEAXReverb->flLFReference);
		alEffectf(uiEffect, AL_EAXREVERB_ROOM_ROLLOFF_FACTOR, pEFXEAXReverb->flRoomRolloffFactor);
		alEffecti(uiEffect, AL_EAXREVERB_DECAY_HFLIMIT, pEFXEAXReverb->iDecayHFLimit);

		if (alGetError() == AL_NO_ERROR)
			bReturn = true;
	}

	return bReturn;
}