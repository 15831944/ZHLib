// kuihua ����̫��

#include <ansi.h>
#define QUESTKILL_D    "/quest/questkh/quest/questkill"
#define QUESTKH_D(x)   ("/quest/questkh/quest/questkh" + x)
#define KHMSG_D      ("/quest/questkh/kuihua-msg")

inherit NPC;
inherit F_MASTER;
inherit F_NOCLONE;

mixed ask_opinion();
void greeting(object);
void init();
int give_quest();
int give_up();
void destory(object);
void npc_dest(object);
string time_period(int timep);

#define ULTRA_OPINION   "��ʦ"
#define OPINION_TYPE    HIY "������" NOR 
#define MY_OPINION      "dodge"

string  *my_opinions = ({ "dodge" });

// ��ͷ�ļ�����������Ƕ��
#include <ultra.h>

void create()
{
        set_name("����̫��", ({ "kuihua taijian", "kuihua", "taijian" }) );
        set("title", HIR "����ʦ" NOR);
        set("gender", "����");
        set("age", 99);
        set("long", "���������������������𣬲�֪��ϲ��ŭ��\n");
        set("attitude", "peaceful");
        set("str", 31);
        set("int", 39);
        set("con", 34);
        set("dex", 36);

        set("max_qi", 9999);
        set("max_jing", 9999);
        set("neili", 9999);
        set("max_neili", 9999);
        set("jiali", 80);

        set("combat_exp", 50000000);

        set("inquiry", ([
                "��������" : "������д��һ�������Ṧ������ĵã���ô��������Ȥ��",
                "����"     : (: ask_opinion :),
                "opinion"  : (: ask_opinion :),
                "��ѧ����" : "ѧϰ����书��û��������ѧ����(martial-cognize)����Ҳ���ᣡ",
                "����" : "����̫�����ͷ����Ħ�����е������⣬ȫ���ע����������\n",
        ]));

        set_skill("unarmed", 500);
        set_skill("finger", 500);
        set_skill("parry", 500);
        set_skill("dodge", 500);
        set_skill("force", 500);
        set_skill("sword", 500);
        set_skill("kuihua-mogong", 500);
        set_skill("martial-cognize", 500);
        set_skill("literate", 220);

        map_skill("parry", "kuihua-mogong");
        map_skill("force", "kuihua-mogong");
        map_skill("dodge", "kuihua-mogong");
        map_skill("finger", "kuihua-mogong");
        map_skill("sword", "kuihua-mogong");

        prepare_skill("finger", "kuihua-mogong");

        set("opinion/ultra",  1);
        set("opinion/master", 1);

        set("rank_info/self", "����");

        setup();
        carry_object("/clone/cloth/cloth")->wear();
        carry_object("/clone/misc/spin")->wield();

        set("startroom", "/d/beijing/shanlu3");
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
                return "�٣�������书ֻ��ץץ����";

        if (me->query("opinion/" MY_OPINION) == ULTRA_OPINION)
                return "�ţ����Ṧ�������Ϊ�Ѿ��Ƶ�������ʦ�ˣ�Ҫ������Ȥ���ǹ����У�";

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

        switch(me->query_temp("want_opinion/kuihua"))
        {
        case 0:
                command("say �ðɣ���׼�����˾ͽ���һ�У��ҿ������ˮƽ��Ρ�");
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

        me->add_temp("want_opinion/kuihua", 1);
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
        lvl += 20;
        return lvl;
}

void do_congration(object me)
{
        command("chat* heihei " + me->query("id"));
}

int accept_hit(object me)
{
        command("heng");
        command("say ���ò��ͷ��ˣ�");
        kill_ob(me);
        return 1;
}

int accept_fight(object me)
{
        object weapon;

        if (me->query("opinion/" MY_OPINION) == ULTRA_OPINION)
        {
                message_vision("$N��$n�������ܺã���Ҳ���Ƕ�������ˣ�"
                               "���ɣ����ǱȻ�һ�£���\n",
                               this_object(), me);
                return 1;
        }

        if (! me->query_temp("want_opinion/kuihua"))
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

        call_out("check_opinion", 2, me);
        set_temp("opinion", me);
        me->delete_temp("want_opinion");
        message_vision("\n$Nһ���ֵ������������������롣��\n",
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
        if (me->query("character") != "���ռ�թ")
        {
                command("say ������û����������ľ���֮����"
                        "�ǻ�ȥ�ɣ�");
                return -1;
        }

        if (! ultrap(me))
        {
                command("say �����ѧ�书���㻹�����ʸ�"
                        "������˴���ʦ��˵�ɣ�");
                return -1;
        }

	if (skill == "kuihua-mogong")
	{
                command("say ��ѧ�ҵĿ���ħ����������Ƿ������õģ�"
                        "���������ѧ����ѧ��������������");
                return -1;
	}

/*
	if (skill == "martial-cognize")
		return 1;

        if (! ultrap(me))
        {
                command("say ��ѧ�ҵĿ����񹦣��㻹�����ʸ�"
                        "������˴���ʦ��˵�ɣ�");
                return -1;
        }

        if (me->query_skill(skill, 1) >= 180)
        {
                command("say ���ˣ��Ҿͽ��㵽����ɣ��书����"
                        "Ҫ���Լ����о����ǣ�");
                return -1;
        }

        if (skill != "kuihua-mogong")
                return 1;

        if (me->query_temp("can_learn/kuihua/kuihua-mogong"))
                return 1;

        me->set_temp("can_learn/kuihua/kuihua-mogong", 1);
        command("nod");
        command("say �����Ҿʹ�������񹦰ɣ���Ҫ��ʲô����"
                "���䣬��������ȥ���˵ģ�");
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
    mapping questtemp,questkh,questkill,skills;
    object ob,npc;
    int exp,time,level,i,lev,lev1;
    string msg,*sname,place;
        
    ob = this_player();
    exp = (int)ob->query("combat_exp");

    if( (ob->query("character") != "���ռ�թ") && (ob->query("character") != "�ĺ�����"))  
    {
        message_vision("����̫��̧ͷ����$Nһ�ۣ�����ɤ�ӵ���������ż��ʼ���Ļ�ɫ���ٲ����ϸ��ҹ�����������Ѫ���岽����\n", ob);
        return 1;
    }
    if( ob->query("shen") >= 0)  
    {
        write("����̫��ͷҲ��̧������̾�˿������������ú�һ���ˣ�ƫҪ����Ͷ���������ҵ������������ǲ����������\n");
        return 1;
    }
    if(exp < 500000)
    {
        write("����̫��ͷҲ��̧���������������ȥ��������ɣ���Ϊ�����£��㻹�����ء���\n");
        return 1;
    }
    if (mapp(ob->query("quest_kh")))
    {
       write("����̫����������й��棬΢΢��ͷ��������������ͷ�������������ˣ���\n");
        return 0;
    }
    if (mapp(ob->query("quest_sn")))
    {
        ob->delete_temp("questsn_times");
        ob->delete("quest_sn");
    }

    if((time()-ob->query_temp("questkh_giveup_time")) < (2+random(2)))
    {
        write("��Ҫ������һ���\n");
        return 1;
    }

    // ���¸�����
    if(exp <= 600000)        level = 0;
    else if(exp <= 900000)   level = 1;
    else if(exp <= 1200000)  level = 2;
    else if(exp <= 1800000)  level = 3;
    else if(exp <= 2500000)  level = 4-random(3);
    else if(exp <= 3200000)  level = 5-random(3);
    else if(exp <= 4000000)  level = 6-random(3);
    else
    {
        if(random(15)==0||(exp>10000000&&random(8)==0))
            level=8;
        else level=7-random(3);
    }

    i = ob->query_temp("questkh_times");
   
    if(i > 20 && random(20) == 15)
    {
        questkill = QUESTKILL_D->query_questkill();
        msg = questkill["msg"];
        write("����̫�����۽������һ�ۣ�΢¶��ɫ���������㵹�Ǻ���ͦ�ܸɵ���ţ���\n");
        write(msg+"\n");
        time = questkill["time"]/2+random(questkill["time"]/2);
        write("����̫���ͷ���˿��㣬�ֵ������Ҹ���"+time_period(time)+"ʱ�䣬���ȥ�ա���\n");
        time += time();
      //��Ҫֱ���޸�questkill
        questkh = ([
            "name" :  questkill["name"], 
            "khmsg":  msg, 
            "dir"  :  questkill["dir"],
            "dir1" :  questkill["dir1"], 
            "type" :  questkill["type"], 
            "time" :  time,
            "level":  level,
            "desc" :  "��",
            ]),
        ob->set("quest_kh",questkh);
        return 1;
    }
    else
    {
        if(level==8)
        {
            npc = new(CLASS_D("generate") + "/player_npc.c");
            NPC_D->place_npc(npc, ob->query("combat_exp") < 500000  ? ({ "����һ��", "����ɽ", "����", "����" }) :
                                  ob->query("combat_exp") < 800000 ? ({ "����һ��", "����ɽ", "����" }) : ({"����һ��", "����"}));
            npc->set_from_me(ob,1);
            npc->add_temp("apply/attack", npc->query_skill("force") * (level - 1) / 15);
            npc->add_temp("apply/dodge", npc->query_skill("force") * (level - 1) / 15);
            npc->add_temp("apply/parry", npc->query_skill("force") * (level - 1) / 15);
            npc->add_temp("apply/damage", 5 + level * 7);
            npc->add_temp("apply/unarmed_damage", 5 + level * 7);
            npc->add_temp("apply/armor", 10 + level * 15);
            npc->set_temp("quester", ob->query("id"));
            npc->set("auto_perform",1);
            NPC_D->random_move(npc);
            NPC_D->random_move(npc);
            NPC_D->random_move(npc);
            place = npc->query("place");

            npc->set("shen", npc->query("combat_exp") / 2000);
            msg="����̫��޺޵�˵����"+npc->name(1)+
                "�����ν�Ĵ����Ŵκ������ԣ���˵�������" + 
                place + "����ȥ����������ͷ��������\n";

            questkh = ([
                "name" : npc->name(1),
                "id"   : npc->query("id"),
                "bonus": (100+random(41)),
                "type" :"ɱ",
                "level":8,
                "chinese_w":place,
                "where":npc->query("startroom"),
                "khmsg":msg,
		"object":base_name(npc),
            ]);
            tell_object(ob,questkh["khmsg"]+"\n");
            ob->set("quest_kh",questkh);

            return 1;       
        }
        else
            {
                questtemp = QUESTKH_D(level)->query_questkh(ob);
                if(undefinedp(msg = questtemp["msg"]) || msg == "" || random(2))
                {
                                if(questtemp["race"])
                                        msg=KHMSG_D->query_khmsg("��",questtemp["name"]);
                                else
                                        msg=KHMSG_D->query_khmsg(questtemp["type"],questtemp["name"]);
                        }
                questkh=([
                        "id":questtemp["id"],
                        "name":questtemp["name"],
                        "bonus":questtemp["bonus"],
                        "type":questtemp["type"],
                        "khmsg":msg,
                        "level":level,
			"object":questtemp["object"],
                        ]);
                write(questkh["khmsg"]+"\n");
                ob->set("quest_kh",questkh);
            }
    }  
    return 1;
}

int accept_object(object who, object ob)
{
   int exp, pot,level,bonus,i,all_quest_kh;
   mapping questkh;
   object me,gold,obj;
   int shen,mar,weiwang,score,quest_count;
   string msg;
   mixed special;
        
   me = this_object();
   if(!(questkh =  who->query("quest_kh")) ||
      (questkh["type"] != "Ѱ" && questkh["type"] != "ɱ"))
   {
      return notify_fail("����̫���������ͷ��ĳ���˵�����߿�����Ҫ�����ҡ���\n");
   }

   if(ob->query("money_id"))
   {
           if (ob->value() < 5000000)
           {
                   tell_object(who,"����̫�ಪȻ��ŭ����������ô��Ǯ�����Ұ����ٲ����ҹ�Զ�㣬�Ұ������Ƥ��\n");
                   return notify_fail("����̫�������˵������ܸ���500���ƽ𣬻����Ҿ��������������\n");
           }
           who->delete("quest_kh");
           tell_object(who,"����̫�����������е�" + ob->name(1) + "���������������������������˰ɡ�\n");
           destruct(ob);
           return 1;
   }

   switch(questkh["type"])
   {
      case "Ѱ"  :
         if(ob->name(1) != questkh["name"] || userp(ob))
         {
            tell_object(who,"����̫���ŭ�������������ʲô��������������Ū��ô����\n");
            return notify_fail("����̫�����˿���������˦˦�֣���������ȥ�ɣ���Ҫ���ҡ���\n");
         }
         break ;
      case "ɱ"  :
         if(!ob->is_head() && !ob->is_corpse())
         {
            tell_object(who,"����̫��б���۾�����һ�£�����������Ǹ�ʲô��������������Ū��ô����\n");
            return notify_fail("����̫�������һ�ۣ�˦˦�֣��������㻹վ�������ʲô��������ȥ����\n");
         }
         else if (! stringp(ob->query("owner_name")) || ob->query("owner_name") != questkh["name"])
            {
                tell_object(who,"����̫�����ű��ӻ���˵������ʲô�����ģ���������ߣ���\n");
                return notify_fail("����̫�������һ�ۣ�˦˦�֣��������Ҹ�����������Ƿ������ˣ���\n");
            }
            else if(ob->query("killed_by") != who->query("id"))
            {
                tell_object(who,"����̫�����һ�����������Ǵ���������ģ����Լ�������ô����\n");
                return notify_fail("����̫�������һ�ۣ�˦˦�֣��������㻹վ�������ʲô���������ȥ����\n");
             }
         break ;
      default    :   
         return 0;
   }

    if(userp(ob) || ob->query("user"))
    {
        write("����̫���ŭ�����������С���֣���Ȼ����ƭ���������ˣ���������ץ��������\n");
        who->move("/d/register/prison");
        log_file( "static/QUEST_DIJIAO", sprintf("%s(%s)(��������)����%s(%s)(%s)����\n", who->query("name"),
             who->query("id"),ob->name(),ob->query("id"),ctime(time()) ) );
        return 1;
    }

   message_vision("$N��$n��������̫�ࡣ\n",who,ob);
   tell_object(who,"����̫����Ц��һ����̧ͷ���˿��㣬��ͷ�������ţ������ȥ�ˡ���\n");
    destruct(ob);
   if((i=who->query_temp("questkh_times")) < 10)   i =10-i;
   else i = 1;
   level = questkh["level"]+1;
   exp = level*80 + questkh["bonus"]*3;
   exp += random(exp/2);
   exp = exp/i;

   if (level > 4 && i > 5)
	exp /= 2;

   pot = exp/(2+random(2));
   score = random(exp/20);
   weiwang = random(exp/15);

   if (who->query_temp("questkh_times") + 1 > 200)
	mar = exp/5 + random(who->query_temp("questkh_times"));
   else mar = random(20);

   if(!random(18))
   {
      i=(exp/100+1);
      if(i>20) i=20;
      gold=new("/clone/money/gold");
      gold->set_amount(i);
      tell_object(who,"ͻȻһ���ƽ����������У��������̫������˵��������Щ������ȥ���պ���������㣡��\n"
          HIW"\n�㱻������ "+i+" ���ƽ�\n"NOR);
       if(!gold->move(who))
       {
          message_vision("����$N���϶���̫�أ��ƽ�һ���Ӵ����л����˵��ϡ�\n",who);
          gold->move(environment());
      }
      QUEST_D->bonus(who, ([ "exp" : exp, "pot" : pot, "mar" : mar, 
                            "weiwang" : weiwang, "score" : score, "percent" : 50 ]), 1);
   }
   else QUEST_D->bonus(who, ([ "exp" : exp, "pot" : pot, "mar" : mar,
                              "weiwang" : weiwang, "score" : score ]), 1);
   
   quest_count = who->query_temp("questkh_times") + 1;
   if (quest_count == 50)
   {
       msg = "$N�ٺ���Ц������������С�ӻ����ԣ�������ʮ"
       "��������ɵĸɾ������������е�ǰ;����\n";
	special = 1;
	   } else
       if (quest_count == 100)
   { 
       msg = "$Ņͷʹ��������һ�۵��������ǲ���һ��"
       "������ɵû����׵�����\n";
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
       msg = "$N����̾�˿������������벻����������ٴ�"
       "������һʧ�֣������Ժ�Ľ��������������������\n";
       special = "/clone/gift/jiuzhuan";
   } else
       if ((quest_count % 10) == 0)
   {
       msg = "$N΢΢��ͷ�����ɵĲ�����Ȼ����" +
       chinese_number(quest_count) +
       "�ζ�û��ʧ�֣��������Һúñ��֣���\n";
   }
   if (special) {
       message_vision(msg, me, who);
       QUEST_D->special_bonus(me, who, special);
   }
   who->add_temp("questkh_times",1);
   who->delete("quest_kh");
   who->add("pk_score",-5);
   if (who->query("pk_score") < 0) who->set("pk_score",0);

   //��¼�������Ĵ�������Ҫ���������������1000��������ʯ��Ƭ
   all_quest_kh = (int)who->query("all_quest_kh");
   if (!all_quest_kh) all_quest_kh = 0;
   all_quest_kh += 1;
   if (all_quest_kh == 1000)
   {
       obj = new("/clone/gift/cdiamond");
       tell_object(who,this_object()->name() + "�ֶ�����˵�ͷ�����Ѿ������������һǧ����������������\n" +
                   "�и�" + obj->query("name") + "���ͽ������ˣ�\n");
       if (!obj->move(who))
               obj->move(environment());
       who->set("all_quest_kh",0);
   } else who->set("all_quest_kh",all_quest_kh);

   return 1;
}

int give_up()
{
   object ob,obj,room;
   mapping questkh;

   ob = this_player();

   if(query("kill_all"))   return 0;

   if(mapp(questkh =  ob->query("quest_kh")))
   {
      if(questkh["desc"] == "��")
      {
         message_vision("$N�ľ���ս��˫���Ҳ����������̫��ȡ���Լ�������\n",ob);
         message_vision("����̫�࿴��$Nһ�ۣ����š���һ�������ÿɷ�\n", ob);
      }
      else if(questkh["type"] == "ɱ"&&questkh["level"] == 8)    //by llm
      {
          message_vision("$N�ľ���ս��˫���Ҳ����������̫��ȡ���Լ�������\n",ob);
          message_vision("����̫��ͷҲ��̧������һ��������û�õĶ��������ģ���\n", ob);
          if(!(room = find_object(questkh["where"])) )
              room = load_object(questkh["where"]);

          if(objectp(obj = present(questkh["id"],room))
              &&obj->is_character()
              &&!userp(obj))
          {
              message_vision("$N����һ����ת���߿��ˡ�\n",obj);
              obj->move("/d/register/prison");
              destruct(obj);
          }
          ob->set_temp("questkh_times",0);
      }
      else
      {
         message_vision("$N�ľ���ս��˫���Ҳ����������̫��ȡ���Լ�������\n",ob);
         message_vision("����̫��ͷҲ��̧������һ��������û�õĶ��������ģ���\n", ob);
         ob->set_temp("questkh_times",0);
      }
   }
   else
   {
      message_vision("$N�ľ���ս��˫���Ҳ����������̫��ȡ���Լ�������\n",ob);
      message_vision("����̫��ר�İ������еĹŶ����������û����$N\n", ob);
   }
   ob->delete("quest_kh");
   ob->set_temp("questkh_giveup_time",time());
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

void npc_dest(object npc)
{
    if(!npc) return;
    if(npc->is_fighting()&&npc->query_temp("wait_times")<4)
    {
        npc->add_temp("wait_times",1);   //4�λ���
        call_out("npc_dest",60,npc);     //�ٵ�һ����
        return;
    }
    if(npc->is_character())
        message_vision("$N����һЦ��������̫������¾���һЩ���ҷϣ���ת��һ�Σ��Ѳ�������Ӱ��\n",npc);
    npc->move("/d/register/prison");
    destruct(npc);
    return ;
}
