// tongji.c ��������ͳ��
 
inherit F_CLEAN_UP;
#include <ansi.h>

#define MORE_THAN 0
#define LESS_THAN 1
#define BETWEEN 0
#define OUTOF 1

void more_or_less(string para, string tar, int n_data, int flag);
void between_or_outof(string para, string tar, int less, int more, int flag);
void same_as(string para, string tar, string str_data, int n_data);

int main(object me, string arg)
{
        string para, cond, str_data, tar;
        int n_data, less, more;
        string* temp;

        if (! SECURITY_D->valid_grant(me, "(admin)"))
                return 0;

        if (! arg || sscanf(arg, "%s %s %s %s", para, tar, cond, str_data) != 4)
		return notify_fail("tongji < ���� -sk|-para|-tpara > <�������> < ���� <|==|>|between|outof > <ͳ��ֵ> \n");

        temp = explode(str_data, " ");

        if (sizeof(temp) == 1)
                sscanf(str_data, "%d", n_data);

        else sscanf(str_data, "%d %d", less, more);
        
        if (para != "-sk" && para != "-para" && para != "-tpara")
                return notify_fail("tongji < ���� -sk|-para|-tpara > <�������> < ���� <|==|>|between|outof > <ͳ��ֵ> \n");

        switch(cond)
        {
              case ">":
                  more_or_less(para, tar, n_data, MORE_THAN);
                  break;

              case "<":
                  more_or_less(para, tar, n_data, LESS_THAN);
                  break;
              
              case "==":
                  same_as(para, tar, str_data, n_data);
                  break;

              case "between":
                  between_or_outof(para, tar, less, more, BETWEEN);
                  break;

              case "outof":
                  between_or_outof(para, tar, less, more, OUTOF);
                  break;

              default:
                  return notify_fail("tongji < ���� -sk|-para|-tpara > <�������> < ���� <|==|"
                                     ">|between|outof > <ͳ��ֵ> \n");

        }

        return 1;
}

void more_or_less(string para, string tar, int n_data, int flag)
{
        object *obs;
        int i = 0, j = 0;

        obs = all_interactive();
        write(sprintf(HIC "\nͳ�ƽ���б�\n" NOR));
        write(HIW "�ԡ���������������������������������������������������������������������������������������\n" NOR);

        switch(para)
        {
              case "-sk":
                 if (file_size("/kungfu/skill/" + tar + ".c") == -1)
                 {
                       write("û�� " + to_chinese(tar) + " ���ּ��ܡ�\n");
                       return ;
                 }
                 for (i = 0; i < sizeof(obs); i ++)
                 {
                       if (flag == MORE_THAN && obs[i]->query_skill(tar, 1) <= n_data)
                                continue;

                       if (flag == LESS_THAN && obs[i]->query_skill(tar, 1) >= n_data)
                                continue;
                       
                       write(sprintf(HIC "��ң�%s(%-5s) " HIW "    |    " HIC "  ͳ����Ŀ��%s  " HIW 
                             "    |    " HIC  "  �����%d\n" NOR, 
                             obs[i]->name(), 
                             obs[i]->query("id"), 
                             to_chinese(tar), 
                             obs[i]->query_skill(tar, 1)));
                       j ++;
                       
                 }
                 break;
                 
              case "-para":
                 for (i = 0; i < sizeof(obs); i ++)
                 {
                       if (! intp(obs[i]->query(tar)) &&
                           ! floatp(obs[i]->query(tar)))
                               continue;

                       if (flag == MORE_THAN && obs[i]->query(tar) <= n_data)
                                continue;
                       
                       if (flag == LESS_THAN && obs[i]->query(tar) >= n_data)
                                continue;

                       write(sprintf(HIC "��ң�%s(%-5s) " HIW "    |    " HIC "  ͳ����Ŀ��%s  " HIW 
                             "    |    " HIC "  �����%d\n" NOR, 
                             obs[i]->name(), 
                             obs[i]->query("id"), 
                             tar, 
                             obs[i]->query(tar)));
                       
                       j ++;
                 }
                 break;
                 
              case "-tpara":
                 for (i = 0; i < sizeof(obs); i ++)
                 {
                       if (! intp(obs[i]->query_temp(tar)) &&
                           ! floatp(obs[i]->query_temp(tar)))
                               continue;

                       if (flag == MORE_THAN && obs[i]->query_temp(tar) <= n_data)
                                continue;

                       if (flag == LESS_THAN && obs[i]->query_temp(tar) >= n_data)
                                continue;
                       
                       write(sprintf(HIC "��ң�%s(%-5s) " HIW "    |    " HIC "  ͳ����Ŀ��%s  " HIW 
                             "    |    " HIC "  �����%d\n" NOR, 
                             obs[i]->name(), 
                             obs[i]->query("id"), 
                             tar, 
                             obs[i]->query_temp(tar)));
               
                       j ++;
                       
                 }
                 break;     
        }
        write(HIG "�ܹ� " + j + " ����Ŀ��\n" NOR);
        write(HIW "�ԡ���������������������������������������������������������������������������������������\n\n" NOR);
        return;
}

