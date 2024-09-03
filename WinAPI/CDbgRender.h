#pragma once

class CDbgRender
{
	SINGLE(CDbgRender);
private:
	list<tDbgRenderInfo>	m_DbgInfo;

public:
	void AddDbgInfo(const tDbgRenderInfo& _info) { m_DbgInfo.push_back(_info); }

public:
	void Render();
};

