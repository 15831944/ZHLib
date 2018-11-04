// murenqing.c

#include <ansi.h>

inherit "/inherit/char/punisher";

void create()
{
        set_name("������", ({ "mu renqing", "mu", "renqing" }));
        set("title", HIY "ȭ����˫" NOR);

        set("gender", "����");
        set("attitude", "peaceful");
        set("shen_type", 1);

        set("age", 66);

        set("str", 33);
        set("int", 36);
        set("con", 31);
        set("dex", 34);

        set("qi", 9999);
        set("max_qi", 9999);
        set("jing", 9999);
        set("max_jing", 9999);
        set("neili", 9999);
        set("max_neili", 9999);
        set("jiali", 300);

        set("combat_exp", 10000000);
        set("score", 10000000);

        set_skill("cuff", 670);
        set_skill("force", 670);
        set_skill("sword", 680);
        set_skill("dodge", 680);
        set_skill("parry", 670);
        set_skill("strike", 670);
        set_skill("zixia-shengong", 670);
        set_skill("poyu-quan", 670);
        set_skill("huashan-sword", 680);
        set_skill("hunyuan-zhang", 670);
        set_skill("feiyan-huixiang",680);
        set_skill("literate", 620);

        map_skill("cuff", "poyu-quan");
        map_skill("force", "zixia-shengong");
        map_skill("dodge", "feiyan-huixiang");
        map_skill("parry", "huashan-sword");
        map_skill("sword", "huashan-sword");
        map_skill("strike", "hunyuan-zhang");

        prepare_skill("strike", "hunyuan-zhang");
        prepare_skill("cuff", "poyu-quan");

        create_family("��ɽ��", 18, "����");

        set("chat_chance_combat", 120);
        set("chat_msg_combat", ({
                (: perform_action, "strike.wuji" :),
                (: perform_action, "cuff.poshi" :),
                (: perform_action, "sword.jianzhang" :),
                (: exert_function, "recover" :),
        }));

        setup();
        carry_object("/clone/misc/cloth")->wear();
        carry_object("/clone/weapon/changjian")->wield();
}


