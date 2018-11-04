// huang ����

#include <ansi.h>
#define QUEST_HS_D(x)          ("/quest/quesths/quest/quesths" + x)
#define QUEST_WUGOOD_D         ("/quest/quesths/quest/hsgood")
#define HSMSG_D                ("/quest/quesths/quest/huangshang-msg")

inherit NPC;
inherit F_MASTER;
inherit F_NOCLONE;

mixed ask_opinion();

#define ULTRA_OPINION   "��ʦ"
#define OPINION_TYPE    HIY "ȭ�Ź���" NOR 
#define MY_OPINION      "unarmed"

int give_quest();
int give_up();
void destory(object);
string time_period(int);
string ask_me();

string  *my_opinions = ({ "unarmed", "finger",
                          "strike", "cuff", "hand", "claw" });

string* hs_msg = ({
"����ͷҲ��̧��˵����",
"���ѷ���һ������������",
"���ѵ�ͷ�����룬˵������",
"��������һ�ݹ��ģ�˵������",
"����΢΢Ц��Ц������",
});

// ��ͷ�ļ�����������Ƕ��
#include <ultra.h>

void create()
{
        set_name("����", ({ "huang shang", "huang" }) );
        set("title", HIY "����ʦ" NOR);
        set("gender", "����");
        set("age", 92);
        set("long", "�����������ţ��������书�ߵ͡�\n");
        set("attitude", "peaceful");
	set("nickname",HIY"����ͬ��"+HIW"����"+NOR);
        set("str", 32);
        set("int", 39);
        set("con", 37);
        set("dex", 32);

        set("max_qi", 9999);
        set("max_jing", 9999);
        set("neili", 9999);
        set("max_neili", 9999);
        set("jiali", 50);

        set("combat_exp", 50000000);

        set("inquiry", ([
                "�����澭" : "����������д��һ�������ڹ�צ��������ĵá�",
                "�����澭" : "��...��...... �Ҳ�̫�����",
                "����"     : (: ask_opinion :),
                "opinion"  : (: ask_opinion :),
                "��ѧ����" : "��ѧ����(martial-cognize)�����ң���̸ʲô�书�أ�",
                "����" : "���Ժã����Ǹ���Ļ���������������������(quest)��\n",
        ]));

        set_skill("unarmed", 500);
        set_skill("finger", 500);
        set_skill("claw", 500);
        set_skill("strike", 500);
        set_skill("hand", 500);
        set_skill("cuff", 500);
        set_skill("parry", 500);
        set_skill("dodge", 500);
        set_skill("force", 500);
        set_skill("jiuyin-shengong", 500);
        set_skill("martial-cognize", 500);
        set_skill("literate", 200);

        map_skill("parry", "jiuyin-shengong");
        map_skill("force", "jiuyin-shengong");
        map_skill("dodge", "jiuyin-shengong");
        map_skill("unarmed", "jiuyin-shengong");
        map_skill("finger", "jiuyin-shengong");
        map_skill("strike", "jiuyin-shengong");
        map_skill("hand", "jiuyin-shengong");
        map_skill("cuff", "jiuyin-shengong");
        map_skill("claw", "jiuyin-shengong");

        prepare_skill("claw", "jiuyin-shengong");
        prepare_skill("cuff", "jiuyin-shengong");

        set("opinion/ultra",  1);
        set("opinion/master", 1);

        set("rank_info/self", "ĳ��");

        setup();
        carry_object("/clone/cloth/cloth")->wear();

        set("startroom", "/d/dali/lushui");
        check_clone();
}

void init()
{
        object me;

        if(!interactive(me = this_player())) return;
        me->delete_temp("want_opinion");

        if( !is_fighting() &&random(5)==0)
        {
        	remove_call_out("greeting");
        	call_out("greeting", 1, me);
        }        
        add_action("give_quest", "quest");
        add_action("give_up","giveup");
}

