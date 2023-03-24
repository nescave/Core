#pragma once
class ObjectSpawner;
class Core;

class Object : public std::enable_shared_from_this<Object>
{
	friend class ObjectSpawner;

private:

protected:
	bool destroyed;
	bool bUpdate;
	Core* core;
	
	Object();

	void SetupTask(double delay, const std::function<void()>& func);

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

