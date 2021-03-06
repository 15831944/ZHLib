// shenni 南海神尼

#include <ansi.h>
#define QUEST_SN_D(x)          ("/quest/questsn/quest/questsn" + x)
#define QUEST_WUGOOD_D         ("/quest/questsn/quest/sngood")
#define SNMSG_D                ("/quest/questsn/quest/shenni-msg")

inherit NPC;
inherit F_MASTER;
inherit F_NOCLONE;

mixed ask_opinion();
int give_quest();
int give_up();
void destory(object);
string time_period(int);
string ask_me();

string* sn_msg = ({
"南海神尼微笑着说：“",
"南海神尼闭着眼睛冥思片刻道：“",
"南海神尼低头想了想，说道：“",
"南海神尼拍了拍手，说道：“",
"南海神尼微微笑了笑道：“",
});

string* qin_msg1 = ({
"动物是人们的朋友，就算name严重影响了生态环境，关起来也就可以了，",
"我听说name过多的繁殖，影响了当地的生态，不过还是不应该随便杀动物，",
"难道name也会给人类带来麻烦？真是稀奇，我到是想看看它，",
"我这里的花园养着很多的动物，就是没有name，",
"在空闲的时候，看看动物的生活能够放松情绪，name其实挺可爱的，",
"独孤求败是一个很喜欢动物的人，尤其是name，用来送给他做礼物最好不过，",
"江湖上打打杀杀的，少不了让name也遭受无辜连累，我有心保护它，",
});

string* qin_msg2 = ({
"你去把它带到这里来吧。”",
"去找到它，把它带来。”",
"你能把它带我这里来么？”",
"你就辛苦一躺去帮我把它找来吧。”",
"把它弄来给我。”",
});

#define ULTRA_OPINION   "宗师"
#define OPINION_TYPE    HIY "内家功夫" NOR 
#define MY_OPINION      "force"

string  *my_opinions = ({ "force" });

// 该头文件必须在这里嵌入
#include <ultra.h>

void create()
{
        set_name("南海神尼", ({ "nanhai shenni", "shenni", "nanhai" }) );
        set("title", HIG "大宗师" NOR);
        set("gender", "女性");
        set("age", 91);
        set("long", "这是一位青衫老尼，看不出有什么不同。\n");
        set("attitude", "peaceful");
        set("class", "bonze");
	set("nickname",HIY"武林同盟"+HIW"副盟主"+NOR);
        set("str", 30);
        set("int", 37);
        set("con", 39);
        set("dex", 33);

        set("max_qi", 9999);
        set("max_jing", 9999);
        set("neili", 9999);
        set("max_neili", 9999);
        set("jiali", 70);

        set("combat_exp", 50000000);

        set("inquiry", ([
                "弹指神通" : "那是我碧海神功关于指法方面的变化，当年我到东海，曾经传授给一人。",
                "评价"     : (: ask_opinion :),
                "opinion"  : (: ask_opinion :),
                "武学修养" : "好好提高自己的武学修养(martial-cognize)，到时候什么武功都如小儿科！",
                "任务" : "本性凶狠但是立身正派的人，可以在我这里领任务(quest)。\n",
        ]));

        set_skill("strike", 500);
        set_skill("finger", 500);
        set_skill("parry", 500);
        set_skill("dodge", 500);
        set_skill("force", 500);
        set_skill("staff", 500);
        set_skill("bluesea-force", 500);
        set_skill("martial-cognize", 500);
        set_skill("literate", 220);

        map_skill("parry", "bluesea-force");
        map_skill("force", "bluesea-force");
        map_skill("dodge", "bluesea-force");
        map_skill("finger", "bluesea-force");
        map_skill("strike", "bluesea-force");
        map_skill("staff", "bluesea-force");

        prepare_skill("finger", "bluesea-force");
        prepare_skill("strike", "bluesea-force");

        set("opinion/ultra",  1);
        set("opinion/master", 1);

        set("rank_info/self", "本座");

        setup();
        carry_object("/clone/cloth/cloth")->wear();
        carry_object("/clone/weapon/zhubang")->wield();

        set("startroom", "/d/xiakedao/zhuwu2");
        check_clone();
}

