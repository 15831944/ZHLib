#include <ansi.h>
inherit QUARRY;

void create()
{
	set_name(HIW "��¹" NOR, ({ "mi lu", "mi", "lu" }));
	set("long", HIW "����һֻ�ж����ݵ���¹��\n" NOR);
        set("no_auto_kill", 1);

	set("age", 3);
	set("str", 20);
	set("dex", 25);
	set("max_qi", 1000);
	set("max_jing", 1000);
	set("combat_exp", 20000);

        set("power", 15);
        set("item1", __DIR__"item/lurou");
        set("item2", "/clone/herb/lurong");

        set_temp("apply/parry", 60);
        set_temp("apply/dodge", 60);
        set_temp("apply/attack", 30);
        set_temp("apply/defense", 60);
        set_temp("apply/unarmed_damage", 30);
        set_temp("apply/armor", 30);

	setup();
}
