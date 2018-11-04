// tonglao.c

#include <ansi.h>

inherit "/inherit/char/punisher";

void create()
{
        set_name("��ɽͯ��", ({ "tonglao", "lao" }));
        set("long", @LONG
������ȥֻ��һ��СС�ĺ�ͯ��������ò��Ȼ���ϡ�
LONG );
        set("gender", "Ů��");
        set("age", 96);
        set("attitude", "peaceful");

        set("str", 36);
        set("int", 31);
        set("con", 46);
        set("dex", 33);

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
        set_skill("dodge", 670);
        set_skill("parry", 670);
        set_skill("hand", 670);
        set_skill("strike", 670);

        set_skill("zhemei-shou", 670);
        set_skill("liuyang-zhang", 670);
        set_skill("yueying-wubu", 670);
        set_skill("bahuang-gong", 670);

        map_skill("force", "bahuang-gong");
        map_skill("strike", "liuyang-zhang");
        map_skill("dodge", "yueying-wubu");
        map_skill("hand", "zhemei-shou");
        map_skill("parry", "liuyang-zhang");

        prepare_skill("hand","zhemei-shou");
        prepare_skill("strike","liuyang-zhang");        

        set("chat_chance_combat", 120);
        set("chat_msg_combat", ({
                (: perform_action, "hand.jiubu" :),
                (: perform_action, "strike.jiutian" :),
                (: exert_function, "recover" :),
        }));

        create_family("���չ�", 0, "����");
        setup();
        carry_object("/d/lingjiu/obj/changpao")->wear();
}


