#include <ansi.h>
inherit QUARRY;

void create()
{
	set_name(NOR + WHT "ɽ��" NOR, ({ "shan zhu", "shan", "zhu" }));
	set("long", WHT "����һֻ�ǳ����͵�ɽ��\n" NOR);

	set("age", 1);
	set("str", 35);
	set("dex", 40);
	set("max_qi", 1400);
	set("max_jing", 1400);
	set("combat_exp", 30000);

        set("power", 28);
        set("item1", __DIR__"item/zhurou");

        set_temp("apply/parry", 60);
        set_temp("apply/dodge", 60);
        set_temp("apply/attack", 30);
        set_temp("apply/defense", 60);
        set_temp("apply/unarmed_damage", 30);
        set_temp("apply/armor", 30);

	setup();
}