void greeting(object ob)
{
    if( !ob || environment(ob) != environment() ) return;
    if(ob->query("quest_hs") && ob->query("shen") < 0)
         write("����˵����" + ob->query("name")+ ",���������ɵ���ô���ˣ�\n");
}

mixed ask_opinion()
{
        object me;
        object ob;

        me = this_player();

        if (me->query("combat_exp") < 200000)
                return "�Ǻǣ�������书��̸ʲô���ۣ�";

        if (me->query("opinion/" MY_OPINION) == ULTRA_OPINION)
                return "��������ȭ�ŷ������Ϊ�Ѿ��Ƶ�������ʦ�ˣ�����Ҫ��Ҫ�����У�";

        if (is_fighting(me))
                return "��������ʲô������Ӯ���ң����Լ����Լ����۰ɣ�";

        if (me->is_fighting())
                return "��Ȼ���ɣ����Ҹ������ǡ�";

        if (objectp(ob = query_temp("opinion")))
        {
                if (ob == me)
                {
                        command("say ����ʲô������Ҫ���ҡ�");
                        return 1;
                }

                message_vision("$N���ڳ�˼��û�лش�$n��ֻ�ǰ��˰��֡�\n",
                               this_object(), me);
                return 1;
        }

        switch(me->query_temp("want_opinion/huang"))
        {
        case 0:
                command("look " + me->query("id"));
                command("say �ðɣ�����ֹ���һ�У��ҿ������ˮƽ��Ρ�");
                break;
        case 1:
                command("say ����˵������һ���ҿ�����");
                break;
        case 2:
                message_vision(CYN "$N" CYN "��ü��$n" CYN
                               "�������ҿ��������ǹ����µġ���\n" NOR,
                               this_object(), me);
                break;
        case 3:
                command("say ���ұ�������죡");
                return 1;
        }

        me->add_temp("want_opinion/huang", 1);
        return 1;
}

int calc_level(object me, string skill)
{
        int lvl;
        string sp;
        mapping action;

        lvl = me->query_skill(skill, 1) / 2;
        sp = me->query_skill_mapped(skill);
        if (! sp) return lvl;

	lvl += me->query_skill(sp, 1);
        action = SKILL_D(sp)->query_action(me, 0);
        lvl += (action["force"] + action["attack"] +
                action["parry"] + action["dodge"] - 150) / 15;
        return lvl;
}

void do_congration(object me)
{
        command("chat ��ϲ��λ" + RANK_D->query_respect(me) + "�������������ֹ������������Ŭ������");
}

int accept_hit(object me)
{
        if (me->query_temp("want_hit/huang") >= 2)
        {
                command("heng");
                command("say �²���������Ҫ�����Ǿ�ȥ���ɣ�");
                kill_ob(me);
                return 1;
        }

        command("shake");
        command("say ��λ" + RANK_D->query_respect(me) + "��"
                "����֮���м�óȻ���ơ�");
        me->add_temp("want_hit/huang", 1);
        return 0;
}

int accept_fight(object me)
{
        object weapon;

        if (me->query("opinion/" MY_OPINION) == ULTRA_OPINION)
        {
                message_vision("$N��ϲ����$n�������ܺã������һ�û��"
                               "����ʦ���ֹ����У����ɣ���\n",
                               this_object(), me);
                return 1;
        }

        if (! me->query_temp("want_opinion/huang"))
        {
                command("say ƽ���޹ʶ�ʲô�֣�");
                return 0;
        }

        if (objectp(weapon = me->query_temp("weapon")))
        {
                command("say �������е�" + weapon->name() + "���ҷ��£�");
                return 0;
        }

        if (me->query("qi") * 100 / me->query("max_qi") < 80||
            me->query("jing") * 100 / me->query("max_jing") < 80)
        {
                command("say ������״̬���ѣ�����Ϣ������˵�ɣ�");
                return 0;
        }

        command("nod");
        COMBAT_D->do_attack(me, this_object(), 0);
        COMBAT_D->do_attack(this_object(), me, 0);

        if (me->query("qi") <= 0)
        {
                message_vision("\n$Nҡҡͷ��$n�����������ڵ��书"
                               "�����Զ������һ�ж��Ӳ�ס����\n",
                               this_object(), me);
                return notify_fail("����Ҫ�úõ����������ˡ�\n");
        }

        call_out("check_opinion", 2, me);
        set_temp("opinion", me);
        me->delete_temp("want_opinion");
        message_vision("\n$N���ͷ���������ˣ����ȵȻ�����������롣��\n",
                       this_object(), me);
        return notify_fail("���������ļ������õ�һ�����\n");
}

