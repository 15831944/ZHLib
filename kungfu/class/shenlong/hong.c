// hong.c �鰲ͨ

#include <ansi.h>
#include "shenlong.h"

inherit NPC;
inherit F_UNIQUE;
inherit F_MASTER;
inherit F_COAGENT;
inherit F_QUESTER;

mixed ask_me();
mixed ask_yx();

void create()
{
        set_name("�鰲ͨ", ({ "hong antong", "hong" }));
        set("title",  HIY "������" NOR "����" );
        set("nickname", HIR "�����ɸ�" NOR);
        set("long", "�������书����������˵�̸֮ɫ��������̽����鰲ͨ��\n");
        set("gender", "����");
        set("age", 50);
        set("attitude", "friendly");

        set("str", 32);
        set("int", 35);
        set("con", 31);
        set("dex", 32);

        set("max_qi", 6000);
        set("max_jing", 3000);
        set("neili", 6800);
        set("max_neili", 6800);
        set("jiali", 100);
        set("combat_exp", 2200000);
        set("shen_type", -1);

        set_skill("finger",280);
        set_skill("force", 250);
        set_skill("shenlong-xinfa", 250);
        set_skill("busi-shenlong",260);
        set_skill("dodge", 230);
        set_skill("yixingbu", 230);
        set_skill("hand", 240);
        set_skill("shenlong-bashi", 240);
        set_skill("strike", 240);
        set_skill("shenlong-jian",250);
        set_skill("yingxiong-sanzhao",260);
        set_skill("huagu-mianzhang", 240);
        set_skill("parry", 250);
        set_skill("staff", 250);
        set_skill("sword", 250);
        set_skill("shedao-qigong", 250);
        set_skill("literate", 220);
        set_skill("medical", 270);
        set_skill("shenlong-mixin", 270);

        map_skill("force", "shenlong-xinfa");
        map_skill("dodge", "yixingbu");
        map_skill("hand", "shenlong-bashi");
        map_skill("strike", "huagu-mianzhang");
        map_skill("parry", "shedao-qigong");
        map_skill("staff", "shedao-qigong");
        map_skill("sword", "shenlong-jian");
        map_skill("finger", "yingxiong-sanzhao");

        prepare_skill("strike", "huagu-mianzhang");
        prepare_skill("hand", "shenlong-bashi");

        create_family("������", 1, "����");

        set("inquiry", ([
                "������" :  "һ�������벻���������̵�(join shenlongjiao)��\n",
                "���"   :  "һ�������벻���������̵�(join shenlongjiao)��\n",
                "�鰲ͨ" :  "�㲻������ǲ���?\n",
                "����"   :  "�Ҿ��������̽�����\n",
                "Ӣ������"   : (: ask_yx :),
                "����"   : (: ask_me :),
                "������" : (: ask_me :),
        ]));
        set("chat_chance_combat", 50);  
        set("chat_msg_combat", ({
                (: command("chat ƾ����" + RANK_D->query_rude(this_player()) +
                           "��Ҳ����̫��үͷ�϶�����") :),
                (: perform_action, "staff.chang" :),
                (: perform_action, "staff.chang" :),
                (: perform_action, "staff.chang" :),
                (: perform_action, "staff.chen" :),
                (: perform_action, "staff.chen" :),
                (: perform_action, "staff.chen" :),
                (: perform_action, "staff.fei" :),
                (: perform_action, "staff.fei" :),
                (: perform_action, "staff.fei" :),
                (: exert_function, "recover" :),
                (: exert_function, "recover" :),
        }));
        setup();
        carry_object("/clone/weapon/gangzhang")->wield();
        carry_object("/clone/misc/cloth")->wear();
        add_money("silver", 35);
}

int do_flatter(string arg)
{
        if (! this_player()->query_temp("pending/flatter"))
        {
                command("say ��������ʲô���������ķ����ҵġ�");
                return 0;
        }

        if (! arg ) return notify_fail("��˵��ʲô��\n");

        this_player()->set_temp("pending/flatter", 0);
        message_vision(CYN "$N����˵����" + arg + "\n" NOR,
                       this_player());

        if (strsrch(arg, "���겻��") >=0 && (strsrch(arg, "�����ɸ�") >=0 &&
            strsrch(arg, "��������") >=0 && strsrch(arg, "������ʥ") >=0))
        {
                command("smile");
                command("say �⻹��ࡣ\n");
                command("recruit " + this_player()->query("id"));
        } else
        {
                command("say ����˲����ҷ�����������������㣿!");
                kill_ob(this_player());
        }
        return 1;
}

