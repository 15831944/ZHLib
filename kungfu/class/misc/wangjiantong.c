// wangjiantong.c ����ͨ

#include <ansi.h>

inherit "/inherit/char/punisher";

void create()
{
        set_name("����ͨ", ({"wang jiantong", "wang", "jiantong"}));

        set("gender", "����");
        set("age", 64);
        set("long", "����̬���࣬��ò���ϡ�\n");
        set("attitude", "peaceful");
        
        set("str", 36);
        set("int", 30);
        set("con", 33);
        set("dex", 31);

        set("chat_chance_combat", 120);
        set("chat_msg_combat", ({
                (: perform_action, "strike.xianglong" :),
                (: perform_action, "staff.wugou" :),
                (: perform_action, "staff.ban" :),
                (: exert_function, "recover" :),
        }) );

        set("qi", 9999);
        set("max_qi", 9999);
        set("jing", 9999);
        set("max_jing", 9999);
        set("neili", 9999);
        set("max_neili", 9999);
        set("jiali", 300);

        set("combat_exp", 10000000);
        set("score", 10000000);

        set_skill("force", 670);
        set_skill("huntian-qigong", 670);
        set_skill("dodge", 660);
        set_skill("feiyan-zoubi", 660);
        set_skill("parry", 660);
        set_skill("staff", 670);
        set_skill("strike", 670);
        set_skill("dragon-strike", 670);
        set_skill("dagou-bang", 670);
        set_skill("begging", 600);
        set_skill("checking", 600);
        set_skill("training", 180);

        map_skill("force", "huntian-qigong");
        map_skill("dodge", "feiyan-zoubi");
        map_skill("parry", "dragon-strike");
        map_skill("staff", "dagou-bang");
        map_skill("strike", "dragon-strike");

        prepare_skill("strike", "dragon-strike");

        create_family("ؤ��", 0, "����");

        setup();
        carry_object("/clone/weapon/gangzhang")->wield();
}


