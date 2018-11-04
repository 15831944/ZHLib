#include <ansi.h>

inherit ITEM;

void create()
{
	set_name("��¯", ({ "xiang lu", "lu" }) );
	set_weight(3000);
	set_max_encumbrance(5000);
	if( clonep() )
		set_default_object(__FILE__);
	else {
		set("unit", "��");
                set("long", "����һ�����ﳣ������¯��������������Ů�ǲ���(pushin)��Ը��\n");
		set("value", 1000);
		set("material", "gold");
		set("no_get",1);
		set("no_drop",1);
		set("amount",30);
	}
       set("box_count",1);
	setup();
}

void init()
{
	add_action("do_pushin", "pushin");
}

int do_pushin(string arg)
{
	object me, ob;
	
	me = this_player();

	if(!arg&&arg!="xiang") return notify_fail("��Ҫ��ʲô������\n");

	if( query("box_count") )
	{
		ob=new("/d/tianlongsi/obj/box");
		ob->move(me);
              add("box_count",-1);
		tell_object(me, "\n���Ȼ�������ڲ���ʱ��ʲô��ס�ˣ�\n��ǿ���ң�������һ�����ӡ�\n");
		return 1;
	}
	else
		return notify_fail("���һ��������¯���������ݡ�\n");
	return 0;
}
