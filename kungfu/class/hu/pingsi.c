// pingsi.c
#include <ansi.h>;

inherit NPC;
inherit F_MASTER;

void create()
{
    set_name("ƽ��", ({"ping si", "ping"}));
    set("gender", "����");
    set("age", 65);
    set("long", "���Ǻ������Ĺ��������ۡ�\n");
    set("attitude", "peaceful");
    set("str", 20);
    set("int", 20);
    set("con", 24);
    set("dex", 20);

    set("qi", 4000);
    set("max_qi", 4000);
    set("jing", 1000);
    set("max_jing", 1000);
    set("neili", 3000);
    set("max_neili", 3000);
    set("combat_exp", 150000);

    set_skill("force", 100);            // �����ڹ�
    set_skill("lengyue-shengong", 100); // ������
    set_skill("blade", 100);            // ��������
    set_skill("zijinbagua-dao", 80);      // ���ҵ���
    set_skill("dodge", 100);            // ��������
    set_skill("taxue-wuhen", 100);      // ̤ѩ�޺�
    set_skill("parry", 100);            // �����м�
    set_skill("strike", 100);           // �����Ʒ�
    set_skill("tianchang-zhang", 100);  // �쳤�Ʒ�
    set_skill("cuff", 100);             // ����ȭ��
    set_skill("hujia-quan", 100);       // ����ȭ��

    map_skill("force", "lengyue-shengong");
    map_skill("blade", "zijinbagua-dao");
    map_skill("dodge", "taxue-wuhen");
    map_skill("parry", "zijinbagua-dao");
    map_skill("strike", "tianchang-zhang");
    map_skill("cuff", "hujia-quan");

    prepare_skill("strike", "tianchang-zhang");
    prepare_skill("cuff",   "hujia-quan");

    create_family("�������", 8, "����");

    set("inquiry",([
        "�ֻ�":     "�ֻ�... ���������\n",
        "��һ��":   "�ǣ����������ˣ�����\n",
        "���˷�":   "������ɲ��ǻ��ˡ�\n",
        "�԰�ɽ":   "�����Ҽ����˵Ľ�������û��˵�ġ� \n",
    ]));

    setup();

    set("title", "������Ӷ");
    carry_object("/clone/cloth/cloth")->wear();
}

void attempt_apprentice(object ob)
{
    object me;

    me = this_object();

    if (ob->query("detach/�������") ||
        ob->query("betrayer/times"))
    {
        message_vision("$Nҡҡͷ��$n˵���㷴���޳����Ҳ�������Ϊͽ��\n",
                       me, ob);
        return;
    }

    if( ob->query("born_family") != "�������" && 
        ob->query("can_not_change") &&
        !ob->query("tianmo_jieti/times") )
    {

        message_vision("$N��$n�����㲻�����Ǻ��ҵ��ˣ�����������Ϊͽ��\n",
                       me, ob);
        return 0;

    }


    if (ob->query("family/family_name") &&
        ob->query("family/family_name") != me->query("family/family_name"))
    {
        message_vision("$N��$n��������Ȼ�Ǻ��ҵ��ˣ����������������ɣ��Ҳ�������Ϊͽ��\n",
                       me, ob);
        return;
    }

    if (ob->query("purename") == "һ��")
    {
        message_vision("$N��ŭ����ȡ���������ʲô��˼��\n", me);
        return;
    }

    if (ob->query("purename") == "�")
    {
        message_vision("$N��ŭ�������̵ģ���ȡ���������ʲô��˼��\n", me);
        return;
    }

    message_vision("$N��̾�������Ǻ��һ�Ҫ������������������\n",
                   me, ob);
    command("recruit " + ob->query("id"));
    return;
}

