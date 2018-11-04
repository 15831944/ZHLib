// taogu.c �ҹ�

#include <ansi.h>

inherit "/inherit/char/punisher";

void create()
{
        set_name("�ҹ�", ({ "tao gu", "tao", "gu" }));
        set("long",  "�������һ��������������ҹ����ˣ���˵���ҹ����ɵ�ʦ�档\n");
        set("gender", "����");
        set("age", 66);
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

        set_skill("force", 670);             // �����ڹ�
        set_skill("bibo-shengong", 670);     // �̲���
        set_skill("luoying-xinfa", 670);     // ��Ӣ�ķ�
        set_skill("hand",600);              // �����ַ�
        set_skill("finger", 670);            // ����ָ��
        set_skill("tanzhi-shentong", 670);   // ��ָ��ͨ
        set_skill("unarmed", 620);           // ����ȭ��
        set_skill("strike", 620);            // ����ȭ��
        set_skill("luoying-shenzhang", 620); // ��Ӣ����
        set_skill("xuanfeng-leg", 620);      // ����ɨҶ��
        set_skill("dodge", 670);             // ��������
        set_skill("anying-fuxiang", 670);    // ��Ӱ����
        set_skill("parry", 670);             // �����м�
        set_skill("sword", 660);             // ��������
	set_skill("throwing", 670);	     // ��������
        set_skill("luoying-shenjian", 660);  // ��Ӣ��
        set_skill("luoying-shenfa",660);
        set_skill("yuxiao-jian", 660);       // ���｣��
        set_skill("lanhua-shou", 670);       // ������Ѩ��
        set_skill("qimen-wuxing", 620);      // ��������
        set_skill("count", 620);             // ��������
        set_skill("literate", 660);          // ����ʶ��
        set_skill("chuixiao-jifa", 600);     // ���＼��
        set_skill("bihai-chaosheng", 600);   // �̺�����
        set_skill("taohua-yuan", 660);       // �һ�Թ
        set_skill("medical", 600);           // ����ҽ��
        set_skill("taohua-yaoli", 600);      // �һ�ҩ��

        map_skill("force"  , "bibo-shengong");
        map_skill("finger" , "tanzhi-shentong");
        map_skill("hand"   , "lanhua-shou");
        map_skill("unarmed", "luoying-zhang");
        map_skill("strike" , "xuanfeng-leg");
        map_skill("dodge"  , "luoying-shenfa");
        map_skill("parry"  , "tanzhi-shentong");
        map_skill("sword"  , "yuxiao-jian");
        map_skill("chuixiao-jifa", "bihai-chaosheng");
	map_skill("throwing", "tanzhi-shentong");

        prepare_skill("finger" , "tanzhi-shentong");
        prepare_skill("hand"   , "lanhua-shou");

        create_family("�һ���", 0, "��ʿ");

        setup();
        carry_object("/d/taohua/obj/yuxiao")->wield();
        carry_object("/d/taohua/obj/bupao")->wear();
}


