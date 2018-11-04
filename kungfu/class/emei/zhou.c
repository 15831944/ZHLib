// zhou.c ������

inherit NPC;
inherit F_MASTER;

#include <command.h>
#include <ansi.h>
#include "emei.h"

mixed ask_me();

void create()
{
        set_name("������", ({ "zhou zhiruo","zhiruo","zhou"}));
        set("long",
                "���Ƕ����ɵĵ��Ĵ����ŵ��ӡ�\n"
                "һ�����������ס�����һ�������ѡ�\n"
                "�����������Ц�д���Щ�����Ρ�\n"
                "���ܼ�į��\n");
        set("gender", "Ů��");
        set("age", 20);
        set("attitude", "peaceful");
        set("shen_type", 1);
        set("chat_chance_combat", 60);
        set("chat_msg_combat", ({
                (: perform_action, "sword.mie" :),
        }) );
        set("inquiry",([
                "���"    : "������ȣ����԰ɡ�",
                "����"    : "Ҫ�������ҵ�ʦ����ȥ��",
                "����"    : "���ġ�����Ҳ���ң�",
                "���޼�"  : "������Ķ����ļһ����Ҳ��Ҫ������",
                "����"    : "��Ҫ���������ӣ�",
                "���콣"  : "���첻����˭�����棿����",
                "������"  : "�������ֳ��ۣ��������ˡ�",
                "���ʦ̫"  : "ʦ���ѵ���ͽ�����Ȱͽ��Ұɡ�",
		"������צ": (: ask_me :),
        ]));
        set("str", 22);
        set("int", 32);
        set("con", 26);
        set("dex", 24);

        set("max_qi", 3800);
        set("max_jing", 1900);
        set("neili", 4400);
        set("max_neili", 4400);
        set("jingli", 1200);
        set("max_jingli", 1200);

        set("combat_exp", 1250000);
        set_skill("persuading", 120);
        set_skill("force", 170);
        set_skill("throwing", 150);
        set_skill("dodge", 180);
        set_skill("finger", 140);
        set_skill("parry", 170);
        set_skill("unarmed", 130);
        set_skill("strike", 145);
        set_skill("sword", 170);
        set_skill("claw", 170);
        set_skill("cuixin-zhang", 170);
        set_skill("literate", 120);
        set_skill("mahayana", 140);
        set_skill("jinding-zhang", 145);
        set_skill("jiuyin-baiguzhao", 170);
        set_skill("tiangang-zhi", 140);
        set_skill("huifeng-jian", 170);
        set_skill("yinlong-bian", 200);
        set_skill("whip", 200);
        set_skill("zhutian-bu", 150);
        set_skill("emei-xinfa", 180);
        set_skill("linji-zhuang", 170);
        map_skill("force","linji-zhuang");
        map_skill("whip","yinlong-bian");
        map_skill("claw","jiuyin-baiguzhao");
        map_skill("dodge","zhutian-bu");
        map_skill("strike","cuixin-zhang");
        map_skill("sword","huifeng-jian");
        map_skill("parry","huifeng-jian");
        prepare_skill("claw","jiuyin-baiguzhao");
        prepare_skill("strike","cuixin-zhang");
        create_family("������", 4, "���ŵ���");

        set("no_teach", ([
                "linji-zhuang" : "��ѧ�ټ�ʮ��ׯ�������ʦ̫ȥ��",
                "jiuyin-baiguzhao" : "��������������Ц�����ˡ�",
        ]));

        setup();
        carry_object("/clone/weapon/changjian")->wield();
        carry_object("/d/emei/obj/ycloth.c")->wear();
}

void attempt_apprentice(object ob)
{
        if (! permit_recruit(ob))
                return;

        if ((int)ob->query_int() < 30 )
        {
                command("say ��λ"+RANK_D->query_respect(ob)+"�������ʲ���һ�㡣");
                command("say �����д���Ǳ���������Ȼ�ȥĥ��ĥ����");
                return ;
        }

        command("say " + ob->query("name") + "������ô��������Ϊ����������ɡ�\n");
        command("recruit " + ob->query("id"));
}

mixed ask_me()
{
        object me;

        me = this_player();
        if (me->query("can_perform/jiuyin-baiguzhao/shenzhao"))
                return "�㻹����ȥ�úõ���ϰһ�¾����׹�צ��";

        if (me->query("family/family_name") != "������")
                return RANK_D->query_respect(me) + "�������Ƕ����ɵ��ˣ����߰ɣ�";

        if (me->query_skill("jiuyin-baiguzhao", 1) < 150)
                return "��ľ����׹�צ��ô�������ҿ���Ц�ˣ�";

        message_vision(HIY "$n" HIY "��ɫһ�������ֳ�צ�ηɻ�������"
                       "�ƿ�֮�������ڶ���˿˿���ι���ͷ����\n"
                       HIY "$n" HIY "��ͷ������$N" HIY "������һ"
                       "��ûʲôϡ�棬����Ҫ�ĺ�������\n" NOR,
                       me, this_object());
        tell_object(me, HIG "��ѧ���˾�����צ��\n" NOR);
        me->set("can_perform/jiuyin-baiguzhao/shenzhao", 1);
        return 1;
}

