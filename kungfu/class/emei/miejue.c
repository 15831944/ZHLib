// miejue.c ���ʦ̫
// Modified by That Oct.1997

inherit NPC;
inherit F_MASTER;
inherit F_QUESTER;
inherit F_COAGENT;

#include <ansi.h>
#include "emei.h"

string ask_for_quit();
string ask_me();

void create()
{
        set_name("���ʦ̫", ({ "miejue shitai","miejue","shitai"}));
        set("long", "���Ƕ����ɵĵ��������ӣ����ζ����������ˡ�\n");
        set("gender", "Ů��");
        set("age", 62);
        set("attitude", "peaceful");
        set("shen_type", 1);
        set("no_get", 1);
        set("class", "bonze");
        set("chat_chance_combat", 60);
        set("chat_msg_combat", ({
                (: perform_action, "sword.mie" :),
        }) );
        set("inquiry",([
                "�ؼ�"  :  (: ask_me :),
                "���"  : "Ҫ����Ҿ�����",
                "����"  : "Ҫ����Ҿ�����",
                "����"  :  (: ask_for_quit :),
        ]));

        set("str", 29);
        set("int", 35);
        set("con", 31);
        set("dex", 30);

        set("max_qi", 4500);
        set("max_jing", 2200);
        set("neili", 6000);
        set("max_neili", 6000);
        set("jingli", 1200);
        set("max_jingli", 1200);

        set("combat_exp", 1850000);
        set_skill("persuading", 160);
        set_skill("throwing", 210);
        set_skill("force", 220);
        set_skill("dodge", 200);
        set_skill("finger", 190);
        set_skill("parry", 220);
        set_skill("strike", 190);
        set_skill("sword", 220);
        set_skill("blade", 200);
        set_skill("literate", 120);
        set_skill("mahayana", 220);
        set_skill("buddhism", 300);
        set_skill("jinding-zhang", 240);
        set_skill("tiangang-zhi", 190);
        set_skill("huifeng-jian", 220);
              set_skill("yitian-jian", 250);
            set_skill("yanxing-dao", 200);
        set_skill("zhutian-bu", 200);
        set_skill("emei-xinfa", 220);
        set_skill("linji-zhuang", 220);

        map_skill("force","linji-zhuang");
        map_skill("finger","tiangang-zhi");
        map_skill("dodge","zhutian-bu");
        map_skill("strike","jinding-zhang");
        map_skill("sword","huifeng-jian");
        map_skill("blade","yanxing-dao");
        map_skill("parry","huifeng-jian");
        create_family("������", 3, "������");

        setup();

	set_temp("apply/attack", 80);
	set_temp("apply/defense", 80);
	set_temp("apply/damage", 100);
	set_temp("apply/armor", 100);
       set("book_count",1);

        carry_object("/clone/weapon/changjian")->wield();
        carry_object("/d/city/obj/cloth.c")->wear();
}

void attempt_apprentice(object ob)
{
	string name,new_name;

        if (! permit_recruit(ob))
                return;

        if ((int)ob->query("shen") < 15000)
        {
                command("say " + RANK_D->query_respect(ob) +
                        "������������֮������̫�٣�ʵ����̫�٣�");
                return;
        }

        if ((int)ob->query_skill("mahayana",1) < 100)
        {
                command("say ���˷𷨵���Ϊ�����С�");
                return;
        }

        if ((int)ob->query_skill("emei-xinfa",1) < 100)
        {
                command("say ��ô���£������ڹ��ķ�����ôѧ�ģ�"
                        "�úø�����ȥ��");
                return;
        }

        command("say �ðɣ��Ҿ��������ˡ�");
        command("say �Ժ���Ҫ��Ϊʦһ���������µĶ���ͳͳɱ�⣡��");
        name = ob->query("purename");
        if (! name) name = ob->query("name");
	new_name = "��" + name[0..1];
        command("say �ӽ��Ժ���ķ�������" + new_name + "��");       	ob->set("name", new_name);
        command("recruit " + ob->query("id"));
}

string ask_for_quit()
{
        object me;
        mapping myfam;
        me = this_player();

        myfam = (mapping)me->query("family");
        if (!myfam || (myfam["family_name"] != "������")) 
                return ("����ʲô�ˣ��ܵ����������ң�\n");

        if( (string)me->query("class") != "bonze" )
                return "�����ӷ��㱾���׼��ˣ���̸���ף�\n";

        me->set_temp("pending/quit_bonze", 1);
        command ("heng");
        command ("say ���ף��ã���������Ƕ����ɣ��ұ������㻹��ȥ�ɣ�\n");
        return "��úõĸ��Ұ����������Ժ�����ħ�������������Ӳ�������\n";
}

string ask_me()
{
 	object ob;
 	 	if (this_player()->query("family/master_id")!="miejue shitai")
 		return RANK_D->query_respect(this_player()) +
  		"���ҵ��ӣ���֪�˻��Ӻ�̸��";
 	if (query("book_count") < 1)
 		return "�������ˣ����ɵ��ؼ����ڴ˴���";
 	add("book_count", -1);
 	ob = new("/d/emei/obj/fojing");
 	ob->move(this_player());
 	return "�ðɣ��Ȿ��"+ob->name()+"�����û�ȥ�ú����С�";
} 

void reset()
{
	set("book_count",1);
}
