// File(/data/room/mei/dating.c) of mei's room
// Create by LUBAN written by Doing Lu

#include <room.h>

     inherit PRIVATE_ROOM;

void create()
{
        set("short", "����֮�ϴ���");
	set ("long", @LONG
����ǲ���֮�����˶�ʫ��ӭ�Ϳ��˵ĵط���������Щ���Σ���
�����������硣���������˶�ʫ��ķ��䣬��һ��ľ�������š��ϱ�
�Ǵ��ţ���ȥ����Ժ�ӡ� 
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
    
        set("room_owner", "��ʫ��");
        set("room_name", "����֮��");
        set("room_id", "mei");
        set("room_owner_id", "mei");
        set("room_position", "ɽ·");
}
