#include <ansi.h>
inherit QUARRY;

void create()
{
	set_name(HIY "��Ǯ��" NOR, ({ "jinqian bao", "jinqian", "bao" }));
	set("long", HIY "����һֻȫ�����Ž�Ǯ���Ƶ��۱���\n" NOR);

	set("age", 3);
	set("str", 35);
	set("dex", 50);
	set("max_qi", 2200);
	set("max_jing", 2200);
	set("combat_exp", 80000);

        set("power", 35);
        set("item1", __DIR__"item/baorou");
        set("item2", __DIR__"item/baopi");

        set_temp("apply/parry", 60);
        set_temp("apply/dodge", 60);
        set_temp("apply/attack", 30);
        set_temp("apply/defense", 60);
        set_temp("apply/unarmed_damage", 30);
        set_temp("apply/armor", 30);

	setup();
}
