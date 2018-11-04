// li.c ����ϼ

inherit NPC;
inherit F_MASTER;

#include "emei.h"

void create()
{
        set_name("����ϼ", ({ "li mingxia","li","mingxia"}));
        set("long", "���Ƕ����ɵĵ��Ĵ��׼ҵ��ӡ�\n");
        set("gender", "Ů��");
        set("age", 23);
        set("attitude", "peaceful");
        set("shen_type", 1);
        set("class", "fighter");

        set("str", 24);
        set("int", 20);
        set("con", 21);
        set("dex", 18);

        set("max_qi", 1400);
        set("max_jing", 700);
        set("neili", 1600);
        set("max_neili", 1600);

        set("combat_exp", 70000);
        set_skill("persuading", 50);
        set_skill("throwing", 30);
        set_skill("force", 80);
        set_skill("dodge", 80);
        set_skill("finger", 85);
        set_skill("parry", 70);
        set_skill("strike", 60);
        set_skill("sword", 60);
        set_skill("jinding-zhang", 60);
        set_skill("tiangang-zhi", 85);
        set_skill("huifeng-jian", 60);
        set_skill("zhutian-bu", 80);
        set_skill("emei-xinfa", 80);
        map_skill("force","emei-xinfa");
        map_skill("finger","tiangang-zhi");
        map_skill("dodge","zhutian-bu");
        map_skill("strike","jinding-zhang");
        map_skill("sword","huifeng-jian");
        map_skill("parry","huifeng-jian");

        create_family("������", 4, "����");

        setup();
        carry_object("/clone/weapon/changjian")->wield();
        carry_object("/d/city/obj/cloth.c")->wear();
}

void attempt_apprentice(object ob)
{
        if (! permit_recruit(ob))
                return;

        command("say �ðɣ��Ҿ��������ˡ�");
        command("recruit " + ob->query("id"));
}
