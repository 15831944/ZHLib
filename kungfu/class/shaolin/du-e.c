// due.c

inherit NPC;
inherit F_MASTER;

mixed ask_me();

void create()
{
	set_name("�ɶ�", ({ "du e", "e" }) );
	set("title", "���ֳ���");
	set("gender", "����");
	set("age", 90);
	set("long",
		"����һ��������ݣ��ݹ��㶡����ɮ������ɫ"
	        "�ݻƣ���ͬһ�ο�ľ��\n");

	set("attitude", "peaceful");
	set("class", "bonze");
	set("combat_exp", 2350000);

	set("str", 34);
	set("int", 36);
	set("con", 35);
	set("dex", 33);

	set("qi", 5800);
	set("max_qi", 2900);
	set("neili", 7200);
	set("max_neili", 7200);
	set("jiali", 110);

	create_family("������", 35, "����");
	assign_apprentice("����", 0);

	set_skill("buddhism", 320);
	set_skill("force", 270);
	set_skill("whip", 270);
	set_skill("parry", 270);
	set_skill("dodge", 260);

	set_skill("hunyuan-yiqi", 270);
	set_skill("shaolin-xinfa", 270);
	set_skill("riyue-bian", 270);
	set_skill("shaolin-shenfa", 260);

	map_skill("force", "hunyuan-yiqi");
	map_skill("whip",  "riyue-bian");
	map_skill("parry", "riyue-bian");
	map_skill("dodge", "shaolin-shenfa");

	set_skill("finger", 260);
	set_skill("strike", 260);
	set_skill("nianhua-zhi", 260);
	set_skill("sanhua-zhang", 260);

	map_skill("finger", "nianhua-zhi");
	map_skill("strike", "sanhua-zhang");

	prepare_skill("finger", "nianhua-zhi");
	prepare_skill("strike", "sanhua-zhang");

	set_skill("medical", 250);
	set_skill("shaolin-yishu", 250);

	set("inquiry", ([
		"��ħ��"     : (: ask_me :),
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

	if (present("fumo zhang", this_player()))
		return RANK_D->query_respect(this_player()) + 
		"����ֻ��һ�ѣ����Ҿ��������ϣ�����̰�����У�";

	if (present("fumo zhang", environment()) )
		return RANK_D->query_respect(this_player()) + 
		"����ֻ��һ�ѣ����Ҿ�����������ȡ�ߣ�����̰�����У�";

	ob = get_object("/d/shaolin/obj/fumo-zhang");
        if (! ob || environment(ob) && environment(ob) != this_object())
		return "��Ǹ���������ˣ���ħ���Ѿ�����ȡ���ˡ�";
	ob->move(this_player());

	message_vision("\n�ɶ�Цһ�������ͷ��������������ȡ����ħ�Ƚ���$N��\n\n", this_player());

	return "���Ȼ�ܴ�����շ�ħȦ������Ȼ�ǵ��������еķǷ�������ħ�����ʷ������ˣ�";
}

#include "/kungfu/class/shaolin/du.h"
