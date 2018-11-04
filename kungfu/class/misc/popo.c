// popo.c ����

#include <ansi.h>

inherit "/inherit/char/punisher";

void create()
{
        set_name("����", ({ "po po", "po" }));
        set("long",  "����һ���������ϸ��ˣ���ɫ���飬��������ȴ�������䡣\n");
        set("gender", "Ů��");
        set("age", 66);
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

        set_skill("force", 680);
        set_skill("nuhai-kuangtao", 680);
        set_skill("sword", 670);
        set_skill("xuantie-jian", 670);
        set_skill("yunv-jian", 670);
        set_skill("quanzhen-jian", 670);
        set_skill("dodge", 660);
        set_skill("yunv-shenfa", 660);
        set_skill("parry", 670);
        set_skill("cuff",660);
        set_skill("meinv-quan", 660);
        set_skill("strike",660);
        set_skill("sad-strike", 660);
        set_skill("literate", 680);
        set_skill("taoism", 640);
        set_skill("medical", 670);
        set_skill("yunv-xinjing", 670);
        set_skill("throwing", 660);
        set_skill("yufeng-zhen", 660);

        map_skill("force", "nuhai-kuangtao");
        map_skill("sword", "xuantie-jian");
        map_skill("dodge", "yunv-shenfa");
        map_skill("parry", "xuantie-jian");
        map_skill("cuff", "meinv-quan");
        map_skill("strike", "sad-strike");

        prepare_skill("strike", "sad-strike");

        create_family("��Ĺ��", 0, "Ԫ��");

        setup();
        carry_object("/clone/weapon/gangjian")->wield();
        carry_object("/clone/cloth/qingyi")->wear();
}


