// yue-buqun.c lasted updated by cocacola on 2.19 for adding chushi
// ����Ⱥ

inherit NPC;
inherit F_MASTER;
inherit F_COAGENT;
inherit F_QUESTER;

#include <ansi.h>
#include "qizong.h"

int  do_xunshan();
void check_weapon();
void unwield_weapon();
string ask_zixia();

// ���ظ��˼�����������֤��quest��ʱ���������quest
int is_bad() { return 0; }
int is_good() { return 1; }

void create()
{
        set_name("����Ⱥ", ({ "yue buqun", "yue" }) );
        set("title", "��ɽ������");
        set("nickname", HIC "���ӽ�" NOR);
        set("gender", "����");
        set("class", "swordsman");
        set("age", 55);
        set("long", "����Ⱥ����ִ�ƻ�ɽ�ɣ��˵���������һ��һ�ĸ��֡�\n");
        set("attitude", "peaceful");
        set("str", 26);
        set("con", 30);
        set("dex", 30);
        set("int", 28);

        set("max_qi", 5200);
        set("max_jing", 2600);
        set("neili", 6000);
        set("max_neili", 6000);
        set("jiali", 80);

        set("combat_exp", 1600000);
        set("xunshan", 1);
        set("apprentice_available", 3);

        set("chat_chance_combat", 120);
        set("chat_msg_combat", ({
                (: exert_function, "powerup" :),
		(: perform_action, "sword.cimu" :),
		(: perform_action, "sword.pi" :),
                (: check_weapon :),
        }));
        set("inquiry", ([
                "Ѳɽ"     : (: do_xunshan :),
                "��ϼ��" : (: ask_zixia  :),
                "��ϼ�ؼ�" : (: ask_zixia  :),
                "�ؼ�"     : (: ask_zixia  :),
        ]));

        set_skill("unarmed", 180);
        set_skill("strike", 180);
        set_skill("sword", 220);
        set_skill("force", 220); 
        set_skill("parry", 180);
        set_skill("hunyuan-zhang", 160);
        set_skill("dodge", 220);
        set_skill("literate", 200);
        set_skill("huashan-sword", 220);
        set_skill("huashan-xinfa", 170);
        set_skill("zixia-shengong", 220);
        set_skill("huashan-quanfa", 180);
        set_skill("feiyan-huixiang", 180);

        map_skill("sword", "huashan-sword");
        map_skill("parry", "huashan-sword");
        map_skill("force", "zixia-shengong");
        map_skill("unarmed", "huashan-quanfa");
        map_skill("dodge", "feiyan-huixiang");
        map_skill("strike", "hunyuan-zhang");

        set("no_teach", ([
                "zixia-shengong" : "��������������ˣ���"
                                   "������ϼ�ؼ����Լ��ж��ɡ�",
                "pixie-jian"     : "�����������ּҵļҴ��书��"
                                   "����ô���ܻ��أ�",
        ]));

        create_family("��ɽ��", 13, "����");
        setup();

	set("book_count", 1);
        carry_object("/clone/weapon/changjian")->wield();
        carry_object("/clone/cloth/cloth")->wear();
        carry_object("/clone/misc/pin");
}

void check_weapon()
{
        if (objectp(query_temp("weapon")))
                return;

        command("wield pin");
        set("chat_msg_combat", ({
                (: exert_function, "powerup" :),
		(: perform_action, "sword.cimu" :),
		(: perform_action, "sword.pi" :),
        }));
        set("chat_chance", 120);
        set("chat_msg", ({
                (: unwield_weapon :),
        }));
}

void unwield_weapon()
{
        command("unwield pin");
        delete("chat_chance");
        delete("chat_msg");
        set("chat_msg_combat", ({
                (: exert_function, "powerup" :),
		(: perform_action, "sword.cimu" :),
		(: perform_action, "sword.pi" :),
                (: check_weapon :),
        }));
}

void attempt_apprentice(object ob)
{
        if( query("apprentice_available") ) {
                if( find_call_out("do_recruit") != -1 )
                        command("say ������һ��һ������");
                else
                        call_out("do_recruit", 2, ob);
        } else {
                command("say �Ϸ�����Ѿ������������ӣ���������ͽ�ˡ�");
        }
}

void do_recruit(object ob)
{
        if( !permit_recruit(ob) )
                return;

        if( (int)ob->query_int() < 23 )
                command("say �һ�ɽ���Խ���Ϊ�������ҿ�" +
                        RANK_D->query_respect(ob)+"���ʺ���ѧ������");

        else {
                command("say �ã��ã��ã��ܺá�");
                command("recruit " + ob->query("id") );
        }
}

