// File(/data/room/suifeng/dating.c) of suifeng's room
// Create by LUBAN written by Doing Lu

#include <room.h>

     inherit PRIVATE_ROOM;

void create()
{
        set("short", "�һ��ȴ���");
	set ("long", @LONG
������һ������������ӭ�Ϳ��˵ĵط���������Щ���Σ�����
���������硣���������������ķ��䣬��һ��ľ�������š��ϱ���
���ţ���ȥ����Ժ�ӡ� 
LONG );

	setup();

	set("exits", ([
                "east"   : __DIR__"woshi",
		"north"  : __DIR__"houyuan",
	]));

        create_door("east", "ľ��", "west", DOOR_CLOSED);

        set("no_sleep_room", 1);

        set("KEY_DOOR", ([
                "exit" : "south",
                "room" : __DIR__"xiaoyuan",
        ]));
    
        set("room_owner", "�����");
        set("room_name", "�һ���");
        set("room_id", "taohuagu");
        set("room_owner_id", "suifeng");
        set("room_position", "��ˮ̶");
}
