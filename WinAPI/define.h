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




