#pragma once

void CreateObject(class CObj* _NewObject, LAYER_TYPE _Layer);
void DeleteObject(CObj* _DeleteObj);


void DrawDebugRect(PEN_TYPE _pen, Vec2 _Pos, Vec2 _Scale, float _Duration);
void DrawDebugCircle(PEN_TYPE _pen, Vec2 _Pos, Vec2 _Scale, float _Duration);
void DrawDebugLine(PEN_TYPE _pen, Vec2 _Start, Vec2 _End, float _Duration);