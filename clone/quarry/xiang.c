#include <ansi.h>
inherit QUARRY;

void create()
{
	set_name(NOR + CYN "����" NOR, ({ "da xiang", "da", "xiang" }));
	set("long", CYN "����һֻ�����С�ľ�������֮����\n" NOR);
        set("no_auto_kill", 1);

	set("age", 3);
	set("str", 100);
	set("con", 100);
	set("dex", 50);
	set("max_qi", 1200);
	set("max_jing", 1200);
        set("neili", 3000);
        set("max_neili", 3000);
	set("combat_exp", 700000);

        set_skill("unarmed", 50);
        set_skill("dodge", 50);
        set_skill("parry", 50);
        set_skill("force", 50);

        set("power", 100);
        set("item1", __DIR__"item/xiangrou");
        set("item2", __DIR__"item/xiangya");

        set_temp("apply/parry", 60);
        set_temp("apply/dodge", 60);
        set_temp("apply/attack", 30);
        set_temp("apply/defense", 60);
        set_temp("apply/unarmed_damage", 30);
        set_temp("apply/armor", 30);

	setup();
}