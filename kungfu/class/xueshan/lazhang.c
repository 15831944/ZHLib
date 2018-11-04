// /kungfu/class/xueshan/lazhang.c  ���»�� 
// by secret 
//modified by rama@hx
 
inherit NPC; 
inherit F_MASTER; 

#include <ansi.h>
#include "xueshan.h"

string ask_for_join();
string ask_me();

void create() 
{ 
        set_name("���»��", ({ "lazhang huofo", "huofo", "lazhang" })); 
        set("long",@LONG 
    ���Ǳ��²ؾ�������ܣ�����Զ�������󾭣���ʱ��ʮ�ꡣ��ʮ����ʱ��ס���£�
�ڱ羭����϶�ռ��ͷ��������ȥ��Ƽ��ݣ������ݸߡ�);
LONG 
        ); 
        set("title",HIY"���"NOR); 
        set("gender", "����"); 
        set("age", 50); 
        set("attitude", "peaceful"); 
        set("shen_type", -1); 
        set("str", 30); 
        set("int", 30); 
        set("con", 30); 
        set("dex", 30);
        set("max_qi", 2900); 
        set("max_jing", 1400); 
        set("neili", 3000); 
        set("max_neili", 3000); 
        set("jiali", 40); 
        set("combat_exp", 470000); 
        set("score", 40000); 
 
        set_skill("lamaism", 150);
        set_skill("literate", 120);
        set_skill("force", 150);
        set_skill("mizong-neigong", 100);
        set_skill("dodge", 120);
        set_skill("shenkong-xing", 110);
        set_skill("hand", 140); 
        set_skill("dashou-yin", 140); 
        set_skill("parry", 120); 
        set_skill("sword", 100); 
        set_skill("mingwang-jian", 100); 
 
        map_skill("force", "mizong-neigong"); 
        map_skill("dodge", "shenkong-xing"); 
        map_skill("hand",  "dashou-yin"); 
        map_skill("parry", "mingwang-jian"); 
        map_skill("sword", "mingwang-jian"); 
 
        prepare_skill("hand",  "dashou-yin");
        set("book_count",3);

        create_family("ѩɽ��", 3, "���"); 
        set("class", "bonze"); 

        set("inquiry",([
                "���"  : (: ask_for_join :),
                "����"  : (: ask_for_join :),
                "�ؾ�" : (: ask_me :),
        ]));

        setup(); 
 
        carry_object("/d/xueshan/obj/y-jiasha")->wear(); 
        carry_object("/d/xueshan/obj/sengmao")->wear(); 
 
        add_money("silver", 20);
} 
 
 
void attempt_apprentice(object ob) 
{
        if (! permit_recruit(ob))
                return;
 
        if ((string)ob->query("gender") != "����")
        {
                command("say ��ϰ�����ڹ���Ҫ����֮�塣");
                command("say ��λ" + RANK_D->query_respect(ob) +
                        "������ذɣ�");
                return;
        }
 
        if ((string)ob->query("class") != "bonze")
        {
                command("say �ҷ��ŵ����������ࡣ");
                ob->set_temp("pending/join_bonze", 1);
                command("say ʩ������������ҷ𣬾������(kneel)�ܽ䡣\n");
                return;
        }
 
        if ((int)ob->query_skill("lamaism", 1) < 50)
        {
                command("say ����ѩɽ�£���ϰ�����ķ�����Ҫ�ġ�" +
                        "\n��λ" + RANK_D->query_respect(ob) +
                        "�Ƿ�Ӧ�ö�����б��ŵ��ķ���");

                return;
        }
 
        command("smile");
        command("nod");
        command("say �������ѧϰ�𷨰ɣ�");
        command("recruit " + ob->query("id"));
        ob->set("title",HIY"������"NOR);
}

void init()
{
        add_action("do_kneel", "kneel");

}

string ask_for_join()
{
        object me;

        me = this_player();

        if ((string)me->query("class")=="bonze")
                return "�����ӷ�����ͬ�ǳ����ˣ��ιʸ�ƶɮ�������Ц��\n";

        if ((string)me->query("gender") != "����")
                return "ʩ��������������ǿ�ϲ�ɺأ���ϧ����ֻ����ͽ��\n";

        me->set_temp("pending/join_bonze", 1);
        return "�����ӷ����գ����գ�ʩ������������ҷ���"
               "����(kneel)�ܽ䡣\n";
}

int do_kneel()
{
        object me = this_player();

        if( !me->query_temp("pending/join_bonze") )
                return notify_fail("����˰�㣬���û�����㡣\n");

        message_vision("$N˫�ֺ�ʮ�����������ع���������\n\n"
                       "$n������ƣ���$Nͷ�������Ħ���˼��£���"
                       "$N��ͷ��������ȥ��\n\n", me, this_object());

        command("smile");

        me->set("class", "bonze");

        return 1;
}
string ask_me()
{
        mapping fam;
        object ob;

        if (!(fam = this_player()->query("family")) || fam["family_name"] !="ѩɽ��"
        && fam["family_name"] !="Ѫ����")
                return RANK_D->query_respect(this_player()) +
                "�뱾��������������֪�˻��Ӻ�̸��";
        if (query("book_count") < 1)
                return "�������ˣ����µľ��鲻�ڴ˴���";
        add("book_count", -1);
        ob = new("/d/xueshan/obj/fojing3.c");
        ob->move(this_player());
        return "�ðɣ��Ȿ�������û�ȥ�ú����С�";
}


