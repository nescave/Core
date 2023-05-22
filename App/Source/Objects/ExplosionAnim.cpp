#include "stdafx.h"
#include "ExplosionAnim.h"
#include "AssetManager.h"
#include "GameEnums.h"
#include "Animation.h"

void ExplosionAnim::Update(double dTime)
{
    RenderableObject::Update(dTime);
    if(!animation->IsPlaying())
    {
        Destroy();
    }
}

void ExplosionAnim::OnSpawn()
{
    SetTexture(AssetManager::Get()->GetLoadedTexture(GameTextures::EXPOLOSION)); 
    SetupAnimation(3,3);
}
