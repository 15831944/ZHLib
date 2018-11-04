#include <ansi.h>

inherit NPC;
inherit F_MASTER;

mixed ask_me(); 

void consider();

void create()
{
        set_name("�ɳ���", ({"xi zhanglao", "xi", "zhanglao"}));
        set("title", "ؤ��Ŵ�����");
        set("gender", "����");
        set("age", 45);

        set("attitude", "peaceful");
        set("rank",9);
        set("str", 35);
        set("int", 21);
        set("con", 32);
        set("dex", 25);

        set("qi", 2500);
        set("max_qi", 2500);
        set("jing", 1200);
        set("max_jing", 1200);
        set("neili", 4000);
        set("max_neili", 4000);
        set("jiali", 80);
        
        set("combat_exp", 1000000);
        set("shen_type", 1);
        set("score", 25000);
        
        set_skill("force", 180);
        set_skill("jiaohua-neigong", 180);
        set_skill("unarmed", 180);
        set_skill("changquan", 150);
        set_skill("dodge", 150);
        set_skill("feiyan-zoubi", 150);
        set_skill("parry", 180);
        set_skill("staff", 180);
        set_skill("fumo-zhang", 180);
        set_skill("begging", 150);
        set_skill("checking", 150);
        set_skill("jueming-tui", 180);

        map_skill("force", "jiaohua-neigong");
        map_skill("unarmed", "jueming-tui");
        map_skill("parry", "fumo-zhang");
        map_skill("staff", "fumo-zhang");
        map_skill("dodge", "feiyan-zoubi");
        
        set("inquiry", ([
                "��ħ��": (: ask_me :),
                "����"  : (: ask_me :),
                "�����": (: ask_me :),
                "����"  : (: ask_me :),
        ]));

        create_family("ؤ��", 18, "�Ŵ�����");

        set("chat_chance_combat", 40);
        set("chat_msg_combat", ({
                (: perform_action, "staff.lun" :),
                (: exert_function, "recover" :),
        }) );

        setup();

        carry_object("/d/gaibang/obj/budai")->set_amount(8);
        carry_object("/d/gaibang/obj/budai")->wear();
        carry_object("/clone/weapon/gangzhang")->wield(); 
}

void attempt_apprentice(object ob)
{
        if (ob->query("class")=="bonze") {
                if (ob->query("gender")=="Ů��")
                        command ("say ʦ̫���ǳ����ˣ���ô���ڱ������л����أ�");
                return;
        }

        if ( (int)ob->query("int") >= 25 && !(int)ob->query("tianmo_jieti")) {
                command("say ����ؤ�������һ���Ը���Ϊ����" + 
                RANK_D->query_respect(ob) + "�ϻ۹��ˣ��ƺ�����ѧؤ��Ĺ���");
                return;
        }

        if( ob->query("family/family_name") != "ؤ��" )
        {
                if( ob->query("rank") > 1 ) {
                        command("say ����������Ϊ�ȣ����ݲ�����������������ļһ\n");
                        return;
                }
        
                command("say �ðɣ�ϣ��" + RANK_D->query_respect(ob) +
                "�ܺú�ѧϰ�����书�������ڽ����д���һ����Ϊ��");
                ob->set("rank", 1); 
                command("recruit " + ob->query("id"));
                ob->set("title", "ؤ��һ������");
        } 
        else
        {
                ob->set_temp("title", ob->query("title"));
                command("recruit " + ob->query("id"));
                ob->set("title", ob->query_temp("title"));
                ob->delete_temp("title");
        }
}
mixed ask_me()
{
        object me;

        me = this_player();
        if (me->query("can_perform/fumo-zhang/lun"))
                return "�Լ��úö���ϰ�ɣ�";

        if (me->query("family/family_name") != query("family/family_name"))
                return RANK_D->query_respect(me) + "�γ����ԣ�";

        if (me->query("rank") < 8)
                return "���ڰ���ı���̫���ˣ����㵽�˴����Ӻ��������Ұɣ�";

        if (me->query_skill("fumo-zhang", 1) < 120)
                return "��ķ�ħ�Ȼ������ң�Ҫ��������";

        message_vision( HIY "$n" HIY "΢Ц�ŵ��˵�ͷ��ͻȻһ�����ȣ�"
                        "�������Ȼ��裬��Ӱ������������Ȧ����\nͬ" NOR +
                        HIR "�����" NOR + HIY "һ�㣬������磬����"
                        "΢���ޱȣ�\n" NOR,
                        me, this_object());
        command("nod");
        command("say ��������ˣ�");
        tell_object(me, HIC "��ѧ���ˡ�����֡���һ�С�\n" NOR);
        if (me->can_improve_skill("staff"))
                me->improve_skill("staff", 160000);
        me->set("can_perform/fumo-zhang/lun", 1);
        return 1;
}


