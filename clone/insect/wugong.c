// wugong.c ���

#include <ansi.h>

inherit POISON_INSECT;

void create()
{
	set_name("���", ({ "wu gong" }) );
        set_weight(100);
	set("race", "����");
       set("subrace", "����");
	set("age", 2);
	set("long", "һֻ��򼡣\n");
	set("attitude", "peaceful");
	set("str", 20);
	set("con", 20);
        set("unit", "ֻ");

        set("insect_poison", ([
                "level"  : 35,
                "maximum": 20,
        ]));

	set("combat_exp", 100);

	setup();
}
