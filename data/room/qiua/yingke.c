// File(/data/room/qiua/yingke.c) of qiua's room
// Create by LUBAN written by Doing Lu

#include <room.h>

     inherit PRIVATE_ROOM;

void create()
{
        set("short", "��ʵӭ����");
	set ("long", @LONG
��������ʵ�����˾�һӭ�Ӱ˷����͵ĵط����󷲿������ݼ���
һ���ٲ��������ﺮ���𻰣��˾���Ľ֮�顣����ͨ��һ�����ң���
������ͬ����Ʒ����������֮���� 
LONG );

	set("exits", ([
		"north"  : __DIR__"yishiting",
                "south"  : __DIR__"zoudao",
                "east"   : __DIR__"chashi",
	]));

        create_door("east", "ľ��", "west", DOOR_CLOSED);

        set("objects", ([
                "/d/room/roomnpc/yahuan" : 2,
        ]));

        set("no_sleep_room", 1);
        setup();

        set("room_owner", "��һ");
        set("room_name", "��ʵ");
        set("room_id", "qiua");
        set("room_owner_id", "qiua");
        set("room_position", "ɽ·");
}