int accept_kill(object me)
{
        if (me->query("combat_exp") < 500000)
        {
                message_vision("$N��ŭ����������С����ʲô"
                               "�ң����ҹ�����˵��һ�ư�$n�����ڵء�\n",
                               this_object(), me);
                me->unconcious();
                return -1;
        }
        command("sigh");
        command("say �ܺã����껹��û������ʲô�Һ��ҽ����ĸ��֣�");
        return 1;
}

int recognize_apprentice(object me, string skill)
{
        if (me->query("character") != "��������")
        {
                command("say ���ɷ����������ƶ�����һ��Ҫ��"
                        "�����䣬�����Բ��������ˡ�");
                return -1;
        }

        if (! ultrap(me))
        {
                command("say �����ѧ�书���㻹�����ʸ�"
                        "������˴���ʦ��˵�ɣ�");
                return -1;
        }

	if (skill == "jiuyin-shengong")
	{
                command("say ��ѧ�ҵľ����񹦣�������Ƿ������õģ�"
                        "���������ѧ����ѧ��������������");
                return -1;
	}

/*
	if (skill == "martial-cognize")
		return 1;

        if (! ultrap(me))
        {
                command("say ��ѧ�ҵľ����񹦣��㻹�����ʸ�"
                        "������˴���ʦ��˵�ɣ�");
                return -1;
        }

        if (me->query_skill(skill, 1) >= 180)
        {
                command("say ���ˣ��Ҿͽ��㵽����ɣ��书����"
                        "Ҫ���Լ����о����ǣ�");
                return -1;
        }

        if (skill != "jiuyin-shengong")
                return 1;

        if (me->query_temp("can_learn/huang/jiuyin-shengong"))
                return 1;

        me->set_temp("can_learn/huang/jiuyin-shengong", 1);
        command("nod");
        command("say �ܺã��Ҿʹ�������񹦰ɣ��ɲ�Ҫ��������"
                "�ĸ�����");

*/
        return 1;
}

void unconcious()
{
//        message("vision", "\n"HIR + name() + "��ɫһ�䣬����һ����"
//                "Ѫ������һ�������Ų�����\n\n" NOR, environment());
//        command("chat �գ��գ��գ��Ϸ�ȥҲ��");
//        destruct(this_object());
return;
}