void init()
{
        object me;

        if (! interactive(me = this_player()))
                return;

        me->delete_temp("want_opinion");
        add_action("give_quest", "quest");
        add_action("give_up","giveup");
}

mixed ask_opinion()
{
        object me;
        object ob;

        me = this_player();

        if (me->query("combat_exp") < 200000)
                return "哼！你这点武功也出来丢人现眼？";

        if (me->query("opinion/" MY_OPINION) == ULTRA_OPINION)
                return "不必了，你内功方面的修为已经称得上是宗师了！要是和贫尼过上几招也不错。";

        if (is_fighting(me))
                return "哈哈，废什么话，打赢了我，你自己给自己评价吧！";

        if (me->is_fighting())
                return "你等会儿吧！待我赶走他们。";

        if (objectp(ob = query_temp("opinion")))
        {
                if (ob == me)
                {
                        command("say 你着什么急？不要烦我。");
                        return 1;
                }

                message_vision("$N颇为恼怒的对$n道：“没看我正忙着吗？”\n",
                               this_object(), me);
                return 1;
        }

        switch(me->query_temp("want_opinion/shenni"))
        {
        case 0:
                command("say 好吧，咱们过一招，比拚一下内力。");
                break;
        case 1:
                command("say 你准备好没有？好了就来吧。");
                break;
        case 2:
                message_vision(CYN "$N" CYN "皱眉对$n" CYN
                               "道：“我看你这人是够罗嗦的。”\n" NOR,
                               this_object(), me);
                break;
        case 3:
                command("say 快给我闭上你的鸟嘴！");
                return 1;
        }

        me->add_temp("want_opinion/shenni", 1);
        return 1;
}

int calc_level(object me, string skill)
{
        int lvl;
        string sp;

        lvl = me->query_skill(skill, 1) / 2;
        sp = me->query_skill_mapped(skill);
        if (! sp) return lvl;

	lvl += me->query_skill(sp, 1);
        if (me->query("max_neili") > 4000) lvl += 20;
        return lvl;
}

void do_congration(object me)
{
        command("chat 不错，不错，真是不错。");
}

int accept_hit(object me)
{
        command("heng");
        command("say 好你个" + RANK_D->query_rude(me) + "，你找死找到这来了！");
        kill_ob(me);
        return 1;
}

int accept_fight(object me)
{
        object weapon;

        if (me->query("opinion/" MY_OPINION) == ULTRA_OPINION)
        {
                message_vision("$N对$n道：“很好，你也算是宗师高手了，"
                               "来吧！咱们比划一下！”\n",
                               this_object(), me);
                return 1;
        }

        if (! me->query_temp("want_opinion/shenni"))
        {
                command("say 你干什么要和我动手？");
                return 0;
        }

        command("look " + me->query("id"));

        COMBAT_D->do_attack(this_object(), me, 0);

        if (me->query("qi") <= 0)
        {
                message_vision("\n$N摇摇头对$n道：“你现在的武功"
                               "还差得远，连我一招都接不住！”\n",
                               this_object(), me);
                return notify_fail("看来要好好的修炼功夫了。\n");
        }

        message_combatd("$N右掌伸出，正和$n手掌相对，两人同时运起内力，"
                       "不一会儿只见二人头上生起腾腾雾气。\n忽然$N手掌"
                       "一撤、收回功力，没有一点阻滞，不禁让$n大为愕然。\n",
                       this_object(), me);
        if (me->query("neili") < 3000)
        {
                message_vision("$N摇摇头对$n道：“适才你内力不足，我难"
                               "以衡量，待你将内力修炼好了再来吧！”\n",
                               this_object(), me);
                return notify_fail("看来还是回去锻炼一下内力吧！\n");
        }
        me->set("neili", 0);
        

        call_out("check_opinion", 2, me);
        set_temp("opinion", me);
        me->delete_temp("want_opinion");
        message_vision("\n$N一摆手道：“好了，待我想想。”\n",
                       this_object(), me);
        return notify_fail("看来不能心急，还得等一会儿。\n");
}

