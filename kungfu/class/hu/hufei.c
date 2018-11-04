// hufei.c

#include <ansi.h>;

inherit NPC;
inherit F_MASTER;
inherit F_COAGENT;
inherit F_QUESTER;

string ask_me();
string ask_book();
string ask_hujia_book();

void create()
{
    set_name("���", ({"hu fei", "hu", "fei"}));
    set("gender", "����");
    set("nickname", "ѩɽ��"HIG"��"NOR);
    set("age", 25);
    set("long", @LONG
�����Ǻ�һ��֮�ӣ������书��ǿ�����û���ڽ�����������š�ѩɽ�ɺ�����
����һ����ɫ�������������һ�ѿ������ܾɵĵ���������ף�����������
һͷŨ����ȴ����衣
LONG);
    set("attitude", "peaceful");
    set("str", 45);
    set("int", 30);
    set("con", 30);
    set("dex", 30);
    set("chat_chance", 10);
    set("chat_msg", ({
        "���̾�˿�����������֪ʲôʱ�����ټ����������\n",
        "����гݺ޵������ֻ����������¶����ұ����д�ⲣ���\n",
    }));

    set("qi", 4200);
    set("max_qi", 4200);
    set("jing", 2100);
    set("max_jing", 2100);
    set("neili", 5800);
    set("max_neili", 5800);
    set("jiali", 80);
    set("combat_exp", 2300000);
    set("score", 20000);
     
    set_skill("force", 210);            // �����ڹ�
    set_skill("lengyue-shengong", 210); // ������
    set_skill("blade", 240);            // ��������
    set_skill("hujia-daofa", 240);      // ���ҵ���
    set_skill("dodge", 240);            // ��������
    set_skill("taxue-wuhen", 240);      // ̤ѩ�޺�
    set_skill("parry", 220);            // �����м�
    set_skill("throwing", 240);         // ��������
    set_skill("mantian-xing", 240);     // ������
    set_skill("strike", 180);           // �����Ʒ�
    set_skill("tianchang-zhang", 180);  // �쳤�Ʒ�
    set_skill("cuff", 180);             // ����ȭ��
    set_skill("hujia-quan", 180);       // ����ȭ��
    set_skill("literate", 180);       // ����д��
    map_skill("force", "lengyue-shengong");
    map_skill("blade", "hujia-daofa");
    map_skill("dodge", "taxue-wuhen");
    map_skill("parry", "hujia-daofa");
    map_skill("throwing", "mantian-xing");
    map_skill("strike", "tianchang-zhang");
    map_skill("cuff", "hujia-quan");

    prepare_skill("strike", "tianchang-zhang");
    prepare_skill("cuff",   "hujia-quan");

    create_family("�������", 7, "����");

    set("inquiry",([
        "����":     (: ask_me :),
        "����":     (: ask_book :),
        "���ҵ���": (: ask_book :),
        "�ܾ�":     (: ask_hujia_book :),
        "�����ܾ�": (: ask_hujia_book :),
        "�ֻ�":     "�ֻ���������ҷ�ɱ�������ɡ�\n",
        "��һ��":   "�ɶ�������һ�����ҵ��������Ҵ�û��������\n",
        "���˷�":   "���˷�ͼҸ����������ɳ�Ϊ֪�����ѣ�Ȼ���Ҹ�ȴ�������Ľ��¡�\n",
        "������":   "��֪ʲôʱ�����ټ����������\n",
        "����":     "��֪ʲôʱ�����ټ����������\n",
        "��������": "��֪ʲôʱ�����ټ����������\n",
        "������":   "������Ҳ��֪���������ֻ����������˵������Ҫȥ������\n",
        "�԰�ɽ":   "�������簡�����������⿴���ء� \n",
        "Ԭ����":   "���ˣ��������������ˡ�\n"
    ]));

    set("baodao_count", 1);
    set("book_count", 1);
    set("hujia_book_count", 1);

    set_temp("apply/damage", 50);
    set_temp("apply/armor", 100);
    set_temp("apply/attack", 40);
    set_temp("apply/dodge", 40);
    set_temp("apply/parry", 40);

    setup();
    carry_object("/d/guanwai/obj/lengyue")->wield();
    carry_object("/clone/cloth/cloth")->wear();
}

