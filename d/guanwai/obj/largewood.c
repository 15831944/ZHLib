// largewood.c

#include <ansi.h>

inherit ITEM;

void create()
{
	set_name(WHT "ľ��" NOR, ({ "large wood", "wood" }));
	set_weight(120000);
	if (clonep())
		set_default_object(__FILE__);
	else
        {
                set("value", 2000);
		set("unit", "��");
		set("long", "����һ�����Գ���ɽ���ϺõĴ�ľ�ϡ�\n");
	}
	setup();
}

int fire(object me, object ob)
{
        return notify_fail("�üһ��ô���ľͷ��ҲҪ�㰡��\n");
}
