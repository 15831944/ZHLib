// Npc: /kungfu/class/shaolin/kong-jian.c

#include <ansi.h>

inherit NPC;
inherit F_GUARDER;

void create()
{
	set_name("�ռ�", ({ "kong jian", "kongjian" }));
	set("long",
		"����һλ�뷢���׵���ɮ��������������ò�Ⱥ͡�\n"
	);

	set("nickname", HIR "��ɮ" NOR);
	set("gender", "����");
	set("attitude", "friendly");
	set("class", "bonze");

	set("age", 60);
	set("shen_type", 1);
	set("str", 32);
	set("int", 34);
	set("con", 31);
	set("dex", 30);
	set("max_qi", 6000);
	set("max_jing", 3000);
	set("neili", 6000);
	set("max_neili", 6000);
	set("jiali", 40);
	set("combat_exp", 2500000);

	set_skill("force", 250);
	set_skill("hunyuan-yiqi", 250);
	set_skill("shaolin-xinfa", 240);
	set_skill("dodge", 240);
	set_skill("shaolin-shenfa", 240);
	set_skill("finger", 240);
	set_skill("nianhua-zhi", 240);
	set_skill("strike", 240);
	set_skill("sanhua-zhang", 240);
	set_skill("parry", 250);
	set_skill("buddhism", 270);
	set_skill("literate", 180);

	map_skill("force", "hunyuan-yiqi");
	map_skill("dodge", "shaolin-shenfa");
	map_skill("strike", "sanhua-zhang");
        map_skill("finger", "nianhua-zhi");
	map_skill("parry", "longzhua-gong");

	prepare_skill("strike", "sanhua-zhang");
        prepare_skill("finger", "nianhua-zhi");

        set("coagents", ({
                ([ "startroom" : "/d/shaolin/cjlou",
                   "id"        : "wuming laoseng" ]),
        }));

	set("guarder", ([
		"refuse_other": "$N��$n�������գ����ֻ�����ֵ��Ӳ������ڣ�ʩ��������ذɣ�",
                "refuse_carry": "$N��$n�����㱳�ϱ�����˭����������������",
	]));

	create_family("������", 36, "����");

	setup();

        carry_object("/d/shaolin/obj/cheng-cloth")->wear();
}

void attempt_apprentice(object ob)
{
        message_vision("$N˫�ֺ�ʮ��$n�����������գ��������Ѳ���ͽ�ˡ�\n",
                       this_object(), ob);
}
