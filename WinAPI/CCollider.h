#pragma once
#include "CComponent.h"

class CRigidBody;

class CCollider :
    public CComponent
{
private:
    struct Flag
    {
        UINT rigid : 1;
    };
private:
    Vec2        m_Offset;   // ��� ��ǥ
    Vec2        m_Scale;    // ũ��
    Vec2        m_FinalPos; // �浹ü�� ���� ��ġ

    bool        m_Active;   // Ȱ��ȭ
    Flag        m_flag;
    int         m_OverlapCount; // �浹 ���� ��ü�� ����
    CRigidBody* m_RigidBody; // �浹 ó�� ���� rigidbody

public:
    void SetScale(Vec2 _Scale) { m_Scale = _Scale; }
    Vec2 GetScale() { return m_Scale; }

    void SetOffset(Vec2 _Offset) { m_Offset = _Offset; }
    Vec2 GetOffset() { return m_Offset; }

    Vec2 GetFinalPos() { return m_FinalPos; }

    Vec2 CalCulateNormal(CCollider* _other);
    void SetRigidBody(CRigidBody* _rigidBody) { m_RigidBody = _rigidBody; }

    bool IsActive() { return m_Active; }
    void SetActive(bool _active) { m_Active = _active; }

    void SetRigid(bool rigid) { m_flag.rigid = rigid; }
    bool IsRigid() { return m_flag.rigid; }

public:
    void BeginOverlap(CCollider* _Other);   // �ٸ� �浹ü�� ���� �浹 ��
    void Overlap(CCollider* _Other);        // �ٸ� �浹ü�� BeginOverlap ���Ŀ��� ��� �������� ���
    void EndOverlap(CCollider* _Other);     // �ٸ� �浹ü�� �����ִٰ� ���ʷ� �������� ����


public:
    virtual void FinalTick() override;

public:
    CCollider();
    ~CCollider();
};

