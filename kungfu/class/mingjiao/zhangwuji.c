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
    set_name("���޼�", ({ "zhang wuji", "zhang", "wuji" }));
    set("long", @LONG
���̽������޼ɣ�ͳ������ʮ����ڣ��������ƣ�߳��ǧ�
�������񹦡�����Ǭ����Ų�ơ��������£��ǽ����в�������
����Ӣ�ۡ�
LONG );
    set("title",HIG "����" HIM " ����" NOR);
    set("gender", "����");
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

    set("inherit_title",HIG"����"HIY"����ʹ��"NOR);

    create_family("����", 33, "����");

    set("chat_chance",2);
    set("chat_msg",({
        "���޼ɷ�Ȼ˵�������ɷ��Թ�Ϊ��, ����ɳ��, ��Ԫ��ҵδ��, ͬ������Ŭ��!��\n",
        "���޼�̾��������ʧһ֪��, ����λ�, �������, ����, ��������?��\n",
        "���޼ɵ����ҽ��ֵ�����: ��������, ���˼�Ϊ��, ��������, ������ħ!��\n",
    }));

    set("inquiry",([
	  "����" :     "���������������ʲô����\n",
          "��ëʨ��" : "�������常л������ְ˾��\n",
          "лѷ" :     "���������常�Ĵ�š�\n",
          "�Ŵ�ɽ" :   "�������Ҹ���������? \n",
          "������" :   "����������������΢������\n",
          "������" :   "��̫ʦ�������ɺ�? \n",
          "����" :     "����ʧһ֪��, ����λ�, �������, ����, ��������?\n",
          "С��" :     "С���ҿ�һֱ�������ĺô���\n",
          "������" :   "������ȥ����ɽ, �������ҡ�\n",
          "������"      : (: ask_ling :),
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
		command("say ħ����������ѧ������������Ȱ������������"
		        "���سɷ�");
	} else
	if((int)ob->query("shen") < -100)
	{
		command("say ��λ���ѣ����н��������е����������߽�аħ�����");
	} else
	if((int)ob->query("shen") >= 0)
	{
		command("say �������������ߣ�Ȱ����ӱ��ء�");
	} else
	if((int)ob->query("shen") > 50000)
	{
		command("say �������ϣ����޼�һ�񣬴������ձ�Ϊ�����̳���");
	}
	return;
}

int accept_fight(object ob)
{
    	if ((ob->query("combat_exp") < 30000) && (ob->query("shen") > 0))
    	{
        	message_vision("�������������ǿ���ݣ��㲻���ҵĶ��֣�"
			       "��ȥ�ɡ�\n",ob);
        	return 0;
    	}
    	message_vision("���޼�һ����˵������λ" + RANK_D->query_respect(ob) +
		       "����������ˡ�\n", ob);
    	return 1;
}

string ask_ling()
{
	mapping family, skl; 
	string *sname;
	object ob;
	int i;
	
	if ( !(family = this_player()->query("family")) || family["family_name"] != "����")
		return RANK_D->query_respect(this_player()) + "�뱾��������������֪�˻��Ӻ�̸��";

	skl = this_player()->query_skills();
	sname  = sort_array( keys(skl), (: strcmp :) );

	for(i=0; i<sizeof(skl); i++) 
	{
		if (skl[sname[i]] < 30) 
		return RANK_D->query_respect(this_player()) + 
		"����������������ȡ�����";
	}

	ob = new("d/mingjiao/obj/tieyanling");
	ob->move(this_player());
	message_vision("$NҪ��һ�������\n",this_player());

	return "�ðɣ�ƾ�������������������������ս��";

}

void attempt_apprentice(object ob)
{
	object me  = this_object();
	mapping ob_fam;
	mapping my_fam  = me->query("family");

	string name, new_name;

        if (!(ob_fam = ob->query("family")) || ob_fam["family_name"] != "����")
	{
                command("say " + RANK_D->query_respect(ob) + "�뱾��������������֪�˻��Ӻ�̸��");
		return;
	}

	if ( ob_fam["generation"] > my_fam["generation"] + 2)
	{
                command("say " + RANK_D->query_respect(ob) + "������ȥ�ҽ��������ֵܺú�ѧѧ�书�ɡ�");
		return;
	}

	if ( ob->query("combat_exp") < 1000000 )
	{
		command("say ��ľ���̫�٣��ú���ȥ���������������ɱ�������̶����� !");
		return;
	}

        command("say �����ã�������������һλ�������֣����ǿ�ϲ�ɺ� !");

        command("say ��ϲ������Ϊ���̹���ʹ�ߣ�");
        command("recruit " + ob->query("id"));

	return;
}
