//baobiao.c

inherit KNOWER;

void create()
{
        set_name("展令扬", ({ "zhan lingyang","zhan" }));
        set("gender", "男性");
        set("age", random(10) + 20);
set("title","御前护卫");
        set("str", 25);
	set("con", 25);
	set("spi", 25);
	set("dex", 25);
	set("int", 25);
        set("shen_type", -1);
    set("long", "他是龙太子的专署保镖，拥有着冷酷的外表和强壮的身躯。\n");
        set("combat_exp", 1000000);
	set("class", "fighter");
        set("attitude", "herosim");
        set_skill("unarmed", 200);
        set_skill("force", 200);
        set_skill("sword", 200);
        set_skill("dodge", 200);
        set_skill("parry", 200);
	set("max_qi", 1200);
	set("max_jing", 1200);
        set("max_neili", 2000);
        set("neili",2000);
        set("jiali", 150);
	set("max_jingli", 2000);
	set("jingli", 2000);

        setup();
        carry_object("/d/changan/npc/obj/sword")->wield();
        carry_object("/d/changan/npc/obj/zhanjia")->wear();
}

int accept_fight(object me)
{
        message_vision("展令扬对着$N喝道：找死啊，敢动我龙族太子，下地狱吧你！\n\n", me);
        return 0;
}

int heal_up()
{
        if (environment() && !is_fighting()) 
	{
                call_out("leave", 1);
                return 1;
	}
        return ::heal_up() + 1;
}

void leave()
{
        object stone;
        this_object()->add("time", 1);
        if ((int)this_object()->query("time") >= 3) 
	{
                message("vision", name() + "微笑道:“我先回侍卫府了"
                        "太子殿下，要是有人再来闹事的话，我会马上过来的！”\n",
                        environment());
                destruct(this_object());
	}
        return;
}
