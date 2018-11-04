// /kungfu/class/xueshan/baoxiang.c  ����
// by secret

inherit NPC;
inherit F_MASTER;
inherit F_GUARDER;

#include <ansi.h>
#include "xuedao.h"

void create()
{
        set_name("����", ({ "bao xiang", "bao", "xiang" }));
        set("long",@LONG
һ�����߼��ݵ�ɮ�ˣ�������â���䡣������Ѫ���������£������ĺ�������
LONG
        );
        set("title",HIR "Ѫ���ŵ��������" NOR);
        set("gender", "����");
        set("age", 35);
        set("attitude", "peaceful");
        set("shen_type", -1);
        set("str", 22);
        set("int", 21);
        set("con", 24);
        set("dex", 22);
        set("max_qi", 5000);
        set("max_jing", 2500);
        set("neili", 2800);
        set("max_neili", 2800);
        set("jiali", 30);
        set("combat_exp", 250000);

        set_skill("lamaism", 50);
        set_skill("literate", 90);
        set_skill("force", 130);
        set_skill("parry", 110);
        set_skill("blade", 125);
        set_skill("dodge", 100);
        set_skill("mizong-neigong", 130);
        set_skill("shenkong-xing", 100);
        set_skill("hand", 110);
        set_skill("dashou-yin", 110);
        set_skill("cuff", 100);
        set_skill("yujiamu-quan", 100);
        set_skill("xue-dao", 125);

        map_skill("force", "mizong-neigong");
        map_skill("dodge", "shenkong-xing");
        map_skill("hand", "dashou-yin");
        map_skill("cuff", "yujiamu-quan");
        map_skill("parry", "xue-dao");
        map_skill("blade", "xue-dao");

        prepare_skill("cuff", "yujiamu-quan");
        prepare_skill("hand", "dashou-yin");

        create_family("Ѫ����", 5, "����");
        set("class", "bonze");

	set("coagents", ({
		([ "startroom" : "/d/xuedao/shandong3",
		   "id" : "xuedao laozu" ]),
	}));

        setup();
        carry_object("/d/xueshan/obj/y-jiasha")->wear();
        carry_object("/clone/weapon/gangdao")->wield();

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
                        "�����Ҫ���ң���������ʦֶ��");
                return;
        }

        if ((string)ob->query("gender") != "����")
        {
                command("say �Ҳ���Ůͽ�ܡ�\n");
                return;
        }

        if (ob->query("shen") > 0)
        {
                command("say ������������������Ļ�����\n");
                this_object()->kill_ob(ob);
                return;
        }

        if ((int)ob->query_skill("lamaism", 1) < 30)
        {
                command("say ����Ѫ���ţ���ϰ���ڷ�����Ҫ�ġ�\n");
                return;
        }

        if ((int)ob->query_skill("force") < 60)
        {
                command("say �������������ô���Ȱ��ڹ����ã�\n");
                return;
        }

        command("recruit " + ob->query("id"));
}
