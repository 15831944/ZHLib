// File(/data/room/suifeng/xiaoyuan.c) of suifeng's room
// Create by LUBAN written by Doing Lu

     inherit PRIVATE_ROOM;

void create()
{
        set("short", "�һ���СԺ");
	set ("long", @LONG
������һ�����ķ�����Ժ�ӣ�Ժǽ�����ú�ש���ɣ�����ߣ���
�Ƿǳ���ˬ���䡣Ժ�м��ù�ľ������Ȼ��һ��������Դ�ĸо���
Ժ��������Լ�Ǻ�ˮ̶��Ժ�ӵı�����һ��ľ�š� 
LONG );

        set("room_key", "1 of suifeng");
	setup();

	set("exits", ([
                "out"    : "/d/gumu/hanshuitan",
	]));

        set("outdoors", "quanzhen");
        set("no_sleep_room", 1);
        set("valid_startroom", 1);

        set("KEY_DOOR", ([
                "exit" : "north",
                "room" : __DIR__"dating",
        ]));
    
        set("room_owner", "�����");
        set("room_name", "�һ���");
        set("room_id", "taohuagu");
        set("room_owner_id", "suifeng");
        set("room_position", "��ˮ̶");
}
