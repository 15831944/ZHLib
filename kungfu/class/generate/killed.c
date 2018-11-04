// person used in quest

inherit CLASS_D("generate") + "/chinese";

int  accept_object(object who, object ob);

void random_move();
int  leave();
int  is_stay_in_room()	{ return 1; }

void create()
{
        ::create();
        set("gender",query("gender"));
	set("age", 30 + random(30));
        if (arrayp(query("from")) && sizeof(query("from")))
                set("long",query("from")[random(sizeof(query("form")))] + "\n");
        else
                set("long","");
	set("attitude", "friendly");
        set("chat_chance", 30);
        set("chat_msg", ({ (: random_move :) }));
        set("chat_chance_combat", 120);
        set("chat_msg_combat", ({
                (: exert_function, "powerup" :),
                (: exert_function, "recover" :),
	}));
        set("scale", 150);
	set_temp("apply/armor", 50);
	set_temp("apply/damage", 50);
	set_temp("born_time", time());
        keep_heart_beat();
}

void set_from_me(object me)
{
        int exp;
	mapping my;

        NPC_D->init_npc_skill(this_object(), NPC_D->check_level(me));
	my = query_entire_dbase();

        if (my["max_qi"] > 9000)
                my["max_qi"] = 9000;

	if (my["max_jing"] < my["max_qi"] / 2)
		my["max_jing"] = my["max_qi"] / 2;

        if (my["max_jing"] > 6000)
                my["max_jing"] = 6000;

	my["eff_jing"] = my["max_jing"];
	my["jing"] = my["max_jing"];
	my["eff_qi"] = my["max_qi"];
	my["qi"] = my["max_qi"];

        exp = me->query("combat_exp") * 11 / 10;
        if (exp > query("combat_exp"))
                set("combat_exp", exp);
}

int accept_fight(object ob)
{
        command("say �ã����ǾͱȻ��Ȼ���");
	command("yun powerup");
        kill_ob(ob);
        return 1;
}

int accept_hit(object ob)
{
        command("say ����ȥ�ɣ�");
	command("yun powerup");
        kill_ob(ob);
        return 1;
}

int accept_kill(object ob)
{
	command("say �ߣ�������");
	command("yun powerup");
	return 1;
}

void random_move()
{
	if (time() - query_temp("born_time") > 900)
	{
		message_vision("$N����ææ�����ˡ�\n", this_object());
		destruct(this_object());
		return;
	}
        NPC_D->random_move(this_object());
}