int accept_kill(object me)
{
        if (me->query("combat_exp") < 500000)
        {
                message_vision("$N大怒道：“无名小辈捣什么"
                               "乱？给我滚！”说罢一掌把$n劈倒在地。\n",
                               this_object(), me);
                me->unconcious();
                return -1;
        }
        command("sigh");
        command("say 很好！近年还真没有遇到什么敢和我较量的高手！");
        return 1;
}

int recognize_apprentice(object me, string skill)
{
        if (me->query("character") != "心狠手辣")
        {
                command("say 你这人生性不够毒辣，下不了狠心，"
                        "我没有兴趣教你！");
                return -1;
        }

        if (! ultrap(me))
        {
                command("say 想跟我学武功？你还不够资格，"
                        "等你成了大宗师再说吧！");
                return -1;
        }

	if (skill == "bluesea-force")
	{
                command("say 想学我的南海玄功？这个岂是凡人能用的，"
                        "你从我这里学点武学修养才是正经！");
                return -1;
	}

/*
	if (skill == "martial-cognize")
		return 1;

        if (! ultrap(me))
        {
                command("say 想学我的碧海神功？你还不够资格，"
                        "等你成了大宗师再说吧！");
                return -1;
        }

        if (me->query_skill(skill, 1) >= 180)
        {
                command("say 够了！我就教你到这里吧，武功还是"
                        "要靠自己多研究才是！");
                return -1;
        }

        if (skill != "bluesea-force")
                return 1;

        if (me->query_temp("can_learn/shenni/bluesea-force"))
                return 1;

        me->set_temp("can_learn/dugu/bluesea-force", 1);
        command("nod");
        command("say 不错，我教你我的绝学碧海神功，能不能学，"
                "就看你的造化了！");
*/
        return 1;
}

void unconcious()
{
//        message("vision", "\n"HIR + name() + "脸色一变，吐了一口鲜"
//                "血，身形一闪，消逝不见。\n\n" NOR, environment());
//        command("chat 罢！罢！罢！贫尼去也！");
//        destruct(this_object());
return;
}

void die()
{
//        message("vision", "\n"HIR + name() + "大叫一声，狂吐了一口鲜"
//                "血，身形一闪，就此不见。\n\n" NOR, environment());
//        command("chat 贫尼去也！");
//        destruct(this_object());
return;
}

