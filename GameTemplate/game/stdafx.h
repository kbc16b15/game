#pragma once
#include <d3d9.h>
#include <d3dx9.h>
#include <d3dx9effect.h>
#include <xaudio2.h>
#include <xaudio2fx.h>
#include <x3daudio.h>

#pragma warning( disable : 4996 ) 
#include <strsafe.h>
#pragma warning( default : 4996 )
#include <cstdlib>
#include <memory>
#include <vector>
#include <list>
#include <algorithm>
#include <map>
#pragma comment(lib, "winmm.lib")
#pragma comment(lib, "X3DAudio.lib")
#include "btBulletDynamicsCommon.h"
#include "BulletCollision\CollisionDispatch\btGhostObject.h"

#include "myEngine/System.h"

#include "myEngine/Graphics/Camera.h"
#include "myEngine/Graphics/SkinModel.h"
#include "myEngine/Graphics/SkinModelData.h"
#include "myEngine/Graphics/Animation.h"
#include "myEngine/Graphics/Light.h"
#include "game.h"
#include "CubeCollision.h"
