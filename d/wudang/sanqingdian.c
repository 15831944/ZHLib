// sanqingdian.c �����
// by Xiang

inherit ROOM;

void create()
{
        set("short", "�����");
        set("long", @LONG
���������������������䵱�ɻ�͵ĵص㡣����Ԫʼ����̫�ϵ�
���������Ͼ��������㰸���������ơ���ǽ���ż���̫ʦ�Σ����Ϸ��ż�
�����š��������������ȣ�����������Ĺ㳡���ϱ��Ǻ�Ժ��
LONG );
        set("valid_startroom", 1);
        set("exits", ([
                "north" : __DIR__"guangchang",
                "south" : __DIR__"houyuan",
                "east"  : __DIR__"donglang1",
                "west"  : __DIR__"xilang",
        ]));
        set("objects", ([
                CLASS_D("wudang") + "/guxu" : 1,
                CLASS_D("wudang") + "/song" : 1
        ]));
        setup();
        "/clone/board/wudang_b"->foo();
}

int valid_leave(object me, string dir)
{
        object guarder;

        if (dir != "west")
                return 1;

        if (! objectp(guarder = present("song yuanqiao", environment(me))))
                return 1;

        return guarder->permit_pass(me, dir);
}
