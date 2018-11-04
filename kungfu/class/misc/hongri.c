// hongri.c ��������

#include <ansi.h>

inherit "/inherit/char/punisher";

void create()
{
        set_name("��������", ({ "hongri zunzhe", "hongri", "zunzhe" }));
        set("long",  "�����Ǻպ������ĺ������ߣ�����Ѫ�������ʦ�����պ��д�Į��ħ����\n");
        set("gender", "����");
        set("age", 65);
        set("attitude", "peaceful");
        set("shen_type", 0);
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

        set_skill("lamaism", 620);
        set_skill("literate", 280);
        set_skill("force", 630);
        set_skill("parry", 620);
        set_skill("blade", 625);
        set_skill("xue-dao", 625);
        set_skill("sword", 680);
        set_skill("mingwang-jian", 680);
        set_skill("dodge", 710);
        set_skill("mizong-neigong", 630);
        set_skill("xuehai-mogong", 630);
        set_skill("shenkong-xing", 710);
        set_skill("hand", 700);
        set_skill("dashou-yin",700);
        set_skill("cuff", 700);
        set_skill("yujiamu-quan", 700);

        map_skill("force", "xuehai-mogong");
        map_skill("dodge", "shenkong-xing");
        map_skill("hand", "dashou-yin");
        map_skill("cuff", "yujiamu-quan");
        map_skill("parry", "xue-dao");
        map_skill("blade", "xue-dao");
        map_skill("sword", "mingwang-jian");

        prepare_skill("cuff", "yujiamu-quan");
        prepare_skill("hand", "dashou-yin");

        create_family("Ѫ����", 0, "ħ��");

        setup();
        carry_object("/d/xueshan/obj/y-jiasha")->wear();
        carry_object("/d/xueshan/obj/xblade")->wield();
}