int give_quest()
{
    mapping quest,qgood,skills;
    object me,target,thing,npc,the_ob;
    int i, exp, giveup,tag,want,lev,lev1;
    string msg,*sname,place,the_race;

    me = this_player();
    exp = (int)me->query("combat_exp");

    if( (me->query("character") != "阴险奸诈") && (me->query("character") != "心狠手辣"))  
    {
        write("南海神尼摇头道：你天性忠实厚道，恐怕接我任务会太过于心慈手软，还是另找别人要任务吧。\n");
        return 1;
    }
    if( !(me->query("shen") > 0))
    {
        write("南海神尼看着你只是摇头：“行走江湖，立身要正！虽然我讲究以杀止杀，但是你邪气太重，还是算了吧！”\n");
        return 1;
    }
    if(exp < 500000)
    {
        write("南海神尼微笑着拍了拍你的脑袋：以你现在的经验，接我任务实在太过危险，好好去历练历练，回头再来找我。\n");
        return 1;
    }

 
    if ( quest = me->query("quest_sn") )
    {
        write("南海神尼呵呵笑着说：心急可是喝不了热粥啊，不要着急，慢慢来。\n");
        return 1;
    }

    if (mapp(me->query("quest_kh")))
    {
        me->delete_temp("questkh_times");
        me->delete("quest_kh");
    }

    giveup = me->query_temp("sn_giveup");
    if((time()-me->query_temp("questsn_giveup_time")) < giveup*2 &&!wizardp(me))
    {
        write("南海神尼笑着对你说道：“怎么完不成任务这么不顺利？不要着急，先好好想想原因在哪里。\n");
        return 1;
    }

    quest = ([]);
    // 以下给任务
    if(exp <= 600000)        tag = 0;
    else if(exp <= 900000)   tag = 1;
    else if(exp <= 1200000)  tag = 2;
    else if(exp <= 1800000)  tag = 3;
    else if(exp <= 2500000)  tag = 4-random(3);
    else if(exp <= 3200000)  tag = 5-random(3);
    else if(exp <= 4000000)  tag = 6-random(3);
    else
    {
        if(random(15)==0||(exp>10000000&&random(8)==0))
            tag=8;
        else tag=7-random(3);
    }

    i = me->query_temp("questsn_times");
    if((i > 20 && random(20)==18))
    {
        qgood = QUEST_WUGOOD_D->query_good();
        msg = qgood["msg"+random(3)];
        want = 15+random(11);
	msg = YEL"南海神尼呵呵大笑，高兴的说道：“你的办事能力真不赖！\n"+msg
            +"\n你想法弄一批"+qgood["name"]+"来，大约要 "+want+" "+qgood["unit"]+"，有多少可以先交多少。去罢！”\n"NOR;
        write(msg);
        quest = ([ 
                   "id"   : qgood["id"],
                   "name" : qgood["name"], 
                   "msg"  :  msg, 
                   "want"  : want,
                   "type" :  "收", 
                   "bonus" : qgood["bonus"], 
                   "level" : tag,
                ]),
        me->set("quest_sn",quest);
        return 1;
    }

    if(tag==8)
    {
            npc = new(CLASS_D("generate") + "/player_npc.c");
            NPC_D->place_npc(npc, me->query("combat_exp") < 500000  ? ({ "大理一带", "终南山", "关外", "西域" }) :
                                  me->query("combat_exp") < 800000 ? ({ "大理一带", "终南山", "西域" }) : ({"大理一带", "西域"}));
            npc->set_from_me(me,1);
            npc->add_temp("apply/attack", npc->query_skill("force") * (tag - 1) / 15);
            npc->add_temp("apply/dodge", npc->query_skill("force") * (tag - 1) / 15);
            npc->add_temp("apply/parry", npc->query_skill("force") * (tag - 1) / 15);
            npc->add_temp("apply/damage", 5 + tag * 7);
            npc->add_temp("apply/unarmed_damage", 5 + tag * 7);
            npc->add_temp("apply/armor", 10 + tag * 15);
            npc->set_temp("quester", me->query("id"));
            npc->set("auto_perform",1);
            NPC_D->random_move(npc);
            NPC_D->random_move(npc);
            NPC_D->random_move(npc);
            place = npc->query("place");

            npc->set("shen", -npc->query("combat_exp") / 2000);
            msg="南海神尼正容对你说：“"+npc->name(1)+
                "这个恶棍多次危害武林，听说他最近在" + 
                place + "，你去除掉他吧！”\n";

            quest = ([
                "name" : npc->name(1),
                "id"   : npc->query("id"),
                "bonus": (100+random(41)),
                "type" :"杀",
                "level":8,
                "chinese_w":place,
                "where":npc->query("startroom"),
                "msg":msg,
		"object":base_name(npc),
            ]);
            tell_object(me,quest["msg"]+"\n");
            me->set("quest_sn",quest);

            return 1;
    }
    else
    {
    quest = QUEST_SN_D(tag)->query_quest();
/*
    if(undefinedp(quest["msg"]) || quest["msg"] == "")
*/
    switch(quest["type"])
    {
        case "擒":
                msg = sn_msg[random(sizeof(sn_msg))] + replace_string(qin_msg1[random(sizeof(qin_msg1))],"name",quest["name"]) + qin_msg2[random(sizeof(qin_msg2))];
                break;
        case "杀":
                if (quest["object"]->query("race") != "人类" || wizardp(me))
                {
                        quest["type"] = "擒";
                        msg = sn_msg[random(sizeof(sn_msg))] + replace_string(qin_msg1[random(sizeof(qin_msg1))],"name",quest["name"]) + qin_msg2[random(sizeof(qin_msg2))];
                        break;
                } else msg=SNMSG_D->query_snmsg("杀",quest["name"]);
                break;
        case "寻":
                msg=SNMSG_D->query_snmsg("寻",quest["name"]);
                break;
        case "送":
                npc = new(CLASS_D("generate") + "/sn_receiver.c");
                NPC_D->place_npc(npc, me->query("combat_exp") < 500000  ? ({ "大理一带", "终南山", "关外", "西域" }) :
                                      me->query("combat_exp") < 800000 ? ({ "大理一带", "终南山", "西域" }) : ({"大理一带", "西域"}));
                NPC_D->set_from_me(npc, me, 100);
                npc->set_temp("quester", me->query("id"));
                NPC_D->random_move(npc);
                NPC_D->random_move(npc);
                NPC_D->random_move(npc);
                place = npc->query("place");
                thing = new(quest["object"]);
                thing->set("send_to",npc->query("id"));
                thing->set("send_from",query("id"));
                thing->set("send_from_name",query("name"));
                msg = sn_msg[random(5)]+"你看能否帮我将"+thing->name(1)+"送至"+npc->name(1)+"处，"
                                        "他现在正在"+place+"，赶紧去，不然误了时间他可能就不在了。";
                if (!thing->move(me))
                {
                    thing->move(environment());
                    message_vision("南海神尼将$N轻轻放在地上。\n",thing);
                } else message_vision("南海神尼将$N交给$n。\n",thing,me);
                quest["thing"] = thing;
                break;
    }
    }
    quest["msg"] = msg;
    quest["level"] = tag;
    me->set("quest_sn", quest);
    if(stringp(quest["msg"])&&quest["msg"]!="")
                write(YEL""+quest["msg"]+"\n"NOR);
    else
    {
                write(YEL""+msg+"\n"NOR);
                me->set("quest_sn/msg", msg);
    }
    return 1;
}

