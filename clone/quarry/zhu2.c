#include <ansi.h>
inherit QUARRY;

void create()
{
	set_name(NOR + YEL "Ұ��" NOR, ({ "ye zhu", "ye", "zhu" }));
	set("long", YEL "����һֻ�����쳣��Ұ��\n" NOR);

	set("age", 1);
	set("str", 35);
	set("dex", 40);
	set("max_qi", 1600);
	set("max_jing", 1600);
	set("combat_exp", 80000);

        set("power", 32);
        set("item1", __DIR__"item/zhurou");

        set_temp("apply/parry", 60);
        set_temp("apply/dodge", 60);
        set_temp("apply/attack", 30);
        set_temp("apply/defense", 60);
        set_temp("apply/unarmed_damage", 30);
        set_temp("apply/armor", 30);

	setup();
}
