#pragma once


enum class PEN_TYPE
{
	RED,
	GREEN,
	BLUE,
	END,
};

enum class BRUSH_TYPE
{
	RED,
	GREEN,
	BLUE,
	GRAY,
	HOLLOW,
	END,
};

enum class LEVEL_TYPE
{
	START,
	STAGE_0,
	STAGE_1,
	STAGE_2,
	EDITOR,

	END,
};


enum class TASK_TYPE
{
	// Param0 : Object Address, Param1 : Layer Index
	CREATE_OBJECT,

	// Param0 : Object Address
	DELETE_OBJECT,

	// Param0 : Objects Layer
	DELETE_OBJECTS,

	// Param0 : Next Level
	CHANGE_LEVEL,
};

enum class LAYER_TYPE
{
	BACKGROUND,
	TILE,
	DEFAULT,
	PLAYER,
	PLAYER_OBJECT,
	MONSTER,
	MONSTER_OBJECT,
	GUN,
	// 7 ~ 30

	UI = 31,
	END = 32
};


enum class COMPONENT_TYPE
{
	COLLIDER,
	RIGIDBODY,
	FLIPBOOKPLAYER,
	FSM,
	TILEMAP,
};

enum class ASSET_TYPE
{
	TEXTURE,	// �̹���
	SOUND,		// �Ҹ�	
	SPRITE,		// Ư�� �ؽ����� Ư�� ����
	FLIPBOOK,	// Sprite �� ����ü
};


enum class DEBUG_SHAPE
{
	RECT,
	CIRCLE,
	LINE,
};