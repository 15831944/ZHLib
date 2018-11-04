// Pill: sanxiaosan.c
#include <ansi.h>
inherit ITEM;

void create()
{
	set_name("��Ц��ңɢ", ({"sanxiao san", "san"}));
	if (clonep())
		set_default_object(__FILE__);
	else {
		set("long", "һ����ɫ�ķ�ĩ, �����Ӳ���Ѱ����Ʒ. \n");
		set("unit", "��");
		set("poison_type", "sanxiao_poison");
                set("can_pour", 1);
                set("can_daub", 0);
                set("can_drug", 1);
                set("poison", ([
                        "level" : 200,
                        "id"    : "ding chunqiu",
                        "name"  : "��Ц��ңɢ��",
                        "duration": 20,
                ]));
		set("value", 2000);
                set("no_sell", 1);
	}
	setup();
}

int init()
{
	add_action("do_eat", "eat");
}

int do_eat(string arg)
{
	object me = this_player();

	if (! arg || ! id(arg))
		return notify_fail("��Ҫ��ʲô��\n");

        message_vision("$N��ͷ����һ��" + name() + "��\n", me);
        me->set_temp("die_reason", "������Ц��ңɢ�������쳣�Ҹ�");
        me->die();
        destruct(this_object());
	return 1;
}
