// guoxiang.c

#include <ansi.h>

inherit "/inherit/char/punisher";

void create()
{
        set_name("����", ({ "guo xiang", "guo" }));
        set("long", "���Ƕ����ɵĿ�ɽ��ʦ��\n");
        set("nickname", HIM "С��а" NOR);
        set("gender", "Ů��");
        set("age", 24);
        set("attitude", "peaceful");
        set("shen_type", 1);
        set("class", "bonze");

        set("chat_chance_combat", 120);
        set("chat_msg_combat", ({
                (: perform_action, "sword.mie" :),
                (: perform_action, "strike.bashi" :),
                (: exert_function, "recover" :),
        }));

        set("str", 29);
        set("int", 39);
        set("con", 37);
        set("dex", 37);

        set("max_qi", 9999);
        set("max_jing", 9999);
        set("neili", 9999);
        set("max_neili", 9999);
        set("jingli", 300);

        set("combat_exp", 10000000);
        set("score", 10000000);

        set_skill("force", 670);
        set_skill("dodge", 670);
        set_skill("finger", 670);
        set_skill("parry", 670);
        set_skill("strike", 670);
        set_skill("sword", 670);
        set_skill("literate", 660);
        set_skill("mahayana", 660);
        set_skill("buddhism", 660);
        set_skill("jinding-zhang", 670);
        set_skill("tiangang-zhi", 670);
        set_skill("huifeng-jian", 670);
        set_skill("zhutian-bu", 670);
        set_skill("emei-xinfa", 670);
        set_skill("linji-zhuang", 670);

        map_skill("force","linji-zhuang");
        map_skill("finger","tiangang-zhi");
        map_skill("dodge","zhutian-bu");
        map_skill("strike","jinding-zhang");
        map_skill("sword","huifeng-jian");
        map_skill("parry","huifeng-jian");

        create_family("������", 1, "��ɽ��ʦ");

        setup();

        carry_object("/clone/weapon/changjian")->wield();
        carry_object("/d/city/obj/cloth.c")->wear();
}


