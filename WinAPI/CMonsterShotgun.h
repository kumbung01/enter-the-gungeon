#pragma once
#include "CMonsterRevolver.h"

class CMonsterShotgun
	:public CMonsterRevolver
{
private:
	virtual void CreateFlipbook() override;
	virtual void CreateBullet() override;
public:
	CMonsterShotgun();
	~CMonsterShotgun();
};

