// File(/data/room/mei/xiaoyuan.c) of mei's room
// Create by LUBAN written by Doing Lu

     inherit PRIVATE_ROOM;

void create()
{
        set("short", "����֮��СԺ");
	set ("long", @LONG
������һ�����ķ�����Ժ�ӣ�Ժǽ�����ú�ש���ɣ�����ߣ���
�Ƿǳ���ˬ���䡣Ժ�м��ù�ľ������Ȼ��һ��������Դ�ĸо���
Ժ��������Լ��ɽ·��Ժ�ӵı�����һ��ľ�š� 
LONG );

        set("room_key", "1 of mei");
	setup();

	set("exits", ([
                "out"    : "/d/quanzhou/qzroad1",
	]));

        set("outdoors", "quanzhou");
        set("no_sleep_room", 1);
        set("valid_startroom", 1);

        set("KEY_DOOR", ([
                "exit" : "north",
                "room" : __DIR__"dating",
        ]));
    
        set("room_owner", "��ʫ��");
        set("room_name", "����֮��");
        set("room_id", "mei");
        set("room_owner_id", "mei");
        set("room_position", "ɽ·");
}
