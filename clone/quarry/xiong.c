#include <ansi.h>
inherit QUARRY;

void create()
{
	set_name(NOR + WHT "����" NOR, ({ "hui xiong", "hui", "xiong" }));
	set("long", WHT "����һֻ��ľ޴������쳣�Ļ��ܡ�\n" NOR);

	set("age", 6);
        set("str", 50);
        set("dex", 20);
        set("con", 50);
        set("max_qi", 2000);
        set("max_jing", 2000);
        set("neili", 3000);
        set("max_neili", 3000);
        set("combat_exp", 300000);

        set("power", 45);
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
