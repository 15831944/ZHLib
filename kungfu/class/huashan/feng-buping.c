// feng-buping.c  �ⲻƽ

inherit NPC;

#include <ansi.h>
#include "jianzong.h"

mixed ask_me();

void create()
{
        set_name("�ⲻƽ", ({ "feng buping", "feng" }) );
        set("nickname", YEL"���콣"NOR);
        set("gender", "����");
        set("class", "swordsman");
        set("title", "��ɽ���ڵ�ʮ��������");
        set("age", 45);
        set("long",
                "�ⲻƽ�ǻ�ɽ���ڵ�һ���֣���������һ�Żƽ�������Ƥ��\n");
        set("attitude", "peaceful");
        set("str", 28);
        set("int", 32);
        set("con", 31);
        set("dex", 29);

        set("max_qi", 4700);
        set("max_jing", 2400);
        set("neili", 5000);
        set("max_neili", 5000);
        set("jiali", 50);

        set("combat_exp", 1800000);
        set("shen_type", -1);
        set("apprentice_available", 3);

        set("chat_chance_combat", 80);
        set("chat_msg_combat", ({
                (: perform_action, "sword.feilong" :),
                (: exert_function, "recover" :),
        }) );

        set_skill("unarmed", 180);
        set_skill("sword", 220);
        set_skill("force", 180);
        set_skill("parry", 200);
        set_skill("strike", 180);
        set_skill("dodge", 190);
        set_skill("literate", 100);
        set_skill("huashan-sword", 220);
        set_skill("kuangfeng-jian", 220);
        set_skill("huashan-xinfa", 180);
        set_skill("huashan-quanfa", 180);
        set_skill("huashan-zhangfa", 180);
        set_skill("huashan-shenfa", 190);

        map_skill("sword", "kuangfeng-jian");
        map_skill("parry", "kuangfeng-jian");
        map_skill("force", "huashan-neigong");
        map_skill("unarmed", "huashan-quanfa");
        map_skill("strike", "huashan-zhangfa");
        map_skill("dodge", "huashan-shenfa");

        set("inquiry", ([
                "����"   : (: ask_me :),
                "����"   : (: ask_me :),
                "�������" : (: ask_me :),
        ]));

        create_family("��ɽ����", 13, "����");
        setup();

        carry_object("/clone/weapon/changjian")->wield();
        carry_object("/clone/cloth/cloth")->wear();
}

mixed ask_me()
{
        object me;

        me = this_player();
        if (me->query("can_perform/huashan-sword/feilong"))
                return "�㻹����ȥ��ϰ�书�����ҽ��ڵľ��������ڷ�ɣ�";

        if (me->query("family/family_name") != "��ɽ��")
                return RANK_D->query_respect(me) + "�������ǻ�ɽ�ɵ��ˣ����߰ɣ�";

        if (me->query_skill("huashan-sword", 1) < 150)
                return "��Ļ�ɽ�����������ң���Ҫ�ٸ��Ҷ����ˣ�";

        message_vision(HIY "$n" HIY "���һ��������ճ��һ��ʯ��"
                       "�����������������ͻȻ������ĩ��\n"
                       HIY "$n" HIY "��ͷ������$N" HIY "������һ"
                       "��ûʲôϡ�棬����Ҫ��������������������"
                        "��Ȼ��ɽӦ�����ڽ�����������ҲҪ�ú�����������\n" NOR,
                       me, this_object());
        tell_object(me, HIG "��ѧ�������������\n" NOR);
        if (me->can_improve_skill("sword"))
                me->improve_skill("sword", 90000);
        me->set("can_perform/huashan-sword/feilong", 1);
        return 1;
}

void attempt_apprentice(object ob)
{
        command("say �Ϸ���Ҫ������Ǳ����������Ҫ��ʦ������������ɣ�");
	return;
}