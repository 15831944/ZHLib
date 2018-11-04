// mu.c
// Modified by Dumb, 2003-10-2, Insert leave xkd function.

#include <ansi.h>
inherit NPC;
inherit F_MASTER;

#define REVIVE_ROOM             "/d/city/wumiao"

int ask_zhou();
int out_xiakedao();

void create()
{
        set_name("ľ����", ({ "mu danfeng", "mu" }));
        set("long", "������������֮ɫ������͵��������ųơ�Ҷ����¶����\n"
                   +"ֻ��������ϡϡ���䣬أ�Ժڶ���٣���һ����ȴ�������ơ�\n"
                   +"����������ʵ����͡�\n");
        set("title", HIB"���͵�����"NOR);
        set("gender", "����");
        set("age", 75);
        set("shen_type",1);
        set("attitude", "peaceful");

        set("str", 30);
        set("int", 29);
        set("con", 30);
        set("dex", 28);

        set("qi", 9000);
        set("max_qi", 9000);
        set("jing", 5000);
        set("max_jing", 5000);
        set("neili", 9000);
        set("max_neili", 9000);
        set("jiali", 200);

        set("combat_exp", 8000000);
        set("score", 200000);
        set_skill("force", 350);
        set_skill("unarmed", 350);
        set_skill("dodge", 350);
        set_skill("parry", 350);
        set_skill("sword", 350);
        set_skill("literate", 150);

        map_skill("force", "taixuan-shengong");
        map_skill("dodge", "taixuan-shengong");
        map_skill("unarmed", "taixuan-shengong");
        map_skill("parry", "taixuan-shengong");
        map_skill("sword", "taixuan-shengong");

        create_family("���͵�",1, "����");
        set("inquiry",([
           "������" :   (: ask_zhou :),
           "���͵�" :  "��������Һ����ֵ������з��ֵġ�\n",
           "�뵺"   :   (: out_xiakedao :),            
        ]));

        setup();
        carry_object("/clone/cloth/cloth")->wear();
        carry_object("/clone/weapon/changjian")->wield();
        add_money("gold", 2);
}

void attempt_apprentice(object ob)
{
        message_vision("ľ��������$N�ļ��΢΢ҡ��ҡͷ��\n", ob);
        return;
}

int accept_object(object who, object ob)
{
        object obn;

        if ( !who || environment(who) != environment() ) return 0;
        if ( !objectp(ob) ) return 0;
        if ( !present(ob, who) ) return notify_fail("��û�����������\n");

        if( (string)ob->query("name") == HIR"���Ʒ�����"NOR )
        {
            if (who->query_skill("taixuan-shengong", 1) > 0)
            {
                 message_vision("$N��$n΢Ц��������λ" + RANK_D->query_respect(who) +
                                "�������͵�Ե�ݲ�ǳ���Ϸ��л�ˣ�\n",
                                this_object(), who);
                 return 1;
            }

            if( (string)ob->query("own") != (string)who->query("id") )
            {
                 message_vision("�ⲻ����Ķ����������������ģ�\n", who);
                 return 0;
            }
            command("say  ԭ����" + (string)who->query("name") + "����" +
                "����ӭ���ٱ�����");
            command("say ����������һ��ʯ�ڣ��Ͽ���̫��������������ȥ������" +
                    "�����ڶ�ʮ�ļ�ʯ�������Ħ��");
            who->set_temp("xiakedao/think", 1);
            return 1;
        }
        else
        {
            message_vision("�Ҳ���Ҫ�ⶫ����\n", who);
            return 0;
        }
}

int ask_zhou()
{
       object me = this_player();
       object ob;

       if (me->query_temp("xiakedao/think"))
       {
           if ( time() - me->query("zhou_time") > 1800 )
           {
                 message_vision("$N����һЦ���������ã�����������ո���ã�" +
                                "��λ" + RANK_D->query_respect(me) + "������" +
                                "ȥ�ɡ���\n", this_object(), me);
                 ob = new("/d/xiakedao/obj/zhou");
                 ob->move(me);
                 message_vision("$N�ó�һ��" + ob->name() +
                                "��$n��\n", this_object(), me);
                 me->set("zhou_time", time());
                 return 1;
           } else
           {
                 message_vision("$N��$n��������λ�������������ԭ�Ϻ��Ѳɵ���" +
                                "���ڻ�û�С���\n", this_object(), me);
                 return 1;
           }
       } else
       {
           message_vision("$N��$n���������Ǳ������еĶ���������Ҫ��һζ" +
                          "���ϳ�ʴ�Ǹ��Ĳݡ����ɣ�Ҫ������Ч��������\n" +
                          "�����ֲ�ÿʮ��ſ�һ�λ������������������" +
                          "һ���˺��ѵõ��ġ�\n" + RANK_D->query_respect(me) +
                          "��Ҫ����Ҫ�����Ե���ˣ���\n", this_object(), me);
           return 1;
       }
}

int out_xiakedao()
{
   object me=this_player();
   if (me->query("baohu_xiakedao"))
   {
           message_vision("$Nһ��̾Ϣ������$n�������˵������" + me->name(1) +
                          "��Ҫ��ס�����߽�����һ�ж���С�Ľ��������ǡ���Ϸ�·������һ����" +
                          "�´Σ�δ�����Ҿ������Ե�֣�һ�ж��Լ������ˣ���\n",
                                       this_object(), me);
           me->delete("baohu_xiakedao");
           me->move(REVIVE_ROOM);
           return 1;
   }
   message_vision("$N���ȵĿ�����һ�ۣ�������˵������" + me->name(1) +
                  "�����Ȼ���������͵�������Ҫ�Ϸ��������ô�뵺ô����Ȼ���ﶴ��·�ԣ�" +
                  "����Ҳ���㲻��������\n",this_object(), me);
   return 1;   
}