void between_or_outof(string para, string tar, int less, int more, int flag)
{
        object *obs;
        int i = 0, j = 0;

        obs = all_interactive();
        write(sprintf(HIC "\nͳ�ƽ���б�\n" NOR));
        write(HIW "�ԡ���������������������������������������������������������������������������������������\n" NOR);

        switch(para)
        {
              case "-sk":
                 if (file_size("/kungfu/skill/" + tar + ".c") == -1)
                 {
                       write("û�� " + to_chinese(tar) + " ���ּ��ܡ�\n");
                       return ;
                 }
                 for (i = 0; i < sizeof(obs); i ++)
                 {
                       if (flag == BETWEEN && 
                           (obs[i]->query_skill(tar, 1) <= less ||
                           obs[i]->query_skill(tar, 1) >= more))
                                continue;

                       if (flag == OUTOF && 
                           (obs[i]->query_skill(tar, 1) >= less &&
                           obs[i]->query_skill(tar, 1) <= more))
                                continue;
                       
                       write(sprintf(HIC "��ң�%s(%-5s) " HIW "    |    " HIC "  ͳ����Ŀ��%s  " HIW 
                             "    |    " HIC  "  �����%d\n" NOR, 
                             obs[i]->name(), 
                             obs[i]->query("id"), 
                             to_chinese(tar), 
                             obs[i]->query_skill(tar, 1)));
                       
                       j ++;
                 }
                 break;
                 
              case "-para":
                 for (i = 0; i < sizeof(obs); i ++)
                 {
                       if (! intp(obs[i]->query(tar)) &&
                           ! floatp(obs[i]->query(tar)))
                               continue;

                       if (flag == BETWEEN && 
                           (obs[i]->query(tar) <= less ||
                           obs[i]->query(tar) >= more))
                                continue;

                       if (flag == OUTOF && 
                           (obs[i]->query(tar) >= less &&
                           obs[i]->query(tar) <= more))
                                continue;

                       write(sprintf(HIC "��ң�%s(%-5s) " HIW "    |    " HIC "  ͳ����Ŀ��%s  " HIW 
                             "    |    " HIC "  �����%d\n" NOR, 
                             obs[i]->name(), 
                             obs[i]->query("id"), 
                             tar, 
                             obs[i]->query(tar)));

                       j ++;
                 }
                 break;
                 
              case "-tpara":
                 for (i = 0; i < sizeof(obs); i ++)
                 {
                       if (! intp(obs[i]->query_temp(tar)) ||
                           ! floatp(obs[i]->query_temp(tar)))
                               continue;

                       if (flag == BETWEEN && 
                           (obs[i]->query_temp(tar) <= less ||
                           obs[i]->query_temp(tar) >= more))
                                continue;

                       if (flag == OUTOF && 
                           (obs[i]->query_temp(tar) >= less &&
                           obs[i]->query_temp(tar) <= more))
                                continue;

                       write(sprintf(HIC "��ң�%s(%-5s) " HIW "    |    " HIC "  ͳ����Ŀ��%s  " HIW 
                             "    |    " HIC "  �����%d\n" NOR, 
                             obs[i]->name(), 
                             obs[i]->query("id"), 
                             tar, 
                             obs[i]->query_temp(tar)));

                       j ++;
                 }
                 break;

        }
        write(HIG "�ܹ� " + j + " ����Ŀ��\n" NOR);
        write(HIW "�ԡ���������������������������������������������������������������������������������������\n\n" NOR);
        return;
}

