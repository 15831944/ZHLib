// whisper.c

#include <ansi.h>

inherit F_CLEAN_UP;

int ultra_whisper(object me, object who, string msg);
private void special_bonus(object me, mixed arg);
private void money_bonus(object me, mixed arg);

int main(object me, string arg)
{
	string dest, msg;
       int r;
	object ob;
        object env;
        mixed info;

	if (! arg )
       return notify_fail("你要对谁耳语些什么？\n");
       if ( sscanf(arg, "%s to %s", msg, dest) != 2 
            && sscanf(arg, "%s %s", dest, msg) != 2 )
	return notify_fail("指令格式：whisper <讯息> to <某人>\n");

        env = environment(me);
	ob = present(dest, env);

	if (! ob || ! ob->is_character())
		return notify_fail("你要对谁耳语？\n");

        if (ob == me)
		return notify_fail("你无法将嘴凑到自己的耳朵旁说话。\n");

        if (me->ban_say(1))
                return 0;

        if (info = env->query("no_say"))
        {
                if (stringp(info))
                {
                        write(info);
                        return 1;
                }

                write("这个地方不能讲话。\n");
                return 1;
        }

        if (me->query("doing") == "scheme")
        {
                if (me->query("jing") < 100)
                        return notify_fail("你现在的精神不济，等一会儿吧。\n");
                me->add("jing", -50);
        }

	write(WHT "你在" + ob->name() + WHT "的耳边悄声说道：" +
	      msg + "\n" NOR);
	tell_room(environment(me), me->name() + "在" + ob->name()
		+ "耳边小声地说了些话。\n", ({ me, ob }));

	if (! userp(ob)) ob->relay_whisper(me, msg);
	else
		tell_object(ob, WHT + me->name() +
				WHT "在你的耳边悄声说道：" + msg + "\n" NOR);
					if (! userp(ob)) 
       {
              r = 0;
              if (me->query("bang_quest") && me->query("bang_quest/type") == "传口信")
                      r = ultra_whisper(me,ob,msg);
              if (!r)
                      ob->ultra_whisper(me, msg);
       }
	else
		tell_object(ob, WHT + me->name() +
				WHT "在你的耳边悄声说道：" + msg + "\n" NOR);

      //配合长安府传暗号任务新增部分
       if ( ! userp(ob) )
       {
          if ( me->query("changanjob/kind") != "whisper" ||
               me->query("changanjob/target") != ob->name() )  
              tell_room(environment(me), CYN + ob->name() + "说道："NOR + HIG
              "你在我耳边即即歪歪说什么?真是牛头不对马嘴。\n"NOR);
          else
              {
                 if ( me->query("changanjob/whisper") )
                 {
                      tell_room(environment(me), CYN + ob->name() + "说道："NOR 
                                 + HIG "啊,多谢把暗号带到。\n"NOR);           
                      if ( me->query("changanjob/whisper") == msg )
                           me->set("changanjob/ok",1);                     
                      me->delete("changanjob/whisper");  
                 } else
                 {
                      tell_room(environment(me), CYN + ob->name() + "说道："NOR 
                                  + HIG"你已经告诉我暗号了呀!\n"NOR);   
                 }            
                 
	if (! userp(ob)) 
       {
              r = 0;
                      if ((me->query("quest_dg") && me->query("quest_dg")["type"] == "传") ||
                          (me->query("quest_kh") && me->query("quest_kh")["type"] == "传") ||
                          (me->query("quest_hs") && me->query("quest_hs")["type"] == "传") ||
                          (me->query("quest_sn") && me->query("quest_sn")["type"] == "传"))
                              r = ultra_whisper(me, ob, msg);

              if (!r)
                      ob->ultra_whisper(me, msg);
       }
	else
		tell_object(ob, WHT + me->name() +
				WHT "在你的耳边悄声说道：" + msg + "\n" NOR);
               }
       }
	return 1;
}

