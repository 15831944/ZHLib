#include <ansi.h>

inherit CLASS_D("generate") + "/chinese";

void random_move();

void create()
{
        mapping my;

        ::create();
        set("gender", "����" );
        set("age", 30 + random(30));
        set("long", "");
        set("attitude", "friendly");
        set("chat_chance", 30);
        set("chat_msg", ({ (: random_move :) }));
        set("scale", 150);
        set_temp("apply/armor", 80);
        set_temp("apply/damage", 60);
        set_temp("born_time", time());

        NPC_D->init_npc_skill(this_object(), 8 + random(3));

        // ��ʼ��NPC������
        my = query_entire_dbase();
        my["max_qi"] = 2000;
        my["max_jing"] = 2000;
        my["max_neili"] = 2000;
        my["eff_jing"] = my["max_jing"];
        my["jing"] = my["max_jing"];
        my["eff_qi"] = my["max_qi"];
        my["qi"] = my["max_qi"];
        my["neili"] = my["max_neili"] * 2;
}

int accept_fight(object ob)
{
        command("say �ҿ�û��Ȥ�����棬����ҹ�����");
        return 0;
}

int accept_hit(object ob)
{
        message_vision(HIR "$N" HIR "��ɫһ�䣬����һ��ɱ�����ȵ�������"
                       "һ��" + RANK_D->query_rude(ob) + HIR "�����ɣ�"
                       "��\n" NOR, this_object());
        kill_ob(ob);
        return 1;
}

int accept_kill(object ob)
{
        if (! living(this_object()))
                return 1;

        return accept_hit(ob);
}

int accept_ansuan(object ob)
{
        return notify_fail("���˾����Ժøߣ����������֡�\n");
}

int accept_touxi(object ob)
{
        return notify_fail("���˾����Ժøߣ����������֡�\n");
}

void random_move()
{
        NPC_D->random_move(this_object());
}

void remove()
{
        if (! environment() || query_temp("die"))
        {
                ::remove();
                return;
        }

        if (! living(this_object()))
        {
                message_vision(WHT "ֻ��һ����Ӱ�����������Բ��ѵ�$N"
                               WHT "����һ�����ݣ���ʧ����Ӱ���١�"
                               "\n" NOR, this_object());
                return;
        }

        message_vision(WHT "$N" WHT "�����ؿ��˿����ܣ�����ææ����"
                       "�ˡ�\n" NOR, this_object());

        ::remove();
}

void die(object killer)
{
        object ob;
        int exp, pot, ww, sc;

        exp = random(100) + 50;
        pot = random(30) + 20;
        ww = random(10) + 10;
        sc = random(25) + 20;

        if ((objectp(ob = killer)
           || objectp(ob = query_last_damage_from()))
           && ob->query_temp("capture/" + this_object()->query("id")))
        {
                ob->add("combat_exp", exp);
                ob->add("potential", pot);
                ob->add("score", sc);
                ob->add("weiwang", ww);
                ob->delete_temp("capture/" + this_object()->query("id"));
                tell_object(ob, HIC "��Ϊ���������ų��켺�������" + chinese_number(exp) +
                                "�㾭�顢" + chinese_number(pot) + "��Ǳ�ܡ�" + chinese_number(sc)
                                + "�㽭��\n�����Լ�" + chinese_number(ww) + "�㽭��������\n" NOR );

                CHANNEL_D->do_channel(this_object(), "rumor", "��˵"
                                      + ob->name(1) + "(" + ob->query("id") +
                                      ")��" + environment()->short() + "Ϊ��"
                                      "�����ɻ�����" + name() + "��");
        }
        set_temp("die", 1);
        ::die(killer);
}
