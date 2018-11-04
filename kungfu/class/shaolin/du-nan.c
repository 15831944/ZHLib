// dunan.c

inherit NPC;
inherit F_MASTER;

mixed ask_me();

void create()
{
	set_name("����", ({ "du nan", "nan" }) );
	set("title", "���ֳ���");
	set("gender", "����");
	set("age", 90);
	set("long",
		"����һ��������ݣ��ݹ��㶡����ɮ������ɫ��ڣ������������ɡ�\n");

	set("attitude", "peaceful");
	set("class", "bonze");
	set("combat_exp", 2500000);

	set("str", 33);
	set("int", 32);
	set("con", 34);
	set("dex", 31);

	set("qi", 5200);
	set("max_qi", 2600);
	set("neili", 7400);
	set("max_neili", 7400);
	set("jiali", 100);

	create_family("������", 35, "����");
	assign_apprentice("����", 0);

	set_skill("buddhism", 300);
	set_skill("force", 260);
	set_skill("whip", 260);
	set_skill("parry", 260);
	set_skill("dodge", 250);

	set_skill("hunyuan-yiqi", 260);
	set_skill("shaolin-xinfa", 260);
	set_skill("riyue-bian", 260);
	set_skill("shaolin-shenfa", 250);

	map_skill("force", "hunyuan-yiqi");
	map_skill("whip",  "riyue-bian");
	map_skill("parry", "riyue-bian");
	map_skill("dodge", "shaolin-shenfa");

	set_skill("strike", 260);
	set_skill("xumishan-zhang", 260);
	set_skill("claw", 250);
	set_skill("hand", 250);
	set_skill("longzhua-gong", 250);
	set_skill("qianye-shou", 250);

	map_skill("strike", "xumishan-zhang");

	prepare_skill("strike", "xumishan-zhang");

	set_skill("medical", 220);
	set_skill("shaolin-yishu", 220);

	set("inquiry", ([
		"������"     : (: ask_me :),
	]));

	set("count", 0);
	if (random(16) == 8) add("count", 1);

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

	if (uptime() < 1800)
		return "�����������֮������������ޱȣ������ڿ�û�С�";

	if ( present("puti zi", this_player()) )
		return RANK_D->query_respect(this_player()) + 
		"������ֻ��һ�ţ����Ҿ��������ϣ�����̰�����У�";

	if ( present("puti zi", environment()) )
		return RANK_D->query_respect(this_player()) + 
		"������ֻ��һ�ţ����Ҿ�����������ȡ�ߣ�����̰�����У�";

	if (query("count") < 1)
		return "�����������֮����ɼ������ޱȣ����������ڿ�û�С�";

	ob = new("/d/shaolin/obj/puti-zi");
	ob->move(this_player());

	add("count", -1);

	message_vision("\n���Ѳ�ȻһЦ�����ų�̾һ������������ȡ���������ƿ�����������ӵݸ�$N��\n\n", this_player());

	return "�ҵ������ڷ�����ǰ���º�Ը��ÿʮ������ɽ�󴨣��������գ�\n" +
	       "���ɵ����������ӣ�������Ե�ˣ��ܵô��컯���������Ϊ֮��";
}
#include "/kungfu/class/shaolin/du.h"
