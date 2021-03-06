#pragma save_binary


// Smallfish@Jdmr
#include <ansi.h>
inherit NPC;
void create()
{
        set_name("呆搬", ({ "dai ban" }) );
        set("gender", "女性" );
        set("age", 62);
set("long","呆搬是一个很独特的女孩，生性寡僻，专门与动物为伍，擅长驯兽（xunlian）。\n");
        set("combat_exp", 50000000);
	set("title",HIW"动物爱好者"NOR);
        set("attitude", "friendly");
        set("chat_chance", 15);
        set("per",29);
        setup();
        carry_object("/clone/cloth/cloth")->wear();

}

void init()
{	
        object ob;
        ::init();
        if( interactive(ob = this_player()) && !is_fighting() ) {
                remove_call_out("greeting");
                call_out("greeting", 1, ob);
        }
        add_action("do_train", "xunlian");

}

void greeting(object ob)
{
        if( !ob || environment(ob) != environment() ) return;
        switch( random(5) ) {
                case 0:
                        say( "呆搬说道：这位" + RANK_D->query_respect(ob)
                                + "，神农架你去过么？\n");
                        break;
                case 1:
                        say( "呆搬叹道：这位" + RANK_D->query_respect(ob)
                                + "，我帮你驯兽，你给我一份去神农架的地图吧。\n");
                        break;
        }
}

int do_train(string arg)
{
	object me,pet,gold;
	int cost;
        me = this_player();
        if(me->is_busy())
        return notify_fail("你上一个动作还没有完成。\n");
	if(!arg) return notify_fail("呆搬道：＂你要驯什么呀？＂\n");
	pet = present(arg,environment());
	if(!objectp(pet)) return notify_fail("呆搬道：＂你要驯什么呀？＂\n");
	if(pet->query("possessed") != me )
	return notify_fail("呆搬道：＂那好象不是你的吧？＂\n");
//okey we identified the target, now the cost:
	cost = (int) pet->query("obedience");
	cost *= cost;
        cost /= 20;
	if (cost < 1) cost = 1;
	gold = present("gold_money", me);
        if(!gold) return notify_fail("你身上没有金子。\n");
        if((int) gold->query_amount() < cost)
        return notify_fail("你身上没有"+chinese_number(cost)+"两金子。\n");
	if((int)me->query("score") < cost/10)
	return notify_fail("你的评价不够"+chinese_number(cost/10)+"点。\n");
	pet->add("obedience",1);
	pet->save();
	gold->add_amount(-cost);
	me->add("score",-cost/10);
	command("say 好了！\n");
	return 1;
}
