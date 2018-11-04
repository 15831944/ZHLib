// fangsheng.c

inherit "/inherit/char/punisher";

void create()
{
        set_name("����", ({ "fang sheng", "fang" }));
        set("long", "����Ŀ�Ⱥͣ���Ȼ��һ�õ���ɮ��\n");

        set("gender", "����");
        set("attitude", "friendly");
        set("class", "bonze");

        set("age", 40);
        set("shen_type", 1);
        set("str", 36);
        set("int", 31);
        set("con", 37);
        set("dex", 32);
        set("max_qi", 9999);
        set("max_jing", 9999);
        set("neili", 9999);
        set("max_neili", 9999);
        set("jiali", 300);
        set("combat_exp", 10000000);
        set("score", 10000000);

        set_skill("force", 670);
        set_skill("yijinjing", 670);
        set_skill("dodge", 660);
        set_skill("shaolin-shenfa", 660);
        set_skill("finger", 670);
        set_skill("strike", 670);
        set_skill("hand", 660);
        set_skill("claw", 660);
        set_skill("parry", 660);
        set_skill("nianhua-zhi", 670);
        set_skill("sanhua-zhang", 670);
        set_skill("fengyun-shou", 660);
        set_skill("longzhua-gong", 660);
        set_skill("buddhism", 660);
        set_skill("literate", 620);
	set_skill("whip", 620);
	set_skill("riyue-bian",620);

        map_skill("force", "yijinjing");
        map_skill("dodge", "shaolin-shenfa");
        map_skill("finger", "nianhua-zhi");
        map_skill("strike", "sanhua-zhang");
        map_skill("hand", "fengyun-shou");
        map_skill("claw", "longzhua-gong");
        map_skill("parry", "nianhua-zhi");
	map_skill("whip", "riyue-bian",620);

        prepare_skill("finger", "nianhua-zhi");
        prepare_skill("strike", "sanhua-zhang");

        create_family("������", 0, "��ɮ");

        set("chat_chance_combat", 120);
        set("chat_msg_combat", ({
                (: perform_action, "strike.san" :),
                (: perform_action, "hand.qinna" :),
                (: perform_action, "claw.zhua" :),
                (: exert_function, "recover" :),
        }));

        setup();
        carry_object("/clone/weapon/changbian")->wield();
        carry_object("/d/shaolin/obj/xuan-cloth")->wear();
}


