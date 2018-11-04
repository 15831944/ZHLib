// banker.c ���м�
// This is a inheritable object.
// Each dealer should support buy, sell, list, value 4 commands
// Updated by Lonely for banghui tax of withdraw

#include <dbase.h>
#include <ansi.h>

int do_check()
{
        // here we use 3 units to display bank infos
        int tax;
        int total = (int)this_player()->query("balance");
        
        tax = (int)environment(this_object())->query("bunch/tax");
                
        if (intp(tax) && tax > 0 && tax < 11)
                write("���̺ŵ�ȡǮ��������Ϊ�ٷ�֮" + chinese_number(tax) + "��\n");       
        else
                write("���̺ŵ�ȡǮ��������Ϊ�ٷ�֮ʮ��\n");      
        
        if (!total || total < 0)
        {
                this_player()->set("balance", 0);
                write("���ڱ��̺�û�д�Ǯ��\n");
                return 1;
        }
        write(this_object()->query("name")+"���ĸ����㣺���ڱ��̺Ź�����" + 
              MONEY_D->money_str(total) + "��\n");
              
        return 1;                                                               
}

int do_convert(string arg)
{
        string from, to;
        int amount, bv1, bv2;
        object from_ob, to_ob;
        object me;

        me = this_player();                                                     

        if (me->is_busy())
                return notify_fail("�㻹�ǵ��п�����˵�ɣ�\n");

        if (this_object()->is_fighting())
                return notify_fail("Ӵ����Ǹ�����������æ���ء��������Ժ�\n");

        if (! arg || sscanf(arg, "%d %s to %s", amount, from, to) != 3)
        {
                return notify_fail("�����ʽ��convert|duihuan <����> <���ҵ�λ> to <�»��ҵ�λ>\n");
        }

        from_ob = present(from + "_money", me);
        to_ob = present(to + "_money", me);

        if (! to_ob && file_size("/clone/money/" + to + ".c") < 0)
                return notify_fail("����һ���ʲô��\n");

        if (! from_ob)
                return notify_fail("������û�д�����Ǯ��\n");

        if (from_ob == to_ob)
                return notify_fail("����ë������\n");

        if (amount < 1)
                return notify_fail("�����׬����\n");

        if ((int)from_ob->query_amount() < amount)
                return notify_fail("�����" + from_ob->query("name") +
                                   "������\n");

        bv1 = from_ob->query("base_value");
        if (! bv1)
                return notify_fail("����������ֵǮ��\n");

        bv2 = to_ob ? to_ob->query("base_value")
                    : call_other("/clone/money/" + to, "query", "base_value");
        if (bv1 < bv2)  amount -= amount % (bv2 / bv1);
        if (amount == 0)
                return notify_fail("��Щ" + from_ob->query("name") +
                                   "��������\n ");

        if (bv1 > bv2 && bv1 / bv2 * amount > 10000)
                return notify_fail("Ŷ��...����һ���ӻ��ò�����ô��ɢǮ...\n");

        // allowed to convert now
        me->start_busy(1);

        from_ob->add_amount(-amount);

        if (! to_ob)
        {
                to_ob = new("/clone/money/" + to);
                to_ob->set_amount(amount * bv1 / bv2);
                to_ob->move(me, 1);
        }
        else
                to_ob->add_amount(amount * bv1 / bv2);

        message_vision(sprintf("$N������ȡ��%s%s%s��������%s%s%s��\n",
                               chinese_number(amount),
                               from_ob->query("base_unit"),
                               from_ob->query("name"),
                               chinese_number(amount * bv1 / bv2),
                               to_ob->query("base_unit"),
                               to_ob->query("name")), me);

        return 1;
}                                                                               

