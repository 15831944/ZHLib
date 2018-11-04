#include <ansi.h>
#include "songshan.h"

inherit NPC;
inherit F_MASTER;
inherit F_GUARDER;

void create()
{
        set_name("����", ({ "di xiu", "xiu", "di" }) );
        set("gender", "����");
        set("class", "swordsman");
        set("age", 25);
        set("attitude", "peaceful");
        set("str", 26);
        set("con", 30);
        set("dex", 30);
        set("int", 28);

        set("neili", 1000);
        set("max_neili", 1000);
        set("jiali", 30);
        set("max_qi",1000);
        set("max_jing",1800);
        set("combat_exp", 90000);
        set("shen_type", 1);

        set_skill("cuff", 60);
        set_skill("songshan-quan", 60); 
        set_skill("strike", 60);    
        set_skill("songshan-zhang", 60); 
        set_skill("sword", 80);
        set_skill("songshan-sword", 80);
        set_skill("force", 80);
        set_skill("parry", 60);
        set_skill("dodge", 60);
        set_skill("lingxu-bu", 60);
        set_skill("songshan-xinfa", 80);
        set_skill("literate", 80);
        set_skill("martial-cognize", 60);

        map_skill("force", "songshan-xinfa");
        map_skill("sword", "songshan-sword");
        map_skill("parry", "songshan-sword");
        map_skill("cuff", "songshan-quan");
        map_skill("strike", "songshan-zhang");
        map_skill("dodge", "lingxu-bu");

        prepare_skill("strike", "songshan-zhang");

        create_family("��ɽ��", 14, "����");

        set("chat_chance_combat", 120);
        set("chat_msg_combat", ({
                (: perform_action, "sword.meng" :),
                (: perform_action, "strike.po" :),
                (: exert_function, "recover" :),
        }));

        set("coagents", ({ 
                ([ "startroom" : "/d/songshan/chanyuan", 
                   "id"        : "zuo lengchan" ]), 
        })); 

        setup();

        carry_object("/clone/weapon/changjian")->wield();
        carry_object("/clone/cloth/cloth")->wear();
}

void attempt_apprentice(object ob)
{
        
        if (! permit_recruit(ob))
                return;

        if ((int)ob->query("shen") < 0)
        {
                command("say �����˲������£�����ɽ�ɿ����㲻�á�");
                return;
        }

        command("say ��Ȼ��ˣ������Ժ�͸����Ұɡ�");
        command("recruit " + ob->query("id"));
}

void unconcious()
{
        die();
}

