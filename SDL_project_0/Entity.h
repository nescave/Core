#pragma once
class Entity
{
protected:
	bool destroyed;
	bool bUpdate;

public:
	const int id;
	std::string name;

	Entity(int iD, std::string n);
	//virtual ~Entity();

	virtual bool IsUpdating() { return bUpdate && !destroyed; }
	virtual bool ShouldRender() { return false; }
	virtual bool HasCollider() { return false; }

	virtual void Begin();
	virtual void Update(double dTime);
	virtual void OnDestroy();

	virtual void Destroy();
	virtual bool IsValid();

};