int accept_object(object me, object ob)
{
    int rank,exp,pot,score,times, i,tag,all_quest_sn;
    mapping quest;
    object gold,who,obj;
    string msg;
    int mar,weiwang,shen,quest_count;
    mixed special = 0;
    
    who = this_object();
    
    if( (me->query("character") != "阴险奸诈") && (me->query("character") != "心狠手辣") && !(me->query("shen") > 0))  
    {
        write("南海神尼惊讶的道：“你是谁？给我这个东西干什么？”\n");
        return 0;
    }
    else if(!(quest = me->query("quest_sn")))
    {
        write("南海神尼呵呵笑道：“我知道你想孝敬我，但是可以靠实际行动嘛，东西你还是自己留着吧。”\n");
        return 0;
    }

    if(ob->query("money_id"))
    {
           if (ob->value() < 5000000)
           {
                   tell_object(me,"南海神尼呵呵一笑：我不缺钱花啊，这点钱，你自己留着买东西吃吧。\n");
                   return notify_fail("南海神尼轻轻说道：如果给我500两黄金，我就取消了你的任务。\n");
           }
           me->delete("quest_sn");
           tell_object(me,"南海神尼随手发下" + ob->name(1) + "，轻轻对你说：那你这个任务不做就算了吧。\n");
           destruct(ob);
           return 1;
    }

    else if(quest["type"]!="寻"&&quest["type"]!="收"&&quest["type"]!="送"&&quest["type"]!="擒")
    {
        write("南海神尼微笑道：“我没有叫你去找东西呀，东西你收回。”\n");
        return 0;
    }
    else if( ob->name(1) != quest["name"])
    {
        write("南海神尼摇头说道：“这个可不是我想要的呀。”\n");
        return 0;
    }

    if(userp(ob) || ob->query("user"))
    {
        write("南海神尼大怒道：“好你个小子，竟然想蒙骗本副盟主！来人！把他给我抓起来！”\n");
        me->move("/d/register/prison");
        log_file( "static/QUEST_DIJIAO", sprintf("%s(%s)(神尼任务)制造%s(%s)(%s)作弊\n", me->query("name"),
             me->query("id"),ob->name(),ob->query("id"),ctime(time()) ) );
        return 1;
    }

    message_vision("$N将$n交给南海神尼。\n",me,ob);
    times = me->query_temp("questsn_times"); //连续次数
    tag = me->query("quest_sn/level")+1;       //任务等级
    if((i=me->query_temp("questsn_times")) < 10)   i =10-i;
    else i = 1;

    exp = tag*80 + quest["bonus"]*3;
    exp += random(exp/2);
    exp = exp/i;

    if (tag > 4 && i > 5)
	exp /= 2;

    pot = exp/(2+random(2));

    score = random(exp/20);
    weiwang = random(exp/15);

    if (times + 1 > 200)
	 mar = exp/5 + random(times);
    else mar = random(20);

    if(quest["type"]=="送")
    {
        if (!ob->is_receipt() || ob->query("reply_to") != who->query("id"))
        {
            write("南海神尼接过来一看，皱眉道：“给我这玩艺干什么？”\n");
            return 0;
        }
    } 
    if(quest["type"]=="收")
    {
        if((int)quest["want"]>(quest["ok"]+1))
        {
            me->add("quest_sn/ok",1);
            write("南海神尼接过来高兴的说：“我要的就是这个，第 "+quest["ok"]+" 了，太好了，还有 "+(quest["want"]-quest["ok"])+" 个，继续努力！”\n");
                    score /= 3;
                    QUEST_D->bonus(me, ([ "exp" : exp, "pot" : pot, "mar" : mar, 
                                           "weiwang" : weiwang, "score" : score]), 1);
            destruct(ob);
            return 1;
        }
        exp = exp*2;
        pot = pot*2;
        weiwang = weiwang;
        mar = mar*2;
        score = score;
    }
    write("南海神尼接过来开心的笑着说：“不错呀！你这次任务完成得很好！”\n");
    destruct(ob);
    if(!random(10))
    {
        i=(exp/400+1);
        if(i>5) i=5;
        gold=new("/clone/money/gold");
        gold->set_amount(i);
        tell_object(me,"然后取出一锭黄金给你：“行走江湖，身上总要带点钱，我这里有些金子，给你去用吧！”\n"
                       HIW"\n你被奖励了 "+i+" 两黄金。\n");
        if(!gold->move(me))
        {
            message_vision("但是$N身上东西太重，黄金一下子从手中滑到了地上。\n",me);
            gold->move(environment());
        }
        QUEST_D->bonus(me, ([ "exp" : exp, "pot" : pot, "mar" : mar,
                            "weiwang" : weiwang, "score" : score, "percent" : 50 ]), 1);
    }
    else QUEST_D->bonus(me, ([ "exp" : exp, "pot" : pot, "mar" : mar,
                              "weiwang" : weiwang, "score" : score ]), 1);
    
    if ( times < 1 )
        me->set_temp("questsn_times",1);
    else
        me->add_temp("questsn_times",1);
        me->set_temp("sn_giveup",0);        

   me->add("pk_score",-5);
   if (me->query("pk_score") < 0) me->set("pk_score",0);

   quest_count = me->query_temp("questsn_times");
   if (quest_count == 50)
   {
       msg = "$N呵呵笑了两声道：“你还可以，连着五十"
       "次任务都完成的漂漂亮亮，继续努力！”\n";
	special = 1;
	   } else
       if (quest_count == 100)
   { 
       msg = "$N笑的合不拢嘴，看了你一眼道：“有志气！一百"
       "次任务干得干净利索！”\n";
       special = "/d/shaolin/obj/puti-zi";
   } else
    if (quest_count == 300)
    {
        msg = "$N叹道：“真是长江后浪推前浪，想不到你接连三百"
               "次任务都无一疏漏，不易，不易！”\n";
	 special = "/clone/misc/tianxiang";
    } else
    if (quest_count == 350)
    {
        msg = "$N吓了一跳：“看来你真的很适合学武，竟接连三百"
               "五十次任务都无一疏漏，不易，不易！”\n";
	 special = "/clone/misc/tianxiang";
    } else
    if (quest_count == 400)
    {
        msg = "$N叹道：“真是一个武学天才啊，想不到你接连四百"
               "次任务都无一疏漏，不易，不易！”\n";
	 special = "/clone/misc/tianxiang";
    } else
    if (quest_count == 450)
        {
        msg = "$N大声叫起来：“天才！真是天才，真有人连续四百"
               "五十次任务都无一疏漏，不易，不易！”\n";
        special = "/clone/gift/jiuzhuan";
    } else
       if (quest_count == 500)
   {
       msg = "$N深深叹了口气，道：“没想到你连着五百次"
       "任务无一失手，看来以后就是你们这些人挑大梁啦！”\n";
       special = "/clone/gift/jiuzhuan";
   } else
       if ((quest_count % 10) == 0)
   {
       msg = "$N微微点头：“干的不错，居然连着" +
       chinese_number(quest_count) +
       "次都没有失手，接着来，别放松！”\n";
   }
   if (special) {
       message_vision(msg, who, me);
       QUEST_D->special_bonus(who, me, special);
   }

    me->delete("quest_sn");

   //记录完成任务的次数（不要求连续），如果满1000次则奖励翡翠残片
   all_quest_sn = (int)me->query("all_quest_sn");
   if (!all_quest_sn) all_quest_sn = 0;
   all_quest_sn += 1;
   if (all_quest_sn == 1000)
   {
       obj = new("/clone/gift/cjade");
       tell_object(me,this_object()->name() + "又对你点了点头：你已经从我这里接了一千个任务，我这里正好\n" +
                   "有个" + obj->query("name") + "，就奖给你了！\n");
       if (!obj->move(me))
               obj->move(environment());
       me->set("all_quest_sn",0);
   } else me->set("all_quest_sn",all_quest_sn);

   return 1;
}

