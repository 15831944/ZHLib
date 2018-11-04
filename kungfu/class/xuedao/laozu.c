// /kungfu/class/xueshan/xuedao.c  Ѫ������
// by secret

inherit NPC;
inherit F_MASTER;
inherit F_QUESTER;
inherit F_COAGENT;

#include <ansi.h>
#include "xuedao.h"

mixed ask_me();
string ask_midao();

void create()
{
        set_name("Ѫ������", ({ "xuedao laozu", "xue dao", "laozu" }));
        set("long",@LONG
���������Ż��ۣ���ͼ��ϣ���ͷ���������϶������ơ�������Ѫ���ŵ��Ĵ����š�
LONG
        );
        set("title",HIR"Ѫ���ŵ��Ĵ�����"NOR);
        set("gender", "����");
        set("age", 85);
        set("attitude", "peaceful");
        set("shen_type", -1);

        set("str", 33);
        set("int", 31);
        set("con", 35);
        set("dex", 32);

        set("max_qi", 5200);
        set("max_jing", 2600);
        set("neili", 6000);
        set("max_neili", 6000);
        set("jiali", 80);
        set("combat_exp", 2100000);

        set_skill("lamaism", 220);
        set_skill("literate", 80);
        set_skill("force", 230);
        set_skill("parry", 220);
        set_skill("blade", 225);
        set_skill("xue-dao", 225);
        set_skill("sword", 180);
        set_skill("mingwang-jian", 180);
        set_skill("dodge", 210);
        set_skill("mizong-neigong", 230);
        set_skill("xuehai-mogong", 230);
        set_skill("shenkong-xing", 210);
        set_skill("hand", 200);
        set_skill("dashou-yin", 200);
        set_skill("cuff", 200);
        set_skill("yujiamu-quan", 200);

        map_skill("force", "xuehai-mogong");
        map_skill("dodge", "shenkong-xing");
        map_skill("hand", "dashou-yin");
        map_skill("cuff", "yujiamu-quan");
        map_skill("parry", "xue-dao");
        map_skill("blade", "xue-dao");
        map_skill("sword", "mingwang-jian");

        prepare_skill("cuff", "yujiamu-quan");
        prepare_skill("hand", "dashou-yin");

	set("chat_chance_combat", 20);  
	set("chat_msg_combat", ({
		(: perform_action, "shendao" :),
		(: perform_action, "xueyu" :),
		(: exert_function, "powerup" :),
		(: exert_function, "recover" :),
	}));

        create_family("Ѫ����", 4, "����");
        set("class", "bonze");

        set("inquiry", ([
                "��Ѫ��"  : (: ask_me :),
                "����"      : (: ask_me :),
                "����"      : (: ask_me :),
                "�ܵ�"      : (: ask_midao :),
                "�ص�"      : (: ask_midao :),
        ]));

        set_temp("apply/attack", 50);
        set_temp("apply/dodge", 50);
        set_temp("apply/parry", 50);
        set_temp("apply/damage", 100);

        setup();
        carry_object("/d/xueshan/obj/y-jiasha")->wear();
        carry_object("/d/xueshan/obj/xblade")->wield();

        add_money("silver",40);
}

void attempt_apprentice(object ob)
{
        command("say �Բ��𣬱����ݲ����š�");
                return;
        if (! permit_recruit(ob))
                return;

        if (ob->query("class") != "bonze")
        {
                ob->set_temp("pending/join_bonze", 1);
                command("say �㲻�ǳ����ˣ�����Ѫ�����ǲ��������ġ�"
                        "�����Ҫ���ң�ȥ�����¡�");
                return;
        }

        if ((string)ob->query("gender") != "����")
        {
                command("say �Ҳ���Ůͽ�ܡ�\n");
                return;
        }

        if ((string)ob->query("family/family_name") != "Ѫ����")
        {
                command("say ��λ" + RANK_D->query_respect(ob) +
                        "�ȷǱ��ŵ��ӣ�������ذɣ�\n");
                return;
        }

        if ((int)ob->query("combat_exp") < 150000)
        {
                command("say ���ʵս����Ҳ߯���ˣ���ȥ�úø�������ȥ��");
                return;
        }

        if ((int)ob->query("shen") > -40000)
        {
                command("say ���ǲ����������������ɱ�˶����ᣡ\n");
                return;
        }

        if ((int)ob->query_skill("lamaism", 1) < 135)
        {
                command("say ����Ѫ���ţ���ϰ���ڷ�����Ҫ�ġ�\n");
                return;
        }

        if ((int)ob->query_skill("force") < 160)
        {
                command("say ����������ô���ģ��ڹ���ô�\n");
                return;
        }

        if ((int)ob->query_skill("blade", 1) < 100)
        {
                command("say �㵶����ô������������ң�\n");
                return;
        }

        command("nod");
        command("recruit " + ob->query("id"));

        ob->set("title", HIR "Ѫ���������״�����" NOR);
}

mixed ask_me()
{
        object me;

        me = this_player();
        if (me->query("can_perform/xue-dao/shendao"))
                return "��ú���ϰ�书����Ҫ���ҵ�����";

        if (me->query("family/family_name") != query("family/family_name"))
                return "����ʲô�ˣ��ҿ���ô����������Ѫ�������أ�";

        if (me->query_skill("xue-dao", 1) < 100)
                return "������㱾�£������Ѫ�������������������Ұɣ�";

        if (me->query("shen") > -1000)
                return "����������ô���ģ���ɱ�˶������ˣ�";

        message_vision(HIR "$n" HIR "̧̧�ֵ��������������$N"
                       HIR "��æ����ǰȥ��ֻ��$n"
                       HIR "���ֹ�����˵��Щʲô��\n" NOR,
                       me, this_object());
        command("heihei");
        command("say �������˰ɣ�");
        tell_object(me, HIG "��ͨ���˼�Ѫ�񵶵İ��\n" NOR);
        if (me->can_improve_skill("blade"))
                me->improve_skill("blade", 90000);
        me->set("can_perform/xue-dao/shendao", 1);
        return 1;
}

string ask_midao()
{
        object me;

        me = this_player();
        if (me->query("family/family_name") != "Ѫ����")
                return "��˵ʲô���Ҳ�֪������";

        command("whisper " + me->query("id") + " ���Ȼ�Ѿ���"
                "���������Ժ���Ҫȥ��ԭ���£�\n����������Ѫ��"
                "�ȱ������µ��ܵ�����ɵ�ɽ������Ѵ�����"
                "(enter mash)��\nȻ�󼴿ɵ�����ԭ������������"
                "Ѫ��������ԭ���������ӿ������ǡ�Ѫ����\n�ߡ����μ��ˣ�");
        return "���֪���ˣ������ܲ���й¶�����ˣ������������";
}
