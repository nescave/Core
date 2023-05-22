#include "stdafx.h"
#include "Damageable.h"

#include "FloatingTextUI.h"
#include "ObjectSpawner.h"

Damageable::Damageable() :
    currentHp(100),
    maxHp(100)
{}

Damageable::~Damageable()
{}

Damageable& Damageable::SetHp(float val)
{
    currentHp = val;
    return *this;
}

Damageable& Damageable::SetMaxHp(float val)
{
    maxHp = val;
    return *this;
}

void Damageable::RecoverHp(float val)
{
    currentHp = currentHp+val<maxHp ? currentHp+val : maxHp;
}

void Damageable::ReportDamage(const Vector2d& position, float damage, uint16_t id, Color color, float floatSpeed, float fadeDelay)
{
    std::shared_ptr<FloatingTextUI> report;
    
    if(reports[id].expired())
    {
        report = ObjectSpawner::SpawnObject<FloatingTextUI>(position);
        reports[id] = report;
        report->reportedDamage = damage;
        report->SetColor(color);
    }else
    {
        report = reports[id].lock();
        report->reportedDamage+=damage;
        report->SetPosition(position);
        report->CancelTasks();
    }
    auto string = std::to_string(report->reportedDamage);
    string.erase(string.find('.')+3, string.size());
       
    report->SetText(string).floatSpeed = floatSpeed;
    report->Destroy(fadeDelay);
}