int recruit_apprentice(object ob)
{
        if( ::recruit_apprentice(ob) )
        add("apprentice_availavble", -1);
}

void reset()
{
	set("book_count", 1);
        set("apprentice_available", 3);
}

int do_xunshan()
{
        object me = this_player();
      	string date;

    	date = NATURE_D->game_time();
	sscanf(date, "%s��%*s��", date);

        if (me->query_temp("xunshan"))
        {
               if (!me->query_temp("xunshan/chaoyang"))
               {
                      	message_vision("$N����$n˵���㳯����ûȥ������"
                                       "����Ѳ��ʲôɽ��\n", this_object(), me);
                        return 1;
               }
               if (!me->query_temp("xunshan/lianhua"))
               {
                      	message_vision("$N����$n˵����������ûȥ������"
                                       "����Ѳ��ʲôɽ��\n", this_object(), me);
                      	return 1;
               }
               if (!me->query_temp("xunshan/yuntai"))
               {
                      	message_vision("$N����$n˵������̨��ûȥ����������"
                                       "Ѳ��ʲôɽ��\n", this_object(), me);
                      	return 1;
               }
               if (!me->query_temp("xunshan/sheshen"))
               {
                      	message_vision("$N����$n˵������ôûȥ�����£�����"
                                       "Ѳ��ʲôɽ��\n", this_object(), me);
                      	return 1;
               }
               if (!me->query_temp("xunshan/siguo"))
               {
                      	message_vision("$N����$n˵���㵽��˼����ȥ�ˣ�����"
                                       "Ѳ��ʲôɽ��\n", this_object(), me);
                      	return 1;
               }
               if (!me->query_temp("xunshan/yunu"))
               {
                      	message_vision("$N����$n˵���㵽��Ů����滪ɽС��"
                                       "ȥ�����ˣ�����Ѳ��ʲôɽ��\n",
                                       this_object(), me);
                      	return 1;
               	}
               	message_vision("$N����$n˵�����������ˡ������ȥ"
                               "��Ϣȥ�ɡ�\n", this_object(), me);
               	me->delete_temp("xunshan");                      
               	me->add("combat_exp", 100 + random(100));
               	return 1;
        }
        else
        {
               if (query("xunshan") == date)
               {
                      	message_vision("$N����$n˵�������Ѿ�����Ѳɽ"
                                     "ȥ�ˡ������������ɡ�\n", this_object(), me);
                      	return 1;
               }
               if( me->query("family/family_name") != "��ɽ��")
               {
                      	message_vision("$N����$n���һ�������ɵ��Ӳ���"
                                     "Ѳɽ�����������ļ�ϸ��\n", this_object(), me);
                      	return 1;
               }
               if( me->query("combat_exp") > 200000)
               {
                      	message_vision("$N����$n�Ǻ�һЦ����Ӧ�ð���������"
                                     "�����ˣ�Ѳɽ�ͽ��������ĵ��Ӱɣ�\n", this_object(), me);
                      	return 1;
               }
               else
               {
                      	set("xunshan", date);
                      	message_vision("$N����$n˵�����ɵ�������Ѳɽ���㣬�ܺã���"
                                       "�ã������ȥѲɽ�ɡ�\n",
				       this_object(), me);
                      	me->set_temp("xunshan/start", 1);
                      	me->set_temp("xunshan/time", time());
                      	return 1;
               }
        }
}

string ask_zixia()
{
        mapping fam;
        object ob;
        object me;

        me = this_player();
        if( fam = me->query("family") )
        {
                if( fam["family_name"] == "��ɽ����" )
                        return "���������ǽ��ھ�ȻҲ�������������ˣ�";

                if( fam["family_name"] != "��ɽ��" )
                        return RANK_D->query_respect(me) +
                               "�뱾�ɺ��޹ϸ𣬺��������ɵ��ؼ���";
        }

        if (me->query_skill("huashan-xinfa", 1) < 100)
                return "��Ļ�ɽ�ķ���ѧ��������ӻ�Ҫʲô��ϼ�ؼ���";

        if (me->query("max_neili", 1) < 800)
                return "�������Ҳ̫���ˣ��ú���������Ҫ����ʲô��ϼ�񹦣�";

        if (query("book_count") < 1)
                return "�������ˣ������ؼ��Ѿ�����ȡ���ˡ�";

        add("book_count", -1);
        ob = new("/clone/book/zixia_book");
        ob->move(me);
        return "�ðɣ��Ȿ����ϼ�ؼ������û�ȥ�ú��ж��������ڹ�������"
               "�����������һ����";
}
