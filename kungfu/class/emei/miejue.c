// miejue.c 灭绝师太
// Modified by That Oct.1997

inherit NPC;
inherit F_MASTER;
inherit F_QUESTER;
inherit F_COAGENT;

#include <ansi.h>
#include "emei.h"

string ask_for_quit();
string ask_me();

void create()
{
        set_name("灭绝师太", ({ "miejue shitai","miejue","shitai"}));
        set("long", "她是峨嵋派的第三代弟子，现任峨嵋派掌门人。\n");
        set("gender", "女性");
        set("age", 62);
        set("attitude", "peaceful");
        set("shen_type", 1);
        set("no_get", 1);
        set("class", "bonze");
        set("chat_chance_combat", 60);
        set("chat_msg_combat", ({
                (: perform_action, "sword.mie" :),
        }) );
        set("inquiry",([
                "秘籍"  :  (: ask_me :),
                "剃度"  : "要剃度找静玄。",
                "出家"  : "要剃度找静玄。",
                "还俗"  :  (: ask_for_quit :),
        ]));

        set("str", 29);
        set("int", 35);
        set("con", 31);
        set("dex", 30);

        set("max_qi", 4500);
        set("max_jing", 2200);
        set("neili", 6000);
        set("max_neili", 6000);
        set("jingli", 1200);
        set("max_jingli", 1200);

        set("combat_exp", 1850000);
        set_skill("persuading", 160);
        set_skill("throwing", 210);
        set_skill("force", 220);
        set_skill("dodge", 200);
        set_skill("finger", 190);
        set_skill("parry", 220);
        set_skill("strike", 190);
        set_skill("sword", 220);
        set_skill("blade", 200);
        set_skill("literate", 120);
        set_skill("mahayana", 220);
        set_skill("buddhism", 300);
        set_skill("jinding-zhang", 240);
        set_skill("tiangang-zhi", 190);
        set_skill("huifeng-jian", 220);
              set_skill("yitian-jian", 250);
            set_skill("yanxing-dao", 200);
        set_skill("zhutian-bu", 200);
        set_skill("emei-xinfa", 220);
        set_skill("linji-zhuang", 220);

        map_skill("force","linji-zhuang");
        map_skill("finger","tiangang-zhi");
        map_skill("dodge","zhutian-bu");
        map_skill("strike","jinding-zhang");
        map_skill("sword","huifeng-jian");
        map_skill("blade","yanxing-dao");
        map_skill("parry","huifeng-jian");
        create_family("峨嵋派", 3, "掌门人");

        setup();

	set_temp("apply/attack", 80);
	set_temp("apply/defense", 80);
	set_temp("apply/damage", 100);
	set_temp("apply/armor", 100);
       set("book_count",1);

        carry_object("/clone/weapon/changjian")->wield();
        carry_object("/d/city/obj/cloth.c")->wear();
}

void attempt_apprentice(object ob)
{
	string name,new_name;

        if (! permit_recruit(ob))
                return;

        if ((int)ob->query("shen") < 15000)
        {
                command("say " + RANK_D->query_respect(ob) +
                        "，你行侠仗义之事做的太少！实在是太少！");
                return;
        }

        if ((int)ob->query_skill("mahayana",1) < 100)
        {
                command("say 你大乘佛法的修为还不行。");
                return;
        }

        if ((int)ob->query_skill("emei-xinfa",1) < 100)
        {
                command("say 怎么回事？本门内功心法你怎么学的？"
                        "好好给我练去！");
                return;
        }

        command("say 好吧，我就收下你了。");
        command("say 以后你要像为师一样，把天下的恶人统统杀光！。");
        name = ob->query("purename");
        if (! name) name = ob->query("name");
	new_name = "静" + name[0..1];
        command("say 从今以后你的法名叫做" + new_name + "。");       	ob->set("name", new_name);
        command("recruit " + ob->query("id"));
}

string ask_for_quit()
{
        object me;
        mapping myfam;
        me = this_player();

        myfam = (mapping)me->query("family");
        if (!myfam || (myfam["family_name"] != "峨嵋派")) 
                return ("你是什么人？跑到这里来捣乱？\n");

        if( (string)me->query("class") != "bonze" )
                return "阿弥陀佛！你本是俗家人，何谈还俗？\n";

        me->set_temp("pending/quit_bonze", 1);
        command ("heng");
        command ("say 还俗？好！你滚出我们峨嵋派，找别人替你还俗去吧！\n");
        return "你好好的给我安心修炼，以后降妖除魔，别天天满脑子不正经。\n";
}

string ask_me()
{
 	object ob;
 	 	if (this_player()->query("family/master_id")!="miejue shitai")
 		return RANK_D->query_respect(this_player()) +
  		"非我弟子，不知此话从何谈起？";
 	if (query("book_count") < 1)
 		return "你来晚了，本派的秘籍不在此处。";
 	add("book_count", -1);
 	ob = new("/d/emei/obj/fojing");
 	ob->move(this_player());
 	return "好吧，这本「"+ob->name()+"」你拿回去好好钻研。";
} 

void reset()
{
	set("book_count",1);
}
