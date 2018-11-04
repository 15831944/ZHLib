//NPC /npc/shizhe.c

inherit NPC;
#include <ansi.h>

void greeting(object);
void init();

void create()
{
        set_name("����ʹ��", ( { "shi zhe", "zhe" }) );
        set("gender", "����" );
        set("age", 30);
        set("long",
              "���Ǹ����Ż��µ���ʮ���꺺�ӣ��ֳ�ľ�������ޱ��顣\n"
             );
        set("attitude", "friendly");
        set("shen_type", 1);

        set("str", 30);
        set("int", 39);
        set("con", 30);
        set("dex", 30);

        set("max_qi", 330);
        set("max_jing", 320);
        set("neili", 300);
        set("max_neili", 300);

        set("combat_exp", 16000);
        set("score", 10000);

        set_skill("force", 50);
        set_skill("dodge", 50);
        set_skill("unarmed", 50);
        set_skill("parry", 50);
        set_temp("apply/attack", 50);
        set_temp("apply/defense", 50);
        set_temp("apply/damage", 50);
        set_temp("apply/armor", 50);

        set_temp("ling",0);
        set_temp("times",5);
        create_family("���͵�", 2, "����");

        set("inquiry", ([
                "����"   : "�ϱ߻��м��Ҵ������Լ�����ȥ�ɣ�\n",
        ]));
        setup();
}

void init()
{
        object ob;

        ::init();

        if( interactive(ob = this_player()) && !is_fighting() )
        {
                remove_call_out("greeting");
                call_out("greeting", 1, ob);
        }
}

void greeting(object ob)
{

        if( !ob || environment(ob) != environment() ) return;
        say("����ʹ��˵������λ" + RANK_D->query_respect(ob)
                + "����ҽй�������ʲô�������͵����ڽ������ء�\n");
             return;
}
