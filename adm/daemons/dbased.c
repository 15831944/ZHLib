// dbased.c ���ü�������ݿ�(���Լ�¼���еĳ�������Ʒ)
// ���ݿ��е�·����dbaseΪ�����ļ�·��Ϊ;����
// ����/d/city/kedian������󱣴������ݿ��еĽ��ǣ�
// /dbase/d/city/kedian�������������һ��mixed���ͣ��������
// restore���������õ�ʱ�򣬶�����뱣֤��receive_dbase_data
// �����������ձ��������ݿ��е����ݡ� �����󱣴��ʱ�����
// ����save_dbase_data����������Ҫ��������ݡ�

#include <ansi.h>

#pragma optimize
#pragma save_binary

inherit F_SAVE;
inherit F_DBASE;

// �������ݵ�ӳ�����
mapping save_dbase;

// ���ú���announec_all_save_objectʱ��ı�־
#define ONLY_SAVE               0
#define DESTRUCT_OBJECT         1
static  int save_flag = ONLY_SAVE;

// �ڲ����õĺ���
static int announce_all_save_object(int destruct_flag);

// �ṩ���ⲿ�ĺ���
mixed   query_data();
int     set_data(mixed data);
mixed   query_object_data(object ob);
int     set_object_data(object ob, mixed data);
mapping query_save_dbase();
string *query_saved_object();
int     clear_object(mixed ob);
int     remove(string euid);
void    mud_shutdown();

void create()
{
        if (! restore() && ! mapp(save_dbase))
                save_dbase = ([]);

        // auto save per 15 minute (900s)
        set_heart_beat(450 + random(30));
}

// ���ݿ������������
int remove(string euid)
{
        if (previous_object() != find_object(SIMUL_EFUN_OB) ||
            ! is_root(euid))
        {
                // Must be called from simul_efun object
                return 0;
        }

        announce_all_save_object(save_flag);
        return 1;
}

// MUD��Ҫֹͣ����
void mud_shutdown()
{
        save_flag = DESTRUCT_OBJECT;
        destruct(this_object());
}

// ֪ͨ���е���Ҫ�������ݵĶ���
static int announce_all_save_object(int destruct_flag)
{
        object ob;
        string *e;
        int i;

        if (mapp(save_dbase))
                e = keys(save_dbase);
        else
                e = ({ });
        // ֪ͨ���еĴ��̶��󱣴�����
        for (i = 0; i < sizeof(e); i++)
        {
                if (! stringp(e[i]))
                        // ��Ӧ�ò����ַ���
                        map_delete(save_dbase, e[i]);
                else
                if (objectp(ob = find_object(e[i])))
                {
                        // �ҵ��˴��̵Ķ���֪ͨ����
                        if (destruct_flag == DESTRUCT_OBJECT)
                                catch(destruct(ob));
                        else
                                catch(ob->save());
                }
        }

        save();
}

// �����������Զ��������е�����
static int heart_beat()
{
        set_heart_beat(450 + random(30));
        announce_all_save_object(ONLY_SAVE);
}

string query_save_file() { return DATA_DIR + "dbased"; }

// ĳ�������ȡ�Լ��ļ�¼
mixed query_data()
{
        return query_object_data(previous_object());
}

// ĳ����������Լ��ļ�¼
int set_data(mixed data)
{
        return set_object_data(previous_object(), data);
}

// ��ȡĳ������ļ�¼
mixed query_object_data(mixed ob)
{
        int i;
        string index,temp_index;

        if (! ob) return 0;

        // ֻ��ROOT������Լ��ſ��Ա�����ȡ����
        if (! is_root(previous_object()) &&
            previous_object() != ob) return 0;

        if (stringp(ob))
        {
                index = ob;
                sscanf(index, "%s.c", index);
        } else
        if (objectp(ob))
                index = base_name(ob);
        else
                return 0;

        temp_index = index;
        if (objectp(ob) && strlen(temp_index) > 21 && temp_index[0..20] == "/data/gaoshou/weapon/")
        {
                i = strsrch(temp_index,"-");
                if (i != -1) temp_index = temp_index[0..i-1];
                i = strsrch(temp_index,"/",-1);
                if (i != -1) temp_index = temp_index[i+1..strlen(temp_index)-1];
                if (temp_index && strlen(temp_index) > 1)
                        temp_index = "/data/item/" + temp_index[0..0] + "/" + 
                                     temp_index + "-" + ob->query("id");
        }
        if (file_size(temp_index+".c") > 0)
                index = temp_index;
        return save_dbase[index];
}

// ����ĳ������ļ�¼
int set_object_data(mixed ob, mixed data)
{
        string index;

        if (! ob) return 0;

        // ֻ��ROOT������Լ��ſ��Ա�����ȡ����
        if (! is_root(previous_object()) &&
            previous_object() != ob) return 0;

        if (stringp(ob))
        {
                index = ob;
                sscanf(index, "%s.c", index);
        } else
        if (objectp(ob))
                index = base_name(ob);
        else
                return 0;

        if (! data)
        {
                map_delete(save_dbase, index);
                return 1;
        }

        save_dbase[index] = data;
        return 1;
}

// ��ȡ���ж���ļ�¼
mapping query_save_dbase()
{
        return save_dbase;
}

// ���ı��������ݵ����ж���
string *query_saved_object()
{
        return keys(save_dbase);
}

// ���һ������
int clear_object(mixed ob)
{
        string index;
        object xob;

        // ����һ�����������ǰһ��ᱣ���Լ������ݣ�����һ�������ܵ�
        // ������Ҫ�ָ�����Ϊԭʼ״̬��ʱ��ͱ��������������Ȼ��
        // ����������ݡ�

        if (! ob) return 0;

        if (stringp(ob))
        {
                index = ob;
                xob = find_object(index);
        } else
        if (objectp(ob))
        {
                xob = ob;
                index = base_name(xob);
        } else return 0;

        if (! is_root(previous_object()) &&
            previous_object() != xob) return 0;

        if (xob) destruct(xob);
        map_delete(save_dbase, index);
        return 1;
}

int init_object()
{
	save_dbase = ([]);
	save();
}