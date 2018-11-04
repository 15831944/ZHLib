// shenni �Ϻ�����

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
"�Ϻ�����΢Ц��˵����",
"�Ϻ���������۾�ڤ˼Ƭ�̵�����",
"�Ϻ������ͷ�����룬˵������",
"�Ϻ������������֣�˵������",
"�Ϻ�����΢΢Ц��Ц������",
});

string* qin_msg1 = ({
"���������ǵ����ѣ�����name����Ӱ������̬������������Ҳ�Ϳ����ˣ�",
"����˵name����ķ�ֳ��Ӱ���˵��ص���̬���������ǲ�Ӧ�����ɱ���",
"�ѵ�nameҲ�����������鷳������ϡ�棬�ҵ����뿴������",
"������Ļ�԰���źܶ�Ķ������û��name��",
"�ڿ��е�ʱ�򣬿�������������ܹ�����������name��ʵͦ�ɰ��ģ�",
"���������һ����ϲ��������ˣ�������name�������͸�����������ò�����",
"�����ϴ��ɱɱ�ģ��ٲ�����nameҲ�����޹����ۣ������ı�������",
});

string* qin_msg2 = ({
"��ȥ���������������ɡ���",
"ȥ�ҵ�����������������",
"���ܰ�������������ô����",
"�������һ��ȥ���Ұ��������ɡ���",
"����Ū�����ҡ���",
});

#define ULTRA_OPINION   "��ʦ"
#define OPINION_TYPE    HIY "�ڼҹ���" NOR 
#define MY_OPINION      "force"

string  *my_opinions = ({ "force" });

// ��ͷ�ļ�����������Ƕ��
#include <ultra.h>

void create()
{
        set_name("�Ϻ�����", ({ "nanhai shenni", "shenni", "nanhai" }) );
        set("title", HIG "����ʦ" NOR);
        set("gender", "Ů��");
        set("age", 91);
        set("long", "����һλ�������ᣬ��������ʲô��ͬ��\n");
        set("attitude", "peaceful");
        set("class", "bonze");
	set("nickname",HIY"����ͬ��"+HIW"������"+NOR);
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
                "��ָ��ͨ" : "�����ұ̺��񹦹���ָ������ı仯�������ҵ��������������ڸ�һ�ˡ�",
                "����"     : (: ask_opinion :),
                "opinion"  : (: ask_opinion :),
                "��ѧ����" : "�ú�����Լ�����ѧ����(martial-cognize)����ʱ��ʲô�书����С���ƣ�",
                "����" : "�����׺ݵ����������ɵ��ˣ�������������������(quest)��\n",
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

        set("rank_info/self", "����");

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
                return "�ߣ�������书Ҳ�����������ۣ�";

        if (me->query("opinion/" MY_OPINION) == ULTRA_OPINION)
                return "�����ˣ����ڹ��������Ϊ�Ѿ��Ƶ�������ʦ�ˣ�Ҫ�Ǻ�ƶ����ϼ���Ҳ����";

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

                message_vision("$N��Ϊ��ŭ�Ķ�$n������û������æ���𣿡�\n",
                               this_object(), me);
                return 1;
        }

        switch(me->query_temp("want_opinion/shenni"))
        {
        case 0:
                command("say �ðɣ����ǹ�һ�У�����һ��������");
                break;
        case 1:
                command("say ��׼����û�У����˾����ɡ�");
                break;
        case 2:
                message_vision(CYN "$N" CYN "��ü��$n" CYN
                               "�������ҿ��������ǹ����µġ���\n" NOR,
                               this_object(), me);
                break;
        case 3:
                command("say ����ұ���������죡");
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
        command("chat �����������ǲ���");
}

int accept_hit(object me)
{
        command("heng");
        command("say �����" + RANK_D->query_rude(me) + "���������ҵ������ˣ�");
        kill_ob(me);
        return 1;
}