void outof(string para, string tar, int less, int more)
{
        object *obs;
        int i = 0, j = 0;

        obs = all_interactive();
        write(sprintf(HIC "\nͳ�ƽ���б�\n" NOR));
        write(HIW "�ԡ���������������������������������������������������������������������������������������\n" NOR);

        switch(para)
        {
              case "-sk":
                 if (file_size("/kungfu/skill/" + tar + ".c") == -1)
                 {
                       write("û�� " + to_chinese(tar) + " ���ּ��ܡ�\n");
                       return ;
                 }
                 for (i = 0; i < sizeof(obs); i ++)
                 {
                       if (obs[i]->query_skill(tar, 1) >= less &&
                           obs[i]->query_skill(tar, 1) <= more)
                                continue;
                       
                       write(sprintf(HIC "��ң�%s(%-5s) " HIW "    |    " HIC "  ͳ����Ŀ��%s  " HIW 
                             "    |    " HIC  "  �����%d\n" NOR, 
                             obs[i]->name(), 
                             obs[i]->query("id"), 
                             to_chinese(tar), 
                             obs[i]->query_skill(tar, 1)));
                       
                       j ++;
                 }
                 break;
                 
              case "-para":
                 for (i = 0; i < sizeof(obs); i ++)
                 {
                       if (! intp(obs[i]->query(tar)) &&
                           ! floatp(obs[i]->query(tar)))
                               continue;

                       if (obs[i]->query(tar) >= less &&
                           obs[i]->query(tar) <= more)
                                continue;

                       write(sprintf(HIC "��ң�%s(%-5s) " HIW "    |    " HIC "  ͳ����Ŀ��%s  " HIW 
                             "    |    " HIC "  �����%d\n" NOR, 
                             obs[i]->name(), 
                             obs[i]->query("id"), 
                             tar, 
                             obs[i]->query(tar)));

                       j ++;
                 }
                 break;
                 
              case "-tpara":
                 for (i = 0; i < sizeof(obs); i ++)
                 {
                       if (! intp(obs[i]->query_temp(tar)) &&
                           ! floatp(obs[i]->query_temp(tar)))
                               continue;

                       if (obs[i]->query_temp(tar) >= less &&
                           obs[i]->query_temp(tar) <= more)
                                continue;

                       write(sprintf(HIC "��ң�%s(%-5s) " HIW "    |    " HIC "  ͳ����Ŀ��%s  " HIW 
                             "    |    " HIC "  �����%d\n" NOR, 
                             obs[i]->name(), 
                             obs[i]->query("id"), 
                             tar, 
                             obs[i]->query_temp(tar)));

                       j ++;
                 }
                 break;

        }
        write(HIG "�ܹ� " + j + " ����Ŀ��\n" NOR);;
        write(HIW "�ԡ���������������������������������������������������������������������������������������\n\n" NOR);
        return;
}
void same_as(string para, string tar, string str_data, int n_data)
{
        object *obs;
        int i = 0, j = 0;
        int types;

        obs = all_interactive();
        write(sprintf(HIC "\nͳ�ƽ���б�\n" NOR));
        write(HIW "�ԡ���������������������������������������������������������������������������������������\n" NOR);

        switch(para)
        {
              case "-sk":
                 if (file_size("/kungfu/skill/" + tar + ".c") == -1)
                 {
                       write("û�� " + to_chinese(tar) + " ���ּ��ܡ�\n");
                       return ;
                 }
                 for (i = 0; i < sizeof(obs); i ++)
                 {
                       if (obs[i]->query_skill(tar, 1) != n_data)
                                continue;
                       
                       write(sprintf(HIC "��ң�%s(%-5s) " HIW "    |    " HIC "  ͳ����Ŀ��%s  " HIW 
                             "    |    " HIC  "  �����%d\n" NOR, 
                             obs[i]->name(), 
                             obs[i]->query("id"), 
                             to_chinese(tar), 
                             obs[i]->query_skill(tar, 1)));

                       j ++;
                       
                 }
                 break;
                 
              case "-para":
                 // �����ж�ͳ�ƶ��󷵻ص�����
                 for (i = 0; i < sizeof(obs); i ++)
                 {
                      if (stringp(obs[i]->query(tar)))
                      {
                            types = 1;
                            break;
                      }
                      if (intp(obs[i]->query(tar)) ||
                          floatp(obs[i]->query(tar)))
                      {
                            // �ٴ��жϱ�֤������ȷ
                            if (! obs[i]->query(tar) &&
                                str_data != "0")
                            {
                                 types = 1; 
                                 break;
                            }
                            types = 2;
                            break;
                      }
                      
                 }
                 if (! types)
                 {
                       write("ͳ�ƶ���ķ�������ֻ��Ϊ �ַ��������ͺ͸����͡�\n" NOR);
                       write(HIW "�ԡ���������������������������������������������������������"
                             "������������������������������\n\n" NOR);
                       return;
                 }

                 for (i = 0; i < sizeof(obs); i ++)
                 {
                       if (types == 1)
                       {

                            if (! stringp(obs[i]->query(tar)) ||
                                obs[i]->query(tar) != str_data)
                                    continue;
                       }
                       else
                       {
                            if (! obs[i]->query(tar) &&
                                obs[i]->query(tar) != n_data)
                                    continue;

                            if (obs[i]->query(tar) != n_data)
                                    continue;
                       }
                       
                       if (types == 1)
                       {
                             write(sprintf(HIC "��ң�%s(%-5s) " HIW "    |    " HIC "  ͳ����Ŀ��%s  " HIW 
                                   "    |    " HIC "  �����%s\n" NOR, 
                                   obs[i]->name(), 
                                   obs[i]->query("id"),
                                   tar, 
                                   obs[i]->query(tar)));
                       }
                       else 
                       {
                             write(sprintf(HIC "��ң�%s(%-5s) " HIW "    |    " HIC "  ͳ����Ŀ��%s  " HIW 
                                   "    |    " HIC "  �����%d\n" NOR, 
                                   obs[i]->name(), 
                                   obs[i]->query("id"), 
                                   tar, 
                                   obs[i]->query(tar)));

                             j ++;

                       }
                 }
                 break;

              case "-tpara":
                 // �����ж�ͳ�ƶ��󷵻ص�����
                 for (i = 0; i < sizeof(obs); i ++)
                 {
                      if (stringp(obs[i]->query_temp(tar)))
                      {
                            types = 1;
                            break;
                      }
                      if (intp(obs[i]->query_temp(tar)) ||
                          floatp(obs[i]->query_temp(tar)))
                      {
                            // �ٴ��жϱ�֤������ȷ
                            if (! obs[i]->query_temp(tar) &&
                                str_data != "0")
                            {
                                 types = 1; 
                                 break;
                            }
                            types = 2;
                            break;
                      }
                      
                 }
                 if (! types)
                 {
                       write("ͳ�ƶ���ķ�������ֻ��Ϊ �ַ��������ͺ͸����͡�\n" NOR);
                       write(HIW "�ԡ���������������������������������������������������������"
                             "������������������������������\n\n" NOR);
                       return;
                 }

                 for (i = 0; i < sizeof(obs); i ++)
                 {
                       if (types == 1)
                       {

                            if (! stringp(obs[i]->query_temp(tar)) ||
                                obs[i]->query_temp(tar) != str_data)
                                    continue;
                       }
                       else
                       {
                            if (! obs[i]->query_temp(tar) &&
                                obs[i]->query_temp(tar) != n_data)
                                    continue;

                            if (obs[i]->query_temp(tar) != n_data)
                                    continue;
                       }
                       
                       if (types == 1)
                       {
                             write(sprintf(HIC "��ң�%s(%-5s) " HIW "    |    " HIC "  ͳ����Ŀ��%s  " HIW 
                                   "    |    " HIC "  �����%s\n" NOR, 
                                   obs[i]->name(), 
                                   obs[i]->query("id"),
                                   tar, 
                                   obs[i]->query_temp(tar)));
                       }
                       else 
                       {
                             write(sprintf(HIC "��ң�%s(%-5s) " HIW "    |    " HIC "  ͳ����Ŀ��%s  " HIW 
                                   "    |    " HIC "  �����%d\n" NOR, 
                                   obs[i]->name(), 
                                   obs[i]->query("id"), 
                                   tar, 
                                   obs[i]->query_temp(tar)));

                             j ++;

                       }
                 }
                 break;                 

        }
        write(HIG "�ܹ� " + j + " ����Ŀ��\n" NOR);
        write(HIW "�ԡ���������������������������������������������������������������������������������������\n\n" NOR);
        return;
}
int help(object me)
{
  write(@HELP
ָ���ʽ : tongji < ���� -sk|-para|-tpara > <�������> < ���� <|==|>|between|outof > <ͳ��ֵ>

           ���� -sk ����ͳ���书���ܣ��磺tongji -sk dodge > 200 ��ʾ
           ��ʾ������ dodge �������ٵ�����б�

           ���� -para ����ͳ��������ݣ��磺tongji -para age > 40 ��ʾ
           ��ʾ�����������ʮ������б�
           
           ���� -tpara ����ͳ�������ʱ���ݣ��磺tongji -tpara apply/amore < 100 ��ʾ
           ��ʾ����������һ�ٵ�����б�

           ���� between ����ͳ��ĳ�����ݶε����ݣ��磺tongji -para age between 20 70 ��ʾ
           ��ʾ�������ڶ�ʮ����ʮ֮�������б�

           ���� outof ����ͳ��ĳ�����ݶ�������ݣ��磺tongji -para age outof 20 70 ��ʾ
           ��ʾ�������ڶ�ʮ����ʮ֮�������б�

��ָ����Ը�����Ҫ��������ͳ�ƣ�����ͳһ�����ά����
HELP );
    return 1;
}
