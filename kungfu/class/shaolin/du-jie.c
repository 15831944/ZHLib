// dujie.c

inherit NPC;
inherit F_MASTER;

mixed ask_me();

void create()
{
	set_name("�ɽ�", ({ "du jie", "jie" }) );
	set("title", "���ֳ���");
	set("gender", "����");
	set("age", 90);
	set("long",
		"����һ��������ݣ��ݹ��㶡����ɮ������ɫ�Ұף���һ��ֽһ����\n");

	set("attitude", "peaceful");
	set("class", "bonze");
	set("combat_exp", 2300000);

	set("str", 32);
	set("int", 30);
	set("con", 33);
	set("dex", 31);

	set("qi", 5000);
	set("max_qi", 2500);
	set("neili", 6700);
	set("max_neili", 6700);
	set("jiali", 90);

	create_family("������", 35, "����");
	assign_apprentice("����", 0);

	set_skill("buddhism", 250);
	set_skill("force", 255);
	set_skill("whip", 255);
	set_skill("parry", 250);
	set_skill("dodge", 240);

	set_skill("hunyuan-yiqi", 255);
	set_skill("shaolin-xinfa", 255);
	set_skill("riyue-bian", 255);
	set_skill("shaolin-shenfa", 240);

	map_skill("force", "hunyuan-yiqi");
	map_skill("whip",  "riyue-bian");
	map_skill("parry", "riyue-bian");
	map_skill("dodge", "shaolin-shenfa");

	set_skill("finger", 250);
	set_skill("jingang-zhi", 250);

	map_skill("finger", "jinggang-zhi");

	prepare_skill("finger", "jingang-zhi");

	set_skill("medical", 200);
	set_skill("shaolin-yishu", 200);

	set("inquiry", ([
		"�����"     : (: ask_me :),
	]));

	setup();

	carry_object("/d/shaolin/obj/changbian")->wield();
}

mixed ask_me()
{
	mapping fam; 
	object ob;
	
	if (! this_player()->query_temp("valid_in_fumoquan"))
	{
		command("say ���󱲣����δ�ɣ�����͵���շ�ħȦ�������������������㣡");
		kill_ob(this_player());
                return 1;
	}

        if (this_player()->query_temp("valid_in_fumoquan") != 1)
        {
                command("heng");
                return 1;
        }

	if (present("jingang zhao", this_player()))
		return RANK_D->query_respect(this_player()) + 
		"����ֻ��һ�������Ҿ��������ϣ�����̰�����У�";

	if (present("jingang zhao", environment()))
		return RANK_D->query_respect(this_player()) + 
		"����ֻ��һ�������Ҿ�����������ȡ�ߣ�����̰�����У�";

	ob = get_object("/d/shaolin/obj/jingang-zhao");
        if (! ob || environment(ob) && environment(ob) != this_object())
                return "��Ǹ���������ˣ�������Ѿ�����ȡ���ˡ�";

	ob->move(this_player());

	message_vision("\n�ɽ�һ�����Ե�����$N���ã�Ť������������ȡ������ֵݸ�$N��\n\n", this_player());

	return "���ܰ����������ϲ���������������޲�����ȷʵ�������������־�������ˣ�";
}

#include "/kungfu/class/shaolin/du.h"
