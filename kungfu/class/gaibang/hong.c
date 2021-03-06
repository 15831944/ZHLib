//hong.c
//modified apprentice conditions for hx

#include <ansi.h>

inherit NPC;
inherit F_MASTER;
inherit F_QUESTER;

int try_to_learn_ds();
int try_to_learn_db();
mixed ask_me();

void create()
{
        set_name("洪七公", ({"hong qigong", "hong", "qigong"}));
        set("nickname", "九指神丐");
        set("gender", "男性");
        set("age", 75);
        set("long", 
"他一张长方脸，颌下微须，粗手大脚，身上衣服东一块西一块的打满了补丁，
却洗得干干净净，背上负着个朱红漆的大葫芦。\n");
        set("attitude", "peaceful");
        set("str", 37);
        set("int", 31);
        set("con", 33);
        set("dex", 32);
        set("rank", 10);
        set("chat_chance", 1);
        set("chat_msg", ({
                "洪七公叹了口气道：“唉……何时能再吃到蓉儿做的「叫化鸡」啊……”\n",
                "洪七公说道：“俗话说「吃在江南」，所以老叫化特地跑来扬州看看。”\n",
                "洪七公喃喃道：“我们丐帮的「降龙十八掌」是天下最霸道的掌法。”\n",
        }));
        set("chat_chance_combat", 1);
        set("chat_msg_combat", ({
                (: perform_action, "strike.xianglong" :),
                (: exert_function, "recover" :),
        }) );
        set("inquiry", ([
                "绝招" : (: ask_me :),
                "绝技" : (: ask_me :),
                "天下无狗" : (: ask_me :),
        ]));
        set("book_count",1);
        set("qi", 5200);
        set("max_qi", 5200);
        set("jing", 2700);
        set("max_jing", 2700);
        set("neili", 7000);
        set("max_neili", 7000);
        set("jiali", 120);
        set("combat_exp", 2500000);
        set("score", 50000);

        set_skill("force", 270);
        set_skill("jiaohua-neigong", 250);
        set_skill("huntian-qigong", 270);
        set_skill("unarmed", 230);
        set_skill("changquan", 230);
        set_skill("dodge", 240);
        set_skill("feiyan-zoubi", 240);
        set_skill("parry", 250);
        set_skill("staff", 270);
        set_skill("strike", 270);
        set_skill("dragon-strike", 270);
        set_skill("jiaohua-bangfa", 250);
        set_skill("dagou-bang", 270);
        set_skill("throwing", 220);
        set_skill("mantianhuayu-zhen", 220);
        set_skill("begging", 200);
        set_skill("checking", 200);
        set_skill("training", 180);
        map_skill("throwing", "mantianhuayu-zhen");
        map_skill("force", "huntian-qigong");
        map_skill("unarmed", "changquan");
        map_skill("dodge", "feiyan-zoubi");
        map_skill("parry", "changquan");
        map_skill("staff", "dagou-bang");
        map_skill("strike", "dragon-strike");
        prepare_skill("strike", "dragon-strike");
        set("no_teach", ([
                "dragon-strike" : (: try_to_learn_ds :),
                "dagou-bang"    : (: try_to_learn_db :),
        ]));
        create_family("丐帮", 17, "帮主");
        setup();
        carry_object("/d/gaibang/obj/budai")->set_amount(9);
        carry_object("/d/gaibang/obj/budai")->wear();
        carry_object(__DIR__"yuzhu_zhang")->wield();
}

int try_to_learn_db()
{
        object me;
        me = this_player();
        if (me->query("can_learn/dagou-bang"))
                return 0;
        if (me->query("rank") < 9)
        {
                command("say 也不看看你是什么辈分，居然想学打狗帮法？");
                return -1;
        }
        if (me->query("shen") < -1000)
        {
                command("say 你中邪魔外道如此之深，还妄想学习神功？");
                return -1;
        }
        command("sigh");
        command("say 打狗帮法本来只传历代帮主，但是现在江湖多争乱，你"
                "也是本帮高手，学之无妨。");
        me->set("can_learn/dagou-bang", 1);
        return 0;
}

int try_to_learn_ds()
{
        object me;
        object sob;
        int i;
        int flag;
        string *sub_skills;
        me = this_player();
        if (me->query("rank") < 9)
        {
                command("say 你要学降龙十八掌？哈哈，等你升到本帮长老再说吧！");
                return -1;
        }
        if (me->query("shen") < -1000)
        {
                command("say 虽然我们丐帮不算什么大侠，不过你中邪魔外"
                        "道太深，还妄想学习神功？");
                return -1;
        }
        sob = find_object(SKILL_D("dragon-strike"));
        if (! sob) sob = load_object(SKILL_D("dragon-strike"));
        if (! sob->valid_learn(me))
                return 0;
        if (me->query_skill("dragon-strike", 1))
        {
                command("say 你不是已经会了么？自己好好练吧。");
                return -1;
        }
        sub_skills = keys(sob->query_sub_skills());
        flag = 0;
        for (i = 0; i < sizeof(sub_skills); i++)
        {
                if (me->query_skill(sub_skills[i], 1) >= 10)
                        continue;
                me->set_skill(sub_skills[i], 10);
                if (! flag)
                {
                        flag = 1;
                        command("say 好！我就将十八路掌法传授与你，"
                                "你要好好练习，他日必能融会贯通！");
                }
                write(HIC "你对" + to_chinese(sub_skills[i]) + "有了一"
                      "些领悟。\n" NOR);
        }
        if (! flag)
        {
                command("say 不是说了待到你融会贯通再来向我讨教吗？");
                return -1;
        }
        command("say 很好，现在你好好用功，把这十八路掌法融会贯通，合"
                "而为一再说吧。");
        notify_fail("好好努力，苦下功夫吧。\n");
        return -1;
}

void attempt_apprentice(object ob)
{
        if( ob->query("detach/丐帮") )
        {
                command("say 早知今日，何必当初！");
                return 0;
        }
        
        if( ob->query("rank") < 6 )
        {
                command("say 我看你在本帮待的时间不长。等你升到六袋以上再来找我吧。");
                return 0;
        }
        
        if( ob->query("betrayer") )
        {
                command("say 小子！再要罗嗦我可就要替你师傅教训教训你了！");
                return 0;
        }

        if( ob->query("family/family_name") &&
            ob->query("family/family_name") != "丐帮" )
        {
                command("say 嘿！你既然已经有了名师指点，还找我老叫花干什么？");
                return 0;
        }

        if ((int)ob->query_str() < 34 || (int)ob->query_con() < 26)
        {
                command("say 当叫化子需要能吃苦耐劳，依我看" +
                        RANK_D->query_respect(ob) +
                        "的资质似乎不适合当叫化子？");
                return;
        }

        if ((int)ob->query_skill("force") < 200)
        {
                command("sigh");
                command("say 你的内功火候太差了，先好好练练再来找我。");
                return;
        }

        if ((int)ob->query("max_neili") < 1000)
        {
                command("shake");
                command("say 就你那点内力哪里学得了什么上乘武功？");
                return;
        }

        ob->set_temp("title", ob->query("title"));
        command("recruit " + ob->query("id"));
        ob->set("title", ob->query_temp("title"));
        ob->delete_temp("title");
        
}

mixed ask_me()
{
        object me,obj;

        me = this_player();

        if (me->query("family/family_name") != query("family/family_name"))
                return "你一边去。";

        if (me->query_skill("dagou-bang", 1) < 250)
                return "你的打狗棒法学得怎么样啊？我看还差得远呢！";

        if(query("book_count") <1)
                return "你来晚了，打狗棒秘籍我已经借出去了。";
        obj=new(__DIR__"obj/book.c");
        obj->set("master",me->query("id"));
        obj->move(me);
        tell_object(me,"洪七公说道：“好吧，这本秘籍你拿去好好研究吧！”\n");        
       add("book_count",-1);
        return 1;
}
