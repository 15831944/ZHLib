// /kungfu/class/xueshan/jiamu.c  ��ľ���
// by secret
//modified by rama

inherit NPC;
inherit F_MASTER;

#include <ansi.h>
#include "xueshan.h"
string ask_me();

void create()
{
        set_name("��ľ���", ({ "jiamu huofo", "huofo", "jiamu" }));
        set("long",@LONG
��ľ�����ѩɽ���е��ĸ�ɮ���Է��о�����о���
����һ����ɫ���ģ�ͷ��ɮñ��Ŀ����磬�ƺ���������
LONG
        );
        set("title",HIY"���"NOR);
        set("gender", "����");
        set("age", 45);
        set("attitude", "peaceful");
        set("shen_type", -1);
        set("str", 30);
        set("int", 30);
        set("con", 30);
        set("dex", 30);
        set("max_qi", 1000); 
        set("max_jing", 2500); 
        set("neili", 2000); 
        set("max_neili", 2000); 
        set("jiali", 50); 
        set("combat_exp", 340000); 
        set("inquiry", ([

                "����" : (: ask_me :),

                "�ؾ�" : "�����»��Ҫȥ��",
                ]));

        set_skill("lamaism", 120);
        set_skill("literate", 80);
        set_skill("force", 125);
        set_skill("mizong-neigong", 125);
        set_skill("dodge", 130);
        set_skill("shenkong-xing", 120);
        set_skill("necromancy", 100);
        set_skill("cuff", 120);
        set_skill("yujiamu-quan", 100);
        set_skill("parry", 120);
        set_skill("sword", 130);
        set_skill("mingwang-jian", 140);

        map_skill("force", "mizong-neigong");
        map_skill("dodge", "shenkong-xing");
        map_skill("cuff", "yujiamu-quan");
        map_skill("parry", "mingwang-jian");
        map_skill("sword", "mingwang-jian");

        prepare_skill("cuff", "yujiamu-quan");

        create_family("ѩɽ��", 3, "���");
        set("class", "bonze");

        setup();

        carry_object("/d/city/obj/changjian")->wield();
        carry_object("/d/xueshan/obj/y-jiasha")->wear();
        carry_object("/d/xueshan/obj/sengmao")->wear();

        add_money("silver",20);
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
                command("say ��λ" + RANK_D->query_respect(ob) +
                        "������ذɣ�");
                return;
        }

        if ((string)ob->query("family/family_name") != "ѩɽ��" && (string)ob->query("family/family_name") != "Ѫ����")
        {
                command("say ��λ" + RANK_D->query_respect(ob) +
                        "�ȷǱ��µ��ӣ�������ذɣ�");
                return;
        }

        if ((int)ob->query_skill("lamaism", 1) < 60)
        {
                command("say ����ѩɽ�£���ϰ�����ķ�����Ҫ�ġ�");
                command("say ��λ" + RANK_D->query_respect(ob) +
                        "�Ƿ�Ӧ�ö�����б��ŵ��ķ���");
                return;
        }

        command("smile");
        command("nod");
        command("say �������ѧϰ�𷨰ɣ�");
        command("recruit " + ob->query("id"));

        ob->set("title", HIY "������" NOR);
}
string ask_me()

{

        mapping fam;

        object wage;

        object me = this_player();



        if (!(fam = me->query("family")) || fam["family_name"] !="ѩɽ��"

        && fam["family_name"] !="Ѫ����" && me->query("class") !="lama")

                return RANK_D->query_respect(this_player()) +

                "�뱾��������������֪�˻��Ӻ�̸��";

        if (me->query_skill("lamaism", 1) < 60)

                return "�㲻��Ҫ���";

        if (me->query("age") < 25 && me->query("lama_wage") > me->query("mud_age") - 86400)

                return RANK_D->query_respect(this_player()) +

                "�����û������������Ҫ���";

        if (me->query("age") > 24 && me->query("lama_wage") > me->query("mud_age") - 259200)

                return RANK_D->query_respect(this_player()) +

                "�����û������������Ҫ���";

        if (me->query_skill("lamaism", 1) >= 60

        && me->query_skill("lamaism", 1) < 90){

        wage = new("/clone/money/gold");        

        wage->set_amount(2);

        wage->move(me);        

        me->set("lama_wage",me->query("mud_age"));

        message_vision("��ľ���ת���ó�һ������ݸ�$N��\n", me);

                return "�������˽���Ĺ�����պá�";

        }

        if (me->query_skill("lamaism", 1) >= 90

        && me->query_skill("lamaism", 1) < 120){

        wage = new("/clone/money/gold");

        wage->set_amount(8);

        wage->move(me);        

        me->set("lama_wage",me->query("mud_age"));

        message_vision("��ľ���ת���ó�һ������ݸ�$N��\n", me);

                return "�������˽���Ĺ�����պá�";

        }

        if (me->query_skill("lamaism", 1) >= 120

        && me->query_skill("lamaism", 1) < 150){

        wage = new("/clone/money/gold");

        wage->set_amount(15);

        wage->move(me);        

        me->set("lama_wage",me->query("mud_age"));

        message_vision("��ľ���ת���ó�һ������ݸ�$N��\n", me);

                return "���Ƿ�ү����Ĺ�����պá�";

        }

        if (me->query_skill("lamaism", 1) >= 150){ 

        wage = new("/clone/money/gold");

        wage->set_amount(20);

        wage->move(me);        

        me->set("lama_wage",me->query("mud_age"));

        message_vision("��ľ���ת���ó�һ������ݸ�$N��\n", me);

                return "���Ƿ�������Ĺ�����պá�";

        }       

}