int give_up()
{
    object me,ob,obj;
    int giveup,rank;
    mapping quest;
    
    me = this_player();
    if( me->query("quest_sn")) 
    {
    if( (me->query("character") != "阴险奸诈") && (me->query("character") != "心狠手辣") && !(me->query("shen") > 0))  
        return 1;
    }
    if((quest =  me->query("quest_sn")))
    {
        message_vision("$N委屈的到南海神尼面前哭诉：“我这次任务没有完成，辜负了您老人家的期望......”\n",me);
        if (quest["type"] == "送")
        {
                if (objectp(ob = quest["thing"]))
                {
                        ob->move("/d/register/prison");
                        destruct(ob);
                }
        }
        message_vision("南海神尼对$N微笑着说:“没关系，下次好好努力就行啦。”\n", me);
        
        me->set_temp("questsn_times",0);

        giveup = me->query_temp("sn_giveup");
        if ( giveup < 1 )
            me->set_temp("sn_giveup",1);
        else if ( giveup < 5 )
            me->set_temp("sn_giveup",giveup+1);
        else me->set_temp("sn_giveup",5);

        me->set_temp("questsn_giveup_time",time());
   
        me->delete("quest_sn");
    }
    else
        write("南海神尼微笑着告诉你：“你目前没有任何任务。”\n");
    return 1;
}

string time_period(int timep)
{
    int t, d, h, m, s;
    string time;
    t = timep;
    s = t % 60;             t /= 60;
    m = t % 60;             t /= 60;
    h = t % 24;             t /= 24;
    d = t;
 
    if(d) time = chinese_number(d) + "天";
    else time = "";
 
    if(h) time += chinese_number(h) + "小时";
    if(m) time += chinese_number(m) + "分";
        time += chinese_number(s) + "秒";
    return time;
}

void destory(object ob)
{
    if(!ob) return;
    if(ob->is_character())
        message_vision("$N突然一溜烟地跑得没影了。\n",ob);
    ob->move("/d/wizard/prison");
    destruct(ob);
    return ;
}
