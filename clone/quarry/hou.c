#include <ansi.h>
inherit QUARRY;

void create()
{
	set_name(NOR + YEL "����" NOR, ({ "hou zi", "hou", "zi" }));
	set("long", YEL "����һֻ�ж����ݵĴ���\n" NOR);
        set("no_auto_kill", 1);

	set("age", 1);
	set("str", 22);
	set("dex", 30);
	set("max_qi", 600);
	set("max_jing", 600);
	set("combat_exp", 8000);

        set("power", 15);

        set_temp("apply/parry", 60);
        set_temp("apply/dodge", 60);
        set_temp("apply/attack", 30);
        set_temp("apply/defense", 60);
        set_temp("apply/unarmed_damage", 30);
        set_temp("apply/armor", 30);

	setup();
}
