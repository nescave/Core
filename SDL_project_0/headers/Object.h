#pragma once
class ObjectSpawner;
class Core;

#define BINDFUNC(f) [this](){this->f();}

class Object : public std::enable_shared_from_this<Object>
{

private:

protected:
	bool destroyed;
	bool bUpdate;
	Core* core;
	
	Object();


public:
	friend class ObjectSpawner;

	const uint32_t id;
	std::string name;

	void SetupTask(double delay, const std::function<void()>& func);
	void CancelTasks();
	
	virtual bool IsUpdating() { return bUpdate && !destroyed; }
	virtual bool HasCollider() { return false; }

	virtual void OnSpawn();
	virtual void Begin();
	virtual void Update(double dTime);
	virtual void OnDestroy();

	virtual void Destroy();
	void Destroy(double delay);
	virtual bool IsValid();

};