int accept_fight(object me)
{
        object weapon;

        if (me->query("opinion/" MY_OPINION) == ULTRA_OPINION)
        {
                message_vision("$N��$n�������ܺã���Ҳ������ʦ�����ˣ�"
                               "���ɣ����ǱȻ�һ�£���\n",
                               this_object(), me);
                return 1;
        }

        if (! me->query_temp("want_opinion/shenni"))
        {
                command("say ���ʲôҪ���Ҷ��֣�");
                return 0;
        }

        command("look " + me->query("id"));

        COMBAT_D->do_attack(this_object(), me, 0);

        if (me->query("qi") <= 0)
        {
                message_vision("\n$Nҡҡͷ��$n�����������ڵ��书"
                               "�����Զ������һ�ж��Ӳ�ס����\n",
                               this_object(), me);
                return notify_fail("����Ҫ�úõ����������ˡ�\n");
        }

        message_combatd("$N�������������$n������ԣ�����ͬʱ����������"
                       "��һ���ֻ������ͷ����������������\n��Ȼ$N����"
                       "һ�����ջع�����û��һ�����ͣ�������$n��Ϊ�Ȼ��\n",
                       this_object(), me);
        if (me->query("neili") < 3000)
        {
                message_vision("$Nҡҡͷ��$n�������ʲ����������㣬����"
                               "�Ժ��������㽫�����������������ɣ���\n",
                               this_object(), me);
                return notify_fail("�������ǻ�ȥ����һ�������ɣ�\n");
        }
        me->set("neili", 0);
        

        call_out("check_opinion", 2, me);
        set_temp("opinion", me);
        me->delete_temp("want_opinion");
        message_vision("\n$Nһ���ֵ��������ˣ��������롣��\n",
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
        if (me->query("character") != "�ĺ�����")
        {
                command("say ���������Բ����������²��˺��ģ�"
                        "��û����Ȥ���㣡");
                return -1;
        }

        if (! ultrap(me))
        {
                command("say �����ѧ�书���㻹�����ʸ�"
                        "������˴���ʦ��˵�ɣ�");
                return -1;
        }

	if (skill == "bluesea-force")
	{
                command("say ��ѧ�ҵ��Ϻ�������������Ƿ������õģ�"
                        "���������ѧ����ѧ��������������");
                return -1;
	}

/*
	if (skill == "martial-cognize")
		return 1;

        if (! ultrap(me))
        {
                command("say ��ѧ�ҵı̺��񹦣��㻹�����ʸ�"
                        "������˴���ʦ��˵�ɣ�");
                return -1;
        }

        if (me->query_skill(skill, 1) >= 180)
        {
                command("say ���ˣ��Ҿͽ��㵽����ɣ��书����"
                        "Ҫ���Լ����о����ǣ�");
                return -1;
        }

        if (skill != "bluesea-force")
                return 1;

        if (me->query_temp("can_learn/shenni/bluesea-force"))
                return 1;

        me->set_temp("can_learn/dugu/bluesea-force", 1);
        command("nod");
        command("say �����ҽ����ҵľ�ѧ�̺��񹦣��ܲ���ѧ��"
                "�Ϳ�����컯�ˣ�");
*/
        return 1;
}

void unconcious()
{
//        message("vision", "\n"HIR + name() + "��ɫһ�䣬����һ����"
//                "Ѫ������һ�������Ų�����\n\n" NOR, environment());
//        command("chat �գ��գ��գ�ƶ��ȥҲ��");
//        destruct(this_object());
return;
}

void die()
{
//        message("vision", "\n"HIR + name() + "���һ����������һ����"
//                "Ѫ������һ�����ʹ˲�����\n\n" NOR, environment());
//        command("chat ƶ��ȥҲ��");
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

    if( (me->query("character") != "���ռ�թ") && (me->query("character") != "�ĺ�����"))  
    {
        write("�Ϻ�����ҡͷ������������ʵ��������½��������̫�����Ĵ������������ұ���Ҫ����ɡ�\n");
        return 1;
    }
    if( !(me->query("shen") > 0))
    {
        write("�Ϻ����ῴ����ֻ��ҡͷ�������߽���������Ҫ������Ȼ�ҽ�����ɱֹɱ��������а��̫�أ��������˰ɣ���\n");
        return 1;
    }
    if(exp < 500000)
    {
        write("�Ϻ�����΢Ц������������Դ����������ڵľ��飬��������ʵ��̫��Σ�գ��ú�ȥ������������ͷ�������ҡ�\n");
        return 1;
    }

 
    if ( quest = me->query("quest_sn") )
    {
        write("�Ϻ�����Ǻ�Ц��˵���ļ����ǺȲ������డ����Ҫ�ż�����������\n");
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
        write("�Ϻ�����Ц�Ŷ���˵��������ô�겻��������ô��˳������Ҫ�ż����Ⱥú�����ԭ�������\n");
        return 1;
    }

    quest = ([]);
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

    i = me->query_temp("questsn_times");
    if((i > 20 && random(20)==18))
    {
        qgood = QUEST_WUGOOD_D->query_good();
        msg = qgood["msg"+random(3)];
        want = 15+random(11);
	msg = YEL"�Ϻ�����ǺǴ�Ц�����˵�˵��������İ��������治����\n"+msg
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
        me->set("quest_sn",quest);
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

            npc->set("shen", -npc->query("combat_exp") / 2000);
            msg="�Ϻ��������ݶ���˵����"+npc->name(1)+
                "���������Σ�����֣���˵�������" + 
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
        case "��":
                msg = sn_msg[random(sizeof(sn_msg))] + replace_string(qin_msg1[random(sizeof(qin_msg1))],"name",quest["name"]) + qin_msg2[random(sizeof(qin_msg2))];
                break;
        case "ɱ":
                if (quest["object"]->query("race") != "����" || wizardp(me))
                {
                        quest["type"] = "��";
                        msg = sn_msg[random(sizeof(sn_msg))] + replace_string(qin_msg1[random(sizeof(qin_msg1))],"name",quest["name"]) + qin_msg2[random(sizeof(qin_msg2))];
                        break;
                } else msg=SNMSG_D->query_snmsg("ɱ",quest["name"]);
                break;
        case "Ѱ":
                msg=SNMSG_D->query_snmsg("Ѱ",quest["name"]);
                break;
        case "��":
                npc = new(CLASS_D("generate") + "/sn_receiver.c");
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
                msg = sn_msg[random(5)]+"�㿴�ܷ���ҽ�"+thing->name(1)+"����"+npc->name(1)+"����"
                                        "����������"+place+"���Ͻ�ȥ����Ȼ����ʱ�������ܾͲ����ˡ�";
                if (!thing->move(me))
                {
                    thing->move(environment());
                    message_vision("�Ϻ����Ὣ$N������ڵ��ϡ�\n",thing);
                } else message_vision("�Ϻ����Ὣ$N����$n��\n",thing,me);
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
    
    if( (me->query("character") != "���ռ�թ") && (me->query("character") != "�ĺ�����") && !(me->query("shen") > 0))  
    {
        write("�Ϻ����ᾪ�ȵĵ���������˭���������������ʲô����\n");
        return 0;
    }
    else if(!(quest = me->query("quest_sn")))
    {
        write("�Ϻ�����Ǻ�Ц��������֪������Т���ң����ǿ��Կ�ʵ���ж�������㻹���Լ����Űɡ���\n");
        return 0;
    }

    if(ob->query("money_id"))
    {
           if (ob->value() < 5000000)
           {
                   tell_object(me,"�Ϻ�����Ǻ�һЦ���Ҳ�ȱǮ���������Ǯ�����Լ����������԰ɡ�\n");
                   return notify_fail("�Ϻ���������˵�����������500���ƽ��Ҿ�ȡ�����������\n");
           }
           me->delete("quest_sn");
           tell_object(me,"�Ϻ��������ַ���" + ob->name(1) + "���������˵��������������������˰ɡ�\n");
           destruct(ob);
           return 1;
    }

    else if(quest["type"]!="Ѱ"&&quest["type"]!="��"&&quest["type"]!="��"&&quest["type"]!="��")
    {
        write("�Ϻ�����΢Ц��������û�н���ȥ�Ҷ���ѽ���������ջء���\n");
        return 0;
    }
    else if( ob->name(1) != quest["name"])
    {
        write("�Ϻ�����ҡͷ˵����������ɲ�������Ҫ��ѽ����\n");
        return 0;
    }

    if(userp(ob) || ob->query("user"))
    {
        write("�Ϻ������ŭ�����������С�ӣ���Ȼ����ƭ�������������ˣ���������ץ��������\n");
        me->move("/d/register/prison");
        log_file( "static/QUEST_DIJIAO", sprintf("%s(%s)(��������)����%s(%s)(%s)����\n", me->query("name"),
             me->query("id"),ob->name(),ob->query("id"),ctime(time()) ) );
        return 1;
    }

    message_vision("$N��$n�����Ϻ����ᡣ\n",me,ob);
    times = me->query_temp("questsn_times"); //��������
    tag = me->query("quest_sn/level")+1;       //����ȼ�
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

    if(quest["type"]=="��")
    {
        if (!ob->is_receipt() || ob->query("reply_to") != who->query("id"))
        {
            write("�Ϻ�����ӹ���һ������ü���������������ո�ʲô����\n");
            return 0;
        }
    } 
    if(quest["type"]=="��")
    {
        if((int)quest["want"]>(quest["ok"]+1))
        {
            me->add("quest_sn/ok",1);
            write("�Ϻ�����ӹ������˵�˵������Ҫ�ľ���������� "+quest["ok"]+" �ˣ�̫���ˣ����� "+(quest["want"]-quest["ok"])+" ��������Ŭ������\n");
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
    write("�Ϻ�����ӹ������ĵ�Ц��˵��������ѽ�������������ɵúܺã���\n");
    destruct(ob);
    if(!random(10))
    {
        i=(exp/400+1);
        if(i>5) i=5;
        gold=new("/clone/money/gold");
        gold->set_amount(i);
        tell_object(me,"Ȼ��ȡ��һ���ƽ���㣺�����߽�����������Ҫ����Ǯ����������Щ���ӣ�����ȥ�ðɣ���\n"
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
        me->set_temp("questsn_times",1);
    else
        me->add_temp("questsn_times",1);
        me->set_temp("sn_giveup",0);        

   me->add("pk_score",-5);
   if (me->query("pk_score") < 0) me->set("pk_score",0);

   quest_count = me->query_temp("questsn_times");
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

    me->delete("quest_sn");

   //��¼�������Ĵ�������Ҫ���������������1000����������Ƭ
   all_quest_sn = (int)me->query("all_quest_sn");
   if (!all_quest_sn) all_quest_sn = 0;
   all_quest_sn += 1;
   if (all_quest_sn == 1000)
   {
       obj = new("/clone/gift/cjade");
       tell_object(me,this_object()->name() + "�ֶ�����˵�ͷ�����Ѿ������������һǧ����������������\n" +
                   "�и�" + obj->query("name") + "���ͽ������ˣ�\n");
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
    if( (me->query("character") != "���ռ�թ") && (me->query("character") != "�ĺ�����") && !(me->query("shen") > 0))  
        return 1;
    }
    if((quest =  me->query("quest_sn")))
    {
        message_vision("$Nί���ĵ��Ϻ�������ǰ���ߣ������������û����ɣ������������˼ҵ�����......��\n",me);
        if (quest["type"] == "��")
        {
                if (objectp(ob = quest["thing"]))
                {
                        ob->move("/d/register/prison");
                        destruct(ob);
                }
        }
        message_vision("�Ϻ������$N΢Ц��˵:��û��ϵ���´κú�Ŭ������������\n", me);
        
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
        write("�Ϻ�����΢Ц�Ÿ����㣺����Ŀǰû���κ����񡣡�\n");
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
