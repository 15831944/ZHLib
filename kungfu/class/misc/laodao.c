// laodao.c �ϵ�

#include <ansi.h>

inherit "/inherit/char/punisher";

void create()
{
    set_name("�ϵ�", ({ "lao dao", "lao", "dao" }));
    set("long", "����һ����ʿ��������գ�Ψ��˫Ŀ������ɫ��\n");
    set("title",HIG "ȫ��" HIM " �ϵ�" NOR);
    set("gender", "����");
    set("age", 70);
    set("shen_type",1);
    set("attitude", "peaceful");
    set("class", "fighter");

    set("str", 33);
    set("int", 36);
    set("con", 38);
    set("dex", 33);

    set("qi", 9999);
    set("max_qi", 9999);
    set("jing", 9999);
    set("max_jing", 9999);
    set("neili", 9999);
    set("max_neili", 9999);
    set("jiali", 300);
    set("combat_exp", 10000000);
    set("score", 10000000);
    
        set_skill("force", 680);
        set_skill("quanzhen-xinfa", 680);
        set_skill("xiantian-gong", 680);
        set_skill("sword", 680);
        set_skill("quanzhen-jian",680);
        set_skill("dodge", 680);
        set_skill("jinyan-gong", 680);
        set_skill("parry", 680);
        set_skill("strike", 680);
        set_skill("chongyang-shenzhang", 680);
        set_skill("haotian-zhang", 680);
        set_skill("literate",680);
        set_skill("finger",680);
        set_skill("taoism",680);
        set_skill("finger",680);
        set_skill("zhongnan-zhi", 680);
        set_skill("sun-finger",680);
        set_skill("medical", 680);
        set_skill("liandan-shu", 680);
	set_skill("cuff",680);
	set_skill("whip",680);
	set_skill("chunyang-quan",680);
	set_skill("duanyun-bian",680);
        set_skill("array",680);
	set_skill("beidou-zhenfa", 680);

	map_skill("array","beidou-zhenfa");
        map_skill("force", "xiantian-gong");
        map_skill("sword", "quanzhen-jian");
        map_skill("dodge", "jinyan-gong");
        map_skill("parry", "quanzhen-jian");
        map_skill("finger","sun-finger");
        map_skill("strike", "haotian-zhang");
	map_skill("cuff",   "chunyang-quan");
	map_skill("whip",   "duanyun-bian");

        prepare_skill("finger","sun-finger");
        prepare_skill("strike","haotian-zhang");

	create_family("ȫ��", 0, "Ԫ��");
	setup();

        carry_object("/clone/weapon/changjian")->wield();
        carry_object("/d/quanzhen/npc/obj/greenrobe")->wear();
}