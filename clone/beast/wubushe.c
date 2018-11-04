// wubushe.c

#include <ansi.h>

inherit SNAKE;

void create()
{
	set_name("�岽��", ({ "wubushe" }) );
	set("long",	"�岽���Ǹ����ط����ߣ��ഫ�ж���·�岽���е��С�\n");

	set("race", "����");
	set("age", 3);
	set("attitude", "peaceful");

	set("max_ging", 180);
	set("max_qi", 300);

	set("str", 10);
	set("con", 50);

	set("limbs", ({ "ͷ��", "����", "β��" }) );
	set("verbs", ({ "bite" }) );

        set("snake_poison", ([
                "level"  : 50,
                "perhit" : 25,
                "remain" : 50,
                "maximum": 50,
                "supply" : 2,
        ]));

	set_temp("apply/attack",  50);
	set_temp("apply/damage",  10);
	set_temp("apply/defense", 70);
	set_temp("apply/armor",   10);

	set("combat_exp", 6000);
	setup();
}

int convert(string arg)
{
	object me = this_player();
	object ob;

	if (arg!="snake" && arg!="wubushe") return 0;
	if (me->query("family/family_name") != "ŷ������") 
		return notify_fail("�㲻�ܻ���Ϊ�ȡ�\n");
	if (random(me->query_skill("training",1)) <20) {
		kill_ob(me);
		return 1;
	}
	message_vision("$N���ְ�ס�岽�ߵ�ͷ�������ḧ���ߴ磬���������дʣ�Ƭ�̼佫�߻�Ϊһ�����ȡ�\n",
		me,);
	        ob = new("/d/baituo/obj/shezhang");
        ob->move(environment(this_object()));
        destruct(this_object());
	return 1;
}