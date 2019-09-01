//This file is a part of "BestSound", 3d cross-platform audio library
//Copyright (C) 2006 Mancuso Raffaele
//To view all terms and condition of use, see bestsound.hpp file in this directory

#include "audioeffect.hpp"

BestSound::Effect::Effect() {
	this->effect=0;
}

BestSound::Effect::~Effect() {
	/*
	if(alIsEffect(this->effect)==AL_TRUE)
		alDeleteEffects(1,&this->effect);

	if(alIsAuxiliaryEffectSlot(this->aux_effect_slot)==AL_TRUE)
		alDeleteAuxiliaryEffectSlots(1,&this->aux_effect_slot);
		*/
	this->Remove();
}

BestSound::Effect::Remove() {
	if(alIsEffect(this->effect)==AL_TRUE)
		alDeleteEffects(1,&this->effect);

	if(alIsAuxiliaryEffectSlot(this->aux_effect_slot)==AL_TRUE)
		alDeleteAuxiliaryEffectSlots(1,&this->aux_effect_slot);
}
bool BestSound::Effect::IsValid() {
	return
}

