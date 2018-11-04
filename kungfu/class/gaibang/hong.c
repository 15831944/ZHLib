//hong.c
//modified apprentice conditions for hx

#include <ansi.h>

inherit NPC;
inherit F_MASTER;
inherit F_QUESTER;

int try_to_learn_ds();
int try_to_learn_db();
mixed ask_me();

void create()
{
        set_name("���߹�", ({"hong qigong", "hong", "qigong"}));
        set("nickname", "��ָ��ؤ");
        set("gender", "����");
        set("age", 75);
        set("long", 
"��һ�ų����������΢�룬���ִ�ţ������·���һ����һ��Ĵ����˲�����
ȴϴ�øɸɾ��������ϸ��Ÿ������Ĵ��«��\n");
        set("attitude", "peaceful");
        set("str", 37);
        set("int", 31);
        set("con", 33);
        set("dex", 32);
        set("rank", 10);
        set("chat_chance", 1);
        set("chat_msg", ({
                "���߹�̾�˿�����������������ʱ���ٳԵ��ض����ġ��л�������������\n",
                "���߹�˵�������׻�˵�����ڽ��ϡ��������Ͻл��ص��������ݿ�������\n",
                "���߹��૵���������ؤ��ġ�����ʮ���ơ���������Ե����Ʒ�����\n",
        }));
        set("chat_chance_combat", 1);
        set("chat_msg_combat", ({
                (: perform_action, "strike.xianglong" :),
                (: exert_function, "recover" :),
        }) );
        set("inquiry", ([
                "����" : (: ask_me :),
                "����" : (: ask_me :),
                "�����޹�" : (: ask_me :),
        ]));
        set("book_count",1);
        set("qi", 5200);
        set("max_qi", 5200);
        set("jing", 2700);
        set("max_jing", 2700);
        set("neili", 7000);
        set("max_neili", 7000);
        set("jiali", 120);
        set("combat_exp", 2500000);
        set("score", 50000);

        set_skill("force", 270);
        set_skill("jiaohua-neigong", 250);
        set_skill("huntian-qigong", 270);
        set_skill("unarmed", 230);
        set_skill("changquan", 230);
        set_skill("dodge", 240);
        set_skill("feiyan-zoubi", 240);
        set_skill("parry", 250);
        set_skill("staff", 270);
        set_skill("strike", 270);
        set_skill("dragon-strike", 270);
        set_skill("jiaohua-bangfa", 250);
        set_skill("dagou-bang", 270);
        set_skill("throwing", 220);
        set_skill("mantianhuayu-zhen", 220);
        set_skill("begging", 200);
        set_skill("checking", 200);
        set_skill("training", 180);
        map_skill("throwing", "mantianhuayu-zhen");
        map_skill("force", "huntian-qigong");
        map_skill("unarmed", "changquan");
        map_skill("dodge", "feiyan-zoubi");
        map_skill("parry", "changquan");
        map_skill("staff", "dagou-bang");
        map_skill("strike", "dragon-strike");
        prepare_skill("strike", "dragon-strike");
        set("no_teach", ([
                "dragon-strike" : (: try_to_learn_ds :),
                "dagou-bang"    : (: try_to_learn_db :),
        ]));
        create_family("ؤ��", 17, "����");
        setup();
        carry_object("/d/gaibang/obj/budai")->set_amount(9);
        carry_object("/d/gaibang/obj/budai")->wear();
        carry_object(__DIR__"yuzhu_zhang")->wield();
}

int try_to_learn_db()
{
        object me;
        me = this_player();
        if (me->query("can_learn/dagou-bang"))
                return 0;
        if (me->query("rank") < 9)
        {
                command("say Ҳ����������ʲô���֣���Ȼ��ѧ�򹷰﷨��");
                return -1;
        }
        if (me->query("shen") < -1000)
        {
                command("say ����аħ������֮�������ѧϰ�񹦣�");
                return -1;
        }
        command("sigh");
        command("say �򹷰﷨����ֻ�������������������ڽ��������ң���"
                "Ҳ�Ǳ�����֣�ѧ֮�޷���");
        me->set("can_learn/dagou-bang", 1);
        return 0;
}

int try_to_learn_ds()
{
        object me;
        object sob;
        int i;
        int flag;
        string *sub_skills;
        me = this_player();
        if (me->query("rank") < 9)
        {
                command("say ��Ҫѧ����ʮ���ƣ������������������ﳤ����˵�ɣ�");
                return -1;
        }
        if (me->query("shen") < -1000)
        {
                command("say ��Ȼ����ؤ�ﲻ��ʲô��������������аħ��"
                        "��̫�������ѧϰ�񹦣�");
                return -1;
        }
        sob = find_object(SKILL_D("dragon-strike"));
        if (! sob) sob = load_object(SKILL_D("dragon-strike"));
        if (! sob->valid_learn(me))
                return 0;
        if (me->query_skill("dragon-strike", 1))
        {
                command("say �㲻���Ѿ�����ô���Լ��ú����ɡ�");
                return -1;
        }
        sub_skills = keys(sob->query_sub_skills());
        flag = 0;
        for (i = 0; i < sizeof(sub_skills); i++)
        {
                if (me->query_skill(sub_skills[i], 1) >= 10)
                        continue;
                me->set_skill(sub_skills[i], 10);
                if (! flag)
                {
                        flag = 1;
                        command("say �ã��Ҿͽ�ʮ��·�Ʒ��������㣬"
                                "��Ҫ�ú���ϰ�����ձ����ڻ��ͨ��");
                }
                write(HIC "���" + to_chinese(sub_skills[i]) + "����һ"
                      "Щ����\n" NOR);
        }
        if (! flag)
        {
                command("say ����˵�˴������ڻ��ͨ���������ֽ���");
                return -1;
        }
        command("say �ܺã�������ú��ù�������ʮ��·�Ʒ��ڻ��ͨ����"
                "��Ϊһ��˵�ɡ�");
        notify_fail("�ú�Ŭ�������¹���ɡ�\n");
        return -1;
}

void attempt_apprentice(object ob)
{
        if( ob->query("detach/ؤ��") )
        {
                command("say ��֪���գ��αص�����");
                return 0;
        }
        
        if( ob->query("rank") < 6 )
        {
                command("say �ҿ����ڱ������ʱ�䲻���������������������������Ұɡ�");
                return 0;
        }
        
        if( ob->query("betrayer") )
        {
                command("say С�ӣ���Ҫ�����ҿɾ�Ҫ����ʦ����ѵ��ѵ���ˣ�");
                return 0;
        }

        if( ob->query("family/family_name") &&
            ob->query("family/family_name") != "ؤ��" )
        {
                command("say �٣����Ȼ�Ѿ�������ʦָ�㣬�������Ͻл���ʲô��");
                return 0;
        }

        if ((int)ob->query_str() < 34 || (int)ob->query_con() < 26)
        {
                command("say ���л�����Ҫ�ܳԿ����ͣ����ҿ�" +
                        RANK_D->query_respect(ob) +
                        "�������ƺ����ʺϵ��л��ӣ�");
                return;
        }

        if ((int)ob->query_skill("force") < 200)
        {
                command("sigh");
                command("say ����ڹ����̫���ˣ��Ⱥú������������ҡ�");
                return;
        }

        if ((int)ob->query("max_neili") < 1000)
        {
                command("shake");
                command("say �����ǵ���������ѧ����ʲô�ϳ��书��");
                return;
        }

        ob->set_temp("title", ob->query("title"));
        command("recruit " + ob->query("id"));
        ob->set("title", ob->query_temp("title"));
        ob->delete_temp("title");
        
}

mixed ask_me()
{
        object me,obj;

        me = this_player();

        if (me->query("family/family_name") != query("family/family_name"))
                return "��һ��ȥ��";

        if (me->query_skill("dagou-bang", 1) < 250)
                return "��Ĵ򹷰���ѧ����ô�������ҿ������Զ�أ�";

        if(query("book_count") <1)
                return "�������ˣ��򹷰��ؼ����Ѿ����ȥ�ˡ�";
        obj=new(__DIR__"obj/book.c");
        obj->set("master",me->query("id"));
        obj->move(me);
        tell_object(me,"���߹�˵�������ðɣ��Ȿ�ؼ�����ȥ�ú��о��ɣ���\n");        
       add("book_count",-1);
        return 1;
}