// ���겻��,�����ɸ�,��������,������ʥ
void die()
{
        message_vision("\n$N���������,��Ȼ������ɱ����,....��"
                       "˵���������۵������ˡ�\n", this_object());
        ::die();
}

void init()
{
        object ob;

        ::init();

        if (interactive(ob = this_player()) && ! is_fighting())
        {
                remove_call_out("greeting");
                call_out("greeting", 4, ob);
        }
        add_action("do_flatter", "flatter");
        add_action("do_join", "join");
}

void greeting(object ob)
{
        object obj;
        if (! objectp(ob)) return;
        if (interactive(ob) && objectp(obj = present("used gao", ob)))
        {
                set("combat_exp", 1000000);
                set("qi", 500);
                set("jing", 500);
        }
}

mixed ask_me()
{
        object me;

        me = this_player();
        if (me->query("can_perform/shedao-qigong/fei"))
                return "�Լ�����������������ǰ���£�";

        if (me->query("family/family_name") != query("family/family_name"))
                return "�����Ķ����ģ���������";

        if (me->query("shen") > -40000)
                return "����ֶλ����������ҿɲ��ܴ�������У�";

        if (me->query_skill("shedao-qigong", 1) < 100)
                return "����ߵ��湦ѧ����ô��������˼�����ң�";

        message_vision(HIM "$n" HIM "��ͷ������������ˣ���˵����"
                       "��Ϊ������ৡ����������������������ѽ���"
                       "�֣������������\n" NOR,
                       me, this_object());
        command("say ���úܼ򵥣������㶮��û�У�");
        tell_object(me, HIG "��ѧ���˷�������\n" NOR);
        if (me->can_improve_skill("sword"))
                me->improve_skill("sword", 90000);
        me->set("can_perform/shedao-qigong/fei", 1);
        return 1;
}

mixed ask_yx()
{
        object me;

        me = this_player();
        if (me->query("can_perform/yingxiong-sanzhao/cansanzhao"))
                return "�Լ�����������������ǰ���£�";

        if (me->query("family/family_name") != query("family/family_name"))
                return "�����Ķ����ģ���������";

        if (me->query("shen") > -40000)
                return "����ֶλ����������ҿɲ��ܴ�������У�";

        if (me->query_skill("yingxiong-sanzhao", 1) < 100)
                return "���Ӣ������ѧ����ô��������˼�����ң�";

        message_vision(HIM "$n" HIM "��ͷ������������ˣ������ڽ������п˵�֮������\n"
                          "------��������\n"
                          "------����ٶ�\n"
                          "------³�����\n"
                       "˵�ձ�һ�߱Ȼ���һ�ߺ����⣡\n" NOR,
                       me, this_object());
        command("say ���úܼ򵥣������㶮��û�У�");
        tell_object(me, HIG "��ѧ��Ӣ�����С�\n" NOR);
        if (me->can_improve_skill("finger"))
                me->improve_skill("finger", 90000);
        me->set("can_perform/yingxiong-sanzhao/cansanzhao", 1);
        return 1;
}


void attempt_apprentice(object ob)
{
        if (ob->query("party/party_name") != "������")
        {
                command("say �㲻�Ǳ��̽���, ����������!");
                return;
        }

        if ((int)ob->query("shen") > -1000)
        {
                command("say �ֳ����ɽ��ҪͶ��״���㲻ɱ��"
                        "���׵�������ô��ʾ���ģ���");
                return;
        }

        if (ob->query_temp("pending/flatter"))
        {
                command("say ����˲����ҷ�����������������㣿");
                kill_ob(ob);
                return 0;
        } else
        {
                command("say �Һ鰲ͨ�������������ʥ����ô������");
                message_vision("�鰲ͨ΢��˫�ۣ������룬һ��"
                               "��������(flatter)�����ӡ�\n",
                               this_player());
                ob->set_temp("pending/flatter", 1);
                return 0;
        }
}


