#include <ansi.h>
inherit QUARRY;

void create()
{
        set_name(NOR + CYN "�ڹ�" NOR, ({ "wu gui", "wu", "gui" }));
	set("long", CYN "����һֻ���ڹ꣬����������С�ˡ�\n" NOR);
        set("no_auto_kill", 1);

	set("age", 28);
        set("str", 5);
        set("dex", 2);
        set("con", 20);
        set("max_qi", 300);
        set("max_jing", 300);
        set("combat_exp", 1000);

        set("power", 5);
        set("item1", "/clone/herb/guijia");

        set_temp("apply/parry", 60);
        set_temp("apply/dodge", 60);
        set_temp("apply/attack", 30);
        set_temp("apply/defense", 60);
        set_temp("apply/unarmed_damage", 30);
        set_temp("apply/armor", 30);

	setup();
}