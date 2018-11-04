
inherit NPC;

#include <ansi.h>
int auto_perform();
int ask_me();
int do_qiecuo();

void create()
{
set_name("�����", ({ "darba", "dar", "ba" }));
        set("long",
"���ǽ��ַ����Ķ����ӣ��ѵ÷����塢�����洫��������������һ�����Ź��� \n"
"�����˵ã������θ��ݣ�ȴʹһ�������ĳߵĴ���ħ�ơ�\n");
        
        set("inquiry",([
               "����"  : (: ask_me :),
                "���ַ���" : (: ask_me :),
        ]));

        set("title", HIY "���" NOR);
        set("gender", "����");
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

        create_family("ѩɽ��", 3, "���");
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
        if( this_player()->query("family/family_name") != "ѩɽ��"
        && this_player()->query("family/family_name") != "Ѫ����")
        return 0;

        if( !present("xiangmo chu", this_object())){
        say("�����ҡ��ҡͷ������û��������˵�ˣ��������������Ұɡ�\n");
        return 1;
        }

        if( this_player()->query("jlfw")){
        say("�����˵����ʦ��Ҫ��ʦ�������ҿ�û�á�\n");
        return 1;
        }

        say(
"����Ϳ���" + this_player()->name() + "һ�۲�м��˵��������ʦ�������ȹ���\n"
"��һ�أ���λ" + RANK_D->query_respect(this_player()) + "�ǲ����Ⱥ����д�һ�£�\n");
        this_player()->set_temp("marks/��1", 1);
        return 1;
}

int accept_fight()
{
        object me, ob;

        me = this_object();
        ob = this_player();

        if( ob->query_temp("marks/��1") 
        && present("xiangmo chu", me)) {
        say(ob->name() + "�Դ����˵���ðɣ���" 
             "�Ҿ�ͬ���д꼸�аɣ��㵽Ϊֹ��\n");
          command("wield chu");
          me->set_temp("challenger", ob);
          ob->set_temp("marks/��1", 0);
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
                  "�����˵�������书ȷ�ǲ�һ�㣬����ʮ�������\n"
                  "��Ȼͨ��������أ����ֱ��ȥ����ʦ���ɡ�\n"
                );
                ob->set_temp("marks/��", 1);
                ob->set("jlfw", 1);
                return ::chat();
        }
        if (( (int)ob->query("qi")*100 / his_max_qi) < 50 ) 
        {
                say(
        "����ͳ���" + ob->name() + "�ٺټ�Ц���������»��ǻ�ȥ��������ɡ�\n"
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
        command("say  �����ɲ���������ͽ��");
        //command("recruit " + ob->query("id"));
}
int accept_kill(object me)
{
        command("say ��ү����������ɱ�ţ��������㵹ù��\n");
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

