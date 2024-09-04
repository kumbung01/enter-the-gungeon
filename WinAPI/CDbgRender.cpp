#include "pch.h"
#include "CDbgRender.h"

#include "CEngine.h"
#include "CTimeMgr.h"
#include "CSelectGDI.h"

CDbgRender::CDbgRender()
{

}

CDbgRender::~CDbgRender()
{

}

void CDbgRender::Render()
{
	list<tDbgRenderInfo>::iterator iter = m_DbgInfo.begin();

	HDC dc = CEngine::GetInst()->GetSecondDC();

	for (; iter != m_DbgInfo.end(); )
	{		
		SELECT_PEN((*iter).Color);
		SELECT_BRUSH(BRUSH_TYPE::HOLLOW);


		switch ((*iter).Type)
		{
		case DEBUG_SHAPE::RECT:		
		
			Rectangle(dc, (*iter).Position0.x - (*iter).Scale.x / 2.f
						, (*iter).Position0.y - (*iter).Scale.y / 2.f
						, (*iter).Position0.x + (*iter).Scale.x / 2.f
						, (*iter).Position0.y + (*iter).Scale.y / 2.f);			

			break;
		case DEBUG_SHAPE::CIRCLE:

			Ellipse(dc, (*iter).Position0.x - (*iter).Scale.x / 2.f
					  , (*iter).Position0.y - (*iter).Scale.y / 2.f
					  , (*iter).Position0.x + (*iter).Scale.x / 2.f
					  , (*iter).Position0.y + (*iter).Scale.y / 2.f);		

			break;
		case DEBUG_SHAPE::LINE:

			MoveToEx(dc, (*iter).Position0.x, (*iter).Position0.y, nullptr);
			LineTo(dc, (*iter).Position1.x, (*iter).Position1.y);

			break;		
		}

		(*iter).Time += DT;
		if ((*iter).Duration <= (*iter).Time)
		{			
			iter = m_DbgInfo.erase(iter);
		}		
		else
		{
			++iter;
		}
	}
}