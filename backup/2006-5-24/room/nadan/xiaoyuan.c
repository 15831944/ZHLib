// File(/data/room/nadan/xiaoyuan.c) of nadan's room
// Create by LUBAN written by Doing Lu

     inherit PRIVATE_ROOM;

void create()
{
        set("short", "С���СԺ");
	set ("long", @LONG
������һ�������Ժ�ӣ����������˼���������������ɢɢ��һ
Щ����ҶƬ��Ժ�����ڣ�����Ժ�Ӿ���һ��С�ݣ��ǳ����¡� 
LONG );

        set("room_key", "1 of nadan");
	setup();

	set("exits", ([
                "out"    : "/d/quanzhou/qzroad1",
	]));

        set("outdoors", "quanzhou");
        set("no_sleep_room", 1);
        set("valid_startroom", 1);

        set("KEY_DOOR", ([
                "exit" : "north",
                "room" : __DIR__"dulewu",
        ]));
    
        set("room_owner", "��ӹ");
        set("room_name", "С���");
        set("room_id", "gold");
        set("room_owner_id", "nadan");
        set("room_position", "ɽ·");
}
