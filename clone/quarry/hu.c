#include <ansi.h>
inherit QUARRY;

void create()
{
	set_name(NOR + WHT "����" NOR, ({ "hu li", "hu", "li" }));
	set("long", WHT "����һֻ���ɵĺ���˫���������⣬͸��������\n" NOR);
        set("no_auto_kill", 1);

	set("age", 1);
	set("str", 30);
	set("dex", 30);
	set("max_qi", 800);
	set("max_jing", 800);
	set("combat_exp", 10000);

        set("power", 20);
        set("item1", __DIR__"item/lirou");
        set("item2", __DIR__"item/lipi");

        set_temp("apply/parry", 60);
        set_temp("apply/dodge", 60);
        set_temp("apply/attack", 30);
        set_temp("apply/defense", 60);
        set_temp("apply/unarmed_damage", 30);
        set_temp("apply/armor", 30);

	setup();
}
