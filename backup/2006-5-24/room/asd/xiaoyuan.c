// File(/data/room/asd/xiaoyuan.c) of asd's room
// Create by LUBAN written by Doing Lu

     inherit PRIVATE_ROOM;

void create()
{
        set("short", "�����õĵط�СԺ");
	set ("long", @LONG
������һ�����ķ�����Ժ�ӣ�Ժǽ�����ú�ש���ɣ�����ߣ���
�Ƿǳ���ˬ���䡣Ժ�м��ù�ľ������Ȼ��һ��������Դ�ĸо���
Ժ��������Լ����ש·��Ժ�ӵı�����һ��ľ�š� 
LONG );

        set("room_key", "1 of asd");
	setup();

	set("exits", ([
                "out"    : "/d/room/playtown/road14",
	]));

        set("outdoors", "playertown");
        set("no_sleep_room", 1);
        set("valid_startroom", 1);

        set("KEY_DOOR", ([
                "exit" : "north",
                "room" : __DIR__"dating",
        ]));
    
        set("room_owner", "��С��");
        set("room_name", "�����õĵط�");
        set("room_id", "asd");
        set("room_owner_id", "asd");
        set("room_position", "��ש·");
}
