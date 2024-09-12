#pragma once
#include "CObj.h"

class CCollider;
class CTexture;

class CPlayer :
    public CObj
{
private:
    float       m_Speed;
    float       m_AttSpeed; // �ʴ� �߻� �ӵ�
    float       m_AccTime;  // �ð� ����
    CCollider*  m_HitBox;

    CTexture*   m_Texture;



public:     
    virtual void Begin() override;
    virtual void Tick() override;    
    virtual void Render() override;

    virtual void BeginOverlap(CCollider* _Collider, CObj* _OtherObject, CCollider* _OtherCollider);
    virtual void Overlap(CCollider* _Collider, CObj* _OtherObject, CCollider* _OtherCollider);
    virtual void EndOverlap(CCollider* _Collider, CObj* _OtherObject, CCollider* _OtherCollider);


public:
    CPlayer();
    ~CPlayer();    
};

