// File(/data/room/qiua/jusuo.c) of qiua's room
// Create by LUBAN written by Doing Lu

#include <room.h>

     inherit PRIVATE_ROOM;

void create()
{
	set("short", "����");
	set ("long", @LONG
�������ʵ���˾�һ��Ϣ������ĵط���¥�Ͼ������˵����ң�
���������鷿�� 
LONG );

	set("exits", ([
		"up"   : __DIR__"woshi",
                "west" : __DIR__"shufang",
	]));

        set("no_sleep_room", 1);
        setup();

        set("KEY_DOOR", ([
                "exit" : "east",
                "room" : __DIR__"huayuan",
        ]));
    
        set("room_owner", "��һ");
        set("room_name", "��ʵ");
        set("room_id", "qiua");
        set("room_owner_id", "qiua");
        set("room_position", "ɽ·");
}
