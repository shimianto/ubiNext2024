#pragma once
class Scene;

class Collider
{
  public:

	float radius;
    
	static bool CheckCollision (Scene &scene, const int &obj1Id, const int &obj2Id);
};