int do_deposit(string arg)                                                      
{
        string what;
        int amount, money_limit;
        object what_ob, me;

        me = this_player();

        if (me->is_busy())
                return notify_fail("�㻹�ǵ��п�����˵�ɣ�\n");

        if (this_object()->is_fighting())
                return notify_fail("Ӵ����Ǹ�����������æ���ء��������Ժ�\n");

        if (! arg || sscanf(arg, "%d %s", amount, what) != 2)
                return notify_fail("�����ʽ��deposit:cun <����> <���ҵ�λ>\n");

        what_ob = present(what + "_money", me);
        if (! what_ob)
                return notify_fail("������û�д�����Ǯ��\n");

        if (amount < 1)
                return notify_fail("��������" + what_ob->query("name") +
                                   "��\n");

        if ((int)what_ob->query_amount() < amount)
                return notify_fail("�����" + what_ob->query("name") +
                                   "������\n");

        // deposit it
        me->start_busy(1);

        me->add("balance", what_ob->query("base_value") * amount);
        what_ob->add_amount(-amount);
        message_vision(sprintf("$N�ó�%s%s%s����������š�\n",
        chinese_number(amount), what_ob->query("base_unit"),
        what_ob->query("name")), me);

        return 1;
}


int do_withdraw(string arg)
{
        string what, banghui;
        int amount, money_limit, tax;
        object what_ob, me, area;
        int v, s;

        me = this_player();

        if (me->is_busy())
                return notify_fail("�㻹�ǵ��п�����˵�ɣ�\n");

        if (this_object()->is_fighting())
                return notify_fail("Ӵ����Ǹ�����������æ���ء��������Ժ�\n");

        if (!arg || sscanf(arg, "%d %s", amount, what) != 2)
                return notify_fail("�����ʽ��withdraw|qu <����> <���ҵ�λ>\n");

        if (amount < 1)
                return notify_fail("����ȡ������Ǯ��\n");

        if(amount >= 10000)
                return notify_fail("��ô�����Ŀ������û��ô����ɢ�ֽ�\n");

        if (file_size("/clone/money/" + what + ".c") < 0)
                return notify_fail("����ȡ��ʲôǮ��\n");

        what = "/clone/money/" + what;
        v = amount * what->query("base_value");
        
        area = environment(this_object());
        if (! area->is_area_room() || ! stringp(area->query("bunch/bunch_name")) ||
            area->query("bunch/npc_file") != base_name(this_object()) ||
            ! intp(area->query("bunch/tax")) || (int)area->query("bunch/tax") < 1 ||     
            (int)area->query("bunch/tax") > 10)     
                tax = v * 1 / 10;
        else
                tax = v * (int)area->query("bunch/tax") / 100;
                
        banghui = (string)this_player()->query("bunch/bunch_name");
        if(! stringp(banghui) || banghui != (string)this_object()->query("bunch/bunch_name")) 
               s = v + tax;
        else
               s = v;
        if (s > me->query("balance") || v <= 0)
               return notify_fail("����Ǯ����ȡ��\n");

        me->start_busy(1);

        me->add("balance",  -s);
        if (s > v && stringp(banghui = this_object()->query("bunch/bunch_name")))
               BUNCH_D->add_info_into_bunch(banghui, "npc_money", tax);
               
        MONEY_D->pay_player(me, v);

        message_vision(sprintf("$N��������ȡ��%s��\n", MONEY_D->money_str(v)), me);

        return 1;
}

int do_tax(string arg)
{
        object me, area;
        string bunch;
        int tax;
        
        me = this_player();
        
        if (! arg || sscanf(arg, "%d", tax) != 1) 
               return notify_fail("��Ҫ�趨�ٷ�֮���ٵ�ȡ�������ѣ�\n"); 

        if (! intp(tax) || tax < 1 || tax > 10)
                return notify_fail("�趨ȡ��������Ҫ���ڰٷ�֮һ�Ͱٷ�֮ʮ֮�䡣\n");
                
        if (! stringp(bunch = me->query("bunch/bunch_name")) ||
            bunch != this_object()->query("bunch/bunch_name"))
                return notify_fail("���̺�û�б�����ƣ�����Ȩ�趨ȡ�������ѡ�\n");
                
        if (me->query("bunch/level") != 9)
                return notify_fail("ֻ�а�������Ȩ���趨�����ȡ�������ѡ�\n");

        area = environment(this_object());
        
        if (! area->is_area_room() || ! stringp(area->query("bunch/bunch_name")) ||
            area->query("bunch/npc_file") != base_name(this_object()))
                return notify_fail("�趨ȡ��������ʧ�ܡ�\n");                
                          
        area->set("bunch/tax", tax);
        area->save();
        
        write("���趨���̺ŵ�ȡǮ��������Ϊ�ٷ�֮" + chinese_number(tax) + "�ɹ���\n");   
        return 1;
}
        
