#include <ansi.h>
inherit QUARRY;

void create()
{
	set_name(NOR + CYN "����" NOR, ({ "hei xiong", "hei", "xiong" }));
	set("long", CYN "����һֻ��ľ޴������쳣�ĺ��ܡ�\n" NOR);

	set("age", 8);
        set("str", 50);
        set("dex", 20);
        set("con", 50);
        set("max_qi", 3000);
        set("max_jing", 3000);
        set("neili", 1500);
        set("max_neili", 1500);
        set("combat_exp", 500000);

        set("power", 50);
        set("item1", __DIR__"item/xiongrou");
        set("item2", __DIR__"item/xiongpi");
        set("item3", "/clone/herb/xiongdan");

        set_temp("apply/parry", 60);
        set_temp("apply/dodge", 60);
        set_temp("apply/attack", 30);
        set_temp("apply/defense", 60);
        set_temp("apply/unarmed_damage", 30);
        set_temp("apply/armor", 30);

	setup();
}
