
inherit NPC;

#include <ansi.h>
int auto_perform();
int ask_me();
int do_qiecuo();

void create()
{
set_name("达而巴", ({ "darba", "dar", "ba" }));
        set("long",
"他是金轮法王的二弟子，已得法王五、六分真传，兼天生神力，一身外门功夫 \n"
"甚是了得，虽身形高瘦，却使一根长达四尺的纯金降魔杵。\n");
        
        set("inquiry",([
               "引见"  : (: ask_me :),
                "金轮法王" : (: ask_me :),
        ]));

        set("title", HIY "活佛" NOR);
        set("gender", "男性");
        set("age", 45);
        set("attitude", "heroism");
        set("shen_type", -1);
        set("str", 26);
        set("int", 19);
        set("con", 22);
        set("dex", 21);
        set("max_qi", 3200);
        set("max_jing", 1600);
        set("neili", 3400);
        set("max_neili", 3400);
        set("jiali", 50);
        set("combat_exp", 270000);

        set_skill("lamaism", 80);
        set_skill("necromancy", 80);
        set_skill("literate", 80);
        set_skill("force", 150);
        set_skill("mizong-neigong", 150);
        set_skill("dodge", 100);
        set_skill("shenkong-xing", 100);
        set_skill("cuff", 140);
        set_skill("yujiamu-quan", 140);
        set_skill("parry", 140);
        set_skill("staff", 120);
        set_skill("xiangmo-chu", 120);

        map_skill("force", "mizong-neigong");
        map_skill("dodge", "shenkong-xing");
        map_skill("cuff", "yujiamu-quan");
        map_skill("parry", "mingwang-jian");
        map_skill("staff", "xiangmo-chu");

        prepare_skill("cuff", "yujiamu-quan");

        create_family("雪山寺", 3, "活佛");
        set("class", "bonze");
        setup();
        carry_object("/d/xueshan/obj/lamajiasha")->wear();
        if (clonep()) carry_object("/clone/weapon/xiangmo-chu");
//      if (ob = carry_object("/d/qilian/obj/xiangmo-chu")) //ob->wield();
}

/*void init()
{
        ::init();
        add_action("do_qiecuo", "qiecuo");
}
*/
int ask_me()
{
        if( this_player()->query("family/family_name") != "雪山寺"
        && this_player()->query("family/family_name") != "血刀门")
        return 0;

        if( !present("xiangmo chu", this_object())){
        say("达尔巴摇了摇头：今天没力气跟你说了，你明天再来问我吧。\n");
        return 1;
        }

        if( this_player()->query("jlfw")){
        say("达尔巴说道：师兄要找师父再问我可没用。\n");
        return 1;
        }

        say(
"达尔巴看了" + this_player()->name() + "一眼不屑地说：想找我师父，得先过我\n"
"这一关，这位" + RANK_D->query_respect(this_player()) + "是不是先和我切搓一下？\n");
        this_player()->set_temp("marks/引1", 1);
        return 1;
}

int accept_fight()
{
        object me, ob;

        me = this_object();
        ob = this_player();

        if( ob->query_temp("marks/引1") 
        && present("xiangmo chu", me)) {
        say(ob->name() + "对达而巴说：好吧，那" 
             "我就同你切搓几招吧，点到为止。\n");
          command("wield chu");
          me->set_temp("challenger", ob);
          ob->set_temp("marks/引1", 0);
          me->set("qi", (int)me->query("max_qi"));
          me->set("eff_qi", (int)me->query("max_qi"));
          me->set("neili", (int)me->query("max_neili"));
          return 1;
        }
        else
          return 0;
}

int chat()
{
        object me = this_object();
        object ob = me->query_temp("challenger");
        int my_max_qi, his_max_qi;

        if ( !objectp(ob) ) return ::chat();

        my_max_qi  = (int)me->query("max_qi");
        his_max_qi = (int)ob->query("max_qi");

        if (me->is_fighting(ob)) return ::chat();

        me->delete_temp("challenger");
        if ( !present(ob, environment()) ) return ::chat(); 

        if (( (int)me->query("qi")*100 / my_max_qi) <= 50 ) 
        {
        say(
                  "达而巴说：阁下武功确是不一般，在下十分佩服。\n"
                  "既然通过了我这关，你就直接去找我师傅吧。\n"
                );
                ob->set_temp("marks/引", 1);
                ob->set("jlfw", 1);
                return ::chat();
        }
        if (( (int)ob->query("qi")*100 / his_max_qi) < 50 ) 
        {
                say(
        "达而巴冲着" + ob->name() + "嘿嘿奸笑两声：阁下还是回去再练几年吧。\n"
                );
                return ::chat();
        }
        return ::chat();
}
/* init()
{
        object ob;

        ::init();
        if (interactive(ob = this_player()) && !is_fighting()) {
        if (ob->query("shen") > 10000) 
                        remove_call_out("do_killing");
                        call_out("do_killing",4,ob);
                        this_object()->kill_ob(ob);
                }
}
void do_killing(object ob)
{
        if (!ob || environment(ob) != environment())
                return;
        this_object()->kill_ob(ob);
}
*/
void attempt_apprentice(object ob)
{
        command("say  法王可不允许我收徒。");
        //command("recruit " + ob->query("id"));
}
int accept_kill(object me)
{
        command("say 大爷我正想找人杀呐，今天算你倒霉。\n");
        if (present("xiangmo chu", this_object())){
        command("wield chu");
        }
        kill_ob(me);
        return 1;
}
int auto_perform()
{
        object me = this_object();
        object target = me->select_opponent();
        object weapon = me->query_temp("weapon");

        if ( !objectp(weapon) ) {
        if ( present("xiangmo chu", me))
        command("wield chu");
        return 1;
        }
}

