// duansh.c ���˺�

#include <ansi.h>

inherit "/inherit/char/punisher";

void create()
{
        set_name("���˺�", ({ "duan shanghong", "shanghong" }));
        set("long",  "���ϻ��忪ɽ�ʵۣ��ڽ����μҽ�ɽ֮ǰ�������ǵ�ʱ�������־������֡�\n");
        set("gender", "����");
        set("age", 65);
        set("attitude", "peaceful");
        set("shen_type", 1);
        set("str", 32);
        set("int", 33);
        set("con", 32);
        set("dex", 31);
        
        set("max_qi", 9999);
        set("max_jing", 9999);
        set("neili", 9999);
        set("max_neili", 9999);
        set("jiali", 300);
        set("combat_exp", 10000000);
        set("score", 10000000);

	set_skill("force", 640);		// �����ڹ�
	set_skill("kurong-changong", 640);	// ��������
	set_skill("finger", 720);		// ����ָ��
	set_skill("sun-finger", 720);		// һ��ָ
	set_skill("dodge", 650);		// ��������
	set_skill("tiannan-step", 650);		// ���ϲ���
	set_skill("parry", 680);		// �����м�

	map_skill("force", "kurong-changong");
	map_skill("dodge", "tiannan-step");
	map_skill("parry", "six-finger");
	map_skill("finger", "sun-finger");
	prepare_skill("finger","sun-finger");

        create_family("���ϻ���", 0, "����");

        setup();
	carry_object("/clone/misc/cloth")->wear();
}


