//This file is a part of "BestSound", 3d cross-platform audio library
//Copyright (C) 2006 Mancuso Raffaele
//To view all terms and condition of use, see bestsound.hpp file in this directory

#include "audiovector.hpp"

BestSound::Vector::Vector(){this->x=this->y=this->z=0;}

BestSound::Vector::Vector(float X,float Y,float Z) {
	this->x=X;
	this->y=Y;
	this->z=Z;
}
