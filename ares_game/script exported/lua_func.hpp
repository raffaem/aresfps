#ifndef LUA_EXPORTS_FUNC_ARES_MANCUSO_RAFFAELE_3248646512610864651608406
#define LUA_EXPORTS_FUNC_ARES_MANCUSO_RAFFAELE_3248646512610864651608406

#include <string>

//!\class AresVec3d 
//!\brief Use this class to rappresent a point in 3d world
//!
//!You can also use this class to raprresent 3 values on 3 axis (like scale or rotation)
//!\version Since 0.3
class AresVec3d {
public:
	//!\brief This costructor set x,y and z to 0
	//!
	//!This is the default costructor
	//!\version Since 0.3
	AresVec3d();
	//!This costructor set x,y and z to user values
	//!\param X the x axle
	//!\param Y the y axle
	//!\param Z the z axle
	//!\version Since 0.3
	AresVec3d(float X,float Y,float Z);
	//!\brief x axle
	float x,/*!\brief y axle*/y,/*!\brief z axle*/z;
};

//ADD FUNCTION

//WEAPON FUNCTIONS
//!\addtogroup weapon_functions Weapon functions
//!\brief This group contain weapon functions
/*@{*/
//!\brief Is the weapon affected by lights?
//!\param value if yes weapon is not affected by lights (using diffuse lighting), otherwise it's affected
//!\return none
//!\version Since 0.3
void AresSetWeaponDiffuseLight(bool value);

//!\brief Get weapon position
//!\return weapon position as AresVec3d object
//!\version Since 0.3
AresVec3d AresGetWeaponPos();

//!\brief Set weapon position
//!\param new_pos The new weapon position
//!\return none
//!\version Since 0.3
void AresSetWeaponPos(AresVec3d new_pos);

//!\brief Get weapon speed
//!\return weapon speed as decimal
//!\version Since 0.3
float AresGetWeaponSpeed();

//!\brief Set the speed of the weapon
//!\param s The new weapon speed as decimal value
//!\return none
//!\version Since 0.3
void AresSetWeaponSpeed(float s);
/*@}*/

//ENEMIE FUNCTION
//!\addtogroup enemie_functions Enemies functions
//!\brief This group contain enemies functions
//!
//!Note that enemies is numerated from 0 to x, when x is the total number of the enemies
//!To aplly a change at all enemies, use a for cicle (see LUA documentation)
/*@{*/
//!\brief Is the enemy affected by lights?
//!\param num the number of the enemy
//!\param value if yes enemy is not affected by lights (using diffuse lighting), otherwise it's affected
//!\return none
//!\version Since 0.3
void AresSetDiffuseLightEnemie(int num,bool value);

//!\brief Erase an enemy
//!\param num the number of the enemy to erase
//!\return none
//!\version Since 0.3
void AresEraseEnemie(int num);

//!\brief Get the total number of enemy
//!
//!\return total number of enemy as integer
//!\warning This function return the total number of enemies start by 1. 
//!The others functions gets the number of an enemy start by 0 (0 is the first enemy). This mean that the 3rd enemy correspond to 2 into others function (0-1-2)and o 3 into this function. If you want to apply a change at all enemies (by calling function), you have to execute a for numeric loop (see LUA documentation) start at 0 and end at AresGetTotalEnemieCount()-1
//!\version Since 0.3
int AresGetTotalEnemieCount();

//!\brief Get the position of an enemy
//!
//!\return enemy position
//!\version Since 0.3
AresVec3d AresGetEnemiePos(int num);

//!\brief Get the rotation of an enemy
//!
//!\return enemy rotation
//!\version Since 0.3
AresVec3d AresGetEnemieRot(int num);

//!\brief Set the position of an enemy
//!\param num the number identifier of the enemy
//|\param new_pos the new position of the enemy
//!\return none
//!\version Since 0.3
void AresSetEnemiePos(int num,AresVec3d new_pos);

//!\brief Set the rotation of an enemy
//!\param num the number identifier of the enemy
//|\param new_rot the new rotation of the enemy
//!\return none
//!\version Since 0.3
void AresSetEnemieRot(int num,AresVec3d new_rot);
/*@}*/

//SPECULAR HIGHTLIGHTS FUNCTIONS
//!\addtogroup specular_hightlights_functions Specular hightlights functions
//!\brief Functions to control the specular hightlights effect
//!
//!Specular hightlights is a special effect that show "light reflection" on object. Generally it takes two parameters: the dimension of the effect and the color of the light.
//!The dimension of the effect is also caled "shininess", and it is inversely proportional. So 0.01 is a very big effect and 100.0 is a very small effect
//!Currently you can only control the dimension of the effect (shininess). The color is white by default.
/*@{*/

//!\brief Set shininess of the weapon
//!\param value shininess as decimal
//!\return none
//!\version Since 0.3
void AresWeaponSetShininess(float value);

//!\brief Set shininess of all enemies weapon
//!\param value shininess as decimal
//!\return none
//!\version Since 0.3
void AresEnemiesSetShininess(float value);

//!\brief Get shininess of the weapon
//!\return weapon shininess
//!\version Since 0.3
float AresWeaponGetShininess();

//!\brief Get shininess of the all enmies
//!\return all enemies shininess
//!\version Since 0.3
float AresEnemiesGetShininess();
/*@}*/

//GENERAL FUNCTIONS
//!\addtogroup general_functions General functions
//!\brief General functions
/*@{*/

//!\brief Show a message box
//!\param caption the caption as string
//!\param message the contenent as string
//!\return none
//!\version Since 0.3
void AresShowMessageBox(std::string caption,std::string message);

//!\brief Show an error message box
//!\param caption the caption as string
//!\param message the contenent as string
//!\return none
//!\version Since 0.3
void AresShowErrorMessageBox(std::string caption,std::string message);

//!\brief Exit immediately from Ares
//!\return none
//!\version Since 0.3
void AresExit();

/*@}*/

//SPECIAL FUNCTIONS
void AresSetImmortal(bool value);

#endif