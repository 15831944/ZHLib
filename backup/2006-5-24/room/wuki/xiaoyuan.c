// File(/data/room/wuki/xiaoyuan.c) of wuki's room
// Create by LUBAN written by Doing Lu

     inherit PRIVATE_ROOM;

void create()
{
        set("short", "����СԺ");
	set ("long", @LONG
������һ�������Ժ�ӣ����������˼���������������ɢɢ��һ
Щ����ҶƬ��Ժ�����ڣ�����Ժ�Ӿ���һ��С�ݣ��ǳ����¡� 
LONG );

        set("room_key", "1 of wuki");
	setup();

	set("exits", ([
                "out"    : "/d/gumu/hanshuitan",
	]));

        set("outdoors", "quanzhen");
        set("no_sleep_room", 1);
        set("valid_startroom", 1);

        set("KEY_DOOR", ([
                "exit" : "north",
                "room" : __DIR__"dulewu",
        ]));
    
        set("room_owner", "��֮����");
        set("room_name", "����");
        set("room_id", "wufang");
        set("room_owner_id", "wuki");
        set("room_position", "��ˮ̶");
}
