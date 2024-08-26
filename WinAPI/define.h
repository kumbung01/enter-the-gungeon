#pragma once


#define SINGLE(Type)	public:\
							static Type* GetInst()\
							{\
								static Type engine;\
								return &engine;\
							}\
							private:\
								Type();\
								Type(const Type& _Origin) = delete;\
								void operator =(const Type& _Origin) = delete;\
								~Type();


#define SELECT_PEN(Pen) CSelectGDI SelectPen(CEngine::GetInst()->GetMainDC(), CEngine::GetInst()->GetPen(Pen));
#define SELECT_BRUSH(Brush) CSelectGDI SelectBrush(CEngine::GetInst()->GetMainDC(), CEngine::GetInst()->GetBrush(Brush));

#define DT CTimeMgr::GetInst()->GetDeltaTime()