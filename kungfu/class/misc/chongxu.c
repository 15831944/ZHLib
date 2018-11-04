// chongxu.c ����

#include <ansi.h>

inherit "/inherit/char/punisher";

void create()
{
        set_name("����", ({ "chong xu", "xu" }));
        set("long",  "�������䵱�ɵĸ��ֳ����������ò��Ȼ��ƮƮ���ɡ�\n");
        set("gender", "����");
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

        set_skill("cuff",670);
        set_skill("force", 680);
        set_skill("wudang-xinfa", 680);
        set_skill("taiji-shengong", 680);
        set_skill("dodge", 660);
        set_skill("tiyunzong", 660);
        set_skill("unarmed", 670);
        set_skill("taiji-quan", 670);
        set_skill("strike", 670);
        set_skill("wudang-zhang", 670);
        set_skill("hand", 670);
        set_skill("paiyun-shou", 670);
        set_skill("parry", 670);
        set_skill("sword", 670);
        set_skill("wudang-jian", 670);
        set_skill("taiji-jian", 670);
        set_skill("taoism", 660);
        set_skill("literate", 600);
        set_skill("medical", 660);
        set_skill("liandan-shu", 660);

        map_skill("force", "taiji-shengong");
        map_skill("dodge", "tiyunzong");
        map_skill("cuff", "taiji-quan");
        map_skill("parry", "taiji-quan");
        map_skill("sword", "taiji-jian");
        map_skill("strike", "wudang-zhang");

        prepare_skill("cuff", "taiji-quan");
        prepare_skill("strike", "wudang-zhang");
        prepare_skill("hand","paiyun-shou");

        create_family("�䵱��", 0, "����");

        set("chat_chance_combat", 120);
        set("chat_msg_combat", ({
                (: perform_action, "sword.chan" :),
                (: perform_action, "sword.lian" :),
                (: perform_action, "sword.sui" :),
                (: exert_function, "recover" :),
        }));

        setup();
        carry_object("/clone/weapon/changjian")->wield();
        carry_object("/d/wudang/obj/whiterobe")->wear();
}


