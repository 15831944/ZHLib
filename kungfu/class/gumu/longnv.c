// longnv.c С��Ů
// 1998.9 by Lgg

inherit NPC;
inherit F_MASTER;
inherit F_QUESTER;

#include <ansi.h>
#include "gumu.h"

string ask_yunv();
string ask_me();
string ask_zhen();

void create()
{
        set_name("С��Ů", ({"long nv", "long"}));
        set("gender", "Ů��");
        set("age", 27);
        set("long",
                "��һ���������£���������������ѩ���������֮�������䣬\n"
                "ʵ��������������¡������ݡ�\n");
        set("attitude", "friendly");

        set("str", 21);
        set("int", 30);
        set("con", 25);
        set("dex", 26);
        set("per",29);

        set("chat_chance_combat", 15);
        set("chat_msg_combat", ({
                (: exert_function, "recover" :),
                (: perform_action, "sword.he" :),
                (: perform_action, "sword.he" :),
                (: perform_action, "sword.ding" :),
                (: perform_action, "sword.ding" :),
        }) );

        set("chat_chance", 1);
        set("chat_msg", ({
                "С��Ů�૵�������Ů����ȫ�潣�ϱڣ��ǿ������޵С�����...����ȥ����һ�����أ���\n",
                "С��Ů�����̾�˿�����ת��ͷȥ��\n",
        }));

        set("qi", 3800);
        set("max_qi", 3800);
        set("jing", 1900);
        set("max_jing", 1900);
        set("neili", 4400);
        set("max_neili", 4400);
        set("jiali", 50);

        set("combat_exp", 1600000);
        set("score", 0);

        set_skill("force", 180);
        set_skill("yunv-xinfa", 180);
        set_skill("sword", 180);
        set_skill("yunv-jian", 180);
        set_skill("quanzhen-jian",170);
        set_skill("dodge", 180);
        set_skill("yunv-shenfa", 180);
        set_skill("parry", 180);
        set_skill("cuff", 160);
        set_skill("meinv-quan", 160);
        set_skill("strike", 160);
        set_skill("fireice-strike", 160);
            set_skill("hand", 180);
            set_skill("tianluo-diwang", 180);
        set_skill("literate", 130);
        set_skill("qufeng", 210);
	set_skill("medical", 200);
	set_skill("yunv-xinjing", 500);
        set_skill("throwing", 200);
        set_skill("yufeng-zhen", 200);

        map_skill("force", "yunv-xinfa");
        map_skill("sword", "yunv-jian");
        map_skill("dodge", "yunv-shenfa");
        map_skill("parry", "meinv-quan");
        map_skill("hand", "tianluo-diwang");
        map_skill("cuff", "meinv-quan");
        map_skill("strike", "fireice-strike");
        map_skill("throwing", "yufeng-zhen");

        prepare_skill("cuff", "meinv-quan");
        prepare_skill("strike", "fireice-strike");

        create_family("��Ĺ��", 3, "����");

        set("book_count", 1);
        set("count", 1);
        set("yfzhen_count", 3);

        set("inquiry", ([
                "����" : "��������������",
		"��"   : (: ask_me :),
                "��Ů����" : "��Ů������ȫ�潣���ϱڣ������޵У�\n",
                "��Ĺ��" : "�ҵ�����ʦүү������������ʦ��һ����ˣ�����...\n",
                "��Ů�ľ�" : (: ask_yunv :),
                "�����" : (: ask_zhen :),
        ]) );

        set("env/wimpy", 40);
        setup();

        carry_object("/d/gumu/npc/obj/shunvjian")->wield();
        carry_object("/clone/cloth/baipao")->wear();

}

void attempt_apprentice(object ob)
{
        if (! permit_recruit(ob) )
                return;

	if (ob->query("per") < 25)
	{
        	command("say ����ʵ�ڲ��ҹ�ά���ҿ��㻹�����˰ɡ�\n");
                return;
	}

        command("say �ðɣ��Ҿ����������ͽ���ˡ�\n");
	command("recruit " + ob->query("id"));
}

string ask_yunv()
{
        object me;
        object ob;
        mapping fam;

        me = this_player();
        if (! (fam = me->query("family")) ||
            fam["family_name"] != "��Ĺ��")
                return RANK_D->query_respect(me) +
                "�뱾�ɺ��޹ϸ𣬺��������ɵ��ľ���";

        if (this_player()->query_skill("yunv-xinfa", 1) < 15)
                return RANK_D->query_respect(me) +
                        "����Ů�ķ����̫ǳ���Ҳ��ܽ���Ů�ľ������㡣";

        if (query("book_count") < 1)
                return "�������ˣ����ɵ���Ů�ľ��Ѿ�����ȡ���ˡ�";

        add("book_count", -1);
        ob = new("/clone/book/yunvjing1");
        ob->move(me, 1);
        return "�ðɣ��Ȿ����Ů�ľ��������ˣ���Ҫ�úÿ�����";
}

string ask_me()
{
        object ob;

        if (query("count") < 1)
                return "��������ͷҲû���ˡ�";

        add("count", -1);
        ob=new("/d/gumu/npc/obj/junzijian");
        ob->move(this_player(), 1);
        return "������ӽ����͸���ɡ�";
}

string ask_zhen()
{
        object me;
        object ob;
        mapping fam;

        me = this_player();
        if (! (fam = me->query("family")) ||
            fam["family_name"] != "��Ĺ��")
                return RANK_D->query_respect(me) +
                "�뱾�ɺ��޹ϸ𣬺��������ɰ�����";

        if (me->query_skill("yufeng-zhen", 1) < 50)
                return RANK_D->query_respect(me) +
                        "��������ַ���򻹲����ң����������Ҳû��ʲô�á�";

        if (query("yfzhen_count") < 1)
                return "�������ˣ�����ͷ��������Ѿ������ˡ�";

        add("yfzhen_count", -1);
        ob = new("/d/gumu/obj/yfzhen");
        message_vision("$N�ó�һЩ�����ݸ�$n��\n", this_object(), me);
        ob->move(me, 1);
        return "�ðɣ���Щ�����������ȥ�ðɡ�";
}

void reset()
{
	set("book_count", 1);
        set("yfzhen_count", 2 + random(2));
}
