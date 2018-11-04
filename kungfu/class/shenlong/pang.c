// pang.c
#include <ansi.h>

inherit NPC;
inherit F_UNIQUE;
inherit F_QUESTER;

void create()
{
        set_name("��ͷ��", ({ "pang toutuo", "pang" ,"toutuo"}));
        set("title", "�������󻤷�");
        set("nickname","�ɶ�������");
        set("long", "��ͷ�������ߣ������ݵó��棻����Ƥ����ͷ��˫\n"
                    "Ŀ���ݣ�������罩ʬһ�㡣\n" );
        set("gender", "����");
        set("age", 44);

        set("str", 32);
        set("int", 28);
        set("con", 31);
        set("dex", 25);

        set("max_qi", 4700);
        set("qi", 4700);
        set("max_jing", 2400);
        set("jing", 2400);
        set("neili", 4800); 
        set("max_neili", 4800);
        set("jiali", 60);

        set("combat_exp", 750000);
        set("shen_type", -1);
        set("attitude", "peaceful");

        set_skill("force", 160);
        set_skill("hand", 160);
        set_skill("strike", 160);
        set_skill("staff", 160);
        set_skill("parry", 160);
        set_skill("dodge", 160);
        set_skill("yixingbu", 160);
        set_skill("shenlong-bashi", 160);
        set_skill("huagu-mianzhang", 160);
        set_skill("shenlong-xinfa", 160);
        set_skill("shedao-qigong", 160);

        map_skill("staff", "shedao-qigong");
        map_skill("force", "shenlong-xinfa");
        map_skill("hand", "shenlong-bashi");
        map_skill("strike", "huagu-mianzhang");
        map_skill("parry", "shedao-qigong");
        map_skill("dodge", "yixingbu");
        prepare_skill("hand", "shenlong-bashi");
        prepare_skill("strike", "huagu-mianzhang");

        create_family("������", 0, "��ɢ����");

        set("inquiry", ([
                "������" : "һ�������벻���������̵�(join shenlongjiao).\n",
                "���"   : "һ�������벻���������̵�(join shenlongjiao).\n",
                "�鰲ͨ" : "����Ƣ������,Ҫ�������Ĳźá�\n",
                "����"   : "����Ƣ������,Ҫ�������Ĳźá�\n",
                "�ں�"   : "���겻�ϣ������ɸ����������룡������ʥ��",
        ]));
        setup();
        carry_object("/clone/misc/cloth")->wear();
        add_money("silver", 10);
}

void attempt_apprentice(object ob)
{
        command("say �����������������ʦȥ�ҽ����ɡ�");
}

