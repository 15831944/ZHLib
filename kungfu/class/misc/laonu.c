// laonu.c ��ū

#include <ansi.h>

inherit "/inherit/char/punisher";

void create()
{
        set_name("��ū", ({ "lao nu", "laonu" }));
        set("long",  "������ȥ�׷��Բԣ�һ�����˴�磬������������ӡ�\n");
        set("gender", "����");
        set("age", 72);
        set("attitude", "peaceful");
        set("shen_type", 1);
        set("str", 32);
        set("int", 33);
        set("con", 38);
        set("dex", 32);
        
        set("max_qi", 6000);
        set("max_jing", 3000);
        set("neili", 7600);
        set("max_neili", 7600);
        set("jiali", 160);
        set("combat_exp", 2600000);
        set("score", 10000000);

        set_skill("force", 670);
        set_skill("strike", 660);
        set_skill("dodge", 660);
        set_skill("parry", 670);
        set_skill("cuff", 660);
        set_skill("finger", 640);
        set_skill("staff", 670);
        set_skill("training", 670);
        set_skill("poison", 670);
        set_skill("shedu-qiqiao", 670);
        set_skill("hamagong", 670);
        set_skill("chanchu-bufa", 660);
        set_skill("lingshe-quan", 660);
        set_skill("lingshe-zhangfa", 670);
        set_skill("baibian-daxue", 660);
        set_skill("guzheng-jifa", 600);
        set_skill("xiyu-tiezheng", 600);
        set_skill("medical", 680);
        set_skill("baituo-michuan", 680);

        map_skill("force", "hamagong");
        map_skill("dodge", "chanchu-bufa");
        map_skill("cuff",  "lingshe-quan");
        map_skill("parry", "lingshe-zhangfa");
        map_skill("staff", "lingshe-zhangfa");
        map_skill("finger", "shedu-qiqiao");
        map_skill("poison", "shedu-qiqiao");
        map_skill("guzheng-jifa", "xiyu-tiezheng");
	map_skill("strike", "hamagong");

        prepare_skill("strike", "hamagong");

        create_family("ŷ������", 0, "��ū");

        set("chat_chance_combat", 120);
        set("chat_msg_combat", ({
                (: perform_action, "staff.chan" :),
                (: perform_action, "staff.qianshe" :),
                (: perform_action, "staff.wuji" :),
                (: perform_action, "cuff.rou" :),
                (: exert_function, "recover" :),
        }));

        setup();
        carry_object("/clone/misc/cloth")->wear();
}
