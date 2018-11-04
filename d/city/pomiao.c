// Room: /city/pomiao.c

#include <room.h>
inherit ROOM;

void create()
{
	set("short", "������");
	set("long", @LONG
����һ���������õ��������������ưܲ�����������������һ�ԣ����ϵ�
��Ҳ�����˻ҳ���һ����֪���Ѿ��ܾ�û�������������ˡ����з��Ÿ����㰸��
�������ҵ����ż�����ʣ�����ļ���ͷ��Ҳ��������Ϊ���ε�ԭ��ɣ���˵ؤ
�ｭ�Ϸֶ�ͱ����ڴ˴����㰸�ڶ����ģ������±��и���(dong)��
LONG );
	set("valid_startroom", 1);
	set("exits", ([
		"west"  : "/d/gaibang/shoushe",
		"east"  : "/d/gaibang/sheyuan",
		"south" : __DIR__"ml4",
		"enter" : __DIR__"gbandao",
	]));
	set("objects", ([
		CLASS_D("gaibang") + "/lu" : 1,
		CLASS_D("gaibang") + "/peng" : 1,
	]));
	create_door("enter", "С��", "out", DOOR_CLOSED);
	setup();
	"/clone/board/gaibang_b"->foo();
}

void init()
{
        add_action("do_enter", "enter");
        add_action("do_enter", "zuan");
}

int do_enter(string arg)
{
	object me;
	mapping fam;

	me = this_player();

	if( !arg || arg=="" ) return 0;

	if( arg=="dong" )
	{
		if( (fam = me->query("family")) && fam["family_name"] == "ؤ��" ) 
		{
			message("vision",
				me->name() + "����ؤ�����ǹ���һ�������㰸�µĶ������˽�ȥ��\n",
				environment(me), ({me}) );
			me->move("/d/gaibang/undergb");
                	message("vision",
				me->name() + "�Ӷ������˽�����\n",
                		environment(me), ({me}) );
			return 1;
		}
		else 
			return notify_fail("��ôС�Ķ�������ý�ȥ��\n");
	}
}	

int valid_leave(object me, string dir)
{
	object ob;
        mapping myfam;

        myfam = me->query("family");

        if ((! mapp(myfam) || myfam["family_name"] != "ؤ��") &&
            (dir == "west" || dir == "east") &&
            objectp(ob = present("lu youjiao", environment(me))) &&
            living(ob))
	{
           	return notify_fail("³�н���ס��˵���˴���"
				   "������أ���ֹ����\n");
	}

        return ::valid_leave(me, dir);
}