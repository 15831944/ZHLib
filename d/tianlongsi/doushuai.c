inherit ROOM;

void create()
{
        set("short", "���ʴ�ʿԺ");
        set("long",@LONG
����һ��ΰ������ܵ�����Զ�ĵط��������Ͼ���������������ɮ��
��֮������Ĳ���á����ǳ��˲������״���ĵط�������ò�Ҫ���Դ���
��������ȷ���ܸ���ɮ�Ǵ�ȥ����Ϣ��
LONG );
        set("exits", ([
                "north" : __DIR__"qingxinge",
		"south" : __DIR__"banruotai",
		"northeast" : __DIR__"doumugong",
		"northwest" : __DIR__"sanwugong",
	]));
	set("objects",([
                __DIR__"obj/xianglu" : 1,
        ]));
        set("no_clean_up",0);
        setup();
}

void reset()
{
        object ob;
        ::reset();
        ob = present("xiang lu",this_object());
        if (!ob) return;
        if (!ob->query("box_count")) ob->set("box_count",1);
}
