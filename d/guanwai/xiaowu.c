// /guanwai/xiaowu.c

inherit ROOM;

void create()
{
    set("short", "Сé��");
    set("long", @LONG
����һ���ó���ɽ��ľ�ݳɵ�С�ݣ����ڴ�ɨ�ĺܸɾ������ܵ�ǽ����
��������Ƥ��ѩ����һ��СС����������һ����״󺺡�
LONG );
    set("exits", ([
        "south" : __DIR__"xiaoyuan",
        "north" : __DIR__"houyuan",
    ]));
    set("objects", ([
        CLASS_D("hu") + "/hufei" : 1,
    ]));
    set("valid_startroom", 1);
    setup();
    "/clone/board/hu_b"->foo();
}

