// laoseng.c ������

#include <ansi.h>

inherit "/inherit/char/punisher";

void create()
{
        set_name("������", ({ "lao lama", "lama" }));
        set("long",  "����һ������ܴ��������ϵ����Ķ��Ѿ��ƾɲ��������Ǿ�˵���ǵ������������ʦ��\n");
        set("gender", "����");
        set("age", 65);
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

        set_skill("force", 660);
        set_skill("longxiang", 660);
        set_skill("mizong-neigong", 660);
        set_skill("dodge", 710);
        set_skill("shenkong-xing", 710);
        set_skill("cuff", 640);
        set_skill("yujiamu-quan", 640);
        set_skill("hand", 650);
        set_skill("dashou-yin", 650);
        set_skill("parry", 650);
        set_skill("staff", 720);
        set_skill("xiangmo-chu", 720);
        set_skill("necromancy", 650);
        set_skill("lamaism", 710);
        set_skill("literate", 700);
        set_skill("hammer", 670);
        set_skill("riyue-lun", 670);
        set_skill("strike",670);
        set_skill("huoyan-dao",650);

        map_skill("force", "longxiang");
        map_skill("dodge", "shenkong-xing");
        map_skill("cuff", "yujiamu-quan");
        map_skill("hand", "dashou-yin");
        map_skill("parry", "riyue-lun");
        map_skill("staff", "xiangmo-chu");
        map_skill("hammer", "riyue-lun");
        map_skill("strike","huoyan-dao");

        prepare_skill("strike", "huoyan-dao");

        create_family("ѩɽ��", 0, "���");

        setup();
        carry_object("/clone/weapon/falun")->set_amount(4);
        carry_object("/clone/weapon/falun")->wield();
        carry_object("/d/xueshan/obj/p-jiasha")->wear();
        carry_object("/d/xueshan/obj/sengmao")->wear();
}


