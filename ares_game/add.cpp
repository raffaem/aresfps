#include "add.hpp"

void AddArmour(irr::core::vector3df posizione,irr::core::vector3df rotazione,int value) {
	raf::ChangeCurrentDirTo(prog_path);

	//per fare atterrare il medikit
	//posizione=raf::Land(posizione,world_selector);

	scene::IAnimatedMesh* armourfile=smgr->getMesh("media\\models\\armour.md2"); 
	scene::ISceneNode* this_armour=smgr->addMeshSceneNode(
		armourfile->getMesh(0),
		0,//parent
		-1,//id
		posizione,
		rotazione);
	this_armour->setMaterialTexture(0, driver->getTexture("media\\texture\\armour.jpg"));
	raf::DiffuseLight(this_armour,dl);//->setMaterialFlag(video::EMF_LIGHTING,false);

	//vector
	obj_to_collide this_armour_for_vec;
	this_armour_for_vec.ogg=this_armour;
	this_armour_for_vec.int_value=value;
	this_armour_for_vec.text=NULL;
	this_armour_for_vec.type=OWC_ARMOUR;
	collides_obj.push_back(this_armour_for_vec);	
}

void AddMedikit(irr::core::vector3df posizione,irr::core::vector3df rotazione,int life) {
	raf::ChangeCurrentDirTo(prog_path);

	//per fare atterrare il medikit
	//posizione=raf::Land(posizione,world_selector);

	scene::IMesh* medikitfile=smgr->getMesh("media\\models\\medikit.md2")->getMesh(1); 
	scene::ISceneNode* medikit=smgr->addMeshSceneNode(
		medikitfile,
		0,//parent
		-1,//id
		posizione,
		rotazione);
	medikit->setMaterialTexture(0, driver->getTexture("media\\texture\\medikit.bmp"));
	raf::DiffuseLight(medikit,dl);//->setMaterialFlag(video::EMF_LIGHTING,false);

	//for vector
	obj_to_collide this_medi;
	this_medi.ogg=medikit;
	this_medi.int_value=life;
	this_medi.text=NULL;
	this_medi.type=OWC_MEDIKIT;
	collides_obj.push_back(this_medi);	

}

void AddAmmunationShotGun(core::vector3df posizione,core::vector3df rotazione,int value) {
	//lo atterra
	//posizione=raf::Land(posizione,raf::PrendiSelector());

	scene::IMesh* medikit_mesh=smgr->getMesh("media\\models\\shotgun_ammunation.md2")->getMesh(0);
	scene::ISceneNode* node=smgr->addMeshSceneNode(
		medikit_mesh,
		0,//parent
		-1,//id
		posizione,
		rotazione
	);	
	node->setMaterialTexture(0,driver->getTexture("media\\texture\\shotgun_ammunation.jpg"));
	raf::DiffuseLight(node,dl);

	//lo metto nel vettore
	obj_to_collide amm;
	amm.ogg=node;
	amm.int_value=value;
	amm.text=NULL;
	amm.type=OWC_AMMUNATION_SHOT_GUN;
	collides_obj.push_back(amm);
}
void AddAmmunationMachineGun(core::vector3df posizione,core::vector3df rotazione,int value) {
	//lo atterra
	//posizione=raf::Land(posizione,raf::PrendiSelector());

	scene::IMesh* medikit_mesh=smgr->getMesh("media\\models\\machinegun_ammunation.md2")->getMesh(0);
	scene::ISceneNode* node=smgr->addMeshSceneNode(
		medikit_mesh,
		0,//parent
		-1,//id
		posizione,
		rotazione
	);	
	node->setMaterialTexture(0,driver->getTexture("media\\texture\\machinegun_ammunation.jpg"));
	raf::DiffuseLight(node,dl);

	//lo metto nel vettore
	obj_to_collide amm;
	amm.ogg=node;
	amm.int_value=value;
	amm.text=NULL;
	amm.type=OWC_AMMUNATION_MACHINE_GUN;
	collides_obj.push_back(amm);
}
void AddAmmunationRifleGun(core::vector3df posizione,core::vector3df rotazione,int value) {
		//lo atterra
	//posizione=raf::Land(posizione,raf::PrendiSelector());

	scene::IMesh* medikit_mesh=smgr->getMesh("media\\models\\riflegun_ammunation.md2")->getMesh(0);
	scene::ISceneNode* node=smgr->addMeshSceneNode(
		medikit_mesh,
		0,//parent
		-1,//id
		posizione,
		rotazione
	);	
	node->setMaterialTexture(0,driver->getTexture("media\\texture\\riflegun_ammunation.jpg"));
	raf::DiffuseLight(node,dl);

	//lo metto nel vettore
	obj_to_collide amm;
	amm.ogg=node;
	amm.int_value=value;
	amm.text=NULL;
	amm.type=OWC_AMMUNATION_RIFLE_GUN;
	collides_obj.push_back(amm);
}