string ask_me()
{
    object ob, me;

    me = this_player();
    if (me->query("family/family_name") !=
        query("family/family_name"))
    {
        command("shake");
        return "������������̸��Щ�¡�\n";
    }

    if ((int)me->query("shen") < 0)
    {
        command("sigh");
        return "����������а·���ܻ��Һ���һ��������\n";
    }

    if ((int)me->query("combat_exp") < 100000)
        return "����Ŀǰ�ı��컹����ʹ�ô���������\n";

    if ((int)me->query("shen") < 100000)
        return "����Ŀǰ������������ʹ�ô���������\n";

    if ((int)query("baodao_count") > 0)
    {       
        add("baodao_count", -1);
        ob = new ("/d/guanwai/obj/cwbdao");
        ob->move(me);
        return " �ðɣ���Ѵ�������������ȥ�ã�ϣ����ú���������\n";
    }
    else
        return "�������ˣ�������ѵ��Ѳ��ڴ˴���\n";
}

string ask_book()
{
    object ob, me;

    me = this_player();
    if (me->query("family/family_name") !=
        query("family/family_name"))
    {
        command("shake");
        return "������������̸��Щ�¡�\n";
    }

    if ((int)me->query("shen") < 0)
    {
        command("sigh");
        return "����������а·���ܻ��Һ���һ��������\n";
    }

    if ((int)me->query("combat_exp") < 5000)
        return "���Ⱥú�ѧϰ�书����������Ȼ�ύ���㡣\n";

    if ((int)query("book_count") > 0)
    {       
        add("book_count", -1);
        ob = new ("/clone/book/blade-book");
        ob->move(me);
        return " �ðɣ��Ȿ���ҵ�������ȥ�����ж��ɡ�\n";
    }
    else
        return "�������ˣ����ڵ����Ѳ��ڴ˴���\n";
}

string ask_hujia_book()
{
    object ob, me;

    me = this_player();
    if (me->query("family/family_name") !=
        query("family/family_name"))
    {
        command("shake");
        return "������������̸��Щ�¡�\n";
    }

    if ((int)me->query("shen") < 0)
    {
        command("sigh");
        return "����������а·���ܻ��Һ���һ��������\n";
    }

    if ((int)me->query("combat_exp") < 50000)
        return "����书̫��������书��˵��\n";

    if ((int)me->query_skill("blade", 1) < 40)
        return "�����ڵ����Ϻú����¹���Ȼ�����ж������ܾ����١�\n";

    if ((int)me->query_skill("hujia-daofa", 1) < 40)
        return "�����ں��ҵ����Ϻú����¹���Ȼ�����ж������ܾ����١�\n";

    if ((int)query("hujia_book_count") > 0)
    {       
        add("hujia_book_count", -1);
        ob = new ("/clone/book/hujia-book");
        ob->move(me);
        return " �ðɣ��Ȿ�����ܾ�����ȥ�����ж��ɡ�\n";
    }
    else
        return "�������ˣ����ڵ����ܾ��Ѳ��ڴ˴���\n";
}

void attempt_apprentice(object ob)
{
    object me;

    me = this_object();
    if (ob->query("name") == "��һ��")
    {
        message_vision("$N��ŭ���Ҳ٣��������ҵ����Ӱ���\n", me);
        return;
    }

    if (ob->query("name") == "���")
    {
        message_vision("$N��ŭ�������̵ģ���զҲ��������֣�\n", me);
        return;
    }

    if (ob->query("born_family") != "�������")
    {
        message_vision("$N��$n�����㲻�����Ǻ��ҵ��ˣ�����������Ϊͽ��\n",
                       me, ob);
        return;
    }

    if (ob->query("detach/�������") ||
        ob->query("betrayer/times"))
    {
        message_vision("$Nҡҡͷ��$n˵���㷴���޳����Ҳ�������Ϊͽ��\n",
                       me, ob);
        return;
    }

    if (ob->query("family/family_name") &&
        ob->query("family/family_name") != me->query("family/family_name"))
    {
        message_vision("$N��$n��������Ȼ�Ǻ��ҵ��ˣ����������������ɣ��Ҳ�������Ϊͽ��\n",
                       me, ob);
        return;
    }

    message_vision("$N��̾�������Ǻ��һ�Ҫ������������������\n",
                   me, ob);
    command("recruit " + ob->query("id"));
    return;
}