void die()
{
//        message("vision", "\n"HIR + name() + "���һ����������һ����"
//                "Ѫ������һ�����ʹ˲�����\n\n" NOR, environment());
//        command("chat �Ϸ�ȥҲ��");
//        destruct(this_object());
return;
}
int give_quest()
{
    mapping quest,qgood,skills;
    object me,target,thing,npc;
    int i, exp, giveup,tag,want,lev,lev1;
    string msg,*sname,place;

    me = this_player();
    exp = (int)me->query("combat_exp");

    if( (me->query("character") != "��������") && (me->query("character") != "������"))  
    {
        write("�������㣺�������Ը���ˣ��������ʲô��\n");
        return 1;
    }
    if( !(me->query("shen") < 0))
    {
        write("���ѿ�����ֻ��ҡͷ�������߽��������ǹ��������������ҽ��������ɱֹɱ����ɱ�Բ������������˰ɣ���\n");
        return 1;
    }
    if(exp < 500000)
    {
        write("���Ѷ���˵�����������ڵľ��飬����Ҫ���ĥ������\n");
        return 1;
    }
 
    if ( quest = me->query("quest_hs") )
    {
        write("���Ѷ���˵���Ȱ������ϵ����������˵��\n");
        return 1;
    }
    if (mapp(me->query("quest_dg")))
    {
        me->delete_temp("questdg_times");
        me->delete("quest_dg");
    }
    giveup = me->query_temp("hs_giveup");
    if((time()-me->query_temp("quesths_giveup_time")) < giveup*2)
    {
        write("���Ѷ������һ�����������겻�������Ҷ���ı��ֺܲ����⣬�ȷ�ʡһ�����\n");
        return 1;
    }
// ���¸�����
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

    i = me->query_temp("quesths_times");
    if((i > 20 && random(20)==18))
    {
        qgood = QUEST_WUGOOD_D->query_good();
        msg = qgood["msg"+random(3)];
        want = 15+random(11);
	msg = YEL"����΢΢Ц�ţ������˵������������������\n"+msg
            +"\n���뷨Ūһ��"+qgood["name"]+"������ԼҪ "+want+" "+qgood["unit"]+"���ж��ٿ����Ƚ����١�ȥ�գ���\n"NOR;
        write(msg);
        quest = ([ 
                   "id"   : qgood["id"],
                   "name" : qgood["name"], 
                   "msg"  :  msg, 
                   "want"  : want,
                   "type" :  "��", 
                   "bonus" : qgood["bonus"], 
                   "level" : tag,
                ]),
        me->set("quest_hs",quest);
        return 1;
    }

    if(tag==8)
    {
            npc = new(CLASS_D("generate") + "/player_npc.c");
            NPC_D->place_npc(npc, me->query("combat_exp") < 500000  ? ({ "����һ��", "����ɽ", "����", "����" }) :
                                  me->query("combat_exp") < 800000 ? ({ "����һ��", "����ɽ", "����" }) : ({"����һ��", "����"}));
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

            npc->set("shen", npc->query("combat_exp") / 2000);
            msg="�������������˵����"+npc->name(1)+
                "������ʼ�����޳�֮ͽ���Σ�����֣���˵�������" + 
                place + "����ȥ�������ɣ���\n";

            quest = ([
                "name" : npc->name(1),
                "id"   : npc->query("id"),
                "bonus": (100+random(41)),
                "type" :"ɱ",
                "level":8,
                "chinese_w":place,
                "where":npc->query("startroom"),
                "msg":msg,
		"object":base_name(npc),
            ]);
            tell_object(me,quest["msg"]+"\n");
            me->set("quest_hs",quest);

            return 1;
    }
    else
    {
    quest = QUEST_HS_D(tag)->query_quesths();
/*
    if(undefinedp(quest["msg"]) || quest["msg"] == "")
*/
    switch(quest["type"])
    {
        case "ɱ":
                msg=HSMSG_D->query_hsmsg("ɱ",quest["name"]);
                break;
        case "Ѱ":
                msg=HSMSG_D->query_hsmsg("Ѱ",quest["name"]);
                break;
        case "��":
                npc = new(CLASS_D("generate") + "/hs_target.c");
                NPC_D->place_npc(npc, me->query("combat_exp") < 500000  ? ({ "����һ��", "����ɽ", "����", "����" }) :
                                      me->query("combat_exp") < 800000 ? ({ "����һ��", "����ɽ", "����" }) : ({"����һ��", "����"}));
                NPC_D->set_from_me(npc, me, 100);
                npc->set_temp("quester",me->query("id"));
                NPC_D->random_move(npc);
                NPC_D->random_move(npc);
                NPC_D->random_move(npc);
                place = npc->query("place");
                msg = hs_msg[random(5)]+npc->name(1)+"ȥ�������ͬ��������߲���Ǯ���ط��ֶ���ֶ�β��ã�"
                        "��˵����������"+place+"����ȥ���ԣ�\n���Ҳ�ղ���Ǯ������������"+quest["name"]+"����������Ҫ��ʾ(chushi)һ�¡�";
                thing = new("/quest/quesths/wulin-ling");
                thing->move(me);
                message_vision("���ѽ��������$N��\n",me);
                quest["target"] = npc->query("id");
                break;
        case "��":
                npc = new(CLASS_D("generate") + "/hs_receiver.c");
                NPC_D->place_npc(npc, me->query("combat_exp") < 500000  ? ({ "����һ��", "����ɽ", "����", "����" }) :
                                      me->query("combat_exp") < 800000 ? ({ "����һ��", "����ɽ", "����" }) : ({"����һ��", "����"}));
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
                msg = hs_msg[random(5)]+"����ҽ�"+thing->name(1)+"����"+npc->name(1)+"����"
                                        "����������"+place+"������ʱ�������ܾ��뿪�ˡ�";
                if (!thing->move(me))
                {
                    thing->move(environment());
                    message_vision("���ѽ�$N���ڵ��ϡ�\n",thing);
                } else message_vision("���ѽ�$N����$n��\n",thing,me);
                quest["thing"] = thing;
                break;
    }
    }
    quest["msg"] = msg;
    quest["level"] = tag;
    me->set("quest_hs", quest);
    if(stringp(quest["msg"])&&quest["msg"]!="")
                write(YEL""+quest["msg"]+"\n"NOR);
    else
    {
                write(YEL""+msg+"\n"NOR);
                me->set("quest_hs/msg", msg);
    }
    return 1;
}

