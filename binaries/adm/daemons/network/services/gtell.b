MUDB��<l*=� include/globals.h include/command.h include/net/dns.h include/net/daemons.h include/net/macros.h include/mudlib.h include/net/daemons.h $ adm/daemons/network/services/gtell.cX  d�        d   K�  0�&	�&	�����  8  �  `  `  `  @  @  @  X  ����        o    8     uh$ u�/h% ul  .<  <  �	
] �    	
z�$     	
z� �	
/$ <h .� ]< �^^l' .;];]�B;B    	
z�^^ ^^;^^� z^^;A ^^;^^ -. �B% �B; �B    	
z� . �B ]<h$ ! �B h "#�B�B <% �B�B0v -$%&�B^'^ �B^(^�B^)^*�B^	^+�B^,^ �B�B.&�B^'^ �B^/^*�B^	^+�B^0^�B^^ .132�B&�B �B*�B+�B ]47�B�B5    	
z�^&�B�6 .�P�  % �3!                             	  
                  @    @     ��d�(�������`�@�@����P����*�A��;���(����� <��E (�y�y�6�	x� �z F�' ��* 8H� <� z��i8<��yXmX�P<� �	�`��������;��<��<��<���@      ���%�     �� feature/clean_up.c feature/dbase.c$ adm/daemons/network/services/gtell.c include/globals.h include/command.h include/net/dns.h include/net/daemons.h include/net/macros.h include/mudlib.h Root     . /adm/daemons/network/dns_master query_mud_name query_mud_info ���Ĳ�û�к� 
  ��ϵ�ϡ�
 | @@@ HOSTADDRESS PORTUDP @@@gtell||NAME:
 ||PORTUDP: query_udp_port ||WIZTO:
 ||WIZFROM: id query ||CNAME: name ||MSG: @@@
 send_udp NAME dns_mudp$ /adm/daemons/network/services/ping_q send_ping_q dns_fake Tell:  WIZFROM @ (
 ) telling  WIZTO MSG 
 aux_log% @@@warning||MSG: Faked gtell message  >  ||FAKEHOST: /cmds/std/tell CNAME remote_tell+ /adm/daemons/network/services/affirmation_a Gtell@ gtell send_affirmation_a incoming_request
 send_gtell� �      �    #        5        "      N  �
��Z�
�������$�������(�����5���
��	�������&��  