int ultra_whisper(object me, object who, string msg)
{
        mapping quest;
        mapping bang_quest,b;

        int level;
        int i;
        int exp;
        int pot;
        int score;
        int weiwang;
        int mar;
	int quest_count;
        string the_quest;
	mixed special = 0;
        mixed money = 0;

        quest = me->query("quest_dg");
        bang_quest = me->query("bang_quest");
        
        //传错人了
        if (bang_quest["target"] != base_name(who))
                return 0;

        //传错话了
        if (msg != bang_quest["send_msg"])
                return 0;

        message_sort("$N面色凝重，一边听着一边对$n使劲的点头：“这位" +
                     RANK_D->query_respect(who) +
                     "，多谢你把话带到！”\n", who, me);

        // 奖励
        me->add("pk_score",-2);
        if (me->query("pk_score") < 0) me->set("pk_score",0);

        exp = bang_quest["bonus"];
        exp += random(exp/2);
        exp += me->query("combat_exp")/5000;
        pot = exp/(2 + random(2));
        score = 5 + random(10);
        weiwang = 5 + random(10);

        b = ([ "exp" : exp,
               "pot" : pot,
               "score" : score,
               "weiwang" : weiwang,
               "prompt": "在把口信传给" + who->name() +
                         HIG "的过程中，经过锻炼" ]);

        QUEST_D->delay_bonus(me, b);

        me->delete("bang_quest");
        me->add_temp("finish_bang_times",1);

        the_quest = "独孤求败";
        if (!quest || quest["type"] != "传")
        {
                quest = me->query("quest_kh");
                the_quest = "葵花太监";
        }
        if (!quest || quest["type"] != "传")
        {
                quest = me->query("quest_hs");
                the_quest = "黄裳";
        }
        if (!quest || quest["type"] != "传")
        {
                quest = me->query("quest_sn");
                the_quest = "南海神尼";
        }

        if (!quest) return 0;

        if (userp(who)) return 0;

        //传错人了
        if (quest["name"] != who->name(1))
                return 0;

        //传错话了
        if (msg != quest["answer"])
                return 0;

        message_sort("$N面色凝重，一边听着一边对$n使劲的点头：“这位" +
                     RANK_D->query_respect(me) +
                     "，多谢你把口令带到！”\n", who, me);

        // 奖励
        level = quest["level"]+1;
        if (the_quest == "独孤求败")
        {
                if((i=me->query("questdg_times")) < 8)   i = 15-i;
                else i = 1;
        }
        if (the_quest == "葵花太监")
        {
                if((i=me->query("questkh_times")) < 15)   i = 15-i;
                else i = 1;
        }
        if (the_quest == "南海神尼")
        {
                if((i=me->query("questsn_times")) < 15)   i = 15-i;
                else i = 1;
        }
        if (the_quest == "黄裳")
        {
                if((i=me->query("quesths_times")) < 15)   i = 15-i;
                else i = 1;
        }

        exp = level*100 + quest["bonus"]*5;
        exp += random(exp/2);
        exp /= i;
        pot = exp/(2+random(2));
        score = random(exp/20);
        weiwang = random(exp/15);
        mar = 10 + random(40);

        QUEST_D->bonus(me, ([ "exp" : exp, "pot" : pot, "mar" : mar,
                              "weiwang" : weiwang, "score" : score ]), 1);

        if (the_quest == "独孤求败")
        {
                me->add("questdg_times",1);
                quest_count = me->query("questdg_times")%500;
                me->delete("quest_dg");
        }
        if (the_quest == "葵花太监")
        {
                me->add("questkh_times",1);
                quest_count = me->query("questkh_times")%500;
                me->delete("quest_kh");
        }
        if (the_quest == "黄裳")
        {
                me->add("quesths_times",1);
                quest_count = me->query("quesths_times")%500;
                me->delete("quest_hs");
        }
        if (the_quest == "南海神尼")
        {
                me->add("questsn_times",1);
                quest_count = me->query("questsn_times")%500;
                me->delete("quest_sn");
        }

        if (quest_count == 50)
		special = 1;
	else if (quest_count == 100)
		special = "/clone/gift/puti-zi";
        else if (quest_count == 150)
                money = 1;
        else if (quest_count == 200)
                money = 1;
        else if (quest_count == 250)
                money = 1;
   	else if (quest_count == 300)
		special = "/clone/misc/tianxiang";
   	else if (quest_count == 350)
		special = "/clone/misc/tianxiang";
   	else if (quest_count == 400)
                special = "/clone/misc/jiuzhuan";
	else if (quest_count == 450)
		special = "/clone/gift/jiuzhuan";
   	else if (quest_count == 0)
                special = "/clone/gift/xuanhuang";

	if (special) special_bonus(me, special);
        if (money) money_bonus(me,money);
            		
        me->add("total_hatred",-5);
        if (me->query("total_hatred") < 0) me->set("total_hatred",0);
        return 1;
}

private void special_bonus(object me, mixed arg)
{
        string *ob_list = ({
                "/clone/gift/xiandan",
                "/clone/gift/shenliwan",
                "/clone/gift/unknowdan",
                "/clone/gift/xisuidan",
                "/d/item/obj/hantie",
                "/d/item/obj/wujins",
                "/d/item/obj/butian",
                "/d/item/obj/tiancs",
        });
        object ob;

        if (stringp(arg))
                ob = new(arg);
        else
                ob = new(ob_list[random(sizeof(ob_list))]);
        ob->move(me, 1);
        tell_object(me, HIM "你获得了一" + ob->query("unit") + ob->name() +
                        HIM "。\n" NOR);
}

void money_bonus(object me, mixed arg)
{
        string *ob_list = ({
                "/clone/gift/jinkuai",
                "/clone/gift/jintiao",
                "/clone/gift/xiaoyuanbao",
                "/clone/gift/dayuanbao",
                "/clone/gift/jinding",
        });
        object ob;

        if (stringp(arg))
                ob = new(arg);
        else
                ob = new(ob_list[random(sizeof(ob_list))]);

        ob->move(me,1);

        tell_object(me, HIM "你获得了一" + ob->query("unit") + ob->name() +
                        HIM "。\n" NOR);
}

int help(object me)
{
	write( @TEXT
指令格式：whisper <某人> about <讯息>

这个指令可以用来和同一房间中的人耳语，包括 NPC 在内。
其中的about可以省略。
TEXT );
	return 1;
}
