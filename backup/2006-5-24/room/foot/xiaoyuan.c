// File(/data/room/foot/xiaoyuan.c) of foot's room
// Create by LUBAN written by Doing Lu

     inherit PRIVATE_ROOM;

void create()
{
        set("short", "�������СԺ");
	set ("long", @LONG
������һ�������Ժ�ӣ����������˼���������������ɢɢ��һ
Щ����ҶƬ��Ժ�����ڣ�����Ժ�Ӿ���һ��С�ݣ��ǳ����¡� 
LONG );

        set("room_key", "1 of foot");
	setup();

	set("exits", ([
                "out"    : "/d/room/playtown/road11",
	]));

        set("outdoors", "playertown");
        set("no_sleep_room", 1);
        set("valid_startroom", 1);

        set("KEY_DOOR", ([
                "exit" : "north",
                "room" : __DIR__"dulewu",
        ]));
    
        set("room_owner", "��Ű�");
        set("room_name", "�������");
        set("room_id", "foot");
        set("room_owner_id", "foot");
        set("room_position", "��ש·");
}
