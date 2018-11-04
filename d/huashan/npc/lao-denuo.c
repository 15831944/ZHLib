// lao-denuo.c

inherit NPC;
inherit F_GUARDER;

int permit_pass(object me, string dir);

void create()
{
        set_name("�͵�ŵ", ({ "lao denuo","lao","denuo" }) );
        set("nickname", "�Ϻ���");
        set("gender", "����");
        set("age", 61);
        set("long", "�͵�ŵ������Ⱥ�Ķ����ӡ�\n");
        set("attitude", "peaceful");

        set("str", 26);
        set("con", 30);
        set("int", 24);
        set("dex", 30);

        set("max_qi", 3400);
        set("max_jing", 1700);
        set("neili", 2800);
        set("max_neili", 2800);

        set("combat_exp", 150000);
        set("shen_type", -1);
        set("score", 5000);

        set("chat_chance_combat", 80);
        set("chat_msg_combat", ({
                (: exert_function, "powerup" :),
                (: exert_function, "recover" :)
        }) );

        set_skill("unarmed", 95);
        set_skill("sword", 95);
        set_skill("force", 95);
        set_skill("parry", 95);
        set_skill("dodge", 95);
        set_skill("literate", 40);

        set_skill("huashan-sword", 95);
        set_skill("huashan-xinfa", 95);
        set_skill("huashan-quanfa", 95);
        set_skill("feiyan-huixiang", 95);

        map_skill("sword", "huashan-sword");
        map_skill("parry", "huashan-sword");
        map_skill("force", "huashan-xinfa");
        map_skill("unarmed", "huashan-quanfa");
        map_skill("dodge", "feiyan-huixiang");

        set_temp("apply/damage", 100);
        set_temp("apply/armor", 100);

        set("apply/dodge", 100);

        set("coagents", ({
                ([ "startroom" : "/d/huashan/qunxianguan",
                   "id"        : "yue buqun" ]),
        }));

        create_family("��ɽ��", 14, "����");
        setup();

        carry_object("/clone/weapon/changjian")->wield();
        carry_object("/clone/cloth/cloth")->wear();
}

int permit_pass(object me, string dir)
{
        object *inv;
        int i;

        if (! living(this_object()))
                return 1;

        if (me->query("family/family_name") == "��ɽ����" &&
            dir == "southup")
        {
                message_vision("$NȰ������ʦ�н���������إ����"
                               "ǰ���뿪��ɽ�ˣ����ϲ��ǻ�ɽ�����ˡ�\n"
                               "�������Ϻ��ˣ���λ" + RANK_D->query_respect(me) +
                               "������ذɡ�\n", this_object());
                return notify_fail("�͵�ŵ���������ȥ��\n");
        }


        notify_fail("����" + name() + "�����������ȥ��\n");

        inv = all_inventory(me);
        for (i = 0; i < sizeof(inv); i++)
        {
                if (! userp(inv[i])) continue;
                if ((string) inv[i]->query("family/family_name") != "��ɽ��")
                {
                        message_vision("$N��$n�ȵ����㱳����˭�����������£�\n",
                                       this_object(), me);
                        return 0;
                }
        }

        if ( me->query("family/family_name") &&
             me->query("family/family_name") != "��ɽ��" ||
             ! me->query("family/family_name") &&
             me->query("combat_exp") > 20000)
        {
                message_vision("$N��$n�����Բ��𣬲������ǻ�ɽ�ɵ���"
                               "�����뱾���صء�\n", this_object(), me);
                return 0;
        }

        return 1;
}
