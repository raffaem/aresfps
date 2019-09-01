#include "script exported\\lua_func.hpp"
#include "evar.hpp"

//various function not exported
core::vector3df AresVecToIrrVec(AresVec3d v) {
	return core::vector3df(v.x,v.y,v.z);
}
AresVec3d::AresVec3d(){
	this->x=0;
	this->y=0;
	this->z=0;
}
AresVec3d::AresVec3d(float X,float Y,float Z) {
	this->x=X;
	this->y=Y;
	this->z=Z;
}
AresVec3d IrrVecToAresVec(core::vector3df v) {
	AresVec3d a;
	a.x=v.X;
	a.y=v.Y;
	a.z=v.Z;
	return a;
}
//end

void AresExit() {
	exit(0);
}

void AresSetDiffuseLightEnemie(int num,bool value) {
	raf::DiffuseLight(nem[num].ogg,value);
}
void AresEraseEnemie(int num) {
	if(num<nem.size()) {
		nem[num].ogg->remove();
		nem.erase(nem.begin()+num);
	}
}
int AresGetTotalEnemieCount() {
	return nem.size();
}
void AresShowMessageBox(std::string caption,std::string message) {
	raf::Message(message,caption);
}
void AresShowErrorMessageBox(std::string caption,std::string message) {
	raf::errore(message,caption);
}
void AresSetWeaponDiffuseLight(bool value) {
	raf::DiffuseLight(weapon->actual_weapon->ogg,value);
}

AresVec3d AresGetEnemiePos(int num) {
	return IrrVecToAresVec(nem[num].ogg->getPosition());
}
AresVec3d AresGetEnemieRot(int num) {
	return IrrVecToAresVec(nem[num].ogg->getRotation());
}

//set functions
void AresSetEnemiePos(int num,AresVec3d new_pos) {
	nem[num].ogg->setPosition(AresVecToIrrVec(new_pos));
}
void AresSetEnemieRot(int num,AresVec3d new_rot) {
	nem[num].ogg->setRotation(AresVecToIrrVec(new_rot));
}

AresVec3d AresGetWeaponPos() {
	AresVec3d temp;
	core::vector3df pos=weapon->actual_weapon->ogg->getPosition();
	temp.x=pos.X;
	temp.y=pos.Y;
	temp.z=pos.Z;
	return temp;
}
void AresSetWeaponPos(AresVec3d new_pos) {
	core::vector3df pos;
	pos.X=new_pos.x;
	pos.Y=new_pos.y;
	pos.Z=new_pos.z;
	weapon->actual_weapon->ogg->setPosition(pos);
}
float AresGetWeaponSpeed() {return weapon_speed_for_millisecond;}
void AresSetWeaponSpeed(float s) {weapon_speed_for_millisecond=s;}

//specular hightlights functions
void AresWeaponSetShininess(float value) {
	shl_dimension_weapon=value;
}
void AresEnemiesSetShininess(float value) {
	shl_dimension_enemy=value;
}
float AresWeaponGetShininess() {
	return shl_dimension_weapon;
}
float AresEnemiesGetShininess() {
	return shl_dimension_enemy;
}
void AresSetImmortal(bool value) {
	immortal=value;
}
//ends
