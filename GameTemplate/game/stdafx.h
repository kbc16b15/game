#pragma once
#include <d3d9.h>
#include <d3dx9.h>
#include <d3dx9effect.h>
#pragma warning( disable : 4996 ) 
#include <strsafe.h>
#pragma warning( default : 4996 )
#include <cstdlib>
#include <memory>
#include <vector>
#include <list>
#include <algorithm>
#include <map>

#include "btBulletDynamicsCommon.h"
#include "BulletCollision\CollisionDispatch\btGhostObject.h"

#include "myEngine/System.h"

#include "myEngine/Graphics/Camera.h"
#include "myEngine/Graphics/SkinModel.h"
#include "myEngine/Graphics/SkinModelData.h"
#include "myEngine/Graphics/Animation.h"
#include "myEngine/Graphics/Light.h"
#include "game.h"
