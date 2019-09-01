#include "myfile.h"
#include "lua.hpp"
#pragma comment(lib,"irrlicht.lib")
#pragma comment(lib,"lua5.1.lib")
#pragma comment(lib,"tolua++5.1.lib")

irr::IrrlichtDevice* device;
irr::video::IVideoDriver* driver;
irr::scene::ISceneManager* smgr;

int main() {
	device=irr::createDevice();
	driver=device->getVideoDriver();
	smgr=device->getSceneManager();

	//scripting
	lua_State* LS=lua_open();
	luaL_openlibs(LS);
	luaopen_AresLua(LS);
	luaL_dofile(LS,"example.lua");
	lua_close(LS);
	//end of scripting

	while(device->run()) {
		driver->beginScene(true,true,irr::video::SColor(0,200,200,200));
		smgr->drawAll();
		driver->endScene();
	}
	device->drop();
	return 0;
}