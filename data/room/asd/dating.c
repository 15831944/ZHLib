// File(/data/room/asd/dating.c) of asd's room
// Create by LUBAN written by Doing Lu

#include <room.h>

     inherit PRIVATE_ROOM;

void create()
{
        set("short", "�����õĵط�����");
	set ("long", @LONG
����Ǽ����õĵط����˺�С��ӭ�Ϳ��˵ĵط���������Щ���Σ�
�������������硣���������˺�С�ӵķ��䣬��һ��ľ�������š���
���Ǵ��ţ���ȥ����Ժ�ӡ� 
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
    
        set("room_owner", "��С��");
        set("room_name", "�����õĵط�");
        set("room_id", "asd");
        set("room_owner_id", "asd");
        set("room_position", "��ש·");
}
