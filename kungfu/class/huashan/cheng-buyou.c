// cheng-buyou.c  �ɲ���
inherit NPC;
#include <ansi.h>

mixed ask_me();
void create()
{
        set_name("�ɲ���", ({ "cheng buyou", "cheng" }) );
        set("gender", "����");
        set("class", "swordsman");
        set("title", "��ɽ���ڵ�ʮ��������");
        set("age", 41);
        set("long",
                "һ���׾���Ƥ�İ��ӣ���Ҳ����С������\n");
        set("attitude", "peaceful");
        set("str", 26);
        set("int", 24);
        set("con", 23);
        set("dex", 27);

        set("max_qi", 2800);
        set("max_jing",1400);
        set("neili", 3600);
        set("max_neili", 3600);
        set("jiali", 45);

        set("combat_exp", 850000);
        set("shen_type", -1);
        set("apprentice_available", 3);

        set("chat_chance_combat", 80);
        set("chat_msg_combat", ({
                (: perform_action, "sword.feilong" :),
                (: exert_function, "recover" :),
        }) );

        set_skill("unarmed", 80);
        set_skill("sword", 150);
        set_skill("force", 100);
        set_skill("parry", 130);
        set_skill("dodge", 130);
        set_skill("literate", 50);
        set_skill("huashan-sword", 150);
        set_skill("huashan-xinfa", 100);
        set_skill("huashan-quanfa", 80);
        set_skill("huashan-shenfa", 130);

        map_skill("sword", "huashan-sword");
        map_skill("parry", "huashan-sword");
        map_skill("force", "huashan-neigong");
        map_skill("unarmed", "huashan-quanfa");
        map_skill("dodge", "huashan-shenfa");

        set("inquiry", ([
                "����"   : (: ask_me :),
                "����"   : (: ask_me :),
                "�����������ɽ�" : (: ask_me :),
        ]));

        create_family("��ɽ����", 13, "����");
        setup();

        carry_object("/clone/weapon/changjian")->wield();
        carry_object("/clone/cloth/cloth")->wear();
}

void attempt_apprentice(object ob)
{
        command("say �Ϸ�Ӳ���ͽ������������ɡ�");
}

mixed ask_me()
{
        object me;

        me = this_player();
        if (me->query("can_perform/huashan-sword/duoming"))
                return "�㻹����ȥ��ϰ�书�����ҽ��ڵľ��������ڷ�ɣ�";

        if (me->query("family/family_name") != "��ɽ��")
                return RANK_D->query_respect(me) + "�������ǻ�ɽ�ɵ��ˣ����߰ɣ�";

        if (me->query_skill("huashan-sword", 1) < 150)
                return "��Ļ�ɽ�����������ң���Ҫ�ٸ��Ҷ����ˣ�";

        message_vision(HIY "$n" HIY "˳�ּ���һ��С��֦������"
                       "���ٻ����������ƿ�֮�������ڶ���\n"
                       HIY "$n" HIY "��ͷ������$N" HIY "������һ"
                       "��ûʲôϡ�棬����Ҫ��������������������"
                       "��Ȼ��ɽӦ�����ڽ�����������ҲҪ�ú�����������\n" NOR,
                       me, this_object());
        tell_object(me, HIG "��ѧ���˶����������ɽ���\n" NOR);
        if (me->can_improve_skill("sword"))
                me->improve_skill("sword", 90000);
        me->set("can_perform/huashan-sword/duoming", 1);
        return 1;
}