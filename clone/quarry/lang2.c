#include <ansi.h>
inherit QUARRY;

void create()
{
	set_name(NOR + WHT "����" NOR, ({ "e lang", "e", "lang" }));
	set("long", WHT "����һֻ�ײм�����Ұ�ǡ�\n" NOR);

	set("age", 1);
	set("str", 35);
	set("dex", 40);
	set("max_qi", 1500);
	set("max_jing", 1500);
	set("combat_exp", 80000);

        set("power", 30);
        set("item1", __DIR__"item/langrou");
        set("item2", __DIR__"item/langpi");

        set_temp("apply/parry", 60);
        set_temp("apply/dodge", 60);
        set_temp("apply/attack", 30);
        set_temp("apply/defense", 60);
        set_temp("apply/unarmed_damage", 30);
        set_temp("apply/armor", 30);

	setup();
}
