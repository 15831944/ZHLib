//  jitan.c ��̳

inherit ROOM;

void create()
{
        set("short","ѩɽ��̳");
        set("long",@LONG
������ѩɽ��ѩɽ��̳���м�һ����̨����ʯ���͡�
��Χ������ľ������ͣ��Ա�һ��ʢˮ��­�����Ű���һ
ֻ���塣һЩʹ��Ϳ�������������������ó��ȡ�
LONG );
        set("outdoors","xueshan");
        set("no_fight","1");
        set("exits",([
                "north" : __DIR__"chang",
        ]));
        set("objects",([
                __DIR__"npc/x_lama": 2,
                __DIR__"npc/fsgelun": 2,
                __DIR__"obj/jitan2": 1,
        ]));
        set("no_clean_up", 0);
        setup();
}

int valid_leave(object me, string dir)
{
        object ob;
        ob=(present("fa tan", (environment(me))));
        if ( me->query("name") == ob->query("pending")
        && ob->query("burning"))
                return notify_fail("�㷨��û��������ߣ�\n");
        return ::valid_leave(me, dir);
}

