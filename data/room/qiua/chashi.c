// File(/data/room/qiua/chashi.c) of qiua's room
// Create by LUBAN written by Doing Lu

#include <room.h>

     inherit PRIVATE_ROOM;

void create()
{
	set("short", "����");
	set ("long", @LONG
��һ������С�ɵĲ��ң������Եþ��¡�������һ�輸��������
������������Ů�������������˵ķԸ�(tea)�� 
LONG );

	set("exits", ([
		"west"  : __DIR__"yingke",
	]));

        set("objects", ([
                "/d/room/roomnpc/teagirl" : 2,
        ]));

        create_door("west", "ľ��", "east", DOOR_CLOSED);

        set("no_sleep_room", 1);
        setup();

        set("room_owner", "��һ");
        set("room_name", "��ʵ");
        set("room_id", "qiua");
        set("room_owner_id", "qiua");
        set("room_position", "ɽ·");
}
