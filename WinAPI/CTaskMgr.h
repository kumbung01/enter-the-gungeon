#pragma once


class CTaskMgr
{
	SINGLE(CTaskMgr);
private:
	vector<tTask>	m_Task;

public:
	void AddTask(const tTask& _task) { m_Task.push_back(_task); }

public:
	void Tick();
};

