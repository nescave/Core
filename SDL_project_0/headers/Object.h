#pragma once
class ObjectSpawner;

class Object
{
	friend class ObjectSpawner;

private:

protected:
	bool destroyed;
	bool bUpdate;
	
	Object();
public:
	const uint32_t id;
	std::string name;

	//virtual ~Entity();

	virtual bool IsUpdating() { return bUpdate && !destroyed; }
	virtual bool ShouldRender() { return false; }
	virtual bool HasCollider() { return false; }

	virtual void OnSpawn();
	virtual void Begin();
	virtual void Update(double dTime);
	virtual void OnDestroy();

	virtual void Destroy();
	virtual bool IsValid();

};
