//xuemuh.c ѦĽ��
// shilling 97.2

inherit NPC;
inherit F_MASTER;

#include "xiaoyao.h"

int ask_me();

void create()
{
	set_name("ѦĽ��", ({ "xue muhua", "xue" }));
	set("long", 
		"�����Ǻų������е���ҽ����ѦĽ������˵����ͨҽ����������������\n");
	set("gender", "����");
	set("title","��ң�ɡ����Ȱ��ѡ�");
	set("nickname","������Ѧ��ҽ");
	set("age", 50);
	set("class", "shaman");
	set("attitude", "peaceful");
	set("str", 25);
	set("int", 27);
	set("con", 25);
	set("dex", 25);

	set("inquiry", ([
		"����" : (:ask_me:),
	]));

	set("max_qi", 1900);
	set("max_jing", 800);
	set("neili", 3100);
	set("max_neili", 3100);
	set("jiali", 60);
	set("combat_exp", 120000);

	set_skill("force", 90);
	set_skill("dodge", 90);
	set_skill("strike",90);
	set_skill("parry", 90);
	set_skill("feiyan-zoubi",80);
	set_skill("xiaoyao-xinfa", 80);
	set_skill("liuyang-zhang", 80);
	set_skill("medical", 150);
        set_skill("literate",120);
	set_skill("xiaoyao-qixue", 150);

	map_skill("strike", "liuyang-zhang");
	map_skill("dodge", "feiyan-zoubi");
	map_skill("force", "xiaoyao-xinfa");

	prepare_skill("strike", "liuyang-zhang");

	create_family("��ң��", 3, "����");
	setup();
	carry_object("/clone/cloth/cloth")->wear();
}

void attempt_apprentice(object ob)
{
        if (! permit_recruit(ob))
                return;

        if (ob->query_int() < 26)
        {
                command("sigh");
                command("say ��Ȼ��˵���ܲ�׾������... �ҿ��㻹���߰ɡ�");
                return;
        }

	command("say �ðɣ��Ҿ��������ˣ��Ժ�Ҫ��Ϊ��ң�ɳ�������");
	command("recruit " + ob->query("id"));
}

int ask_me()
{
	object ob;
	ob=this_player();

	if (ob->query("family/family_name") != "��ң��")
		return notify_fail("�㲻�����ɵ��ӣ��Ҳ�����Ϊ�����ˡ�\n");
	if ((int)ob->query("eff_qi") == (int)ob->query("max_qi"))
	{
		command("?"+ob->query("id"));     
		command("say ��û�����κ��˰���\n");
		return 1;
	}
	else
	{
		message_vision("ѦĽ��ι$N����һ��ҩ��,Ȼ����ϥ���£�˫������$N�ı��ġ�\n", ob);
		remove_call_out("recover");
		call_out("recover",2,ob);
		return 1;
	}
}

int recover(object ob)
{
	ob->set("eff_qi", (int)ob->query("max_qi"));
	ob->set("eff_jing", (int)ob->query("max_jing"));  
	message_vision("��Լ����һ�Ѳ��ʱ�ݣ�ѦĽ��������վ��������\n",ob);
	command("say ��������Ѿ�ȫ����,����������\n");
	return 1;
}
