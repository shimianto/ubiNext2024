#pragma once
#include "../GameObject.h"

class Scene;
class Vector3;

class Button : public GameObject
{

	public:
		using GameObject::GameObject;


		static void InstantiateInScene (Scene &scene, Vector3 position);
        void Execute (Scene &scene);
};
