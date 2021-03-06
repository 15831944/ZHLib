// /kungfu/class/xueshan/jiumozhi.c 鸠摩智
// by secret

inherit NPC;
inherit F_MASTER;
inherit F_QUESTER;

#include <ansi.h>
#include "xueshan.h"


void create()
{
        set_name("鸠摩智", ({ "jiumo zhi", "zhi" ,"ming wang"}));
        set("nickname", HIG "大轮明王" NOR);
        set("long",@LONG
他就是雪山寺的掌门，人称大轮明王的鸠摩智。他对佛法有精深的研究。
身穿一件大红袈裟，头戴僧帽。
LONG
        );
        set("title","雪山寺掌门");
        set("gender", "男性");
        set("age", 60);
        set("attitude", "friendly");
        set("shen_type", -1);

        set("str", 32);
        set("int", 40);
        set("con", 31);
        set("dex", 31);

        set("max_qi", 5800);
        set("max_jing", 2900);
        set("neili", 7100);
        set("max_neili", 7100);
        set("jiali", 100);
        set("combat_exp", 2500000);

        set_skill("force", 270);
        set_skill("xiaowuxiang", 270);
        set_skill("mizong-neigong", 270);
        set_skill("dodge", 240);
        set_skill("shenkong-xing", 240);
        set_skill("necromancy", 250);
        set_skill("parry", 270);
        set_skill("sword", 220);
        set_skill("mingwang-jian", 220);
        set_skill("lamaism", 250);
        set_skill("literate", 220);
        set_skill("strike", 270 );
        set_skill("huoyan-dao", 270);
        set_skill("cuff", 260);
        set_skill("yujiamu-quan", 260);
        set_skill("hand", 270);
        set_skill("dashou-yin", 270);

        map_skill("force", "xiaowuxiang");
        map_skill("dodge", "shenkong-xing");
        map_skill("parry", "mingwang-jian");
        map_skill("sword", "mingwang-jian");
        map_skill("strike","huoyan-dao");
        map_skill("cuff", "yujiamu-quan");

        prepare_skill("strike", "huoyan-dao");
        prepare_skill("hand", "dashou-yin");

        create_family("雪山寺", 1, "掌门");
        set("class", "bonze");
        setup();

        carry_object("/clone/weapon/changjian")->wield();
        carry_object("/d/xueshan/obj/r-jiasha")->wear();
        carry_object("/d/xueshan/obj/sengmao")->wear();

        add_money("silver",50);
}

void attempt_apprentice(object ob)
{
        if (! permit_recruit(ob))
                return;
 
        if ((string)ob->query("gender") != "男性")
        {
                command("say 修习密宗内功需要纯阳之体。");
                command("say 这位" + RANK_D->query_respect(ob) +
                        "还是请回吧！");
                return;
        }

        if ((string)ob->query("class") != "bonze")
        {
                command("say 我佛门的清规戒律甚多。");
                command("say 这位" + RANK_D->query_respect(ob) +
                        "还是请回吧！");
                return;
        }

       if ((string)ob->query("family/family_name") != "雪山寺" && (string)ob->query("family/family_name") != "血刀门"  )
        {
                command("say 这位" + RANK_D->query_respect(ob) +
                        "既非我密宗弟子，还是请回吧！");
                return;
        }

        if ((int)ob->query_skill("lamaism", 1) < 150) {
                command("say 入我雪山寺，修习密宗心法是首要的。");
                command("say 这位" + RANK_D->query_respect(ob) +
                        "是否还应该多多钻研本门的心法？");
                return;
        }

        command("recruit " + ob->query("id"));
        ob->set("title", HIY "法王" NOR);
}