int accept_object(object me, object ob)
{
    int rank,exp,pot,score,times, i,tag,all_quest_hs;
    mapping quest;
    object gold,who,obj;
    string msg;
    int mar,weiwang,shen,quest_count;
    mixed special = 0;
    
    who = this_object();
    
    if( (me->query("character") != "��������") && (me->query("character") != "������") && !(me->query("shen") <0))  
    {
        write("��������������Ǻ��ˣ���\n");
        return 0;
    }
    else if(!(quest = me->query("quest_hs")))
    {
        write("����˵�������޹�����»���������ջء���\n");
        return 0;
    }

    if(ob->query("money_id"))
    {
           if (ob->value() < 5000000)
           {
                   tell_object(me,"�����������õĶ���˵����ôһ���Ǯ����������ʲô�����Լ����������ðɣ�\n");
                   return notify_fail("����̧ͷ���죬����˵�����������500���ƽ𣬻����Ҿ��������������\n");
           }
           me->delete("quest_hs");
           tell_object(me,"���ѽӹ����" + ob->name(1) + "��΢΢Ц��Ц����ͷ����������������������˰ɡ�\n");
           destruct(ob);
           return 1;
    }

    else if(quest["type"]!="Ѱ"&&quest["type"]!="��"&&quest["type"]!="��"&&quest["type"]!="��")
    {
        write("����˵��������û�н���ȥ�Ҷ������������ջء���\n");
        return 0;
    }
    else if (quest["type"] != "��" && ob->name(1) != quest["name"])
    {
        write("����˵�������ⲻ������Ҫ�ġ���\n");
        return 0;
    }
    
    if(userp(ob) || ob->query("user"))
    {
        write("���Ѵ�ŭ�����������С�ӣ���Ȼ����ƭ�����������ˣ���������ץ��������\n");
        me->move("/d/register/prison");
        log_file( "static/QUEST_DIJIAO", sprintf("%s(%s)(��������)����%s(%s)(%s)����\n", me->query("name"),
             me->query("id"),ob->name(),ob->query("id"),ctime(time()) ) );
        return 1;
    }

    message_vision("$N��$n�������ѡ�\n",me,ob);
    times = me->query_temp("quesths_times"); //��������
    tag = me->query("quest_hs/level")+1;       //����ȼ�
    if((i=me->query_temp("quesths_times")) < 10)   i = 10 - i;
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

    if(quest["type"]=="��"&&(string)ob->query_temp("zheng")!=me->query("id"))
    {
        write("���ѽӹ�����һ��ŭ������������������ģ�������ƭ���������ߣ���Ľ������������ˣ���\n");
        me->add("weiwang",-weiwang*(random(5)+4)/4);
        if (me->query("weiwang") < 0) me->set("weiwang",0);
        me->delete("quest_hs");
        return 1;
    }
    if(quest["type"]=="��")
    {
        if (!ob->is_receipt() || ob->query("reply_to") != who->query("id"))
        {
            write("���ѽӹ���һ������ü���������������ո�ʲô����\n");
            return 0;
        }
    } 
    if(quest["type"]=="��")
    {
        if((int)quest["want"]>(quest["ok"]+1))
        {
            me->add("quest_hs/ok",1);
            write("���ѽӹ������ͷ˵������ "+quest["ok"]+" �ˣ��ܺã����� "+(quest["want"]-quest["ok"])+" ��������Ŭ������\n");
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
    write("���ѽӹ���˵�������ܺã������������ɵò�����\n");
    destruct(ob);

    if (quest["type"]=="��" && objectp(obj = present("wulin ling", me)))
	destruct(obj);

    if(!random(10))
    {
        i=(exp/400+1);
        if(i>5) i=5;
        gold=new("/clone/money/gold");
        gold->set_amount(i);
        tell_object(me,"Ȼ��ȡ��һ���ƽ���㣺����ν���Щ���ӣ��´μ���Ŭ������\n"
                       HIW"\n�㱻������ "+i+" ���ƽ�\n");
        if(!gold->move(me))
        {
            message_vision("����$N���϶���̫�أ��ƽ�һ���Ӵ����л����˵��ϡ�\n",me);
            gold->move(environment());
        }
        QUEST_D->bonus(me, ([ "exp" : exp, "pot" : pot, "mar" : mar,
                            "weiwang" : weiwang, "score" : score, "percent" : 50 ]), 1);
    }
    else QUEST_D->bonus(me, ([ "exp" : exp, "pot" : pot, "mar" : mar,
                              "weiwang" : weiwang, "score" : score ]), 1);
    
    if ( times < 1 )
        me->set_temp("quesths_times",1);
    else
        me->add_temp("quesths_times",1);
        me->set_temp("hs_giveup",0);        

   me->add("pk_score",-5);
   if (me->query("pk_score") < 0) me->set("pk_score",0);

   quest_count = me->query_temp("quesths_times");
   if (quest_count == 50)
   {
       msg = "$N�Ǻ�Ц�������������㻹���ԣ�������ʮ"
       "��������ɵ�ƯƯ����������Ŭ������\n";
	special = 1;
	   } else
       if (quest_count == 100)
   { 
       msg = "$NЦ�ĺϲ�£�죬������һ�۵�������־����һ��"
       "������ɵøɾ���������\n";
       special = "/d/shaolin/obj/puti-zi";
   } else
    if (quest_count == 300)
    {
        msg = "$N̾���������ǳ���������ǰ�ˣ��벻�����������"
               "��������һ��©�����ף����ף���\n";
	 special = "/clone/misc/tianxiang";
    } else
    if (quest_count == 350)
    {
        msg = "$N����һ��������������ĺ��ʺ�ѧ�䣬����������"
               "��ʮ��������һ��©�����ף����ף���\n";
	 special = "/clone/misc/tianxiang";
    } else
    if (quest_count == 400)
    {
        msg = "$N̾����������һ����ѧ��Ű����벻��������İ�"
               "��������һ��©�����ף����ף���\n";
	 special = "/clone/misc/tianxiang";
    } else
    if (quest_count == 450)
        {
        msg = "$N����������������ţ�������ţ������������İ�"
               "��ʮ��������һ��©�����ף����ף���\n";
        special = "/clone/gift/jiuzhuan";
    } else
       if (quest_count == 500)
   {
       msg = "$N����̾�˿�����������û�뵽��������ٴ�"
       "������һʧ�֣������Ժ����������Щ��������������\n";
       special = "/clone/gift/jiuzhuan";
   } else
       if ((quest_count % 10) == 0)
   {
       msg = "$N΢΢��ͷ�����ɵĲ�����Ȼ����" +
       chinese_number(quest_count) +
       "�ζ�û��ʧ�֣�������������ɣ���\n";
   }
   if (special) {
       message_vision(msg, who, me);
       QUEST_D->special_bonus(who, me, special);
   }

    me->delete("quest_hs");

   //��¼�������Ĵ�������Ҫ���������������1000������ˮ����Ƭ
   all_quest_hs = (int)me->query("all_quest_hs");
   if (!all_quest_hs) all_quest_hs = 0;
   all_quest_hs += 1;
   if (all_quest_hs == 1000)
   {
       obj = new("/clone/gift/ccrystal");
       tell_object(me,this_object()->name() + "�ֶ�����˵�ͷ�����Ѿ������������һǧ����������������\n" +
                   "�и�" + obj->query("name") + "���ͽ������ˣ�\n");
       if (!obj->move(me))
               obj->move(environment());
       me->set("all_quest_hs",0);
   } else me->set("all_quest_hs",all_quest_hs);
   return 1;
}

int give_up()
{
    object me,ob,obj;
    int giveup,rank;
    mapping quest;
    
    me = this_player();
    if( me->query("quest_hs")) 
    {
    if( (me->query("character") != "��������") && (me->query("character") != "������") && !(me->query("shen") <0))  
        return 1;
    }
    if((quest =  me->query("quest_hs")))
    {
        message_vision("$Nսս�������ߵ�������ǰ�����С�ĸ���������������������......��\n",me);
        if (quest["type"] == "��")
        {
               if (ob = present("wulin ling",me))
               {
                        ob->move("/d/register/prison");
                        destruct(ob);
               }
        }
        if (quest["type"] == "��")
        {
                if (objectp(ob = quest["thing"]))
                {
                        ob->move("/d/register/prison");
                        destruct(ob);
                }
        }
        message_vision("���Ѷ�$N̾��һ����: ��ô�������Խ��ô�򵥵����鶼�����ˡ�\n", me);
        
        rank = me->query("quest_hs/level");
        me->add("weiwang",-(rank*6+random(rank+4)));
        if ( me->query("weiwang")<0 )
               me->set("weiwang",0);
        write("���Ѹ����㣺����Ľ������������ˣ���\n");

        me->set_temp("quesths_times",0);

        giveup = me->query_temp("hs_giveup");
        if ( giveup < 1 )
            me->set_temp("hs_giveup",1);
        else if ( giveup < 5 )
            me->set_temp("hs_giveup",giveup+1);
        else me->set_temp("hs_giveup",5);

        me->set_temp("quesths_giveup_time",time());
   
        me->delete("quest_hs");
    }
    else
        write("���Ѹ����㣺��Ŀǰû���κ�����\n");
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
 
    if(d) time = chinese_number(d) + "��";
    else time = "";
 
    if(h) time += chinese_number(h) + "Сʱ";
    if(m) time += chinese_number(m) + "��";
        time += chinese_number(s) + "��";
    return time;
}

void destory(object ob)
{
    if(!ob) return;
    if(ob->is_character())
        message_vision("$NͻȻһ���̵��ܵ�ûӰ�ˡ�\n",ob);
    ob->move("/d/wizard/prison");
    destruct(ob);
    return ;
}

