#pragma once

void CreateObject(class CObj* _NewObject, LAYER_TYPE _Layer);
void DeleteObject(CObj* _DeleteObj);
void DeleteObjects(LAYER_TYPE _layer);
void ChangeLevel(LEVEL_TYPE _NextLevel);

bool IsValid(CObj*& _Object);

Vec2 Rotate(Vec2 _Dir, float _Angle);
bool GetClockWise(Vec2 _A, Vec2 _B);
float ToDegree(Vec2 _Dir);

class CAsset;
void SaveAssetRef(CAsset* _Asset, FILE* _File);
CAsset* LoadAssetRef(FILE* _File);


void DrawDebugRect(PEN_TYPE _pen, Vec2 _Pos, Vec2 _Scale, float _Duration);
void DrawDebugCircle(PEN_TYPE _pen, Vec2 _Pos, Vec2 _Scale, float _Duration);
void DrawDebugLine(PEN_TYPE _pen, Vec2 _Start, Vec2 _End, float _Duration);

float Saturate(float _Ratio);
float EaseInOut(float t);
