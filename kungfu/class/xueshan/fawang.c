// /kungfu/class/xueshan/fawang.c  ���ַ���
// by secret

inherit NPC;
inherit F_MASTER;
inherit F_COAGENT;

#include <ansi.h>
#include "xueshan.h"

mixed ask_me();

void create()
{
        set_name("���ַ���", ({ "jinlun fawang", "fawang", "jinlun" }));
        set("long",@LONG
����ѩɽ�µĻ��̷�������ѩɽ�µĵ�λ�������������Ħ�ǡ�
��һ���Ϻ����ģ�ͷ��ɮñ��
LONG
        );
        set("title", HIY "����" NOR);
        set("gender", "����");
        set("age", 50);
        set("no_get", 0);
        set("attitude", "peaceful");
        set("shen_type", -1);

        set("str", 31);
        set("int", 32);
        set("con", 31);
        set("dex", 29);

        set("max_qi", 5200);
        set("max_jing", 5200);
        set("neili", 7500);
        set("max_neili", 7500);
        set("jiali", 100);
        set("combat_exp", 2400000);

        set_skill("force", 260);
        set_skill("longxiang", 260);
        set_skill("mizong-neigong", 260);
        set_skill("dodge", 210);
        set_skill("shenkong-xing", 210);
        set_skill("cuff", 240);
        set_skill("yujiamu-quan", 240);
        set_skill("hand", 250);
        set_skill("dashou-yin", 250);
        set_skill("parry", 250);
        set_skill("staff", 220);
        set_skill("xiangmo-chu", 220);
        set_skill("necromancy", 250);
        set_skill("lamaism", 210);
        set_skill("literate", 200);
        set_skill("hammer", 270);
        set_skill("riyue-lun", 270);

        map_skill("force", "longxiang");
        map_skill("dodge", "shenkong-xing");
        map_skill("cuff", "yujiamu-quan");
        map_skill("hand", "dashou-yin");
        map_skill("parry", "riyue-lun");
        map_skill("sword", "xiangmo-chu");
        map_skill("hammer", "riyue-lun");

        prepare_skill("hand", "dashou-yin");
        prepare_skill("cuff", "yujiamu-quan");

        create_family("ѩɽ��", 2, "���̷���");
        set("class", "bonze");

        set("inquiry", ([
                "����" : (: ask_me :),
                "����" : (: ask_me :),
                "����" : (: ask_me :),
        ]));

        set_temp("apply/damage", 100);
        set_temp("apply/armor", 100);
        set_temp("apply/attack", 30);
        set_temp("apply/dodge", 25);
        set_temp("apply/parry", 25);

        setup();

        carry_object("/clone/weapon/falun")->set_amount(4);
          carry_object("/clone/weapon/falun")->wield();
              carry_object("/d/xueshan/obj/p-jiasha")->wear();
        carry_object("/d/xueshan/obj/sengmao")->wear();
        carry_object("/d/xueshan/obj/xuelian");
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

       if ((string)ob->query("family/family_name") != "ѩɽ��"
                && ob->query("family/family_name") != "Ѫ����")
        {
                command("say ��λ" + RANK_D->query_respect(ob) +
                        "�ȷ������ڵ��ӣ�������ذɣ�");
                return;
        }
         if ((int)ob->query("jlfw") < 1){
                command("say " + RANK_D->query_respect(ob) +
                        "��ȥ����ͽ�ܴ���ʹ�ܣ��������Ұɡ�");
        return;
        }

       if ((int)ob->query_skill("lamaism", 1) < 100)
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

        ob->set("title", HIY "���" NOR);
}

mixed ask_me()
{
        object me;

        me = this_player();
        if (me->query("can_perform/riyue-lun/poli"))
                return "��������ʲô���ú�����ȥ��";

        if (me->query("family/family_name") != query("family/family_name"))
                return "����������ѩɽ����˵";

        if (me->query_skill("riyue-lun", 1) < 120)
                return "��������ַ���Ϊ�����У��úõĸ�������";

        message_vision(HIY "$n" HIY "��$N" HIY "�������ֹ���"
                       "��˵��һЩ�ھ���\n" NOR,
                       me, this_object());
        command("say ȥ�ɣ�");
        tell_object(me, HIG "��ͨ���������İ��\n" NOR);
        if (me->can_improve_skill("hammer"))
                me->improve_skill("hammer", 90000);
        me->set("can_perform/riyue-lun/poli", 1);
        return 1;
}

