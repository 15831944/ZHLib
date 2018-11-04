// huyidao.c ��һ��

#include <ansi.h>

inherit "/inherit/char/punisher";

void create()
{
        set_name("��һ��", ({ "hu yidao", "yidao" }));
        set("long",  "����������һ�����ݴ������Ѿ������쵶���磬���˼�����𣬺�����ǧ��\n");
        set("gender", "����");
        set("age", 65);
        set("attitude", "peaceful");
        set("shen_type", 1);
        set("str", 32);
        set("int", 33);
        set("con", 32);
        set("dex", 31);
        
        set("max_qi", 9999);
        set("max_jing", 9999);
        set("neili", 9999);
        set("max_neili", 9999);
        set("jiali", 300);
        set("combat_exp", 10000000);
        set("score", 10000000);

    set_skill("force", 710);            // �����ڹ�
    set_skill("lengyue-shengong", 710); // ������
    set_skill("blade", 640);            // ��������
    set_skill("hujia-daofa", 640);      // ���ҵ���
    set_skill("dodge", 640);            // ��������
    set_skill("taxue-wuhen", 640);      // ̤ѩ�޺�
    set_skill("parry", 620);            // �����м�
    set_skill("throwing", 640);         // ��������
    set_skill("mantian-xing", 640);     // ������
    set_skill("strike", 680);           // �����Ʒ�
    set_skill("tianchang-zhang", 680);  // �쳤�Ʒ�
    set_skill("cuff", 680);             // ����ȭ��
    set_skill("hujia-quan", 680);       // ����ȭ��

    map_skill("force", "lengyue-shengong");
    map_skill("blade", "hujia-daofa");
    map_skill("dodge", "taxue-wuhen");
    map_skill("parry", "hujia-daofa");
    map_skill("throwing", "mantian-xing");
    map_skill("strike", "tianchang-zhang");
    map_skill("cuff", "hujia-quan");

    prepare_skill("strike", "tianchang-zhang");
    prepare_skill("cuff",   "hujia-quan");

    create_family("�������", 0, "����");

    setup();
    carry_object("/d/guanwai/obj/lengyue")->wield();
    carry_object("/clone/cloth/cloth")->wear();
}


