//zhangwuji.c

inherit F_MASTER;
inherit F_QUESTER;
inherit F_UNIQUE;
inherit NPC;

#include <ansi.h>
#include "mingjiao.h"

void greeting(object ob);
string ask_ling();

void create()
{
    seteuid(getuid());
    set_name("张无忌", ({ "zhang wuji", "zhang", "wuji" }));
    set("long", @LONG
明教教主张无忌，统领天下十万教众，豪气干云，叱咤千秋，
「九阳神功」、「乾坤大挪移」独步天下，是江湖中不世出的
少年英雄。
LONG );
    set("title",HIG "明教" HIM " 教主" NOR);
    set("gender", "男性");
    set("age", 20);
        set("no_get", 1);
    set("shen_type",1);
    set("attitude", "friendly");
    set("class", "fighter");

    set("str", 33);
    set("int", 35);
    set("con", 38);
    set("dex", 33);
        set("per",28);

    set("qi", 5800);
    set("max_qi", 5800);
    set("jing", 2700);
    set("max_jing", 2700);
    set("neili", 8000);
    set("max_neili", 8000);
    set("jiali", 120);

    set("combat_exp", 2900000);
    set("score", 455000);
    
    set_skill("force", 340);
    set_skill("cuff", 300);
    set_skill("dodge", 200);
    set_skill("parry", 350);
    set_skill("sword", 260);
    set_skill("strike",260);
    set_skill("literate", 220);

    set_skill("shenghuo-xuanming", 340);
    set_skill("shenghuo-xinfa", 280);
    set_skill("qiankun-danuoyi", 350);
    set_skill("lingxu-bu", 250);
    set_skill("shenghuo-quan", 250);
    set_skill("liehuo-jian", 260);
    set_skill("shenghuo-ling", 230);
    set_skill("guangming-zhang", 220);

    map_skill("force", "shenghuo-xuanming");
    map_skill("dodge", "lingxu-bu");
    map_skill("cuff", "shenghuo-quan");
    map_skill("sword","shenghuo-ling");
    map_skill("parry","qiankun-danuoyi");
    map_skill("strike","guangming-zhang");

    prepare_skill("cuff", "shenghuo-quan");
    prepare_skill("strike","guangming-zhang");

    set("inherit_title",HIG"明教"HIY"光明使者"NOR);

    create_family("明教", 33, "教主");

    set("chat_chance",2);
    set("chat_msg",({
        "张无忌愤然说道“大丈夫当以国为家, 捐躯沙场, 抗元大业未成, 同辈仍需努力!”\n",
        "张无忌叹道“人生失一知己, 生亦何欢, 死亦何忧, 敏儿, 你在哪里?”\n",
        "张无忌道“我教兄弟听了: 生于乱世, 当克己为公, 行侠仗义, 荡寇驱魔!”\n",
    }));

    set("inquiry",([
	  "明教" :     "你打听我们明教做什么？。\n",
          "金毛狮王" : "那是我义父谢大侠的职司。\n",
          "谢逊" :     "他就是我义父的大号。\n",
          "张翠山" :   "你想找我父亲有事麽? \n",
          "殷素素" :   "我妈是明尊座下紫微堂主。\n",
          "张三丰" :   "我太师父近来可好? \n",
          "赵敏" :     "人生失一知己, 生亦何欢, 死亦何忧, 敏儿, 你在哪里?\n",
          "小昭" :     "小昭我可一直念着她的好处。\n",
          "周芷若" :   "找她就去峨嵋山, 别来烦我。\n",
          "铁焰令"      : (: ask_ling :),
    ]));
    setup();
    carry_object("/clone/book/shenghuo-ling")->wield();
    add_money("silver",70);
}

void init()
{
	object ob;

	::init();

	if (interactive(this_player()) && this_player()->query_temp("fighting"))
	{
		COMBAT_D->do_attack(this_object(), this_player(), query_temp("weapon") );
		this_player()->add_temp("beat_count", 1);
	}       
	if( interactive(ob=this_player()) && !is_fighting())
	{
		remove_call_out("greeting");
		call_out("greeting",1,ob);
	}
}

void greeting(object ob)
{
	if (! ob || environment(ob)!=environment()) return;
	if ((int)ob->query("shen") < -50000)
	{
		command("wield yitian jian");
		command("hit" + (string)ob->query("id"));
        	command("unwield yitian jian");
	} else
	if ((int)ob->query("shen") < -5000)
	{
		command("say 魔从心起，于武学不利，其道必诛，劝君放下屠刀，"
		        "立地成佛。");
	} else
	if((int)ob->query("shen") < -100)
	{
		command("say 这位朋友，人行江湖，言行当正，切务走进邪魔歪道。");
	} else
	if((int)ob->query("shen") >= 0)
	{
		command("say 光明正道任人走，劝君多加保重。");
	} else
	if((int)ob->query("shen") > 50000)
	{
		command("say 大侠在上，受无忌一礼，大侠它日必为武林翘楚。");
	}
	return;
}

int accept_fight(object ob)
{
    	if ((ob->query("combat_exp") < 30000) && (ob->query("shen") > 0))
    	{
        	message_vision("武林中人最忌争强斗狠，你不是我的对手，"
			       "回去吧。\n",ob);
        	return 0;
    	}
    	message_vision("张无忌一拱手说道：这位" + RANK_D->query_respect(ob) +
		       "，在下领教了。\n", ob);
    	return 1;
}

string ask_ling()
{
	mapping family, skl; 
	string *sname;
	object ob;
	int i;
	
	if ( !(family = this_player()->query("family")) || family["family_name"] != "明教")
		return RANK_D->query_respect(this_player()) + "与本教素无来往，不知此话从何谈起？";

	skl = this_player()->query_skills();
	sname  = sort_array( keys(skl), (: strcmp :) );

	for(i=0; i<sizeof(skl); i++) 
	{
		if (skl[sname[i]] < 30) 
		return RANK_D->query_respect(this_player()) + 
		"功力不够，不能领取铁焰令。";
	}

	ob = new("d/mingjiao/obj/tieyanling");
	ob->move(this_player());
	message_vision("$N要得一面铁焰令。\n",this_player());

	return "好吧，凭这面铁焰令，你可自由向你的尊长挑战。";

}

void attempt_apprentice(object ob)
{
	object me  = this_object();
	mapping ob_fam;
	mapping my_fam  = me->query("family");

	string name, new_name;

        if (!(ob_fam = ob->query("family")) || ob_fam["family_name"] != "明教")
	{
                command("say " + RANK_D->query_respect(ob) + "与本教素无来往，不知此话从何谈起？");
		return;
	}

	if ( ob_fam["generation"] > my_fam["generation"] + 2)
	{
                command("say " + RANK_D->query_respect(ob) + "，你先去找教内其他兄弟好好学学武功吧。");
		return;
	}

	if ( ob->query("combat_exp") < 1000000 )
	{
		command("say 你的经验太少，好好再去江湖闯荡闯荡，可别给我明教丢脸啊 !");
		return;
	}

        command("say 恩，好！本教又培养出一位江湖高手，真是可喜可贺 !");

        command("say 恭喜你荣升为明教光明使者！");
        command("recruit " + ob->query("id"));

	return;
}
