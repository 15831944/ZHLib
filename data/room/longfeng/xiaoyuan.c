// File(/data/room/longfeng/xiaoyuan.c) of longfeng's room
// Create by LUBAN written by Doing Lu

     inherit PRIVATE_ROOM;

void create()
{
        set("short", "�ʺ��СԺ");
	set ("long", @LONG
������һ�����ķ�����Ժ�ӣ�Ժǽ�����ú�ש���ɣ�����ߣ���
�Ƿǳ���ˬ���䡣Ժ�м��ù�ľ������Ȼ��һ��������Դ�ĸо���
Ժ��������Լ����ʯС����Ժ�ӵı�����һ��ľ�š� 
LONG );

        set("room_key", "1 of longfeng");
	setup();

	set("exits", ([
                "out"    : "/d/room/playtown/road1",
	]));

        set("outdoors", "playertown");
        set("no_sleep_room", 1);
        set("valid_startroom", 1);

        set("KEY_DOOR", ([
                "exit" : "north",
                "room" : __DIR__"dating",
        ]));
    
        set("room_owner", "����");
        set("room_name", "�ʺ��");
        set("room_id", "look");
        set("room_owner_id", "longfeng");
        set("room_position", "��ʯС��");
}
