#include<bits/stdc++.h>
#include<sstream>
#include<fstream>
#include<windows.h>
#include<conio.h>
#include<wchar.h>
#include<locale>
#include<mmsystem.h> 
#include<fstream>
#include<exception>
#pragma comment(lib,"Winmm.lib")
#pragma GCC optimize(3)//��Լ10ms 
using namespace std;
/*δ��wqxͬ���ֹת�� 
2024.2.11 7015
2024.6.28 ���Ӻʹ�����Ľ����ḻһ�� ì��mvbҪ��ʹ֩������ 
2024.7.26 ���ӻֳᷱ�ˣ����԰���������ˡ�֩�����ǿһ�� 
2024.9.15 �Թ�����ӳ�����ɷ�ʽ����֩��ʵ���ƺ���ǿ�� 
2024.10.2 �챻��֩�뱡ɴ�ˡ���򲻵�һ�㣻����һ���ǽ�ڲ��ڿգ��ռ���˵㣬���ڱ��ƼӶ��ˣ�����·���ǲ����� 
2024.10.3 ��ô��ʱ��Ī����������
2024.10.8 ս����ϵ���£�����Ч�����������ƶ��ֿ�
2024.10.9 �о��򲻹�ʯ�����ˣ�Կ��������һ�� 
2024.10.19 ���˸�������Թ����ɷ�ʽ��·��΢��һ�㣬����¥������ 
2024.11.9 ����Կ��������ˣ�����˳��ڴ��ڵĹ�mvb��ס������ 
2025.1.19 �����Ұ�ܵ����Զ�������ƣ���Ǳ���������е��߼����� 
2025.1.24 ��������Ʒ���ļܹ��������Ϊ�����ĸ��´�û�������ķ�Ӧ�ٶ����ӱ����� 
2025.2.1 ��Ѫ���ܹ⣬�ᱻǿ��ɹ��
2025.2.6 ��ì���԰˷��������ȥ�ˣ����ҿ��Դ̵��� 
2025.2.14 ����game_log������־�������� 
2025.2.15 ذ�ס��̽������� 
2025.2.21 �̽��ͳ���ֻ������Ұ��Χ�ڳ��֣������ì��BUG 
2025.3.2 ���������������bug���˰���QwQ�� 
idea:
1.����갴��-��ק-�ɿ��ķ�ʽ����Զ���������Ӷ���
2.����
3.��ɷ��������ڣ���������ֻ����/�ߵ�����
4.��Ĺ������ƶ����׷��룬�����÷�Ӧʱ���ж� 
5.��Ұ�shift���񵲣��öܣ�/���� 
6.���Ը���ϡ��Źֵ��Թ������㷨
7.��Ʒ�����ɲ�Ҫ̫������������ƽ�������ľۼ�����
8.Կ�ײ�Ҫ���Ǿ��ڳ����ظ���
9.Կ������0-9
10.�����ڹؼ�λ��ʹ�������� 
11.������ͨ�����⣨�������ɵģ������Ӹ�������ֵֹķ���
12.���ķ�����ٶȷ����෴ʱ�ٶȼ��� 
13.��������ḻһ�㣬�������Թ�������ʰȡ 
14.����������Ʒ��ʰϵͳ 
15.������ʱ���ٷḻһ������͹�����ʽ��
16.��Ұ�shift�������񣬿��������м������������ӡ����ӵȵ��赲���������� 
17.��ʾ���˵�Ѫ�� 
18.������ 
һ����λ�ƶ�
	��������  ��Ϸ����       ʵ�ʴ�С
	ʱ��      ����           1ms 
	����      ��             1��=2���ַ�
	�¶�      degree         1 degree=1���϶� 
����BUG��¼ 
	1����ͼ���Եǽ���ɴ���
	    1�����졢����ʱ�䣺2022.1
	    2����������
	    	(1)��ͼ�ܳ�16~17�����䣬���䳤5��
	    3���������
	        (1)ǽ����ʾΪ�����ַ���ȫ��/��/����/������ģ����ڣ�
		    (2)�������ݼ�¼���� 
		4������ʱ�䣺2022.7.14ǰ 
	2�����ڱ����������
		1�����졢����ʱ�䣺2022.6.27
		2������������������ڱ���ʱ��char(24~27)�� 
		3���������
			(1)������ 
		4������ʱ�䣺2022.7.10
		   ��������Ϊ�����ַ� 
	3��Կ���ſ���״̬����
		1������ʱ�䣺2022.8
		2������ʱ�䣺2022.9
		3�����������������Ϸ
		4������ԭ�򣺳�ʼ��ʱΧ�Ʒ��������ţ�doors_around_rooms���ĺ���û��������Ϊδ�������˴���Ϸ�д򿪵����ٴ�
			��Ϸʱ����״̬�����ǿ�������ͬһ��λ�õ��ű��ֿ��������Զ���ۼ� 
		5������ʱ�䣺2022.9.30 
	4�������細������
		1������ʱ�䣺2023.4 
		2������ʱ�䣺2022.7.5
		3�����������������Ϸ�Һ�һ�εĵ�ͼû����ȫ����ǰһ�ε�
		4������ԭ�򣺽���ʼ���˵�ǰ�����ͼ�������д��������ڱ�Եǽ�� 
	5����Ļ֡�ʹ���
		1������ʱ�䣺2023.7
		2������������δ֪
		3��������ۣ�������٣�����������϶�ʱ 
	6��Failed to execute
		1��ʱ�䣺2024.2.25
		2��ԭ���ڴ泬�� 
	7��100*100����ͼ��С����ʱ����
		1��ʱ�䣺2024.10.3
		2�����֣����ɻ�ʼ��Ϸ������ʱ���� 
		3��ԭ��
			(1)dis_to_player/exit���ֿյ�ֵΪ0���������������� 
			(2)make_window�ж������ƺ��а�ȫ������
		4������δ���֣��ƺ������� 
������Ϸ��ͼ
	1������綨
		1����һ��λ�û��䳤��/��� 
		2����㣺һ��λ��/�������Σ��Ķ��㣬ÿ�����ĸ�������ڣ�һ������½Ǹ�㣨��ӡ��ʾΪ���ϣ�������Ϊ�˸�
			����(x,y)�����Ͻ�(x,y+1)�����½�(x+1,y)�����Ͻ�(x+1,y+1)
		3����Եǽ������x==1||x==length||y==1||y==width��λ�õļ���
		4�����Σ��ųɳ����ε�һЩλ�õļ��� 
		5�����䣺������һ��������ǽ�ĳ�����2�ľ��ε�һЩλ�õļ��� 
	2����С
		��length�񣬿�width�񣬸�height*2�㣨x��y��z����1��ʼ��ţ�
		1~height��Ϊһ����Ϸ����height+1~height*2��Ϊ��չ�泲������������ӳ�Ѩ���� 
	3������
		1����ܣ��յ�+ǽ+¥��+��Ѩ��
			rand_maze���ɳ�ʼ��ͼ���γ��ض�·��
			fill_dead_endsɾ��һ���ֵ�·
			make_roomȥ����ͼ��һ������������ǽ��ȫ�����/�γ����� 
				������pos_in_room�ļ�¼ 
		2���������make_player
			�����˸�λ������Ҿ���ļ�¼ 
		3�����ɵ���make_enemy
		4��������Ʒmake_thing 
�ġ� ��
	1��Կ����
		1��������4��
		2������
			(1)�������ͨ��ԽԶԽ�ࣩ
			(2)Χ�Ʒ������� 
	2��Կ��
		1��������4�֣���Ӧ�ţ� 
		2������
			(1)�������ͨ��ԽԶԽ�٣�
			(2)����������
			(3)����������
				[1]ģʽ��ȷ����ÿ���ŵ�Կ�׶����ڲ��������ŵ������ȡ��
				[2]ʵ�ַ���
					��׼��
						BFS�����ף�Q��vst
						vector<position_3D> vspace�ѷ��ʡ�û����Ʒ�Ŀյ�	
						vector<position_3D> vdoor[4]�ѷ��ʡ�δ�Ŷ�ӦԿ�׵��ţ����ֱַ��¼�� 
						vector<position_3D> vkind����ѡ����ŵ����� 
					�ڳ�ʼ����
						a.ȫ�����
						b.�����������Ϊ��� 
					���ظ�ִ�У� 
						a.BFS���������ѷ��ʡ��ѷŶ�ӦԿ�׵��ţ��ܵ��ĵط���
						����vspace������������δ���ʵ��Ŷ�����vdoor
						b.Ϊ�´�ѭ��׼�� 
							��4������������Ϊ0�����ȿյض���������vkind 
							������һ���ſ���ѡ�� 
								��vkind�����ȡ��һ���ţ���������ȫ������Q��ȥ����
								��vspace�����ȡ�������������Ŀյط��ö�Ӧ��һ��Կ��
						 	�����˳�ѭ�� 
					ע�⣺����BFS���������ظ������ѷ��ʹ��ĵط���֮ǰѭ����Ҳ���ᣩ��  
		3��ʹ��
			(1)״̬�������������򿪡����رա� 
			(2)��������ʱ�ж�ӦԿ��/���رա�ʱ ���Դ򿪽��룬������Ϊ���򿪡�״̬
			(3)���򿪡�״̬�¿����ߵ���λ�ã����¿ո�����رա������ﲻ��ֱ�ӽ��룩 ����ҿ����Ĵ��ƶ� 
	3��������
		1������Կ�״򿪣���ͨ�����Զ��ر� 
		2����ǽ����ʾ��ͬ 
	4����ת��
		1����С��2*2
		2���������������ת����תʱ������Χ�����п��ƶ���Ʒ������һ����ת
		3��ʾ��ͼ
			��  	����
		  ������	��   
�塢���
	1���ƶ�
		1������ٿ�
			����� ��Ӧ���� ����仯
			��     0        (x,y-1,z) 
			��     1        (x+1,y,z)
			��     2        (x,y+1,z)
			��     3        (x-1,y,z)
			���ƶ���ģʽ�¸ı�λ�ã����ı䳯��ģʽ�½��ı䷽�� 
		2����ײ���
		   ��ʽ�������������������������/�򡭡����͡�������Ȼ�󡭡��������򡭡�����Ȼ�󡭡������� 
			(1)����ǽ��ͣ��
			(2)����������ж�ӦԿ�׾ͽ��ŷ���ͣ�� 
		3�������ƶ�
			(1)�ֶ�����¥�����¿ո������/��¥ �Զ�����¥������¥�ݾ���/��¥
			(2)�������ݾ�����ѡ¥����棬Ȼ���ƶ�����Ӧ¥��
	2�������Ʒ
		��Ʒ��    ��ʰ    ʹ�ã���1��ʹ��1����2��ʹ��2��������    ����Ч������1��Ч��1����2��Ч��2��������
		Կ��      �Զ�    �Զ�                                    ����Ӧ��
		���ڱ���  ��      ��                                      ָ�򵽴���ڵ����·�ߵķ���
		����      ��      ��                                      ������ߣ�ʹ����ܿ�����Զ�ĵط���ʹ�ƶ���Ʒ�ı䷽�� 
		����      ��	  �����ƶ�                                ���ش����������ڵ�������ߣ� 
	3����Ұ����
		1����������¥����/��¥���������ӹ��䣨����Ҫ�޶���Զ���룿��
			ǽ��������һ�㣬�������ⶼ�ܿ���
		2��׼��
			int game_map[][][].in_player_sight������һ�ο������λ�õ�ʱ�䣬��Ϊ��Ϸ��ͼ 
			queue<position_3D> pos_in_sight����Ҫ����Ļ������ʾ��λ�ã���Ϊ��1 
			queue<position_2D> pos_lst_sight�ϴ�����Ļ����ʾ��λ�ã�scr������Ϊ��2
			queue<position_2D> pos_backupλ�ã�scr�����ݣ�Ϊ�»غϵĶ�2��׼������Ϊ��3 
			string print_game_map_pos(position_3D pos)��Ļ������� 
			map<position_2D,string> screen_pos��Ļ�ϵ�λ����ʾ���ݵı��루����print_game_map_pos(kind=3)�� 
			map<position_2D,int> screen_z��Ļ��������Ҫ��ʾ��λ��������¥�㣨z���꣩ 
			position_3Dtoscr��position_scrto3D�ȸ��������ת������ 
			(1)��ʼ����all_assigned����ÿ����Ϸ��ʼʱ���һ��������Щ������screen_zÿ�غ϶�Ҫ�� 
			(2)����ѿ�����
			 	[1]�Ѿ���ǹ���Ϸ��ͼ��[3]
				[2]�����Ϸ��ͼ�����1�����screen_z������ 
				[3]��λ�������λ�ã����screen_z������ 
		3������
			(1)ʮ����
				[1]��飺ʮ�����ӽǣ�ǰ�����ң�+������ӷ�Χ�Ż� 
				[2]�ŵ㣺ʵ�ּ� ȱ�㣺��������ȫ���ã������ﲻ�ܿ���ȫ����Χ 
			    [3]ʵ�ַ���
					���Ȱ�������ڵ�λ�����1�����һ����Ϸ��ͼ
					����4�����������Ұ�����1�����һ����Ϸ��ͼ
						������λ�����߿��Դ������Ͱ��������λ�����1������ѿ���
						��������λ����������������߷����෴�ķ����ϵ�ǰһ��λ�ã�
						���ǰһ��λ�����߿��Դ������Ͱ�����Ӧ���λ�����1������ѿ��� 
			(1)������
				[1]��飺�����λ��Ϊ������BFS����������ǽ�ͼ�¼���ڵ������߷�Χ������ϵ����ǣ������λ�õ��ĸ��
					Ϊԭ�㣩�������ʱ���ȫ�ڵ���λ�ã�ֱ���������߷�Χ�����ڵ�
				[2]�ŵ㣺��Ϊ��ʵ�ļ�������Ұ��ʵ��������� 
				   ȱ�㣺ʱ�临�Ӷ��Ըߣ��о���������13����Ż�������������޴����ӵ����� 
				[3]׼��
					bool occlusion[4][360]��¼���λ��4������ϱ��ڵ������߷�λ�ǣ�0��δ�ڵ���1�����ڵ�
					int cnt_occlusion[4]��¼���λ��4�������δ���ڵ������߷�λ�ǻ�ʣ��������occlusion[0~3]��0���� 
					int calc_angle(position_3D p)����p������λ�õķ�λ�ǣ�0~360�㣩 
					bool invisible(position_3D p)����p�Ƿ񿴲��� 
					void mark_occlusion(position_3D p)���p�ڵ��ĽǶȷ�Χ
					queue<position_3D> visible_stair�����ܿ�����¥�ݵ�λ�� 
					BFS�����ף�Q��vst
					�ֲ�λ�ñ�����u��v��v2 
					��ʼ����assigned����ÿ�μ���ǰocclusion���㣬cnt_occlusion[0~3]����Ϊ360 
					��λ��ö�ٷ�������ʱ�룬���359�㣩��for(int i=��С�Ƕ�;i!=(���Ƕ�+1)%360;i=(i+1)%360)
				[4]ʵ�ַ�����player_calculate_vision2(position_3D pos=player1.pos)��
					�����������Ӳ����vst
					�ڶ���Ϊ�ջ�cnt_occlusion[0~3]��Ϊ0���ᣬ����ȡ������u  
					�۲�����չ���ڣ�������չ��v
					��v������ͼ��Χ���� 
					�ݿ�����v��invisible(v)���ͱ��vst������
					��v�ǲ���͸��λ�ã����occlusion��mark_occlusion(v)��
					��v��Ӳ����vst������Ϸ��ͼ�б�ǣ����� 
					��v��¥�ݣ�����ͨ����λ��v2���visible_stair������ 
					������뿴��¥��/�£�ö��visible_stair��ÿ��λ��u��
					occlusion���㣬cnt_occlusion[0~3]����Ϊ360�� 
					������ͨ����¥�ݿ����ķ�λ�Ƿ�ΧΪ�ɼ���mark_occlusion()���ı�cnt_occlusion��ͬʱȡ��occlusion���� 
					����player_calculate_vision2(u) 
		4����Ļ���£�screen_update��ʱ
			(1)�����2
				[1]ȡ������spos 
				[2]����spos��screen_z�����Ļ�������λ��Ҫ��ӡ��Ϸ��ͼ���ĸ�λ�ã�now_pos�� 
					screen_zû����Ļ���λ�õ���Ϣ�������λ��Ϳ�ڣ�����screen_pos��886 
				[3]�ж� 
					����now_pos����ʾ���ݱ����������Ļ�ϣ�δ���£�����ʾ���ݱ��벻ͬ��
						�������now_pos��print_game_map_pos(now_pos)��������screen_pos
					d.now_pos�����3
			(2)�����1
				[1]ȡ������now_pos
				[2]�����print_game_map_pos(now_pos)��
				[3]position_3Dtoscr(now_pos)�����3 
			(3)��3������ȫ���Ƶ���2 
		5��ģ��Ч�� 
			(1)������֩����������
			(2)����
			(3)��ʾ 
	4����������
		1������ֵ
			(1)��ʼ��100%
			(2)����0�����������Ϸʧ��
		2������ֵ
			(1)��ʼ��100%
			(2)����ƶ�ʱ����1�㣬����<100%��ÿ0.5��ظ�1��
	5������ 
		1��ʳ�� 
			�ȼ�\Ч��  �����ָ�ADDL  �����ظ�ADDS  
			1          +40%          +20%
			2          +20%          +10%
			3		   +10%          +5%
									���ָ������ޣ�
		2��͸��
			�����һ��ʱ���͸��Ч��
		3������
			�ɼ�ʰ������Ʒ����ʹ��ʱ������ɫ������Ѹ����ɢ 
	6������
		1����������/�;ö� 
			(1)���ɷ�����������ɡ������ԽԶԽ��/�ࡢ�����ԽԶԽ��/�� 
		2����������
			(1)����ǹ LAS 
				[1]��ʾ��������ɫ��ǹ�����ֳ�ʱ�����ʾΪ��ɫ������ 
				[2]ʹ�ã�������꣬����1����������������귽�򷢳���ɫ������������0.5�룬
					 ��ÿ��ǹ������������ʱ��������ģ������Զ�������ʧ�� 
				[2]�ص㣺����˲������Ŀ�꣬����ǽ�����ϵ��ž��жϣ��������Ӿͷ��䣬���߶��������ɫ����
				[3]����Ч������ȼTNT������� 
			(2)������ DAR
				[1]��ʾ�����ϡ�ʮ���ɶѵ����ֳ�ʱ�����ʾΪ��ɫ���ڡ� 
				[2]ʹ�ã�������꣬��������1������귽���ӳ������ڣ��ٶ�15m/s��
				[3]�ص㣺�ٶȽϸߣ�����ǽ�����ϵ��ž�ֹͣ���У���ɿɼ�ʰ����Ʒ���ɻ���
					��������л���Ч������20%�ٶȣ�
					30%�����ʣ�����ʱ��80%�ٶ� 
				[4]����Ч����
					�𻵴��������ӡ�����
			(3)ì SPE
				[1]��ʾ������һ�񡰡������ֳ�ʱ�����ʾΪ��ì����������������һ�񡰡�����ǰ��ʱ2�� 
				[2]ʹ�ã�
					ÿ���ƶ�/�ı䷽������ҳ����������Ϊ1��ì�����ֲ���ֱ���´�
					�������ǰ�̵�2�񣬻���б�� 
					��ײ�жϣ�����ì�ı䷽��ʱ��һ���������̳�ʱ���� 
						���������;öȼ��٣�������ٶ��йأ�����ɻ����˺� 
				[3]�ص㣺˲������Ŀ�꣬���ӱ������޷��ƶ��͹���������ǽ�����ϵ��ž�ͣ��
				[4]����Ч�������� 
			(4)ذ�� DAG
				[1]��ʾ������һ����ɫ��ذ�����ֳ�ʱ�����ʾΪ��ɫ��ذ��
				[2]ʹ�ã����·������������ʱ�˺�*5�������˸��ذ��
				[3]�ص㣺����ȭ���˺���ȡ�����ˣ�30%����
					����������ذ�׵������й� 
				[4]����Ч�����Դ������·�����������;�-25
				[5]�;ã�100�������Զ���ʧ
			(5)�� SWO
				[1]��ʾ������һ���ɫ���������ֳ�ʱ�������������ҳ������һ�񡰽���
				[2]ʹ�ã�
					�Ӷ����ӽ���������귽��ĵ��ˣ����л���
				[3]�ص㣺һ�񹥻���Χ��20%����
					���������뽣�������й� 
				[4]����Ч�����Դ������·����/�ӽ��������;�-25
				[5]�;ã�100�������Զ���ʧ
			(6)����
				[1]��ʾ���������񡰡��������ֳ�ʱ�������������ҳ���������񡰡�����
				[2]ʹ��
					�ƶ����ӵ���ÿ�θı䷽�򶼼���һ���˺��������˺��ȵ����ߣ����˱ȵ����ͣ�
					���ո���߳��ķ�ΧΪ���ķ�Χ���˺�*2������*2 
				[3]�ص㣺2�񹥻���Χ��8����20%����
					���������뵶�������й� 
				[4]����Ч�����Դ������·����/�ӵ��������;�-50 
				[5]�;ã�100�������Զ���ʧ
			(7)��ǹ
				[1]��ʾ������1���ɫ��ǹ�����ֳ�ʱ��������������ʾΪ������������ҳ������һ��ǹ��
					�����ܻ���ʾ�ض����� e.g.M4A1,PR5,AK47��
				[2]ʹ��
					������꿪������һ��ҩ��һЩǹ�������� 
					���д������ļ����Զ�������ȫ�������û��
					���л�������ɣ���ʾΪ��ɫ������ 
					�ӵ����ɼ����п�����Ч�����к���ʾ���������л���Ч�� 
				[3]�ص㣺ֻ�ܱ�ǽ�����ӡ������ŵ��£��ɴ��š���������֩����ȣ�����˺���
					����������ǹ�������й� 
				[4]����Ч�����Դ������𣬴����;�-50 
				[5]����������10��������Ʒ�����ռ�ռ�
			(8)�ɸ�
				[1]��ʾ������ĺ�ɫ������ 
				[2]ʹ�ã�������꣬��������1������귽���ӳ������ڣ��ٶ�15m/s��
				[3]�ص㣺�ٶȽϸߣ�����ǽ�����ϵ��ž�ֹͣ���У���ɿɼ�ʰ����Ʒ���ɻ���
					��������л���Ч������75%�ٶȣ�
					50%�����ʣ�����ʱ��100%�ٶ� 
				[4]����Ч����
					�𻵴��������ӡ�����
			(9)��
				[1]��ʾ������
				[2]ʹ��
					������곯����ʾ�����޿ռ�Ͳ���ʾ
					���������ɶ�����λ�õ�����
					������ת�������߷������ 
				[3]�ص㣺������λ�������޷�ֱ�Ӷ��������˺�������*0.2�������Ķ������ݶ���*0.5���������������������Զ�����
				{4]����Ч����ײ�������������;�-20 
				[5]�;ã�100��ÿ�θ񵲶������ 
			
		3��������� 
			(1)���� 
				[1]��ȡ 
					������ʱ��fʰȡ������Ҫ���򵶱��� 
					���ж����Ʒ�ѵ���ʰȡ���Ϸ��ģ�����ʾ�����ģ�
					������ͬ��
					����/�������գ�������/������
					��������Ʒ���п�λ��������� 
				[2]����
					ѡ��������������������/������/��Ʒ������ѡ����������q�����������λ��
					���ж����Ʒ�ѵ����ŵ�������
					ɾ����Ӧ���λ��
					������ͬ��
				[3]�л�
					����Ʒ����ѡ���������ٴε����e����������
					��ctrl�����������л��������� 
					��������Ϊ��ǹ��ѡ�е��У������e���Զ�������ǰ���У�������ɾȥ��Ӧλ��
			(2)ʵ��
				ÿ����������ʱΨһ���id����WEAPON_ID_START=10��ʼ��ţ�����Ʒ��������Ʒ��code�� 
				�Ա��Ϊ�±��¼������Ϣ���飺
					���࣬�;�/�������Ƿ�������ʧ���������ƣ�
					���ࣺSPR=1,LSG,DART,DAGGER,SWORD,LSWD,BLSWD,RIFLE,AXE 
					����ܶѵ����ѵ����ĸ�id���棨under����û�о���None=0 
				THING�б���ĸ�id�������棨top=None/...��
				��/��������ر�����¼�ѵ����������id��Top����û��=None
				��Ʒ��ֻ�洢����id 
				����ע��㣺
					����ע��id/top�Ƿ�ΪNone 
					���ע�������Ƿ�����ʧ
					������ʧ�������������� 
				��������������Ʒ������£���
					����������ʧ������������ 
					��top!=None����ȡtop��weapon[top].under=None
					��Ʒ��������id
				ѡ����Ʒ������ʱ�� 
					��id!=None������id����������Ϣ����ʾ
				��Ʒ��������id���л�����������
					��������None��top=id 
					�������������������ѵ���weapon[id].under=Top,Top=id	e.g.���� 
					���������������� 
				����������id����
					�����ж������Ƿ�None 
					���ҵ�����λ�ã�Ȼ�� 
						����top->under1->under2->...�ҵ����һ��ID��������ģ� 
						weapon[ID].under=id 
					top=weapon[id].under
					weapon[id].under=��Ӧλ��.top
					��������δ��ʧ����Ӧλ��.top=id 
				��������������
					��������������None��
						swap(weapon[idx].under,weapon[idy].under)
					���� �������ڵ�.under=None
					swap(��.Top,��.Top) 
				player_use_weapon������ʹ���������жϲ��� 
				����ʹ�����;�/�����þ���
					ɾ�����λ�ñ�Ų��������ʧ
					��Ӧ���λ��.top=weapon[id].under 
		4�����ֿ�ȭ
			�����������ȭ	���ո��������
			ȭ�˺��͵������Կ� 
		5����Ļ��ʾ
			(1)��������к�ɫ��KO����ʾ  
			(2)��ս��������ʱ���Ŷ��� 
	7����Ʒ���� 
		1�����ƶ���Ʒ��mvb�� 
			(1)ģʽ�����ơ����������ӡ� 
			(2)�ٿط���
				[1]��d���л�ģʽ
				[2]���ơ�ģʽ�£�
					�ٿ�ͬʱ�ƶ������Ʒ
					�������ƶ�����λ�õ���Ʒ������еĻ��� 
				[3]������ģʽ�£�
					��������Ʒѡ��
					���л�ģʽ���ƶ�ʱѡ����Ʒ���赲���޷�������ȡ��ѡ��
					���ƶ�ʱ�����Ƶ�ѡ����Ʒ������ѡ����Ʒ�������
				[4]���ӡ�ģʽ�£������ո���� 
					���Ƶ���Ʒ���䷽���ƶ����޷��ƶ�
					�ڶ���������˺� 
			(3)���ƶ���Ʒ
							����	����	����   ����   ��   ���   �� 
				���ߴ�͸	��	 	��		��      ��    ��   ��     ��
				����ڴ� 	��		��		��      ��    ��   ��     ��
				������kg��  40      20      10      5     10   10     5
		2�����䣨Ŀǰ�������������
			(1)��������
				[1]δѡ��ʱ���䰴�ո�����ɴ򿪴˷�������ţ���Ұ���£�
				[2]��򿪵������ƶ��ɽ������� 
				[3]���������а��ո��Ч��ͬ[1]
				[4]���������п�ֱ�������������ƶ������ô�����
			(2)����
				[1]�ж������޷������ţ��޷����뿪�������ӣ��޷�͸���رյ����ӹ�����ң������������⣩ 
				[2]���Ӳ�͸�⣨��ҿ�͸�����ŷ�϶���⿴���ֵ�Ͳͬ��calculate_vision1()�� 
				[3]�ɵĶ����޷��������� 
	8������
		(1)ȭ����2N ����1������ 
		(2)���ߣ�15N ����(��Ʒ����*0.4)������ 
	9������Ч��
		(1)͸�ӡ���Ұģ�� 
		(2)����
			������������ 
			����t�룬ÿ�뽵��x���������޷��Զ��ظ��������޷�ʹ�ÿո���������������
			��ʾΪ��ɫǰ�� 
		(3)ѣ��
			�ڶ���Ұ���� 
			����t�룬�������Ļ����ʾ��λ�����ذڶ�(screen_center)��ÿ�ΰڶ����ΪTms(T>=200ms)���ڶ�����1�񣬷������ 
			��ʾΪ��ɫǰ�� 
		(4)ʧ�� 
			�����Ұ��Χ��С
			����calculate_vision2����mx_dis��1~5 
			��ʾΪ��ɫǰ�� 
		(5)�ж�
			������Ѫ 
			����t�룬ÿ���x��Ѫ 
			��ʾΪ��ɫǰ�� 
		(6)�Ի�
			ʹ�����Ұ�г���һЩ����Ӱ�� 
			����t�룬��Ļ���ʱ���������Ϊa����ĳЩλ����ʾ����������� 
			��ʾΪ��ɫǰ�� 
��������
	1��ֱ�߾��루�����ľ��빫ʽ��
	2�������پ��루MHT_DIST��
	3������/�������루�����һ���ߵ���һ��Ĳ�����
�ߡ���Ļ��ʾ 
	1�������������ң��������£� 
		1�������Ϣ��[0,0]->[46,48] 47*49 
		2����Ϸ��ͼ��[46,0]->[142,48] 97*49
		3�������Ʒ��[142,0]->[188,48] 47*49 
			(1)��ʽ
				[1]���
					���Ͻǣ�"��Ʒ��"
					�б�ǩ���������;á����桢ʹ��ָ�ϵ�
					�б�ǩ����Ʒ��+��ʾͼ�� 
				[2]MC��� 
					��1~2�У�"������Ʒ��     ������   �;ã�   " 
					��2�У�"ʹ�÷�����"
					��3�У�������Ʒ��ͼ�񣨰�����˳������ 
			(2)ʹ��
				[1]��f��������Ʒ/ѡ����Ʒ���˳�
				[2]������Ʒʱʹ�÷����ѡ��
	2����Ļ���£�������ҡ���
	3����ɫ
		1��256ɫ SetConsoleTextAttribute(hout,0x00~0xff);
		2��RGB��ɫ
			(1)����ɫ printf("\033[48;2;%d;%d;%dm",back.r,back.g,back.b);
			   ǰ��ɫ printf("\033[38;2;%d;%d;%dm",forw.r,forw.g,forw.b);
			(2)���뷽ʽ��lh->hsv->rgb
				[1]lh=light����+hueɫ��
					����light��-100~0~100��s0v0~s0v100~s100v100�� 
					ɫ��hue��0~359��h��+360���ף� 
				[2]ɫ�� 
					h 0  30  60  90  120  150 180  210 240  270 300  330 360
					 ��  ��  �� ����  �� ī��  �� ����  �� տ��  �� �Ϻ�  �� 
			(3)���ټ�������ɫ�Ż� 
		 		ÿ��������ɫʱ�жϱ���/ǰ��ɫ�Ƿ��л�����������ʹ��printf������¼��ɫ��back_now/forw_now 
	4����ͼ��ӡ
		1������ɫback
			(1)���ȼ���ע����Щ�����ǲ��������ͬһλ�õģ� 
				ʬ�壨KO��>��ҹ�Ȧ����ʾ��Ϣ��>����Ӽ�Ѫ/��Ѩ������Ĺ�Ȧ> 
				>��������Ȧ>��>B��֩�뱾��>B��֩�븽֫>������>��������/�أ�>����
				>�ţ���/�أ�>����>��Ĺ�Ȧ�����ܣ�>ǽ>�յ�
		2��ǰ��ɫforw+����ַ���out
			(1)���ȼ�
				KO>֩������51~100�� 
				>��������>������� 
				>��>ʯ>��>�� 
				>A��B��֩�뱾��>��>B��֩�븽֫
				>��>��>��>��
				>ì>������>A��֩�븽֫>֩��˿��1~50�� 
				>�ţ���/�أ�>ʳ��>��Ѩ��>������>���ڱ���>�ţ�����>������>����>����>����>����>Կ��
				>��>����>¥��>ǽ>�յ� 
		3������ǿ��brightness 
			ʵ������=����+brightness
			��������[-100,100]�� 
�ˡ���ʱ������־ 
	1��׼��
		map<string,int> game_timer��¼δ��ĳ���¼�����ʱ����Ϸʱ��
		map<string,bool> game_flag��¼ĳ���¼��Ƿ��� 
	2��ʹ��
	e.g.game_timer["����ƶ�"]=game_time+1000;�������ֵplayer1.vts.stg.strength_value����һ�루1000ms���ظ�+1
		game_flag["���ʬ��"]=true;��ʬ�屻����������Ļ 
		��Ļ��ȥ��KO������ 
		1��󡭡� 
		if(game_timer["pvsr"]<=game_time&&����) player1.vts.stg.strength_value++;�������ֵ�ظ�+1
	3����ʱ��ʽ�Ա�
		1��game_time%���ʱ��
			��㣬��������ʱ��׼��������Ϊ��Ļ�������Ӧ���ٵ��ֶ�
		2��game_timer[??]<=game_time?...game_timer[??]+=���ʱ��
			��ȷ������ʱ����ɳ�������
		3��game_timer[??]<=game_time?...game_timer[??]=game_timer+���ʱ��
		��game_timer[??]+���ʱ��<=game_time?...game_timer[??]=game_timer
			׼ȷ����ʹ��������ұ�����ͬ���ٳ̶�
�š�����
	1��������£���С��������
		1����ʼ�������ж��У�Qbug/Qghost��Ϊ��
		2��ÿ�������Ұ���㽫�ܿ����Ҳ��ڶ��еĵ��˼�����У������õ���Ϊ����״̬��.update=true�� 
		3��ÿ�θ��µ���ʱ������Ҿ���>50����Ҳ��ܿ�����������˾ͳ��ӣ�ֹͣ���£�.update=false��
			�������ƶ�ʱ���������µĵ��ˣ�����������У��������������Ϊ����״̬��.update=true�� 
	2������
		1������
			(1)λ�ã���Ѩ��һ��ʼ�����λ�� 
			(2)��Ϸ�����Ƶ�������� 
		2���ƶ�
			(1)���򣺳�ʼ���������ǽ�����������ת�䣨������ʱ�䣩������¥�����¥��/��û���������������¥��������Ѩ�ͽ��� 
			(2)�ٶȣ�1~10��/1000���루����ʱȷ����
		3������
			(1)��ʽ����ײ
			(2)�˺���1~5��Ѫ�����ٶ��йأ�  
		4��Ѫ����5��
			(1)���������˺�+1
			(2)������/������/ì����-5
			(3)������ÿ0.5s-1
			(4)Ѫ��=0ʱ��������������Ѩ�ڲ����λ�ã�û�п�λ�͵��ţ� 
	3�����ӳ�Ѩ
		1�����ɣ���Ѩ��λ�ھ������һ��������Ŀյأ������Խ��Խ�࣬ͬʱ�ڳ�Ѩ�ڲ���ͼ����ͬһλ�õĳ�Ѩ�ڲ���Ӧ 
		2����Ѩ��Ѫ����3��
		���������-1��Ѫ��=0ʱ���ݻٲ���ʧ����������Ϊ��Ѩ��
		3������/��ҽ���ɴ�������Ѩ�ڲ���ͼ 
		4���洢��game_map[1~length][1~width][height+1~height+height].things.nst 
		5�����裺ֻ�пյغ�ǽ��û���κ���Ʒ 
	4��֩��
		1������
			(1)A�ͣ��������֯����ͨ��������Ѱ�������Ҫ��ս 
			�v ��u	�v �Ũu
			���룼	���롳
			�u ��v	�u �Ĩv
			(2)B�ͣ������ã��������ң���ҪԶ�̷�����˿�����޷�������С�ռ䣨��Χ8�������ϰ������޷������� 
			��  ��		�v �Ŧ�		 �v��u		 ��Ũu
			���룼		����		���룼		  �롳
			�u�� �v		�u�Ħ�		��  ��		��Ĩv
		2������ 
			(1)λ�ã�һ��ʼ�����λ�� 
			(2)��Ϸ�����Ƶ�������� 
		3���ƶ�
			(1)�ٶȣ�2~4��/1000���� 
			(2)�������
				[1]��������Լ�����˿���Һ��Լ���������������˿����ҷ����ƶ����������� 
				[2]���ģʽ���������ת�䣨������ʱ�䣩������¥�ݾ�������ʽ��룬������볲Ѩ 
					�ƶ���ĳ��λ��u�ĸ������������ľ��롢��˿�;ö��й� 
				[3]����ģʽ��B�ͣ�
					 ÿ���ƶ�ǰ����Ұ��Χ�ڣ���Զ���룺5����������/�������Ҳ���õ������ƶ�������еĻ��� 
			(3)B��֩���޷����ת 
		4������
			(1)��ײ��1~5��Ѫ�����ٶ��йأ��Գ���Ҳ��Ч�����и��ʸ���Ҹ����ж�Ч�����þ����޷��ƶ����������͵ȣ� 
			(2)������˿���������Զ��˿���������ʱ���и��ʷ�����˿��ס��� 
				��˿���ʣ������в����٣��ɴ����յء�֩�븽֫��¥�ݿڡ����ŵ��š��� 
				ʵ�ַ�����
				[1]���䣺��˿��ʼλ����֩����ǰ������˷���ǰ֩���������Ŀ�꣨�н�<45�㣩 
				[2]���У��ٶ�10~15m/s����֩��Ѫ������
				[3]���У������޷�����ģ�ǽ���š����ӵȣ�ͣ������ǰ������������������endurance+=75�� 
			(3)��Һ
				[1]��ԣ����10s����Ч�� 
		5��Ѫ����20��
			(1)������/�����ڻ���-5
			(2)������ÿ0.5��-1 
			(3)Ѫ��=0ʱ��������������ͼ���λ��
		6����Ʒ���� 
			(1)����·���ţ���/�ض��У����Ƶ�·����Ʒ���Ʋ��������ˣ� 
			(2)ÿ���ƶ���������˿
		7������ 
			(1)�;ö�endurance��0~100 
				���k��0~1000 ��ʼ����ʱ��t���Ժ���Ϊ��λ 
				add(x)�����񶯣�
					k=max(0,k-game_time+t)+x;�����ϴ��񶯵�����k��ʣk-game_time+t��0��������������x 
					t=game_time;����ʱ��Ϊ��ǰʱ�� 
			(2)Ч��
				���		�;ñ仯	���� 
				֩�뾭�� 	+10
				��Ʒ�ɹ�	-2*v		���٣�v*(1.5-�;�*0.01)�� 
				��Ҿ���	-20			ͣ�ټ����;�ֱ���;�<=50��ÿ��ͣ������-2 
				���Ӿ���				�;�>25�Ͷ����� 
			(3)��ʾ�������;öȣ� 
				1~25����  26~50����  51~75��˿  76~100����
				λ��������Ʒ�ϣ�ǰ��ɫ��Ϊ������ɫ 
	5����
		1������
			(1)λ�ã�һ��ʼ�����λ�� 
			(2)��Ϸ�����Ƶ�������� 
		2���ƶ�
			(1)�ٶȣ�3~5��/1000���루����ʱȷ����
			(2)�������
				[1]�ܿ�����ң�����ҷ����ƶ������Ƴ������Ұ 
				[2]���������������������Դ�ƶ� 
				[3]��������㼣�������㼣�����ƶ� 
				[4]���ģʽ���������ת�䣨������ʱ�䣩������¥��/��Ѩ��������ʽ��� 
		3������
			(1)��ʽ����ײ������ 
			(2)�˺���1~5��Ѫ�����ٶ��йأ�  
		4��Ѫ����30��
			(1)������/�����ڻ���-5/-3
			(2)������ÿ0.5��-1 
			(3)Ѫ��=0ʱ��������������Ѩ�ڲ����λ�ã�û�п�λ�͵��ţ�
		5����Ʒ����
			(1)�ƶ���Ʒ
			(2)���鲣����ÿ���;ö�-20�� 
			(3)���ѽ�����Կ���ţ���һ����ײ���򿪡����ڶ������룩 
			(4)����
				[1]ȭ����2N
				[2]���ߣ�20N
		6���������� 
			(1)��������������ǽ������͸�ӣ�������˲�ƣ�����15������͸�ӣ�����Ѫ
			(2)���������������ܣ�Զ��������Ч����ʯ�������˿��ԡ�ì���������Ч������ܣ����������˺���Ч���Ҳ���������ϵͳ�� 
		7����ʾ
			(1)�ַ�
				������ 
				��ǽ���q
				˲�ƣ��� 
				ʯ������
				���ܣ��� 
				��������+�ض���ɫ 
ʮ���˶�����
	1���˶�
		1�������ƶ���player_detect_move��deal_bug��deal_ghost
			�����ƶ� 
		2���ƶ���push_thing
			�����ƶ��������ƶ����������ӿ�ת�� 
		3�����У�throw_removable
		 	�����ƶ������ܴ��������ϵ��� 
		4��ͨ�ù�ʽ
			a=F/m���ٶȼ��� 
			m1v1+m2v2=m1'v1'+m2'v2'�����غ� 
			1/2 m1v1^2 + 1/2 m2v2^2 = 1/2 m1'v1'^2 + 1/2 m1'v1'^2�����غ�
			��v1=2m2/(m1+m2)*(v2-v1)  ��v2=2m1/(m1+m2)*(v1-v2) �Ƶ�ʽ 
ʮһ��������Ʒ
	�;öȼ���	�ƶ�/��ҽ���	�������	����������	�������� 
		����			50		ײ���ٶ�*5	ײ���ٶ�*5	0 
		���� 			5		ײ���ٶ�	ײ���ٶ�	0
		����			0		0			50			1
ʮ��������ϵͳ
	1����Դ		��Χ				����	�ص� 
	   �ֵ�Ͳ	player1.d1-45��~45��100		��������˶� 
	   �� 		���� 				50~150  �������ɿ��� 
	2������ǿ��brightness����light��
		1����ʼ����100 
		2�����㣺��ÿ����Դ����/���٣�����/����
			����calculate_vision2()����ÿ���յ���λ�ü��� 
		3����ʾ����light'ת��
			�ǵ�ǰλ��Ϊu����Χ����λ��Ϊv1,v2...vn 
			(1)͸��λ�ã�u->brightness
			(2)��͸��λ�ã�max(v1->brightness,v2->brightness,...)
			light'=light+brightness;limit_number(light',-100,100);
	3���ƶ�̬���� 
		1��׼��
			struct light->idÿ���Ʒ���һ����� 
			queue<position_3D> pos_affect_light;Ҫ���¹��յ�λ��
			queue<position_3D> light_area[id];ÿ�������һ�θ�������������λ��
		2����ʼ��
			���յ���λ�ü���light_area[id]
		3�����������������ƶ������𻵡�������/���� 
		4������
			(1)����pos_affect_light������calculate_vision2()��������䵽����λ�õ�ÿյ�� 
			(2)����ÿյ�ƣ�
				light_area[id]��ÿ��λ��.brightness���ٲ����У�����calculate_vision2()��
				ÿ���յ���λ��.brightness���ӣ�������light_area[id] 
	4�������ֵ�Ͳ
		1��׼��
			item::queue<position_3D> lst;�ֵ�Ͳ���һ�θ����յ���λ��
		2�����������������Ұ���¼���ʱ 
		3������
			(1)pos_flashlightÿ��λ��.brightness���ٲ�����
			(2)��player_calculate_vision2()�У����ڼ��������Ұʱret��ÿ��λ��v��
			��������a=calc_angle(player1.pos,v)��VPOS.brightness+=P/sqrt(dis)*cos(abs(player.d-a)/90*PI);���Ҳ��˥�� 
ʮ������Ϸ��������
	1���߼���
		1�����ظ������ͬλ�ã������Ұ���㣩
		2����ͬ��ɫ���ظ����ã�set_RGBcolor��
		3������λ�÷���������������Ұ���㣩
		4�������ֵ�Ͳ���¹���Ƶ��
		5����O2 
	2�������
		1�����������������setvbuf�����������ǰ�棩
		2��cout.tie(0)��ios::sync_with_stdio(false)��
		3����������endl 
*/
#define MMPP(a,b,c,d) MP(MP(a,b),MP(c,d))
#define MP(a,b) make_pair(a,b)
#define PPII pair<PII,PII >
#define PII pair<int,int>
#define PSB pair<string,bool>
#define TD3 tuple<double,double,double>
#define MT make_tuple
#define PRESS_KEY_UP 72
#define PRESS_KEY_DOWN 80
#define PRESS_KEY_LEFT 75
#define PRESS_KEY_RIGHT 77
#define PRESS_KEY_TAB 9
#define PRESS_KEY_ENTER 13
#define PRESS_KEY_ESC 27
#define PRESS_KEY_SPACE 32
#define PRESS_KEY_SHIFT 16 
#define PRESS_KEY_CTRL 17
#define	PRESS_KEY_0	48
#define	PRESS_KEY_1	49
#define	PRESS_KEY_2	50
#define	PRESS_KEY_3	51
#define	PRESS_KEY_4	52
#define	PRESS_KEY_5	53
#define	PRESS_KEY_6	54
#define	PRESS_KEY_7	55
#define	PRESS_KEY_8	56
#define	PRESS_KEY_9	57
#define	PRESS_KEY_A	97
#define	PRESS_KEY_B	98
#define	PRESS_KEY_C	99
#define	PRESS_KEY_D	100
#define	PRESS_KEY_E	101
#define	PRESS_KEY_F	102
#define	PRESS_KEY_G	103
#define	PRESS_KEY_H	104
#define	PRESS_KEY_I	105
#define	PRESS_KEY_J	106
#define	PRESS_KEY_K	107
#define	PRESS_KEY_L	108
#define	PRESS_KEY_M	109
#define	PRESS_KEY_N	110
#define	PRESS_KEY_O	111
#define	PRESS_KEY_P	112
#define	PRESS_KEY_Q	113
#define	PRESS_KEY_R	114
#define	PRESS_KEY_S	115
#define	PRESS_KEY_T	116
#define	PRESS_KEY_U	117
#define	PRESS_KEY_V	118
#define	PRESS_KEY_W	119
#define	PRESS_KEY_X	120
#define	PRESS_KEY_Y	121
#define	PRESS_KEY_Z	122
#define KEY_DOWN(VK_NONAME) ((GetAsyncKeyState(VK_NONAME) & 0x8000)?1:0)  //������ⰴ���ĵ���¼�
#define REP(a) for(ll counting_variable=1;counting_variable<=a;counting_variable++)
typedef long long ll;
POINT ScreenP;
HWND h; 
CONSOLE_FONT_INFO consoleCurrentFont;
HANDLE hin=GetStdHandle(STD_INPUT_HANDLE);
HANDLE hout=GetStdHandle(STD_OUTPUT_HANDLE);//�����������ɫר�ã� 
const int SMALLEST_TIME=10;//��Ϸʱ����С��λ��10����
const int MAX_SCREEN_LENGTH=189,MAX_SCREEN_WIDTH=49;//ConsolePauser����󳤿�ע��ÿ���ַ���1��2�� 
const int MAX_LENGTH=100,MAX_WIDTH=100,MAX_HEIGHT=10;//��Ϸ��ͼ����󳤿�� 
const int HUE=360,LIGHT=100;//ɫ�ࣨ0~359�������ȣ�-100~100�� 
const int KINDS_OF_DOORS=4,KINDS_OF_KEYS=4;//�š�Կ�׵�����������4
const int KINDS_OF_FOOD=2,EFFECT_OF_FOOD=3;//ʳ�����������2��Ч���ȼ�����3 
const int MAX_OBJECT_NUM=1000000;//��Ʒ�����Ŀ 
const int MAX_PLAYER_SPEED=2000;//��ҵ�����ٶ� 
const int MAX_SIZE_OF_ITEM_LAB=17;//�����Ʒ�����������
const int CREATURES_NUM=4;//��������������ҡ����ӡ�֩�롢�� 
const int MAX_BUG_NUM=1000000,MAX_SPIDER_NUM=500000,MAX_GHOST_NUM=100000;//���ӡ�֩�롢���������� 
const int SPIDERB_SIGHT=10,GHOST_SIGHT=20;
const int MAX_LIGHT_NUM=1000000;//�Ƶ�������� 
const int T_SPREAD_DELAY=50;//t_spread��ms��Խ����ɢ���㾫��Խ�� 
const double V_FOG_SPREAD=0.5;//v_spread����%/s��Խ����ɢ�ٶ�Խ��
const int INF=2e9;//��Ϸ������֡� 
const double PI=acos(-1);//�� 
const double eps=1e-4;//��Сֵ
int game_map_from=0;//��Ϸ��ͼ��Դ��0��������� 1����ȡģ�壩 
bool game_pause=false,game_end=false,game_success=false,start_again=false;//�Ƿ���ͣ/������Ϸ���ɹ����ѡ����¿�ʼ
int game_time,start_time;//��Ϸ�����С���ʼ��ʱ��
double now_timer;//��ǰ��ʱ��ʱ�䣨ms��
int lst_see_time;//�ϴ����¼��������Ұ��ʱ�� 
map<string,int> game_timer;//��Ϸ��ʱ�� 
map<string,bool> game_flag;//��Ϸ��־ 
PII back_now=MP(-100,360),forw_now=MP(0,360);//������ɫ 
void gotoxy(int x=0,int y=0);
void set_RGBcolor(int light1,int hue1,int light2,int hue2);
int RAND(int max,int min);
bool RAND_BOOL(int a);
enum MAP_FROM{
	RANDOM,FILE_MODEL
};
enum MAZE{//�Թ���ǽ�ڡ��š�ͨ���� 
	WALL,SPACE,EXIT,UPSTAIR,DOWNSTAIR,NEST,DOORS,STAIRS//ǰ����λ�ò�׼�� 
};
enum FLOOR{//�ذ�״�� 
	NORMAL,HOLE
}; 
enum PLAYER_ENEMY{//��Һ͵��ˣ���������ǵø�nobody_here��CREATURES_NUM�ȣ� 
	NOBODY,PLAYER,BUG,SPIDER,GHOST
};
enum OBJECT{//�ɶѵ�ʰȡ��Ʒ���� 
	NONE,KEY,FOO,WCG,SMO,PER,LAS/*����ǹ*/,DAR/*����*/,SPE/*��ì*/,DAG/*ذ��*/,SWO/*��*/,BLA/*����*/ 
	//LAS֮�������� 
};
enum ALL_ITEM{//������Ʒ
	K1=1,K2,K3,K4,AS1,AS2,AS3,AL1,AL2,AL3,SM,PPT,BX,BL,TT,CE//ȡ���ַ���β�ַ� 
};
enum DOOR{//��
	DOOR1=1,DOOR2,DOOR3,DOOR4
};
enum DOOR_KEY{//Կ�� 
	KEY1=1,KEY2,KEY3,KEY4
};
enum FOOD_KIND{//ʳ��
	ADDS=1,ADDL//�����ָ��������ָ�
}; 
enum WEAPON{//������������˼ǵ�ȥ wcnt ����һ�£��� 
	SPR=1,LSG,DART
};
enum MOVABLE{//���ƶ���Ʒ��������˼ǵ�ȥ movable ����һ�£���
	BOX,DESK,CHAIR,BALL
};
enum DEAL_ITEM{//������ƶ���Ʒ�ķ�ʽ
	PUSH,PULL,PUSH_HARD,BREAK 
};
enum DIRECTION_KEY{//�����
	STOP=0,
	UP,DOWN,LEFT,RIGHT
};
enum CHANGE_DIRECTION{//�ı䷽��
	TURN_RIGHT,TURN_BACK,TURN_LEFT 
};
enum ACTION_KIND{//��ҵĲ������� 
	RUN,WALK,CHOOSE_ITEM,CHANGE_WPN 
};
enum ATTACK_ATTRIBUTE{//���������� 
	VAMPIRE=1,DISAPP,THROUGH,INSTANT
}; 
enum DEFENSE_ATTRIBUTE{//����������
	EVADE=1,ROCK,SHIELD
};
int length,width,height;//��Ϸ��ͼ����� 
int cnt_notWALL,cnt_SPACE,cnt_STAIRS;//���� 
struct RGB_color{//RGB��ɫ���� 
	int r,g,b;//0~255
	void init(int _r,int _g,int _b){
		r=_r;g=_g;b=_b;
	}
};
struct position_2D{//����ṹ�壨xOy�� 
	int x,y;//x�����y���� 
	void init(){
		x=y=0;
	}
	bool operator<(position_2D a)const{//����< 
		return x<a.x||(x==a.x&&y<a.y);
	}
	bool operator==(position_2D a)const{//����== 
		return x==a.x&&y==a.y;	
	}
	bool operator!=(position_2D a)const{//����!=
		return x!=a.x||y!=a.y;	
	}
	void output1(bool enter=0){//��ӡ���� 
		cout<<"("<<x<<","<<y<<")";
		if(enter) cout<<"\n";
	}
}pos00;
struct position_3D{//����ṹ�壨xOyOz�� 
	int x,y,z;//x���ꡢy�����z���� 
	void init(){
		x=y=z=0;
	}
	bool operator==(position_3D a)const{//����== 
		return x==a.x&&y==a.y&&z==a.z;	
	}
	bool operator!=(position_3D a)const{//����!=
		return x!=a.x||y!=a.y||z!=a.z;	
	}
	bool operator<(position_3D a)const{//����<
		if(x!=a.x) return x<a.x;
		if(y!=a.y) return y<a.y;
		return z<a.z;	
	}
	void output1(bool enter=0){//��ӡ���� 
		cout<<"("<<x<<","<<y<<","<<z<<")";
		if(enter) cout<<"\n";
	}
}pos000;
		struct pheromone{//���ӵ���Ϣ�� 
			int disapp,id,d;//��Ϣ����ʧ��ʱ�䡢˭���µġ�ָ�� 
			void init(){
				disapp=d=0;id=-1;
			}
		};
	struct enemy{//������Ϣ 
		int id;//���˵ı�� 
		bool dead;//���������ǻ� 
		int body_disapp;//ʬ����ʧ��ʱ�� 
		pheromone phm;//��Ϣ��
		int ghost_block;//��һ����������׷��ұ��ϰ��赲��ʱ�䣨��ֹ��ס�� 
		void init(){
			id=-1;dead=false;body_disapp=ghost_block=-INF;
			phm.init();
		}
		void init2(){
			id=-1;dead=false;body_disapp=0;
		}
	};
		struct key_door{//��
			bool exist;
			int kind;//DOOR1,DOOR2,DOOR3,DOOR4
			int state;//0��������1���򿪣�2���ر� 
			bool light_through;//�Ƿ�͸�� 
			void init(){
				exist=kind=state=light_through=0;
			}
		};
		struct hiden_door{//������
			bool exist;
			int kind;//1��αװ��ǽ 2��αװ������ 
			void init(){
				exist=kind=0;
			} 
		}; 
		struct exit_sign{//���ڱ��ƽṹ��
			bool exist;//��û�г��ڱ��� 
			int dir;//���ڱ���ָʾ�ĳ��ڷ���
			void init(){
				exist=dir=0;
			}
		};
		struct mirror{//���ӽṹ��
			bool exist;//��û�о��� 
			int dir,side;//���ӵķ��������
			/*      0	1	2	3
			1side  ��  ��  ��  ��
			2side 	�u	�v  
			*/
			int endurance;//�;ö� 
			void init(){
				exist=dir=side=endurance=0;
			}
			void damage(int edc){
				endurance-=edc;
				if(endurance<=0) init();
			}
		};
		struct window{//�����ṹ��
			bool exist;//��û�д��� 
			int endurance;//�;ö� 
			bool state;//����״̬��0���� 1������ 
			void init(){
				exist=endurance=state=0;
			}
			void damage(int edc,position_3D u);
		};
		struct curtain{//���ӽṹ��
			bool exist;//��û������
			int endurance;//�;ö� 
			void init(){
				exist=endurance=0;
			}
		};
		struct food_pile{//ʳ��ṹ��
			/*һ��λ��ֻ��һ�� 
			bool exist;//��û��ʳ�� 
			int kind,effect;//kind:0,ADDS,ADDL effect:1,2,3��Ч���ж�� 
			void init(){
				exist=kind=effect=0;
			}*/
			int food_cnt[KINDS_OF_FOOD][EFFECT_OF_FOOD];//ʳ��ѵ� 
			//food_cnt[i][j]:i(kind)->ADDS-1(0),ADDL-1(1),j(effect)->1(0),2(1),3(2)
			bool exist(){
				for(int i=0;i<KINDS_OF_FOOD;i++)
					for(int j=0;j<EFFECT_OF_FOOD;j++)
						if(food_cnt[i][j]>0) return true;
				return false;
			} 
			void init(){
				memset(food_cnt,0,sizeof(food_cnt));
			}
			void make(int kind,int effect){
				if(kind<=0||effect<=0) return;
				if(kind>KINDS_OF_FOOD||effect>EFFECT_OF_FOOD) return;
				//kind:ADDS=1,ADDL=2 effect:1,2,3
				food_cnt[kind-ADDS][effect-1]++;
			}
			int kind(){//��ʾ������
				for(int i=0;i<KINDS_OF_FOOD;i++)
					for(int j=EFFECT_OF_FOOD-1;j>=0;j--)
						if(food_cnt[i][j]>0) return i+ADDS;
			}
			int effect(){//��ʾ�ĵȼ� 
				for(int i=0;i<KINDS_OF_FOOD;i++)
					for(int j=EFFECT_OF_FOOD-1;j>=0;j--)
						if(food_cnt[i][j]>0) return j+1;
			}
		};
		struct laser{//�������ṹ��
			bool exist;//��û�м����� 
			int laser_beam;//����������ʽ��0~3���������򡪣���4������Ŀ����� 
			void init(){
				exist=laser_beam=0;
			}
		};
		struct weapon_energy_edc{//��������/�;öȻظ�
			bool exist;
			int num,kind;//��������������/�;öȻظ���0������ǹ 1��ì��
			void init(){
				exist=num=kind=0;
			}
		};
		struct dart{//�����ڽṹ��
			bool exist(){//��û�л�����
				return num[0]>0||num[1]>0;
			}
			bool exist0(){//��û�е��ϵĻ�����
				return num[0]>0;
			}
			bool exist1(){//��û�з��еĻ�����
				return num[1]>0;
			}
			int num[2];//0������ʾʱ�ã����� /1�����������ã�������  �Ļ����ڵ����� 
			void init(){
				num[0]=num[1]=0;
			} 
		}; 
		struct spear{//ì�ṹ��
			bool exist;//��û��ì
			int d;//ì�ķ���
			bool head;//ìͷ 
			void init(){
				exist=d=head=0;
			} 
		};
		struct sword{//���ŵĽ��ṹ��
			bool exist;//��û�н�
			void init(){
				exist=0;
			} 
		};
		struct blade{//���ŵĵ��ṹ��
			bool exist;//��û�е� 
			bool head;//�ǲ��ǵ��� 
			void init(){
				exist=head=0;
			} 
		};
		struct nest{//���ӵĳ�Ѩ��
			bool exist;//��û�г�Ѩ�� 
			int id;//���
			position_3D to;//��Ӧ�ĳ�Ѩ��λ�ã�ע�⣺�����ǽ�ȥҲ�����ǳ����� 
			void init(){
				exist=0;id=-1;to.init();
			} 
		};
		struct movable{//���ƶ�����
			bool exist;
			int kind;//0������ 1������ 2������ 3��Ƥ�� 
			bool door[4];//�����Ƿ��� ��ʼΪ�رգ�0�� 
			void init(){
				exist=kind=0;
				memset(door,0,sizeof(door));
			}
		};
		struct footprint{//�㼣�ṹ��
			bool exist(){//��û���㼣
				return d!=-1;
			}
			int d;//����㼣����4����/��¥�� 
			void init(){
				d=-1;
			}
		};
		struct perspective{//ʹ��Ҳ���͸��Ч������Ʒ
			bool exist;
			int kind,time;//2~3,5000ms~20000ms 
			void init(){
				exist=kind=time=0;
			} 
		};
		struct smoke_bomb{//����
			bool exist;
			//double absorbance[3];
			void init(){
				exist=false;
				//memset(absorbance,0,sizeof(absorbance));
			}
		};
		struct light{//��
			bool exist;
			int p;//���� 
			int id;//��� 
			bool update;//��Ҫ���� 
			bool state;//״̬��0���� 1������ 
			void init(){
				exist=p=update=0;state=1;id=-1;
			}
		};
		struct spider_leg{//֩����
			int num;//�м�ֻ�������� 
			int id;//-1:��ȷ��Ҫ���¼��� >=0����������֩��ı�� 
			void init(){
				num=0;id=-1;
			}
		};
			bool RAND_BOOL(int a);
		struct spider_net{//֩����
			int endurance;
			int k,t;//�����0~1000����˥����ʼʱ��
			//ÿ1ms���-1 
			bool exist(){
				return endurance>0;
			} 
			void init(){
				endurance=k=t=0;
			}
			void addedc(int k,position_3D u);
			int nowk(){//��ǰ���
				return max(0,k-game_time+t);//��ֹ�������� 
			}
			void addk(int x){//game_timeʱ�񶯷�������x 
				k=max(0,nowk()+x);//�����������ֹ���������� 
				t=game_time;//�ı���ʼʱ�� 
			}
			void mxk(int x){//game_timeʱ�񶯷�����xȡ���ֵ 
				k=max(0,max(nowk(),x));//�����������ֹ���������� 
				t=game_time;//�ı���ʼʱ�� 
			}
		};
		struct spider_silk{//֩��˿
			int num;//���� 
			bool exist(){
				return num>0;
			}
			void init(){
				num=0;
			}
		};
		struct fog{//���� 
			double absorbance[3];//�����ʣ�0.00~100.00��0Ϊû��������ɫ���� 
			//RGB_color col;//��������ɫ��Ӱ��ģ��Ч���ĵ�����ɫ�� 
			bool update;//�Ƿ���pos_fog�� 
			bool exist(){
				return absorbance[0]>eps||absorbance[1]>eps||absorbance[2]>eps; 
			}
			void init(){
				memset(absorbance,0,sizeof(absorbance));
				update=0;
				//col.init(255,255,255);
			}
		};
	struct thing{
		int fir;//���������Ʒobject��� 
		key_door kdr;
		hiden_door hdr;
		int key;//0,KEY1,KEY2,KEY3,KEY4
		mirror mirrors;
		window windows; 
		curtain crt;
		movable mvb;
		light lgt;
		food_pile foods;
		weapon_energy_edc wee;
		nest nst;  
		laser lsr;
		dart drt;
		spear spr;
		sword swd;
		blade bld;
		smoke_bomb smb;
		perspective ppt;  
		spider_leg slg;
		spider_net snt;
		spider_silk ssk;
		bool empty(){//��ʾ�����Ƿ�û�ж��� ||exit_signs.exist���ùܳ��ڱ��� 
			return !(kdr.exist||hdr.exist||key||mirrors.exist||windows.exist||crt.exist||mvb.exist||lgt.exist||nst.exist
			||lsr.exist||drt.exist()||spr.exist||swd.exist||bld.exist
			||slg.num>0||snt.exist()||ssk.exist()||fir>=0); 
		}
		bool noitem(){//û��object�������Ʒ 
			return !(kdr.exist||hdr.exist||mirrors.exist||windows.exist||crt.exist||mvb.exist||lgt.exist||nst.exist
			||lsr.exist||drt.exist()||spr.exist||swd.exist||bld.exist||slg.num>0||snt.exist()||ssk.exist()); 
		}
		//���²����������Ʒ�жϣ�����  
		exit_sign exit_signs;
		footprint fpt;//����ʾ 
		fog fogs;//����ͨ��ģ��Ч���۲쵽 
		void init(){//��ʼ�� 
			fir=-1; 
			key=0;
			kdr.init();hdr.init();exit_signs.init();mirrors.init();windows.init();crt.init();mvb.init();lgt.init();foods.init();
			wee.init();nst.init();lsr.init();drt.init();spr.init();swd.init();bld.init();smb.init();ppt.init();
			slg.init();snt.init();ssk.init();fogs.init();
			fpt.init();
		}
	};
		struct velocity{//�ٶȹ����壨v��
			double speed;//��λ����/1000���루����Ϊ0������������ 
			int wait_time;//��1��ͣ���ٺ��루����Ϊ0��������Ϊ�� 
			void tv(){//wait_time->speed
				if(wait_time<=0) wait_time=1;//��ֹ���� 
				speed=1000.0/wait_time;
			}
			void vt(){//speed->wait_time
				if(fabs(speed)>0.01) wait_time=1000/fabs(speed)+0.5;//�������� 
				else wait_time=100000;//speedС��һ���̶Ⱦ�Ĭ��Ϊ0.01 
				if(wait_time<=0) wait_time=1;//��ֹ���� 
			}
		};
	struct force_move{
		int tx,ty;//�˶�ʱ�� 
		velocity vx,vy;//�ٶ� 
		bool lock;//�������޷���������mvb�����У� 
		PII from;//��Դ��<����,id>�� 
		void init(){
			tx=ty=-1;
			vx.speed=0;vx.vt();
			vy.speed=0;vy.vt();
			lock=0;
			from=MP(0,-1);
		}
		void init2(double speed,double angle,PII f){//���ӳ�ȥ�Ķ��� 
			tx=ty=game_time; 
			double tmpx=cos(angle/180.0*PI),tmpy=sin(angle/180.0*PI);//vx/v��vy/v���������� 
			vx.speed+=speed*tmpx;vx.vt();//���ٶ� 
			vy.speed+=speed*tmpy;vy.vt();//���ٶ� 
			if(tx<=game_time) tx=game_time+vx.wait_time;//��ֹ˲���ƶ�2�� 
			if(ty<=game_time) ty=game_time+vy.wait_time;//��ֹ˲���ƶ�2�� 
			lock=true;
			from=f;
		}
		void init3(double spx,double spy){//�ı��˶�������ٶ�
			vx.speed=spx;vx.vt();
			vy.speed=spy;vy.vt();
		}
		void init4(double speed,double angle){//�ı��˶�������ٶ�
			vx.speed=speed*cos(angle/180.0*PI);vx.vt();
			vy.speed=speed*sin(angle/180.0*PI);vy.vt();
		}
		double speed(){//���ٶȣ����� 
			return sqrt(vx.speed*vx.speed+vy.speed*vy.speed); 
		}
	};
	struct in_sight{
		int player;//������һ�ο������λ�õ�ʱ�䣨=lst_see_time��������ڿ��õ���<lst_see_time��������ڿ�������
		double vague[3];//player_vague ��ҿ������λ�õ�ģ���̶ȣ�0~1�����ֲ�ͬ��ɫ��r0g1b2�� 
		int other;//�������� 
		void init(){
			player=other=-INF;
			vague[0]=vague[1]=vague[2]=0;
		}
		double pvg(){
			return (vague[0]+vague[1]+vague[2])/3;
		} 
		bool vague_exist(){
			return vague[0]>eps||vague[1]>eps||vague[2]>eps; 
		}
	};
struct MAP{//��������Ҫȥall_assigned��һ�� 
	int maze;//WALL,SPACE,EXIT,UPSTAIR,DOWNSTAIR,LIFT
	int floor;//NORMAL,HOLE 
	int player_enemy;//NOBODY,PLAYER,BUG,GHOST
	int brightness;//�������� 
	enemy emy;//������Ϣ 
	thing things;//��Ʒ 
	force_move fcmv;//�����˶� 
	in_sight ist;
	void init(){
		floor=NORMAL;
		maze=WALL;
		player_enemy=NOBODY;
		brightness=-95;//΢���Ļ����� 
		emy.init(); 
		things.init();
		fcmv.init();
		ist.init();
	}
	double mass();
	bool update_light(){//��λ�ñ仯���¹����Ƿ����ã����˷�ʱ�䣩 
		return 1;//brightness>-100&&(ist.player==lst_see_time||ist.other==lst_see_time)
	}
	bool see(int being=GHOST,int attack=0){//�����Ƿ�ɿ�����λ�� 
		if(being==GHOST){
			if(attack==VAMPIRE)//������Ѫ������� 
				return brightness>=-100&&brightness<=0&&ist.pvg()<0.5;
			if(attack==THROUGH)//���Դ�ǽ������� 
				return brightness>=-100&&brightness<=100&&ist.pvg()<0.7;
			return brightness>=-80&&brightness<=80&&ist.pvg()<0.4;
		}
		else if(being==SPIDER) return brightness>=-90&&brightness<=30&&ist.pvg()<0.4;
		//���Ⱥ��ʡ�ģ����(0~1)���� 
		return false;
	}
	bool see_fr(){//�����Ƿ�ɴӴ�λ�ÿ�����
	    return ist.pvg()<0.4;//ģ����(0~1)����
	}
	bool burn_vampire(){//��ǿ�Ƿ��������Ѫ��
		return brightness>0; 
	}
}game_map[MAX_LENGTH+9][MAX_WIDTH+9][MAX_HEIGHT*2+9];
struct direction{//����ṹ�� 
	int d1,d2;//d1��ǰ��ƫd2�����ң����� 
};
		struct life_injury{//���������˽ṹ��
			int change;//�����������û�У�1������ 2�����٣� 
			double life;//����ֵ��0%~100%��%ʡ�ԣ�
			double hurt,recovery;//����ֵ���ظ�ֵ 
			double lst_hurt;//�ϴ����˵ļ���ֵ 
			PII last_injury_from;//�ϴ��˺���Դ 
			int last_injury_time;//�ϴ�����ʱ�� 
			int no_hurt;//����Ч����ֹʱ�� 
			void init(double lf){//��ʼ�� 
				life=lf;hurt=recovery=lst_hurt=change=0;last_injury_from=MP(0,-1);last_injury_time=-INF; 
				no_hurt=-INF; 
			}
			bool canhurt(){
				return no_hurt<=game_time;
			}
		};
		struct strength{//�����ṹ��
			bool change;//�����������û�� 
			double physical_strength;//����ֵ��0%~100%��%ʡ�ԣ�
			int recovery_time;//�ָ�ʱ�� 
			void init(){//��ʼ�� 
				physical_strength=100;change=1;recovery_time=300;
			}
		};
	struct vital_signs{//���������ṹ�� 
		life_injury lfin;//����������
		strength stg;//���� 
		void init(){//��ʼ�� 
			lfin.init(100);stg.init(); 
		}
	};
	struct kill_count{//��ɱ��
		int sum;
		int det[CREATURES_NUM+1];//NOBODY==0
		bool change;//��ɱ���Ƿ�仯 
		void init(){
			sum=change=0;
			memset(det,0,sizeof(det));
		}
		void update(int add,int kind){
			sum+=add;det[kind]+=add;
			change=true;
		} 
		string detail(int k=0);
	}; 
	struct score{//��������ָ��Ϸ����ʱ����Ҫ�õ�ָ�꣩ 
		int time_spent;//�ӳ����ѵ�ʱ�� 
		kill_count kc;//��ɱ�� 
		int shoot_times,shoot_hit_times;//��ɱ����ʹ��������������������е��˴��� 
		double hit_rate;//������ 
		int hurt_times;//���ܹ������� 
		void init(){//��ʼ�� 
			time_spent=shoot_times=shoot_hit_times=hit_rate=hurt_times=0;
			kc.init();
		}
	};
		struct key{//Կ�׽ṹ��
			int door_keys[KINDS_OF_KEYS];//�洢��ͬ�����Կ��
			int treasure_keys;//�����������Կ��
			void init(){//��ʼ�� 
				memset(door_keys,0,sizeof(door_keys));
				treasure_keys=0;
			} 
		};
		struct stored_food{//��Ҵ洢��ʳ��ṹ��
			int food_cnt[KINDS_OF_FOOD][EFFECT_OF_FOOD];//�洢��ͬЧ����ʳ�� 
			void init(){//��ʼ�� 
				memset(food_cnt,0,sizeof(food_cnt));
			} 
		};
			struct laser_gun_info{//����ǹ������ 
				int last_time,cool_time;//����ʱ�䡢��ȴʱ�� 
				int kind,kd_cnt;//ģʽ��ģʽ���� 
				bool kd_change;//�����������û��
				int kd_energy[5];//ģʽ��Ӧ���������� 
				string kname[5];//ģʽ��
				void init(){
				 	kind=0;last_time=300;cool_time=200;
				 	kd_cnt=5;
				 	kd_energy[0]=1;kd_energy[1]=3;kd_energy[2]=3;kd_energy[3]=4;kd_energy[4]=8;
				 	kname[0]="����";kname[1]="����";kname[2]="����";kname[3]="�Ĵ�ɨ��";kname[4]="���濪��";
				}
			};
			/*
			struct holding_spear{//�ֳ�ì
				int endurance;//�;ö� 
				void init(){
					endurance=100;
				}
			};
			struct throwing_dart{//������
				int num;//���� 
				void init(){
					num=0;
				}
			};*/
		struct weapon_carried{//����
			int primary,secondary;//�������������� 
			//��Ӧ��Ʒ���еı��
			bool sw_change;//�����������û��
			laser_gun_info lsg;
			/*
			throwing_dart drt;
			holding_spear hsr;*/
			bool data_change,mode_change;//���������Ĳ�����Ϣ/ģʽ����û�� 
			void init(){
				primary=secondary=-1;
				sw_change=data_change=mode_change=0; 
				lsg.init();//drt.init();hsr.init();
			}
		};
		struct removable{//���ƶ�����Ʒ 
			int deal_kind;//������Ʒ�ķ�ʽ��PUSH,PULL�� 
			bool dl_change;//�����������û�� 
			position_3D select;//ѡ�������λ��
			bool throw_ready;//׼���Ӷ��� 
			void init(){
				deal_kind=PUSH;dl_change=throw_ready=false; 
				select.init();
			} 
		}; 
		struct flashlight{//�ֵ�Ͳ
			bool state;//0���� 1���� 
			int angle;//����Ƕȣ�d-angle ~ d+angle 
			int p;//���� 
			bool change;//������Щ��������û�� 
			queue<pair<position_3D,int> > lst;//�ϴθ�������ĵط���λ�ã�����ǿ�������� 
			void init(){
				state=0;angle=60;p=70;change=0;
				while(!lst.empty()) lst.pop();
			}
		};
		struct prop{//���� 
			int smb;//����
			void init(){
				smb=0;
			} 
		};
	struct item{//��Ʒ�ṹ�� 
		key keys; 
		stored_food foods;
		prop pp;
		bool num_change;//��Ʒ�����Ƿ�仯 
		int select_number;//ѡ�е���Ʒ����Ʒ����ı�ţ�0~�� 
		bool sn_change;//�����������û��  
		vector<int> item_lab,item_num;//��Ʒ���������Ʒ���+������
		bool il_change;//�����������û�� 
		weapon_carried wpn;
		removable rmv;
		flashlight flt;
		void init(){//��ʼ�� 
			keys.init();
			foods.init();
			pp.init();
			//��������Ʒ������Ϣ 
			num_change=0; 
			select_number=0;sn_change=il_change=0;
			wpn.init();
			item_lab.clear();item_num.clear();
			for(int i=0;i<MAX_SIZE_OF_ITEM_LAB;i++) item_lab.push_back(-1),item_num.push_back(0);
			flt.init();
		}
		string item_name(int sn);//��Ʒ���� 
		//int item_num(int sn);//��Ʒ���� 
		int item_endurance(int sn);//��Ʒ�;� 
		string item_method(int sn);//��Ʒʹ�÷��� 
		void print_item(int k);//������Ʒ�ı����ӡ��Ʒ 
		void print1();//��ӡ��Ʒ��ѡ�е���Ʒ��Ϣ 
		void print2();//��ӡ��Ʒ�����������Ʒ
		void print3();//��ѡ��������λ��
		void wpn_print1();//��ӡ���������� 
		void wpn_print2();//��ӡ������������Ϣ 
		void wpn_print3();//��ӡ������
	};
		struct x_ray{//͸�� 
			int num,time;//��Ұ������1������״̬����͸��num-1�㣩������ʱ�䣬ֻ�ܿ���x_ray���赲����λ���ڵ�λ��
		    bool change;//������Щ����û�� 
			void init(){
				num=1;time=-1;
				change=false; 
			}
		};
		struct dim_sight{//�����ƶ��е���Ұģ��
			int cpt,part;//��ȫ/����ģ������С���루>�� 
			int time,last;//�ϴ��ƶ���ʱ�� 
			bool dim;//��ǰ�Ƿ�ģ����ʾ 
			void init(){
				cpt=15;part=7;
				time=-INF;last=700;
				dim=false; 
			}
		};
		struct weakness{//���� 
			int end;//Ч������ʱ��
			int t,T;//�ϴμ�����ʱ�䡢���������� 
			int x;//�������� 
		    bool change;//������Щ����û�� 
		    PII from;//Ч����Դ 
			bool exist(){
				return end>game_time;
			} 
			void init(){
				end=t=-INF;
				T=0;
				x=0;
				change=false; 
				from=MP(0,-1);
			}
		};
		struct vertigo{//ѣ��
			int end;//Ч������ʱ��
			int t,T;//�ϴΰڶ�ʱ�䡢�ڶ����� 
		    bool change;//������Щ����û�� 
		    PII from;//Ч����Դ 
			bool exist(){
				return end>game_time;
			} 
			void init(){
				end=t=-INF;T=0;
				change=false; 
				from=MP(0,-1);
			}
		}; 
		struct blindness{//��ä
			int end;//Ч������ʱ��
			int vision_dis;//������Զ���루�����٣�
		    bool change;//������Щ����û�� 
		    PII from;//Ч����Դ 
			bool exist(){
				return end>game_time;
			}
			void init(){
				end=-INF;
				vision_dis=-1;
				change=false; 
				from=MP(0,-1);
			}
		};
		struct methysis{//�ж�
			int end;//Ч������ʱ��
			int t,T;//�ϴο�Ѫʱ�䡢��Ѫ����
			int x;//ÿ�ο�Ѫ��Ѫ�� 
		    bool change;//������Щ����û�� 
		    PII from;//Ч����Դ 
			bool exist(){
				return end>game_time;
			} 
			void init(){
				end=t=-INF;
				T=x=0;
				change=false; 
				from=MP(0,-1);
			}
		};
		struct confusion{//�Ի�
			int end;//Ч������ʱ��
			int a;//��Ļ���ִ���Ӱ��ĸ���
		    bool change;//������Щ����û�� 
		    PII from;//Ч����Դ 
			bool exist(){
				return end>game_time;
			} 
			void init(){
				end=-INF;
				a=0;
				change=false; 
				from=MP(0,-1);
			} 
		};
	struct special_effect{//����Ч���ṹ�壨��������Ѫ����������
		x_ray xry; 
		dim_sight dst;
		weakness wks;
		vertigo vtg;
		blindness bds;
		methysis mts;
		confusion cfs;
		void init(){
			xry.init();//������Ұ
			dst.init();
			
			wks.init();
			vtg.init();
			bds.init();
			mts.init();
			cfs.init();
		}
		bool exist(){//�����Ƿ�������Ч�� 
			return xry.num>1||wks.exist()||vtg.exist()||bds.exist()||mts.exist()||cfs.exist();
		}
		bool change(){
			return xry.change||wks.change||vtg.change||bds.change||mts.change||cfs.change;
		}
	};
struct player{//��� 
	position_3D pos;//����
	int d1,d2;//�ƶ���������/��׼����
	int color;//�����ʾ��0�������� 1����Ѫ�� 2�����˺� 3���䷽���������4���� 5����˸�֣� 
	string flash_word; 
	int angle,lsta;//���ָ��ķ���0~359��
	int alc;//��귽���ϴθı�ʱ�� angle lst change 
	velocity w;//���ٶȣ���/s�� 
	position_3D mpos;//���λ�� 
	vital_signs vts;//�������� 
	score scr;//���� 
	velocity vlc;//�ٶ� 
	item items;//��Ʒ
	special_effect spe;//����Ч�� 
	string name;//���� 
	int grid;//�񵲳�����ʲôʱ�� 
	void init();//��ʼ�� 
	/*����Ϊ��־����*/
	bool d1_change,d2_change,move;//�����Ƿ�ı䣬�Ƿ�ı���λ��
	bool up_down,ud_change,lst_ud,lst_enter,enter_nest;
	//�Ƿ��Զ�����/��¥�ݻ��߽�/����Ѩ�ڣ�ǰ���������û�У��ϴ��Ƿ��Զ���/��¥�ݣ��ϴ��Ƿ��Զ���/����Ѩ��
	bool flash,use_weapon,pull_thing,enemy_move;//�Ƿ���˸���Ƿ�ʹ���������Ƿ�������Ʒ������/������Ұ��Ƿ�ı���λ�� 
	int action_kind;//��Ҷ�����0������ 1������ 2��ѡ����Ʒ 4���ı䷽��
	//RUN,WALK,CHOOSE_ITEM,CHANGE_WPN
	bool ak_change;//�����������û�� 
}player1; 
struct pos_player_see{//��ҿ��ü��ĸ��� 
	position_3D pos;//����
};
queue<position_3D> pos_in_sight;
//������ڿ��ü����£���Ļ�϶�Ӧλ��û����ʾ��λ��
queue<position_2D> pos_lst_sight;
//�ϴ���Ļ����ʾ��λ��
set<position_2D> pos_backup;//���ݣ�ȥ�أ�
set<position_3D> pos_change;//����Ұ���Լ����µ�λ�� 
map<position_2D,string> screen_pos;//��Ļ�ϵ�λ����ʾ���ݵı��� 
map<position_2D,int> screen_z;//��Ļ��������Ҫ��ʾ��λ��������¥�㣨z���꣩ 
struct rectangle{//���νṹ�壨������Ļ����ȣ� 
	position_2D upper_left,lower_right;//���ϽǺ����½�
	void init(position_2D ul,position_2D lr){//��ʼ�� 
		upper_left=ul,lower_right=lr;
	} 
	void init(int x_1,int y_1,int x_2,int y_2){//��ʼ�� 
		upper_left=(position_2D){x_1,y_1},lower_right=(position_2D){x_2,y_2};
	}
	void output_frame(string c="*",PPII color=MP(MP(-100,360),MP(0,360)),int kind=1){//������α߿� 
		PII back=color.first,forw=color.second;//����ɫ��ǰ��ɫ 
		for(int x=upper_left.x;x+c.size()-1<=lower_right.x;x+=c.size()){
			int y_1=upper_left.y,y_2=lower_right.y;
			gotoxy(x,y_1);
			set_RGBcolor(back.first,back.second,forw.first,forw.second);//SetConsoleTextAttribute(hout,color);
			cout<<c;
			gotoxy(x,y_2);
			cout<<c;
		}
		if(kind)
			for(int y=upper_left.y;y<=lower_right.y;y++){
				int x_1=upper_left.x,x_2=lower_right.x;
				gotoxy(x_1,y);
				set_RGBcolor(back.first,back.second,forw.first,forw.second);//SetConsoleTextAttribute(hout,color);
				cout<<c;
				gotoxy(x_2,y);
				cout<<c;
			}
	}
	bool contain(position_2D u){//u�ڴ���Ļ�����У��������߽磩 
		int x_1=upper_left.x,x_2=lower_right.x;
		int y_1=upper_left.y,y_2=lower_right.y;
		return u.x>x_1&&u.x<x_2&&u.y>y_1&&u.y<y_2;
	}
}whole_screen,vital_signs_area,item_area,weapon_area;
//������Ļ����Ϸ��ͼ���������Ϣ���������Ʒ������������� 
position_2D screen_center;//��Ļ���Ķ�Ӧ�ĵ�ͼ���� 
	struct food{//һ��ʳ�� 
		int kind,effect;//kind:0,ADDS,ADDL effect:1,2,3
		void init(){kind=effect=0;}
		bool operator==(food b){
			return kind==b.kind&&effect==b.effect;
		}
	}food00;
	struct weapon_charge{//�������ܣ�װ��/�;ã�
		int num,kind;//��������������/�;öȻظ���0������ǹ 1��ì��
		void init(){num=kind=0;} 
		bool operator==(weapon_charge b){
			return num==b.num&&kind==b.kind;
		}
	};
	struct see_through_prop{//͸�ӵ���
		int kind,time;//2~3,5000ms~20000ms  
		void init(){kind=time=0;}
		bool operator==(see_through_prop b){
			return kind==b.kind&&time==b.time;
		}
	}ppt00;
struct object{//��ͼ��Ʒ 
	int type;//NONE,KEY,FOO,WCG,SMO,PER,LAS,DAR,SPE,DAG,SWO,BLA
	int und;//����ŵ���Ʒ��id��û�У�-1�� 
	union{
		int key;//0,KEY1,KEY2,KEY3,KEY4
		food foods;
		weapon_charge wcg;
		int lsrE,sprE,daggerE,swordE,bladeE;
		see_through_prop stp;
	};
	void init(){
		type=NONE;
		und=-1;
		key=lsrE=sprE=daggerE=swordE=bladeE=0;
		foods.init();wcg.init();stp.init();
	}
	bool nowea(){
		return type<LAS;
	}
};
bool operator==(object a,object b){
	if(a.type!=b.type) return false;
	switch(a.type){
		case KEY:return a.key==b.key;
		case FOO:return a.foods==b.foods;
		case WCG:return a.wcg==b.wcg;
		case LAS:case DAR:case SPE:case DAG:case SWO:case BLA:return 1;
		case SMO:return 1;
		case PER:return a.stp==b.stp;
	}
	return true;
}
vector<object> objects;//��ͼ������Ʒ���б� 
bool type_weapon(int type){
	return type>=LAS;
}
int object_type(int x){//objects[item_lab[x]].type 
	vector<int> &v=player1.items.item_lab;
	if(x<0||x>=v.size()) return NONE;
	int id=v[x];
	if(id<0) return NONE;
	return objects[id].type;
}
void new_object(object obj,int &fir){//�����µ���Ʒ 
	obj.und=fir;
	fir=objects.size();//��0��ʼ��� 
	objects.push_back(obj);
}
bool add_object1(position_3D pos,int id){//������Ʒobects[id]��pos
	if(id<0) return 0;
	MAP &POS=game_map[pos.x][pos.y][pos.z];
	thing &THING=POS.things;
	objects[id].und=THING.fir;
	THING.fir=id; 
	if(POS.ist.player==lst_see_time) pos_change.insert(pos);//��Ļ���� 
	return 1;
}
bool del_object1(position_3D pos){//����pos���ϲ���Ʒ
	MAP &POS=game_map[pos.x][pos.y][pos.z];
	thing &THING=POS.things;
	int id=THING.fir;
	if(id<0) return 0;
	THING.fir=objects[id].und;
	objects[id].und=-1;
	if(POS.ist.player==lst_see_time) pos_change.insert(pos);//��Ļ���� 
	return 1;
}
bool add_object2(int id,int x){//������Ʒobjects[id]��item_lab[x]���ϲ�/���²�  
	if(id<0) return 0;
	item &items=player1.items;
	vector<int> &v=items.item_lab;
	if(x<0||x>=v.size()) return 0;
	if(v[x]<0) items.il_change=true;
	if(v[x]>=0&&type_weapon(objects[v[x]].type)){
		int tmp=v[x];
		while(objects[tmp].und>=0) tmp=objects[tmp].und;//���v[x]�ǿվͰ������������²� 
		objects[tmp].und=id;
		items.item_num[x]++;//����+1 
		items.num_change=true;
		if(x==items.wpn.primary||x==items.wpn.secondary){
			items.wpn.sw_change=items.wpn.data_change=1;//��ʱ���� 
		}
		return 1;//�ǵ÷��� 
	}
	objects[id].und=v[x];
	v[x]=id;
	items.item_num[x]++;
	items.num_change=true;
	return 1;
}
bool del_object2(int x){//����item_lab[x]���ϲ���Ʒ
	item &items=player1.items;
	vector<int> &v=items.item_lab;
	if(x<0||x>=v.size()) return 0;
	int id=v[x];
	if(id<0) return 0;
	v[x]=objects[id].und;
	objects[id].und=-1;
	items.item_num[x]--;//����-1 
	if(v[x]<0) items.il_change=true;
	items.num_change=true;
	weapon_carried &wpn=items.wpn;
	if(x==wpn.primary){
		if(v[x]<0){
			wpn.primary=wpn.secondary;//���������ɸ����� 
			wpn.secondary=-1;//������ �� 
			wpn.sw_change=1;
		}
		wpn.data_change=1;//��ʱ���� 
	}
	if(x==wpn.secondary){
		if(v[x]<0){
			wpn.secondary=-1;//������ �� 
			wpn.sw_change=1;
		}
		wpn.data_change=1;//��ʱ���� 
	}
	return 1;
}
void player_putback_weapon(int id){
	if(id<0) return;
	object &ob=objects[id];
	item &items=player1.items;
	vector<int> &v=items.item_lab;
	bool success=0;
	for(int i=0;i<v.size();i++)
		if(v[i]>=0){
			object ob2=objects[v[i]];
			if(ob==ob2){//����һ�������� 
				ob.und=v[i];
				v[i]=id;
				success=1;
				break;
			}
		}
	if(!success){
		for(int i=0;i<v.size();i++)
			if(v[i]<0){//��Ȼ�ͷ��ڿ�λ�� 
				ob.und=v[i];
				v[i]=id;
				break;
			}
		/*
		if(!success){//�ٲ�Ȼ�¿�һ��λ�� 
			v.push_back(-1);
			del_object1(pos);
			add_object2(id,v.size()-1);
		}*/
	}
} 
bool add_weapon(int x){//�ó������� 
	item &items=player1.items;
	vector<int> &v=items.item_lab;
	if(x<0||x>=v.size()) return 0;
	weapon_carried &wpn=items.wpn;
	wpn.secondary=wpn.primary;
	wpn.primary=x;
	wpn.data_change=wpn.sw_change=1;
	return 1;
}
bool object_addE(int x,int add){//��������Ʒ���еļ���ǹ����ì�� 
	item &items=player1.items;
	vector<int> &v=items.item_lab;
	weapon_carried &wpn=items.wpn;
	if(x<0||x>v.size()) return 0;
	int id=v[x];
	if(id<0) return 0;
	object &obj=objects[id];
	int flag=0;
	switch(obj.type){
		case LAS:
			obj.lsrE+=add;
			if(obj.lsrE<=0) flag=2;
			else flag=1;
			break;
		case SPE:
			obj.sprE+=add;
			if(obj.sprE<=0) flag=2;
			else flag=1;
			break;
		case DAG:
			obj.daggerE+=add;
			if(obj.daggerE<=0) flag=2;
			else flag=1;
			break;
		case SWO:
			obj.swordE+=add;
			if(obj.swordE<=0) flag=2;
			else flag=1;
			break;
		case BLA:
			obj.bladeE+=add;
			if(obj.bladeE<=0) flag=2;
			else flag=1;
			break;
	}
	if(flag==2) del_object2(x);//����/�;úĹ� 
	if(flag) wpn.data_change=1;
	return flag;
}
int object_cnt(int id){//�ѵ����� 
	int cnt=0;
	while(id>=0){
		id=objects[id].und;
		cnt++;
	}
	return cnt;
}
queue<position_3D> spears,swords,blades,laser_beams;//�ϴ���ʾ����Ļ��ì�����������������Ķ��� 
queue<pair<position_3D,int> > laser_beam_light;//������������Χ���� 
struct flying_dart{//���еĻ�����
	position_3D pos;//���� 
	int tx,ty;//ÿ�ηɶ���ʱ�� 
	velocity vx,vy;//x��y�����ϵ��ٶȣ��������� 
	int id;//��� 
	void init(position_3D u,double angle,int _id){//��ʼ��
		id=_id;
		pos=u; 
		tx=ty=game_time; 
		double speed=15;//�������ٶ�15m/s 
		double tmpx=cos(angle/180.0*PI),tmpy=sin(angle/180.0*PI);//vx/v��vy/v���������� 
		vx.speed=speed*tmpx;vx.vt();
		vy.speed=speed*tmpy;vy.vt();
		if(vx.wait_time<vy.wait_time) ty+=vy.wait_time-vx.wait_time;
		else tx+=vx.wait_time-vy.wait_time;
	}
}; 
queue<flying_dart> darts;//�����еĻ����ڶ���
struct flying_mvb{//���еĿ��ƶ���Ʒ
	position_3D pos;//���� 
	int lst_move_time;//�ϴηɶ�ʱ�� 
	void init(position_3D u){
		pos=u; 
		lst_move_time=game_time; 
	} 
}; 
queue<flying_mvb> mvbs;//�����еĶ�������
struct bug{//���ӽṹ��
	position_3D pos;//���� 
	int d;//���� 
	velocity vlc;//�ٶ�  
	life_injury lfin;//����
	int lst_ud;//�ϴ�����¥ʱ�䣨��ֹ����һ��¥��� 
	bool change_pos;//�������ˣ��ı�λ�ø��� 
	bool update;//�Ƿ�Ҫ���£���С�������� 
	int enter_nest;//�ϴν�����Ѩ��ʱ�� 
	void init(position_3D u,double speed);
};
vector<bug> bugs;//��ţ�0~MAX_BUG_NUM-1
queue<int> Qbug_hurt;//���Ӷ��У���ţ�
struct bug_nest{//���ӳ�Ѩ�ڽṹ��
	position_3D pos;//����
	life_injury lfin;//����
	bool destroy;//�Ƿ񱻴ݻ� 
	void init(position_3D u);
};
vector<bug_nest> bug_nests;//���ӵĳ�Ѩ��
struct spider{//֩��ṹ�� 
	position_3D pos;//���� 
	position_3D bir;//������ 
	position_3D prey;//���������ֵ�λ�� 
	int d;//����4������¥��������Ѩ�ڣ� 
	velocity vlc;//�ٶ�  
	life_injury lfin;//����
	bool kind;//0��A�� 1��B�� 
	bool change_pos;//�������ˣ��ı�λ�ø��� 
	bool update;//�Ƿ�Ҫ���£���С�������� 
	void init(position_3D u,bool k);
}; 
vector<spider> spiders;//��ţ�0~MAX_SPIDER_NUM-1
queue<int> Qspider_hurt;//֩����У���ţ�
struct flying_ssk{//���е�֩��˿
	position_3D pos;//���� 
	int tx,ty;//ÿ�ηɶ���ʱ�� 
	velocity vx,vy;//x��y�����ϵ��ٶȣ��������� 
	void init(position_3D u,double speed,double angle){//��ʼ������dart�ģ� 
		pos=u; 
		tx=ty=game_time; 
		double tmpx=cos(angle/180.0*PI),tmpy=sin(angle/180.0*PI);//vx/v��vy/v���������� 
		vx.speed=speed*tmpx;vx.vt();
		vy.speed=speed*tmpy;vy.vt();
		if(vx.wait_time<vy.wait_time) ty+=vy.wait_time-vx.wait_time;
		else tx+=vx.wait_time-vy.wait_time;
	}
}; 
queue<flying_ssk> ssks;//�����е���˿����
string spider_image[2][4][3][3]={//AB��*4����*3y*3x 
	{//A�� 
		{//d=0
			{"�v ","��","�u "},
			{"��","��","��"},
			{"�u ","��","�v "},
		},
		{//d=1
			{"�v ","��","�u "},
			{"��","��","��"},
			{"�u ","��","�v "},
		},
		{//d=2 
			{"�v ","��","�u "},
			{"��","��","��"},
			{"�u ","��","�v "},
		},
		{//d=3
			{"�v ","��","�u "},
			{"��","��","��"},
			{"�u ","��","�v "},
		}
	},
	{//B�� 
		{//d=0
			{"��","","��"},
			{"��","��","��"},
			{"�u ","��","�v "},
		},
		{//d=1
			{"�v ","��","��"},
			{"��","��",""},
			{"�u ","��","��"},
		},
		{//d=2 
			{"�v ","��","�u "},
			{"��","��","��"},
			{"��","","��"},
		},
		{//d=3
			{"��","��","�u "},
			{"","��","��"},
			{"��","��","�v "},
		}
	}
};//���ַ����ǲ������ 
		struct skill_vampire{
			int time;
			void init(){
				time=0;
			}
		};
		struct skill_through{
			bool use;//�Ƿ�����ʹ�� 
			int time;//Ч����ʼ/����ʱ�� 
			void init(){
				use=time=0;
			}
		};
		struct skill_disappear{ 
			bool use;//�Ƿ�����ʹ�� 
			int time;//Ч����ʼ/����ʱ�䣨���л�use��ʱ��㣩 
			int maxt;//�������ʱ�� 
			int kind;//���ࣨ1����̬��αװ��ǽ 2����ʧ�� 
			void init(){
				use=time=maxt=0;kind=1; 
			}
		};
		struct skill_instant{
			int p;//ÿ���ƶ�˲�Ƹ��� 
			int dis;//˲�ƺ������������ 
			void init(){
				p=dis=0;
			}
		};
		struct skill_evade{
			bool use;//�Ƿ�����ʹ��
			int k;//���ܸ��� 
			void init(){
				use=k=0;
			}
		};
		struct skill_rock{
			bool use;//�Ƿ�����ʹ�� 
			double k;//������ϵ�����ٶ�*=k�� 
			void init(){
				use=0;k=1;
			}
		};
	struct special_attribute{//��������
		int attack,defense;
		//�����Լ��ܣ�VAMPIRE,DISAPP,THROUGH,INSTANT���������Լ��ܣ�EVADE,ROCK,SHIELD�� 
		skill_vampire vpr;
		skill_through thr;
		skill_disappear disa;
		skill_instant ins;
		skill_evade eva;
		skill_rock rck;
		void init(int a=0,int d=0){
			attack=a;defense=d;
			vpr.init();thr.init();disa.init();ins.init();
			eva.init();rck.init();
		}
		bool can_through(){//�ܷ�ǽ 
			return attack==THROUGH&&thr.use;
		} 
		bool can_disappear(){//�Ƿ�����
			return attack==DISAPP&&disa.use;
		}
		bool can_evade(){//�Ƿ����� 
			return (defense==EVADE||defense==SHIELD)&&RAND_BOOL(eva.k);
		}
	};
struct ghost{//��ṹ�� 
	position_3D pos;//���� 
	position_3D goal;//�ƶ�Ŀ�� 
	int d;//����4������¥��������Ѩ�ڣ� 
	velocity vlc;//�ٶ�  
	life_injury lfin;//����
	special_attribute spat;//���� 
	special_effect spe;//����Ч�� 
	double attack_time;//��Ӧʱ�䣨0~1��
	//ָÿ���ƶ����ں�attack_time*vlc.wait_time�������� 
	bool change_pos;//�������ˣ��ı�λ�ø��� 
	bool update;//�Ƿ�Ҫ���£���С�������� 
	bool rampage;//�Ƿ��ں��ֱײ�������𲽣� 
	void init(position_3D u,int att,int def);
};
vector<ghost> ghosts;//��ţ�0~MAX_GHOST_NUM-1
queue<int> Qghost_hurt;//����У���ţ� 
queue<position_3D> pos_dead;//ʬ����� 
struct barrel{//Ͱ�ṹ��
	position_3D pos;//���� 
	velocity vlc;//�ٶ� 
	bool stage;//״̬����/���� 
}; 
struct tnt{//ը���ṹ�� 
	position_3D pos;//����
	bool stage;//״̬����ֹ/��ȼ�� 
};
queue<barrel> barrels;//Ͱ����
queue<tnt> TNTs;//ը������
queue<PPII> message_box;//��Ϣ��aɱ��b�� 
queue<position_3D> pos_affect_light,lights_update;//���иı�״̬���Թ������Ӱ���λ�á���Ҫ���£�LGT.update==1�������еƵ�λ�� 
vector<position_3D> light_area[MAX_LIGHT_NUM];//ÿ��id�ĵ����һ�θ��µĹ��շ�Χ 
queue<position_3D> pos_fog;//�п�����ɢ���� 
int dx4[4]={0,1,0,-1};
int dy4[4]={-1,0,1,0};
//ǰ���ҡ����� 
int dx8[8]={0,1,1,1,0,-1,-1,-1};
int dy8[8]={-1,-1,0,1,1,1,0,-1};
//ǰ����ǰ���ҡ��Һ󡢺��������ǰ 
queue<position_3D> Q;
bool vst[MAX_LENGTH+9][MAX_WIDTH+9][MAX_HEIGHT*2+9];
int dis[MAX_LENGTH+9][MAX_WIDTH+9][MAX_HEIGHT*2+9];
int dis_to_exit[MAX_LENGTH+9][MAX_WIDTH+9][MAX_HEIGHT*2+9],dis_to_player[MAX_LENGTH+9][MAX_WIDTH+9][MAX_HEIGHT*2+9];
int pos_cnt[MAX_LENGTH+9][MAX_WIDTH+9][MAX_HEIGHT*2+9];
int mx_dis_to_player;
bool pos_in_room[MAX_LENGTH+9][MAX_WIDTH+9][MAX_HEIGHT*2+9];
vector<position_3D> pos_dis_to_player_door[MAX_LENGTH*MAX_WIDTH*MAX_HEIGHT*2],pos_dis_to_player_key[MAX_LENGTH*MAX_WIDTH*MAX_HEIGHT*2];
vector<position_3D> pos_in_nest;
//BFSר��
int sum1[MAX_LENGTH+9][MAX_WIDTH+9],sum2[MAX_LENGTH+9][MAX_WIDTH+9];
//ǰ׺�� 
bool flagx[MAX_LENGTH+9],flagy[MAX_WIDTH+9];
int val_x[MAX_LENGTH+9][2],val_y[MAX_WIDTH+9][2];
//��������ӳ�� 
int fa_dsu[MAX_LENGTH*MAX_WIDTH*MAX_HEIGHT*2+9];
//���鼯 
bool stair_exist[MAX_HEIGHT+9][2];//��¼ĳ��¥��û����0/��1¥��
vector<position_3D> divided_walls;//�ָ�ǽ/������¥�ݵĵذ� 
//�Թ����� 
int occlusion[4][360];
int cnt_visible[4]={360,360,360,360};
double vague[4][360][3];//��ͬ��ɫ��ģ���̶ȣ�0.00����ȫ������1.00��ɶҲ�����壩 
queue<position_3D> pos_vague;//ģ����λ�� 
//��Ұ���� 
char sound_spider_move[5][20]={
	"�����ж�1.wav",
	"�����ж�2.wav",
	"�����ж�3.wav",
	"�����ж�4.wav",
	"�����ж�5.wav"
};
//���� 
double screen_zoom;//��Ļ����ֵ
//��Ϸ��־
std::ofstream logFile1("game_log.txt",std::ios::app),logFile2("game_log.txt",std::ios::trunc); 
//���� 
void logMessage(const std::string& message,int kind=1){//��Ϸ��־ 
	if(kind==1) logFile1<<message<<std::endl;
	else logFile2<<message<<std::endl;
	/*
    if(logFile.is_open()){
        logFile<<message<<std::endl;
        logFile.close();
    }*/
}
void clearGameLog(){
	logMessage("",2);
	/*
	//�Խض�ģʽ���ļ����������ļ�����
    std::ofstream file("game_log.txt", std::ios::trunc);
    //����ļ��ɹ��򿪣����Զ��رգ���Ϊ ofstream ��������ʱ��ر��ļ�
    */
}
double get_screen_zoom(){//��ȡ��Ļ����ֵ
	HWND hWnd=GetDesktopWindow();
    HMONITOR hMonitor=MonitorFromWindow(hWnd, MONITOR_DEFAULTTONEAREST);
    //��ȡ�������߼������߶�
    MONITORINFOEX miex;
    miex.cbSize=sizeof(miex);
    GetMonitorInfo(hMonitor, &miex);
    int cxLogical=(miex.rcMonitor.right-miex.rcMonitor.left);
    int cyLogical=(miex.rcMonitor.bottom-miex.rcMonitor.top);
    //��ȡ��������������߶�
    DEVMODE dm;
    dm.dmSize=sizeof(dm);
    dm.dmDriverExtra=0;
    EnumDisplaySettings(miex.szDevice,ENUM_CURRENT_SETTINGS,&dm);
    int cxPhysical=dm.dmPelsWidth;
    int cyPhysical=dm.dmPelsHeight;
    //���ű������� ��ʵ����ʹ���κ�һ�����ɣ� 
    double horzScale=((double)cxPhysical/(double)cxLogical);//�������ֵ 
    double vertScale=((double)cyPhysical/(double)cyLogical);//�߶�����ֵ 
    return horzScale;
}
position_2D pos_mouse(){//��굱ǰλ�ã�x��һ��Ϊż���� 
	GetCursorPos(&ScreenP);
	ScreenToClient(h,&ScreenP);
	//ScreenP.x*=screen_zoom;ScreenP.y*=screen_zoom;//��Ļ���ű��� *screen_zoom
	GetCurrentConsoleFont(hout,FALSE,&consoleCurrentFont);//��ȡ������Ϣ
	consoleCurrentFont.dwFontSize.X=consoleCurrentFont.dwFontSize.Y/2;
	position_2D pos; 
	int sx=consoleCurrentFont.dwFontSize.X,sy=consoleCurrentFont.dwFontSize.Y;
	pos.x=ScreenP.x/sx;
	pos.y=(ScreenP.y-sy*2)/sy;
	return pos;
}
void hideCursor(){//���ع�� 
	CONSOLE_CURSOR_INFO cursor_info1={1,0};
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE),&cursor_info1);
} 
void gotoxy(int x,int y){//�ƶ����
	if(x<0||x>MAX_SCREEN_LENGTH-1||y<0||y>MAX_SCREEN_WIDTH-1) return;
	COORD pos={short(x),short(y)};
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),pos);
}
position_2D GetConsoleCursor(){
	position_2D coordScreen={0,0}; //���λ��
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	if(GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE),&csbi)){
		coordScreen.x=csbi.dwCursorPosition.X;
		coordScreen.y=csbi.dwCursorPosition.Y;
	}
	return coordScreen; //���λ��
}
bool pos_in_game_map(position_2D pos){
	return whole_screen.contain(pos)
	&&!vital_signs_area.contain(pos)&&!item_area.contain(pos)&&!weapon_area.contain(pos);
}
void SLEEP(int x){//��ʱ����λ�����룩 
	int time_now=clock();
	while(clock()-time_now<x); 
}
LARGE_INTEGER nbegin_time,nend_time,nFreq;
void init_timer(){//��ʼ�� 
    QueryPerformanceFrequency(&nFreq); 
}
void start_timer(){//��ʱ��ʼ��������һ�Σ� 
    QueryPerformanceCounter(&nbegin_time);
} 
void read_timer(){//��ʱ����ȡ����ֹͣ��ʱ��
	logMessage("read_timer()",2); 
    QueryPerformanceCounter(&nend_time);
    now_timer=(double)(nend_time.QuadPart-nbegin_time.QuadPart)/(double)nFreq.QuadPart*1000;//��λ������ 
}
void CLEAR(){
	cout.flush();
	SetConsoleTextAttribute(hout,0x07);
	system("cls");
	SetConsoleTextAttribute(hout,0x07);
}
void RGB_init(){
	DWORD dwMode=0;
	GetConsoleMode(hout,&dwMode);
	dwMode|=0x0004;
	SetConsoleMode(hout,dwMode);
}
RGB_color code_to_RGB(double light,double hue,double vague){
	/*hsvģʽ
	hue��ɫ��0~360 
	light���Զ������ȣ�>0�����Ͷ� <0�����ȣ�-100~100
	vague���Զ���ģ��ֵ 0.00~1.00 
	*/
	double l=light/100.0,s=1.0,v=1.0,r=0,g=0,b=0;
	if(light>0) s=1.0-l;
	else v=1.0+l;
	s=max(0.0,s-vague);//s=max(0.0,s-0.5);ģ��Ч������ 
	//����hsv 3���� 
	int h=floor(hue/60.0);
	double f=hue/60.0-h,p=v*(1.0-s),q=v*(1.0-f*s),t=v*(1.0-(1.0-f)*s);
	switch(h){
		case 0:r=v,g=t,b=p;
			break;
		case 1:r=q,g=v,b=p;
			break;
		case 2:r=p,g=v,b=t;
			break;
		case 3:r=p,g=q,b=v;
			break;
		case 4:r=t,g=p,b=v;
			break;
		case 5:r=v,g=p,b=q;
			break;
		case 6:r=g=b=v;
			break;
	}
	r*=255;g*=255;b*=255;
	return (RGB_color){int(r),int(g),int(b)};//rgbȡ�� 
}
void limit_int(int &a,int l,int r);
void limit_double(double &a,double l,double r);
void RGB_brightness(double (&ret)[3],double col[3],double x){//����double[3]��int�����&double[3]��->ret�� 
//x�����ȣ�brightness��double���ͷ������ 
	x=1.0+x/100.0;
	//e.g. -20->80% 20->120% 
	ret[0]=col[0]*x;
	ret[1]=col[1]*x;
	ret[2]=col[2]*x; 
	//ֱ�Ӱ��ٷֱȼ��� 
	limit_double(ret[0],0,1);
	limit_double(ret[1],0,1);
	limit_double(ret[2],0,1);
	//��ֹԽ��
	//ע��vague��Χ[0,1] 
}
void set_text_color(RGB_color back,RGB_color forw);
void set_RGBcolor(int light1,int hue1,int light2,int hue2){
	limit_int(light1,-100,100);
	limit_int(light2,-100,100);
	RGB_color back,forw;
	back=code_to_RGB(light1,hue1,0);
	back_now=MP(light1,hue1);
	forw=code_to_RGB(light2,hue2,0);
	forw_now=MP(light2,hue2);
	set_text_color(back,forw);
	//if(back_now!=MP(light1,hue1)){
	//}
	//if(forw_now!=MP(light2,hue2)){
	//}
}
RGB_color mix_color(RGB_color colA,RGB_color colB,double (&rate)[3]){
	//col=colA*(1-rate)+colB*rate
	//rate:R/G/B 
	RGB_color col;
	col.r=(1.0-rate[0])*colA.r+rate[0]*colB.r;
	col.g=(1.0-rate[1])*colA.g+rate[1]*colB.g;
	col.b=(1.0-rate[2])*colA.b+rate[2]*colB.b;
	return col;
}
void set_RGBcolor_vague(int light1,int hue1,int light2,int hue2,double (&vague)[3]){//����ģ��Ч�� 
	//vague����ǰ������ ->ǰ��������ɫ�Ļ�ϳ̶ȣ���ģ��Ч������ɫ�Ļ�ϳ̶� 
	//(light3,hue3)��ʾģ��Ч������ɫ ,int light3,int hue3
	//vague:R/G/B 
	limit_int(light1,-100,100);
	limit_int(light2,-100,100);
	for(int i=0;i<3;i++) limit_double(vague[i],0,1);
	
	back_now=MP(light1,hue1);//
	forw_now=MP(light2,hue2);//
	
	RGB_color back,forw;
	/*
	back=code_to_RGB(light1,hue1,0);
	forw=code_to_RGB(light2,hue2,0);*/
	double separate_vague=max(vague[0],max(vague[1],vague[2]));
	back=code_to_RGB(light1,hue1,separate_vague);
	forw=code_to_RGB(light2,hue2,separate_vague);
	//������ǰ��ɫ�ֱ𵥶�ģ���������ֵ���� 
	
	RGB_color back_forw;
	back_forw.r=back.r*0.9+forw.r*0.1;
	back_forw.g=back.g*0.9+forw.g*0.1;
	back_forw.b=back.b*0.9+forw.b*0.1;
	//vague=1��ǰ����������ɫ 
	back=mix_color(back,back_forw,vague);
	forw=mix_color(forw,back_forw,vague);
	//back.r=(1-vague)*back.r+vague*r;back.g=(1-vague)*back.g+vague*g;back.b=(1-vague)*back.b+vague*b;
	//forw.r=(1-vague)*forw.r+vague*r;forw.g=(1-vague)*forw.g+vague*g;forw.b=(1-vague)*forw.b+vague*b;
	//����ǰ��ɫ����vague��һ�� 
	
	//RGB_color vague_color=code_to_RGB(light3,hue3,0);//ģ�����ӵ���ɫ����Ҫ��vague�������� 
	RGB_color vague_color=code_to_RGB(0,360,0);//ģ�����Ӱ�ɫ
	//����Ч����vague[3]���� 
	back=mix_color(back,vague_color,vague);
	forw=mix_color(forw,vague_color,vague);
	
	set_text_color(back,forw);
	//if(back_now!=MP(light1,hue1)){
	//}
	//if(forw_now!=MP(light2,hue2)){
	//}
}
void wait_until(int key){
	while(1){
		if(_kbhit()){
			int c=_getch();
			if(c==key) return;
		}
	}
}
void MUSIC(const char name[],int n){//���Ʋ�������
//n����ģʽ��0Ϊֹͣ���ţ�1Ϊ����һ�Σ�2Ϊ�ظ�����
	return;//ȫ������ 
	char File[100],path[100]="./��Ƶ/";
	if(n==1||n==2) strcpy(File,"play ");
	else if(n==0) strcpy(File,"close ");
	strcat(path,name);
	strcat(File,path);
	if(n==2) strcat(File," repeat");
	mciSendString(File,NULL,0,NULL);
}
void init_dsu(int num){
	for(int i=1;i<=num;i++) fa_dsu[i]=i;
}
int find_dsu(int x){
	if(fa_dsu[x]==x) return x;
	return fa_dsu[x]=find_dsu(fa_dsu[x]); 
} 
void unit_dsu(int x,int y){
	int u=find_dsu(x),v=find_dsu(y);
	if(u==v) return;
	if(rand()%2) fa_dsu[u]=v;
	else fa_dsu[v]=u;
}
int cnt_dsu(int num){
	int cnt=0;
	for(int i=1;i<=num;i++)
		if(fa_dsu[i]==i) cnt++;
	return cnt;
}
bool pos_in_area(int posx,int posy,int areax,int areay,int areal,int areaw){//�ж������Ƿ���ָ����Χ��
	//areal ��Χ�� areaw ��Χ�� 
	return posx>=areax&&posx<=areax+areal-1&&posy>=areay&&posy<=areay+areaw-1;
}
bool pos_in_area2(int posx,int posy,int areax1,int areay1,int areax2,int areay2,int kind=1){//�ж������Ƿ���ָ����Χ��
	//areal ��Χ�� areaw ��Χ�� 
	//kind��1��2�� 
	if(kind==1) return posx>=areax1&&posx<=areax2&&posy>=areay1&&posy<=areay2;
	if(kind==2) return posx>areax1&&posx<areax2&&posy>areay1&&posy<areay2;
	return false;
}
position_2D position_3Dto2D(position_3D pos){
	return (position_2D){pos.x,pos.y};
} 
position_3D position_2Dto3D(position_2D pos,int z){
	return (position_3D){pos.x,pos.y,z};
}
position_2D position_2Dtoscr(position_2D pos){
	return (position_2D){(pos.x-screen_center.x)*2+MAX_SCREEN_LENGTH/2,(pos.y-screen_center.y)+MAX_SCREEN_WIDTH/2};
} 
position_2D position_3Dtoscr(position_3D pos){
	return (position_2D){(pos.x-screen_center.x)*2+MAX_SCREEN_LENGTH/2,(pos.y-screen_center.y)+MAX_SCREEN_WIDTH/2};
} 
position_2D position_scrto2D(position_2D pos){
	return (position_2D){(pos.x-MAX_SCREEN_LENGTH/2)/2+screen_center.x,pos.y-MAX_SCREEN_WIDTH/2+screen_center.y};
}
position_3D position_scrto3D(position_2D pos,int z){
	pos.x=pos.x/2*2;//ת����ż�� 
	return (position_3D){(pos.x-MAX_SCREEN_LENGTH/2)/2+screen_center.x,pos.y-MAX_SCREEN_WIDTH/2+screen_center.y,z};
}
//��ά����ά����Ļ��ͼ��ʾ���껥��ת�� 
direction ptp(position_3D a,position_3D b){//b->a�ķ��� 
	direction ret;
	if(a.x>b.x) ret.d2=1;//��
	else if(a.x<b.x) ret.d2=3;//��
	else ret.d2=-1;
	if(a.y<b.y) ret.d1=0;//��
	else if(a.y>b.y) ret.d1=2;//��
	else ret.d1=-1;
	/*
	gotoxy();
	set_RGBcolor(-100,0,0,0);
	cout<<"direction "<<ret.d1<<","<<ret.d2<<endl;*/
	return ret; 
}
void dtp_error(int &dir,int d,string func,int id=-1){ 
	if(dir<0||dir>=d){
		gotoxy();
		set_RGBcolor(-100,0,0,0);
		cout<<func<<": dtp error["<<id<<"]->"<<dir<<" d="<<d<<endl;
		dir=0;//�ĵ� 
	}
}
position_2D dtp2(position_2D pos,int dir,int d){//��posλ�õ�d������ʲôλ�� 
	dtp_error(dir,d,"dtp2"); 
	switch(d){
		case 4:return (position_2D){pos.x+dx4[dir],pos.y+dy4[dir]};
		case 8:return (position_2D){pos.x+dx8[dir],pos.y+dy8[dir]};
		default:return (position_2D){0,0};
	}
}
position_3D dtp3(position_3D pos,int dir,int d){//��posλ�õ�d������ʲôλ�� 
	dtp_error(dir,d,"dtp3"); 
	switch(d){
		case 4:return (position_3D){pos.x+dx4[dir],pos.y+dy4[dir],pos.z};
		case 8:return (position_3D){pos.x+dx8[dir],pos.y+dy8[dir],pos.z};
		default:return (position_3D){0,0,0};
	}
}
int turn(int dir,int op,int d=4,int id=-1){//������ǰ����d����һ��������op����TURN_RIGHT,TURN_BACK,TURN_LEFT��
	dtp_error(dir,d,"turn",id); 
	if(d==4){
		switch(op){
			case TURN_RIGHT:return (dir+1)%d;
			case TURN_BACK:return (dir+2)%d;
			case TURN_LEFT:return (dir+3)%d;
		}
	}
	else if(d==8){
		switch(op){
			case TURN_RIGHT:return (dir+2)%d;
			case TURN_BACK:return (dir+4)%d;
			case TURN_LEFT:return (dir+6)%d;
		}
	}
	return dir;
}
int atd(int angle){
	int a2=angle%90;
	int d1=(angle/90+1)%4,d2=(d1+1)%4;//d1={270~359->0 0~89->1 90~179->2 180~269->3}
	if(a2>45) return d2;
	return d1;
}
int fatd(int angle){//����ֵ��atd�෴ 
	int a2=angle%90;
	int d1=(angle/90+1)%4,d2=(d1+1)%4;//d1={270~359->0 0~89->1 90~179->2 180~269->3} �� 
	if(a2>45) return d1;
	return d2;
}
bool cmpa(int a,int b){//�Ƕ�С�� 
	return (a-b+360)%360>180;
} 
int sub_angle(int a,int b){//a��b֮�����С�нǣ���180��
	return min((a-b+360)%360,(b-a+360)%360);
} 
int calc_angle(position_3D a,position_3D b){//a->b���㷽��ǣ�int�� 
	position_3D c=b;c.x-=a.x;c.y-=a.y;
	int angle=(c.x==0?90:atan(1.0*abs(c.y)/abs(c.x))/PI*180);//C++���Ǻ���ʹ�û����� 
	//cout<<abs(c.y)<<"/"<<abs(c.x)<<"->"<<angle<<"\n";
	if(c.x<0){
		if(c.y>0) angle=180-angle;
		else angle+=180;
	}
	else if(c.y<0) angle=360-angle;
	return angle;
}
int calc_angle2(double x,double y){//��x����y���㷽��� 
	int angle=(x==0?90:atan(1.0*abs(y)/abs(x))/PI*180.0);//C++���Ǻ���ʹ�û����� 
	//cout<<abs(c.y)<<"/"<<abs(c.x)<<"->"<<angle<<"\n";
	if(x<0){
		if(y>0) angle=180-angle;
		else angle+=180;
	}
	else if(y<0) angle=360-angle;
	return angle;
}
double MAP::mass(){
	double m=0;
	switch(player_enemy){
		case SPIDER:
			m+=4; 
			if(emy.id>=0&&emy.id<spiders.size()&&spiders[emy.id].kind) m+=4;
			break;
		case GHOST:
			m+=2.5;
			break;
		case PLAYER:
			m+=2;
			break;
		case BUG:
			m+=1;
			break;
	}
	if(things.mvb.exist)
		switch(things.mvb.kind){
			case BOX:
				m+=8;
				break;
			case DESK:
				m+=4;
				break;
			case CHAIR:
				m+=2;
				break;
			case BALL:
				m+=0.67;
				break;
		}
	if(m<0.1) m+=0.1;
	return m;
}
bool wall_here(position_3D u){
	return game_map[u.x][u.y][u.z].maze==WALL;
}
bool space_here(position_3D u){
	return game_map[u.x][u.y][u.z].maze==SPACE;
}
bool exit_here(position_3D u){
	return game_map[u.x][u.y][u.z].maze==EXIT;
}
bool upstair_here(position_3D u){
	return game_map[u.x][u.y][u.z].maze==UPSTAIR;
}
bool downstair_here(position_3D u){
	return game_map[u.x][u.y][u.z].maze==DOWNSTAIR;
}
bool stair_here(position_3D u){
	return game_map[u.x][u.y][u.z].maze==UPSTAIR||game_map[u.x][u.y][u.z].maze==DOWNSTAIR;
}
bool body_here(position_3D u){
	MAP &POS=game_map[u.x][u.y][u.z];
	return POS.emy.dead&&POS.emy.body_disapp>game_time;
}
bool player_here(position_3D u){
	return player1.pos==u;
}
bool bug_here(position_3D u){
	//try{
	//	if(u.x<0||u.y<0||u.z<0) throw std::out_of_range("����Խ��");
		MAP &POS=game_map[u.x][u.y][u.z];
		int id=POS.emy.id;
		if(id<0||id>=bugs.size()){
			if(POS.player_enemy==BUG) POS.player_enemy=NOBODY;
			return 0;
		}
	//	if(id<0||id>=bugs.size()) throw std::out_of_range("����Խ��");
		bug &bg=bugs[id];
		if(POS.player_enemy==BUG&&bg.pos!=u) POS.player_enemy=NOBODY;
		if(POS.player_enemy!=BUG&&bg.pos==u) POS.player_enemy=BUG;
		return bg.pos==u;
	//}
	//catch(const std::out_of_range &e){
    //    std::cerr << "�쳣����: " << e.what() << std::endl;
	//}
	//������ṹ���е�����Ϊ׼ 
}
bool bug_nest_here(position_3D u){
	MAP &POS=game_map[u.x][u.y][u.z];
	thing &THING=POS.things;
	return THING.nst.exist;
}
bool spider_body_here(position_3D u){//֩�뱾�� 
	//try{
	//	if(u.x<0||u.y<0||u.z<0) throw std::out_of_range("����Խ��");
		MAP &POS=game_map[u.x][u.y][u.z];
		int id=POS.emy.id;
		if(id<0||id>=spiders.size()){
			if(POS.player_enemy==SPIDER) POS.player_enemy=NOBODY;
			return 0;
		}
	//	if(id<0||id>=spiders.size()) throw std::out_of_range("����Խ��");
		spider &sr=spiders[id];
		if(POS.player_enemy==SPIDER&&sr.pos!=u) POS.player_enemy=NOBODY;
		if(POS.player_enemy!=SPIDER&&sr.pos==u) POS.player_enemy=SPIDER;
		return sr.pos==u;
	//}
	//catch(const std::out_of_range &e){
    //    std::cerr << "�쳣����: " << e.what() << std::endl;
	//}
	//������ṹ���е�����Ϊ׼ 
}
bool hiden_door_here(position_3D u){
	MAP &POS=game_map[u.x][u.y][u.z];
	thing &THING=POS.things;
	return THING.hdr.exist;
} 
bool check_leg(position_3D u,position_3D v){//�ж�һ��֩�븽֫�Ƿ�ǽ���� 
	if(u.x==v.x||u.y==v.y) return true;//�ķ���һ��û����
	position_3D u2=u,v2=v;//���Խ�λ�õ��������� 
	u2.y=v.y;v2.y=u.y;//u2:(ux,vy) v2:(vx,uy)
	if(wall_here(u2)&&wall_here(v2)) return false;
	return true;
}
PSB str_spider_leg(position_3D u){
//u�����֩�븽֫���������ַ������򷵻�"" 
	try{
		PSB none=MP("",0);
		if(wall_here(u)||hiden_door_here(u)) return none;//ǽ�ڲ���ʾ֩�븽֫ 
		if(u.x<0||u.y<0||u.z<0) throw std::out_of_range("����Խ�� xyz");
		MAP &POS=game_map[u.x][u.y][u.z];
		spider_leg &slg=POS.things.slg;
		if(slg.num<=0) return none;//û�оͲ��˷�ʱ���� 
		if(slg.id>=0&&slg.id<spiders.size()){//��֩������Ϣ 
			spider &sr=spiders[slg.id];
			position_3D v=sr.pos;
			int ix=1+u.x-v.x,iy=1+u.y-v.y;//��spider_image�е�����
			if(!pos_in_area2(ix,iy,0,0,2,2)||!check_leg(u,v)||sr.kind>1||sr.kind<0||sr.d>=4||sr.d<0) return none;//�����ǽ 
			if(sr.kind>1||sr.kind<0||iy<0||iy>2||ix<0||ix>2||sr.d>=4||sr.d<0) throw std::out_of_range("����Խ�� spider_image");
			return MP(spider_image[sr.kind][sr.d][iy][ix],sr.kind);//xy��������Ļ��ʾ������������xy�ụ���ģ� 
		}
		string s="";
		for(int i=0;i<8;i++){
			position_3D v=dtp3(u,i,8);
			if(!pos_in_area2(v.x,v.y,1,1,length,width)) continue;//��ֹ���� 
			MAP &NPOS=game_map[v.x][v.y][v.z];
			if(NPOS.emy.id>=0&&NPOS.emy.id<=spiders.size()&&spider_body_here(v)&&check_leg(u,v)){//�ҵ�֩�� 
				int id=NPOS.emy.id;
				spider &sr=spiders[id];
				int j=turn(i,TURN_BACK,8,1);//������֫�ڳ����ĸ�����
				int ix=1+dx8[j],iy=1+dy8[j];//��spider_image�е�����
				if(!pos_in_area2(ix,iy,0,0,2,2)||!check_leg(u,v)||sr.kind>1||sr.kind<0||sr.d>=4||sr.d<0) return none;//�����ǽ 
				if(sr.kind>1||sr.kind<0||iy<0||iy>2||ix<0||ix>2||sr.d>=4||sr.d<0) throw std::out_of_range("����Խ�� spider_image");
				s=spider_image[sr.kind][sr.d][iy][ix];//xy��������Ļ��ʾ������������xy�ụ���ģ� 
				POS.things.slg.id=id;//�´ξͲ��������� 
				if(sr.kind&&s!="") return MP(s,1);//��ֹB��֩��ǰ�����ݸ�������֩��ĸ�֫ 
			}
		}
		return MP(s,0); 
	}
	catch(const std::out_of_range &e){
        std::cerr << "�쳣����: " << e.what() << std::endl;
	}
}
bool spider_leg_here(position_3D u){//�Ƿ���B��֩����ȣ�A��֩�������������ֻ��װ�����ã� 
	PSB ssl=str_spider_leg(u);
	return ssl.first!=""&&ssl.second;
}
bool spider_here(position_3D u){//�Ƿ�������֩�루AB����/B�ȣ� 
	return spider_body_here(u)||spider_leg_here(u);
}
bool ghost_here(position_3D u){
	//try{
	//	if(u.x<0||u.y<0||u.z<0) throw std::out_of_range("����Խ��");
		MAP &POS=game_map[u.x][u.y][u.z];
		int id=POS.emy.id;
		if(id<0||id>=ghosts.size()){
			if(POS.player_enemy==GHOST) POS.player_enemy=NOBODY;
			return 0;
		}
	//	if(id<0||id>=ghosts.size()) throw std::out_of_range("����Խ��");
		ghost &gt=ghosts[id];
		if(POS.player_enemy==GHOST&&gt.pos!=u) POS.player_enemy=NOBODY;
		if(POS.player_enemy!=GHOST&&gt.pos==u) POS.player_enemy=GHOST;
		return gt.pos==u;
	//}
	//catch(const std::out_of_range &e){
    //    std::cerr << "�쳣����: " << e.what() << std::endl;
	//}
}
bool ghost_here_a(position_3D u,int att=-1){
	if(!ghost_here(u)) return 0;
	MAP &POS=game_map[u.x][u.y][u.z];
	int id=POS.emy.id;
	if(POS.player_enemy!=GHOST||id<0||id>=ghosts.size()) return false;
	ghost gt=ghosts[id];
	return att==-1||gt.spat.attack==att;
}
bool ghost_here_d(position_3D u,int def=-1){
	if(!ghost_here(u)) return 0;
	MAP &POS=game_map[u.x][u.y][u.z];
	int id=POS.emy.id;
	if(POS.player_enemy!=GHOST||id<0||id>=ghosts.size()) return false;
	ghost gt=ghosts[id];
	return def==-1||gt.spat.defense==def;
}
bool enemy_here(position_3D u){//����B��֩�븽֫ 
	MAP &POS=game_map[u.x][u.y][u.z];
	int k=POS.player_enemy;
	return bug_here(u)||ghost_here(u)||spider_here(u);
}
bool enemy_here2(position_3D u){//������B��֩�븽֫ 
	MAP &POS=game_map[u.x][u.y][u.z];
	int k=POS.player_enemy;
	return bug_here(u)||ghost_here(u)||spider_body_here(u);
}
bool dead_here(position_3D u){//��ʬ�� 
	MAP &POS=game_map[u.x][u.y][u.z];
	return POS.emy.dead&&POS.emy.body_disapp>game_time;
}
bool nobody_here(position_3D u){//����B��֩�븽֫ 
	return !(player_here(u)||bug_here(u)||spider_here(u)||ghost_here(u));
}
bool nobody_here2(position_3D u){//������B��֩�븽֫
	return game_map[u.x][u.y][u.z].player_enemy==NOBODY;
}
bool empty_here(position_3D u){
	return game_map[u.x][u.y][u.z].things.empty();
}
bool noitem_here(position_3D u){
	return game_map[u.x][u.y][u.z].things.noitem();
}
int key_above(position_3D u){
	int id=game_map[u.x][u.y][u.z].things.fir;
	if(id<0||objects[id].type!=KEY) return false;
	return objects[id].key;
}
food food_above(position_3D u){
	int id=game_map[u.x][u.y][u.z].things.fir;
	if(id<0||objects[id].type!=FOO) return food00;
	return objects[id].foods;
}
bool smb_above(position_3D u){
	int id=game_map[u.x][u.y][u.z].things.fir;
	if(id<0||objects[id].type!=SMO) return false;
	return true;
}
see_through_prop ppt_above(position_3D u){
	int id=game_map[u.x][u.y][u.z].things.fir;
	if(id<0||objects[id].type!=PER) return ppt00;
	return objects[id].stp;
}
int weapon_above(position_3D u){
	int id=game_map[u.x][u.y][u.z].things.fir;
	if(id<0||objects[id].nowea()) return 0;
	return objects[id].type;
}
bool door_here(position_3D u,int state=-1){
	return game_map[u.x][u.y][u.z].things.kdr.exist
	&&(state==-1||game_map[u.x][u.y][u.z].things.kdr.state==state);
}
bool key_door_here(position_3D u){
	return game_map[u.x][u.y][u.z].things.kdr.exist;
}
bool locked_door_here(position_3D u){
	return door_here(u,0);
}
bool open_door_here(position_3D u){
	return door_here(u,1);
}
bool closed_door_here(position_3D u){
	return door_here(u,2);
}
bool door1_here(position_3D u){
	return game_map[u.x][u.y][u.z].things.kdr.exist&&game_map[u.x][u.y][u.z].things.kdr.kind==DOOR1;
}
bool door2_here(position_3D u){
	return game_map[u.x][u.y][u.z].things.kdr.exist&&game_map[u.x][u.y][u.z].things.kdr.kind==DOOR2;
}
bool door3_here(position_3D u){
	return game_map[u.x][u.y][u.z].things.kdr.exist&&game_map[u.x][u.y][u.z].things.kdr.kind==DOOR3;
}
bool door4_here(position_3D u){
	return game_map[u.x][u.y][u.z].things.kdr.exist&&game_map[u.x][u.y][u.z].things.kdr.kind==DOOR4;
}
bool (*doorx_here[4])(position_3D)={door1_here,door2_here,door3_here,door4_here};
bool laser_beam_here(position_3D u){
	MAP &POS=game_map[u.x][u.y][u.z];
	thing &THING=POS.things;
	return THING.lsr.exist;
} 
bool mirror_here(position_3D u){
	MAP &POS=game_map[u.x][u.y][u.z];
	thing &THING=POS.things;
	return THING.mirrors.exist;
}
int mirror_relect(int md,int side,int dir){//���䷽�����
	int d1=turn(dir,TURN_LEFT),d2=turn(dir,TURN_RIGHT),d3=md;
	if(side==1){
		if(dir==d3) return d2;
		else if(d2==d3) return d1;
		return -1;
	}
	else{
		if(dir%2==d3) return d2;
		return d1;
	} 
} 
bool normv_here(position_3D u){
	return !game_map[u.x][u.y][u.z].things.mvb.exist;
}
bool box_here(position_3D u){
	MAP &POS=game_map[u.x][u.y][u.z];
	thing &THING=POS.things;
	return THING.mvb.exist&&THING.mvb.kind==BOX;
}
bool closed_box_here(position_3D u){//ȫ�ص����� 
	MAP &POS=game_map[u.x][u.y][u.z];
	thing &THING=POS.things;
	movable &MVB=THING.mvb;
	return MVB.exist&&MVB.kind==BOX&&MVB.door[0]+MVB.door[1]+MVB.door[2]+MVB.door[3]==0;
}
bool closed_box_here(position_3D u,int d){
	if(d<0||d>4) return true;
	MAP &POS=game_map[u.x][u.y][u.z];
	thing &THING=POS.things;
	movable &MVB=THING.mvb;
	return MVB.exist&&MVB.kind==BOX&&MVB.door[d]==0;
}
bool open_box_here(position_3D u){//ȫ�������� 
	MAP &POS=game_map[u.x][u.y][u.z];
	thing &THING=POS.things;
	movable &MVB=THING.mvb;
	return MVB.exist&&MVB.kind==BOX&&MVB.door[0]+MVB.door[1]+MVB.door[2]+MVB.door[3]==4; 
}
bool open_box_here(position_3D u,int d){
	if(d<0||d>4) return true;
	MAP &POS=game_map[u.x][u.y][u.z];
	thing &THING=POS.things;
	movable &MVB=THING.mvb;
	return MVB.exist&&MVB.kind==BOX&&MVB.door[d]==1;
}
bool mvb_here(position_3D u,int lock=-1){
	MAP &POS=game_map[u.x][u.y][u.z];
	thing &THING=POS.things;
	return THING.mvb.exist&&(lock==-1||POS.fcmv.lock==lock);
}
bool mvb_through(position_3D u,int dir){
	MAP &POS=game_map[u.x][u.y][u.z];
	thing &THING=POS.things;
	mirror &MIRRORS=THING.mirrors;
	return !(wall_here(u)||door_here(u,0)||door_here(u,2)||mvb_here(u,1)
	||mirror_here(u)&&mirror_relect(MIRRORS.dir,MIRRORS.side,dir)==-1
	||spider_leg_here(u));
}
bool flying_thing_here(position_3D u){
	MAP &POS=game_map[u.x][u.y][u.z];
	return (mvb_here(u)||nobody_here2(u))&&POS.fcmv.lock==1;
}
bool window_here(position_3D u){
	return game_map[u.x][u.y][u.z].things.windows.exist;
}
bool curtain_here(position_3D u){
	return space_here(u)&&game_map[u.x][u.y][u.z].things.crt.exist;
}
bool nest_here(position_3D u){
	return space_here(u)&&game_map[u.x][u.y][u.z].things.nst.exist;
}
bool food_here(position_3D u){
	MAP &POS=game_map[u.x][u.y][u.z];
	thing &THING=POS.things;
	return THING.foods.exist();
}
bool smoke_bomb_here(position_3D u){
	MAP &POS=game_map[u.x][u.y][u.z];
	thing &THING=POS.things;
	return THING.smb.exist;
}
bool ppt_here(position_3D u){
	MAP &POS=game_map[u.x][u.y][u.z];
	thing &THING=POS.things;
	return THING.ppt.exist;
}
bool divided_here(position_3D u){
	MAP &POS=game_map[u.x][u.y][u.z];
	thing &THING=POS.things;
	return wall_here(u)||THING.hdr.exist;
}
int divided_part(position_3D u){//һ��ǽ��Χ�ָ����ֵ����� 
	int cnt=0;
	init_dsu(4);//��ʼ�� 
	for(int i=0;i<4;i++){ 
		int j=turn(i,TURN_LEFT,4,2),k=turn(i,TURN_RIGHT,4,3);//���ڷ��� 
		position_3D v1=dtp3(u,i,4),v2=dtp3(u,j,4),v3=dtp3(u,k,4);//�ķ���
		position_3D v4=dtp3(v1,j,4),v5=dtp3(v1,k,4);//�Խ� 
		int a=i+1,b=j+1,c=k+1;//���� 
		if(!divided_here(v1)){
			if(!divided_here(v2)&&!divided_here(v4)) unit_dsu(b,a);//�����ͨ 
			if(!divided_here(v3)&&!divided_here(v5)) unit_dsu(c,a);//�ұ���ͨ 
		}
		else cnt++;
	}
	return cnt_dsu(4)-cnt;
}
bool no_mirror_around(position_3D pos){//���һ��λ�û᲻���뾵�����ڻ��غ�
	if(game_map[pos.x][pos.y][pos.z].things.mirrors.exist) return false; 
	for(int i=0;i<4;i++){
		position_3D v=dtp3(pos,i,4);
		if(pos_in_area2(v.x,v.y,1,1,length,width,2)
		&&game_map[v.x][v.y][v.z].things.mirrors.exist) return false;
	}
	return true;
}
bool worth_relecting(position_3D pos){//�������λ�ö���������õ� 
	return space_here(pos)||stair_here(pos);
} 
bool in_room(position_3D pos){//λ����ĳ�������� 
	if(wall_here(pos)) return false;
	for(int i=0;i<4;i++){
		int j=turn(i,TURN_RIGHT,4,4);
		position_3D a=dtp3(pos,i,4),b=dtp3(pos,j,4);
		if(wall_here(a)) continue;
		if(wall_here(b)){
			i++;
			continue;
		}
		position_3D c=dtp3(a,j,4);//pos��i����j����iƫj�����λ��
		if(!wall_here(c)) return true; 
	}
	return false;
}
bool in_walls(position_3D pos){//λ��������һƬ��ǽ�����2*2��С�� 
	//��������ȫ�෴ 
	if(!wall_here(pos)) return false;
	for(int i=0;i<4;i++){
		int j=turn(i,TURN_RIGHT,4,5);
		position_3D a=dtp3(pos,i,4),b=dtp3(pos,j,4);
		if(!wall_here(a)) continue;
		if(!wall_here(b)){
			i++;
			continue;
		}
		position_3D c=dtp3(a,j,4);//pos��i����j����iƫj�����λ��
		if(wall_here(c)) return true; 
	}
	return false;
}
bool fog_through(position_3D u,position_3D pos){//�������Դ������� pos->u
	MAP &POS=game_map[u.x][u.y][u.z];
	thing &THING=POS.things;
	int door_d_u=atd(calc_angle(u,pos)),door_d_pos=atd(calc_angle(pos,u));
	return !(wall_here(u)||door_here(u,0)||door_here(u,2)||window_here(u)
	||(u.z==pos.z//ע�����ӵ��ж� 
	?closed_box_here(u,door_d_u)||closed_box_here(pos,door_d_pos)
	:box_here(u)||box_here(pos))
	);//ֻ�ڳ�Ѩ����ɢ &&u.z>height
	//ǽ���š��䡢�� 
}
bool block_light(position_3D u){//���ڴ�λ�ã�λ�ñ����ڵ���Ұ 
	MAP &POS=game_map[u.x][u.y][u.z];
	thing &THING=POS.things;
	movable &MVB=THING.mvb;
	return box_here(u)&&!open_box_here(u);
}
bool light_through(position_3D u,int kind=2){//���߿���ֱ�Ӵ������λ��
//kind=1�����⣨���Դ������ӣ����޷�����B��֩����ȣ� 
//kind=2�����ߣ����Դ������𣿣� 
//kind=3��B��֩������ߣ�����͸���Լ����ȿ��� 
	MAP &POS=game_map[u.x][u.y][u.z];
	thing &THING=POS.things;
	ghost gt;gt.init(pos000,0,0);
	bool through_ghost=true;//�����ܷ񴩹���û�й��Ϊtrue 
	if(ghost_here(u)&&POS.emy.id>=0&&POS.emy.id<ghosts.size()){
		gt=ghosts[POS.emy.id];
		through_ghost=(gt.spat.can_disappear()?gt.spat.disa.kind!=1:1);
	}
	movable &MVB=THING.mvb;
	bool box_state=(box_here(u)&&!open_box_here(u));//���ϵ����� 
	bool door_state=((door_here(u,0)||door_here(u,2))&&!THING.kdr.light_through);//���ϵĲ�͸���� 
	bool maze_state=(space_here(u)||stair_here(u));
	bool curtain_state=(THING.crt.exist&&nobody_here(u)&&!THING.spr.exist&&!THING.bld.exist);
	if(kind==1)
		return !(box_state
		||THING.hdr.exist||door_state)
		&&!spider_leg_here(u)
		&&(maze_state||(THING.windows.exist&&THING.windows.state));
	else if(kind==2)
		return !(box_state
		||THING.hdr.exist||door_state||curtain_state
		)//"��" ||THING.snt.endurance>75
		&&!spider_leg_here(u)
		&&(maze_state||(THING.windows.exist&&THING.windows.state))&&through_ghost;
	else
		return !(box_state
		||THING.hdr.exist||door_state||curtain_state
		)//"��" ||THING.snt.endurance>75
		&&(maze_state||(THING.windows.exist&&THING.windows.state))&&through_ghost;
}
bool light_through2(position_3D u,int d,int kind=2){//���߿�����d�������u���������λ��
	//calculate_visionר�ã��ķ��� 
//kind=1�����⣨���Դ������ӣ� 
//kind=2������
	MAP &POS=game_map[u.x][u.y][u.z];
	thing &THING=POS.things;
	ghost gt;gt.init(pos000,0,0);
	bool through_ghost=true;//�����ܷ񴩹���û�й��Ϊtrue 
	if(ghost_here(u)&&POS.emy.id>=0&&POS.emy.id<ghosts.size()){
		gt=ghosts[POS.emy.id];
		through_ghost=(gt.spat.can_disappear()?gt.spat.disa.kind!=1:1);
	}
	movable &MVB=THING.mvb;
	int d2=turn(d,TURN_BACK);//����2����������Ҫ�ж� 
	if(kind==1)
		return !(closed_box_here(u,d)||closed_box_here(u,d2)//���ϵ����� 
		||THING.hdr.exist||((door_here(u,0)||door_here(u,2))&&!THING.kdr.light_through))//���ϵĲ�͸���� 
		&&!spider_leg_here(u)
		&&(space_here(u)||stair_here(u)||(THING.windows.exist&&THING.windows.state));
	else
		return !(closed_box_here(u,d)||closed_box_here(u,d2)//���ϵ����� 
		||THING.hdr.exist||((door_here(u,0)||door_here(u,2))&&!THING.kdr.light_through)||(THING.crt.exist&&nobody_here(u)&&!THING.spr.exist)
		)//"��" ||THING.snt.endurance>75
		&&!spider_leg_here(u)
		&&(space_here(u)||stair_here(u)||(THING.windows.exist&&THING.windows.state))&&through_ghost;
}
double light_vague(position_3D u,int col){//�˴���������Ұ��ģ��Ч���ĳ̶ȣ�����ֵ��0.00~1.00������RGB 
	MAP &POS=game_map[u.x][u.y][u.z];
	thing &THING=POS.things;
	double ret=min(100.0,THING.fogs.absorbance[col])/100.0;
	//=THING.fogs.absorbance/100.0;��  or  =max(0,THING.snt.endurance-50)*1.0/100.0;"˿ ��" 
	return max(min(ret,1.0-eps),0.0+eps);//��ֹԽ�� 
}
bool push_thing(position_3D pos,int dir,int kind);
int spiderB_part_through(position_3D u,int dir,int d){//B��֩������ĳһ������ײ��� 
//dir:�ƶ��ķ��� d:�ȵİ˷���/���壨d=8�� 
	if(dir>=4||dir<0||d>8||d<0) return false;
	MAP &POS=game_map[u.x][u.y][u.z];
	thing &THING=POS.things;
	movable &MVB=THING.mvb;
	bool tmp=(MVB.exist?MVB.kind!=BOX:1)&&!(door_here(u,0)||door_here(u,2)||THING.hdr.exist||THING.lsr.exist)&&(stair_here(u)||space_here(u));
	if(d<8){
		if(d%2==0){//�ķ��� 
			if(d==dir*2) return true;//��ǰ�����ʲô������ 
			return tmp&&!POS.fcmv.lock
			//&&!THING.spr.existB��֩���Ȳ�����ì�����ǻᱻ��ס 
			&&!spider_body_here(u);
			//���Դ���Ʒ������ȥ�����ӡ��ɵĲ��У����ܴ��������ţ� 
		}
		else{//б���ж������һ�㣩 
			if(!tmp) return -1;//б��ס�۷� 
			return !POS.fcmv.lock
			&&!THING.lsr.exist//&&(stair_here(u)||space_here(u))
			//&&!THING.spr.exist B��֩���Ȳ�����ì�����ǻᱻ��ס 
			&&!spider_body_here(u);
			//���Դ���Ʒ������ȥ���ɵĲ��У� 
		}
	}
	return tmp&&!POS.fcmv.lock
	&&!THING.spr.exist//B��֩�뱾�岻����ì 
	&&nobody_here2(u)&&THING.slg.num<=1;//B��֩��Ҫ�����ǲ����Լ�����
	//���Դ���Ʒ������ȥ�����ӡ��ɵĲ��У����ܴ��������ţ���������ì 
}
bool spider_through(position_3D u,int d,bool k){//֩����Դ���
	MAP &POS=game_map[u.x][u.y][u.z];
	thing &THING=POS.things;
	bool tmp=nobody_here(u);
	if(k){//B��֩�� 
		int cnt=0;//б��ס�Ĵ��� 
		for(int i=0;i<8;i++){//�ȵķ��� 
			if(turn(d*2,TURN_BACK,8,6)==i) continue;//����ĸ�֫һ���������ϴε����壨ע��d��4����ģ� 
			position_3D v=dtp3(u,i,8);
			int spt=spiderB_part_through(v,d,i);
			if(spt==0) return false;//һ�����оͶ����� 
			if(spt==-1){
				cnt++;
				if(cnt>=2) return false;//б���ܿ�ס2�� 
			}
		}
		int spt=spiderB_part_through(u,d,8);
		if(spt==0) return false;//һ�����оͶ����� 
		if(spt==-1){
			cnt++;
			if(cnt>=2) return false;//б���ܿ�ס2�� 
		}
		return true;
	}
	movable &MVB=THING.mvb;
	return (MVB.exist?MVB.kind!=BOX:1)&&!POS.fcmv.lock&&!THING.spr.exist//֩����Դ���Ʒ������ȥ�����ӡ��ɵĲ��У� 
	&&!(door_here(u,0)||door_here(u,2)||THING.lsr.exist)&&(stair_here(u)||space_here(u))
	&&nobody_here(u);//����ײ��B��֩�븽֫�� 
} 
bool spider_towards(position_3D u,int d,bool k){//֩�������˴��ƶ�����һ�����λ�ƣ����ܷ�����Ʒ������
	MAP &POS=game_map[u.x][u.y][u.z];
	thing &THING=POS.things;
	int door_d=(d==4?0:turn(d,TURN_BACK,4,7));
	return spider_through(u,d,k)
	||(door_here(u,0)||door_here(u,2))&&RAND_BOOL(50)
	||d!=4&&closed_box_here(u,door_d)&&RAND_BOOL(100)//�и������� 
	||bug_here(u)&&POS.emy.id>=0//�Գ��� 
	||ghost_here(u)//��� 
	||k&RAND_BOOL(50);//�и���ԭ��תȦ 
}
bool ghost_through(position_3D pos,position_3D u,int d,bool att_thr){//����Դ���
	//pos--d-->u 
	MAP &POS=game_map[u.x][u.y][u.z];
	thing &THING=POS.things;
	movable &MVB=THING.mvb;
	bool normal_route=
		!(THING.hdr.exist||door_here(u,0)||door_here(u,2)||THING.lsr.exist||THING.drt.exist1())
		&&(stair_here(u)||space_here(u))&&nobody_here(u)
		&&!POS.fcmv.lock;
	if(d==-1) return normal_route;//˲�� 
	//if(closed_box_here(pos,d)) return false;
	if(att_thr) return pos_in_area2(u.x,u.y,1,1,length,width,1)&&!POS.fcmv.lock&&nobody_here(u);//��ǽ����������Եǽ�� 
	if(d==4)//����¥/���볲Ѩ�����⴦�� 
		return !box_here(u)&&normal_route;
	int reverse_d=turn(d,TURN_BACK);
	bool pos_open_box=open_box_here(pos,d);
	bool u_open_box=open_box_here(u,reverse_d);
	bool go_through_box=(box_here(pos)?pos_open_box:true)&&(box_here(u)?u_open_box:true);
	return (MVB.exist?(push_thing(u,d,0)||go_through_box):1)
		&&normal_route;
} 
bool ghost_towards(position_3D pos,position_3D u,int d,bool att_thr){//�������˴��ƶ�����һ�����λ�ƣ����ܷ�����Ʒ������
	//pos--d-->u 
	//if(box_here(pos)&&game_map[pos.x][pos.y][pos.z].things.mvb.door[d]==0) return false;
	MAP &POS=game_map[u.x][u.y][u.z];
	thing &THING=POS.things;
	movable &MVB=THING.mvb;
	return ghost_through(pos,u,d,att_thr)
	||closed_box_here(pos,d)
	||(MVB.exist&&!POS.fcmv.lock&&(d<4?1:MVB.kind!=BOX))
	||THING.windows.exist||door_here(u,2)
	||bug_here(u)||spider_body_here(u);//�������Ӻ�֩�� 
}
int count_around_pos(position_3D pos,int d,bool (*fp)(position_3D),int n=length,int m=width){
	int cnt=0;
	switch(d){
		case 4:
			for(int i=0;i<4;i++){
				position_3D v=dtp3(pos,i,4);
				if(pos_in_area2(v.x,v.y,1,1,n,m)&&fp(v)) cnt++;
			}
			break;
		case 8:
			for(int i=0;i<8;i++){
				position_3D v=dtp3(pos,i,8);
				if(pos_in_area2(v.x,v.y,1,1,n,m)&&fp(v)) cnt++;
			}
			break;
	}
	return cnt;
}
int gcd(int m,int n){//���Լ��
	if(m%n==0) return n;
	else return gcd(n,m%n);//շת����� 
}
int lcm(int m,int n){//��С������ 
	return m/gcd(m,n)*n;//ԭ���Ļ�=���Լ��*��С������ 
} 
void nearest_RATIO(int a,int b,int l){//��ӽ��ķ�Χ���Ʊ�ֵ 
	if(a==0||b==0){
		cout<<a<<":"<<b;
		return;
	}
	int k1=1000,k2=1,min=k1*b-k2*a;
	for(int i=1;i<=l;i++){
		for(int j=1;j<=l;j++){
			if(abs(i*b-j*a)<min&&i*b>=j*a){
				k1=i;k2=j;
				min=k1*b-k2*a;
			}
		}
	}
	cout<<k1<<":"<<k2;
}
void limit_int(int &a,int l,int r){//����a��[l,r]��Χ�� 
	a=max(a,l);
	a=min(a,r);
}
void limit_double(double &a,double l,double r){//����a��[l,r]��Χ�� 
	a=max(a,l);
	a=min(a,r);
}
int rafz(double num){//roundAwayFromZero������ȡ�� 
    if(num>=0) return ceil(num);
	return floor(num);
}
int MHT_DIST(int x1,int y1,int x2,int y2){//�����پ��� 
	return abs(x1-x2)+abs(y1-y2);
}
int MHT_DIST2(int x1,int y1,int z1,int x2,int y2,int z2){//��ά�����پ���
	return  abs(x1-x2)+abs(y1-y2)+abs(z1-z2);
}
int MHT_DIST_p3(position_3D u,position_3D v){//�����پ��� 
	return abs(u.x-v.x)+abs(u.y-v.y)+abs(u.z-v.z);
}
int NED(int x1,int y1,int x2,int y2){//normal euclidean distance ŷ����þ���
	return sqrt(pow(x1-x2,2)+pow(y1-y2,2));
}
int NED2(int x1,int y1,int z1,int x2,int y2,int z2){//normal euclidean distance ŷ����þ���
	return sqrt(pow(x1-x2,2)+pow(y1-y2,2)+pow(z1-z2,2));
}
double NED_p3(position_3D u,position_3D v){//normal euclidean distance ŷ����þ���
	return sqrt(pow(u.x-v.x,2)+pow(u.y-v.y,2)+pow(u.z-v.z,2));
}
void CUT_LINE(int length,char x){//�ָ��� 
	for(;length>0;length--){
		cout<<x;		
	}
	cout<<"\n";
}
void PRINT(rectangle area,int x,int y,string a,int times=1,int time=0,bool enter=false){
//�Զ���������ظ�����ʱ���Զ����У� 
	position_2D pos;
	pos.x=x,pos.y=y;
	for(int i=1;i<=times;i++){
		for(int j=0;j<int(a.size());j++,pos.x++){
			if(pos.x>=0&&pos.y>=0&&(int(a[j])>=0||int(a[j-1]>=0))) gotoxy(pos.x,pos.y);
			if(pos_in_area2(pos.x,pos.y
			,area.upper_left.x,area.upper_left.y,area.lower_right.x,area.lower_right.y,2)){
				cout<<a[j];
				cout.flush();
				SLEEP(time);
			}
		}
		if(enter) cout<<endl,pos.y++,pos.x=x;
	}
	cout.flush();
}
string connect_str(string a,string b,string c="",string d="",string e="",string f="",string g="",string h=""){
	//�����ַ��������8���� 
	string ret;
	ret+=a;ret+=b;ret+=c;ret+=d;ret+=e;ret+=f;ret+=g;ret+=h;
	return ret;
}
string int_to_str(int x,int y=0){//int����ת����string�ַ�����yλ����λ��ǰ��0���䣬y==0ʱ����ʹ��ǰ��0�� 
	string s="";string f=(x<0?"-":"");
	if(x==0){
		if(y==0) return "0"; 
		while(y--) s+='0';
		return s;
	}
	x=abs(x);
	while(x){
		s+=char(x%10+'0');
		x/=10;
	}
	reverse(s.begin(),s.end());
	while(y!=0&&int(s.size()+f.size())<y) s='0'+s;
	s=f+s;
	return s;
}
string ll_to_str(ll x,ll y=0){//ll����ת����string�ַ�����yλ����λ��ǰ��0���䣬y==0ʱ����ʹ��ǰ��0�� 
	string s="";string f=(x<0?"-":"");
	if(x==0){
		if(y==0) return "0"; 
		while(y--) s+='0';
		return s;
	}
	x=abs(x);
	while(x){
		s+=char(x%10+'0');
		x/=10;
	}
	reverse(s.begin(),s.end());
	while(y!=0&&ll(s.size()+f.size())<y) s='0'+s;
	s=f+s;
	return s;
}
string double_to_str(double x,int y=0,int z=0){//double������ת����string�ַ���������yλС�����ܹ�z���ַ�����λ��ǰ��0���䣩 
	if(y>15) y=15;
	bool negative=x<0;string f=(x<0?"-":"");
	if(x<0) x=-x;
	ll a=x*pow(10,y)+0.5,b=a/pow(10,y),c=(b>0?log10(b):0)+1;
	string s=ll_to_str(a,c+y);
	if(c<ll(s.size())) s.insert(c,".");
	while(z!=0&&s.size()+f.size()<z) s='0'+s;
	s=f+s;
	return s;
}
string PII_to_str(PII x){
	int a=x.first,b=x.second;
	return int_to_str(a)+","+int_to_str(b);
} 
string PPII_to_str(PPII x){
	PII a=x.first,b=x.second;
	return "("+PII_to_str(a)+")"+","+"("+PII_to_str(b)+")";
} 
string to_time(int hour,int min,int sec,string k="HHСʱMM����SS��",bool leading0=false){
	min+=sec/60;sec%=60;hour+=min/60;min%=60;
	string ret=k,h=int_to_str(hour),m=int_to_str(min),s=int_to_str(sec);
	if(leading0){
		if(h.size()<2) h='0'+h;
		if(m.size()<2) m='0'+m;
		if(s.size()<2) s='0'+s;
	}
	int p1,p2,p3;
	p1=ret.find("HH");
	if(hour!=0) ret.replace(p1,2,h);
	else ret.erase(0,ret.find("MM")-p1);
	p2=ret.find("MM");
	if(min!=0) ret.replace(p2,2,m);
	else ret.erase(p2,ret.find("SS")-p2);
	p3=ret.find("SS");
	if(sec!=0||(hour==0&&min==0)) ret.replace(p3,2,s);
	else ret.erase(p3,ret.size()-p3);
	return ret;
}
string repeat_char(char c,int times){
	string s="";
	if(times<=0) return "";
	while(times--) s+=c;
	return s;
}
string repeat_str(string s,int times){
	string ret="";
	if(times<=0) return "";
	while(times--) ret+=s;
	return ret;
}
string being_name(PII x){//��������
	int k=x.first,id=x.second;
	if(id<0&&k!=PLAYER) return "ERROR";//���� 
	switch(k){
		case PLAYER:return "���";
		case BUG:return "����"+int_to_str(id)+"��";
		case SPIDER:return "֩��"+int_to_str(id)+"��";
		case GHOST:return "��"+int_to_str(id)+"��";
	}
	return "δ֪����";
}
string being_name2(int k){//��������
	switch(k){
		case PLAYER:return "���";
		case BUG:return "����";
		case SPIDER:return "֩��";
		case GHOST:return "��";
	}
	return "δ֪����";
}
string kill_count::detail(int k){
	string ret="";
	switch(k){
		case 0:
			for(int i=1;i<=CREATURES_NUM;i++)
				if(i!=PLAYER) ret+="ɱ"+being_name2(i)+int_to_str(det[i])+"ֻ ";
			break;
		default:return "";
	}
	return ret;
}
void formatted_output(int kind,rectangle area,int x,int y,PPII color,string s,int times=1,int time=0,bool enter=false){
//kind=1��������ӡ 2��PRINT��color=-1�����ϴ�һ����x=INF�������ϴκ��� 
	game_flag["����ר��"]=true; 
	position_2D pos;
	if(x==INF) pos=GetConsoleCursor();
	else pos.x=x,pos.y=y;
	PII back=color.first,forw=color.second;//����ɫ��ǰ��ɫ 
	if(back.first!=-1) set_RGBcolor(back.first,back.second,forw.first,forw.second);//SetConsoleTextAttribute(hout,color);
	if(kind==1){
		for(int i=0;i<int(s.size());i++,pos.x++){
			if(pos.x>=0&&pos.y>=0&&(int(s[i])>=0||int(s[i-1])>=0)) gotoxy(pos.x,pos.y);
			if(pos_in_area2(pos.x,pos.y
			,area.upper_left.x,area.upper_left.y,area.lower_right.x,area.lower_right.y,2)){
				cout<<s[i];
				cout.flush();
			}
			else break;
		}
	}
	else PRINT(area,pos.x,pos.y,s,times,time,enter);
}
void print_key(int k,PII light=MP(0,360)){//light:�ƹ����� 
	switch(k){
		case KEY1:
			set_RGBcolor(light.first,light.second,0,0);//�� SetConsoleTextAttribute(hout,light+0x0c);
			cout<<"1";
			break;
		case KEY2:
			set_RGBcolor(light.first,light.second,0,0);//�� SetConsoleTextAttribute(hout,light+0x0c);
			cout<<"2";
			break;
		case KEY3:
			set_RGBcolor(light.first,light.second,-100,360);//�� SetConsoleTextAttribute(hout,light+0x00);
			cout<<"3";
			break;
		case KEY4:
			set_RGBcolor(light.first,light.second,-100,360);//�� SetConsoleTextAttribute(hout,light+0x00);
			cout<<"4";
			break;
	}
	cout<<"="; 
}
void print_food(int kind,int effect){
	switch(effect){
		case 1:set_RGBcolor(0,360,-20,60);//����� SetConsoleTextAttribute(hout,0xf6);
			break;
		case 2:set_RGBcolor(0,360,-20,300);//������ SetConsoleTextAttribute(hout,0xf5);
			break;
		case 3:set_RGBcolor(0,360,0,240);//���� SetConsoleTextAttribute(hout,0xf9);
			break;
	}
	if(kind==ADDL) cout<<"v+"; 
	else cout<<"��";
}
void print_smk(){
	set_RGBcolor(0,360,-50,360);
	cout<<"��";
}
void print_ppt(int kind,int time){
	switch(kind){
		case 1:set_RGBcolor(0,360,0,240);//�� 
			break;
		case 2:set_RGBcolor(0,360,-20,300);//���� 
			break;
		case 3:set_RGBcolor(0,360,-20,60);//��� 
			break;
	}
	cout<<int_to_str(time/1000,2); 
}
void print_laser_gun(){
	set_RGBcolor(0,360,0,180);//��
	cout<<"��";
}
void print_dart(int x){
	set_RGBcolor(0,360,0,240);//��
	if(x%2) cout<<"�� ";
	else cout<<"ʮ"; 
}
void print_spear(){
	set_RGBcolor(0,360,-20,60);//��� 
	cout<<"ì";
}
void print_dagger(){
	set_RGBcolor(0,360,-40,360);//�� 
	cout<<"ذ";
}
void print_sword(){
	set_RGBcolor(0,360,-40,360);//�� 
	cout<<"��";
}
void print_blade(){
	set_RGBcolor(0,360,-20,360);//�� 
	cout<<"��";
}
void print_space(){
	set_RGBcolor(0,360,0,360);//�װ� SetConsoleTextAttribute(hout,0xff);
	cout<<"  ";
}
string item::item_name(int sn){//��֤����ֵ����>=6 
	vector<int> &v=player1.items.item_lab;
	if(sn<0||sn>=v.size()) return "��    "; 
	int id=v[sn];
	if(id<0) return "      ";
	object &ob=objects[id];
	int k=ob.type;
	switch(k){
		case KEY:return "Կ��"+int_to_str(ob.key)+" "; 
		case FOO:
			if(ob.foods.kind==ADDS) return "������"+int_to_str(ob.foods.effect)+"��";
			return "������"+int_to_str(ob.foods.effect)+"��";
		case SMO:return "����";
		case PER:return "͸�ӵ���";
		case LAS:return "����ǹ"; 
		case DAR:return "����"; 
		case SPE:return "��ì"; 
		case DAG:return "ذ��";
		case SWO:return "�̽�"; 
		case BLA:return "����"; 
		/*
		case BX:return "����  ";
		case BL:return "ľͰ  ";
		case TT:return "TNT   ";
		case CE:return "����  ";*/
	}
	return "ERROR ";
}
/*
int item::item_num(int sn){
	item &items=player1.items;
	vector<int> &v=items.item_lab;
	if(sn<0||sn>=v.size()) return 0; 
	int id=v[sn];
	if(id<0) return 0;
	object &ob=objects[id];
	int k=ob.type;
	switch(k){
		case KEY:return ITEM.keys.door_keys[k-K1+KEY1-1]; 
		case FOO:
			return ITEM.foods.food_cnt[ob.foods.kind-ADDS][ob.foods.effect-1];
		case SMO:return ITEM.pp.smb;
	}
	return 0;
}*/
int item::item_endurance(int sn){
	vector<int> &v=player1.items.item_lab;
	if(sn<0||sn>=v.size()) return 0; 
	int id=v[sn];
	if(id<0) return 0;
	object &ob=objects[id];
	int k=ob.type;
	switch(k){
		case KEY:return 0; 
		case FOO:return 0; 
		case WCG:return 0;
		case SMO:return 0; 
		case PER:return 0;  
		case LAS:return 0; 
		case DAR:return 0;
		case SPE:return ob.sprE; 
		case DAG:return ob.daggerE;
		case SWO:return ob.swordE;
		case BLA:return ob.bladeE;
	}
	return 0;
}
string item::item_method(int sn){
	vector<int> &v=player1.items.item_lab;
	if(sn<0||sn>=v.size()) return "��"; 
	int id=v[sn];
	if(id<0) return "��";
	object &ob=objects[id];
	int k=ob.type;
	switch(k){
		case KEY:return "�������"; 
		case FOO:return "��"; 
		case WCG:return "��"; 
		case SMO:return "��"; 
		case PER:return "��"; 
		case LAS:return "�������"; 
		case DAR:return "�������"; 
		case SPE:return "��תͻ��"; 
		case DAG:return "��ս�Զ�";
		case SWO:return "�ƶ�ͻ�̣����迳ɱ";
		case BLA:return "�񵶻��ˣ����迳ɱ"; 
	}
	return "��"; 
}
void item::print_item(int sn){
	vector<int> &v=player1.items.item_lab;
	if(sn<0||sn>=v.size()){
		print_space();//����һ��
		return;
	}
	int id=v[sn];
	if(id<0){
		print_space();//����һ��
		return;
	}
	object &ob=objects[id];
	int k=ob.type;
	switch(k){
		case KEY:
			print_key(ob.key);
			break;
		case FOO:
			print_food(ob.foods.kind,ob.foods.effect);
			break;
		case SMO:
			print_smk();
			break;
		case PER:
			print_ppt(ob.stp.kind,ob.stp.time);
			break;
		case LAS:
			print_laser_gun();
			break;
		case DAR:
			print_dart(sn);
			break;
		case SPE:
			print_spear();
			break; 
		case DAG:
			print_dagger();
			break; 
		case SWO:
			print_sword();
			break; 
		case BLA:
			print_blade();
			break;
		default:
			set_RGBcolor(-100,360,0,0);
			cout<<"ERROR";
	}
}
void item::print1(){//�������
	position_2D opos;
	opos.x=item_area.upper_left.x;opos.y=item_area.upper_left.y;//�ο��� 
	PPII col;
	if(player1.action_kind==CHOOSE_ITEM) col=MMPP(0,360,-100,360);//�׵׺��� 
	else col=MMPP(-100,360,0,360);//�ڵװ��� 
	formatted_output(1,item_area,opos.x+1,opos.y+1,col,"��");
	formatted_output(1,item_area,opos.x+1,opos.y+2,col,"Ʒ");
	formatted_output(1,item_area,opos.x+1,opos.y+3,col,"��");
}
void item::print2(){//�����1��2�� 
	position_2D opos;
	opos.x=item_area.upper_left.x+3;opos.y=item_area.upper_left.y+1;//�ο���
	PPII col;
	vector<int> &v=player1.items.item_lab;
	int sn=item::select_number;
	for(int i=0;i<MAX_SIZE_OF_ITEM_LAB;i++){//��һ��д��Ʒ�� 
		if(sn==i) col=MMPP(0,360,-100,360);//�׵׺��� 
		else col=MMPP(-100,360,0,360);//�ڵװ��� 
		formatted_output(1,item_area,opos.x,opos.y,col,item_name(i)+"  ");
		opos.x+=6; 
	}
	formatted_output(2,item_area,opos.x,opos.y,MMPP(-100,360,-100,360)," ",6*(MAX_SIZE_OF_ITEM_LAB-v.size()));
	opos.x=item_area.upper_left.x+3;opos.y++;
	for(int i=0;i<MAX_SIZE_OF_ITEM_LAB;i++){//�ڶ���д * ��Ʒʾ��ͼ *
		if(sn==i) col=MMPP(0,360,-100,360);//�׵׺��� 
		else col=MMPP(-100,360,0,360);//�ڵװ��� 
		formatted_output(1,item_area,opos.x,opos.y,col,"��  ��");
		gotoxy(opos.x+2,opos.y);
		print_item(i);//��2��*�м���� 
		cout.flush();
		opos.x+=6; 
	}
	formatted_output(2,item_area,opos.x,opos.y,MMPP(-100,360,-100,360)," ",6*(MAX_SIZE_OF_ITEM_LAB-v.size()));
}
void item::print3(){//�����3�� 
	if(item::select_number<0) return;//ûѡ����Ʒ
	int sn=item::select_number;
	position_2D opos;
	opos.x=item_area.upper_left.x+3;opos.y=item_area.upper_left.y+3;//�ο���
	PPII col;
	vector<int> &v=player1.items.item_lab;
	if(item_num.size()<MAX_SIZE_OF_ITEM_LAB) return;
	for(int i=0;i<MAX_SIZE_OF_ITEM_LAB;i++){//������д * (�;ö�) * ���� 
		if(sn==i) col=MMPP(0,360,-100,360);//�׵׺��� 
		else col=MMPP(-100,360,0,360);//�ڵװ��� 
		formatted_output(1,item_area,opos.x,opos.y,col,"����"+int_to_str(item_num[i],2));
		opos.x+=6; 
	}
	formatted_output(2,item_area,opos.x,opos.y,MMPP(-100,360,-100,360)," ",6*(MAX_SIZE_OF_ITEM_LAB-v.size()));//ͳһ��պ���Ĳ��� 
} 
string weapon_name(int sw){
	switch(sw){
		case LAS:return "����ǹ";
		case DAR:return "������";
		case SPE:return "ì"; 
		case DAG:return "ذ��";
		case SWO:return "�̽�"; 
		case BLA:return "����";
		default:return "NONE";
	}
}
string weapon_method(int sw){
	switch(sw){
		case LAS:return "����S������";
		case DAR:return "����S��Ͷ��";
		case SPE:return "����ͻ��"; 
		case DAG:return "��ս�Զ�";
		case SWO:return "���ͻ�̣����迳ɱ"; 
		case BLA:return "�񵶻��ˣ����迳ɱ"; 
		default:return "ERROR";
	}
}
string weapon_status(int id){
	if(id<0) return "          ";
	object &ob=objects[id];
	switch(ob.type){
		case LAS:return "������"+int_to_str(ob.lsrE);
		case DAR:return "������"+int_to_str(object_cnt(id));
		case SPE:return "�;ã�"+int_to_str(ob.sprE);
		case DAG:return "�;ã�"+int_to_str(ob.daggerE);
		case SWO:return "�;ã�"+int_to_str(ob.swordE);
		case BLA:return "�;ã�"+int_to_str(ob.bladeE);
		default:return "ERROR";
	}
}
void item::wpn_print1(){
	PPII col=MMPP(-100,360,0,360);
	position_2D opos;
	opos.x=weapon_area.upper_left.x;opos.y=weapon_area.upper_left.y;//�ο���
	if(player1.action_kind==CHANGE_WPN) col=MMPP(0,360,-100,360);//�׵׺��� 
	else col=MMPP(-100,360,0,360);//�ڵװ��� 
	formatted_output(1,weapon_area,opos.x+1,opos.y+1,col,"��");
	formatted_output(1,weapon_area,opos.x+1,opos.y+2,col,"��");
	formatted_output(1,weapon_area,opos.x+1,opos.y+3,col,"��");
	opos.x+=3;opos.y++;
} 
void item::wpn_print2(){
	PPII col=MMPP(-100,360,0,360);
	string name;
	position_2D opos;
	opos.x=weapon_area.upper_left.x+3;opos.y=weapon_area.upper_left.y+1;//�ο���
	vector<int> &v=item_lab;
	int x=wpn.primary,id=-1,sw=-1;//x:��������Ʒ����� sw:������type 
	if(x>=0&&x<v.size()){
		id=v[x];
		if(id>=0) sw=objects[id].type;
		switch(sw){
			case LAS:col=MMPP(-100,360,0,180);break; 
			case DAR:col=MMPP(-100,360,0,240);break; 
			case SPE:col=MMPP(-100,360,-20,60);break;
			case DAG:col=MMPP(-95,360,-5,360);break;
			case SWO:col=MMPP(-90,360,-10,360);break;
			case BLA:col=MMPP(-85,360,-15,360);break;
		}
	}
	name=weapon_name(sw);
	formatted_output(1,weapon_area,opos.x,opos.y,MMPP(-100,360,0,360),"��������<");
	formatted_output(1,weapon_area,opos.x+9,opos.y,col,name);//���������ʹ�ӡ 
	formatted_output(1,weapon_area,opos.x+9+name.size(),opos.y,MMPP(-100,360,0,360),">    ");
	opos.x+=2;opos.y++;
	formatted_output(1,weapon_area,opos.x,opos.y,col,weapon_status(id)+"  ");//����������Ϣ 
}
void item::wpn_print3(){
	PPII col=MMPP(-100,360,0,360);
	vector<int> &v=item_lab;
	int x=wpn.secondary,sw=-1;
	if(x>=0&&x<v.size()){
		sw=v[x];
		if(sw>=0) sw=objects[sw].type;
	}
	string name=weapon_name(sw);
	position_2D opos;
	opos.x=weapon_area.upper_left.x+3;opos.y=weapon_area.upper_left.y+3;//�ο���
	formatted_output(1,weapon_area,opos.x,opos.y,MMPP(-100,360,0,360),"��������<");
	formatted_output(1,weapon_area,opos.x+9,opos.y,col,name);//�и������ʹ�ӡ 
	formatted_output(1,weapon_area,opos.x+9+name.size(),opos.y,MMPP(-100,360,0,360),">    ");
}
void set_text_color(RGB_color back,RGB_color forw){//����������ɫ��ANSIת���ַ� 
	//printf(("\033[48;2;"+int_to_str(back.r)+";"+int_to_str(back.g)+";"+int_to_str(back.b)+"m").c_str());
	//printf(("\033[38;2;"+int_to_str(forw.r)+";"+int_to_str(forw.g)+";"+int_to_str(forw.b)+"m").c_str());
	printf("\033[48;2;%d;%d;%dm",back.r,back.g,back.b);
	printf("\033[38;2;%d;%d;%dm",forw.r,forw.g,forw.b);
}
int interconnection_distance(position_3D s,position_3D e,int max_dis,position_3D no_reach){
	//��s��e�Ĳ��о��루BFS�� 
	memset(vst,0,sizeof(vst));
	memset(dis,0,sizeof(dis));
	while(!Q.empty()) Q.pop();
	vst[s.x][s.y][s.z]=1;
	dis[s.x][s.y][s.z]=0;
	Q.push(s);
	while(!Q.empty()){
		position_3D u=Q.front();Q.pop();
		if(u==e) return dis[u.x][u.y][u.z];
		if(dis[u.x][u.y][u.z]>max_dis) return -1;
		for(int i=0;i<4;i++){
			position_3D v=dtp3(u,i,4);
			if(v.x>=1&&v.x<=length&&v.y>=1&&v.y<=width&&v.z>=1&&v.z<=height
				&&!(vst[v.x][v.y][v.z]&&v!=no_reach)
				&&!wall_here(v)
				&&!door_here(v)
				){
				if(game_map[v.x][v.y][v.z].maze==UPSTAIR) v.z++;
				else if(game_map[v.x][v.y][v.z].maze==DOWNSTAIR) v.z--;
				vst[v.x][v.y][v.z]=1;
				dis[v.x][v.y][v.z]=dis[u.x][u.y][u.z]+1;
				Q.push(v);
			}
		}
	}
	return -1; 
}
bool useful_door(position_2D u,int z,int dis){//�ж����Ƿ�����
	position_2D a,b;//��ǰ���ź��λ��
	a.x=0;b.x=0;
	for(int i=0;i<4;i++){
		position_2D v=dtp2(u,i,4);
		if(pos_in_area2(v.x,v.y,1,1,length,width,2)&&space_here(position_2Dto3D(v,z))){
			if(a.x==0) a=v;
			else{
				b=v;
				break;
			}
		}
	}
	if(a.x==0||b.x==0) return false;//���λ�ò������������յ�
	position_3D no_reach={-1,-1,-1};
	int dmaze=game_map[u.x][u.y][z].maze;
	if(game_map[u.x][u.y][z].maze!=WALL) game_map[u.x][u.y][z].maze=WALL;//no_reach=position_2Dto3D(u,z);
	int connect=interconnection_distance((position_3D){a.x,a.y,z},(position_3D){b.x,b.y,z},dis,no_reach);
	game_map[u.x][u.y][z].maze=dmaze;
	if(connect==-1||connect>=dis) return true;
	return false;
}
bool invisible(position_3D pos,position_3D p){//pos������pλ�� 
	for(int i=0;i<4;i++){
		if(!cnt_visible[i]) continue;
		position_3D u=pos;u.x+=bool(i&1);u.y+=bool(i&2);//�� 
		int mn=-1,mx=-1; 
		for(int j=0;j<4;j++){
			position_3D v=p;v.x+=bool(j&1);v.y+=bool(j&2);//�� 
			if(u==v) continue;
			int a=calc_angle(u,v);
			if(mn==-1||cmpa(a,mn)) mn=a;
			if(mx==-1||cmpa(mx,a)) mx=a;
		}
		/*
		if(sub_angle(mn,mx)>5||pos.x==p.x||pos.y==p.y)
		//mn=mx,��pλ�õĿ��ӽǶ�<=10��ʱ���ж�Ϊ������ 
		//�����������ƽ��ֱʱ��֤���� 
		*/
		for(int j=mn;j!=(mx+1)%360;j=(j+1)%360)
			if(occlusion[i][j]>0) return false;
	}
	return true; 
}
void mark_lose_sight(int i,int j){//��Ǵ˴��������ˣ������޸ģ� 
	if(occlusion[i][j]>0){
		occlusion[i][j]--;
		if(occlusion[i][j]==0) cnt_visible[i]--;
	}
} 
void mark_lose_sight_area(int i,int mn,int mx){//��Ǵ˴��������ˣ������޸ģ� 
	for(int j=mn;j!=(mx+1)%360;j=(j+1)%360)
		mark_lose_sight(i,j); 
}
void calc_mark_vague(position_3D p,position_3D pos){//����pģ��ֵ����¼��game_map 
	//p_vague��p�Ƿ����ģ��Ч�� 
	int cnt=0;//������ 
	double sum[3];
	//p����ģ��Ч��=avg(vague[0~3][mn~mx])
	for(int i=0;i<4;i++){
		if(!cnt_visible[i]) continue;
		position_3D u=pos;u.x+=bool(i&1);u.y+=bool(i&2);//�� 
		int mn=-1,mx=-1; 
		for(int j=0;j<4;j++){
			position_3D v=p;v.x+=bool(j&1);v.y+=bool(j&2);//�� 
			if(u==v) continue;
			int a=calc_angle(u,v);
			if(mn==-1||cmpa(a,mn)) mn=a;
			if(mx==-1||cmpa(mx,a)) mx=a;
		}
		for(int j=mn;j!=(mx+1)%360;j=(j+1)%360){
			for(int k=0;k<3;k++){//RGB
				double p_vague=light_vague(p,k);//R/G/B��ģ���� 
				if(p_vague>eps){//����ģ���ٱ�� 
					vague[i][j][k]=1.0-(1.0-vague[i][j][k])*(1.0-p_vague);//����ģ������ 
					//if(fabs(vague[i][j]-1.0)<eps)//ģ������ȫ������ 
					//	mark_lose_sight(i,j); 
				}
				if(occlusion[i][j]>0) sum[k]+=vague[i][j][k]; 
				//�����ܿ�����λ�ö�����ģ��ֵ ?
			}
			if(occlusion[i][j]>0) cnt++;
		}
	}
	double (&ret)[3]=game_map[p.x][p.y][p.z].ist.vague;//p��ģ������ 
	for(int i=0;i<3;i++){//RGB
		if(cnt==0){//��ֹ���� 
			ret[i]=1.0;//ɶ�������� 
			return;
		}
		double avg=sum[i]/cnt;//R/G/B����һ����ɫ��ƽ��ģ��ֵ 
		limit_double(avg,0.0,1.0);
		ret[i]=avg;//[0,1]����p��ģ��ֵ 
	}
}
void mark_line_occlusion(position_3D pos,position_3D u,position_3D p,position_3D v1,position_3D v2,int i){
	int a=calc_angle(u,v1),b=calc_angle(u,v2);
	if(u==v1) a=calc_angle(pos,p);
	if(u==v2) b=calc_angle(pos,p);
	//��֤����ʱ������ȷ 
	if(cmpa(b,a)) swap(a,b);//��֤�Ƕ�������ȷ 
	mark_lose_sight_area(i,a,b);
}
void mark_occlusion(position_3D p,position_3D pos,bool kind=1){//pλ���ڵ���pos����
	//kind 1:�������ӵ� 0�������� 
	//����˭�ڵ�˭�� 
	for(int i=0;i<4;i++){
		if(!cnt_visible[i]) continue;
		position_3D u=pos;u.x+=bool(i&1);u.y+=bool(i&2);//�� 
		//��������p��ô�ڵ� 
		if(kind&&box_here(p)&&!closed_box_here(p)&&!open_box_here(p)){//�п��ŵ�����
			//ȫ�أ������Ƕ��� ȫ����ûӰ�� 
			movable &MVB=game_map[p.x][p.y][p.z].things.mvb;
			/*
				       d=0
				x,y o======o x+1,y
				    |      |
				d=3 | ���� | d=1
				    |      |
			  x,y+1 o======o x+1,y+1
			           d=2
			v1��v2��ͼ�а�˳ʱ������ ��ȷ���Ƕ����Ҳ��˳ʱ�룿 
			[a,b]��Ϊ�����ڵ�����Ұ���� 
			*/
			//BUG HERE
			if(MVB.door[0]==0){//�˷����Ź��� 
				position_3D v1=p,v2=p;
				v2.x++;
				mark_line_occlusion(pos,u,p,v1,v2,i);
			}
			if(MVB.door[1]==0){//�˷����Ź��� 
				position_3D v1=p,v2=p;
				v1.x++;
				v2.x++;v2.y++;
				mark_line_occlusion(pos,u,p,v1,v2,i);
			}
			if(MVB.door[2]==0){//�˷����Ź��� 
				position_3D v1=p,v2=p;
				v1.x++;v1.y++;
				v2.y++;
				mark_line_occlusion(pos,u,p,v1,v2,i);
			}
			if(MVB.door[3]==0){//�˷����Ź��� 
				position_3D v1=p,v2=p;
				v1.y++;
				mark_line_occlusion(pos,u,p,v1,v2,i);
			}
		}
		else{
			int mn=-1,mx=-1; 
			for(int j=0;j<4;j++){
				position_3D v=p;v.x+=bool(j&1);v.y+=bool(j&2);//�� 
				if(u==v) continue;
				int a=calc_angle(u,v);
				if(mn==-1||cmpa(a,mn)) mn=a;
				if(mx==-1||cmpa(mx,a)) mx=a;
			}
			mark_lose_sight_area(i,mn,mx);
		}
	}
}
void prd(){
	gotoxy(0,40);
	for(int j=0;j<360;j++) printf("%4d",j);
	//cout<<"\n";
	for(int i=0;i<4;i++){
		for(int j=0;j<360;j++) printf("%4d",occlusion[i][j]);
		//cout<<"\n";
	}
}
bool rand_error(int max,int min){
	if(max<min){
		formatted_output(1,whole_screen,30,30,MMPP(-100,360,0,0),"�����������д���ˣ���");
		return true;
	}
	return false;
}
int my_rand(){
	return (rand()<<15)+rand();
}
int RAND(int max,int min){//����� 
	if(rand_error(max,min)) swap(max,min);
	int num=my_rand()%(max-min+1)+min;
	return num;
}
bool RAND_BOOL(int a){//�����������ֵ 
	int num=my_rand()%100+1;
	if(num<=a) return 1;
	else return 0;
}
int RAND_ALTO(int max,int min,int a){//Ⱥ������� 
	if(rand_error(max,min)) swap(max,min);
	int k=min;
	for(int i=1;i<=max-min+1;i++){
		if(RAND_BOOL(a)) k++;
	}
	return k;
}
double RAND_DOUBLE(double max,double min){
	if(rand_error(max*1000,min*1000)) swap(max,min);
	int num=my_rand()%int(max*1000-min*1000+1)+min*1000;//min*1000~max*1000
	return num/1000.0;//��λС������ 
}
void RAND_EXIT_AROUND_GAME_MAP(int cnt,int l=length,int w=width,int h=height){//��ͼ����� 
	vector<position_3D> v;//�洢���ܻᱻѡ����λ��
	/* l=5,w=5
	0��ʾ�����ܻᱻѡ����1��ʾ�п��ܻᱻѡ�� 
		(1,1)==>01110<==(l,1)
				10001
				10001
				10001
    	(1,w)==>01110<==(l,w)
 	��Ȼ��ÿ��¥��Ҫ���ȥ
 	���⣬ѡ����λ�ã�����Ҫ��һ����ǽ�������ڣ�������һ��ͨ��������ô�ӳ�ȥ����*/ 
	for(int z=1;z<=height+h;z++){//�ҳ����п������ó��ڵ�λ�� 
		for(int x=2;x<l;x++){
			if(game_map[x][2][z].maze!=WALL)
				v.push_back((position_3D){x,1,z});
			if(game_map[x][w-1][z].maze!=WALL)
				v.push_back((position_3D){x,w,z});
		}
		for(int y=2;y<w;y++){
			if(game_map[2][y][z].maze!=WALL)
				v.push_back((position_3D){1,y,z});
			if(game_map[l-1][y][z].maze!=WALL)
				v.push_back((position_3D){l,y,z});
		}
	}
	for(int i=1;i<=cnt&&v.size()>0;i++){
		int j=RAND(v.size()-1,0);
		position_3D u=v[j];
		swap(v[j],v[v.size()-1]);v.pop_back();
		game_map[u.x][u.y][u.z].maze=EXIT;
		//Q.push(u);vst[u.x][u.y][u.z]=1;//Ϊ���ڱ��Ƶ�������׼�� 
		/*
				fog &FOGS=game_map[u.x][u.y][u.z].things.fogs;
				FOGS.absorbance=1000000;//��ʼ��������������ɢ
				FOGS.update=true; 
				pos_fog.push(u);//������� */
	} 
}
int RAND_MIRROR_DIRECTION(position_3D pos){//���ѡ���ӷ��� 
	vector<int> v;//�洢���ܻᱻѡ���ľ��ӳ��� 
	/*  				0��	   1��	  2��	 3�� 
	�����ĸ������λ��  1��2�� 2��3�� 3��0�� 0��1�� 
	*/
	for(int i=0;i<4;i++){
		int j=turn(i,TURN_RIGHT),k=turn(i,TURN_LEFT);
		position_3D a=dtp3(pos,i,4),b=dtp3(pos,j,4);
		if(worth_relecting(a)&&worth_relecting(b)) v.push_back(k);
	}
	if(v.size()>0) return v[RAND(v.size()-1,0)];
	return -1;
}
position_3D RAND_PLAYER_IN_GAME_MAP(int l=length,int w=width,int h=height){
//����Ϸ��ͼ�����ѡ����ҵ�λ�ã��յ����ˣ�Զ����ڣ�������·�� 
	vector<position_3D> v;//�洢���ܻᱻѡ����λ��
	int mx_dis=0;
	for(int z=1;z<=h;z++)
		for(int y=2;y<w;y++)
			for(int x=2;x<l;x++){
				position_3D u;
				u.x=x;u.y=y;u.z=z;
				if(space_here(u)&&nobody_here(u)&&empty_here(u)
				&&count_around_pos(u,4,space_here)+count_around_pos(u,4,stair_here)>=1){
					if(dis_to_exit[x][y][z]>mx_dis){
						v.clear();
						v.push_back(u);
						mx_dis=dis_to_exit[x][y][z];
					}
					else if(dis_to_exit[x][y][z]==mx_dis) v.push_back(u);
				}
			}
	if(v.size()>0) return v[RAND(v.size()-1,0)];
	return (position_3D){length/2,width/2,1};
}
void window::damage(int edc,position_3D u){//�Ҵ���=���;�ֵ��+ǽ��յأ�+��Ļ����+���ո��� 
	MAP &POS=game_map[u.x][u.y][u.z];
	bool in_sight=POS.ist.player==lst_see_time;
	endurance-=edc;
	if(endurance<=0){
		if(state==0&&POS.update_light()) pos_affect_light.push(u);//������û���¹��� 
		init();
		POS.maze=SPACE;
		if(in_sight) game_flag["��Ʒ��ʧ"]=true;
		if(MHT_DIST(u.x,u.y,player1.pos.x,player1.pos.y)<=10&&u.z==player1.pos.z)
			MUSIC("Glass_Breaking.wav",1);//��ʾ�� 
	}
	else if(in_sight){
		game_flag["��Ʒ��"]=true;
		pos_change.insert(u);
	}
}
void spider_net::addedc(int k,position_3D u){
	MAP &POS=game_map[u.x][u.y][u.z];
	int a=endurance;
	endurance=max(0,min(100,endurance+k));
	int b=endurance;
	/*����̬�����ˣ�̫���� 
	if(RAND_BOOL(abs(a*a-b*b)/2)//�仯Խ�󣬸��µĿ�����Խ�� 
	&&(a>50||b>50)&&(k>0?POS.ist.pvg()<=95:1)//����95�ٸ�ģ��Ҳ���������� 
	&&game_map[u.x][u.y][u.z].ist.player==lst_see_time) game_flag["�����仯"]=true;*/
}
struct cmp_bug{
	bool operator() (int &a,int &b){
		string s1="����"+int_to_str(a);
		string s2="����"+int_to_str(b);
		return game_timer[s1]>game_timer[s2];
	}
};
priority_queue<int,vector<int>,cmp_bug > Qbug;//���Ӷ��У���ţ�
struct cmp_spider{
	bool operator() (int &a,int &b){
		string s1="֩��"+int_to_str(a);
		string s2="֩��"+int_to_str(b);
		return game_timer[s1]>game_timer[s2];
	}
};
priority_queue<int,vector<int>,cmp_spider > Qspider;//֩����У���ţ�
struct cmp_ghost{
	bool operator() (int &a,int &b){
		string s1="��"+int_to_str(a);
		string s2="��"+int_to_str(b);
		return game_timer[s1]>game_timer[s2];
	}
};
//priority_queue<int,vector<int>,cmp_ghost > Qghost;//����У���ţ�
queue<int> Qghost;//����У���ţ������٣� 
void io_init(){
	// �����Ϸ��־ 
	clearGameLog();
	 
	// Ϊstd::cout����һ����Ļ�����
    const size_t bufferSize = 1024 * 1024; // 1MB�Ļ�������С
    char buffer[bufferSize];
 
    // ����������std::cout����
    setvbuf(stdout, buffer, _IOFBF, bufferSize);
}
void API_init(){//��WINAPI�йصĳ�ʼ�� 
	DWORD mode;GetConsoleMode(hin,&mode);
	mode&=~ENABLE_QUICK_EDIT_MODE;SetConsoleMode(hin,mode);
	h=GetForegroundWindow();
	screen_zoom=get_screen_zoom();
}
//���ú��� 
void screen_partition();
void welcome_player();
void ask_player();
void show_insturction(); 
void initial();
void game();
void win();
void lose();
void detail();
void end();
void ask_try_again();
void player_calculate_vision1(int d);
void vision_init(int k,vector<PII > v,vector<position_3D> &ret,position_3D pos);
void calculate_vision2(position_3D pos,int pl_ot,vector<position_3D> &ret,int mx_dis,bool vague);
void player_calculate_vision2();
//�������� 
int main(){//������Ʒ��������Ʒ 
	srand(time(0));
	//��Ļ����������������������ɫ��
	io_init();
	API_init(); 
	hideCursor();//���������� 
	RGB_init();//RGB��ɫ��ʼ�� 
	init_timer();//��ʼ����ʱ�� 
	start_timer();//������ʱ�� 
	screen_partition();
	welcome_player();CLEAR();
	while(1){
		ask_player();CLEAR();
		show_insturction();//CLEAR();
		initial();
		//�����ʼ����ͽ�����Ϸ������ģ��������� 
		game();CLEAR();
		if(game_success) win();
		else lose();
		detail();
		ask_try_again();
		CLEAR();
		if(!start_again){
			end();
			break;
		}
	}
	return 0;
}
//������
void screen_partition(){//��Ļ���� 
	//ע����Ļ���Ͻ�Ϊ(0,0)�����½�Ϊ(MAX_SCREEN_LENGTH-1,MAX_SCREEN_WIDTH-1)
	whole_screen.init(-1,-1,MAX_SCREEN_LENGTH,MAX_SCREEN_WIDTH);//�߿�����Ļ�� 
	vital_signs_area.init(-1,-1,MAX_SCREEN_LENGTH,1);//��Ļ����һ�� 
	item_area.init(41,MAX_SCREEN_WIDTH-4,MAX_SCREEN_LENGTH-43,MAX_SCREEN_WIDTH);
	weapon_area.init(MAX_SCREEN_LENGTH-44,MAX_SCREEN_WIDTH-4,MAX_SCREEN_LENGTH,MAX_SCREEN_WIDTH);
	/* 
	int midx=MAX_SCREEN_LENGTH/2,midy=MAX_SCREEN_WIDTH/2;//��Ļ����ʾ����Ϸ��ͼ���ĵ㣨��ҵ�λ�ã�
	game_map_area.init(max(0,midx-midy*2),0,min(MAX_SCREEN_LENGTH-1,midx+midy*2),MAX_SCREEN_WIDTH-1);
	//����ҵ�λ��Ϊ���ĵ�һ��������������������Ϊ��Ϸ��ͼ��Χ��97*48�������¿���Ļ�߽�
	vital_signs_area.init(0,0,game_map_area.upper_left.x,MAX_SCREEN_WIDTH-1);
	//�����Ϣ�������
	item_area.init(game_map_area.lower_right.x,0,MAX_SCREEN_LENGTH-1,MAX_SCREEN_WIDTH-1);
	//�����Ʒ�����ұ�*/
}
void welcome_player(){
	//��ǰҪ���� 
	formatted_output(2,whole_screen,40,20,MMPP(-100,360,0,360),"��ӭ������Ұ���٣�",1,150);
	formatted_output(2,whole_screen,40,21,MMPP(-100,360,0,360),"���ߣ�wqx",1,150);
	formatted_output(2,whole_screen,40,22,MMPP(-100,360,0,60),"���»س��Կ�ʼ",1,150);
	wait_until(PRESS_KEY_ENTER);
	formatted_output(2,whole_screen,40,22,MMPP(-100,360,0,180),"��Ϸ������......",1,100);
}
	void choose_game_map_from(){
		while(1){
			if(_kbhit()){
				int c=_getch();
				if(c==PRESS_KEY_A){
					game_map_from=RANDOM; 
					//cout<<'a';
					return;
				}
				else if(c==PRESS_KEY_B){
					game_map_from=FILE_MODEL;
					//cout<<'b';
					return;
				}
			}
		} 
	}
void ask_player(){
	//��ǰҪ����
	formatted_output(2,whole_screen,40,20,MMPP(-100,360,0,360),"��������ʲô���֣���",1,100);
	formatted_output(2,whole_screen,INF,0,MMPP(-100,360,0,60),"���ð����ո�ͱ�����",1,100);
	formatted_output(2,whole_screen,INF,0,MMPP(-100,360,0,360),"��",1,100);
	cin>>player1.name; 
	formatted_output(2,whole_screen,40,20,MMPP(-100,360,0,360),"����Ҫ  a.������ɵĵ�ͼ  or  b.Ԥ���ͼ �� ",1,100);
	choose_game_map_from();
	if(game_map_from==RANDOM){//������ɵĵ�ͼ
		formatted_output(2,whole_screen,40,21,MMPP(-100,360,0,360),"�������ͼ����ߣ�",1,100);
		formatted_output(2,whole_screen,INF,0,MMPP(-100,360,0,60),
		"4<=��<="+int_to_str(MAX_LENGTH)+"��4<=��<="+int_to_str(MAX_WIDTH)+"��1<=��<="+int_to_str(MAX_HEIGHT),
		1,100);
		formatted_output(2,whole_screen,INF,0,MMPP(-100,360,0,360),"������",1,100);
		formatted_output(2,whole_screen,INF,0,MMPP(-100,360,0,60),"�ո�",1,100);
		formatted_output(2,whole_screen,INF,0,MMPP(-100,360,0,360),"�ָ�����",1,100);
		cin>>length>>width>>height;
	}
}
string game_instruction[26]={
	"һ����ʾ",
	"    ��Ļ���Ϊ��Ϣ��������������������ģʽ���á���ɱ��Ϣ��",
	"    ��Ļ�Ҳ�Ϊ��Ʒ����������",
	"    ��Ļ�м�Ϊ��Ϸ��",
	"��������",
	"    1���ƶ�",
	"        WASD����Ӧǰ����ҵ��ƶ����򣬰�C������¥/������Ѩ��",
	"        �ƶ�����꡿������Ұ����",
	"    2��ʹ����Ʒ",
	"        ��F������Ʒ����",
	"        ���������������Ļ�²����Ʒ�������ѡ����Ʒ��ʹ��",
	"        ��TAB�������ֵ�Ͳ",
	"    3��ʹ������",
	"        1���л��������ּ���",
	"           ��ì �ڼ��� �ۻ�����",
	"        2��ʹ��",
	"           ì�Զ����������⡢�����ڰ��¡�������������꡿������",
	"           ����ì�;á����������ĵ�����ʾΪ+n����������ʾΪ ʮ ��",
	"    4���ƶ���Ʒ",
	"        1������꡿��������ѡ�в���������ƶ�ʱ�Զ��ƶ�����",
	"        2�����¿ո���ɽ�ѡ���������ǰ��������꡿�����ӳ�������������˺�",
	"           ע�⣺�����Ӻ�ʯ������Ч", 
	"�������ˣ����ӡ���֩��",
	"    �������㣬�������Ϳ��ܣ�", 
	"�ġ���ϷĿ�꣺���������ߵ�����E]", 
	"���棺��������æʱ���������٣�����Ը�" 
};
string player_advice[6]={
	"�����������ߵ��Ҹ棺",
	"һ����������",
	"�������ֹ���",
	"����С�ı���",
	"�ġ�ע�ⵯҩ",
	"��ʿ��ף�����"
}; 
void show_insturction(){//չʾ��Ϸ˵�� 
	formatted_output(1,whole_screen,35,1,MMPP(-100,360,0,360),"��Ϸ˵��");
	for(int i=0;i<26;i++) formatted_output(2,whole_screen,1,i+2,MMPP(-100,360,0,360),game_instruction[i]);
	for(int i=0;i<6;i++) formatted_output(2,whole_screen,90,i+2,MMPP(-100,360,0,180),player_advice[i]);
	formatted_output(2,whole_screen,1,47,MMPP(-100,360,0,0),"��2�οո������",1,100);
	wait_until(PRESS_KEY_SPACE);wait_until(PRESS_KEY_SPACE);
	formatted_output(1,whole_screen,1,47,MMPP(-100,360,0,180),"��Ϸ������ʼ......");
}
	void all_assigned(){//��ȷ����Щ����ȫ��Ҫ��ʼ���Ķ������� 
		logMessage("all_assigned"); 
		API_init();
		pos00.init();pos000.init();
		
		game_end=game_success=game_pause=start_again=false;
		hideCursor();
		for(int z=1;z<=height*2;z++){
			for(int y=1;y<=width;y++){
				for(int x=1;x<=length;x++){
					MAP &POS=game_map[x][y][z];
					POS.init();
				}
			}
		}
		
		objects.clear();
		
		cnt_notWALL=cnt_SPACE=cnt_STAIRS=0;
		memset(stair_exist,0,sizeof(stair_exist));
		memset(pos_in_room,0,sizeof(pos_in_room));
		
		mx_dis_to_player=0;
		for(int i=0;i<(MAX_LENGTH-1)*(MAX_WIDTH-1)*(MAX_HEIGHT*2);i++) pos_dis_to_player_door[i].clear();
		for(int i=0;i<(MAX_LENGTH-1)*(MAX_WIDTH-1)*(MAX_HEIGHT*2);i++) pos_dis_to_player_key[i].clear();
		
		player1.up_down=0;
		while(!pos_in_sight.empty()) pos_in_sight.pop();
		while(!pos_lst_sight.empty()) pos_lst_sight.pop();
		pos_backup.clear();pos_change.clear();
		screen_pos.clear();screen_z.clear();
		
		while(!pos_dead.empty()) pos_dead.pop();
		
		for(int i=0;i<4;i++) cnt_visible[i]=360;
		memset(occlusion,0,sizeof(occlusion));
		memset(vague,0,sizeof(vague));
		while(!pos_vague.empty()) pos_vague.pop();
		
		game_time=lst_see_time=start_time=0;
		game_timer.clear(); 
		game_flag.clear();
		
		bugs.clear();ghosts.clear();spiders.clear();
		pos_in_nest.clear();
		while(!Qbug.empty()) Qbug.pop();
		while(!Qbug_hurt.empty()) Qbug_hurt.pop();
		while(!Qspider.empty()) Qspider.pop();
		while(!Qspider_hurt.empty()) Qspider_hurt.pop();
		while(!ssks.empty()) ssks.pop();
		while(!Qghost.empty()) Qghost.pop();
		while(!Qghost_hurt.empty()) Qghost_hurt.pop();
		
		while(!spears.empty()) spears.pop();
		while(!swords.empty()) swords.pop();
		while(!blades.empty()) blades.pop();
		while(!laser_beams.empty()) laser_beams.pop();
		while(!laser_beam_light.empty()) laser_beam_light.pop();
		while(!darts.empty()) darts.pop();
		while(!mvbs.empty()) mvbs.pop();
		while(!pos_fog.empty()) pos_fog.pop(); 
		
		while(!message_box.empty()) message_box.pop(); 
		while(!pos_affect_light.empty()) pos_affect_light.pop(); 
		while(!lights_update.empty()) lights_update.pop(); 
		memset(light_area,0,sizeof(light_area));
		
		forw_now=back_now=MP(-100,360);
	}
					void pos_being_information(position_3D pos,bool &bgh,bool &srh,bool &gth,bool &plh,bool &bnh
					,bug &bg,spider &sr,ghost &gt,bug_nest &bns,life_injury &lfin){
						MAP &POS=game_map[pos.x][pos.y][pos.z];
						thing &THING=POS.things;
						if(bug_here(pos)&&POS.emy.id>=0&&POS.emy.id<bugs.size()){//�г��� 
							bg=bugs[POS.emy.id];
							lfin=bg.lfin;
							bgh=1;
						}
						else if(spider_body_here(pos)&&POS.emy.id>=0&&POS.emy.id<spiders.size()){//��֩��
							sr=spiders[POS.emy.id];
							lfin=sr.lfin;
							srh=1;
						}
						else if(ghost_here(pos)&&POS.emy.id>=0&&POS.emy.id<ghosts.size()){//�й� 
							gt=ghosts[POS.emy.id];
							lfin=gt.lfin;
							gth=1;
						}
						else if(player_here(pos))//��� 
							plh=1;
						else if(bug_nest_here(pos)&&THING.nst.id>=0){//��Ѩ
							bns=bug_nests[THING.nst.id];
							lfin=bns.lfin;
						}
					}
				PII pos_background_color(position_3D pos){//��λ�õı���ɫ 
					PII back=MP(0,0); 
					MAP &POS=game_map[pos.x][pos.y][pos.z];
					thing &THING=POS.things;
					bool bgh=0,srh=0,gth=0,plh=0,bnh=0;
					bug bg;bg.init(pos000,0);//���� 
					spider sr;sr.init(pos000,0);//֩�� 
					ghost gt;gt.init(pos000,0,0);//��
					bug_nest bns;bns.init(pos000);//��Ѩ 
					life_injury lfin;lfin.init(0);
					pos_being_information(pos,bgh,srh,gth,plh,bnh,bg,sr,gt,bns,lfin);
					special_attribute spat=gt.spat;//��ļ��� 
					PSB ssl=str_spider_leg(pos);
					string sleg=ssl.first;bool slk=ssl.second;
					int door_d=atd(calc_angle(pos,player1.pos));
					if(POS.emy.dead&&POS.emy.body_disapp>game_time)//ʬ��
						back=MP(0,0);//��
					else if(plh&&(player1.color==3||player1.color==4||player1.color==5))//��ҹ�Ȧ����ʾ��Ϣ�� 
						back=MP(0,240);//��
					else if(bgh&&bg.lfin.change==2||srh&&sr.lfin.change==2||gth&&gt.lfin.change==2
					||bnh&&bns.lfin.change==2||plh&&player1.color==2) back=MP(0,0);//��
					else if(bgh&&bg.lfin.change==1||srh&&sr.lfin.change==1||gth&&gt.lfin.change==1
					||bnh&&bns.lfin.change==1||plh&&player1.color==1) back=MP(0,120);//�� 
					//����/��Ѩ�ڣ���ʷ����BUG���Ӽ�Ѫ 
					else if(THING.lsr.exist)//��������Ȧ 
					//&&(!light_through(dtp3(pos,THING.lsr.laser_beam,4),1)||THING.mirrors.exist||THING.windows.exist||THING.mvb.exist)
						back=MP(0,180);//�� 
					else if(mvb_here(pos)&&THING.mvb.kind==BOX){//����
						if((!(food_above(pos)==food00)||!(ppt_above(pos)==ppt00))&&!closed_box_here(pos,door_d)) back=MP(-75,60);//��ֹ����̫�������嶫�� 
						else back=MP(-25,60);//��
					}
					else if(srh&&sr.kind)//B��֩�� 
						back=MP(-100,360);//�� 
					else if(sleg!=""&&slk)//B��֩�븽֫ 
						back=MP(-100,360);//�� 
					else if(THING.hdr.exist)//������
						back=MP(-15,360);//�� 
					else if(window_here(pos)){//���� 
						if(THING.windows.state) back=MP(0,180);//�� �� 
						else back=MP(-10,360);//ǳ�� �� 
					}
					else if(curtain_here(pos))//����
						back=MP(-20,360);//��
					else if(door_here(pos)){//��
						if(THING.kdr.state==1) back=MP(-20,120);//���� ��
						else back=MP(-20,60);//��� ��/�� 
					}
					else if(exit_here(pos))//����
						back=MP(0,120);//�� 
					else if(gth&&!(spat.can_disappear()&&spat.disa.kind==2)){//��û��������ʧ�� �Ĺ�Ȧ�����ܣ� 
						switch(spat.defense){
							case 0:back=MP(-100,360);break;
							case EVADE:back=MP(-20,120);break;
							case ROCK:back=MP(-20,360);break;
							case SHIELD:back=MP(-20,180);break;
						}
						if(spat.can_disappear()&&spat.disa.kind==1)//������ 
							back=MP(-10,360);//ǳ�� ǽ 
					}
					else if(wall_here(pos))//ǽ
						back=MP(-10,360);//ǳ��
					else back=MP(0,360);//�ף��������ǿյػ���¥�������/���ӣ� 
					return back; 
				}
				PII pos_forward(position_3D pos){//��λ�õ�ǰ��ɫ 
					PII forw=MP(0,0);
					MAP &POS=game_map[pos.x][pos.y][pos.z];
					thing &THING=POS.things;
					bool bgh=0,srh=0,gth=0,plh=0,bnh=0;//������ʲô���� 
					bug bg;bg.init(pos000,0);//���� 
					spider sr;sr.init(pos000,0);//֩�� 
					ghost gt;gt.init(pos000,0,0);//��
					bug_nest bns;bns.init(pos000);//��Ѩ 
					life_injury lfin;lfin.init(0);
					pos_being_information(pos,bgh,srh,gth,plh,bnh,bg,sr,gt,bns,lfin);
					special_attribute spat=gt.spat;
					PSB ssl=str_spider_leg(pos);
					string sleg=ssl.first;bool slk=ssl.second;
					int door_d=atd(calc_angle(pos,player1.pos));
					if(POS.emy.dead&&POS.emy.body_disapp>game_time){//ʬ��
						forw=MP(0,360);//��
					}
					else if(srh){//֩�뱾��
						if(THING.snt.endurance>50||sr.kind) forw=MP(25,360);//��
						else forw=MP(-200,360);//��
					}
					/*
					else if(THING.snt.nowk()>=1000){
						forw=MP(25,360);
						out=int_to_str(THING.snt.nowk()/1000,2);
					}*/
					else if(plh){//���
						special_effect &spe=player1.spe;
						if(player1.pull_thing){//��ʾ������Ʒ
							forw=MP(0,360);
						}
						else if(player1.color==3){//��ʾ��Ϣ 
							forw=MP(0,360);//��
						}
						else if(player1.color==4){
							forw=MP(0,360);//��
						}
						else if(player1.color==5){
							forw=MP(0,360);//�� 
						}
						else if(spe.mts.exist()&&player1.vts.lfin.change==2){//�ж�
							forw=MP(0,120);//��
						}
						else if(spe.vtg.exist()){//ѣ�� 
							forw=MP(0,300);//��
						}
						else if(spe.bds.exist()){//ʧ�� 
							forw=MP(-200,360);//��
						} 
						else if(spe.cfs.exist()){//�Ի� 
							forw=MP(0,60);//��
						}
						else if(spe.wks.exist()){//����
							forw=MP(-20,360);//�� 
						}
						else if(spe.xry.num>1){//͸��
							forw=MP(0,240);//��
						}
						else{//������ʾ 
							forw=MP(0,240);//��
						}
					}
					else if(gth&&!(spat.can_disappear()&&spat.disa.kind==2)&&!closed_box_here(pos,door_d)&&!wall_here(pos)){
					//��û��������ʧ��û�в��������û�д�ǽ�� 
						switch(spat.attack){
							case 0:forw=MP(0,360);break;
							case VAMPIRE:forw=MP(0,0);break;
							case DISAPP:forw=MP(0,60);break;
							case THROUGH:forw=MP(0,180);break; 
							case INSTANT:forw=MP(0,300);break;
						}
						if(spat.can_disappear()&&spat.disa.kind==1){//������ 
							forw=MP(-80,360);//ǳ�� ǽ 
						}
					}
					else if(bgh&&!closed_box_here(pos,door_d)){//�棨û�в��������  
						if(bg.lfin.change!=0) forw=MP(0,360);//��
						else if(THING.snt.exist()) forw=MP(25,360);//��
						else forw=MP(0,0);//��
					}
					else if(sleg!=""&&slk){//B��֩�븽֫ 
						forw=MP(0,360);//�� 
					} 
					else if(mvb_here(pos)
					&&!(box_here(pos)&&THING.mvb.door[door_d]&&(!(food_above(pos)==food00)||smb_above(pos)||!(ppt_above(pos)==ppt00)))
					){//������Ǳ��䣨���ü�����Ķ����� 
						bool select=(player1.items.rmv.select==pos);
						if(select) forw=MP(0,180);//�� ��ѡ�� 
						else if(THING.snt.exist()) forw=MP(25,360);//��
						switch(THING.mvb.kind){
							case BOX:
								if(!select) forw=MP(0,360);//�� 
								break;
							case DESK: 
								if(!select) forw=MP(-25,60);//�� 
								break;
							case CHAIR:
								if(!select) forw=MP(-25,60);//��
								break;
							case BALL:
								if(!select) forw=MP(-30,360);//��� 
								break; 
						}
					}
					else if(THING.nst.exist){//��Ѩ��
						if(bns.lfin.change){
							forw=MP(0,360);//��
						}
						else{
							forw=MP(0,0);//��
						}
					}
					else if(THING.spr.exist){//ì
						int d=THING.spr.d;
						if(THING.nst.exist) forw=MP(0,0);//��
						else forw=MP(-20,60);//��� 
					}
					else if(THING.swd.exist){//�� 
						forw=MP(-60,360);
					}
					else if(THING.bld.exist){//�� 
						forw=MP(-40,360);
					}
					else if(THING.snt.endurance>50){
						if(bgh) forw=MP(25,0);//�� 
						else forw=MP(25,360);//��
						//1~25����  26~50����  51~75��˿  76~100����
						int edc=THING.snt.endurance;
					}
					else if(sleg!=""){//A��֩�븽֫
						if(THING.snt.endurance>0) forw=MP(50,360);//��
						else forw=MP(-200,360);//��
					}
					else if(THING.drt.exist()){//������
						if(THING.nst.exist) forw=MP(0,0);//��
						else forw=MP(0,240);//��
					}
					else if(THING.ssk.exist()){//���е�֩��˿ 
						forw=MP(-100,360);//�� 
					}
					else if(THING.snt.endurance>0){//��һ���֩���� 
						forw=MP(25,360);//��
						//1~25����  26~50����  51~75��˿  76~100����
						int edc=THING.snt.endurance;
					}
					else if(door_here(pos,0)){//������
						forw=MP(0,360);//�� 
					} 
					else if(door_here(pos,2)){//�ص���
						if(plh) forw=MP(0,240);//��
						else forw=MP(0,360);//��
					}
					else if(weapon_above(pos)){//������
						switch(weapon_above(pos)){
							case LAS:
								forw=MP(-40,180);//�� 
								break;
							case DAR:
								forw=MP(0,240);//��
								break;
							case SPE:
								forw=MP(-20,60);//��� 
								break; 
							case DAG:
								forw=MP(-40,360);//��
								break;
							case SWO:
								forw=MP(-40,360);//��
								break;  
							case BLA:
								forw=MP(-20,360);//��
								break; 
						}
					}
					else if(!(food_above(pos)==food00)){//��ʳ��
						food foods=food_above(pos);
						switch(foods.effect){
							case 1:forw=MP(-20,60);//��� 
								break;
							case 2:forw=MP(-20,300);//���� 
								break;
							case 3:forw=MP(0,240);//�� 
								break;
						}
					}
					else if(THING.lsr.exist){//����
						forw=MP(0,360);
					}
					else if(door_here(pos,1)){//ò��������
						if(plh) forw=MP(0,240);//��
						else forw=MP(0,360);//��
					}
					else if(THING.hdr.exist){//������
						forw=MP(-80,360);//��
					}
					else if(window_here(pos)){//����
						int endurance=THING.windows.endurance,state=THING.windows.state;
						if(state) forw=MP(0,360);//�� ��
						else forw=MP(0,180);//�� ��
					} 
					else if(curtain_here(pos)){//����
						int endurance=THING.crt.endurance;
						forw=MP(-80,360);//�����
					}
					/*else if(THING.wee.exist){//����������/�;öȻظ�
						int num=THING.wee.num,kind=THING.wee.kind;
						switch(kind){
							case 0:forw=MP(0,180);//�� �������� 
								break;
							case 1:forw=MP(-20,60);//��� ì�;ö� 
								break;
						}
					}*/
					else if(smb_above(pos)){//������
						forw=MP(-100,360);
					}
					else if(!(ppt_above(pos)==ppt00)){//��͸�ӵ���
						see_through_prop ppt=ppt_above(pos);
						int kind=ppt.kind,time=ppt.time;
						switch(kind){
							case 1:forw=MP(0,240);//�� 
								break;
							case 2:forw=MP(-20,300);//���� 
								break;
							case 3:forw=MP(-20,60);//��� 
								break;
						}
					}
					else if(key_above(pos)){//��Կ�� 
						forw=MP(0,0);//�� 
					}
					else if(THING.lgt.exist){//�� 
						forw=MP(-200,360);//���� 
					}
					else if(THING.exit_signs.exist){//��ָ����ڵı���
						forw=MP(0,120);//�� 
					}
					else if(POS.maze==EXIT){//���� 
						forw=MP(0,360);//�� 
					}
					else if(stair_here(pos)){//¥�� 
						forw=MP(-100,360);//�� 
					}
					else if(POS.maze==WALL){//�����Ƕ�ǽ 
						forw=MP(-80,360);//����� 
					}
					else{//�����ǿյ� 
						forw=MP(0,360);//�� 
						//forw=MP(-100,360);
						//out=double_to_str(POS.things.fogs.absorbance*100,0,2);//���� 
					}
					return forw; 
				}
				string pos_output(position_3D pos){//��λ�õ�������� 
					string out=""; 
					MAP &POS=game_map[pos.x][pos.y][pos.z];
					thing &THING=POS.things;
					bool bgh=0,srh=0,gth=0,plh=0,bnh=0;//������ʲô���� 
					bug bg;bg.init(pos000,0);//���� 
					spider sr;sr.init(pos000,0);//֩�� 
					ghost gt;gt.init(pos000,0,0);//��
					bug_nest bns;bns.init(pos000);//��Ѩ 
					life_injury lfin;lfin.init(0);
					pos_being_information(pos,bgh,srh,gth,plh,bnh,bg,sr,gt,bns,lfin);
					special_attribute spat=gt.spat;
					PSB ssl=str_spider_leg(pos);
					string sleg=ssl.first;bool slk=ssl.second;
					int door_d=atd(calc_angle(pos,player1.pos));
					if(POS.emy.dead&&POS.emy.body_disapp>game_time){//ʬ��
						out="KO"; 
					}
					else if(srh){//֩�뱾��
						if(sr.kind==1) out="�J";
						else out="��";  
					}
					/*
					else if(THING.snt.nowk()>=1000){
						forw=MP(25,360);
						out=int_to_str(THING.snt.nowk()/1000,2);
					}*/
					else if(plh){//���
						special_effect &spe=player1.spe;
						if(player1.pull_thing){//��ʾ������Ʒ
							out="��"; 
						}
						else if(player1.color==3){//��ʾ��Ϣ 
							switch(player1.d1){//��ʾ���� 
								case 0:out="��";
									break;
								case 1:out="��";
									break;
								case 2:out="��";
									break;
								case 3:out="��";
									break;
							}
							out+=" "; 
						}
						else if(player1.color==4){
							out="��";
						}
						else if(player1.color==5){
							out=player1.flash_word;
						}
						else if(spe.mts.exist()&&player1.vts.lfin.change==2){//�ж�
							out="��"; 
						}
						else if(spe.vtg.exist()){//ѣ�� 
							out="��";
						}
						else if(spe.bds.exist()){//ʧ�� 
							out="ä"; 
						} 
						else if(spe.cfs.exist()){//�Ի� 
							out="��";
						}
						else if(spe.wks.exist()){//����
							out="��"; 
						}
						else if(spe.xry.num>1){//͸��
							out="��";
						}
						else{//������ʾ 
							out=player1.name.substr(0,2);
						}
					}
					else if(gth&&!(spat.can_disappear()&&spat.disa.kind==2)&&!closed_box_here(pos,door_d)&&!wall_here(pos)){
					//��û��������ʧ��û�в��������û�д�ǽ�� 
						if(spat.eva.use) out="��";
						else if(spat.rck.use) out="��";
						else if(spat.can_through()) out="�q";//��ǽ�� 
						else if(spat.can_disappear()&&spat.disa.kind==1){//������ 
							out="ǽ";
						}
						else{
							/*
							������ 
							��ǽ���q
							˲�ƣ��� 
							ʯ������
							���ܣ��� */
							if(spat.attack==DISAPP) out="��";
							else if(spat.attack==THROUGH) out="�q";
							else if(spat.attack==INSTANT) out="��";
							else if(spat.defense==ROCK) out="��";
							else if(spat.defense==EVADE) out="��";
							else out="��";
							//out=double_to_str(gt.lfin.life,0,2);
						}
						/**/
						special_effect &spe=gt.spe;
						if(spe.mts.exist()&&gt.lfin.change==2)//�ж�
							out="��"; 
						else if(spe.vtg.exist())//ѣ�� 
							out="��";
						else if(spe.bds.exist())//ʧ�� 
							out="ä"; 
						else if(spe.wks.exist())//����
							out="��"; 
						//�������Ч��ֻӰ���ӡ������ 
						if(lfin.change&&lfin.lst_hurt>=1)
							out=int_to_str(lfin.lst_hurt,2);
					}
					else if(bgh&&!closed_box_here(pos,door_d)){//�棨û�в��������  
						out="��";  
					}
					else if(sleg!=""&&slk){//B��֩�븽֫ 
						out=sleg;
					} 
					else if(mvb_here(pos)
					&&!(box_here(pos)&&THING.mvb.door[door_d]&&(!(food_above(pos)==food00)||smb_above(pos)||!(ppt_above(pos)==ppt00)))
					){//������Ǳ��䣨���ü�����Ķ����� 
						switch(THING.mvb.kind){
							case BOX:
								if(THING.mvb.door[door_d]) out="[]";//atd(...):��ҿ��ø����������һ��
								else out="��";
								break;
							case DESK: 
								out="��";
								break;
							case CHAIR:
								out="��";
								break;
							case BALL:
								out="��";
								break; 
						}
					}
					else if(THING.spr.exist){//ì
						int d=THING.spr.d;
						if(THING.spr.head){
							switch(d){
								case 0:out="��";
									break;
								case 1:out="�J";
									break;
								case 2:out="��";
									break;
								case 3:out="�K";
									break;
								case 4:out="��";
									break;
								case 5:out="�L";
									break;
								case 6:out="��";
									break;
								case 7:out="�I";
									break;
							}
							out+=" "; 
						}
						else{
							switch(d){
								case 0:case 4:out="��";
									break;
								case 2:case 6:out="��";
									break;
								case 1:case 5:out="��";
									break;
								case 3:case 7:out="��";
									break;
							}
						}
					}
					else if(THING.swd.exist){//�� 
						out="��";
					}
					else if(THING.bld.exist){//�� 
						if(THING.bld.head) out="��";
						else out="�� ";
					}
					else if(THING.snt.endurance>50){
						//1~25����  26~50����  51~75��˿  76~100����
						int edc=THING.snt.endurance;
						if(edc>75) out="��";
						else out="˿";
					}
					else if(sleg!=""){//A��֩�븽֫
						out=sleg;
					}
					else if(THING.drt.exist()){//������
						if((pos.x%2)^(pos.y%2)) out="�� ";
						else out="ʮ"; 
					}
					else if(THING.ssk.exist()){//���е�֩��˿ 
						out="ss"; 
					}
					else if(THING.snt.endurance>0){
						//1~25����  26~50����  51~75��˿  76~100����
						int edc=THING.snt.endurance;
						if(edc>25) out="��";
						else out="��";
					}
					else if(door_here(pos,0)){//������
						switch(THING.kdr.kind){
							case DOOR1:out="1";
								break;
							case DOOR2:out="2";
								break;
							case DOOR3:out="3";
								break;
							case DOOR4:out="4";
								break;
						}
						out+="]";
					} 
					else if(door_here(pos,2)){//�ص���
						if(THING.kdr.light_through) out=" ]";
						else out="��";
					}
					else if(weapon_above(pos)){//������
						switch(weapon_above(pos)){
							case LAS:
								out="��";
								break;
							case DAR:
								if((pos.x%2)^(pos.y%2)) out="�� ";
								else out="ʮ"; 
								break;
							case SPE:
								out="ì";
								break; 
							case DAG:
								out="ذ";
								break;
							case SWO:
								out="��";
								break;  
							case BLA:
								out="��";
								break;  
						}
					}
					else if(!(food_above(pos)==food00)){//��ʳ��
						food foods=food_above(pos);
						if(foods.kind==ADDL) out="v+";
						else out="��";
					}
					else if(THING.nst.exist){//��Ѩ��
						if(bns.lfin.change){
							out=double_to_str(bns.lfin.life,0,2); 
						}
						else{
							out="��";
						}
					}
					else if(THING.lsr.exist){//����
						out="�� ";
					}
					else if(THING.hdr.exist){//������
						out="ǽ";//��ǽ��������һ�� 
					}
					else if(window_here(pos)){//����
						int endurance=THING.windows.endurance,state=THING.windows.state;
						if(endurance==100) out="��"; 
						else out=int_to_str(endurance,2);
					} 
					else if(curtain_here(pos)){//����
						int endurance=THING.crt.endurance;
						if(endurance==100) out="��";
						else out=int_to_str(endurance,2);
					}
					else if(THING.wee.exist){//����������/�;öȻظ�
						int num=THING.wee.num,kind=THING.wee.kind;
						out="+"+int_to_str(num);
					}
					else if(smb_above(pos)){//������
						out="��"; 
					}
					else if(!(ppt_above(pos)==ppt00)){//��͸�ӵ���
						see_through_prop ppt=ppt_above(pos);
						int kind=ppt.kind,time=ppt.time;
						out=int_to_str(time/1000,2); 
					}
					else if(key_above(pos)){//��Կ�� 
						switch(key_above(pos)){
							case KEY1:
								//forw=MP(0,0);//�� 
								out="1=";
								break;
							case KEY2:
								//forw=MP(0,0);//�� 
								out="2=";
								break;
							case KEY3:
								//forw=MP(-100,360);//�� 
								out="3=";
								break;
							case KEY4:
								//forw=MP(-100,360);//�� 
								out="4=";
								break;
						}
					}
					else if(THING.lgt.exist){//�� 
						if(THING.lgt.state) out="�� ";
						else out="��";
					}
					else if(THING.exit_signs.exist){//��ָ����ڵı���
						switch(THING.exit_signs.dir){
							case 0:out="��";
								break;
							case 1:out="��";
								break;
							case 2:out="��";
								break;
							case 3:out="��";
								break;
						}
						out+=" "; 
					}
					else if(door_here(pos,1)){//ò��������
						if(THING.kdr.light_through) out=" ]";
						else out="��";
					}
					else if(POS.maze==EXIT){//���� 
						if(pos.x==1||pos.y==1) out="E]";
						else out="[E";
					}
					else if(stair_here(pos)){//¥�� 
						switch(POS.maze){
							case UPSTAIR:
								out="��";
								break;
							case DOWNSTAIR:
								out="��";
								break;
						}
					}
					else if(POS.maze==WALL){//�����Ƕ�ǽ 
						out="ǽ";
					}
					else{//�����ǿյ� 
						out="  ";
						//forw=MP(-100,360);
						//out=double_to_str(POS.things.fogs.absorbance*100,0,2);//���� 
					}
					return out; 
				}
				int pos_brightness(position_3D u){//һ��λ�õ�ʵ�ʹ������� 
					MAP &POS=game_map[u.x][u.y][u.z];
					int B=POS.brightness;
					if(exit_here(u)||u.z!=player1.pos.z){//����/¥����������ʾ���� 
						limit_int(B,-25,25);
						return B;
					}
					if(light_through(u,2)||player_here(u)) return POS.brightness;//͸��λ�û����λ�� 
					int ret=-100;
					for(int i=0;i<4;i++){//��͸��λ��
						position_3D v=dtp3(u,i,4);
						MAP &NPOS=game_map[v.x][v.y][v.z];
						if(light_through(v,2)&&NPOS.ist.player==lst_see_time||player_here(v))//��ֹ�������ű�����Ϲ 
							ret=max(ret,NPOS.brightness);//��Χ���Կ�����͸��λ��/���λ�������е����ֵ 
					}
					return ret;
				}
			string print_game_map_pos(position_3D pos,int kind){//kind=1�����������ù�� 2�����������ù�� 3����������ݣ�ֻ���ر��� 
				//�������������������ݵı���
				position_2D spos=position_3Dtoscr(pos); 
				int x=pos.x,y=pos.y,z=pos.z,px=spos.x,py=spos.y;//���������� 
				game_flag["����ר��"]=true; 
				MAP &POS=game_map[x][y][z];
				thing &THING=POS.things;
				int brightness=pos_brightness(pos);//����ǿ�� 
				//brightness=0;//ȫ�� 
				PII back=MP(0,0),forw=MP(0,0);
				string out="";
				int dis=MHT_DIST_p3(player1.pos,pos);
				dim_sight &dst=player1.spe.dst;
				int delta_t=game_time-dst.time;
				bool quick_move=delta_t<dst.last;
				double k=player1.vts.stg.physical_strength/100.0;//����Խ�Ϳ����ķ�ΧԽС 
				bool flag=true;//�Ƿ��ӡ 
				/*��̬ģ�� 
				if(dis>dst.cpt*k&&quick_move){//��Զ��ģ����ʾ 
					brightness=-90;
					back=MP(-70,360);forw=MP(-70,360);
					out="  ";
					dst.dim=true;
					flag=false;
				}
				/*
				else if(dis>dst.part*k//�о��봦ֻ��ʾ��Ҫ��Ϣ 
				&&nobody_here(pos)&&!THING.foods.exist()&&!THING.kdr.exist&&!THING.lgt.exist //û�����ʳ��š��ƾͲ���ʾ
				&&quick_move//�����ƶ��� 
				){
					brightness=-70;
					back=MP(-50,360);forw=MP(-50,360);
					out="  ";
					dst.dim=true;
					flag=true;
				}
				else{
				}*/
				back=pos_background_color(pos);//����ɫ 
				forw=pos_forward(pos);//ǰ��ɫ
				out=pos_output(pos);//�������
				back.first+=brightness;forw.first+=brightness;
				limit_int(back.first,-100,100);
				limit_int(forw.first,-100,100);
				//���ݹ���ǿ�ȶ�����������
				flag=true;
				double vague=POS.ist.pvg();
				//����ģ��ϵ��������ɫ 
				string code=PII_to_str(back)+","+PII_to_str(forw)+" "+out;//������� 
				if(kind==1&&!pos_in_game_map(spos)//��겻����Ϸ��ͼ��Χ�� 
				||kind==3||!flag)//����� 
					return code;
				if(kind==1) gotoxy(px,py);//�ƶ���� 
				double vague_RGB[3];
				RGB_brightness(vague_RGB,POS.ist.vague,POS.brightness);//���������޸�һ��POS.ist.vague���ظ�vague_color 
				//set_RGBcolor_vague(back.first,back.second,forw.first,forw.second,vague,brightness,0);//������ɫ 
				//set_RGBcolor_vague(back.first,back.second,forw.first,forw.second,vague,POS.things.fogs.col);//������ɫ
				set_RGBcolor_vague(back.first,back.second,forw.first,forw.second,vague_RGB);//������ɫ
				//���ԣ��� 
				cout<<out<<endl;
				return code;
			}
		void print_game_map_z(int z){//�ݲ����� 
			for(int y=1;y<=width;y++){
				for(int x=1;x<=length;x++){
					gotoxy((x-1)*2,y-1+(height*2-z)*width);
					print_game_map_pos((position_3D){x,y,z},2);
					//SLEEP(5);
				}
			}
		}
	void print_game_map(){//�ݲ����� 
		for(int z=1;z<=height*2;z++) print_game_map_z(z);
	}
			void rand_basic(int sx,int sy,int sz,int a,int b,int c,const int l=length,const int w=width,int h1=1,int h2=height){
			//���ɻ����Թ����յ�+ǽ+¥��+��Ѩ��һ��ͨ·��������ߴ���ָһ����Ϸ���ģ���������Ѩ�� 
			//a��b��c�ֱ�ָ����¥�ݡ�����->���³�Ѩ�ڡ�����->���泲Ѩ�ڵĸ��� 
			//h1~h2:���ɵĸ߶ȷ�Χ 
				memset(stair_exist,0,sizeof(stair_exist));
				vector<position_3D> vec;//�洢ֻ����һ����ǽλ�õ�ǽ
				map<position_3D,bool> f;//���ǽ�Ƿ����б��� 
				position_3D st;st.x=sx,st.y=sy;st.z=sz;
				int smaze=2;//0��UPSTAIR 1��DOWNSTAIR 2��SPACE 
				if(sz<h2&&sz>h1) smaze=RAND(1,0);
				else if(sz<h2) smaze=0;
				else if(sz>h1) smaze=1;
				//��װ¥�ݾ�װ¥�� 
				if(smaze==2){
					game_map[sx][sy][sz].maze=SPACE;cnt_SPACE++;
				}
				else{
					position_3D pos=st;
					if(smaze==0) pos.z=sz+1;
					else pos.z=sz-1;
					game_map[sx][sy][pos.z].maze=UPSTAIR+(smaze^1),stair_exist[pos.z][smaze^1]=true;
					for(int i=0;i<4;i++){
						position_3D v=dtp3(pos,i,4);
						if(pos_in_area2(v.x,v.y,1,1,l,w,2))
							vec.push_back(v),f[v]=true;
					}
					game_map[sx][sy][sz].maze=UPSTAIR+smaze;stair_exist[sz][smaze]=true;cnt_STAIRS++;
				}
				cnt_notWALL++;
				for(int i=0;i<4;i++){
					position_3D u=dtp3(st,i,4);
					if(pos_in_area2(u.x,u.y,1,1,l,w,2)){
						vec.push_back(u);f[u]=true; 
					}
				}
				while(vec.size()){
					int k=RAND(vec.size()-1,0);
					position_3D u=vec[k];//���ѡһ��ǽ
					swap(vec[k],vec[vec.size()-1]);vec.pop_back();f[u]=0;//��ǽuɾ�� 
					if(count_around_pos(u,4,wall_here,l,w)==3&&pos_in_area2(u.x,u.y,1,1,l,w,2)){
					//���Ǳ�Եǽ�Һ����涼��ǽ����������ͨ·��������չ
						for(int i=0;i<4;i++){//�������u���ǽ������ʧ����ǰ������Χ��ǽ����� 
							position_3D v=dtp3(u,i,4);
							if(!f.count(v)&&game_map[v.x][v.y][v.z].maze==WALL&&pos_in_area2(v.x,v.y,1,1,l,w,2))
								vec.push_back(v),f[v]=true;
						}
						bool add_stair=RAND_BOOL(a),add_up=0,add_down=0;
						//�Ƿ��¥�ݣ�����/��¥�ݷֱ��в��У����ӵĳ�Ѩ�ڲ��ݲ��������¥�ݣ� 
						int stair_kind;//¥�ݵ����ࣨ0��UPSTAIR 1��DOWNSTAIR�� 
						position_3D u2=u;u2.z++;//������/��¥��ͨ����λ�� 
						if(u.z<=h2&&u.z>=h1&&u2.z<=h2&&game_map[u2.x][u2.y][u2.z].maze==WALL&&count_around_pos(u2,4,wall_here,l,w)==4)
							add_up=true; 
						//��һ����Ϸ����������¥��ͨ�������λ�ò��ǿյ�����Χ����ǽ�� 
						u2=u;u2.z--;//������¥��ͨ����λ�� 
						if(u.z<=h2&&u2.z>=h1&&u2.z<=h2&&game_map[u2.x][u2.y][u2.z].maze==WALL&&count_around_pos(u2,4,wall_here,l,w)==4)
							add_down=true; 
						//��һ����Ϸ����������¥��ͨ�������λ�ò��ǿյ�����Χ����ǽ�� 
						bool add_nest=RAND_BOOL((u.z<=height?b:c)); 
						position_3D u3=u;u3.z+=(u.z>height?-height:height);//�����/����Ѩ��ͨ����λ��
						//��>height:�ڳ�Ѩ�-=height <=height:�ڳ�Ѩ�⣬+=height�� 
						if(!(game_map[u3.x][u3.y][u3.z].maze==WALL&&count_around_pos(u3,4,wall_here,l,w)==4))
							add_nest=false;
						//��/����Ѩ��ͨ�������λ�ò��ǿյ�����Χ����ǽ�� ��������������Ͳ��� 
						if((add_up||add_down)//����¥��������һ����
						&&((add_up&&!stair_exist[u.z][0])//��㻹û������¥��
						||(add_down&&!stair_exist[u.z][1])//����㻹û������¥�� 
						||add_stair)//�����¥��
						){
							u2=u;
							if(add_up&&add_down) stair_kind=RAND(1,0);
							else if(add_up) stair_kind=0;
							else stair_kind=1;
							if(stair_kind==0) u2.z++;
							else u2.z--;
							for(int i=0;i<4;i++){//¥��/����Χ��ǽ 
								position_3D v=dtp3(u2,i,4);
								if(!f.count(v)&&pos_in_area2(v.x,v.y,1,1,l,w,2))
								//���汣֤¥����Χ����ǽ�����Բ����ж�
									vec.push_back(v),f[v]=true;
							}
							game_map[u.x][u.y][u.z].maze=UPSTAIR+stair_kind;
							game_map[u2.x][u2.y][u2.z].maze=UPSTAIR+(stair_kind^1);
							stair_exist[u.z][stair_kind]=true;stair_exist[u2.z][stair_kind^1]=true;
							cnt_STAIRS+=2;cnt_notWALL+=2;
						}
						else if(add_nest){//�Ӹ���Ѩ��û����
							for(int i=0;i<4;i++){//��/����Ѩ�ں���Χ��ǽ 
								position_3D v=dtp3(u3,i,4);
								if(!f.count(v)&&pos_in_area2(v.x,v.y,1,1,l,w,2))
								//���汣֤��/����Ѩ�ں���Χ����ǽ�����Բ����ж�
									vec.push_back(v),f[v]=true;
							}
							bug_nest bns;//���ɳ�Ѩ��
							if(u.z<=height) bns.init(u);
							else bns.init(u3);
							//�洢��һ����Ϸ���������
							bug_nests.push_back(bns);
							int id=int(bug_nests.size())-1;
							game_map[u.x][u.y][u.z].maze=game_map[u3.x][u3.y][u3.z].maze=SPACE;
							nest &NST=game_map[u.x][u.y][u.z].things.nst,&NST2=game_map[u3.x][u3.y][u3.z].things.nst;
							//�ֱ��Ӧu��u3�����������ã������� 
							NST.exist=NST2.exist=true;NST.id=NST2.id=id;//������Ӧ�ĳ�Ѩ�ڹ���һ����� 
							NST.to=u3;NST2.to=u;//��Ѩ�ڵ������Ӧ���� 
							cnt_SPACE++;cnt_notWALL++;
						}
						else{//¥�ݷ��˻�����һ��ͨ·���߲����¥�ݣ���ֻ�ǿյ� 
							game_map[u.x][u.y][u.z].maze=SPACE;
							cnt_SPACE++;cnt_notWALL++;
						}
					}
				}
			}
			void fill_dead_ends(int kind,int a,int l=length,int w=width,int h1=1,int h2=height){//�������ͬ 
				vector<position_3D> vec;//�洢ֻ����һ���յصĿյأ�����ͬ��
				int cnt2=0;//�������ĵط������ڲ�һ��������ͬ�� 
				for(int z=h1;z<=h2;z++)
					for(int y=2;y<w;y++)
						for(int x=2;x<l;x++){
							position_3D u;
							u.x=x;u.y=y;u.z=z;
							if(space_here(u)&&empty_here(u)){
								cnt2++;
								if(count_around_pos(u,4,wall_here,l,w)==3&&count_around_pos(u,4,nest_here,l,w)==0) vec.push_back(u);
							}
						}
				int cnt=0;
				if(kind==1) cnt=a;
				else cnt=cnt2*a/100;
				while(vec.size()&&cnt){
					int k=RAND(vec.size()-1,0);
					position_3D u=vec[k];//���ѡһ������ǽ��λ��
					game_map[u.x][u.y][u.z].maze=WALL;cnt--;
					swap(vec[k],vec[vec.size()-1]);
					vec.erase(vec.begin()+vec.size()-1);
					//�����λ�øĳ�ǽ��ɾ��
					for(int i=0;i<4;i++){//һ��������ǽֻ��ʹ��Χ�Ŀյؿ��ܱ������ͬ 
						position_3D v=dtp3(u,i,4);
						if(space_here(v)&&empty_here(v)&&count_around_pos(v,4,wall_here,l,w)==3&&count_around_pos(v,4,nest_here,l,w)==0
						&&pos_in_area2(v.x,v.y,1,1,l,w,2))//�Ӹ��ж��Ƿ���� 
							vec.push_back(v);
					}
				}
			}
			void make_room(int a,int b,int c,int d,const int l=length,const int w=width,int h=height){
			//a��ȥ��һƬǽ�ĸ��� 
			//b���Ѿ���һ���ǽ�ڹ⣬�γ�һ������ĸ��� 
			//���򻭳�����ͼ k=RAND(c,d),c>=d
				memset(vst,0,sizeof(vst));
				for(int z=1;z<=h;z++){
					//bool flag=0; 
					for(int y=2;y<w;y++){
						for(int x=2;x<l;x++){
							position_3D pos;
							pos.x=x;pos.y=y;pos.z=z;
							if(!vst[x][y][z]&&in_walls(pos)){//���δ�ÿ��δ��չ����ǽ��ʼ��չ 
								//int cnt=1;
								gotoxy();
								//cout<<"start"<<endl;
								//pos.output1(1);cout.flush();
								vector<position_3D> v_wall;//�洢���ϵ�ǽ 
								while(!Q.empty()) Q.pop();
								vst[x][y][z]=1;
								Q.push(pos);
								//cout<<"???"<<endl;
								while(!Q.empty()){
									position_3D u=Q.front();Q.pop();
									//cout<<"???"<<endl;
									v_wall.push_back(u);
									//u.output1(1);cout.flush();
									for(int i=0;i<4;i++){
										position_3D v=dtp3(u,i,4);
										if(pos_in_area2(v.x,v.y,1,1,l,w,2)&&!vst[v.x][v.y][v.z]&&in_walls(v)){//�ڱ�Եǽ�ϵĲ��ڵ� 
											vst[v.x][v.y][v.z]=1;
											Q.push(v);
											//cnt++;
										}
									}
									//if(cnt>30) break;
								}
								if(RAND_BOOL(a)){//�и��ʲ�ȥ�� 
									int sz=v_wall.size(),k=RAND(c,d),kind=RAND_BOOL(b);
									while(sz<k*k*5&&k>=d) k--;
									if(k<d) kind=1;
									int tmp=(k-1)/2;//RAND(k-2,(k-1)/2)��%k=��0~tmpΪ�ڵ���Χ 
									int delta=0;//RAND(k-1,0);//��������� 
									for(int i=0;i<sz;i++){
										position_3D u=v_wall[i];
										if(kind||(u.x+delta)%k<=tmp||(u.y+delta)%k<=tmp) game_map[u.x][u.y][u.z].maze=SPACE;
										//kind:0������ 1ȫ�ڵ� 
									}
									//SLEEP(5*1000);
									//flag=1;
									//break;//����һ�� 
								}
								
							}
						}
						//if(flag) break;
					}
				}
			}
			void enlarge_maze(int l,int w,int h=height){//ӳ�� 
				/*���ӳ�䣺
					x[3,l-1]->[3,length-1]
					y[3,w-1]->[3,width-1]
				¥�ݡ���Ѩ���⴦��
				1�����ѡһ��λ����Ϊӳ���
					valx[][1],valy[][1]
				*/ 
				vector<int> v;//���ȡ��
				memset(flagx,0,sizeof(flagx));
				for(int x=3;x<length;x++) v.push_back(x);//3~length
				flagx[2]=1;
				for(int i=1;i<=l-3;i++){//[3,length-1]ȡl-3�� 
					int sz=v.size();
					int k=RAND(sz-1,0),nx=v[k];
					swap(v[k],v[sz-1]);
					v.pop_back();
					flagx[nx]=1;
				}
				int px=2;
				memset(val_x,0,sizeof(val_x));
				val_x[1][0]=1;val_x[2][0]=2;val_x[length][0]=l;
				int lstx=2;//lstx<x,flagx[lstx]=true 
				for(int x=3;x<length;x++){
					if(flagx[x]){
						//[lstx,x-1]->px
						val_x[RAND(x-1,lstx)][1]=px;//¥�ݻ�Ѩ�� 
						px++;
						lstx=x;
					}
					val_x[x][0]=px;
				}
				//�����x 
				memset(flagy,0,sizeof(flagy));
				v.clear();
				for(int y=3;y<width;y++) v.push_back(y);//3~width
				for(int i=1;i<=w-3;i++){//[3,width-1]ȡw-3�� 
					int sz=v.size();
					int k=RAND(sz-1,0),ny=v[k];
					swap(v[k],v[sz-1]);
					v.pop_back();
					flagy[ny]=1;
				}
				int py=2;
				memset(val_y,0,sizeof(val_y));
				val_y[1][0]=1;val_y[2][0]=2;val_y[width][0]=w;
				int lsty=2;//lsty<y,flagy[lsty]=true 
				for(int y=3;y<width;y++){
					if(flagy[y]){
						//[lsty,y-1]->py
						val_y[RAND(y-1,lsty)][1]=py;
						py++;
						lsty=y;
					}
					val_y[y][0]=py;
				}
				//�����y 
				/*
				gotoxy(0,0);
				set_RGBcolor(-100,360,0,360);
				for(int x=1;x<=length;x++) cout<<val_x[x][0]<<" ";
				cout<<endl;
				for(int y=1;y<=width;y++) cout<<val_y[y][0]<<" ";
				cout<<endl;
				for(int x=1;x<=length;x++) cout<<val_x[x][1]<<" ";
				cout<<endl;
				for(int y=1;y<=width;y++) cout<<val_y[y][1]<<" ";
				cout<<endl;
				SLEEP(5000);*/
				for(int z=1;z<=h*2;z++)
					for(int y=width;y>=1;y--)
						for(int x=length;x>=1;x--){
							position_3D u;
							u.x=val_x[x][0];u.y=val_y[y][0];u.z=z;
							position_3D pos;
							pos.x=x;pos.y=y;pos.z=z;
							MAP &POS=game_map[u.x][u.y][u.z];//��С��ͼ��λ�� 
							MAP &NPOS=game_map[pos.x][pos.y][pos.z];//��λ��
							/*
							bool match_ud=(val_x[x][1]==u.x&&val_y[y][1]==u.y);//����¥/������Ѩ�� 
							if(stair_here(u)){
								if(match_ud){
									NPOS.maze=POS.maze;
								}
								else NPOS.maze=SPACE;
							}
							else if(nest_here(u)&&POS.things.nst.id!=-1){
								if(match_ud){
									bug_nest &bnt=bug_nests[POS.things.nst.id];
									if(h<height) bnt.init(pos);//�洢��һ����Ϸ���������
									NPOS.things.nst=POS.things.nst;
									position_3D &to=NPOS.things.nst.to;
									to.x=x;to.y=y;//�޸ĳ�Ѩ�ڵ�ӳ��� 
									POS.things.nst.init();//ɾ��ԭ��Ѩ�� �� 
								}
								else NPOS.maze=SPACE;
							}
							else NPOS.maze=POS.maze;*/
							bool match_ud=(val_x[x][1]&&val_y[y][1]);//����¥
							NPOS.maze=POS.maze;
							if(stair_here(u)&&!match_ud) NPOS.maze=SPACE;
						}
			}
			void make_hollow(bool spe=true,int l=length,int w=width,int h=height){//�ѷǳ�Ѩ�����о���һ���ǽ�ڳ��п� 
				memset(vst,0,sizeof(vst));//���������� 
				for(int z=1;z<=height;z++)
					for(int y=width;y>=1;y--)
						for(int x=length;x>=1;x--){
							position_3D u;
							u.x=x;u.y=y;u.z=z;
							if(wall_here(u)&&count_around_pos(u,4,wall_here)==4) vst[x][y][z]=1; 
						}
			
					for(int z=1;z<=height;z++)
						if(spe){//���ű�Եǽ��ǽ���ڣ���ֹ������������������� 
							for(int y=width-2;y>=3;y--)
								for(int x=length-2;x>=3;x--)
									if(vst[x][y][z]) game_map[x][y][z].maze=SPACE;
						}
						else{
							for(int y=width-1;y>=2;y--)
								for(int x=length-1;x>=2;x--)
									if(vst[x][y][z]) game_map[x][y][z].maze=SPACE;
						}
			}
			void nest_maze(int a,int b,int c,int l=length,int w=width,int h=height){//�������ɳ�Ѩ
				//a�����ɳ�Ѩ�� b������ͨ�� c���ؿ�ͨ�� 
				for(int z=h+1;z<=h+h;z++){//ö�ٳ�Ѩ��ÿһ�� 
					rand_basic(RAND(l-1,2),RAND(w-1,2),z,1,0,0,l,w,z,z);
					for(int y=1;y<=w;y++)
						for(int x=1;x<=l;x++){
							position_3D u,v;
							u.x=x;u.y=y;u.z=z;
							v.x=x;v.y=y;v.z=z-h;
							MAP &UPOS=game_map[u.x][u.y][u.z];
							MAP &VPOS=game_map[v.x][v.y][v.z];
							int rate=RAND(100,1);//���� 
							if(rate<=a&&space_here(u)&&space_here(v)){
								bug_nest bns;//���ɳ�Ѩ��
								bns.init(v);
								//�洢��һ����Ϸ���������
								bug_nests.push_back(bns);
								int id=int(bug_nests.size())-1;
								UPOS.maze=VPOS.maze=SPACE;
								nest &NST=UPOS.things.nst,&NST2=VPOS.things.nst;
								NST.exist=NST2.exist=true;NST.id=NST2.id=id;//������Ӧ�ĳ�Ѩ�ڹ���һ����� 
								NST.to=v;NST2.to=u;//��Ѩ�ڵ������Ӧ����
							}
							else if(rate<=a+b&&space_here(u)) UPOS.maze=WALL;
						}
				}
				for(int z=h+1;z<=h+h;z++)//ö�ٳ�Ѩ��ÿһ�� 
					for(int y=1;y<=w;y++)
						for(int x=1;x<=l;x++){
							position_3D u;
							u.x=x;u.y=y;u.z=z;
							if(RAND_BOOL(c)&&space_here(u)&&pos_in_area2(x,y,3,l-2,3,w-2)){
								for(int ny=y-1;ny<=y+1;ny++)
									for(int nx=x-1;nx<=x+1;nx++)
										game_map[nx][ny][z].maze=SPACE;
								//�ؿ��3*3 
							}
						}
				fill_dead_ends(2,85,length,width,height+1,height*2);//ɾ��һЩ����ͬ 
			}
			void mark_maze(int l=length,int w=width,int h=height){//����Թ���Ϣ
				for(int z=1;z<=h;z++)
					for(int y=1;y<=w;y++)
						for(int x=1;x<=l;x++){//��Ƿ��� 
							position_3D u;
							u.x=x;u.y=y;u.z=z;
							pos_in_room[x][y][z]=in_room(u);
						}
				for(int z=height+1;z<=height+h;z++)
					for(int y=1;y<=w;y++)
						for(int x=1;x<=l;x++){
							position_3D u;
							u.x=x;u.y=y;u.z=z;
							MAP &POS=game_map[u.x][u.y][u.z];
							if(!wall_here(u)) pos_in_nest.push_back(u);//��Ѩ�ڲ�������ϣ���¼���ӵĸ���� 
						}
			}
				bool path_pos_here(position_3D u){
					return space_here(u)&&empty_here(u)&&divided_part(u)==1&&count_around_pos(u,4,space_here)>1;
				}
			void fill_wide_path(int a,int l=length,int w=width,int mnh=1,int mxh=height){//�ѵ�������·����խ
			//����յأ����ǽ�󲻻�ı��Թ����˽ṹ�Ŀյ� 
				memset(vst,0,sizeof(vst));
				vector<position_3D> path;//��ʱ����ȥ�����Ķ���յ� 
				for(int z=mnh;z<=mxh;z++)
					for(int y=2;y<w;y++)
						for(int x=2;x<l;x++){
							position_3D u;
							u.x=x;u.y=y;u.z=z;
							//MAP &POS=game_map[u.x][u.y][u.z];
							if(path_pos_here(u)){
								vst[u.x][u.y][u.z]=1;
								path.push_back(u);
							}
						}
				//Ԥɸѡ�� 
				int cnt_path=path.size(),cnt_del=cnt_path*a/100;
				int del_space=0;//ʵ���Ѿ�ɾ�˶��� 
				while(del_space<cnt_del&&path.size()>0){
					int k=RAND(path.size()-1,0);
					position_3D u=path[k];
					swap(path[k],path[path.size()-1]);path.pop_back();
					MAP &POS=game_map[u.x][u.y][u.z];
					if(path_pos_here(u)){
						POS.maze=WALL;
						del_space++;
						//�ĳ�ǽ 
						for(int i=0;i<4;i++){
							position_3D v=dtp3(u,i,4);
							if(pos_in_area2(v.x,v.y,1,1,length,width,2)&&path_pos_here(v)&&!vst[v.x][v.y][v.z]){
								vst[v.x][v.y][v.z]=1;
								path.push_back(v);
							} 
						}
						//������Χ�� 
					}
					
				}
			}
			void draft_line(int cnt,int mnl,int mxl,int l=length,int w=width,int h=height){
				//����ˮƽ����ֱ��ǽ 
				for(int z=1;z<=h;z++){//������� 
					int num=cnt;//���¥���� 
					while(num>0){
						int line_length=RAND(mxl,mnl);
						if(RAND_BOOL(50)){//x���䣬 
							int x=RAND(l-2,3),y=RAND(w-line_length+1,1);//��ʼλ�� 
							//if(x==2||x==length-1) continue;//��ֹ��ס��Եǽ 
							for(int i=0;i<line_length;i++)
								game_map[x][i+y][z].maze=WALL;
						}
						else{//y���� 
							int x=RAND(l-line_length+1,1),y=RAND(w-2,3);//��ʼλ�� 
							//if(y==2||y==width-1) continue;//��ֹ��ס��Եǽ 
							for(int i=0;i<line_length;i++)
								game_map[i+x][y][z].maze=WALL;
						}
						num--; 
					}
				}
			}
				int pos_id(int x,int y,int z){//������
					return x+(y-1)*length+(z-1)*length*width;
				}
				int pos_id(position_3D pos){//������
					return pos.x+(pos.y-1)*length+(pos.z-1)*length*width;
				}
			void connect_room(int l=length,int w=width,int h=height){
				//����draft_line()���ɵķ��� 
				init_dsu(l*w*h);
				for(int z=1;z<=h;z++)
					for(int y=2;y<width;y++)
						for(int x=2;x<length;x++){
							if(game_map[x][y][z].maze==SPACE){
								if(x<length&&game_map[x+1][y][z].maze==SPACE) unit_dsu(pos_id(x,y,z),pos_id(x+1,y,z));
								if(y<width&&game_map[x][y+1][z].maze==SPACE) unit_dsu(pos_id(x,y,z),pos_id(x,y+1,z));
								//��ͨ 
								if(z>1&&game_map[x][y][z-1].maze==SPACE||z<height&&game_map[x][y][z+1].maze==SPACE)
									divided_walls.push_back((position_3D){x,y,z});//�����������յ� 
							}
							else divided_walls.push_back((position_3D){x,y,z}); 
						}
				while(divided_walls.size()>0){
					int sz=divided_walls.size(),k=RAND(sz-1,0);
					position_3D pos=divided_walls[k];
					swap(divided_walls[k],divided_walls[sz-1]);divided_walls.pop_back();
					MAP &POS=game_map[pos.x][pos.y][pos.z];
					int posid=pos_id(pos);
					if(space_here(pos)){
						position_3D u=pos,v=pos;
						u.z--;v.z++;//��¥����¥ 
						int uid=pos_id(u),vid=pos_id(v);
						bool can_down=u.z>=1&&space_here(u)&&find_dsu(posid)!=find_dsu(uid)
						,can_up=v.z<=height&&space_here(v)&&find_dsu(posid)!=find_dsu(vid);
						bool kind;
						if(can_down&&can_up) kind=RAND_BOOL(50);
						else if(can_down) kind=0;
						else if(can_up) kind=1;
						else continue;
						//����¥�� 
						if(kind==0){
							POS.maze=DOWNSTAIR;
							game_map[u.x][u.y][u.z].maze=UPSTAIR;
							unit_dsu(posid,uid);//��ͨ 
						}
						else{
							POS.maze=UPSTAIR;
							game_map[v.x][v.y][v.z].maze=DOWNSTAIR;
							unit_dsu(posid,vid);//��ͨ 
						}
					}
					else if(wall_here(pos)){
						int id=-1;bool flag=false;//id��¼��һ��λ�ñ�� 
						for(int d=0;d<4;d++){
							position_3D u=dtp3(pos,d,4);
							if(pos_in_area(u.x,u.y,1,1,length,width)&&space_here(u)){
								int uid=pos_id(u);
								if(id==-1) id=uid;
								else if(find_dsu(id)!=find_dsu(uid)){//����ͨ��ͬ����
								//ֱ�����ϣ���������ǽ 
									unit_dsu(id,uid);//��ͨ 
									id=uid;
									flag=true;
								}
							}
						}
						if(flag){//��ն���� 
							POS.maze=SPACE;//�ڵ�ǽ 
							unit_dsu(posid,id);//��ͨ
						}
					}
				}
			}
			void print_maze(){
				return;
				gotoxy();
				for(int z=1;z<=height;z++){//����ӡ��Ѩ�� 
					gotoxy();
					for(int y=1;y<=width;y++){
						for(int x=1;x<=length;x++){
							position_3D u;
							u.x=x;u.y=y;u.z=z;
							if(wall_here(u)){
								set_RGBcolor(-100,360,0,360);
								cout<<"ǽ";
							}
							else if(nest_here(u)){
								set_RGBcolor(0,360,0,0);
								cout<<"��";
							}
							else if(upstair_here(u)){
								set_RGBcolor(-20,360,0,360);
								cout<<"��";
							}
							else if(downstair_here(u)){
								set_RGBcolor(-50,360,0,360);
								cout<<"��";
							}
							else{
								set_RGBcolor(0,360,0,360);
								cout<<"  ";
							}
						}
						cout<<endl;
					}
					SLEEP(5*1000);
					system("cls");
				}
			}
		void rand_maze(int l=length,int w=width,int h=height){
			/*��ֵķ��仮�ַ�*/
			make_hollow(false);//ȫ���ڿ� 
			draft_line(l*w/100,min(5,min(l,w)),min(l,w));//����������������ɷ��� 
			print_maze();//
			connect_room();//�������ѷ��������� 
			print_maze();//
			fill_wide_path(3);
			nest_maze(2,10,20);
			mark_maze();//
			print_maze();
			/*�Ҹ㷨 
			������������CS�ĵ�ͼ 
			int p=80;
			while(p>0){
				fill_dead_ends(2,p,length,width,1,height);
				make_hollow();
				fill_wide_path(p);
				p-=20;
				print_maze();
			}*/ 
			/*
			double x=RAND_DOUBLE(3,2);//��Сϵ�� 
			if(l>10&&w>10){//��С���� 
				l/=x;
				w/=x;
			}
			else x=1;
			*/
			/*��Сϵ����2 BUG 
			rand_basic(RAND(l-1,2),RAND(w-1,2),RAND(h,1),1,5,10,l,w);//������С�������ɵ�ͼ��������Ѩ 
			print_maze();
			enlarge_maze(l,w);//�Ŵ� 
			fill_wide_path(50);//��С��Ѩ���Ŀ�· 
			make_hollow();//�ڿյ�������ǽ 
			mark_maze();//����� 
			print_maze();
			*/
			/*��Сϵ����1 
			
			rand_basic(RAND(l-1,2),RAND(w-1,2),RAND(h,1),1,0,0,l,w);//������С�������ɵ�ͼ�������ɳ�Ѩ 
			//gotoxy(100,0);	
			//set_RGBcolor(-100,360,0,360);
			//cout<<"l="<<l<<" w="<<w<<endl;
			//print_maze();
			enlarge_maze(l,w);
			make_hollow();
			fill_wide_path(5);
			nest_maze(2,10,20);
			mark_maze();
			print_maze();
			*/
			/*�ɷ��� 
			rand_basic(RAND(l-1,2),RAND(w-1,2),RAND(h,1),1,5,10);
			//����������Щ�����Ĳ��������ɲ�ͬ���Թ�
			fill_dead_ends(1,RAND_ALTO(cnt_SPACE,0,RAND(40,20)),length,width,1,height);
			fill_dead_ends(2,85,length,width,height+1,height*2);
			make_room(100,5,6,2);
			mark_maze();
			//print_maze();*/
		}
			void make_exits(int l=length,int w=width,int h=height){//�������еĳ���
				int exit_nums=RAND_ALTO(max(max(l,w)*height/10,1),1,1)+1;//��Ϸ��ͼ�г��ڵ���������֤������һ���� 
				RAND_EXIT_AROUND_GAME_MAP(exit_nums,l,w,h);
			}
				void mark_exit(int x,int y,int z){//���һ������ 
					Q.push((position_3D){x,y,z});
					vst[x][y][z]=1;
					dis_to_exit[x][y][z]=0;
					//cout<<x<<" "<<y<<" "<<z<<"\n"; 
				}
			void make_exit_sign(int a,int b,int l=length,int w=width,int h=height){//���ɳ��ڵı���->]����ͷ��char(24~27)��
				memset(vst,0,sizeof(vst));
				memset(dis_to_exit,-1,sizeof(dis_to_exit));
				//����ȫ����ʼ��Ϊ-1�� 
				while(!Q.empty()) Q.pop();
				for(int z=1;z<=height*2;z++){
					for(int x=2;x<=length-1;x++)//ö�����±�Ե
						if(game_map[x][1][z].maze==EXIT) mark_exit(x,1,z);
						else if(game_map[x][width][z].maze==EXIT) mark_exit(x,width,z);
					for(int y=2;y<=width-1;y++)//ö�����ұ�Ե 
						if(game_map[1][y][z].maze==EXIT) mark_exit(1,y,z);
						else if(game_map[length][y][z].maze==EXIT) mark_exit(length,y,z);
					//���ϲ����г��� 
				}
				//make_exits��make_exit_sign�и 
				while(!Q.empty()){//BFS 
					position_3D u=Q.front();Q.pop();
					for(int i=0;i<4;i++){
						position_3D v=dtp3(u,i,4);
						if(pos_in_area2(v.x,v.y,1,1,l,w,2)){
							if(!vst[v.x][v.y][v.z]&&game_map[v.x][v.y][v.z].maze!=WALL){
								vst[v.x][v.y][v.z]=1;
								dis_to_exit[v.x][v.y][v.z]=dis_to_exit[u.x][u.y][u.z]+1;
								Q.push(v);
								if(v.z<=height&&space_here(v)&&empty_here(v) 
								&&count_around_pos(v,4,space_here)>=3
								&&(pos_in_room[v.x][v.y][v.z]?RAND_BOOL(a):RAND_BOOL(b))
								){
									exit_sign &EXIT_SIGN=game_map[v.x][v.y][v.z].things.exit_signs;
									EXIT_SIGN.exist=1;
									EXIT_SIGN.dir=turn(i,TURN_BACK);
								}
								if(game_map[v.x][v.y][v.z].maze==UPSTAIR) v.z++;
								else if(game_map[v.x][v.y][v.z].maze==DOWNSTAIR) v.z--;
								else if(game_map[v.x][v.y][v.z].things.nst.exist) v=game_map[v.x][v.y][v.z].things.nst.to;
								if(!vst[v.x][v.y][v.z]&&u.z!=v.z){//�����¥�ݻ��߳�Ѩ�� 
									vst[v.x][v.y][v.z]=1;
									dis_to_exit[v.x][v.y][v.z]=dis_to_exit[u.x][u.y][u.z]+1;
									Q.push(v);
								}
							}
						}
					}
				}
			}
		void make_exit(){
			//��������Թ�������ʩ������Ϻ󣡣��� 
			if(game_map_from==RANDOM) make_exits(); 
			//�ļ�������ʱ�ر���Щ 
			make_exit_sign(4,8);
		}
	void make_map(){
		logMessage("make_map");
		if(game_map_from==RANDOM) rand_maze();
		//�ļ�������ʱ�ر���Щ 
		make_exit();
	}
		void player::init(){
			pos=RAND_PLAYER_IN_GAME_MAP();
			game_map[pos.x][pos.y][pos.z].player_enemy=PLAYER;
			d1=d2=0;color=0;flash_word="";
			angle=lsta=270;//��ǰ�ķ���� 
			alc=0;
			w.speed=0;w.vt();
			mpos=pos000;
			vts.init();
			//vlc.wait_time=1;vlc.ts();//wait_time����speed 
			vlc.speed=100;vlc.vt();//speed����wait_time 
			scr.init();
			items.init();
			spe.init();
			move=true;
			action_kind=RUN; 
			lst_ud=lst_enter=false;
			grid=-INF;
		}
			void update_pos_mx_dis(position_3D u){//ͳ�Ƶ���Ҳ�ͬ�����λ�ã�������Զ����
				int x=u.x,y=u.y,z=u.z;
				if(dis_to_player[x][y][z]>0&&!wall_here(u)){
					pos_dis_to_player_door[dis_to_player[x][y][z]].push_back(u);
					pos_dis_to_player_key[dis_to_player[x][y][z]].push_back(u);
				}
				mx_dis_to_player=max(mx_dis_to_player,dis_to_player[x][y][z]); 
			}
		void calculate_dis_to_player(int l=length,int w=width,int h=height){
			while(!Q.empty()) Q.pop();
			memset(vst,0,sizeof(vst));
			memset(dis_to_player,-1,sizeof(dis_to_player));
			//��ʼ��Ϊ-1��
			Q.push(player1.pos);
			vst[player1.pos.x][player1.pos.y][player1.pos.z]=1;
			dis_to_player[player1.pos.x][player1.pos.y][player1.pos.z]=0;
			while(!Q.empty()){//BFS 
				position_3D u=Q.front();Q.pop();
				for(int i=0;i<4;i++){
					position_3D v=dtp3(u,i,4);
					MAP &NPOS=game_map[v.x][v.y][v.z];
					if(pos_in_area2(v.x,v.y,1,1,l,w,2)){
						if(!vst[v.x][v.y][v.z]&&NPOS.maze!=WALL){
							vst[v.x][v.y][v.z]=1;
							dis_to_player[v.x][v.y][v.z]=dis_to_player[u.x][u.y][u.z]+1;
							update_pos_mx_dis(v);
							Q.push(v);
							if(NPOS.maze==UPSTAIR) v.z++;
							else if(NPOS.maze==DOWNSTAIR) v.z--;
							else if(NPOS.things.nst.exist) v=NPOS.things.nst.to;
							if(!vst[v.x][v.y][v.z]&&u.z!=v.z){//�����¥�ݿ������� 
								vst[v.x][v.y][v.z]=1;
								dis_to_player[v.x][v.y][v.z]=dis_to_player[u.x][u.y][u.z]+1;
								update_pos_mx_dis(v);
								Q.push(v);
							}
						}
					}
				}
			}
		}
	void make_player(){
		logMessage("make_player"); 
		player1.init();
		calculate_dis_to_player();
	}
			void bug::init(position_3D u,double speed){
				pos=u;d=0;vlc.speed=speed;vlc.vt();
				lfin.init(5);//�������bug_move_awayҲҪ��
				lst_ud=enter_nest=-INF;change_pos=update=false;
			}
			void bug_nest::init(position_3D u){
				pos=u;
				lfin.init(3);
			}
			void pos_make_bug(position_3D u,double speed,bool upd){//��ָ��λ�����ɳ��ӣ�Ҫ�ȼ���λ�ú����ԣ� 
				//upd:�Ƿ������и��� 
				MAP &POS=game_map[u.x][u.y][u.z];
				bug bg;//���ɳ���
				bg.init(u,speed);
				bugs.push_back(bg);
				int id=int(bugs.size())-1;
				POS.player_enemy=BUG;POS.emy.id=id;
				/*�ݲ�������У�����BUG */
				if(upd){
					Qbug.push(id);
					bugs[id].update=true;//������bg.update�� 
				}
			}
		void make_bug(int a,int b,int c,int l=length,int w=width,int h=height){//���ɳ��� 
			for(int z=1;z<=height+h;z++)
				for(int y=1;y<=w;y++)
					for(int x=1;x<=l;x++){
						position_3D u;
						u.x=x;u.y=y;u.z=z;
						if(space_here(u)&&nobody_here(u)&&empty_here(u)&&dis_to_player[x][y][z]>=10//���������10������ 
						&&dis_to_exit[x][y][z]>0&&RAND_BOOL(a+b/dis_to_exit[x][y][z]*(100-c-a)/b+(z>height?c:0))){ 
							pos_make_bug(u,RAND(4,3),0);
						}
					}
		}
			void spider::init(position_3D u,bool k){
				pos=bir=u;prey=pos000;d=0;vlc.speed=RAND(5,4);vlc.vt();
				lfin.init(20);//�������spider_move_awayҲҪ��
				kind=k;
				change_pos=update=false;
			}
		void make_spider(int a,int b,int l=length,int w=width,int h=height){//����֩�� 
			for(int z=1;z<=height;z++)
				for(int y=1;y<=w;y++)
					for(int x=1;x<=l;x++){
						position_3D u;
						u.x=x;u.y=y;u.z=z;
						MAP &POS=game_map[u.x][u.y][u.z];
						int k=RAND_BOOL(b);//��ǰ������ 
						//if(count_around_pos(u,8,space_here)==8&&count_around_pos(u,8,noitem_here)==8) k=1;
						//else k=0;
						//k=1;
						if(space_here(u)&&nobody_here(u)&&noitem_here(u)&&dis_to_player[x][y][z]>=10//���������10������ 
						&&(k?count_around_pos(u,8,space_here)==8&&count_around_pos(u,8,noitem_here)==8:1)
						&&RAND_BOOL(a)&&RAND_BOOL(10)){
							spider sr;//����֩��
							sr.init(u,k);
							spiders.push_back(sr);
							int id=int(spiders.size())-1;
							POS.player_enemy=SPIDER;POS.emy.id=id;
							for(int i=0;i<8;i++){ 
								position_3D v=dtp3(u,i,8);
								MAP &VPOS=game_map[v.x][v.y][v.z];
								spider_leg &slg=VPOS.things.slg;
								slg.num++;slg.id=id;//��֫�ڵ�ͼ�ϱ��һ��
							}
							if(k==0) POS.things.snt.endurance=100;//A��֩�����������֩���� 
						}
					}
		}
			void ghost::init(position_3D u,int att,int def){
				//def=0;//����������� 
				pos=u;goal=pos000;d=0;vlc.speed=RAND_DOUBLE(3.5,1.5);vlc.vt();
				lfin.init(30);//�������ghost_move_awayҲҪ�� 
				spat.init(att,def);
				switch(spat.attack){
					case THROUGH:
						spat.thr.time=RAND(10000,1);
						break;
					case DISAPP:
						spat.disa.use=true;//һ��ʼ���� 
						spat.disa.time=RAND(20000,10000);
						spat.disa.maxt=RAND(10000,5000);
						spat.disa.kind=RAND(2,1);
						break;
					case INSTANT:
						spat.ins.p=RAND(60,30); 
						spat.ins.dis=RAND(7,3);
						break;
				}
				switch(spat.defense){
					case EVADE:
						spat.eva.k=RAND(100,50);
						break;
					case ROCK:
						spat.rck.k=RAND(50,1)*0.01;
						break;
					case SHIELD://=����2�������� 
						spat.rck.k=RAND(50,30)*0.01;
						spat.eva.k=RAND(75,50);
						break;
				}
				change_pos=update=false;
				attack_time=RAND_DOUBLE(0.7,0.5);
				spe.init();//����Ч����� 
			}
		void make_ghost(int a,int b,int l=length,int w=width,int h=height){//���ɹ� 
			for(int z=1;z<=height+h;z++)
				for(int y=1;y<=w;y++)
					for(int x=1;x<=l;x++){
						position_3D u;
						u.x=x;u.y=y;u.z=z;
						MAP &POS=game_map[u.x][u.y][u.z];
						if(space_here(u)&&nobody_here(u)&&empty_here(u)&&dis_to_player[x][y][z]>=20//���������20������ 
						&&RAND_BOOL(10)&&mx_dis_to_player>0&&RAND_BOOL(a+dis_to_player[x][y][z]*(b-a+1)/mx_dis_to_player)){ 
							ghost gt;//���ɹ�
							gt.init(u,RAND(RAND(RAND(INSTANT,0),0),0),RAND(RAND(ROCK,0),0));
							//gt.init(u,VAMPIRE,0);
							special_attribute &spat=gt.spat;
							int id=int(ghosts.size());
							
							if(/*(spat.attack==THROUGH||spat.attack==DISAPP||spat.attack==INSTANT)
							&&*/MHT_DIST_p3(u,player1.pos)<=50){//��ǰ��ʼ���� 
								gt.update=true;
								Qghost.push(id);
							}
							ghosts.push_back(gt);
							POS.player_enemy=GHOST;POS.emy.id=id;
						}
					}
		}
	void make_enemy(){
		logMessage("make_enemy"); 
		make_bug(4,30,40);
		make_spider(5,80);
		make_ghost(20,25);
	}
			void farther_more_doors(int a,int b,int c,int d){//ԽԶԽ��
			logMessage("farther_more_doors"); 
			//a:ĳ�����������ŵĸ��� [b,c]:�ӽ���Զ�ŵ���������ռ�˾���������������ռ�� d:���ŵ��ŵĸ��� 
				for(int i=10;i<=mx_dis_to_player;i++)//ö�ٲ�ͬ�ľ��� 
					if(RAND_BOOL(a)){
						int sz=pos_dis_to_player_door[i].size(),door_num=RAND_ALTO(sz>0?sz:1,1,b+i*(c-b)/mx_dis_to_player);
						//��ǰ��������Ͽ��Է��ŵ�λ���������������ȡλ�ã�����Ҫ�������� 
						logMessage("sz,door_num"); 
						while(sz>0&&door_num>0){
							int k=RAND(sz-1,0);
							position_3D u=pos_dis_to_player_door[i][k];
							swap(pos_dis_to_player_door[i][k],pos_dis_to_player_door[i][sz-1]);
							sz--;
							logMessage("door pos?"); 
							//����ҷ��ŵ�λ��
							MAP &DPOS=game_map[u.x][u.y][u.z]; 
							thing &THING=DPOS.things;
							key_door &DRS=THING.kdr;
							bool kdr_place=space_here(u)&&empty_here(u)&&!count_around_pos(u,4,key_door_here);
							logMessage("kdr_place"); 
							spider_leg_here(u);
							logMessage("kdr_place spider_leg_here?"); 
							player_here(u);
							logMessage("kdr_place player_here?"); 
							//ghost_here(u);
							logMessage("kdr_place ghost_here?"); 
							spider_body_here(u);
							logMessage("kdr_place spider_body_here?"); 
							bug_here(u);
							logMessage("kdr_place bug_here?"); 
							bool kdr_being=0;
							kdr_being=nobody_here(u)&&count_around_pos(u,4,player_here)==0;//��Χû����� 
							logMessage("kdr_being"); 
							/*
							try{
							}
							catch (const std::exception& e){
								string message = e.what();
								logMessage("�����쳣: "+message);
								continue;
    						}*/
							if(u.z<=height
							&&kdr_place
							&&kdr_being
							&&useful_door(position_3Dto2D(u),u.z,10)){
							//�յء�������ã����ŵ�һ�ߵ���һ�ߵ�·�̲���̫���� 
								int door_kind=RAND(4,1);//���ѡ������
								DRS.exist=true;
								DRS.kind=door_kind-1+DOOR1;
								DRS.light_through=RAND_BOOL(80);//���ѡ���ŵ�͸����
								DRS.state=RAND_BOOL(d)*2;//0/2
								door_num--;
								logMessage("door here"); 
							}
							logMessage("next door"); 
						}
						logMessage("next dis"); 
					}
			}
			void doors_around_rooms(int a,int b,int l=length,int w=width,int h=height){//�������ڷ�����Χ 
			//b:���ŵ��ŵĸ��� 
				logMessage("doors_around_rooms"); 
				for(int z=1;z<=h;z++)
					for(int y=2;y<w;y++)
						for(int x=2;x<l;x++){
							position_3D u;
							u.x=x;u.y=y;u.z=z;
							MAP &POS=game_map[u.x][u.y][u.z]; 
							thing &THING=POS.things;
							key_door &DRS=THING.kdr;
							if(RAND_BOOL(a)
							&&!pos_in_room[u.x][u.y][u.z]
							&&space_here(u)&&nobody_here(u)&&empty_here(u)
							&&count_around_pos(u,4,wall_here)<=2&&!count_around_pos(u,4,key_door_here)
							&&count_around_pos(u,4,player_here)==0){//��Χû����� 
							//���ڷ�����յأ���Χû���š�������2��ǽ 
								bool flag=0;
								for(int i=0;i<4;i++){
									position_3D v=dtp3(u,i,4);
									if(pos_in_room[v.x][v.y][v.z]){
										flag=1;
										break;
									}
								}
								if(!flag) continue;
								int door_kind=RAND(4,1);//���ѡ������
								DRS.exist=true;
								DRS.kind=door_kind-1+DOOR1;
								DRS.light_through=RAND_BOOL(20);//���ѡ���ŵ�͸���� 
								DRS.state=RAND_BOOL(b)*2;//0/2
							}
						}
			}
		void make_key_door(){
			logMessage("make_key_door"); 
			farther_more_doors(5,10,25,0);
			doors_around_rooms(100,0);
		}
		void make_hiden_door(int a,int l=length,int w=width,int h=height){
			logMessage("make_hiden_door"); 
			return;//�Ȳ����ã��е㷳 
			for(int z=1;z<=h;z++)
				for(int y=2;y<w;y++)
					for(int x=2;x<l;x++){
						position_3D u;
						u.x=x;u.y=y;u.z=z;
						MAP &POS=game_map[u.x][u.y][u.z];
						if(RAND_BOOL(a)
						&&space_here(u)&&nobody_here(u)&&empty_here(u)
						&&divided_part(u)>=2&&count_around_pos(u,4,nobody_here)==4){
							hiden_door &HDR=POS.things.hdr;
							HDR.exist=true;
							HDR.kind=1;//RAND(2,1);
						}
					}
		}
			void farther_less_keys(int a,int b,int c){//ԽԶԽ�� 
				for(int i=1;i<=mx_dis_to_player;i++)
					if(RAND_BOOL(a)){
						int sz=pos_dis_to_player_key[i].size(),key_num=RAND_ALTO(sz>0?sz:1,1,b-i*(b-c)/mx_dis_to_player);
						//��ǰ��������Ͽ��Է�Կ�׵�λ���������������ȡλ�ã�����Ҫ��Կ�����������������ɲ��ϼ�С�� 
						while(sz&&key_num){
							int k=RAND(sz-1,0);
							position_3D u=pos_dis_to_player_key[i][k];
							swap(pos_dis_to_player_key[i][k],pos_dis_to_player_key[i][sz-1]);
							//sz--;λ�ÿ����ظ��� 
							//����ҷ�Կ�׵�λ��
							MAP &KPOS=game_map[u.x][u.y][u.z]; 
							thing &KTHING=KPOS.things;
							object obj;obj.type=KEY;
							if(u.z<=height&&space_here(u)&&KPOS.things.noitem()){
								int key_kind=RAND(3,0);//���ѡԿ������
								KTHING.key=key_kind+KEY1;
								obj.key=key_kind+KEY1;
								new_object(obj,KTHING.fir);
								key_num--;
							} 
						}
					}
			}
			void keys_in_rooms(int a,int l=length,int w=width,int h=height){//Կ�������ڷ�������
				vector<position_3D> v;
				for(int z=1;z<=h;z++)
					for(int y=1;y<=w;y++)
						for(int x=1;x<=l;x++){
							position_3D u;
							u.x=x;u.y=y;u.z=z;
							MAP &KPOS=game_map[u.x][u.y][u.z]; 
							if(pos_in_room[x][y][z]&&space_here(u)&&KPOS.things.noitem())
								v.push_back(u);
						}
				for(int i=0;i<int(v.size());i++){
					position_3D u=v[i];
					MAP &KPOS=game_map[u.x][u.y][u.z]; 
					thing &KTHING=KPOS.things;
					object obj;obj.type=KEY;
					if(RAND_BOOL(a)){
						int key_kind=RAND(3,0);//���ѡԿ������
						obj.key=KTHING.key=key_kind+KEY1;
						new_object(obj,KTHING.fir);
						new_object(obj,KTHING.fir);
						//һ���Է�2�� 
					} 
				}
			}
			void keys_to_doors(int a,int b,int l=length,int w=width){//ÿ��Կ�׶���Ӧһ���� 
				vector<position_3D> vspace;//�ѷ��ʡ�δ��Կ�׵Ŀյ�	
				vector<position_3D> vdoor[4];//�ѷ��ʡ�δ�Ŷ�ӦԿ�׵��ţ����ֱַ��¼��
				while(!Q.empty()) Q.pop();
				memset(vst,0,sizeof(vst));
				Q.push(player1.pos);
				vst[player1.pos.x][player1.pos.y][player1.pos.z]=1;
				while(1){
					while(!Q.empty()){//BFS 
						position_3D u=Q.front();Q.pop();
						for(int i=0;i<4;i++){
							position_3D v=dtp3(u,i,4);
							if(pos_in_area2(v.x,v.y,1,1,l,w,2)){
								if(!vst[v.x][v.y][v.z]
								&&!wall_here(v)&&!door_here(v)){//����ǽ�������ţ���Ȼ��������㣩 
									vst[v.x][v.y][v.z]=1;
									Q.push(v);
									if(space_here(v)&&noitem_here(v)) vspace.push_back(v);//�ѷ��ʡ�û����Ʒ�Ŀյ�
									else if(game_map[v.x][v.y][v.z].maze==UPSTAIR) v.z++;
									else if(game_map[v.x][v.y][v.z].maze==DOWNSTAIR) v.z--;
									else if(game_map[v.x][v.y][v.z].things.nst.exist) v=game_map[v.x][v.y][v.z].things.nst.to;
									if(u.z!=v.z&&!vst[v.x][v.y][v.z]){//�����¥�ݿ�������/��Ѩ���Խ������Ҳ����ߵ�ȥ���ĵط� 
										vst[v.x][v.y][v.z]=1;
										Q.push(v);
									}
								}
								else if(!vst[v.x][v.y][v.z]&&door_here(v)){
									vst[v.x][v.y][v.z]=1;
									vdoor[game_map[v.x][v.y][v.z].things.kdr.kind-DOOR1].push_back(v);
									//�ѷ��ʡ�δ�Ŷ�ӦԿ�׵���
								}
							}
						}
					}
					vector<int> vkind;//����ѡ����ŵ����� 
					for(int i=0;i<4;i++)
						if(vdoor[i].size()&&vspace.size()>=vdoor[i].size()) vkind.push_back(i);
					if(vkind.size()){//�п���ѡ����ŵ�����  
						int door_kind=vkind[RAND(vkind.size()-1,0)];//���ѡ�ŵ�����
						for(int i=0;i<int(vdoor[door_kind].size());i++){
							position_3D dr=vdoor[door_kind][i];//��ǰ�ŵ�Կ�׶�Ӧ���� 
							Q.push(dr);
							//�ѷ��˶�ӦԿ�׵��š��򿪡�����Ϊ�´�ѭ������� 
							int k=RAND(vspace.size()-1,0);
							position_3D u=vspace[k];
							//ȡ��Ҫ��Կ�׵Ŀյ�
							MAP &KPOS=game_map[u.x][u.y][u.z];
							thing &KTHING=KPOS.things;
							object obj;obj.type=KEY;
							if(1){
							//Ŀǰ�����Ŷ���֤��Կ�� 
							//dis_to_player[dr.x][dr.y][dr.z]>0?RAND_BOOL(a*max(1,b/dis_to_player[dr.x][dr.y][dr.z])):RAND_BOOL(a)
								int key_kind=door_kind;
								obj.key=KTHING.key=key_kind+KEY1;
								new_object(obj,KTHING.fir);
								//�յز�ɾ�������Զѵ� 
								//swap(vspace[k],vspace[vspace.size()-1]);vspace.pop_back();//����Կ�ײŰ�����յ�ɾ�� 
							}
							//����Կ�� 
						}
						vdoor[door_kind].clear();//��������� 
					}
					else break;//ѭ����û��δ�Ŷ�ӦԿ�׵��ţ�����һ�Σ���Ϊ�ʼû�ţ� 
				}
			}
		void make_key(){
			logMessage("make_key"); 
			//farther_less_keys(20,15,5); 
			//keys_in_rooms(10);//10
			keys_to_doors(100,0); 
		}
		void make_mirror(position_3D u,int a,int l=length,int w=width,int h=height){
			logMessage("make_mirror"); 
			MAP &POS=game_map[u.x][u.y][u.z];
			thing &THING=POS.things; 
			if(RAND_BOOL(a)
			&&space_here(u)&&no_mirror_around(u)&&nobody_here(u)&&empty_here(u)&&!THING.exit_signs.exist){//�������ڳ��ڱ����� 
				int mirror_dir=RAND_MIRROR_DIRECTION(u);
				if(mirror_dir==-1) return;
				int cw=count_around_pos(u,4,wall_here),mirror_side;
				if(cw==2) mirror_side=1;
				else if(!cw) mirror_side=2;
				else mirror_side=RAND(2,1);
				mirror &MIRROR=game_map[u.x][u.y][u.z].things.mirrors;
				MIRROR.exist=1;MIRROR.side=mirror_side;
				if(mirror_side==1) MIRROR.dir=mirror_dir;
				else MIRROR.dir=mirror_dir%2;
				MIRROR.endurance=100;
			}
		}
		void make_window(position_3D u,int a,int l=length,int w=width,int h=height){
			logMessage("make_window"); 
			MAP &POS=game_map[u.x][u.y][u.z];
			if(RAND_BOOL(a+count_around_pos(u,4,window_here)*15)&&pos_in_area2(u.x,u.y,1,1,length,width,2)
			//+(u.x==length||u.y==width?100:0)��Եǽ�򴰻� 
			&&wall_here(u)&&nobody_here(u)&&empty_here(u)&&divided_part(u)>=2
			//&&!game_map[u.x-1][u.y-1][u.z].things.windows.exist
			&&!count_around_pos(u,4,player_here)){
				window &WDN=POS.things.windows;
				WDN.exist=true;
				WDN.endurance=100;
				WDN.state=RAND(1,0);
			}
		}
		void make_curtain(position_3D u,int a,int b,int l=length,int w=width,int h=height){
			logMessage("make_curtain"); 
			MAP &POS=game_map[u.x][u.y][u.z];
			if(RAND_BOOL(a+count_around_pos(u,4,curtain_here)*b)
			&&space_here(u)&&nobody_here(u)&&empty_here(u)&&count_around_pos(u,4,wall_here)<=2){
				curtain &CRT=POS.things.crt;
				CRT.exist=true;
				CRT.endurance=100;
			}
		}
				int pos_to_brightness(position_3D u,position_3D v,int p){//��uΪ��Դ����v�Ĺ���ǿ����������ɢ�⣩ 
					if(u.x==v.x&&u.y==v.y) return p;//��ֹ/0��
					return p/MHT_DIST(u.x,u.y,v.x,v.y);
				}
				int pos_to_brightness2(position_3D u,position_3D v,int p,int dir,int angle){//��uΪ��Դ����v�Ĺ���ǿ���������۹�ƣ�
					//dir��d�������0~359 
					if(u.x==v.x&&u.y==v.y) return p;
					int d=calc_angle(u,v),tmp=(dir-d+360)%360,d2=min(tmp,360-tmp);//�ǶȲ� 
					if(d2>angle||angle==0) return 0;
					return p/sqrt(MHT_DIST(u.x,u.y,v.x,v.y))*cos(d2*(90.0/angle)/180.0*PI);
					//  ����   �������ӣ���ƽ����СӰ�죩      ����˥�����ӣ�d2=0->1,d2=angle->0�� 
				}
			void update_light_brightness(position_3D u,bool scr=1){//���¼�����u��Ϊ��Դ�Ĺ��շ�Χ�����£���ɢ�⣩ 
				//scr���Ƿ���µ���Ļ 
				MAP &POS=game_map[u.x][u.y][u.z];
				thing &THING=POS.things; 
				light &LGT=THING.lgt;
				LGT.update=false;//��ֹ�ظ����� 
				int id=LGT.id;
				if(id<0) return;
				map<position_3D,bool> mp;
				for(int i=0;i<light_area[id].size();i++){//����ϴε��������� 
					position_3D v=light_area[id][i];
					MAP &NPOS=game_map[v.x][v.y][v.z];
					NPOS.brightness-=pos_to_brightness(u,v,LGT.p);//����
					mp[v]=1;
					if(NPOS.ist.player==lst_see_time){//�ϴ������ȫ��������� (!LGT.state&&�ƹ���?)
						game_flag["���ո���"]=true;
						pos_change.insert(v);
					} 
				}
				light_area[id].clear();
				if(!LGT.state) return;//�ƹ��� 
				vector<PII> v;vector<position_3D> ret;
				for(int i=0;i<4;i++) v.push_back(MP(0,359));
				vision_init(1,v,ret,pos000);
				calculate_vision2(u,2,ret,INF,0);//�����µ����䷶Χ
				for(int i=0;i<ret.size();i++){
					position_3D v=ret[i];
					MAP &NPOS=game_map[v.x][v.y][v.z];
					light_area[id].push_back(v);//���´˵����䷶Χ 
					NPOS.brightness+=pos_to_brightness(u,v,LGT.p);//���� 
					if(scr&&!mp[v]&&NPOS.ist.player==lst_see_time){//���µ���Ļ
						game_flag["���ո���"]=true;
						pos_change.insert(v);
					}
				}
			}
		void make_light(position_3D u,int a,int b,int c,int &cnt,int l=length,int w=width,int h=height){//���ɵ�
			logMessage("make_light"); 
			MAP &POS=game_map[u.x][u.y][u.z];
			thing &THING=POS.things; 
			light &LGT=THING.lgt;
			int p=RAND(40,20);
			bool st=RAND_BOOL(c);//�и����ǰ��� 
			if((pos_in_room[u.x][u.y][u.z]?RAND_BOOL(a):RAND_BOOL(b))
			&&space_here(u)&&nobody_here(u)&&empty_here(u)&&!THING.exit_signs.exist&&!THING.nst.exist
			&&POS.brightness+p<=0){//��ֹ̫�� 
				LGT.exist=true;
				LGT.p=p;
				LGT.id=cnt++;
				LGT.update=true;
				LGT.state=st;
				update_light_brightness(u,0);//����ʾ����Ļ 
			}
		}
		void make_fog(position_3D u,int a,int l=length,int w=width,int h=height){//��������
			logMessage("make_fog"); 
			if(RAND_BOOL(a)&&(space_here(u)||stair_here(u))&&nobody_here(u)&&empty_here(u)
			//&&(u.z<=height?count_around_pos(u,4,space_here)+count_around_pos(u,4,stair_here):count_around_pos(u,4,bug_nest_here))==0
			){
				fog &FOGS=game_map[u.x][u.y][u.z].things.fogs;
				for(int i=0;i<3;i++) FOGS.absorbance[i]=RAND_BOOL(50)*7000+3000;//��ʼ��������������ɢ
				//�����ɫ��RGB��ԭɫ�����ɫ��8�֣�������ɫ��absorbance�ϵ� 
				//absorbance[x]>0��ʾx��ɫ������ 
				//FOGS.col=code_to_RGB(0,120*RAND(2,0),0);//��/��/���� 
				FOGS.update=true; 
				pos_fog.push(u);//������� 
			}
		}
		void make_mvb(position_3D u,int a,int b,int c,int l=length,int w=width,int h=height){//���ɿ��ƶ���Ʒ
			logMessage("make_mvb"); 
			MAP &POS=game_map[u.x][u.y][u.z];
			thing &THING=POS.things; 
			movable &mvb=POS.things.mvb;
			int k=RAND(BALL,BOX);//BOX;//
			if(ghost_here(u)||bug_here(u)) k=BOX;
			logMessage("ghost_herebug_here"); 
			bool rAnD=RAND_BOOL(k==BOX&&ghost_here(u)?a:(pos_in_room[u.x][u.y][u.z]?b:c));//�ڷ���/�й��λ�����Ӹ߸��� 
			logMessage("rAnD"); 
			bool plh=player_here(u);
			logMessage("plh"); 
			bool sph=spider_here(u);
			logMessage("sph"); 
			bool noh=nobody_here(u);
			logMessage("noh"); 
			bool emh=empty_here(u);
			logMessage("emh"); 
			bool being=(k==BOX?!plh&&!sph:noh&&emh);//����������г���ҡ�֩����������� 
			logMessage("being"); 
			if(rAnD&&being&&space_here(u)&&dis_to_player[u.x][u.y][u.z]>=15){
				logMessage("mvb.exist=true;"); 
				mvb.exist=true;
				mvb.kind=k;
				POS.fcmv.lock=false;
			}
		}
		void make_dart(position_3D u,int a,int b,int l=length,int w=width,int h=height){//���ɵ��ϵĻ�����
			logMessage("make_dart"); 
			dart &DRT=game_map[u.x][u.y][u.z].things.drt;
			if((RAND_BOOL(a)&&box_here(u)||RAND_BOOL(b)&&!box_here(u)&&empty_here(u))&&space_here(u)&&nobody_here(u)){
				DRT.num[0]++;
			}
		}
		void make_smoke_bomb(position_3D u,int a,int b,int l=length,int w=width,int h=height){//���� 
			logMessage("make_smoke_bomb"); 
			MAP &POS=game_map[u.x][u.y][u.z];
			thing &THING=POS.things; 
			smoke_bomb &SMB=game_map[u.x][u.y][u.z].things.smb;
			if((RAND_BOOL(a)&&box_here(u)||RAND_BOOL(b)&&!box_here(u)&&empty_here(u))&&space_here(u)&&nobody_here(u)){
				object obj;obj.type=SMO; 
				new_object(obj,THING.fir);
			}
		}
		void make_ppt(position_3D u,int a,int b,int l=length,int w=width,int h=height){//���ɿ�ʹ��һ��͸��Ч���ĵ���
			logMessage("make_ppt"); 
			MAP &POS=game_map[u.x][u.y][u.z];
			thing &THING=POS.things; 
			perspective &PPT=game_map[u.x][u.y][u.z].things.ppt;
			if((RAND_BOOL(a)&&box_here(u)||RAND_BOOL(b)&&!box_here(u)&&empty_here(u))&&space_here(u)&&nobody_here(u)){
				/*
				PPT.exist=true;
				PPT.kind=RAND(RAND(1,1),1); //2
				PPT.time=RAND(10,5)*1000;//ms */
				object obj;obj.type=PER; 
				obj.stp.kind=RAND(RAND(1,1),1);//2
				obj.stp.time=RAND(10,5)*1000;//ms
				new_object(obj,THING.fir);
			}
		}
			void pos_make_food(position_3D u,int kind,int effect){
				thing &THING=game_map[u.x][u.y][u.z].things;
				food_pile &FOOD=THING.foods;
				//FOOD.make(kind,effect);
				object obj;obj.type=FOO;
				obj.foods={kind,effect};
				new_object(obj,THING.fir);
			}
		void make_food(position_3D u,int a,int b,int l=length,int w=width,int h=height){
			logMessage("make_food"); 
			if((RAND_BOOL(a)&&box_here(u)||RAND_BOOL(b)&&!box_here(u)&&empty_here(u))&&space_here(u)&&nobody_here(u)){
				int kind=RAND(ADDL,ADDS),effect=log2(RAND(1<<3,1<<1));//8,7,6,5->3;4,3->2;2->1
				pos_make_food(u,kind,effect);
			}
		}
		void make_wpn_energy_edc(position_3D u,int a,int b,int c,int l=length,int w=width,int h=height){//��������������/�;öȻظ�
			logMessage("make_wpn_energy_edc"); 
			weapon_energy_edc &WEE=game_map[u.x][u.y][u.z].things.wee;
			if((RAND_BOOL(a)&&box_here(u)||RAND_BOOL(pos_in_room[u.x][u.y][u.z]?b:c)&&!box_here(u)&&empty_here(u))&&space_here(u)&&nobody_here(u)&&empty_here(u)){
				WEE.exist=true;
				WEE.num=RAND(9,1);
				if(RAND_BOOL(c)) WEE.kind=0;
				else WEE.kind=1;
			}
		}
		void make_weapon(position_3D u,int a,int b,int c,int l=length,int w=width,int h=height){//�������� 
			logMessage("make_weapon"); 
			thing &THING=game_map[u.x][u.y][u.z].things;
			if((RAND_BOOL(a)&&box_here(u)||RAND_BOOL(pos_in_room[u.x][u.y][u.z]?b:c)&&!box_here(u)&&noitem_here(u))
			&&space_here(u)&&nobody_here(u)&&noitem_here(u)){
				object obj;obj.type=RAND(BLA,LAS);//LAS,DAR,SPE,DAG,SWO,BLA
				//obj.type=SPE;
				switch(obj.type){
					case LAS:obj.lsrE=RAND(9,1);break;//����ǹ���� 
					case SPE:obj.sprE=RAND(100,50);break;//��ì�;� 
					case DAG:obj.daggerE=RAND(100,50);break;//ذ���;� 
					case SWO:obj.swordE=RAND(100,50);break;//���;� 
					case BLA:obj.bladeE=RAND(100,50);break;//�����;� 
				}
				new_object(obj,THING.fir);
			}
		}
		void make_TNT(){
		}
		void make_treasure(){
		}
		void make_candle(){
		}
		void make_water(){
		}
		void make_magma(){
		}
	void make_thing(int l=length,int w=width,int h=height){
		logMessage("make_thing"); 
		int cnt_light=0;
		make_key_door();
		if(game_map_from==RANDOM) make_hiden_door(20);
		make_key();
		//print_maze();
		for(int z=1;z<=h;z++)//�������Ķ��� 
			for(int y=1;y<=w;y++)
				for(int x=1;x<=l;x++){
					position_3D u;
					u.x=x;u.y=y;u.z=z;
					//make_mirror(u,10); 
					if(game_map_from==RANDOM) make_window(u,5);
					if(game_map_from==RANDOM) make_curtain(u,2,12);
					make_light(u,15,50,50,cnt_light);
					//make_fog(u,1);//ָ��λ��ȫ������ 
					make_mvb(u,100,15,1);
					//make_dart(u,20,2); 
					make_smoke_bomb(u,20,0);
					make_food(u,80,1);
					//make_wpn_energy_edc(u,20,2,80);
					make_weapon(u,15,2,20);//10,1,15
				}
		//print_maze();
		for(int z=h+1;z<=h*2;z++)//��Ѩ���Ķ��� 
			for(int y=1;y<=w;y++)
				for(int x=1;x<=l;x++){
					position_3D u;
					u.x=x;u.y=y;u.z=z;
					//make_fog(u,1);//��Ѩ��ȫ������ 
					make_mvb(u,3,3,3);
					//make_dart(u,30,0); 
					make_ppt(u,20,1);
					make_smoke_bomb(u,30,5);
					make_food(u,40,5);
					//make_wpn_energy_edc(u,30,11,50);
					make_weapon(u,30,10,50);
				}
		make_TNT();
		make_treasure();
		make_candle();
		make_water();
		make_magma();
	}
	void print_initial_picture(){ 
	    //��ǰҪ���� 
		logMessage("print_initial_picture"); 
		screen_center=position_3Dto2D(player1.pos);
		game_time=lst_see_time=0;
		player_calculate_vision2();
		player_calculate_vision1(player1.d2);
		while(!pos_in_sight.empty()){
			position_3D u=pos_in_sight.front();pos_in_sight.pop();
			print_game_map_pos(u,1);
			position_2D spos=position_3Dtoscr(u);
			pos_lst_sight.push(spos);
		}
		
		formatted_output(1,vital_signs_area,0,0,MMPP(-100,360,0,0),"����ֵ��"+repeat_str("��",player1.vts.lfin.life/10.0)+"           ");
		formatted_output(1,vital_signs_area,50,0,MMPP(-100,360,0,120),"����ֵ��100% ");
		formatted_output(1,vital_signs_area,80,0,MMPP(-100,360,0,360),"����Ч����1.͸��0�㣬����0��");
		formatted_output(1,vital_signs_area,160,0,MMPP(-100,360,0,60),"��ɱ����0");
		
		player1.items.print1();player1.items.print2();player1.items.print3();
		player1.items.wpn_print1();player1.items.wpn_print2();player1.items.wpn_print3();
	}//������������λ������ҲҪ��
void initial(){//��Ϸ��ʼ��
	//��ǰ��Ҫ���� 
	logMessage("initial()",2); 
	ifstream fin;
	if(game_map_from==FILE_MODEL){//�ļ���ȡԤ���ͼ 
		fin.open("map.in",ios::in);
		if(!fin.is_open()){
			cout<<"�ļ�����"<<"\n";
			exit(0);
		}
		fin>>length>>width>>height;
	}
	
	all_assigned();
	
	if(game_map_from==FILE_MODEL){//�ļ���ȡԤ���ͼ 
		for(int z=1;z<=height*2;z++)
			for(int y=1;y<=width;y++)
				for(int x=1;x<=length;x++)
					fin>>game_map[x][y][z].maze;
		fin.close();
	}
	 
	make_map();
	make_player();
	//print_maze();
	make_enemy();
	//print_maze();
	make_thing();
	//print_maze();
	//print_game_map();
	//SLEEP(10000);
	CLEAR();
	print_initial_picture();
}			
	void assigned(){
		logMessage("assigned()",2);
		player1.scr.time_spent=game_time;
		//������ʱ 
		while(!Q.empty()) Q.pop();
		pos_backup.clear();
		for(int i=0;i<4;i++) cnt_visible[i]=360;
		memset(occlusion,0,sizeof(occlusion));
		player1.d1_change=player1.d2_change=player1.move=player1.vts.lfin.change=player1.vts.stg.change
		=player1.ud_change=player1.ak_change=player1.flash=player1.use_weapon=player1.pull_thing
		=player1.enemy_move
		=player1.items.num_change=player1.items.sn_change=player1.items.il_change
		=player1.items.wpn.sw_change=player1.items.wpn.data_change=player1.items.wpn.mode_change
		=player1.items.rmv.dl_change
		=player1.items.flt.change
		=player1.scr.kc.change
		=player1.spe.xry.change
		=player1.spe.wks.change=player1.spe.vtg.change=player1.spe.bds.change=player1.spe.mts.change=player1.spe.cfs.change
		=game_flag["��Ϸ��ͣ/����"]=game_flag["���ո���"]
		=game_flag["���˱���ҹ���"]=game_flag["���ʬ��"]=game_flag["������"]=game_flag["��Ѫ"]=game_flag["����¥����"] 
		=game_flag["���ì�ı�λ��"]=game_flag["�����ڱ仯"]=game_flag["��˿�仯"]=game_flag["��Ʒ��"]
		=game_flag["������"]=game_flag["��"]=game_flag["��"]=game_flag["��noply"]
		=game_flag["����ר��"]
		=false;
	}
	void pause(){
		logMessage("pause",2);
		if(!game_pause) return;
		position_2D scr_mouse=pos_mouse();//������Ļλ�� 
		char getch=_getch();
		if(getch!=PRESS_KEY_ESC){//��Ϸ��ͣ->��Ϸ����
			game_pause=false;
			game_flag["��Ϸ��ͣ/����"]=true;
		}
		else if(KEY_DOWN(VK_LBUTTON)&&!game_flag["��굥��"]){//������
			game_flag["��굥��"]=true;
			if(scr_mouse.x<=20){//��Ϸ���� 
				game_pause=false;
				game_flag["��Ϸ��ͣ/����"]=true;
			}
		}
		else game_flag["��굥��"]=false;
		SLEEP(100);//��ֹ��ε������ͣ��game_time���䣬�޷�ʹ��game_timer�� 
	}
			void player_reduce_blood(double sub,PII from){
				vital_signs &vts=player1.vts;
				life_injury &lfin=vts.lfin;
				if(lfin.life<=0) return;//�Ѿ����˾Ͳ����� 
				score &scr=player1.scr;
				if(sub<=0||sub>0&&lfin.canhurt()) lfin.life-=sub;//�ı�Ѫ��
				player1.flash=true;
				if(sub>=0&&lfin.canhurt()){ 
					lfin.hurt+=sub;//�˺��ۼ� 
					lfin.lst_hurt=sub;
					scr.hurt_times++;//���˴��� 
					lfin.change=2;//��Ѫ 
					if(from!=MP(0,-1)) lfin.last_injury_from=from;
					lfin.last_injury_time=game_time;
					player1.color=2;
					game_timer["���ͼ����˸"]=game_time+100;
				}
				else{
					lfin.recovery-=sub;//��Ѫ�ۼ� 
					lfin.change=1;//��Ѫ 
					player1.color=1;
					game_timer["���ͼ����˸"]=game_time+1000;
				}
				if(lfin.life<=0){//��ֹ���� 
					message_box.push(MP(from,MP(PLAYER,-1)));//��ɱ��Ϣ 
					lfin.life=0;
					game_end=true;game_success=false;
				}
			}
			void player_add_stg(double add){
				player1.vts.stg.physical_strength+=add;
				limit_double(player1.vts.stg.physical_strength,1,100);//��ҪԽ�� 
				player1.vts.stg.change=true;
			}
			void hurt_enemy(MAP &POS){
				if(POS.player_enemy!=NOBODY&&POS.emy.id>=0){
					int id=POS.emy.id;
					if(POS.player_enemy==BUG) Qbug_hurt.push(id);
					else if(POS.player_enemy==SPIDER) Qspider_hurt.push(id);
					else if(POS.player_enemy==GHOST) Qghost_hurt.push(id);
				}
			}
			bool bug_move_away(int id){//�ı�λ��������false��û��Ѩ���޷���� 
				if(id<0||id>=bugs.size()) return false;
				bug &bg=bugs[id];
				bg.update=false;
				if(pos_in_nest.size()==0){//û�г�Ѩ�� 
					bg.change_pos=false;//�޷����� 
					return false;
				}
				int k=RAND(pos_in_nest.size()-1,0);
				position_3D npos=pos_in_nest[k];
				MAP &NPOS=game_map[npos.x][npos.y][npos.z];
				if(space_here(npos)&&nobody_here(npos)&&!NPOS.fcmv.lock&&NPOS.emy.id==-1){
					bg.pos=npos;
					NPOS.player_enemy=BUG;NPOS.emy.id=id;
					bg.lfin.init(5);
					bg.vlc.speed++;bg.vlc.vt();
					bg.enter_nest=true;
					bg.change_pos=false;
				}
				else bg.change_pos=true;
				return true; 
			}
			void bug_reduce_blood(int id,double hurt,PII from,bool push=1){
				if(id<0||id>=bugs.size()) return;
				bug &bg=bugs[id];
				if(bg.lfin.life<=0) return;//�Ѿ����˾Ͳ��ٿ�Ѫ�� 
				MAP &POS=game_map[bg.pos.x][bg.pos.y][bg.pos.z];
				thing &THING=POS.things;
				life_injury &lfin=bg.lfin;
				if(hurt<=0||hurt>0&&lfin.canhurt()) lfin.life-=hurt;
				if(hurt>0&&lfin.canhurt()){
					lfin.change=2;
					lfin.hurt+=hurt;
					lfin.lst_hurt=hurt;
					lfin.last_injury_from=from;
					lfin.last_injury_time=game_time;
				} 
				else lfin.change=1;
				if(push) 
					Qbug_hurt.push(id);
				if(POS.ist.player==lst_see_time){
					game_flag["���˱���ҹ���"]=true; 
					pos_change.insert(bg.pos);
				}
			}
				void spider_update_leg(position_3D pos,int k,int id){//λ��Ϊpos��֩�븽֫��Ļ���£�ֻҪ֩��λ�á�����ı�͵��ã� 
					if(id<0) return;
					for(int i=0;i<8;i++){//֮ǰ�ĸ�֫����Ļ�ϸ��� 
						position_3D v=dtp3(pos,i,8);
						MAP &VPOS=game_map[v.x][v.y][v.z];
						spider_leg &slg=VPOS.things.slg;
						slg.num+=k;//����������û�и�֫���Ӽ� 
						if(k>=0&&(id<0||id>=spiders.size()?1:spiders[id].kind==2)) slg.id=id;
						else slg.id=-1;//֩���뿪Ҫ�����жϸ�֫ 
						if(!wall_here(v)&&VPOS.ist.player==lst_see_time){
							player1.enemy_move=true;
							pos_change.insert(v);
							game_flag["�ڵ������ƶ�"]=true; 
						}
					}
				}
			void spider_move_away(int id){//�ı�λ������ 
				if(id<0||id>=spiders.size()) return;
				spider &sr=spiders[id];
				sr.update=false;
				position_3D npos;
				npos.x=RAND(length-1,1);npos.y=RAND(width-1,1);npos.z=RAND(height,1);
				MAP &NPOS=game_map[npos.x][npos.y][npos.z];
				if((space_here(npos)||stair_here(npos))&&nobody_here(npos)&&!NPOS.fcmv.lock&&NPOS.emy.id==-1){
					sr.pos=npos;
					NPOS.player_enemy=SPIDER;NPOS.emy.id=id;
					sr.bir=sr.pos;
					sr.lfin.init(20);//��make_spider������ͬ 
					sr.vlc.speed+=1.2;sr.vlc.vt();
					sr.change_pos=false;
					sr.update=true;
					spider_update_leg(sr.pos,1,id);//�������Ǹ�֫ 
					NPOS.things.snt.endurance=100;//����������֩���� 
				}
				else sr.change_pos=true;
			}
			void spider_reduce_blood(int id,double hurt,PII from){
				if(id<0||id>=spiders.size()) return;
				spider &sr=spiders[id];
				if(sr.lfin.life<=0) return;//�Ѿ����˾Ͳ����� 
				MAP &POS=game_map[sr.pos.x][sr.pos.y][sr.pos.z];
				thing &THING=POS.things;
				life_injury &lfin=sr.lfin;
				if(hurt<=0||hurt>0&&lfin.canhurt()) lfin.life-=hurt;
				if(hurt>0&&lfin.canhurt()){
					lfin.change=2;
					lfin.hurt+=hurt;
					lfin.lst_hurt=hurt;
					lfin.last_injury_from=from;
					lfin.last_injury_time=game_time;
				} 
				else lfin.change=1;
				if(POS.ist.player==lst_see_time){
					game_flag["���˱���ҹ���"]=true; 
					pos_change.insert(sr.pos);
				}
			}
			void ghost_move_away(int id){//�ı�λ������ 
				logMessage("ghost_move_away id="+int_to_str(id)); 
				if(id<0||id>=ghosts.size()) return;
				ghost &gt=ghosts[id];
				if(gt.lfin.life<=0) return;//�Ѿ����˾Ͳ����� 
				gt.update=false;
				position_3D npos;
				npos.x=RAND(length-1,1);npos.y=RAND(width-1,1);npos.z=RAND(height,1);
				MAP &NPOS=game_map[npos.x][npos.y][npos.z];
				if(space_here(npos)&&nobody_here(npos)&&!NPOS.fcmv.lock&&NPOS.ist.player!=lst_see_time&&NPOS.emy.id==-1){
					gt.pos=npos;
					NPOS.player_enemy=GHOST;NPOS.emy.id=id;
					gt.lfin.init(30);//��make_ghost������ͬ 
					gt.vlc.speed+=0.5;gt.vlc.vt();
					gt.change_pos=false;
					gt.update=true;
					gt.spe.init();//����Ч��ȫ����� 
					special_attribute &spat=gt.spat;
					switch(gt.spat.attack){
						case INSTANT:
							spat.ins.p=min(100,spat.ins.p+10);
							break;
					}
					switch(gt.spat.defense){
						case EVADE:
							spat.eva.k=min(100,spat.eva.k+10);
							break;
						case ROCK:
							spat.rck.k*=0.5;
							break;
						case SHIELD://=����2��������
							spat.eva.k=min(100,spat.eva.k+10); 
							spat.rck.k*=0.5;
							break;
					}
					//���ܹ�ʵ�����ϼ�ǿ
					gt.attack_time=gt.attack_time-RAND_DOUBLE(0.05,0.0);//���ϼ�С 
					limit_double(gt.attack_time,0.0,0.5); 
				}
				else gt.change_pos=true;
			}
			void ghost_reduce_blood(int id,double hurt,PII from){
				if(id<0||id>=ghosts.size()) return;
				ghost &gt=ghosts[id];
				MAP &POS=game_map[gt.pos.x][gt.pos.y][gt.pos.z];
				thing &THING=POS.things;
				life_injury &lfin=gt.lfin;
				if(hurt<=0||hurt>0&&lfin.canhurt()) lfin.life-=hurt;
				if(hurt>0&&lfin.canhurt()){//�ܵ��˺���û����� 
					lfin.change=2;
					lfin.hurt+=hurt;
					lfin.lst_hurt=hurt;
					lfin.last_injury_from=from;
					lfin.last_injury_time=game_time;
				} 
				else lfin.change=1;
				if(POS.ist.player==lst_see_time){
					game_flag["���˱���ҹ���"]=true; 
					pos_change.insert(gt.pos);
				}
			}
			void living_things_reduce_blood(position_3D pos,double hurt,int kind,PII from){//���������Ѫ 
				MAP &POS=game_map[pos.x][pos.y][pos.z]; 
				if(POS.player_enemy==PLAYER) player_reduce_blood(hurt,from);
				else if(POS.player_enemy==BUG&&POS.emy.id>=0&&POS.emy.id<bugs.size())
					bug_reduce_blood(POS.emy.id,hurt,from);
				else if(POS.player_enemy==SPIDER&&POS.emy.id>=0&&POS.emy.id<spiders.size())
					spider_reduce_blood(POS.emy.id,hurt,from);
				else if(POS.player_enemy==GHOST&&POS.emy.id>=0&&POS.emy.id<ghosts.size()){
					ghost &gt=ghosts[POS.emy.id];
					if(kind==1&&gt.spat.defense==ROCK||gt.spat.defense==SHIELD) ghost_reduce_blood(POS.emy.id,hurt*gt.spat.rck.k,from);
					//����ʱ���ܼ��� 
					else ghost_reduce_blood(POS.emy.id,hurt,from);
				}
			}
			void player_kill_reward(position_3D u,int kill,special_attribute spat){
				MAP &POS=game_map[u.x][u.y][u.z];
				thing &THING=POS.things;
				int kind,effect;
				switch(kill){
					case GHOST:
						//ֱ������ʳ�ﲹ�� 
						if(spat.attack&&spat.defense){//˫���ܵĹ� 
							kind=ADDS;//ֻ�������ظ� 
							effect=RAND(spat.attack+spat.defense,spat.defense);//����Ϊ����+����������Ϊ�������и��ʳ�ϡ�е��� 
							limit_int(effect,1,3);//���Ʒ�Χ
						}
						else if(!spat.attack&&!spat.defense){//�޼��ܵĹ� 
							kind=RAND(ADDL,RAND(ADDL,ADDS));//�󲿷������ظ� 
							effect=RAND(2,1);//�ȼ��ϵ� 
						}
						else{//�����ܵĹ� 
							kind=RAND(ADDL,ADDS);//�������ظ��������ظ�
							effect=log2(RAND(RAND(1<<3,1<<1),1<<1));//�ߵȼ��Ľ�Ϊϡ�� 
						}
						food_pile &FOOD=THING.foods;
						pos_make_food(u,kind,effect);//FOOD.make(kind,effect);
						break;
				}
			}
			void player_move_update(position_3D npos);
				void move_box_thing(position_3D u,position_3D v){//u->v u[box]
					//��������װ�Ķ������� 
					MAP &POS=game_map[u.x][u.y][u.z];
			   		thing &THING=POS.things;
					MAP &NPOS=game_map[v.x][v.y][v.z];
			   		thing &NTHING=NPOS.things;
			   		/*
					for(int i=0;i<KINDS_OF_FOOD;i++)
						for(int j=0;j<EFFECT_OF_FOOD;j++)
							NTHING.foods.food_cnt[i][j]+=THING.foods.food_cnt[i][j];
					THING.foods.init();
					swap(THING.ppt,NTHING.ppt);
					swap(THING.smb,NTHING.smb);*/
					swap(THING.fir,NTHING.fir);
					//�ƶ�ʳ����� 
					
					swap(POS.player_enemy,NPOS.player_enemy);
					swap(POS.emy.id,NPOS.emy.id);
					int id=NPOS.emy.id;
					//��ʱ���ƶ������� 
					if(NPOS.player_enemy==BUG&&id>=0&&id<bugs.size()){//�� 
						bug &bg=bugs[id];
						bg.pos=v;
					}
					else if(NPOS.player_enemy==GHOST&&id>=0&&id<ghosts.size()){//�� 
						ghost &gh=ghosts[id];
						gh.pos=v;
					}
					else if(NPOS.player_enemy==SPIDER&&id>=0&&id<spiders.size()){//֩�� 
						spider &sr=spiders[id];
						spider_update_leg(sr.pos,-1,id);
						sr.pos=v;
						spider_update_leg(v,1,id);
					}
					else if(NPOS.player_enemy==PLAYER){//���
						player1.items.rmv.select=pos000;
						player_move_update(v);//�����е����ޣ� 
					} 
					//�ƶ����� 
				}
				void vibrate_spider_net(position_3D pos,int k){//��֩���� 
					map<position_3D,bool> mp;//vst 
					while(!Q.empty()) Q.pop();
					game_map[pos.x][pos.y][pos.z].things.snt.mxk(k);
					mp[pos]=1;
					Q.push(pos);
					while(!Q.empty()){
						position_3D u=Q.front();Q.pop();
					   	MAP &POS=game_map[u.x][u.y][u.z];
					   	thing &THING=POS.things;
					   	int uk=THING.snt.nowk();
						if(uk<=1000) continue;//�ټ�����0�� 
						for(int i=0;i<=4;i++){//0~3+4¥�� 
							position_3D v;
							if(i<4) v=dtp3(u,i,4);//�����ķ��򴫵� 
							else if(stair_here(u)){//¥�� 
								v=u;
							   	if(upstair_here(u)) v.z++;
						   		else v.z--;
							}
							else break;//û��¥�ݾ����� 
						   	MAP &NPOS=game_map[v.x][v.y][v.z];
						   	thing &NTHING=NPOS.things;
						   	if(mp[v]) continue;//���ʹ��� 
						   	if(!NTHING.snt.exist()) continue;//û��֩���������� 
						   	if(wall_here(v)||exit_here(v)||door_here(v,0)||door_here(v,2)) continue;//�������� 
						   	int vk=NTHING.snt.nowk(),nxtk=uk-1000;
						   	if(vk>=nxtk) continue;//û�и��¾Ͳ����ڴ˴���չ�� 
						   	NTHING.snt.mxk(nxtk);//�����˥����������
						   	mp[v]=1;
						   	Q.push(v);
						}
					}
				}
			void player_move_update(position_3D npos){//����ƶ��ĸ������������������Ʒ���������� 
				removable &rmv=player1.items.rmv;
				position_3D u=rmv.select,v=player1.pos;
			   	MAP &POS=game_map[v.x][v.y][v.z];
			   	thing &THING=POS.things;
			   	MAP &NPOS=game_map[npos.x][npos.y][npos.z];
			   	thing &NTHING=NPOS.things;
				if(u!=pos000){//rmv.deal_kind==PULL&&
					if((u==npos?0:!NTHING.mvb.exist)&&(u==v?0:!THING.mvb.exist||u==npos)){//����������Ʒ
						MAP &SPOS=game_map[u.x][u.y][u.z];
						thing &STHING=SPOS.things;
						if(STHING.mvb.exist){
							if(THING.mvb.kind==BOX&&POS.update_light()) pos_affect_light.push(v);//���Ӷ��˸��¹��� 
							if(STHING.mvb.kind==BOX&&SPOS.update_light()) pos_affect_light.push(u);//���Ӷ��˸��¹��� 
							if(box_here(u)){
								move_box_thing(u,v);
							}
							swap(THING.mvb,STHING.mvb);//����
							int k=STHING.mvb.kind;
							if(k==CHAIR||k==DESK||k==BOX)
								MUSIC("������2.wav",1);//��������/����/���ӵ����� 
						}
						player1.items.rmv.select=v;
					}
					else if(u!=npos&&u!=v&&!NTHING.mvb.exist) player1.items.rmv.select=pos000;//û���ߵ�ѡ�е���Ʒ��
				}
				if(NTHING.snt.exist()) vibrate_spider_net(npos,15*1000);//������15�� 
				if(MHT_DIST(screen_center.x,screen_center.y,npos.x,npos.y)==1) screen_center=position_3Dto2D(npos);
				//����Ϊ1ֱ���л������򽻸�player_sight_update 
				player1.spe.dst.time=game_time;
				player1.pos=npos;//����λ�� 
				player1.move=true;
				game_timer["����ϴ��ƶ�"]=game_time;
			}
			bool push_thing(position_3D pos,int dir,int kind){
			//��posλ�õĿ��ƶ���Ʒ��dir�����ƣ������������ӡ�����ȣ��������Ƿ�ɹ��ƶ� 
			//kind=0��ֻ����ֵ���κ�Ч�� 1������ƶ�����Ч��������ײ�鶫����������ֵΪ����ƶ� 
			   	MAP &POS=game_map[pos.x][pos.y][pos.z];
			   	thing &THING=POS.things;
				mirror &MIRRORS=THING.mirrors;
				if(mirror_here(pos)) dir=mirror_relect(MIRRORS.dir,MIRRORS.side,dir);//ʵ�ʷ��� 
				if(dir==-1) return false;
				position_3D u=dtp3(pos,dir,4);//pos->u
			   	MAP &NPOS=game_map[u.x][u.y][u.z];
			   	thing &NTHING=NPOS.things;
				bool nothing=normv_here(pos),nobody=nobody_here(pos);
			   	if(nothing&&nobody) return true;//���ڵ�λ���ǿ�λ�����ƶ�
			   	if(!pos_in_area2(u.x,u.y,1,1,length,width,2)//������ͼ��Χ 
				||!mvb_through(u,dir)){//�ϰ�
					if(kind==1){//��鸽��Ч��
						bool effect=0;
						if(mirror_here(u)){//ײ������ 
							NTHING.mirrors.damage(30);
							effect=1;
						}
					 	else if(window_here(u)){//ײ������ 
							NTHING.windows.damage(5,u);
							effect=1;
						}
						if(effect&&NPOS.ist.player==lst_see_time) player_add_stg(-5);//�и���Ч���������� 
					}
				 	return false;//�Ʋ����� 
				}
			   	if(!push_thing(u,dir,kind)) return false;//�����Ʋ����Ͳ����� 
			   	if(kind==0) return true;//ֻ����ֵ
			   	if(player1.items.rmv.select==pos) player1.items.rmv.select=pos000;
			   	NTHING.snt.addedc(THING.snt.endurance/2,u);
			   	THING.snt.endurance/=2;//��һ�뵽��һ��λ�� 
				if(!nothing){//�ƶ���Ʒ
					swap(NTHING.mvb,THING.mvb);
					if(box_here(u)){//THING->NTHING �Ѿ��ƹ�ȥ�� 
						move_box_thing(pos,u);
					}
					if(THING.mvb.kind==BOX&&POS.update_light()) pos_affect_light.push(pos);//���Ӷ��˸��¹��� 
					if(NTHING.mvb.kind==BOX&&NPOS.update_light()) pos_affect_light.push(u);//���Ӷ��˸��¹��� 
					if((NTHING.mvb.kind==CHAIR||NTHING.mvb.kind==DESK||NTHING.mvb.kind==BOX)
					&&MHT_DIST(u.x,u.y,player1.pos.x,player1.pos.y)<=10&&u.z==player1.pos.z)
						MUSIC("������2.wav",1);//�ƶ�����/����/���ӵ����� 
					if(NPOS.ist.player==lst_see_time){
						game_flag["������"]=true;
						pos_change.insert(pos); 
					}
				}
				nobody=nobody_here(pos);//��ֹ�ƶ�����˳���Ű����������� 
				if(!nobody){//�ƿ�����
					int id=POS.emy.id;
					if(POS.player_enemy==BUG&&id>=0&&id<bugs.size()){//�� 
						bug &bg=bugs[id];
						bg.pos=u;
					}
					else if(POS.player_enemy==GHOST&&id>=0&&id<ghosts.size()){//�� 
						ghost &gh=ghosts[id];
						gh.pos=u;
					}
					else if(POS.player_enemy==SPIDER&&id>=0&&id<spiders.size()){//֩�� 
						spider &sr=spiders[id];
						spider_update_leg(sr.pos,-1,id);
						sr.pos=u;
						spider_update_leg(u,1,id);
					}
					else if(POS.player_enemy==PLAYER){//���
						player1.items.rmv.select=pos000;
						player_move_update(u);//�����е����ޣ� 
					} 
					swap(NPOS.player_enemy,POS.player_enemy);
					swap(NPOS.emy.id,POS.emy.id);
				}
				game_timer["��"]++;
				return true;
			}
			void throw_thing(position_3D pos,double speed,double hurt,int angle,pair<int,int> from){
			//��pos������speed�ļ��ٶȣ�����angle����Դfrom 
			//�Ӷ�����׼�����������µ�ͼ+�������+ײ����Ѫ�� 
			//hurt���˺�ϵ�� 
				MAP &POS=game_map[pos.x][pos.y][pos.z]; 
				force_move &FCMV=POS.fcmv;
				flying_mvb fmb;
				fmb.init(pos);//�µ��ƶ���Ʒ 
				if(!FCMV.lock) mvbs.push(fmb);//û���ڶ�����ͷ������
				FCMV.init2(speed,angle,from);
				if(!nobody_here2(pos)&&fabs(hurt)>eps)//��/ײ������ 
					living_things_reduce_blood(pos,hurt*speed,0.5,from);
				//formatted_output(1,vital_signs_area,1,17,MMPP(0,360,-100,360),double_to_str(vx.speed,0,3));
				//formatted_output(1,vital_signs_area,1,18,MMPP(0,360,-100,360),double_to_str(vy.speed,0,3));
			}
			void update_being(position_3D pos){//ʹĳ�����￪ʼ���� 
				MAP &POS=game_map[pos.x][pos.y][pos.z];
				if(POS.player_enemy==BUG&&POS.emy.id>=0&&POS.emy.id<bugs.size()){//�ܿ����������
					int id=POS.emy.id;
					bug &bg=bugs[id];
					if(!bg.update){
						Qbug.push(id);
						bg.update=true;
					}
				}
				else if(POS.player_enemy==SPIDER&&POS.emy.id>=0&&POS.emy.id<spiders.size()){//�ܿ������֩��
					int id=POS.emy.id;
					spider &sr=spiders[id];
					if(!sr.update){
						Qspider.push(id);
						sr.update=true;
					}
				}
				else if(POS.player_enemy==GHOST&&POS.emy.id>=0&&POS.emy.id<ghosts.size()){//�ܿ��������
					int id=POS.emy.id;
					ghost &gt=ghosts[id];
					if(!gt.update){
						Qghost.push(id);
						gt.update=true;
					}
				}
				if(spider_leg_here(pos)&&POS.things.slg.id>=0&&POS.things.slg.id<=spiders.size()){//B��֩�븽֫�壨�ֿ����ǣ� 
					int id=POS.things.slg.id;
					spider &sr=spiders[id];
					if(!sr.update){
						Qspider.push(id);
						sr.update=true;
					}
				} 
			}
		void deal_bug(){
			logMessage("deal_bug"); 
			int bug_num=Qbug_hurt.size();
			while(bug_num>0){
				bug_num--;
				int id=Qbug_hurt.front();Qbug_hurt.pop();
				if(id<0||id>=bugs.size()) continue;
				bug &bg=bugs[id];
				life_injury &lfin=bg.lfin; 
				MAP &POS=game_map[bg.pos.x][bg.pos.y][bg.pos.z];
				string s="����"+int_to_str(id);
				if(bg.lfin.life>0&&!bg.update){//���˸��� 
					Qbug.push(id);
					bg.update=true;
				}
				thing &THING=POS.things;
				if(THING.lsr.exist||THING.drt.exist1()
				||(THING.spr.exist&&game_timer[s+"��ì����"]<=game_time)//1000������ʱ�ѵ� 
				){
				    if(THING.spr.exist){
						game_timer[s+"��ì����"]=game_time+1000;//ÿ�����һ���˺� 
						object_addE(player1.items.wpn.primary,-bg.vlc.speed);
					}
					else player1.scr.shoot_hit_times++;
					bug_reduce_blood(id,5,MP(PLAYER,-1),0);
				}
				if(POS.fcmv.lock){
					if(POS.fcmv.speed()>5&&game_timer[s+"������"]<=game_time){
						bug_reduce_blood(id,1,POS.fcmv.from,0);
						game_timer[s+"������"]=game_time+500;
					}
				}
				if(lfin.life<=0){//����ۼ� bug_here(bg.pos)&&POS.emy.id==id&&
					if(POS.ist.player==lst_see_time){
						game_flag["���˱���ҹ���"]=true; 
						pos_change.insert(bg.pos);
						pos_dead.push(bg.pos);
					}
					if(bg.pos!=pos000){
						message_box.push(MP(lfin.last_injury_from,MP(BUG,id)));//��ɱ��Ϣ 
						bg.pos=pos000;
						if(lfin.last_injury_from.first==PLAYER) player1.scr.kc.update(1,BUG);
					}
					POS.fcmv.lock=false;//game_flag["��"]=true;pos_change.insert(bg.pos);//������� 
					POS.emy.dead=true;POS.emy.body_disapp=game_time+200;
					POS.player_enemy=NOBODY;POS.emy.id=-1;
					/*�𸴻��� 
					if(bug_move_away(id)){//���һ�θ���ͳɹ��Ͳ��ͷ������Ǹ�ѭ���� 
						Qbug.push(id);
						bg.update=true;
					}*/
					//continue; 
				}
				game_timer["��"]++;
			}//ѭ��1����������ѭ�� 
			bug_num=Qbug.size();
			while(bug_num>0){
				bug_num--;
				int id=Qbug.top();Qbug.pop();
				if(id<0||id>=bugs.size()) continue;
				bug &bg=bugs[id];
				MAP &POS=game_map[bg.pos.x][bg.pos.y][bg.pos.z];
				string s="����"+int_to_str(id);
				if(bg.lfin.life<=0) continue;//��������
				/* ��������
				if(bg.change_pos){//������ 
					game_timer["��"]++;
					
					if(bug_move_away(id)) Qbug.push(id);//û�г�Ѩ���þͲ�Ҫ�ٸ�����
					continue; 
				}*/
				if(MHT_DIST2(bg.pos.x,bg.pos.y,(bg.pos.z>height?bg.pos.z-height:bg.pos.z),player1.pos.x,player1.pos.y,player1.pos.z)>100
				&&POS.ist.player<lst_see_time)//����Ҿ��볬��100��ע�ⳲѨ�߶ȣ�����ҿ����� 
					bg.update=false;//ֹͣ���� 
				if(!bg.update) continue;
				Qbug.push(id);
				thing &THING=POS.things;
				if(game_timer[s]>game_time)//ʱ��û�������� 
					break;
				game_timer[s]=game_time+bg.vlc.wait_time; 
				game_timer["��"]++;
				if(!(THING.lsr.exist||THING.drt.exist1()||THING.spr.exist)
				&&game_timer[s+"������"]<=game_time){
				//Ҫ������һһ��Ӧ 
					if(bg.lfin.change!=0&&POS.ist.player==lst_see_time){
						game_flag["���˱���ҹ���"]=true; 
						pos_change.insert(bg.pos);
					}
					bg.lfin.change=0;
				}
				THING.snt.addedc(-2,bg.pos);//��֩���� 
				if(THING.spr.exist||POS.fcmv.lock||THING.snt.endurance>25){
					continue;//��ì�����޷��ƶ��͹��� 
				}
				position_3D npos=bg.pos;
				int d=bg.d;
				if(POS.emy.phm.disapp>game_time&&POS.emy.phm.id!=id) d=POS.emy.phm.d;//����Ϣ�� 
				else if(d==4) d=RAND(3,0);//����¥/������Ѩ�ں�������÷��� 
				//bool special_move=false;
				if(stair_here(npos)&&(bg.lst_ud+5000<=game_time||d==4)){//����¥ 
					if(game_map[npos.x][npos.y][npos.z].maze==UPSTAIR) npos.z++;
					else npos.z--;
					bg.lst_ud=game_time;//special_move=true;
					d=4;
				}
				else if(POS.things.nst.exist&&(bg.enter_nest+5000<=game_time||d==4)){//����Ѩ��
					position_3D npos2=POS.things.nst.to;
					MAP &POS2=game_map[npos2.x][npos2.y][npos2.z];
					npos.x=npos2.x;npos.y=npos2.y;npos.z=npos2.z;//�ƶ�����Ӧ�ĳ�Ѩ��
					bg.enter_nest=game_time;//special_move=true;
					d=4;
				}
				else{//��ͨ�ƶ� 
					npos.x+=dx4[d];
					npos.y+=dy4[d];
				}
				MAP &NPOS=game_map[npos.x][npos.y][npos.z];
				thing &NTHING=NPOS.things;
				if(!(NTHING.spr.exist||NTHING.mvb.exist||door_here(npos,0)||door_here(npos,2)||NTHING.hdr.exist
				||closed_box_here(bg.pos,d)
				||NTHING.lsr.exist||NPOS.fcmv.lock)
				&&(stair_here(npos)||space_here(npos))&&nobody_here(npos)){
					POS.player_enemy=NOBODY;POS.emy.id=-1;
					if(POS.emy.phm.disapp<=game_time||POS.emy.phm.d!=d){//������Ϣ��
						POS.emy.phm.disapp=game_time+5000;//����ʱ��5s 
						POS.emy.phm.id=id;
						POS.emy.phm.d=d; 
					}
					NPOS.player_enemy=BUG;NPOS.emy.id=id;
					if(POS.ist.player==lst_see_time&&bg.pos.z==player1.pos.z){
						player1.enemy_move=true;
						pos_change.insert(bg.pos);
						if(THING.crt.exist&&POS.ist.player==lst_see_time){
							game_flag["����ҡ��"]=true;
							if(POS.update_light()) pos_affect_light.push(bg.pos);//���Ӷ��˹��ո��� 
						}
					}
					if(NPOS.ist.player==lst_see_time&&npos.z==player1.pos.z){
						player1.enemy_move=true;
						pos_change.insert(npos);
						if(NTHING.crt.exist&&POS.ist.player==lst_see_time){
							game_flag["����ҡ��"]=true;
							if(NPOS.update_light()) pos_affect_light.push(npos);//���Ӷ��˹��ո��� 
						}
					}
					if(NTHING.snt.exist()) vibrate_spider_net(npos,10*1000);
					
					//��ֳ 
					if(bg.pos.z>height//���ڳ�Ѩ�ڷ�ֳ 
					&&space_here(bg.pos)&&nobody_here(bg.pos)&&!dead_here(bg.pos)&&empty_here(bg.pos)&&!POS.fcmv.lock
					//�յأ�û������û���������ᱻײ�� 
					//&&!(THING.lsr.exist||THING.spr.exist||THING.drt.exist())
					//&&count_around_pos(bg.pos,4,wall_here)==3//������ͬ�ﷱֳ 
					&&count_around_pos(bg.pos,4,nobody_here)>=2//��̫���� 
					&&bg.lfin.life>=6//&&RAND_BOOL(20)&&RAND_BOOL(5)//�趨���� 
					){
						pos_make_bug(bg.pos,bg.vlc.speed+1,1);
						bug_reduce_blood(id,1,MP(BUG,id));//����������ֳ 
					}
					
					bg.pos=npos;//����λ�� 
					if(!stair_here(npos)) bg.lst_ud=game_time-5000;
					if(!NPOS.things.nst.exist) bg.enter_nest=game_time-5000;
				}
				else{
					if(d==4&&!box_here(bg.pos)||d<4&&!closed_box_here(bg.pos,d)){
						int door_d=(d==4?0:turn(d,TURN_BACK,4,8));//���� 
						if(NPOS.player_enemy==PLAYER&&(d==4?!box_here(bg.pos):!door_here(npos,2)&&!closed_box_here(npos,door_d))){
							player_reduce_blood(10.0/bg.vlc.speed,MP(BUG,id));
							bug_reduce_blood(id,-1,MP(BUG,id));//������Ѫ
							if(POS.ist.player==lst_see_time){
								game_flag["���˱���ҹ���"]=true; 
								pos_change.insert(bg.pos);
							}
						}
						else if(NTHING.mvb.exist&&(NTHING.mvb.kind==BALL||NTHING.mvb.kind==CHAIR)&&!NPOS.fcmv.lock){//�ƶ�����/���� 
							position_3D v=dtp3(npos,d<4?d:RAND(3,0),4);
							MAP &VPOS=game_map[v.x][v.y][v.z];
							thing &VTHING=VPOS.things;
							if(!(VTHING.spr.exist||VTHING.mvb.exist||door_here(v,0)||door_here(v,2)||VTHING.hdr.exist)
							&&(stair_here(v)||space_here(v))&&nobody_here(v)){//ֻ��һ��
								swap(VTHING.mvb,NTHING.mvb); 
								if(NPOS.ist.player==lst_see_time){
									game_flag["��noply"]=true;
									pos_change.insert(npos);
								}
								if(VPOS.ist.player==lst_see_time){
									game_flag["��noply"]=true;
									pos_change.insert(v);
								}
							}
						}
						else if(enemy_here(npos)){
							update_being(npos);
							int id=NPOS.emy.id;
							if(ghost_here(npos)&&!door_here(npos,2)
							&&(id<0||id>=ghosts.size()?1:ghosts[id].spat.defense!=ROCK&&ghosts[id].spat.defense!=SHIELD)){
								ghost_reduce_blood(id,10.0/bg.vlc.speed,MP(BUG,id));//��������ʯ���Ĺ�
								bug_reduce_blood(id,-1,MP(BUG,id));//������Ѫ 
								if(NPOS.ist.player==lst_see_time){
									game_flag["���˱���ҹ���"]=true;//����һ�� 
									pos_change.insert(bg.pos);
								}
							}
							if(id!=-1&&spider_body_here(npos)&&THING.snt.endurance<50){//������ʱ�ɹ���֩��
								spider_reduce_blood(id,10.0/bg.vlc.speed,MP(BUG,id)); 
								bug_reduce_blood(id,-1,MP(BUG,id));//������Ѫ 
								if(NPOS.ist.player==lst_see_time){
									game_flag["���˱���ҹ���"]=true;//����һ�� 
									pos_change.insert(bg.pos);
								}
							}
						}
						int tmp=count_around_pos(npos,4,space_here);
						if(npos.z>height&&pos_in_area2(npos.x,npos.y,1,1,length,width,2)
						&&wall_here(npos)&&tmp<3
						&&(tmp<=1?RAND_BOOL(15):RAND_BOOL(5))){//�����ڳ�Ѩ 
							NPOS.maze=SPACE;
							pos_in_nest.push_back(npos);//������Ѩ��������� 
							position_3D npos2=npos;npos2.z-=height;
							MAP &NPOS2=game_map[npos2.x][npos2.y][npos2.z];
							if(NPOS.ist.player==lst_see_time) game_flag["�����ڵص�"]=true;
							if((wall_here(npos2)||space_here(npos2))&&count_around_pos(npos2,4,space_here)<=2&&RAND_BOOL(80)){//���ɳ�Ѩ��
								if(!light_through(npos2)&&NPOS2.ist.player==lst_see_time) game_flag["�����ڵص�"]=true;
								NPOS2.maze=SPACE;NPOS2.things.windows.init();//�д����ʹ��� 
								bug_nest bns;
								bns.init(npos2);
								bug_nests.push_back(bns);
								int id=int(bug_nests.size())-1;
								nest &NST=NPOS.things.nst,&NST2=NPOS2.things.nst; 
								NST.exist=NST2.exist=true;NST.id=NST2.id=id;
								NST.to=npos2;NST2.to=npos; 
							}
						}
					}
					if(d==4) d=RAND(3,0);
					else if(RAND_BOOL(50)) d=turn(d,TURN_RIGHT,4,9);
					else d=turn(d,TURN_LEFT,4,10);
					bg.d=d;
				}
			}//ѭ��2������ѭ�� 
		}
				void spider_decision_update(vector<int> &vd,vector<double> &vrate,int &d,int &i,position_3D bir,position_3D u,position_3D v){
					MAP &POS=game_map[u.x][u.y][u.z];
					thing &THING=POS.things;
					MAP &NPOS=game_map[v.x][v.y][v.z];
					thing &NTHING=NPOS.things;
					double rate=1;
					int uk=THING.snt.nowk(),vk=NTHING.snt.nowk(),disu=MHT_DIST_p3(bir,u),disv=MHT_DIST_p3(bir,v);
					if(disv<disu) rate=5;//�����������ƶ����ʴ� 
					//if(dis>0) rate*=2.0/dis;//�������ԽԶ����ԽС����ֹ/0��
					//else rate*=2; 
					if(NTHING.snt.exist()){
						//rate*=sqrt((50-abs(50-NTHING.snt.endurance))/25+1);//��ֹ*0
						if(vk>uk) rate*=pow((vk-uk)/1000+1,4);//��ֹ*0 
					}
					if(!nobody_here2(v)) rate*=3;//������ʹ�����������
					if(door_here(v,0)||door_here(v,2)) rate*=0.5;//��С���ʿ��� 
					//if(d==i) rate*=1.5;//�ϴ����ά��ԭ�ȷ��� 
					vd.push_back(i);
					vrate.push_back(rate); 
				}  
				int spider_see(int id){//����ǰ������
					if(id<0||id>=spiders.size()) return RAND(3,0);
					int mx_dis=SPIDERB_SIGHT;//��Զ�۲���� 
					spider &sr=spiders[id];
					position_3D pos=sr.pos;//ԭλ�� 
					int d=sr.d;//ԭ���� 
					vector<PII > v(4);vector<position_3D> ret;
					int tmp=(d+3)%4*90;//֩�뷽���Ӧ�ķ����
					for(int i=0;i<4;i++) v[i]=MP((tmp-90+360)%360,(tmp+90+360)%360);//֩�벿����Ұ��-90��~90�㣩 
					vision_init(1,v,ret,pos000);
					calculate_vision2(sr.pos,3,ret,mx_dis,0);
					position_3D goal=pos000;
					for(int i=0;i<ret.size();i++){
						position_3D u=ret[i];
						MAP &NPOS=game_map[u.x][u.y][u.z];
						int gtid=NPOS.emy.id;
						if(player_here(u)//�ҵ���� 
						||ghost_here(u)&&(gtid<0||gtid>=ghosts.size()?1:!ghosts[gtid].spat.can_disappear())){//�������� 
							goal=u;//�ͽ�ԭ��retһ���Ǵӽ���Զ����ģ� 
							break;
						}
					}
					if(goal==pos000){//������Ŀ�� 
						if(sr.prey==pos000) return -1;//�Ҳ������� 
						if(sr.pos==sr.prey){
							sr.prey=pos000;
							return -1;//�������������ֵ�λ�ã��������Ҳ��� 
						}
						else goal=sr.prey;//Ŀ����Ϊ���������ֵ�λ��
					}
					else sr.prey=goal;//�������������ֵ�λ�� 
					direction direct=ptp(goal,pos);
					int d1=direct.d1,d2=direct.d2;
					vector<int> vd2;
					if(pos.y!=goal.y){
						position_3D u=dtp3(pos,d1,4);//��λ�� 
						vision_init(1,v,ret,pos000);
						calculate_vision2(u,3,ret,mx_dis,0);//����Ұ
						if(find(ret.begin(),ret.end(),goal)!=ret.end()&&spider_through(u,d1,1)) vd2.push_back(d1);//d1������� 
					}
					if(pos.x!=goal.x){
						position_3D u=dtp3(pos,d2,4);//��λ��
						vision_init(1,v,ret,pos000);
						calculate_vision2(u,3,ret,mx_dis,0);//����Ұ 
						if(find(ret.begin(),ret.end(),goal)!=ret.end()&&spider_through(u,d2,1)) vd2.push_back(d2);//d2������� 
					}
					if(vd2.size()) return vd2[RAND(vd2.size()-1,0)];
					return -1;
				}
			void spider_turn(int &d,int id){//֩��ѡ����
				//����dֱ�ӽ��к������޸� 
				//MAP &PPOS=game_map[player1.pos.x][player1.pos.y][player1.pos.z];
				if(id<0||id>=spiders.size()) return;
				spider &sr=spiders[id];
				bool srk=sr.kind;
				vector<int> vd;//��ѡ����
				vector<double> vrate;//Ȩ�� 
				position_3D u=sr.pos;
				MAP &POS=game_map[u.x][u.y][u.z];
				thing &THING=POS.things;
				position_3D v;
				for(int i=0;i<4;i++){
					v=dtp3(u,i,4);
					MAP &NPOS=game_map[v.x][v.y][v.z];
					thing &NTHING=NPOS.things;
					int door_d=turn(i,TURN_BACK,4,11);//i���෴�������ţ� 
					if(door_d==sr.d&&sr.kind==1) continue;//B��֩��̫��׾û�����ת 
					if((player_here(v)||ghost_here(v))&&!closed_box_here(v,door_d)){//�Ա�����ҡ�����߹�ȥ 
						d=i;
						return;//��߼���ֱ���˳� 
					}
					if(spider_towards(v,i,srk)){
						/*
						if(i==d1) ok1=1;
						else if(i==d2) ok2=1;
						//֩�����Ұ��Χ���󣬲��ÿ���̫�� */
						spider_decision_update(vd,vrate,d,i,sr.bir,u,v);
					}
				}
				if(srk==0&&stair_here(u)){//����¥��B��֩������̫�󼷲���ȥ�� 
					int i=4;
					v=u;
					position_3D v2=v;
					MAP &POS2=game_map[v2.x][v2.y][v2.z];
					if(POS.maze==UPSTAIR) v.z++;
					else if(POS.maze==DOWNSTAIR) v.z--;
					MAP &NPOS=game_map[v.x][v.y][v.z];
					thing &NTHING=NPOS.things;
					if((player_here(v)||ghost_here(v))&&!box_here(v)){//�Ա�����ҡ�֩����߹�ȥ 
						d=i;
						return;//��߼���ֱ���˳� 
					}
					if(spider_towards(v,i,srk)) spider_decision_update(vd,vrate,d,i,sr.bir,u,v);
				}
				if(srk){//B��֩�� 
					int goal_d=spider_see(id);
					if(goal_d!=-1){
						d=goal_d;
						return;
					}
				}
				int sz=vd.size();
				for(int i=0;i<sz;i++)//��ԭ������������ 
					for(int j=1;j<vrate[i];j++) vd.push_back(vd[i]);
				sz=vd.size();
				if(sz) d=vd[RAND(sz-1,0)]; 
				d=(d+RAND(1,-1)+4)%4;//û�п�ѡ����������ת��ת��ԭ�ȷ��� 
			}
			void spider_shoot_silk(position_3D pos,double speed,int angle){//֩�뷢����˿
				MAP &POS=game_map[pos.x][pos.y][pos.z];
				thing &THING=POS.things;
				flying_ssk fsk;
				fsk.init(pos,speed,angle);
				ssks.push(fsk);//�������
				THING.ssk.num++;//���µ�ͼ
			} 
				void poison_spe(special_effect &spe,int k,PII from){//����˵�Ч��һ�� 
					switch(k){
						case 1://���� 
							spe.wks.change=true;
							spe.wks.end=max(spe.wks.end,game_time)+5000;
							spe.wks.t=-INF;spe.wks.T=RAND(10,5)*100;
							spe.wks.x=RAND(10,5);
							spe.wks.from=from;
							break;
						case 2://ѣ��
							spe.vtg.change=true;
							spe.vtg.end=max(spe.vtg.end,game_time)+10000;
							spe.vtg.t=-INF;spe.vtg.T=RAND(6,4)*100;
							spe.vtg.from=from;
							break;
						case 3://ʧ�� 
							spe.bds.change=true; 
							spe.bds.end=max(spe.bds.end,game_time)+6000;
							spe.bds.vision_dis=RAND(5,1);
							spe.bds.from=from;
							break;
						case 4://�ж�
							spe.mts.change=true;
							spe.mts.end=max(spe.mts.end,game_time)+5000;
							spe.mts.t=-INF;spe.mts.T=RAND(10,5)*100;
							spe.mts.x=2;
							spe.mts.from=from;
							break;
						case 5://�Ի� 
							spe.cfs.change=true;
							spe.cfs.end=max(spe.cfs.end,game_time)+4000;
							spe.cfs.a=5;
							spe.cfs.from=from;
							break;
					}
				}
			void poison_player(PII from){//ע�䶾Һ
				int k=RAND(5,1);
				special_effect &spe=player1.spe;
				/*
				1 weakness wks;
				2 vertigo vtg;
				3 blindness bds;
				4 methysis mts;
				5 confusion cfs;
				���˲���������Ҳ��һ�� 
				*/
				poison_spe(spe,k,from);
			}
			void poison_ghost(int id,PII from){
				if(id<0||id>=ghosts.size()) return;
				int k=RAND(4,1);
				ghost &gt=ghosts[id];
				if(gt.lfin.life<=0) return;//�Ѿ����˾Ͳ����¶��� 
				special_effect &spe=gt.spe;
				/*
				1.�������ƶ��ٶ��½���
				2.ѣ�Σ��޷�������
				3.ʧ������Ұ��Χ���ޣ�
				4.�ж���������Ѫ�� 
				*/
				poison_spe(spe,k,from);
			}
		void deal_spider(){
			logMessage("Qspider_hurt"); 
			int spider_num=Qspider_hurt.size();
			while(spider_num>0){
				spider_num--;
				int id=Qspider_hurt.front();Qspider_hurt.pop();
				if(id<0||id>=spiders.size()) continue;
				spider &sr=spiders[id];
				life_injury &lfin=sr.lfin;
				MAP &POS=game_map[sr.pos.x][sr.pos.y][sr.pos.z];
				string s="֩��"+int_to_str(id);
				if(!sr.update){//����
					sr.update=true;
					Qspider.push(id);
				}
				thing &THING=POS.things;
				if(THING.lsr.exist||THING.drt.exist1()
				||(THING.spr.exist&&game_timer[s+"��ì����"]<=game_time)//1000������ʱ�ѵ� 
				){//Ҫ������һһ��Ӧ
				    if(THING.spr.exist){
						game_timer[s+"��ì����"]=game_time+1000;//ÿ�����һ���˺� 
						object_addE(player1.items.wpn.primary,-sr.vlc.speed*2);
					}
					else player1.scr.shoot_hit_times++;
					spider_reduce_blood(id,5*(THING.lsr.exist+THING.drt.exist1()*THING.drt.num[1])+THING.spr.exist,MP(PLAYER,-1));
					//��ì��֩����ɵ��˺�΢����΢��-1�� 
					if(POS.ist.player==lst_see_time){
						game_flag["���˱���ҹ���"]=true;
						pos_change.insert(sr.pos);
					}
				}
				if(POS.fcmv.lock&&game_timer[s+"������"]<=game_time){
					if(POS.fcmv.speed()>2){
						spider_reduce_blood(id,1,POS.fcmv.from);
						game_timer[s+"������"]=game_time+500;
					}
				}
				if(lfin.life<=0){//����ۼ� spider_here(sr.pos)&&
					logMessage("Qspider_hurt lfin.life<=0"); 
					if(POS.ist.player==lst_see_time){
						game_flag["���˱���ҹ���"]=true; 
						pos_change.insert(sr.pos);
						pos_dead.push(sr.pos);
					}
					if(sr.pos!=pos000){
						message_box.push(MP(lfin.last_injury_from,MP(SPIDER,id)));//��ɱ��Ϣ 
						sr.pos=pos000;
						if(lfin.last_injury_from.first==PLAYER) player1.scr.kc.update(1,SPIDER);
					}
					spider_update_leg(sr.pos,-1,id);//���˸�֫ҲҪ����� 
					POS.fcmv.lock=false;//game_flag["��"]=true;pos_change.insert(sr.pos);//������� 
					POS.emy.dead=true;POS.emy.body_disapp=game_time+300;
					POS.player_enemy=NOBODY;POS.emy.id=-1;
					spider_move_away(id);
					logMessage("Qspider_hurt lfin.life<=0 end"); 
				}
				//game_timer["֩��"]++;
			}//ѭ��1����������ѭ�� 
			logMessage("Qspider"); 
			spider_num=Qspider.size();
			while(spider_num>0){
				spider_num--;
				int id=Qspider.top();Qspider.pop();
				if(id<0||id>=spiders.size()) continue;
				spider &sr=spiders[id];
				int srk=sr.kind;//֩������ 
				MAP &POS=game_map[sr.pos.x][sr.pos.y][sr.pos.z];
				string s="֩��"+int_to_str(id);
				if(sr.change_pos){
					Qspider.push(id);
					spider_move_away(id);
					continue;
				}
				if(MHT_DIST_p3(sr.pos,player1.pos)>100 
				&&POS.ist.player<lst_see_time)//����Ҿ��볬��100������ҿ����� 
					sr.update=false;//ֹͣ���� 
				if(!sr.update) continue;
				if(sr.lfin.life<=0) Qspider_hurt.push(id);
				Qspider.push(id);
				thing &THING=POS.things;
				if(game_timer[s]>game_time)//ʱ��û�������� 
					break;
				game_timer[s]=game_time+sr.vlc.wait_time; 
				game_timer["֩��"]++;//
				if(!(THING.lsr.exist||THING.drt.exist1()||THING.spr.exist)
				&&game_timer[s+"������"]<=game_time){
					if(sr.lfin.change!=0&&POS.ist.player==lst_see_time){
						game_flag["���˱���ҹ���"]=true; 
						pos_change.insert(sr.pos);
					}
					sr.lfin.change=0;
				}
				if(THING.lsr.exist||POS.fcmv.lock&&sr.kind==0) continue;//���������л򱻻��ɣ�A�ͣ��޷��ƶ��͹��� 
				position_3D npos=sr.pos;
				int d=sr.d;
				spider_turn(d,id); 
				if(stair_here(npos)&&d==4){//����¥ 
					if(game_map[npos.x][npos.y][npos.z].maze==UPSTAIR) npos.z++;
					else npos.z--;
				}
				else{//��ͨ�ƶ� 
					npos.x+=dx4[d];
					npos.y+=dy4[d];
				}
				MAP &NPOS=game_map[npos.x][npos.y][npos.z];
				thing &NTHING=NPOS.things;
				if(spider_through(npos,d,srk)){
					logMessage("Qspider move"); 
					/*
					if(sr.kind&&sr.prey!=pos000){//B��֩�뷢����˿ 
						int angle=calc_angle(sr.pos,sr.prey),angle2=(d+3)%4*90;//angle��Ŀ�귽�� angle2���ƶ�����·��� 
						if(sub_angle(angle,angle2)<=45&&MHT_DIST_p3(npos,sr.prey)>=2)
							spider_shoot_silk(npos,7,angle);//���򡢾������ 
					}*/
					POS.player_enemy=NOBODY;POS.emy.id=-1;
					NPOS.player_enemy=SPIDER;NPOS.emy.id=id;
					if(POS.ist.player==lst_see_time){
						player1.enemy_move=true;
						pos_change.insert(sr.pos);
						if(THING.crt.exist&&POS.ist.player==lst_see_time){
							game_flag["����ҡ��"]=true;
							if(POS.update_light()) pos_affect_light.push(sr.pos);//���Ӷ��˹��ո��� 
						}
					}
					if(NPOS.ist.player==lst_see_time){
						player1.enemy_move=true;
						pos_change.insert(npos);
						if(NTHING.crt.exist&&POS.ist.player==lst_see_time){
							game_flag["����ҡ��"]=true;
							if(NPOS.update_light()) pos_affect_light.push(npos);//���Ӷ��˹��ո��� 
						}
					}
					spider_update_leg(sr.pos,-1,id);
					spider_update_leg(npos,1,id);
					if(sr.kind==0) NTHING.snt.addedc(10,npos);//A��֩������֩��˿ ÿ���ƶ��и���if(RAND_BOOL(100-NTHING.snt.endurance))  
					sr.pos=npos;
					if(MHT_DIST(sr.pos.x,sr.pos.y,player1.pos.x,player1.pos.y)<=7&&sr.pos.z==player1.pos.z)
						MUSIC(sound_spider_move[RAND(4,0)],1);//֩�������� 
					sr.d=d;
					logMessage("Qspider move end"); 
				}
				else{
					logMessage("Qspider pump"); 
					int door_d=(d==4?0:turn(d,TURN_BACK,4,12));//���� 
					bool make_net=false;
					if(player_here(npos)&&(d==4?!box_here(npos):!closed_box_here(npos,door_d))){
						player_reduce_blood(5.0/sr.vlc.speed,MP(SPIDER,id));
						if(RAND_BOOL(25)) poison_player(MP(SPIDER,id));//25%���ʸ����ע�䶾Һ 
						make_net=true;
					}
					else if(ghost_here(npos)&&NPOS.emy.id!=-1&&!closed_box_here(npos,door_d)){
						ghost_reduce_blood(NPOS.emy.id,2.5,MP(SPIDER,id));//֩���� 
						if(sr.kind) spider_reduce_blood(id,-2,MP(SPIDER,id));//�Թ��Ѫ��B�ͣ�
						if(RAND_BOOL(25)) poison_ghost(id,MP(SPIDER,id));//25%���ʸ���ע�䶾Һ  
						hurt_enemy(NPOS);
						make_net=true;
					}
					else if(bug_here(npos)&&NPOS.emy.id!=-1&&!closed_box_here(npos,door_d)){
						bug_reduce_blood(NPOS.emy.id,2.5,MP(SPIDER,id));//֩��Գ���
						spider_reduce_blood(id,-1,MP(SPIDER,id));//�Գ��ӻ�Ѫ 
						hurt_enemy(NPOS);
						make_net=true;
					}
					else if(door_here(npos,0)||door_here(npos,2)){
						int &state=NTHING.kdr.state;
						if(state==2){
							state=1;//��->�� 
							if(NPOS.update_light()) pos_affect_light.push(npos);//�ſ��˹��ո���
							if(NPOS.ist.player==lst_see_time) game_flag["����"]=true;
						}
						else{//��ס����Ҳ�ܿ� 
							state=2;//��->�� ������ 
							if(NPOS.ist.player==lst_see_time){
								game_flag["��Ʒ��"]=true;
								pos_change.insert(npos);
							}
						}
					}
					else if(closed_box_here(npos,door_d)){
						NTHING.mvb.door[door_d]^=1;
						if(NPOS.ist.player==lst_see_time) game_flag["����"]=true;
					}
					else if(NTHING.windows.exist){
						window &WDN=NTHING.windows;
						WDN.damage(20,npos); 
					}
					if(make_net&&sr.kind==0){//A��֩�빥������˳������
						NTHING.snt.addedc(40,npos);
					}
					if(d!=sr.d) spider_update_leg(sr.pos,0,id);//�ı䷽��֫���£��������䣩 
					if(sr.kind==0||spider_through(sr.pos,d,srk)) sr.d=d;//��ֹB��֩��תһ�°��Լ���ס 
					logMessage("Qspider pump end"); 
				}
				//sr.d=d;
			}//ѭ��2������ѭ�� 
		}
				void ghost_decision_update(int id,vector<int> &vd,int &d,int &i,int &fpt,MAP &POS,MAP &NPOS,thing &THING,thing &NTHING){
					if(id<0||id>=ghosts.size()) return;
					ghost &gt=ghosts[id];
					if(d==i) vd.push_back(i),vd.push_back(i);//������ʱ���ԭ�ȷ��� 
					if(THING.fpt.d==i)//�㼣��ǰ������ 
						fpt=THING.fpt.d;
					if(NTHING.fpt.d!=-1){//�Ա����㼣 
						//fnear=i;
						vd.push_back(i);
						vd.push_back(i);
					}
					if(NPOS.player_enemy==SPIDER) vd.push_back(i),vd.push_back(i),vd.push_back(i);//����������Աߵ�֩�� 
					if(gt.spat.attack==VAMPIRE&&POS.brightness>NPOS.brightness){
						REP(10) vd.push_back(i);//��������ʣ���Ѫ��Զ��������� 
					} 
					vd.push_back(i);
				}  
				position_3D ghost_aim_goal(position_3D u,position_3D v){//u->v��
					/*
					int angle=calc_angle(u,v);
					double dis=NED_p3(u,v)+3;//������Һ���һ�� 
					position_3D pos=u;
					pos.x+=round(dis*cos(angle*PI/180.0)); 
					pos.y+=round(dis*sin(angle*PI/180.0));*/
					position_3D pos;
					pos.x=2*v.x-u.x;
					pos.y=2*v.y-u.y;
					pos.z=u.z;
					return pos;
				}
			void ghost_turn(int &d,int id){//����ı䷽��/��������㼣/����������� 
				logMessage("ghost_turn id="+int_to_str(id)); 
				//�Ա������>����>�㼣>�Ա����㼣>��� 		
				if(id<0||id>=ghosts.size()) return;
				MAP &PPOS=game_map[player1.pos.x][player1.pos.y][player1.pos.z];
				ghost &gt=ghosts[id];
				special_attribute &spat=gt.spat;
				int &att=spat.attack,&def=spat.defense;
				blindness &bds=gt.spe.bds;
				
				int mx_dis=(bds.exist()?bds.vision_dis:GHOST_SIGHT);//ʧ��Ч����������Ұ 
				vector<int> vd;vd.clear();//�����ߵķ��� 
				vector<int> d_vpr;d_vpr.clear();//��Ѫ������ߵķ��� 
				
				position_3D u=gt.pos;
				MAP &POS=game_map[u.x][u.y][u.z];
				thing &THING=POS.things;
				position_3D v;
				
				/*
				���ֱײ��������Ŀ�귨 
				double dis1=NED_p3(gt.pos,player1.pos),dis2=NED_p3(gt.goal,gt.pos),dis3=NED_p3(player1.pos,gt.goal);
				if(POS.ist.other==lst_see_time){
					if(gt.goal==pos000&&dis1>2&&RAND_BOOL(30))
						gt.goal=ghost_aim_goal(gt.pos,player1.pos);//gt.goal=player1.pos;//���ָ��� 
					//else if(gt.goal!=pos000&&dis3>5)
					//	gt.goal=ghost_aim_goal(gt.pos,player1.pos);//gt.goal=player1.pos;//���ָ��� 
					else if(gt.pos==gt.goal) gt.goal=pos000;//��ʧĿ�� 
				}
				else if(gt.goal!=pos000&&gt.pos==gt.goal) gt.goal=pos000;//��ʧĿ�� 
				*/
				direction direct;
				if(gt.goal==pos000) direct=ptp(player1.pos,u);
				else direct=ptp(gt.goal,u);
				int snd=-1,fpt=-1,fnear=-1,d1=direct.d1,d2=direct.d2;
				if(u.y==player1.pos.y&&RAND_BOOL(25)&&gt.goal!=pos000) d1=-1;
				if(u.x==player1.pos.x&&RAND_BOOL(25)&&gt.goal!=pos000) d2=-1;
				//����׷�����ʱ���������ˮƽ����ֱ����ʱ��75%���ʰѴ�ֱ��������ҵķ�����뿼�� 
				
				bool ok1=0,ok2=0;
				for(int i=0;i<4;i++){
					v=dtp3(u,i,4);
					MAP &NPOS=game_map[v.x][v.y][v.z];
					thing &NTHING=NPOS.things;
					int door_d=turn(i,TURN_BACK,4,13);//����
					/*
					if(player_here(v)&&!closed_box_here(v,door_d)&&NPOS.see(GHOST,gt.spat.attack)&&POS.see_fr()){//�Ա�����Ҿ��߹�ȥ 
						d=i;
						return;//��߼���ֱ���˳� 
					}*/
					if(ghost_towards(gt.pos,v,i,spat.can_through())&&(gt.spat.attack==VAMPIRE?!NPOS.burn_vampire():1)){
						if(gt.spat.attack==VAMPIRE&&POS.burn_vampire()&&POS.brightness>NPOS.brightness)//��Ѫ����ǿ�� 
							d_vpr.push_back(i);
						if((POS.ist.other==lst_see_time&&NPOS.ist.other==lst_see_time//�������һ�����ܿ������
						||spat.can_through()&&player1.pos.z==u.z)//��ǽ��͸�ӣ���λ��ͬһ¥�� 
						&&PPOS.see(GHOST,gt.spat.attack)&&POS.see_fr()){//̫����̫���������� 
							if(i==d1) ok1=1;
							else if(i==d2) ok2=1;
						}
						ghost_decision_update(id,vd,d,i,fpt,POS,NPOS,THING,NTHING);
					}
				}
				if(stair_here(u)||POS.things.nst.exist){//����¥��������Ѩ��
					int i=4;
					v=u;
					position_3D v2=v;
					if(POS.things.nst.exist) v2=POS.things.nst.to;
					MAP &POS2=game_map[v2.x][v2.y][v2.z];
					if(POS.maze==UPSTAIR) v.z++;
					else if(POS.maze==DOWNSTAIR) v.z--;
					else{//�ƶ�����Ӧ�ĳ�Ѩ��
						v.x=v2.x;
						v.y=v2.y;
						v.z=v2.z;
					}
					MAP &NPOS=game_map[v.x][v.y][v.z];
					thing &NTHING=NPOS.things;
					if(player_here(v)&&!box_here(v)&&NPOS.see(GHOST,gt.spat.attack)&&POS.see_fr()){//�Ա�����Ҿ��߹�ȥ 
						d=i;
						return;//��߼���ֱ���˳� 
					}
					if(ghost_towards(gt.pos,v,i,spat.can_through())&&(gt.spat.attack==VAMPIRE?!NPOS.burn_vampire():1)){
						if(gt.spat.attack==VAMPIRE&&POS.burn_vampire()&&POS.brightness>NPOS.brightness)//��Ѫ����ǿ�� 
							d_vpr.push_back(i);
						ghost_decision_update(id,vd,d,i,fpt,POS,NPOS,THING,NTHING);
					}
				}
				
				int sz3=d_vpr.size();//��Ѫ����Զ�ܵķ��� 
				if(gt.spat.attack==VAMPIRE&&POS.burn_vampire()&&sz3){//��Ѫ���⹥���� 
					d=d_vpr[RAND(sz3-1,0)];
					return;
				}
				
				vector<int> vd2;//׷����ҿ����ߵķ��� 
				if(ok1) vd2.push_back(d1);
				if(ok2) vd2.push_back(d2);
				int sz=vd.size(),sz2=vd2.size();
				int B=POS.brightness;
				int a=max(0,100-abs(B)*2);//�����㼣�ĸ��� 
				bool chase=0;//�Ƿ�׷�� 
				if(snd!=-1) d=snd;
				else if(NED_p3(u,player1.pos)<=mx_dis&&sz2){
					d=vd2[RAND(sz2-1,0)];//����Ұ��Χ�ھ�׷ 
					chase=1;
				}
				else if(fpt!=-1&&RAND_BOOL(a)) d=fpt;//�����㼣 
				//else if(fnear!=-1) d=fnear;
				else if(sz) d=vd[RAND(sz-1,0)]; 
				
				if(!chase) gt.goal=pos000; 
			}
			void ghost_disappear_print(position_3D pos,int kind){//���л�����״̬����ʾ���� 
				MAP &POS=game_map[pos.x][pos.y][pos.z];
				if(kind==1){
					game_flag["��װǽ"]=true;
					if(POS.ist.player==lst_see_time&&POS.update_light()) pos_affect_light.push(pos);//��αװ��ǽ���¹��� 
				}
				else{
					game_flag["������"]=true;
					if(POS.ist.player==lst_see_time) pos_change.insert(pos);
				}
			}
			position_3D ghost_instant_pos(position_3D pos,special_attribute &spat){//Χ��pos����˲��
				position_3D npos;
				int d=RAND(spat.ins.dis,1),dx=RAND(d,1)*(RAND(1,0)*2-1),dy=RAND(d,1)*(RAND(1,0)*2-1);//ƫ���� 
				//��ͬ�����˲�Ƹ�����ͬ 
				if(RAND_BOOL(50)) dx=(d-abs(dy))*(RAND(1,0)*2-1);
				else dy=(d-abs(dx))*(RAND(1,0)*2-1);
				npos.x=pos.x+dx;npos.y=pos.y+dy;npos.z=pos.z;//�µ����꣨����˲�Ƶ�¥�£� 
				if(npos.x<=1) npos.x=2;
				else if(npos.x>=length) npos.x=length-1;
				if(npos.y<=1) npos.y=2;
				else if(npos.y>=width) npos.y=width-1;//��ֹ������ͼ��Χ 
				return npos;
			}
				bool player_grid(int angle){//������angle�ĸ��Ƿ���Ч 
					return player1.color==4&&game_timer["���ͼ����˸"]>game_time&&sub_angle(angle,player1.angle)<=20;
				}
			void ghost_attack(int id,string s){//Ŀǰֻ�й�����ң�ר����Ը���
				if(id<0||id>=ghosts.size()) return; 
				ghost &gt=ghosts[id];
				special_effect &spe=gt.spe;
				vertigo &vtg=spe.vtg;//ѣ�� 
				MAP &POS=game_map[gt.pos.x][gt.pos.y][gt.pos.z];
				thing &THING=POS.things;
				MAP &PPOS=game_map[player1.pos.x][player1.pos.y][player1.pos.z];
				int door_d=atd(calc_angle(player1.pos,gt.pos)),door_d2=turn(door_d,TURN_BACK,4,14);//���� 
				bool hit_around=count_around_pos(gt.pos,4,player_here)
				&& !closed_box_here(player1.pos,door_d) && !closed_box_here(gt.pos,door_d2);
				bool change_z=false;//�ܷ��¥�㹥�� 
				if(gt.pos.x==player1.pos.x&&gt.pos.y==player1.pos.y){//�п��ܿ�¥�� 
					if(stair_here(gt.pos)){//��¥�� 
						position_3D npos=gt.pos;
						if(upstair_here(gt.pos)) npos.z++;
						else npos.z--;
						if(npos==player1.pos) change_z=true;
					}
					else if(nest_here(gt.pos)){//�߳�Ѩ 
						position_3D npos=POS.things.nst.to;
						if(npos==player1.pos) change_z=true;
					}
					//�������𣿣�ע������¥/������Ѩ�ڵ������
				}
				change_z=change_z and !box_here(player1.pos);
				bool atk=(PPOS.ist.other==lst_see_time&&PPOS.see(GHOST,gt.spat.attack)&&POS.see_fr()//���ü��Ŵ� 
					&&(hit_around||change_z)&&!vtg.exist())//ûѣ��
					&&!(THING.lsr.exist||POS.fcmv.lock);//û���������л��߳�ȥ 
				//ȷ������������
				if(atk){
					if(game_timer[s+"�ɴ����"]==0) game_timer[s+"�ɴ����"]=game_time;
					//������Թ�����ά��������ǰ����ɹ�����ʱ��� 
				}
				else game_timer[s+"�ɴ����"]=0;//�������� 
				//��¼ʱ�� 
				double atk_t=gt.attack_time;
				int angle_ghost_player=calc_angle(gt.pos,player1.pos);//��->��ҷ���� 
				if(spe.wks.exist()){//���� 
					atk_t*=1.5;//������Ĺ����ٶ� 
					limit_double(atk_t,0.0,0.5);//��ֹԽ�� 
				}
				//if(gt.goal!=pos000&&(gt.d+3)%4*90==angle_ghost_player) atk_t=0;//��������׼�˾����뷴 
				int react_time=atk_t*gt.vlc.wait_time*((gt.d+3)%4*90==angle_ghost_player?1.0:2.0);//��Ӧʱ�䣨ms�� 
				//����������͵�ǰ����ͬ����Ӧʱ���ӳ� 
				if(gt.spat.attack==INSTANT) react_time*=(100-gt.spat.ins.p)/100.0;
				//˲�ƹ�ķ�Ӧʱ������ 
				if(game_timer[s+"�ɴ����"]+react_time<=game_time//��Ӧʱ�仹û�� 
				&&RAND_BOOL(100)&&atk){//��һ������ 
					int angle=(RAND(45,-45)+angle_ghost_player+360)%360;
					if(change_z) angle=RAND(359,0);
					//����¥/������Ѩ�� ����Ҵ� 
					double force=0,hurt_rate=0;//���������˺�ϵ�� 
					if(RAND_BOOL(50)&&!box_here(player1.pos)){//�߷ɣ����Ӳ��ߣ� 
						force=15.0;
						hurt_rate=0.3;
						if(player_grid((angle_ghost_player+180)%360)) force*=0.2,hurt_rate*=0.2;//������80%
						if(!change_z) throw_thing(gt.pos,2.5*PPOS.mass()/POS.mass(),0,(angle+180)%360,MP(GHOST,id));
						//����������¥�㹥��ʱ�����ǣ� 
					}
					else{//ȭ�� 
						force=10.0;
						hurt_rate=0.2;
					}
					throw_thing(player1.pos,force/PPOS.mass(),hurt_rate,angle,MP(GHOST,id));//����������������ϵ� 
					
					game_timer[s+"�ɴ����"]=game_time+gt.vlc.wait_time;
					//��ȴʱ�� 
				}
				double dis1=NED_p3(gt.pos,player1.pos),dis2=NED_p3(gt.goal,gt.pos),dis3=NED_p3(player1.pos,gt.goal);
				if(game_timer[s]<=game_time&&POS.ist.other==lst_see_time&&dis1<=10&&dis1>=4&&!POS.fcmv.lock
				&&RAND_BOOL(30)){
					double v=15,v2=1;
					int nohurt_time=(v-v2)*1000;//v0,vt=1,a=1->t=(v0-vt)/a 
					gt.rampage=true;//gt.lfin.no_hurt=game_time+nohurt_time;//��ֹ�˺� 
					throw_thing(gt.pos,v,0,calc_angle(gt.pos,player1.pos),MP(GHOST,id)); 
				}
			}
			void shut_door(position_3D pos,position_3D who,PII from){//ˤ�ŵ��˼����� 
				int angle=calc_angle(who,pos);
				direction dir=ptp(pos,who);
				int d1=dir.d1,d2=dir.d2;
				if(d1!=-1){
					position_3D u=dtp3(pos,d1,4);
					MAP &POS=game_map[u.x][u.y][u.z];
					if(!nobody_here2(u)&&!box_here(u)){//����ˤ���������� 
						throw_thing(u,10.0/POS.mass(),0.3,angle,from);
					}
				}
				if(d2!=-1){
					position_3D u=dtp3(pos,d2,4);
					MAP &POS=game_map[u.x][u.y][u.z];
					if(!nobody_here2(u)&&!box_here(u)){//����ˤ���������� 
						throw_thing(u,10.0/POS.mass(),0.3,angle,from);
					}
				}
			} 
		void deal_ghost(){
			logMessage("deal_ghost"); 
			int ghost_num=Qghost_hurt.size();
			while(ghost_num>0){
				ghost_num--;
				int id=Qghost_hurt.front();Qghost_hurt.pop();
				logMessage("Qghost_hurt id="+int_to_str(id)); 
				if(id<0||id>=ghosts.size()) continue;
				ghost &gt=ghosts[id];
				life_injury &lfin=gt.lfin;
				MAP &POS=game_map[gt.pos.x][gt.pos.y][gt.pos.z];
				string s="��"+int_to_str(id);
				if(!gt.update){//ֻҪ������������
					gt.update=true;
					Qghost.push(id);
				}
				thing &THING=POS.things;
				special_attribute &spat=gt.spat;
				int &att=spat.attack,&def=spat.defense;
				if((THING.lsr.exist||THING.drt.exist1())&&game_timer[s+"������"]<=game_time
				||(THING.spr.exist&&game_timer[s+"��ì����"]<=game_time)){ //1000������ʱ�ѵ� 
					if(!spat.can_evade()){//û������ 
						player1.scr.shoot_hit_times++;
						ghost_reduce_blood(id,5*THING.lsr.exist+1.5*THING.drt.num[1]+0.5*THING.spr.exist,MP(PLAYER,-1));
						//�����˺�5.0 �����˺�1.5 ��ì�˺�0.5 
						game_timer[s+"������"]=game_time+500;//0.5s��ʱ��ֹ�����ظ��ж�
						game_timer[s+"��ì����"]=game_time+1000;//1.0s��ʱ 
					}
					else{
						spat.eva.use=true;
						if(POS.ist.player==lst_see_time){//��ʾ������ 
							game_flag["���˱���ҹ���"]=true;
							pos_change.insert(gt.pos);
						}
					}
				}
				if(POS.fcmv.lock&&game_timer[s+"������"]<=game_time&&!gt.rampage){//��������û�д����� 
					if(POS.fcmv.speed()>5){//�ٶȴ���5ÿ���ܵ�1���˺� 
						ghost_reduce_blood(id,1,POS.fcmv.from);
						game_timer[s+"������"]=game_time+500;
					}
				}
				special_effect &spe=gt.spe;
				methysis &mts=spe.mts;
				if(mts.exist()&&mts.t+mts.T<=game_time){//�ж���Ѫ 
					mts.t=game_time;
					ghost_reduce_blood(id,mts.x,mts.from);
				}
				skill_disappear &disa=spat.disa;
				if(lfin.change!=0&&spat.attack==DISAPP&&lfin.life<10){//������������ֵ��ֹͣ���� 
					disa.use=false;
					disa.time=game_time+RAND(20000,10000);
					if(POS.ist.player==lst_see_time) ghost_disappear_print(gt.pos,disa.kind);
				}
				if(lfin.life<=0){//����ۼ� ghost_here(gt.pos)&&POS.emy.id>=0&&
					logMessage("lfin.life<=0"); 
					if(POS.ist.player==lst_see_time){
						game_flag["���˱���ҹ���"]=true; 
						pos_change.insert(gt.pos);
						pos_dead.push(gt.pos);
					}
					if(gt.pos!=pos000){
						message_box.push(MP(lfin.last_injury_from,MP(GHOST,id)));//��ɱ��Ϣ 
						gt.pos=pos000;
						if(lfin.last_injury_from.first==PLAYER){
							player1.scr.kc.update(1,GHOST);
							player_kill_reward(gt.pos,GHOST,gt.spat);
						}
					}
					POS.fcmv.lock=false;//game_flag["��"]=true;pos_change.insert(gt.pos);//������� 
					POS.emy.dead=true;POS.emy.body_disapp=game_time+400;
					POS.player_enemy=NOBODY;POS.emy.id=-1;
					ghost_move_away(id);
				}
				game_timer["��"]++;
			}//ѭ��1����������ѭ�� 
			ghost_num=Qghost.size();
			while(ghost_num>0){
				ghost_num--;
				int id=Qghost.front();Qghost.pop();
				logMessage("Qghost id="+int_to_str(id)); 
				if(id<0||id>=ghosts.size()) continue;
				ghost &gt=ghosts[id];
				life_injury &lfin=gt.lfin;
				special_effect &spe=gt.spe;
				MAP &POS=game_map[gt.pos.x][gt.pos.y][gt.pos.z];
				string s="��"+int_to_str(id);
				if(gt.change_pos){
					Qghost.push(id);
					ghost_move_away(id);
					continue;
				}
				if(MHT_DIST2(gt.pos.x,gt.pos.y,(gt.pos.z>height?gt.pos.z-height:gt.pos.z),player1.pos.x,player1.pos.y,player1.pos.z)>100
				&&POS.ist.player<lst_see_time)//����Ҿ��볬��100��ע�ⳲѨ�߶ȣ�����ҿ����� 
					gt.update=false;//ֹͣ���� 
				if(lfin.life<=0){//ûѪ�˾ͼ������ 
					Qghost_hurt.push(id);
					gt.update=false;//ֹͣ���� 
				}
				if(gt.spe.exist()) Qghost_hurt.push(id);//����Ч���ͼ������ 
				if(!gt.update) continue;//�������˾��������� 
				Qghost.push(id);
				thing &THING=POS.things;
				special_attribute &spat=gt.spat;
				skill_vampire &vpr=spat.vpr;
				skill_through &thr=spat.thr;
				skill_disappear &disa=spat.disa;
				spat.eva.use=false;
				switch(spat.attack){//�г���ʱ��ļ��ܸ��� 
					case VAMPIRE:
						if(POS.burn_vampire()&&thr.time<=game_time){
							ghost_reduce_blood(id,0.1*POS.brightness,MP(GHOST,id));
							thr.time=game_time+1000;//ÿ�����һ�������˺� 
						}
						break;
					case THROUGH:
						if(thr.time<=game_time){
							thr.time+=10000;//ÿʮ�뿪��һ�δ�ǽ���ܣ�����ʮ�� 
							thr.use=!thr.use;
						}
						break;
					case DISAPP:
						if(disa.time<=game_time){
							if(!disa.use&&disa.kind==1&&POS.ist.other==lst_see_time
							&&game_map[player1.pos.x][player1.pos.y][player1.pos.z].see(GHOST,gt.spat.attack)&&POS.see_fr())
								disa.time=game_time+RAND(4000,2000);//������ʱ���л�Ϊ����
							else{
								disa.use=!disa.use;
								if(disa.use) disa.time=game_time+RAND(disa.maxt,disa.maxt/2);
								else disa.time=game_time+RAND(3000,1000);
								if(POS.ist.player==lst_see_time) ghost_disappear_print(gt.pos,disa.kind);
							} 
						}
						break;
				}
				force_move &FCMV=POS.fcmv;
				if(gt.rampage&&(FCMV.lock?not(FCMV.from==MP(int(GHOST),id)):1)) gt.rampage=false;//�����𲽽��� 
				double atktime=gt.attack_time;
				ghost_attack(id,s);//���˹���ʱ��
				if(game_timer[s]>game_time)//ʱ��û�����ƶ� 
					continue;
				int wait_time=gt.vlc.wait_time;
				if(spat.attack==INSTANT&&RAND_BOOL(spat.ins.p))//����˲�Ƽ���
					wait_time=0;
				else if(gt.goal!=pos000) wait_time/=5;//�ٶ�*5 
				game_timer[s]=game_time+wait_time; 
				game_timer["��"]++;
				if(!(THING.lsr.exist||THING.drt.exist1()||THING.spr.exist)
				&&game_timer[s+"������"]<=game_time&&game_timer[s+"��ì����"]<=game_time){//Ҫ������һһ��Ӧ 
					if(lfin.change!=0&&POS.ist.player==lst_see_time){
						game_flag["���˱���ҹ���"]=true; 
						pos_change.insert(gt.pos);
					}
					lfin.change=0;
				}
				if(THING.lsr.exist||POS.fcmv.lock){
					if(FCMV.lock&&(spat.defense==ROCK||spat.defense==SHIELD)){
						int k=spat.rck.k;
						FCMV.init3(FCMV.vx.speed*k,FCMV.vy.speed*k);
						if(FCMV.speed()<=1) FCMV.init();
						spat.rck.use=true;//��ļ��� 
					}
					else spat.rck.use=false;
					continue;//���������л򱻻����޷��ƶ��͹��� 
				}
				else spat.rck.use=false;
				if(spat.can_disappear()&&disa.kind==1) continue;//����״̬��αװ��ǽ���ƶ� 
				spider_net &SNT=THING.snt;
				SNT.addedc(-20,gt.pos);//��֩���� 
				if(SNT.endurance>50+25)//�ȼ������ж� 
					continue;//��֩����ճס 
				weakness &wks=spe.wks;
				vertigo &vtg=spe.vtg;
				if(wks.exist()&&RAND_BOOL(wks.x*8)){
					if(POS.ist.player==lst_see_time) pos_change.insert(gt.pos);
					continue;//����������ж���ɿ��� 
				}
				position_3D npos=gt.pos;
				int d=gt.d;
				ghost_turn(d,id); 
				bool use_instant=false;
				if(spat.attack==INSTANT//��˲�� 
				&&count_around_pos(gt.pos,4,spider_here)+count_around_pos(gt.pos,4,flying_thing_here)>=1){
				//���ȿ��Ƕ��֩�롢�ɹ����Ķ��� 
					logMessage("instant1"); 
					npos=ghost_instant_pos(gt.pos,spat);
					int cnt=10;//�����10�Σ����˾Ͳ�����
					while(cnt>0&&!ghost_through(gt.pos,npos,-1,spat.can_through())){//����˲�Ƶ�npos�ͻ�һ�� 
						npos=ghost_instant_pos(gt.pos,spat);
						cnt--;
					}
					use_instant=true;
					d=4;
				}
				else if(spat.attack==INSTANT&&RAND_BOOL(spat.ins.p)//��˲�� 
				&&POS.ist.player<lst_see_time){
					logMessage("instant2"); 
					npos=ghost_instant_pos(gt.pos,spat);
					use_instant=true;
					d=4;
				}
				else if(spat.attack==INSTANT&&(MHT_DIST_p3(gt.pos,player1.pos)<spat.ins.dis*2)
				&&RAND_BOOL(spat.ins.p)){//˲�Ƶ�����Ա� 
					logMessage("instant3"); 
					npos=ghost_instant_pos(player1.pos,spat);
					use_instant=true;
					d=4;
				}
				else if(d==4){ 
					if(stair_here(npos)){//����¥
						logMessage("stair"); 
						if(game_map[npos.x][npos.y][npos.z].maze==UPSTAIR) npos.z++;
						else npos.z--;
					}
					else if(POS.things.nst.exist){//����Ѩ��
						logMessage("nest"); 
						position_3D npos2=POS.things.nst.to;
						MAP &POS2=game_map[npos2.x][npos2.y][npos2.z];
						npos.x=npos2.x;npos.y=npos2.y;npos.z=npos2.z;//�ƶ�����Ӧ�ĳ�Ѩ��
					}
				}
				else{//��ͨ�ƶ� 
					logMessage("normal d="+int_to_str(d)); 
					npos.x+=dx4[d];
					npos.y+=dy4[d];
				}
				MAP &NPOS=game_map[npos.x][npos.y][npos.z];
				thing &NTHING=NPOS.things;
				if(npos!=gt.pos//��ֹ˲�ƹ����� 
				&&ghost_through(gt.pos,npos,d,spat.can_through())){
					logMessage("move"); 
					if(NTHING.mvb.exist&&!NPOS.fcmv.lock&&d<4){//��һ���У������Ƶģ�����
						push_thing(npos,d,1);//�ƶ���Ʒ 
						position_3D u=dtp3(npos,d,4);//��ʱ��Ʒ���ڵ�λ��
						MAP &MPOS=game_map[u.x][u.y][u.z]; 
						thing &MTHING=MPOS.things; 
						if(MTHING.mvb.kind!=BOX&&!wks.exist()//����ʱ�Ӳ��˶��� 
						&&RAND_BOOL(POS.ist.other==lst_see_time&&POS.see(GHOST,gt.spat.attack)&&POS.see_fr()?40:20)){//�и����ӳ�ȥ���������ʱ���ʸ��� 
							int angle=calc_angle(gt.pos,player1.pos),angle2=(d+3)%4*90;//angle:������� angle2:����ǰ���� 
							if(vtg.exist()) angle=RAND(359,0);//ѣ��ʱ�����Ӷ��� 
							if((angle-angle2+360)%360>90&&(angle2-angle+360)%360>90) angle=angle2;//�����Լ����� 
							throw_thing(u,15.0/MPOS.mass(),0,angle,MP(GHOST,id));
							throw_thing(gt.pos,2.5*MPOS.mass()/POS.mass(),0,(angle+180)%360,MP(GHOST,id));//������ 
						}
					}
					POS.player_enemy=NOBODY;POS.emy.id=-1;
					NPOS.player_enemy=GHOST;NPOS.emy.id=id;
					if(POS.ist.player==lst_see_time&&gt.pos.z==player1.pos.z){
						player1.enemy_move=true;
						pos_change.insert(gt.pos);
						if(THING.crt.exist){
							game_flag["����ҡ��"]=true;
							if(POS.update_light()&&POS.ist.player==lst_see_time) pos_affect_light.push(gt.pos);//���Ӷ��˹��ո��� 
						}
					}
					if(NPOS.ist.player==lst_see_time&&npos.z==player1.pos.z){
						player1.enemy_move=true;
						pos_change.insert(npos);
						if(NTHING.crt.exist){
							game_flag["����ҡ��"]=true;
							if(NPOS.update_light()&&POS.ist.player==lst_see_time) pos_affect_light.push(npos);//���Ӷ��˹��ո��� 
						}
					}
					if(NTHING.snt.exist()) vibrate_spider_net(npos,20*1000);//��֩���� 
					light &NLGT=NTHING.lgt;
					if(NLGT.exist&&NLGT.state==0&&NPOS.brightness+NLGT.p<-10
					&&!(spat.attack==VAMPIRE||spat.can_disappear())){//��Ѫ����������������� 
						NLGT.state=1;//���ŵĵ���������������¿��Դ� 
						pos_affect_light.push(npos);//�ƿ��˹��ո���
					}
					gt.pos=npos;
				}
				else if(npos!=gt.pos){//��ֹ˲�ƹ����� 
					logMessage("block"); 
					int rev_d=(d<4?turn(d,TURN_BACK):0);//d�ķ����� 
					if(d<4&&closed_box_here(gt.pos,d)){
						if(POS.ist.player==lst_see_time&&MHT_DIST_p3(player1.pos,gt.pos)<=2&&gt.pos.z==player1.pos.z
						//������Ҳ���ͬһ¥�㡢����Ͻ� 
						||lfin.change==2){
						//�����⵽���� 
							THING.mvb.door[d]=1;//�������Ӵ��� 
							if(POS.ist.player==lst_see_time) game_flag["����"]=true;
							if(POS.update_light()) pos_affect_light.push(gt.pos);//���ո���
						}
					}
					else if(d<4&&closed_box_here(npos,rev_d)){
						NTHING.mvb.door[rev_d]=1;//��ǰ���Ӵ���
						if(NPOS.ist.player==lst_see_time) game_flag["����"]=true;
						if(NPOS.update_light()) pos_affect_light.push(npos);//���ո���
					}
					else if(d==4&&!box_here(gt.pos)&&!box_here(npos)||d<4){
						int angle=(d+3)%4*90;
						int angle2=(d<4?(RAND(90,-90)+angle+360)%360:RAND(359,0));
						if(door_here(npos,2)){
							NTHING.kdr.state=1;
							shut_door(npos,gt.pos,MP(GHOST,id));//����ˤ�� 
							if(NPOS.update_light()) pos_affect_light.push(npos);//�ſ��˹��ո���
							if(NPOS.ist.player==lst_see_time) game_flag["����"]=true;//������Ұ���� 
						}
						else if(NTHING.mvb.exist&&NTHING.mvb.kind!=BOX
						&&RAND_BOOL(50+max(0,20-MHT_DIST_p3(player1.pos,npos)))){//�Ӷ��� 
							throw_thing(npos,15.0/NPOS.mass(),0,angle2,MP(GHOST,id));
							throw_thing(gt.pos,2.5*NPOS.mass()/POS.mass(),0,(angle2+180)%360,MP(GHOST,id));//������ 
						}
						else if(NTHING.windows.exist){
							window &WDN=NTHING.windows;
							WDN.damage(20,npos); 
						}
						int door_d=(d==4?0:turn(d,TURN_BACK,4,15));//����
						if(!vtg.exist()){//ѣ��ʱ�޷�����
							//�ƶ��ܵ��谭�Ĺ���
							/* ����ҵ���ʱȡ�� 
							if(NPOS.player_enemy==PLAYER&&!use_instant&&NPOS.see(GHOST,gt.spat.attack)&&POS.see_fr()
							&&!(d==4?box_here(npos):closed_box_here(npos,door_d))){
								//�����š�������Ź��� 
								player_reduce_blood(5.0/gt.vlc.speed,MP(GHOST,id));
								if(spat.attack==VAMPIRE) ghost_reduce_blood(id,-1);//����Ѫ
							}
							else*/ 
							if(enemy_here(npos)){//����Ӻ�֩�룬�������� 
								if(!use_instant&&(bug_here(npos)||spider_body_here(npos))){//Ҫ�ų���˲��������� 
									throw_thing(npos,15.0/NPOS.mass(),0.3,angle,MP(GHOST,id));
									throw_thing(gt.pos,2.5*NPOS.mass()/POS.mass(),0,(angle+180)%360,MP(GHOST,id));//������ 
								}
								update_being(npos);
							} 
						}
					}
				}
				gt.d=d;
			}//ѭ��2������ѭ�� 
		}
	void deal_enemy(){
		logMessage("deal_enemy()",2);
		deal_bug();
		deal_spider();
		deal_ghost();
	}
				void player_erase_flashlight(){//�����ϴ��ֵ�Ͳ���������򲢸����ֵ�Ͳ����Ϣ 
					flashlight &flt=player1.items.flt;
					queue<pair<position_3D,int> > &lst=flt.lst;
					while(!lst.empty()){
						pair<position_3D,int> x=lst.front();lst.pop();
						position_3D u=x.first;
						int sub=x.second;
						game_map[u.x][u.y][u.z].brightness-=sub;
					}
				}//ÿ�������Ұ����ǰ������ã� 
				void player_update_flashlight(position_3D pos){//����ֵ�Ͳ�յ�posλ�� 
					bool state=player1.items.flt.state;
					if(!state) return;//���˾Ͳ������� 
					int tmp=player1.angle;//��ҷ����Ӧ�ķ���� (player1.d2+3)%4*90
					flashlight &flt=player1.items.flt;
					queue<pair<position_3D,int> > &lst=flt.lst;
					int add=pos_to_brightness2(player1.pos,pos,flt.p,tmp,flt.angle);//�ֵ�Ͳ���� 
					if(add>0){
						game_map[pos.x][pos.y][pos.z].brightness+=add;
						lst.push(make_pair(pos,add));//�����´θ������� 
					}
				}
				void calculate_vision(position_3D pos,vector<position_3D> &ret,int dir,bool mir,bool pl_ot,int mx_dis){//������posλ����d���򿴵���Ұ
					//ֻ�����ܿ����ĵط����������κ���Ұ���µı�� 
					//pl_ot��0�� 1���  mx_dis����Զ���루�����٣� 
					ret.clear();//��� 
					int cnt=player1.spe.xry.num;//͸�� 
					position_3D npos=pos;
 					int door_d=turn(dir,TURN_BACK);
 					do{
						npos=dtp3(npos,dir,4);
						if(!pos_in_area2(npos.x,npos.y,1,1,length,width)) return;
						//������ͼ��Χ�Ϳ���ֱ��������
						if(MHT_DIST_p3(npos,pos)>mx_dis) return;
						//�������� 
						MAP &POS=game_map[npos.x][npos.y][npos.z];
						/*
						if(POS.ist.player<game_time){
							if(!screen_pos.count(position_3Dtoscr(npos))) pos_in_sight.push(npos);
							//��ҿ��ü��ĸ������
							screen_z[position_3Dtoscr(npos)]=npos.z;//�޸���Ļ�����λ��������¥�㣨����֮ǰ�� 
							if(pl_ot) POS.ist.player=game_time;//�����Ϸ��ͼ
							else if(!mir&&cnt==player1.spe.xry.num) POS.ist.other=game_time;
							update_being(npos);//�������� 
						}*/
						if(pl_ot||!mir&&cnt==player1.spe.xry.num) ret.push_back(npos);
						if(light_through2(npos,door_d,pl_ot+1)){
							int d1=turn(dir,TURN_LEFT),d2=turn(dir,TURN_RIGHT);
							position_3D pos1=dtp3(npos,d1,4),pos2=dtp3(npos,d2,4);
							/*
							if(game_map[pos1.x][pos1.y][pos1.z].ist.player<game_time){
								pos_in_sight.push(pos1);
								screen_z[position_3Dtoscr(pos1)]=pos1.z;
								if(pl_ot) game_map[pos1.x][pos1.y][pos1.z].ist.player=game_time;
								else if(!mir) game_map[pos1.x][pos1.y][pos1.z].ist.other=game_time;
							}*/
 							if(pl_ot||!mir) ret.push_back(pos1);
							/*
							if(game_map[pos2.x][pos2.y][pos2.z].ist.player<game_time){
								pos_in_sight.push(pos2);
								screen_z[position_3Dtoscr(pos2)]=pos2.z;
								if(pl_ot) game_map[pos2.x][pos2.y][pos2.z].ist.player=game_time;
								else if(!mir) game_map[pos2.x][pos2.y][pos2.z].ist.other=game_time;
							}*/
 							if(pl_ot||!mir) ret.push_back(pos2);
							if(POS.things.mirrors.exist){ 
								mirror &MIRROR=POS.things.mirrors;
								int d1=turn(dir,TURN_LEFT),d2=turn(dir,TURN_RIGHT),d3=MIRROR.dir;
								int mx_dis2=mx_dis-MHT_DIST_p3(pos,npos);//�¾��� 
								if(MIRROR.side==1){
									if(dir==d3) calculate_vision(npos,ret,d2,1,pl_ot,mx_dis2);
									else if(d2==d3) calculate_vision(npos,ret,d1,1,pl_ot,mx_dis2);
								}
								else{
									if(dir%2==d3) calculate_vision(npos,ret,d2,1,pl_ot,mx_dis2);
									else calculate_vision(npos,ret,d1,1,pl_ot,mx_dis2);
								}
							}
						}
						else{
							int d1=turn(dir,TURN_LEFT),d2=turn(dir,TURN_RIGHT),d3=turn(dir,TURN_BACK);
							position_3D pos1=dtp3(npos,d1,4),pos2=dtp3(npos,d2,4),pos3=dtp3(pos1,d3,4);
 							if(light_through2(pos3,door_d,pl_ot+1)&&(pl_ot||!mir)) ret.push_back(pos1);
							pos3=dtp3(pos2,d3,4);
 							if(light_through2(pos3,door_d,pl_ot+1)&&(pl_ot||!mir)) ret.push_back(pos2);
						}
						if(!light_through2(npos,door_d,pl_ot+1)) cnt--;
					}while(cnt>0);//���߿��Դ����ͼ������㣨���ٻῴ��һ�����ӣ�
				}
			void player_calculate_vision1(int d){//������ҵ���Ұ
				//if(block_light(pos)) return;//���λ�õĶ�����סȫ����Ұ 
				MAP &POS=game_map[player1.pos.x][player1.pos.y][player1.pos.z];
				if(POS.ist.player<game_time){//��ֹ�ظ��˷�ʱ�� 
					if(!screen_pos.count(position_3Dtoscr(player1.pos)))//��Ļ�����λ��û����ʾ����
						pos_in_sight.push(player1.pos);//���������ڵ�λ�á����
					screen_z[position_3Dtoscr(player1.pos)]=player1.pos.z;//�޸���Ļ�����λ��������¥��
					POS.ist.player=game_time;
					if(!block_light(player1.pos)) POS.ist.other=game_time;
					player_update_flashlight(player1.pos);
				}
				vector<position_3D> ret;
				if(d!=-1){
					//�����Ұ��������㣨���������赲����ֻ����ǰ������� 
					int mx_dis=(player1.spe.bds.exist()?player1.spe.bds.vision_dis:INF);//��Ұ������ 
					calculate_vision(player1.pos,ret,d,0,1,mx_dis);//��� 
					for(int i=0;i<ret.size();i++){
						position_3D u=ret[i];
						MAP &UPOS=game_map[u.x][u.y][u.z];
						if(UPOS.ist.player<game_time){//��ֹ�ظ��˷�ʱ�� 
							pos_in_sight.push(u);
							screen_z[position_3Dtoscr(u)]=u.z;
							game_map[u.x][u.y][u.z].ist.player=game_time;//��� 
							player_update_flashlight(u);//�ֵ�Ͳ���յ����� 
	 						update_being(u);//�������� 
	 					}
					}
				}
				for(int i=0;i<4;i++){//ö��4���� 
					if(closed_box_here(player1.pos,i)) continue;//���λ�õĶ�����ס���˴˷�����Ұ 
					calculate_vision(player1.pos,ret,i,0,0,INF);//���� 
					for(int j=0;j<ret.size();j++){
						position_3D u=ret[j];
						//���ظ����pos_in_sight��screen_z 
						MAP &UPOS=game_map[u.x][u.y][u.z];
						if(UPOS.ist.other<game_time){//��ֹ�ظ��˷�ʱ�� 
							game_map[u.x][u.y][u.z].ist.other=game_time;//���� 
							update_being(u);//�������� 
						}
					}
				}
			}
				void vision_init(int k,vector<PII > v,vector<position_3D> &ret,position_3D pos){//ÿ�μ���ǰ���ã�k��͸�ӣ� 
					for(int i=0;i<4;i++) cnt_visible[i]=0;
					memset(occlusion,0,sizeof(occlusion));
					for(int i=0;i<4;i++){
						for(int j=v[i].first;j!=v[i].second;j=(j+1)%360){//a~b 0=>b+1~a-1 1
							occlusion[i][j]=k;
							cnt_visible[i]++;
						}
						occlusion[i][v[i].second]=k;
						cnt_visible[i]++; 
					}
					/*
					if(pos!=pos000&&block_light(pos)){//��ʼλ���ж����ڵ���Ұ 
						movable &MVB=game_map[pos.x][pos.y][pos.z].things.mvb;
						position_3D u[4];
						u[0]=u[1]=u[2]=u[3]=pos;
						for(int i=0;i<4;i++) u[i].x+=(i&1),u[i].y+=(i&2);//��ʼλ���ĸ���� 
						int tmp[4][4]={{0,1,2,3},{1,3,0,2},{3,2,0,1},{2,0,1,3}};//tmp[i][0,1]Ϊ�ڵ��㣬[2,3]Ϊ����� 
						for(int i=0;i<4;i++)//��ǰ���ŷ��� 
							if(MVB.door[i]==0)
								for(int j=2;j<4;j++){//�ĸ������
									int p=tmp[i][j],q=tmp[i][0],r=tmp[i][1];
									int a=calc_angle(u[p],u[q]);
									int b=calc_angle(u[p],u[r]);
									if(cmpa(b,a)) swap(a,b);
									mark_lose_sight_area(p,a,b);
									//�������ĵ�
									a=calc_angle(u[p],u[q]);b=calc_angle(u[q],u[p]);
									int c,d;
									c=d=(i+3)%4*90;//�ص�����ڵ����� 
									if(cmpa(c,a)) swap(a,c);
									mark_lose_sight_area(q,a,c);
									if(cmpa(d,b)) swap(b,d);
									mark_lose_sight_area(r,b,d);
									//�����ĵ� 
								}
					}*/
					memset(vague,0,sizeof(vague));//ȫ����� 
					ret.clear();//ʹ��ǰ��� 
				}
				void calculate_vision2(position_3D pos,int pl_ot,vector<position_3D> &ret,int mx_dis,bool vague){
					//��posΪ��Դ�������/��Ұ��Χ��ͬһ�㣩 
					//ret����Χ�ڵ�λ�� pl_ot=0��͸������ 1����͸������ �������Ǽ���/��ͨ�⣩ vague���Ƿ����ģ��ֵ 
					//����mx_dis�Ͳ������� 
					//���ӵ��Ľǣ�(x,y)->0,(x+1,y)->1,(x,y+1)->2,(x+1,y+1)->3 
					//vision_init�����ɣ�if(block_light(pos)) return;//���λ�õĶ�����סȫ����Ұ �� 
					int x=pos.x,y=pos.y,z=pos.z;
					memset(vst,0,sizeof(vst));
					while(!Q.empty()) Q.pop();
					vst[x][y][z]=1;
					ret.push_back(pos); 
					Q.push(pos);
					if(block_light(pos)){//��ʼλ���ж����ڵ���Ұ 
						movable &MVB=game_map[pos.x][pos.y][pos.z].things.mvb;
						for(int d=0;d<4;d++){
							position_3D u=dtp3(pos,d,4);
							if(MVB.door[d]==0) mark_occlusion(u,pos,0);//������ת��Ϊһ�����鴦�� 
						}
					}
					while(!Q.empty()&&(cnt_visible[0]||cnt_visible[1]||cnt_visible[2]||cnt_visible[3])){
						position_3D u=Q.front();Q.pop();
						movable &UMVB=game_map[u.x][u.y][u.z].things.mvb;
						for(int i=0;i<4;i++){
							position_3D v=u;v.x+=dx4[i];v.y+=dy4[i];
							MAP &POS=game_map[v.x][v.y][z];
							movable &MVB=POS.things.mvb;
							if(!pos_in_area2(v.x,v.y,1,1/*,200,200,������Ե����Ұ*/,length,width)
							||vst[v.x][v.y][z]
							||NED_p3(pos,v)>mx_dis//������Զ����Ҳ���У�ŷ����þ��룩
							)//u�������赲 ||box_here(u)&&UMVB.door[i]==0
								continue;
							//||box_here(v)&&MVB.door[turn(i,TURN_BACK)]==0 v���������������赲 
							vst[v.x][v.y][z]=1;
							if(invisible(pos,v)) continue;
							ret.push_back(v);
							if(vague)//�ȼ���ģ��Ч��
								calc_mark_vague(v,pos);//����v����Ұ��Ϣ��ģ��ֵ�������v���ģ�����һ�� 
							if(!light_through(v,pl_ot)) mark_occlusion(v,pos);//��0+1��͸�����ӣ���ң�1+1������  
							if(!invisible(pos,v)) Q.push(v); 
						}
					}
					game_timer["ѭ"]++;
				}
			void player_calculate_vision2(){//������Ұ�������ֵ�Ͳ 
				game_timer["see"]++;
				vector<PII > v(4);vector<position_3D> ret;
				int tmp=player1.angle;//��ҷ����Ӧ�ķ���� (player1.d2+3)%4*90
				for(int i=0;i<4;i++) v[i]=MP((tmp-120+360)%360,(tmp+120+360)%360);
				while(!pos_vague.empty()){//ÿ�μ��������Ұǰ������ϴ�ģ���ĵط� 
					position_3D pos=pos_vague.front();pos_vague.pop();
					MAP &POS=game_map[pos.x][pos.y][pos.z];
					memset(POS.ist.vague,0,sizeof(POS.ist.vague));//���� 
				}
				vision_init(player1.spe.xry.num,v,ret,player1.pos);
				position_2D scr_mouse=pos_mouse();//������Ļλ�� 
				position_3D map_mouse=position_scrto3D(scr_mouse,player1.pos.z);//���ĵ�ͼλ��
				int player_sight_dis=(player1.spe.bds.exist()?player1.spe.bds.vision_dis:NED_p3(map_mouse,player1.pos));
				//�����Ұ��Χ��ʧ��Ч�������λ�õ����� 
				calculate_vision2(player1.pos,2,ret,player_sight_dis,1);//��Ҳ�����Ұ 
				for(int i=0;i<ret.size();i++){//������player1.pos 
					position_3D pos=ret[i];
					MAP &POS=game_map[pos.x][pos.y][pos.z];
					thing &THING=POS.things;
					light &LGT=THING.lgt;
					if(POS.ist.player<game_time){//��ֹ�ظ��˷�ʱ�� 
						POS.ist.player=game_time;
						if(!screen_pos.count(position_3Dtoscr(pos))) pos_in_sight.push(pos);
						screen_z[position_3Dtoscr(pos)]=pos.z;
						update_being(pos); 
						player_update_flashlight(pos);
					}
					if(LGT.exist&&LGT.update) update_light_brightness(pos,0);//��Ұ��Χ�ڵƹ����� 
					if(POS.ist.vague_exist()) pos_vague.push(pos);//ģ����λ����ӣ��������� 
				}
				for(int i=0;i<4;i++) v[i]=MP(0,359);
				vision_init(1,v,ret,player1.pos);
				calculate_vision2(player1.pos,1,ret,INF,0);//�����ˣ�ȫ����Ұ 
				for(int i=0;i<ret.size();i++){
					position_3D pos=ret[i];
					MAP &POS=game_map[pos.x][pos.y][pos.z];
					thing &THING=POS.things;
					light &LGT=THING.lgt;
					if(POS.ist.other<game_time){//��ֹ�ظ��˷�ʱ�� 
						POS.ist.other=game_time;
						update_being(pos); 
					}
					if(LGT.exist&&LGT.update) update_light_brightness(pos,0);//��Ұ��Χ�ڵƹ�����
				}
			}
				void add_fog(position_3D pos,double r,double g,double b){//�������� 
					fog &FOGS=game_map[pos.x][pos.y][pos.z].things.fogs;
					FOGS.absorbance[0]+=r;
					FOGS.absorbance[1]+=g;
					FOGS.absorbance[2]+=b;
					FOGS.update=true;
					pos_fog.push(pos);
				}
				void player_have_food(int kind,int effect){
					if(kind==ADDS){
						player_reduce_blood(-(1<<(EFFECT_OF_FOOD-effect))*5,MP(PLAYER,-1));//��������ֵ 
						player1.items.num_change=true;
					}
					else{
						player_add_stg((1<<(EFFECT_OF_FOOD-effect))*10);//��������ֵ 
						player1.items.num_change=true;
					}
				}
				void player_use_ppt(int kind,int time){
					x_ray &xry=player1.spe.xry;
					xry.num+=kind;
					if(xry.time<=game_time) xry.time=game_time+time;
					else xry.time+=time;
					xry.change=true;
					game_flag["�����Ұ�����ı�"]=true;
				}
			void player_use_item(){//��ң���E��ʹ����Ʒ 
				MAP &POS=game_map[player1.pos.x][player1.pos.y][player1.pos.z];
				item &items=player1.items;
				weapon_carried wpn=items.wpn;
				vector<int> &v=items.item_lab;
				int x=items.select_number;
				if(x<0||x>=v.size()) return;
				int id=v[x];
				if(id<0) return;
				object &ob=objects[id];
				int k=ob.type;
				life_injury &lfin=player1.vts.lfin;
				strength &stg=player1.vts.stg;
				bool del=false;
				switch(k){
					case FOO:
						player_have_food(ob.foods.kind,ob.foods.effect);
						del=true;//������Ҫɾ�� 
						break;
					case SMO:
						add_fog(player1.pos,10000,10000,10000);
						del=true;//������Ҫɾ��
						break;
					case PER:
						player_use_ppt(ob.stp.kind,ob.stp.time);
						del=true;
						break;
					case LAS:case DAR:case SPE:case DAG:case SWO:case BLA:
						add_weapon(x);
						//�Զ��ֻ����� 
						break; 
				}
				if(del){
					del_object2(x);//�ǵ�ɾ�����˵���Ʒ 
				}
				player1.items.il_change=true;
			} 
							void damage_curtain(position_3D u,int hurt=1){
								MAP &POS=game_map[u.x][u.y][u.z];
								thing &THING=POS.things;
								curtain &CRT=THING.crt;
								CRT.endurance-=hurt;
								if(POS.ist.player==lst_see_time){
									game_flag["��Ʒ��"]=true;
									pos_change.insert(u);
								}
								if(CRT.endurance<=0){
									CRT.init();
									if(POS.update_light()) pos_affect_light.push(u);//����û�˸��¹��� 
									game_flag["��Ʒ��ʧ"]=true;
								}
							}
							bool laser_beam_through(position_3D pos,position_3D u,int angle){//��pos��������Ϊ��㣬����Ƕ�Ϊangle�������Ƿ񾭹�u
								pos.x=pos.x*2+1;pos.y=pos.y*2+1;
								int mn=-1,mx=-1;//��С/��� 
								for(int i=0;i<4;i++){
									position_3D v=u;v.x+=bool(i&1);v.y+=bool(i&2);//u���ӵ�ĳ���� 
									v.x*=2;v.y*=2;
									int a=calc_angle(pos,v);//������㵽����ǵķ���� 
									if(mn==-1||cmpa(a,mn)) mn=a;//a<mn
									if(mx==-1||cmpa(mx,a)) mx=a;//mx<a
								}
								return cmpa(mn,angle)&&cmpa(angle,mx);//����Ƕ��ڷ�Χ�� 
							}
							void make_laser_beam_brightness(position_3D pos,int p){
								vector<PII > v;vector<position_3D> ret;
								for(int i=0;i<4;i++) v.push_back(MP(0,359));
								vision_init(1,v,ret,pos);
								calculate_vision2(pos,1,ret,p,0);//mx_dis=p���Ƽ��㷶Χ����Լ���� 
								for(int i=0;i<ret.size();i++){
									position_3D u=ret[i];
									MAP &POS=game_map[u.x][u.y][u.z];
									thing &THING=POS.things;
									if(light_through(u,1)){
										int tmp=pos_to_brightness(pos,u,p);
										POS.brightness+=tmp;
										laser_beam_light.push(MP(u,tmp));//(������λ��,��������)
										if(POS.ist.player==lst_see_time) pos_change.insert(u);
									}
								}
							}
						int player_shoot_laser_beam2(position_3D pos,int angle){//0~359 �������еĸ������� 
							vector<PII > v;vector<position_3D> ret;
							int a1=(angle+1)%360,a2=(angle-1+360)%360;
							for(int i=0;i<4;i++) v.push_back(MP(a2,a1));
							vision_init(1,v,ret,pos);
							calculate_vision2(pos,1,ret,INF,0);
							int cnt=0;
							for(int i=0;i<ret.size();i++){
								position_3D u=ret[i];
								MAP &POS=game_map[u.x][u.y][u.z];
								thing &THING=POS.things;
								if(u==pos||!laser_beam_through(pos,u,angle)) continue;
								if(light_through(u,1)&&u!=pos){
									THING.lsr.exist=true;
									cnt++;
								}
								laser_beams.push(u);
								
								//if(!nobody_here(u)) make_laser_beam_brightness(u,7);//����һЩ�������� 
								POS.brightness+=40;//�Ӹ�����Ч���� 
								
			 					if(POS.ist.player==lst_see_time) pos_change.insert(u);//��Ļ���� 
			 					if(nobody_here(u)&&THING.nst.exist&&THING.nst.id!=-1){//���г��ӵĳ�Ѩ��
			 						position_3D v=THING.nst.to;
			 						MAP &NPOS=game_map[v.x][v.y][v.z];
			 						thing &NTHING=NPOS.things;
								 	nest &NST=THING.nst,&NST2=NTHING.nst;
								 	int id=NST.id;
								 	bug_nest &bns=bug_nests[id];
								 	bns.lfin.life--;bns.lfin.change=2;//����˺� 
								 	bns.lfin.last_injury_from=MP(PLAYER,-1);
									bns.lfin.last_injury_time=game_time;
								 	if(bns.lfin.life<=0){//��û�� 
								 		NST.exist=false;
										NST.id=-1;
										NST2.exist=false;
										NST2.id=-1;
									}
								}
								hurt_enemy(POS);
								if(THING.crt.exist) damage_curtain(u);
							}
							return cnt;
						}
					void player_use_laser_gun012(int k){
						if(game_timer["����ǹ��ȴ"]>game_time) return;//��û��ȴ�þͲ����� 
						item &items=player1.items;
						weapon_carried &wpn=items.wpn;
						laser_gun_info &lsg=wpn.lsg;
						if(object_type(wpn.primary)!=LAS) return;
						int id=items.item_lab[wpn.primary];
						object &ob=objects[id];
						bool use=false;//�Ƿ�ʹ���� 
						if(ob.lsrE>0&&player_shoot_laser_beam2(player1.pos,player1.angle)){//������1������� 
							object_addE(wpn.primary,-1);
							use=true; 
						}
						int ang[5];//ע�ⲻҪԽ�� 
						ang[0]=player1.angle;
						for(int i=1;i<5;i++) ang[i]=ang[i-1]+pow(-1,i)*i*5;
						if(k>=1){//����������ϲ�
							if(ob.lsrE>0&&player_shoot_laser_beam2(player1.pos,ang[1])){
								object_addE(wpn.primary,-1);
								use=true; 
							}
							if(ob.lsrE>0&&player_shoot_laser_beam2(player1.pos,ang[2])){
								object_addE(wpn.primary,-1);
								use=true; 
							}
						}
						if(k==2){//����������ϲ�
							if(ob.lsrE>0&&player_shoot_laser_beam2(player1.pos,ang[3])){
								object_addE(wpn.primary,-1);
								use=true; 
							}
							if(ob.lsrE>0&&player_shoot_laser_beam2(player1.pos,ang[4])){
								object_addE(wpn.primary,-1); 
								use=true; 
							}
						}
						if(use){//���ȥ�� 
							game_timer["���������"]=game_time+lsg.last_time;game_timer["����ǹ��ȴ"]=game_timer["���������"]+lsg.cool_time;
							player1.use_weapon=true;
							player1.scr.shoot_times++;//�����Ϣ���� 
							MUSIC("Laser2.wav",1);//��ʾ�� 
						}
					}
				void player_use_laser_gun(){
					weapon_carried &wpn=player1.items.wpn;
					laser_gun_info &lsg=wpn.lsg;
					player_use_laser_gun012(0);
					/*
					int k=lsg.kind;
					switch(k){
						case 0:case 1:case 2:
							player_use_laser_gun012(k);//if(lsg.energy>=2*k+1) ��ǰ�ж������Ƿ��㹻�� 
							break;
						case 3:
							break;
						case 4:
							break;
					}*/
				}
			    void player_use_dart(){//�����ӳ��Ļ����ڲ���������ڶ��� 
					weapon_carried &wpn=player1.items.wpn;
					int x=wpn.primary;//��������Ʒ���еı�� 
					if(object_type(x)!=DAR) return;
					int id=player1.items.item_lab[x];//����id 
					flying_dart fdt;
					dart &DRT=game_map[player1.pos.x][player1.pos.y][player1.pos.z].things.drt; 
					fdt.init(player1.pos,player1.angle,id);//�����λ���ӳ� 
					darts.push(fdt);//������� 
					DRT.num[1]++;//��ͼ����
					player1.scr.shoot_times++;//�����Ϣ���� 
					del_object2(x); 
					//����һ������ 
					game_timer["�ӻ�������ȴ"]=game_time+200;
					MUSIC("������2.wav",1);//����ವ÷ɹ������� 
				}
			void player_use_weapon(){
				weapon_carried &wpn=player1.items.wpn;
				laser_gun_info &lsg=wpn.lsg;
				vector<int> &v=player1.items.item_lab;
				int type=object_type(wpn.primary);
				if(!type_weapon(type)) return;
				switch(type){
					case LAS:
						if(game_timer["����ǹ��ȴ"]<=game_time) player_use_laser_gun();
						break;//ob.lsrE>=lsg.kd_energy[lsg.kind]&&
					case DAR:
						if(game_timer["�ӻ�������ȴ"]<=game_time
						&&!game_map[player1.pos.x][player1.pos.y][player1.pos.z].things.drt.exist1()) player_use_dart();
						break;//object_cnt(id)>=1&&
				}
 			}
			    void player_erase_spear(){//�����ϴ���ʾ��ì 
		    		while(!spears.empty()){
		    			position_3D u=spears.front();spears.pop();
		    			if(game_map[u.x][u.y][u.z].ist.player==lst_see_time)
							pos_change.insert(u),game_flag["���ì�ı�λ��"]=true;
			    		MAP &POS=game_map[u.x][u.y][u.z];
			    		POS.things.spr.exist=false;
			    		hurt_enemy(POS);//ȡ���˺�Ч��
			    		/*
			    		if(curtain_here(u)){
							game_flag["����ҡ��"]=true;
							if(POS.update_light()&&POS.ist.player==lst_see_time) pos_affect_light.push(u);//���Ӱڶ����¹���  
						}*/
			    	}
			    }
			    void player_use_spear(position_3D pos,int angle,int dir,int le=2){ 
					weapon_carried &wpn=player1.items.wpn;
					int x=wpn.primary;
					if(object_type(x)!=SPE) return;
					if(objects[player1.items.item_lab[x]].sprE<=0)
						del_object2(x);//�Զ����� 
					if(object_type(x)!=SPE) return;
					int a2=(dir+3)%4*90;
					bool kind=0;
					int d2=0;
					position_3D npos;
					if(sub_angle(a2,angle)>22){//22.5�� 
						if(angle<a2) d2=(dir+3)%4;
						else d2=(dir+1)%4;
						if(dir==3&&d2==0||dir==0&&d2==3) dir=7;
						else dir=dir+d2;
						npos=dtp3(pos,dir,8);
						le/=1.414;
						kind=1;
					}
		    		else{
		    			npos=dtp3(pos,dir,4);
						kind=0;
					}
					position_3D lpos=pos;
					int i=1;
		    		while(1){
		    			MAP &NPOS=game_map[npos.x][npos.y][npos.z];
		    			thing &NTHING=NPOS.things;
		        		if(NTHING.mvb.exist||door_here(npos,0)||door_here(npos,2)||NTHING.hdr.exist
						||wall_here(npos)||exit_here(npos)||ghost_here_d(npos,ROCK)||i>le){//ì�������ӡ�ǽ��ʯ�����ì�ĳ��Ȳ��� 
		    				MAP &LPOS=game_map[lpos.x][lpos.y][lpos.z];
		    				if(i!=1) LPOS.things.spr.head=true;
		        			break;
					    }
					    hurt_enemy(NPOS);
			    		if(curtain_here(npos)){
							game_flag["����ҡ��"]=true;
							if(NPOS.update_light()&&NPOS.ist.player==lst_see_time) pos_affect_light.push(npos);//���Ӱڶ����¹���  
						}
						NTHING.snt.addedc(-10,npos); 
			    		spear &spr=NTHING.spr;
			    		spr.exist=true;
						if(kind==0) spr.d=dir*2;
						else spr.d=dir;
						spr.head=false;
			    		//if(NPOS.ist.player==lst_see_time) pos_change.insert(npos);
						spears.push(npos);
			    		lpos=npos;
						if(kind==0) npos=dtp3(npos,dir,4);
						else npos=dtp3(pos,dir,8);
						i++;
			    	}
		    	}
			void player_update_spear(){//ì�Զ�����
				player_erase_spear();
				player_use_spear(player1.pos,player1.angle,atd(player1.angle),2); 
			}
				void player_erase_sword(){
					while(!swords.empty()){
		    			position_3D u=swords.front();swords.pop();
		    			if(game_map[u.x][u.y][u.z].ist.player==lst_see_time)
							pos_change.insert(u),game_flag["��ҽ��ı�λ��"]=true;
			    		MAP &POS=game_map[u.x][u.y][u.z];
			    		POS.things.swd.exist=false;
			    		if(curtain_here(u)){
							game_flag["����ҡ��"]=true;
							if(POS.update_light()&&POS.ist.player==lst_see_time) pos_affect_light.push(u);//���Ӱڶ����¹���  
						}
			    	}
				}
				void player_use_sword(position_3D pos,int angle,int dir,int le){
					int a2=(dir+3)%4*90;
					bool kind=0;
					int d2=0;
					position_3D npos;
					if(sub_angle(a2,angle)>22){//22.5�� 
						if(angle<a2) d2=(dir+3)%4;
						else d2=(dir+1)%4;
						if(dir==3&&d2==0||dir==0&&d2==3) dir=7;
						else dir=dir+d2;
						npos=dtp3(pos,dir,8);
						//length/=1.414;ȥ����ֹб��û�� 
						kind=1;
					}
		    		else{
		    			npos=dtp3(pos,dir,4);
						kind=0;
					}
					int i=1;
		    		while(1){
		    			MAP &NPOS=game_map[npos.x][npos.y][npos.z];
		    			thing &NTHING=NPOS.things;
		        		if(NTHING.mvb.exist||door_here(npos,0)||door_here(npos,2)||NTHING.hdr.exist
						||wall_here(npos)||exit_here(npos)||ghost_here_d(npos,ROCK)||ghost_here_d(npos,SHIELD)
						||NPOS.ist.player<lst_see_time||i>le){
						//���������ӡ�ǽ������Ұ��Χ��򽣵ĳ��Ȳ��� 
		        			break;
		        		}
		        		if(enemy_here2(npos)&&!NPOS.fcmv.lock){
		        			//living_things_reduce_blood(npos,5.0,1,MP(PLAYER,-1));
		        			if(player1.w.speed>90){
		        				double v=0.2*player1.w.speed*PI/180;//�����ٶ� 
		        				throw_thing(npos,v,0.5,player1.angle,MP(PLAYER,-1));
		        				object_addE(player1.items.wpn.primary,-0.01*pow(v,2)*NPOS.mass());
							}
		        			player1.color=5;
		        			player1.flash_word="��";
		        			player1.flash=true;
							game_timer["���ͼ����˸"]=game_time+500;
		        			pos_change.insert(player1.pos);
						}
			    		if(curtain_here(npos)){
							game_flag["����ҡ��"]=true;
							if(NPOS.update_light()&&NPOS.ist.player==lst_see_time) pos_affect_light.push(npos);//���Ӱڶ����¹���  
						}
						NTHING.snt.addedc(-5,npos); 
			    		sword &swd=NTHING.swd;
			    		swd.exist=true;
			    		if(NPOS.ist.player==lst_see_time) pos_change.insert(npos);
						swords.push(npos);
						if(kind==0) npos=dtp3(npos,dir,4);
						else npos=dtp3(pos,dir,8);
						i++;
			    	}
				}
			void player_update_sword(){//���Զ����� 
				player_erase_sword();
				weapon_carried &wpn=player1.items.wpn;
				int x=wpn.primary;
				if(object_type(x)!=SWO) return;
				if(objects[player1.items.item_lab[x]].swordE<=0)
					del_object2(x);//�Զ����� 
				if(object_type(x)!=SWO) return;
				//������� 
				int start_angle,end_angle;
				if(cmpa(player1.angle,player1.lsta))
					start_angle=player1.angle,end_angle=player1.lsta;
				else
					start_angle=player1.lsta,end_angle=player1.angle;
				for(int i=start_angle;cmpa(i,end_angle);i+=30) player_use_sword(player1.pos,i,atd(i),1); 
				player_use_sword(player1.pos,end_angle,atd(end_angle),1); 
			}
				void player_erase_blade(){
					while(!blades.empty()){
		    			position_3D u=blades.front();blades.pop();
		    			if(game_map[u.x][u.y][u.z].ist.player==lst_see_time)
							pos_change.insert(u),game_flag["��ҵ��ı�λ��"]=true;
			    		MAP &POS=game_map[u.x][u.y][u.z];
			    		POS.things.bld.init();
			    		if(curtain_here(u)){
							game_flag["����ҡ��"]=true;
							if(POS.update_light()&&POS.ist.player==lst_see_time) pos_affect_light.push(u);//���Ӱڶ����¹���  
						}
			    	}
				}
				void player_use_blade(position_3D pos,int angle,int le){
					position_3D lpos=pos;//��һ��λ�� 
					/*
	        			player1.color=5;
	        			player1.flash_word="��";
	        			player1.flash=true;
						game_timer["���ͼ����˸"]=game_time+500;
	        			pos_change.insert(player1.pos);*/
	        		int i=1;
					for(;i<=le;i++){
				        int dx=round(i*cos(angle*PI/180.0));
				        int dy=round(i*sin(angle*PI/180.0));
				        //���㵱ǰ�����������ʼλ�õ�ƫ���� 
						position_3D npos=pos;
						npos.x+=dx;npos.y+=dy;
				        //���㵱ǰ�����������ͼ�е�λ��
		        		//	if(player1.flash_word!="da"&&player1.flash_word!="DA") player1.flash_word="��";
		    			MAP &NPOS=game_map[npos.x][npos.y][npos.z];
		    			thing &NTHING=NPOS.things;
						if(lpos==npos||NTHING.bld.exist) continue;
				        //����Ƿ��ظ� 
		        		//	if(player1.flash_word!="da") player1.flash_word="da";
		        		if(!pos_in_area2(npos.x,npos.y,1,1,length,width,2)||
						NTHING.mvb.exist||door_here(npos,0)||door_here(npos,2)||NTHING.hdr.exist
						||wall_here(npos)||exit_here(npos)||ghost_here_d(npos,ROCK)||ghost_here_d(npos,SHIELD)
						||NPOS.ist.player<lst_see_time){
						//���������ӡ�ǽ������Ұ��Χ�� 
							if(lpos!=pos) game_map[lpos.x][lpos.y][lpos.z].things.bld.head=1;
		        			break;
		        		}
		        		//	player1.flash_word="DA";
		        		if(enemy_here2(npos)&&!NPOS.fcmv.lock){
		        			//living_things_reduce_blood(npos,5.0,1,MP(PLAYER,-1));
		        			if(player1.w.speed>90){
		        				double v=0.3*NED(player1.pos.x,player1.pos.y,npos.x,npos.y)*player1.w.speed*PI/180;//�����ٶ� 
								throw_thing(npos,v,0.5,player1.angle,MP(PLAYER,-1));
								object_addE(player1.items.wpn.primary,-0.01*pow(v,2)*NPOS.mass());
							}
		        			player1.color=5;
		        			player1.flash_word="��";
		        			player1.flash=true;
							game_timer["���ͼ����˸"]=game_time+500;
		        			pos_change.insert(player1.pos);
						}
						NTHING.snt.addedc(-5,npos); 
						blade &bld=NTHING.bld;
						bld.exist=1;bld.head=0;
			    		if(NPOS.ist.player==lst_see_time) pos_change.insert(npos);
						blades.push(npos);
						lpos=npos;
				    }
				    if(i>le) game_map[lpos.x][lpos.y][lpos.z].things.bld.head=1;
				}
			void player_update_blade(){//���Զ�����
				player_erase_blade(); 
				weapon_carried &wpn=player1.items.wpn;
				int x=wpn.primary;
				if(object_type(x)!=BLA) return;
				if(objects[player1.items.item_lab[x]].bladeE<=0)
					del_object2(x);//�Զ����� 
				if(object_type(x)!=BLA) return;
				//������� 
				int start_angle,end_angle;
				if(cmpa(player1.angle,player1.lsta))
					start_angle=player1.angle,end_angle=player1.lsta;
				else
					start_angle=player1.lsta,end_angle=player1.angle;
				for(int i=start_angle;cmpa(i,end_angle);i+=30) player_use_blade(player1.pos,i,2);
				player_use_blade(player1.pos,end_angle,2);
			}
			void player_pickup_object(position_3D pos){//��ʰ��Ʒ
				thing &THING=game_map[pos.x][pos.y][pos.z].things;
				int id=THING.fir;
				if(id<0) return;
				object &ob=objects[id];
				item &items=player1.items;
				int sn=items.select_number;
				vector<int> &v=items.item_lab;
				bool success=0;
				for(int i=0;i<v.size();i++)
					if(v[i]>=0){
						object ob2=objects[v[i]];
						if(ob==ob2){//����һ�������� 
							del_object1(pos);
							add_object2(id,i);
							success=1;
							break;
						}
					}
				if(!success){
					for(int i=0;i<v.size();i++)
						if(v[i]<0){//��Ȼ�ͷ��ڿ�λ�� 
							del_object1(pos);
							add_object2(id,i);
							success=1;
							break;
						}
					/*
					if(!success){//�ٲ�Ȼ�¿�һ��λ�� 
						v.push_back(-1);
						del_object1(pos);
						add_object2(id,v.size()-1);
					}*/
				}
				/*
				switch(obj.type){
					case KEY:
						if(ob.key){
						}
						break;
				}*/
			}
			void player_discard_object(position_3D pos){//������Ʒ 
				if(!(space_here(pos)&&noitem_here(pos))) return;//Υ�涪�� 
				item &items=player1.items;
				int sn=items.select_number;
				vector<int> &v=items.item_lab;
				if(sn<0||sn>=v.size()) return;
				int id=v[sn];
				if(id<0) return;
				object &obj=objects[id];
				del_object2(sn);
				add_object1(pos,id);
			}
		void player_detect_move(){
			logMessage("player_detect_move");
			int maze=game_map[player1.pos.x][player1.pos.y][player1.pos.z].maze;
			MAP &POS=game_map[player1.pos.x][player1.pos.y][player1.pos.z];
			thing &THING=POS.things;
			vector<int> &item_lab=player1.items.item_lab;
			removable &rmv=player1.items.rmv;
			int d=player1.d1,tmp;//����ܵ�����ȥ����Ͳ���
			position_2D scr_mouse=pos_mouse();//������Ļλ�� 
			position_3D map_mouse=position_scrto3D(scr_mouse,player1.pos.z);//���ĵ�ͼλ��
			bool mouse_in_area=pos_in_game_map(scr_mouse);//����Ƿ�����Ϸ��ͼ���� 
			if(mouse_in_area&&player1.mpos!=map_mouse){//���Ʒ���
				//formatted_output(1,vital_signs_area,1,11,MMPP(0,360,-100,360),int_to_str(scr_mouse.x,3));
				//formatted_output(1,vital_signs_area,1,12,MMPP(0,360,-100,360),int_to_str(scr_mouse.y,3));
				//formatted_output(1,vital_signs_area,1,13,MMPP(0,360,-100,360),int_to_str(screen_zoom,3));
				player1.mpos=map_mouse;//�������λ�� 
				game_flag["�����Ұ�����ı�"]=true;//
				int mouse_angle=calc_angle(player1.pos,map_mouse);
				if(player1.angle!=mouse_angle){
					player1.w.speed=1.0*sub_angle(player1.angle,mouse_angle)/(game_time-player1.alc)*1000;
					player1.w.vt();
					//���½��ٶ� 
					player1.lsta=player1.angle;
					player1.angle=mouse_angle;
					player1.alc=game_time;
					//���½Ƕ� 
					int d2=atd(player1.angle);
					player_update_spear();player_update_sword();player_update_blade();//�ı䷽��͸���ì�������� 
					if(player1.d2!=d2){
						player1.d2=d2;
						player1.d2_change=true;
					}
					//if(game_time%200==0) //���Ƹ���Ƶ��
					game_flag["�����Ұ�����ı�"]=true;
				}
			}
			if(game_timer["����ƶ�"]>game_time) return;
			game_timer["����ƶ�"]=game_time+player1.vlc.wait_time;
			bool want_move=false;//�����Ҫ�ƶ� 
			position_3D npos;//��һ���ߵ���λ�� 
			npos=player1.pos;
			int mouse_dis=MHT_DIST_p3(map_mouse,player1.pos);//��굽��ҵľ��� 
			if(KEY_DOWN(VK_LBUTTON)&&game_timer["�������"]<=game_time&&!game_flag["��굥��"]){//������
				game_timer["�������"]=game_time+100;//���Ƶ�� 
				game_flag["��굥��"]=true;
				if(mouse_in_area){//����Ϸ��ͼ������ 
					if(pos_in_area2(map_mouse.x,map_mouse.y,1,1,length,width)){//��ͼ���� 
						MAP &MPOS=game_map[map_mouse.x][map_mouse.y][map_mouse.z];
						thing &MTHING=MPOS.things;
						item &items=player1.items;
						bool mouse_near=(mouse_dis==1);//��������
						int connect=interconnection_distance(player1.pos,map_mouse,3,pos000);//���ڼ������ܷ񹻵õ� 
						if(mouse_near&&MTHING.mvb.exist){//��ȡ����ѡ��������Ʒ
							game_flag["��"]=true;
							position_3D &select=items.rmv.select;
							if(select!=pos000&&game_map[select.x][select.y][select.z].ist.player==lst_see_time)
								pos_change.insert(select);//��һ�� 
							if(select==map_mouse) select=pos000;//ȡ��ѡ�� 
							else select=map_mouse;//ԭ��û�У�ѡ���µ� 
							player1.pull_thing=true;
							player1.color=3;//��ʾ�����������Ʒ 
							player1.flash=true;
							game_timer["���ͼ����˸"]=game_time+500;
							if(MPOS.ist.player==lst_see_time) pos_change.insert(map_mouse); 
						}
						else if(mouse_dis<=2&&door_here(map_mouse,1)){//������ 
							MTHING.kdr.state=2;
							if(MPOS.update_light()) pos_affect_light.push(map_mouse);//�ſ��˹��ո���
							shut_door(map_mouse,player1.pos,MP(PLAYER,-1));//����ˤ��Ķ������� 
							game_flag["����"]=true;
							MUSIC("Door_Closing.wav",1);//��ʾ�� 
						}
						else if(mouse_near&&door_here(map_mouse,0)){//��������
							bool unlock=false;
							for(int i=0;i<item_lab.size();i++){//����Ѱ��Կ�� 
								int id=item_lab[i];
								if(id<0) continue;
								object &ob=objects[id];
								if(ob.type==KEY&&ob.key==MTHING.kdr.kind-DOOR1+KEY1){
									del_object2(i);
									unlock=true;
									break;
								}
							}
							if(unlock){
								MTHING.kdr.state=1;//����Կ���ڿ��� 
								if(MPOS.update_light()) pos_affect_light.push(map_mouse);//�ſ��˹��ո���
								game_flag["����"]=true; 
								MUSIC("����.wav",1);//��ʾ��
							}
						}
						else if(mouse_near&&MTHING.windows.exist){ 
							MTHING.windows.state^=1;//��/��
							if(MPOS.update_light()) pos_affect_light.push(map_mouse);//�ſ��˹��ո��� 
							game_flag["��ҿ�/�ش���"]=true; 
							if(MTHING.windows.state) MUSIC("����.wav",1);//��ʾ�� 
							else MUSIC("�ص�.wav",1);//��ʾ��
						}
						else if(mouse_dis<=2&&MTHING.lgt.exist
						&&connect!=-1&&connect<=mouse_dis){//���ص� 
							//���õ�����ֹ���۹�Ͻ��
							MTHING.lgt.state=!MTHING.lgt.state;
							update_light_brightness(map_mouse);
						}
						else{
							player_use_weapon();
							return;
						} 
					}
					else{
						player_use_weapon();
						return;
					} 
				}
				else if(scr_mouse.x<=20){
					game_pause=!game_pause;
					game_flag["��Ϸ��ͣ/����"]=true; 
					return;
				}
				else if(item_area.contain(scr_mouse)){//�����Ʒ�� 
					player1.action_kind=CHOOSE_ITEM;player1.ak_change=true;
					game_timer["�������"]=game_time;//һ��ʹ����Ʒ�����ð����� 
					return;
				}
				else if(weapon_area.contain(scr_mouse)){//��������� 
					player1.action_kind=CHANGE_WPN;
					player1.ak_change=true;
					return;
				}
				//���ã���Ʒ�� 
			}
			else if(game_timer["�������"]<=game_time) game_flag["��굥��"]=false; 
			position_3D throw_pos;
			if(_kbhit()){
				position_3D u=dtp3(player1.pos,player1.d2,4),v=player1.items.rmv.select;//�����ǰ��angle����������ŵ�
				//position_3D u2=dtp3(player1.pos,fatd(player1.angle),4);//���ַ�λ 
				int delta_angle=sub_angle(player1.angle,calc_angle(player1.pos,v));
				MAP &UPOS=game_map[u.x][u.y][u.z];
				thing &UTHING=UPOS.things;
				flashlight &flt=player1.items.flt;
				char getch=_getch();
				if(getch!=PRESS_KEY_SPACE) game_flag["���ո��"]=false;
				int door_d;
				switch(getch){//��ⰴ�� 
					case PRESS_KEY_W:
						d=0;want_move=true;
						break;
					case PRESS_KEY_D:
						d=1;want_move=true;
						break;
					case PRESS_KEY_S:
						d=2;want_move=true;
						break;
					case PRESS_KEY_A:
						d=3;want_move=true;
						break;
					case PRESS_KEY_TAB:
						flt.state=!flt.state;//�����ֵ�Ͳ 
						flt.change=1;
						break;
					case PRESS_KEY_SPACE:
						if(game_flag["���ո��"]) break; 
						game_flag["���ո��"]=true;
						POS.player_enemy=NOBODY;//��������Ʒ 
						//u:�����ǰ��angle��  v:������ŵ�
						if(box_here(u)){//��ǰ������
							door_d=turn(player1.d2,TURN_BACK,4,16);//���ŷ�����˷����෴ 
							movable &UMVB=UTHING.mvb;
							UMVB.door[door_d]^=1;//���� �����л� 
							game_flag["����"]=true;
							if(UPOS.update_light()) pos_affect_light.push(u);//���ո���
						}
						else if(box_here(player1.pos)){//������������
							door_d=player1.d2;//���ŷ�����˷�����ͬ 
							movable &MVB=POS.things.mvb;
							MVB.door[door_d]^=1;//���� �����л� 
							game_flag["����"]=true;
							if(POS.update_light()) pos_affect_light.push(player1.pos);//���ո��� 
						}
						else if(!nobody_here2(u)//����ǰ�������߳�ȥ����B��֩�븽֫��û�õģ� 
						||mvb_here(u)&&UTHING.mvb.kind!=BOX//����ǰ�Ķ����ӳ�ȥ
						||mvb_here(player1.pos,0)&&push_thing(player1.pos,player1.d2,1)){//���ڿ��ƶ���Ʒλ���ҿ����ƶ�
							throw_pos=u;//����λ 
							player1.items.rmv.throw_ready=true;
						}
						else if(v!=pos000&&game_map[v.x][v.y][v.z].things.mvb.kind!=BOX//�����ŵ���Ʒ�ӳ�ȥ
						&&(mvb_through(u,player1.d2)&&push_thing(u,player1.d2,1)||
						v!=player1.pos&&delta_angle<=90)){//�����Ķ��������ҵ��Լ� 
						//(u2==v) 
							if(delta_angle>90) swap(UTHING.mvb,game_map[v.x][v.y][v.z].things.mvb);
							//�����Ķ������﷽�������� 
							player1.items.rmv.select=pos000; 
							game_flag["��"]=true;
							if(game_map[v.x][v.y][v.z].ist.player==lst_see_time) pos_change.insert(v);
							if(delta_angle<=90) throw_pos=v;//����λ
							else{
								if(game_map[u.x][u.y][u.z].ist.player==lst_see_time) pos_change.insert(u);//����λ
								throw_pos=u;
							}
							player1.items.rmv.throw_ready=true;
							player_add_stg(-UPOS.mass()*0.5);//�������٣����Ķ���������������� 
							MUSIC("Whiz.wav",1);//��ʾ�� 
						}
						else if(v!=pos000&&(mirror_here(u)||window_here(u))){
							if(mirror_here(u)) UTHING.mirrors.damage(30);//�Ҿ��� 
							else UTHING.windows.damage(20,u);//�Ҵ��� 
							player_add_stg(-5);//�������� 
						}
						POS.player_enemy=PLAYER;
						break;
					case PRESS_KEY_ESC:
						game_pause=true;
						game_flag["��Ϸ��ͣ/����"]=true; 
						return;
					case PRESS_KEY_C:
						if(stair_here(player1.pos)||POS.things.nst.exist){//����¥/������Ѩ�� 
							d=THING.fpt.d=4;//��¼�㼣
							if(maze==UPSTAIR) npos.z++;
							else if(maze==DOWNSTAIR) npos.z--;
							else npos=THING.nst.to;
						}
						break;
					case PRESS_KEY_E:
						player_use_item();
						return;
					case PRESS_KEY_F:
						door_d=turn(player1.d2,TURN_BACK,4,16);//���ŷ�����˷�����ͬ 
						if(!closed_box_here(u,door_d)) player_pickup_object(u);
						return;
					case PRESS_KEY_Q:
						player_discard_object(u);
						return;
					case PRESS_KEY_CTRL:
						player1.color=4;
						game_timer["���ͼ����˸"]=game_time+200;
						pos_change.insert(player1.pos); 
						break; 
				}
			}
			else game_flag["���ո��"]=false;
			if(player1.items.rmv.throw_ready){//�Ѿ�ΪͶ������׼�� 
				position_3D u=throw_pos;//Ͷ��������λ�� 
				MAP &UPOS=game_map[u.x][u.y][u.z];
				player_add_stg(-UPOS.mass()*0.5);//�������� 
				throw_thing(u,15.0/UPOS.mass(),0.3,player1.angle,MP(PLAYER,-1));//���� 
				throw_thing(player1.pos,2.5*UPOS.mass()/POS.mass(),0,(player1.angle+180)%360,MP(PLAYER,-1));//������ 
				player1.items.rmv.throw_ready=false;
			}
			if(npos==player1.pos&&want_move){//û������¥�ͼ�����λ��
				THING.fpt.d=d;//��¼�㼣
				npos.x+=dx4[d];
				npos.y+=dy4[d];
			}
			MAP &NPOS=game_map[npos.x][npos.y][npos.z];
			thing &NTHING=NPOS.things;
			if(player1.pos!=npos){//�����Ǹı���λ�� 
				int nmaze=NPOS.maze;
				int door_d=(d==4?0:turn(d,TURN_BACK,4,17));//���ŷ��� 
				int pri_type=object_type(player1.items.wpn.primary);//����������Ʒ���еı�� 
				if(!nobody_here(npos)&&!(d==4?box_here(npos):closed_box_here(npos,door_d))){//�����б������
					if(!spider_leg_here(npos)){//B��֩�븽֫����������ѽ
						weapon_carried &wpn=player1.items.wpn;
						int pri=object_type(wpn.primary);
						if(pri==DAG){//ذ�ײ����ˣ���Ϊ���5���˺���������30% 
							living_things_reduce_blood(npos,5*(1+RAND_BOOL(30)),1,MP(PLAYER,-1));
							player1.color=5;
							player1.flash_word="ذ";
							player1.flash=true;
							pos_change.insert(player1.pos);
							game_timer["���ͼ����˸"]=game_time+500;
						}
						else throw_thing(npos,10/NPOS.mass(),0.3,(d<4?(d+3)%4*90:RAND(359,0)),MP(PLAYER,-1));//ֱ��һȭ��ע������¥������� 
						player_add_stg(-3);//��������
					}
					if(d==4){//����¥/������Ѩ�ڵ�����ס
						game_flag["����¥����"]=true; 
						pos_change.insert(npos);
					}
				}
				else if(!(door_here(npos,0)||door_here(npos,2)||mvb_here(npos,1))//û�п��ŵ��Ż��������Ʒ 
				&&(nmaze==SPACE||nmaze==EXIT//�����ǿյء�����
				||(UPSTAIR<=nmaze&&nmaze<=DOWNSTAIR)//����¥��
				)){//���������ƶ� 
					bool flag=false;
					movable &NMVB=NTHING.mvb; 
					position_3D select=player1.items.rmv.select;
					if(mvb_here(npos,0)){//�о�ֹ�Ķ�������
					
						door_d=(d==4?0:turn(d,TURN_BACK,4,18));//�ж��ܷ���룬�����ƶ������෴��d<4����Ч�� 
						
						if(NMVB.kind==BALL) flag=true;//���򵲲��ˣ� 
						else if(d==4&&NMVB.kind!=BOX) flag=true;//�����ߵ�¥�µ���/����/������
						//����¥/������Ѩ�� �� 
						else if(d<4&&select==npos&&NTHING.mvb.kind!=BOX) flag=true;//�����ߵ�ѡ�е�����/������
						else if(d<4&&select!=npos&&NMVB.kind==BOX&&(NMVB.door[door_d]||box_here(player1.pos))) flag=true;
						//��ǰ�������ǿ�����/��������֮���ƶ� 
						else if(d<4&&select!=npos&&push_thing(npos,d,1)) flag=true;//�ƶ���ǰ��Ʒ
					}
					else if(!mvb_here(npos,1)) flag=true;//�˶������岻�� 
					//�����жϲ��е���� 
					
					door_d=d;//�ж��ܷ��ȥ�������ƶ�������ͬ 
					
					if(closed_box_here(player1.pos,door_d)&&!(d<4&&box_here(npos)&&select!=npos)) flag=false;
					//����ڹرյ�������û������ͬһ¥�������δѡ�����ӳ��⣩ 
					if(d==4&&!flag){//����¥/������Ѩ�ڵ�����ס
						game_flag["����¥����"]=true; 
						pos_change.insert(npos);
					}
					spider_net &SNT=THING.snt;
					if(SNT.endurance>50){
						player_add_stg(-2);//����ֵ����
						flag=false;//��֩����ճס 
						game_flag["��Ʒ��"]=true;
						pos_change.insert(player1.pos);
					}
					SNT.addedc(-25,player1.pos);
					if(flag){
						if(door_here(npos,2)) NTHING.kdr.state=1;//�Զ��򿪹��ϵ��� 
						player1.move=1;
						if(nmaze==EXIT){
							swap(NPOS.player_enemy,POS.player_enemy);
							game_end=game_success=true;
							return;
						}
					}
				}
				else if(door_here(npos,2)){//�Ź����˿��� 
					NTHING.kdr.state=1;//ֱ�ӿ��� 
					if(NPOS.update_light()) pos_affect_light.push(npos);//�ſ��˹��ո��� 
					player1.move=1;
					MUSIC("����",1);//������ 
				}
				else if(window_here(npos)&&(pri_type==DAG||pri_type==SWO||pri_type==BLA)){
					NPOS.things.windows.damage(25,npos);
				}
			}
			if(d!=-1&&d!=4&&player1.d1!=d){
				if(!player1.move){
					player1.color=3;
					player1.flash=true;
					game_timer["���ͼ����˸"]=game_time+200;
				}
				player1.d1=d;
				player1.d1_change=true;
			}
			if(player1.move){
				if(THING.crt.exist&&POS.update_light()&&POS.ist.player==lst_see_time) pos_affect_light.push(player1.pos);//���Ӷ��˹��ո��� 
				if(NTHING.crt.exist&&NPOS.update_light()&&NPOS.ist.player==lst_see_time) pos_affect_light.push(npos);//���Ӷ��˹��ո��� 
				POS.fcmv.init();//game_flag["��"]=true;pos_change.insert(player1.pos);//����������ƶ���ֹͣ�����ƶ� 
				game_map[player1.pos.x][player1.pos.y][player1.pos.z].player_enemy=NOBODY;
				game_map[npos.x][npos.y][npos.z].player_enemy=PLAYER;
				//��ǵ�ͼ 
				player_move_update(npos);
			}
			if(!stair_here(player1.pos)) player1.lst_ud=false;
			if(!THING.nst.exist) player1.lst_enter=false;
		}
			/*
			bool player_check_key(position_3D pos,item &items,vector<int> &v){//��Կ�� 
			//�����Ƿ������Ʒ 
				bool ret=false;
				thing &THING=game_map[pos.x][pos.y][pos.z].things;
				int id=THING.fir;
				if(id<0) return 0;
				object &obj=objects[id];
				if(obj.key==0) return 0;
				int nkey=obj.key;
				//int &nkey=THING.key;
				int &dk=items.keys.door_keys[nkey-KEY1];
				if(nkey){
					if(!dk){
						v.insert(v.end(),nkey-KEY1+K1);//��ԭ��û�е� 
						items.il_change=true;
					} 
					dk++;items.num_change=true;
					//nkey=0; 
					del_object1(pos);
					ret=true;
				}
				return ret;
			}
			bool player_check_food(thing &THING,item &items,vector<int> &v){//��ʳ�� 
			//�����Ƿ������Ʒ 
				bool ret=false;
				food_pile &nfood=THING.foods;
				if(nfood.exist()){//����������һ��ʳ�� 
					int nkind=nfood.kind(),neffect=nfood.effect();//��ʲôʳ�� 
					int &fc=items.foods.food_cnt[nkind-ADDS][neffect-1];//�����Ʒ�� 
					if(!fc){
						v.insert(v.begin(),AS1+(nkind-1)*EFFECT_OF_FOOD+(neffect-1));//��ԭ��û�е�
						items.il_change=true;
						MUSIC("Collect.wav",1);//��ʾ�� 
					} 
					fc++;items.num_change=true;
					nfood.food_cnt[nkind-ADDS][neffect-1]--;//�޸ĵ�ͼ�ϵ����� 
					ret=true;
				}
				return ret;
			}
			bool player_check_wpn_energy_edc(thing &THING,item &items){//��������;öȻظ� 
			//�����Ƿ������Ʒ 
				bool ret=false;
				weapon_energy_edc &wee=THING.wee;
				int &ly=items.wpn.lsg.energy,&hec=items.wpn.hsr.endurance,&num=wee.num,&kind=wee.kind;
				bool &dc=items.wpn.data_change,&ex=wee.exist;
				if(ex){
					switch(kind){
						case 0:ly+=num;num=ex=0;dc=1;
							MUSIC("Coin.wav",1);//��ʾ�� 
							break;
						case 1:hec+=num;num=ex=0;dc=1;
							MUSIC("Coin.wav",1);//��ʾ�� 
							break;
					}
					ret=true;
				}
				return ret;
			}
			bool player_check_wpn(thing &THING,item &items){//������
			//�����Ƿ��������
				bool ret=false;
				dart &DRT=THING.drt;
				weapon_carried &wpn=items.wpn;
				int &dnum=wpn.drt.num;
				if(DRT.exist0()){//���ϵĻ����� 
					dnum+=DRT.num[0];
					DRT.num[0]=0;
					wpn.data_change=true;
					ret=true;
				}
				return ret;
			}
			bool player_check_spe(thing &THING,item &items,vector<int> &v){//�񵽵���
			//�����Ƿ������Ʒ 
				bool ret=false;
				special_effect &spe=player1.spe; 
				perspective &ppt=THING.ppt;
				bool &nppt=ppt.exist;
				if(nppt){//͸�� 
					int& kind=ppt.kind,time=ppt.time;
					x_ray &xry=spe.xry;
					xry.num+=kind;
					if(xry.time<=game_time) xry.time=game_time+time;
					else xry.time+=time;
					xry.change=true;
					game_flag["�����Ұ�����ı�"]=true;
					nppt=kind=time=0; 
					ret=true;
				}
				if(THING.smb.exist){//���� 
					THING.smb.exist=false;
					int &num=items.pp.smb;
					if(num==0){
						v.push_back(SM);
						items.il_change=true;
					}
					num++;
					items.num_change=true;
					ret=true;
				}
				return ret;
			}
		void player_check_thing(){//��Ҽ�ʰ��Ʒ
			return;
			thing &THING=game_map[player1.pos.x][player1.pos.y][player1.pos.z].things;
			if(THING.empty()) return;//����û����ֱ���˳� 
			item &items=player1.items;
			vector<int> &v=items.item_lab;
			//ÿ��ֻ��һ������ 
			player_check_key(player1.pos,items,v);
			player_check_food(THING,items,v);
			player_check_wpn_energy_edc(THING,items);
			player_check_wpn(THING,items);
			player_check_spe(THING,items,v);
			//if(player_check_key(THING,items,v)) return;
			//if(player_check_food(THING,items,v)) return;
			//if(player_check_wpn_energy_edc(THING,items)) return;
			//if(player_check_wpn(THING,items)) return;
			//if(player_check_spe(THING,items,v)) return;
		}*/
		void player_choose_item(){
			logMessage("player_choose_item");
			position_2D scr_mouse=pos_mouse();//������Ļλ�� 
			bool press_once=game_timer["�������"]<=game_time&&!game_flag["��굥��"];//���� 
			int mx=scr_mouse.x,my=scr_mouse.y;//�������Ļ�ϵ�x��y����
			item &items=player1.items;
			int x=item_area.upper_left.x,y=item_area.upper_left.y;//��Ʒ������x��y���� 
			if(KEY_DOWN(VK_LBUTTON)){//������
				game_timer["�������"]=game_time+100;//�������Ƶ�� 
				game_flag["��굥��"]=true;
				if(scr_mouse.x<=20){//�����Ϣ�� 
					game_pause=!game_pause;
					game_flag["��Ϸ��ͣ/����"]=true; 
					return;
				}
				else if(pos_in_game_map(scr_mouse)){//�����Ϸ��ͼ���� 
					player1.action_kind=RUN;player1.ak_change=true;
					return;
				}
				else if(item_area.contain(scr_mouse)){//�����Ʒ�� 
					if(press_once){//��ֹ��ε�� 
						if(my>=y+1){//ѡ��ʹ����Ʒ 
							int x2=mx-x-3;//x�����ֵ
							int select=x2/6;//ѡ�е���Ʒ���
							if(select>=0&&select<MAX_SIZE_OF_ITEM_LAB){//����Ʒ����С��Χ��
								if(player1.items.select_number==select) player_use_item();
								items.select_number=select;
								items.sn_change=true;
							}
						}
					}
				}
				else if(weapon_area.contain(scr_mouse)){//��������� 
					if(press_once){//��ֹ��ε�� 
						player1.action_kind=CHANGE_WPN;
						player1.ak_change=true;
					}
				}
			}
			else game_flag["��굥��"]=false;
			game_flag["���ո��"]=false;
			if(_kbhit()){
				int c=_getch();
				int &sn=items.select_number;
				vector<int> &v=items.item_lab,&num=items.item_num;
				switch(c){
					case PRESS_KEY_A://���󽻻� 
						if(sn>=1&&sn<v.size()){
							if(sn==items.wpn.primary) items.wpn.primary--;
							if(sn==items.wpn.secondary) items.wpn.secondary--;
							swap(v[sn-1],v[sn]);
							swap(num[sn-1],num[sn]);
							items.il_change=items.num_change=1;
							sn--;
							items.sn_change=1;
						}
						break;
					case PRESS_KEY_D://���ҽ��� 
						if(sn>=0&&sn<v.size()-1){
							if(sn==items.wpn.primary) items.wpn.primary++;
							if(sn==items.wpn.secondary) items.wpn.secondary++;
							swap(v[sn],v[sn+1]);
							swap(num[sn],num[sn+1]);
							items.il_change=items.num_change=1;
							sn++;
							items.sn_change=1;
						}
						break;
					case PRESS_KEY_E:
						player_use_item();
						return;
				}
			}
		}
			/*
			void player_weapon_mode(){//��������ģʽ 
				item &items=player1.items;
				weapon_carried &wpn=items.wpn;
				laser_gun &lsg=wpn.lsg;
				switch(wpn.select_wpn){
					case LSG:
						lsg.kind=(lsg.kind+1)%lsg.kd_cnt;
						wpn.mode_change=true;
						break;
				}
			}*/
		void player_update_weapon(){//�������� 
			logMessage("player_update_weapon");
			item &items=player1.items;
			weapon_carried &wpn=items.wpn;
			position_2D scr_mouse=pos_mouse();//������Ļλ�� 
			bool press_once=game_timer["�������"]<=game_time&&!game_flag["��굥��"];//���� 
			int mx=scr_mouse.x,my=scr_mouse.y;//�������Ļ�ϵ�x��y����
			int x=weapon_area.upper_left.x,y=weapon_area.upper_left.y;//����������x��y���� 
			if(KEY_DOWN(VK_LBUTTON)){//������
				game_timer["�������"]=game_time+100;//�������Ƶ�� 
				game_flag["��굥��"]=true;
				if(scr_mouse.x<=20){//�����Ϣ�� 
					game_pause=!game_pause;
					game_flag["��Ϸ��ͣ/����"]=true; 
					return;
				}
				else if(pos_in_game_map(scr_mouse)){//�����Ϸ��ͼ���� 
					player1.action_kind=RUN;player1.ak_change=true;
					return;
				}
				else if(weapon_area.contain(scr_mouse)){//���������
					if(press_once){//��ֹ��ε�� 
						swap(wpn.primary,wpn.secondary);//������������ 
						wpn.data_change=wpn.sw_change=1; 
						/*
						if(my==y+1){//�л��������� 
							if(mx>=x+16){
								wpn.select_wpn=(wpn.select_wpn)%wpn.wcnt+1;//��1��ʼ���
								wpn.sw_change=true;
							}
							else{
								wpn.select_wpn=(wpn.select_wpn-2+wpn.wcnt)%wpn.wcnt+1;//��1��ʼ��� 
								wpn.sw_change=true;
							}
						}
						else if(my==y+2)//�л�����ģʽ 
							player_weapon_mode();
						*/
					}
				}
				else if(item_area.contain(scr_mouse)){//�����Ʒ��
					if(press_once){//�����Ʒ�� 
						player1.action_kind=CHOOSE_ITEM;
						player1.ak_change=true;
					}
				}
			}
			else game_flag["��굥��"]=false;
			game_flag["���ո��"]=false;
		}
		void player_lfin_update(){
			logMessage("player_lfin_update"); 
			MAP &POS=game_map[player1.pos.x][player1.pos.y][player1.pos.z];
			if(POS.fcmv.lock&&POS.fcmv.speed()>5&&game_timer["��ұ�����"]<=game_time){//�������޷��ƶ��͹���
				player_reduce_blood(1,POS.fcmv.from);
				game_timer["��ұ�����"]=game_time+500;
			}
			special_effect &spe=player1.spe;
			methysis &mts=spe.mts;
			weakness &wks=spe.wks;
			if(mts.exist()&&mts.t+mts.T<=game_time){//�ж���Ѫ 
				mts.t=game_time;
				player_reduce_blood(mts.x,mts.from);
			}
			if(wks.exist()&&wks.t+wks.T<=game_time){//����������
				wks.t=game_time;
				player_add_stg(-wks.x); 
			}
			if(game_timer["��������ָ�"]<=game_time){
				//game_timer["��ҿ�ʼ����"]=game_time;
				game_timer["��ұ��ܲ���"]=0;
			}//����
			if(player1.move){
				double x=sqrt(game_timer["��ұ��ܲ���"]);
				//->�����仯�� 
				player_add_stg(-x);//player_add_stg(-1);//����ֵ���� 
				//�������������½���Խ��Խ�� 
				game_timer["��������ָ�"]=game_time+player1.vts.stg.recovery_time;
				//�ƶ�ʱ���ظ����� 
				game_timer["��ұ��ܲ���"]++;
			}
			else if(game_timer["��������ָ�"]<=game_time&&player1.vts.stg.physical_strength<100){//�����ָ�ʱ���ѵ�
				player_add_stg(1);//����ֵ���� 
				game_timer["��������ָ�"]+=player1.vts.stg.recovery_time;
			}
			player1.vlc.speed=max(1.0,pow(player1.vts.stg.physical_strength,2)/double(200));
			//�ٶ����ֵΪ1����ֹ������ʱ��ʱ���� 
			player1.vlc.vt();
		}
		void player_sight_update(){//���¼�����Ұ 
			logMessage("player_sight_update"); 
			if(player1.spe.xry.num!=1&&player1.spe.xry.time<=game_time){
				player1.spe.xry.num=1;player1.spe.xry.change=true;
				game_flag["�����Ұ�����ı�"]=true;
			}
			special_effect &spe=player1.spe;
			dim_sight &dst=spe.dst;
			vertigo &vtg=spe.vtg;
			if(vtg.exist()&&vtg.t+vtg.T<=game_time){
				vtg.t=game_time;
				position_2D &u=screen_center;
				u.x+=RAND(2,-2);
				u.y+=RAND(2,-2);
				//�ڶ� 
				limit_int(u.x,player1.pos.x-10,player1.pos.x+10);
				limit_int(u.y,player1.pos.y-10,player1.pos.y+10);
				//��ֹ��̫Զ 
				game_flag["�����Ұ�����ı�"]=true;
			}
			if(!vtg.exist()&&screen_center!=position_3Dto2D(player1.pos)&&game_timer["�ƶ���Ļ����"]<=game_time){
			//&&game_timer["����ϴ��ƶ�"]+1000<=game_time
			//�ƶ���Ļ����screen_pos
				position_2D &u=screen_center;
				if(u.x>player1.pos.x) u.x--;
				else if(u.x<player1.pos.x) u.x++;
				if(u.y>player1.pos.y) u.y--;
				else if(u.y<player1.pos.y) u.y++;
				game_timer["�ƶ���Ļ����"]=game_time+200;
				game_flag["�����Ұ�����ı�"]=true;
			}
			if(player1.d2_change||player1.move||player1.ud_change||player1.items.flt.change
			||game_flag["�����Ұ�����ı�"]||game_flag["��ҿ�/�ش���"]||game_flag["�����ڵص�"]||game_flag["��װǽ"]||game_flag["�����仯"]
			||game_flag["����ҡ��"]||game_flag["��Ʒ��ʧ"]||game_flag["����"]||game_flag["����"]||game_flag["������ɢ"]||game_flag["�ڵ������ƶ�"]
			||dst.dim&&game_time-dst.time>dst.last){//ģ����Ұ���������� 
				game_flag["�����Ұ�����ı�"]=game_flag["��ҿ�/�ش���"]=game_flag["�����ڵص�"]=game_flag["��װǽ"]=game_flag["�����仯"]=false; 
				game_flag["����ҡ��"]=game_flag["��Ʒ��ʧ"]=game_flag["����"]=game_flag["����"]=game_flag["������ɢ"]=game_flag["�ڵ������ƶ�"]=false; 
				dst.dim=false;
				game_flag["�����Ұ���¼���"]=true;
				while(!pos_in_sight.empty()) pos_in_sight.pop();//���û������ 
				screen_z.clear();//���±����Ļ��λ�õ�ӳ�� 
				player_erase_flashlight();//���ֵ�Ͳ�յ���ɾ�� 
				player_calculate_vision2();
				//player_calculate_vision1(player1.d2);
				lst_see_time=game_time;//������Ұ 
			}
		}
		void player_others(){//��������
			logMessage("player_others");  
			if(player1.move) player_update_spear(),player_update_sword(),player_update_blade();//�ƶ��͸���ì�������� 
			//player_erase_spear();//ì���;ö��ù����ì�Զ�ɾ�� 
		}
	void deal_player(){
		logMessage("deal_player()",2);
		MAP &POS=game_map[player1.pos.x][player1.pos.y][player1.pos.z];
		switch(player1.action_kind){
			case RUN:case WALK:
				if(!(POS.fcmv.lock&&POS.fcmv.speed()>2)){
					POS.fcmv.init();
					player_detect_move();
				}
				//player_check_thing();//if(player1.move) 
				break;
			case CHOOSE_ITEM:
				player_choose_item();
				break;
			case CHANGE_WPN:
				player_update_weapon();
				break;
		}
		player_lfin_update();
		player_sight_update();
		player_others();
	}
		void clean_dead(){//���ʬ�� 
			logMessage("clean_dead");
			while(!pos_dead.empty()){
				position_3D u=pos_dead.front();
				MAP &POS=game_map[u.x][u.y][u.z];
				if(POS.emy.body_disapp>game_time) return;//�����ʬ�廹û������ʱ�䣬�������Ĳ��ÿ���
				if(POS.ist.player==lst_see_time){
					pos_change.insert(u);
					game_flag["���ʬ��"]=true;
				}
				pos_dead.pop(); 
			}
		}
		void shoot_laser_beam(){//��������� 
			logMessage("shoot_laser_beam");
			if(laser_beams.size()&&game_timer["���������"]<=game_time){
				player1.use_weapon=true;
				while(!laser_beams.empty()){
					position_3D u=laser_beams.front();laser_beams.pop();
					MAP &POS=game_map[u.x][u.y][u.z];
					POS.things.lsr.exist=false;
					
					POS.brightness-=40;//��������Ч�� 
					
					if(POS.ist.player==lst_see_time) pos_change.insert(u);
					hurt_enemy(POS);//ȡ���˺�Ч�� 
					if(!POS.things.nst.exist||POS.things.nst.id<0) continue;
					bug_nest &bgn=bug_nests[POS.things.nst.id];
					if(bgn.lfin.change!=0) bgn.lfin.change=0;//��Ѩ�����е���˸ֹͣ 
				}
				/*��������Ч�������ͼ���׿�����������������ˣ� 
				while(!laser_beam_light.empty()){
					pair<position_3D,int> p=laser_beam_light.front();laser_beam_light.pop();
					position_3D u=p.first;int x=p.second;
					MAP &POS=game_map[u.x][u.y][u.z];
					POS.brightness-=x;
					if(POS.ist.player==lst_see_time) pos_change.insert(u);
				}*/
			}
		}
		void pierce_spear(){//�̳�ì
			logMessage("pierce_spear");
			int num=spears.size();
			if(num==0) return;
			while(num>0){
				num--;
				position_3D u=spears.front();spears.pop();
				spears.push(u);//�ٷŻ�ȥ 
				MAP &POS=game_map[u.x][u.y][u.z];
				if(POS.player_enemy==BUG&&POS.emy.id!=-1) Qbug_hurt.push(POS.emy.id);//�˺�
				else if(POS.player_enemy==SPIDER&&POS.emy.id!=-1) Qspider_hurt.push(POS.emy.id);//�˺�
			}
		}
			void dart_fall(flying_dart fdt){//���������� 
				position_3D pos=fdt.pos;
				MAP &POS=game_map[pos.x][pos.y][pos.z];
				thing &THING=POS.things;
				dart &DRT=THING.drt;
				DRT.num[1]--;
				add_object1(pos,fdt.id);//DRT.num[0]++;
				if(POS.ist.player==lst_see_time){//������Ļ 
					game_flag["�����ڱ仯"]=true;
					pos_change.insert(pos); 
				}
			}
		void throw_dart(){//�����ڷ��� 
			logMessage("throw_dart");
			int num=darts.size();
			while(num>0){
				num--;
				flying_dart fdt=darts.front();darts.pop();
				MAP &POS=game_map[fdt.pos.x][fdt.pos.y][fdt.pos.z];
				dart &DRT=POS.things.drt;
				int d=0;//�ƶ����� 
				velocity *vlc;//�����ƶ��ķ����Ӧ�ٶȵ�ָ�루vx/vy�� 
				double vxy=sqrt(fdt.vx.speed*fdt.vx.speed+fdt.vy.speed*fdt.vy.speed);//�ϳ��ٶȵĴ�С 
				if(fdt.tx<=game_time){//x�� 
					d=(fdt.vx.speed>0?1:3);//vx������ 
					fdt.tx=game_time+fdt.vx.wait_time;
					vlc=&fdt.vx;
				}
				else if(fdt.ty<=game_time){//y�� 
					d=(fdt.vy.speed>0?2:0);//vy������ 
					fdt.ty=game_time+fdt.vy.wait_time;
					vlc=&fdt.vy;
				}
				else{//û���ƶ�ʱ�� 
					darts.push(fdt);
					break;
				}
				position_3D npos=dtp3(fdt.pos,d,4);//��һ���ط� 
				MAP &NPOS=game_map[npos.x][npos.y][npos.z];
				thing &NTHING=NPOS.things;
				dart &NDRT=NTHING.drt;
				hurt_enemy(POS);
				hurt_enemy(NPOS);
				if(mirror_here(npos)||window_here(npos)){//ײ������/���� 
					if(mirror_here(npos)) NTHING.mirrors.damage(fabs(vlc->speed)*3);
					else NTHING.windows.damage(fabs(vlc->speed),npos);
					vlc->speed*=0.8;vlc->vt();//���� 
					if(NPOS.ist.player==lst_see_time){
						game_flag["��"]=true;
						pos_change.insert(npos);
					}
				}
				int eid=NPOS.emy.id;
				if(enemy_here(npos)&&!nobody_here2(npos)//ײ�����ˣ��еж�����ı���
				&&(eid<0||eid>=ghosts.size()||!ghost_here(npos)?1:ghosts[eid].spat.defense!=EVADE)//���ܹ���Ч 
				&&!box_here(npos)//���������� 
				){
					/*
					position_3D b;
					b.x=fdt.vx.speed;b.y=fdt.vy.speed;b.z=0;//����Ƕȵĸ������� 
					throw_thing(npos,vxy*0.5,0,calc_angle(pos000,b),MP(PLAYER,-1));*/
					throw_thing(npos,fdt.vx.speed*0.2,0,0,MP(PLAYER,-1));
					throw_thing(npos,fdt.vy.speed*0.2,0,90,MP(PLAYER,-1));
					//����ģ��һ�� 
					fdt.vx.speed*=0.8;fdt.vx.vt();//���� 
					fdt.vy.speed*=0.8;fdt.vy.vt();//���� 
				}
				if(pos_in_area2(npos.x,npos.y,1,1,length,width,2)
				&&!(door_here(npos,0)||door_here(npos,2)||wall_here(npos)||spider_leg_here(npos)
				||NTHING.mvb.exist||NTHING.hdr.exist||NTHING.crt.exist)
				){
					if(game_map[fdt.pos.x][fdt.pos.y][fdt.pos.z].ist.player==lst_see_time){//������Ļ 
						game_flag["�����ڱ仯"]=true;
						pos_change.insert(fdt.pos); 
					}
					if(game_map[npos.x][npos.y][npos.z].ist.player==lst_see_time){//������Ļ 
						game_flag["�����ڱ仯"]=true;
						pos_change.insert(npos); 
					}
					DRT.num[1]--;
					fdt.pos=npos;
					NDRT.num[1]++;
					darts.push(fdt);//���·Żض��� 
				}
				else{
					if(NTHING.crt.exist) damage_curtain(npos,50); 
					dart_fall(fdt);//����ǽ�����ӡ����ϵ��š�B��֩�븽֫�������š����Ӿ�ֹͣ����
				}
			}
		}
		void shoot_spider_silk(){//��˿���� 
			logMessage("shoot_spider_silk");
			int num=ssks.size();
			while(num>0){
				num--;
				flying_ssk fsk=ssks.front();ssks.pop();
				MAP &POS=game_map[fsk.pos.x][fsk.pos.y][fsk.pos.z];
				thing &THING=POS.things;
				spider_silk &ssk=THING.ssk;
				int d=0;//�ƶ����� 
				velocity *vlc;//�����ƶ��ķ����Ӧ�ٶȵ�ָ�루vx/vy�� 
				if(fsk.tx<=game_time){//x�� 
					d=(fsk.vx.speed>0?1:3);
					fsk.tx=game_time+fsk.vx.wait_time;
					vlc=&fsk.vx;
				}
				else if(fsk.ty<=game_time){//y�� 
					d=(fsk.vy.speed>0?2:0);
					fsk.ty=game_time+fsk.vy.wait_time;
					vlc=&fsk.vy;
				}
				else{//û���ƶ�ʱ�� 
					ssks.push(fsk);
					break;
				}
				position_3D npos=dtp3(fsk.pos,d,4);//��һ���ط� 
				MAP &NPOS=game_map[npos.x][npos.y][npos.z];
				thing &NTHING=NPOS.things;
				spider_silk &nssk=NTHING.ssk;
				if(pos_in_area2(npos.x,npos.y,1,1,length,width,2)
				&&!(door_here(npos,0)||door_here(npos,2)||wall_here(npos)||NTHING.mvb.exist&&NTHING.mvb.kind==BOX)//�޷����� 
				){
					if(game_map[fsk.pos.x][fsk.pos.y][fsk.pos.z].ist.player==lst_see_time){//������Ļ 
						game_flag["��˿�仯"]=true;
						pos_change.insert(fsk.pos); 
					}
					if(game_map[npos.x][npos.y][npos.z].ist.player==lst_see_time){//������Ļ 
						game_flag["��˿�仯"]=true;
						pos_change.insert(npos); 
					}
					ssk.num--;
					fsk.pos=npos;
					if(NTHING.mvb.exist&&(NTHING.mvb.kind==CHAIR||NTHING.mvb.kind==BOX)
					||NTHING.hdr.exist||NTHING.crt.exist||!nobody_here2(npos)) NTHING.snt.addedc(75,npos);//�������ס�� 
					else{//�ɹ� 
						nssk.num++;
						ssks.push(fsk);//���·Żض��� 
					} 
				}
				else{//����ס��ͣ��ǰ�棨fsk.pos�� 
					ssk.num--;
					THING.snt.addedc(75,fsk.pos);//�����汣��һ�� 
				}
			}
		}
		void fly_removable(){//�ӿ��ƶ���Ʒ��������� 
			logMessage("fly_removable");
			int num=mvbs.size()*2;//��ɨ����ʹx��y���ƶ� 
			queue<flying_mvb> mvbs_new; 
			while(!mvbs.empty()&&num>0){
				num--;
				flying_mvb fmb=mvbs.front();mvbs.pop();
				MAP &POS=game_map[fmb.pos.x][fmb.pos.y][fmb.pos.z];
				thing &THING=POS.things;
				movable &MVB=THING.mvb;
				force_move &FCMV=POS.fcmv;
				if(!FCMV.lock) continue;//������
				double speed=FCMV.speed();//���ٶȣ����� 
				if(speed<1//̫���� 
				||nobody_here2(fmb.pos)&&!mvb_here(fmb.pos)){//�ɵĶ���û�� 
					FCMV.init();//�ٶ����� 
					//game_flag["��"]=true;pos_change.insert(fmb.pos);
					continue;
				} 
				int d=0;//�ƶ����� 
				velocity *vlc;//�����ƶ��ķ����Ӧ�ٶȵ�ָ�루vx/vy�� 
				velocity &vx=FCMV.vx,&vy=FCMV.vy;
				if(fabs(vx.speed)>0.01&&FCMV.tx<=game_time){//x�� 
					d=(vx.speed>0?1:3);
					FCMV.tx=game_time+vx.wait_time;
					vlc=&vx;
				}
				else if(fabs(vy.speed)>0.01&&FCMV.ty<=game_time){//y�� 
					d=(vy.speed>0?2:0);
					FCMV.ty=game_time+vy.wait_time;
					vlc=&vy;
				}
				else{//û���ƶ�ʱ�� 
					mvbs.push(fmb);
					continue;
				}
				int lst_move_time=fmb.lst_move_time;//����һ�� 
				fmb.lst_move_time=game_time;
				THING.snt.addedc(-THING.snt.endurance/2,fmb.pos);//��֩������*0.5�� 
				int angle=calc_angle2(vx.speed,vy.speed);//��Ʒ�ƶ����� 
				position_3D npos=dtp3(fmb.pos,d,4);
				MAP &NPOS=game_map[npos.x][npos.y][npos.z];
				thing &NTHING=NPOS.things;
				movable &NMVB=NTHING.mvb;
				force_move &NFCMV=NPOS.fcmv;
				mirror &NMIRRORS=NTHING.mirrors;
				hurt_enemy(POS);
				hurt_enemy(NPOS);
				if(window_here(npos)){//ײ������/���� 
					NTHING.windows.damage(speed,npos);
					vx.speed*=0.8;vx.vt();//���� 
					vy.speed*=0.8;vy.vt();//���� 
					if(NPOS.ist.player==lst_see_time){
						game_flag["��"]=true;
						pos_change.insert(npos);
					}
				}
				if(!(wall_here(npos)||door_here(npos,0)||door_here(npos,2)||exit_here(npos))
				&&nobody_here(npos)&&!NMVB.exist
				&&(spider_here(fmb.pos)&&POS.emy.id>=0&&POS.emy.id<=spiders.size()?spider_through(npos,d,spiders[POS.emy.id].kind):1)){//���ܼ����ɣ�֩�����У� 
					if(POS.ist.player==lst_see_time){
						game_flag["��"]=true;
						pos_change.insert(fmb.pos);
					}
					if(NPOS.ist.player==lst_see_time){
						game_flag["��"]=true;
						pos_change.insert(npos);
					}
					fmb.pos=npos;//����λ�� 
					mvbs.push(fmb);//���·Żض���
					swap(NMVB,MVB);
					swap(NPOS.player_enemy,POS.player_enemy);
					swap(NPOS.emy.id,POS.emy.id);
					int id=NPOS.emy.id;
					//��ʱ���ƶ������� 
					if(NPOS.player_enemy==BUG&&id>=0&&id<bugs.size()){//�� 
						bug &bg=bugs[id];
						bg.pos=npos;
					}
					else if(NPOS.player_enemy==SPIDER&&id>=0&&id<spiders.size()){//֩�� 
						spider &sr=spiders[id];
						spider_update_leg(sr.pos,-1,id);
						sr.pos=npos;
						spider_update_leg(npos,1,id);
					}
					else if(NPOS.player_enemy==GHOST&&id>=0&&id<ghosts.size()){//�� 
						ghost &gh=ghosts[id];
						gh.pos=npos;
					}
					else if(NPOS.player_enemy==PLAYER){//�ƿ���� 
						NTHING.fpt.d=d;
						player1.items.rmv.select=pos000;
						player1.pos=npos;
						player_erase_spear();
					} 
					swap(NFCMV,FCMV);//game_flag["��"]=true;pos_change.insert(fmb.pos);pos_change.insert(npos);//���������ϢǨ�Ƶ���һ��λ��
					double deltav=(game_time-lst_move_time)*0.005;//�ٶ���Ħ�������ı��� 
					int speed2=max(0.0,speed-deltav);//��ֹ��������  
					NFCMV.init4(speed2,angle);//����
					//vx��vyͬ������ 
					vibrate_spider_net(npos,speed*1000);//��֩���� 
				}
				else{
					if(player_here(fmb.pos))//����ٶ�<=5����Ѫ 
						living_things_reduce_blood(fmb.pos,max(0.0,speed-5)*0.2,1,FCMV.from);
					else if(!(ghost_here(fmb.pos)&&POS.emy.id>=0&&POS.emy.id<ghosts.size()&&ghosts[POS.emy.id].rampage))
					//���ں��ֱײʱײ��Ҳ���Ѫ 
						living_things_reduce_blood(fmb.pos,speed*0.2,1,FCMV.from);
					int door_d=turn(d,TURN_BACK,4,19);
					if(mvb_here(npos)&&NMVB.kind!=BOX||!nobody_here2(npos)&&!closed_box_here(npos,door_d)){//�ж���/�����Ҳ������ӻ�B��֩�븽֫ 
						//game_flag["��"]=true;pos_change.insert(fmb.pos);pos_change.insert(npos);
						//���⶯���غ������Ⱑ 
						//����û������
						//2024.8.1 
						force_move &NFCMV=NPOS.fcmv;
						double v1x=vx.speed,v1y=vy.speed;
						double v2x=NFCMV.vx.speed,v2y=NFCMV.vy.speed;
						double v12x=v1x-v2x,v12y=v1y-v2y;
						double m1=POS.mass(),m2=NPOS.mass();
						double deltav1x=-2.0*m2/(m1+m2)*v12x,deltav2x=2.0*m1/(m1+m2)*v12x;
						double deltav1y=-2.0*m2/(m1+m2)*v12y,deltav2y=2.0*m1/(m1+m2)*v12y;
						double newv1x=v1x+deltav1x,newv1y=v1y+deltav1y;
						double newv2x=v2x+deltav2x,newv2y=v2y+deltav2y;
						if(fabs(newv1x)<0.1) newv1x=0;
						if(fabs(newv1y)<0.1) newv1y=0;
						if(fabs(newv2x)<0.1) newv2x=0;
						if(fabs(newv2y)<0.1) newv2y=0;
						//��ֹ�������� 
						FCMV.init3(newv1x,newv1y);//����
						NFCMV.init3(newv2x,newv2y);//����
						
						if(FCMV.speed()>=1){//�ı��Լ��ٶ�
							mvbs.push(fmb);
						}
						else FCMV.init();//ֹͣ�˶� 
						
						if(NFCMV.speed()>=1){//���ܴ��� 
							if(!NFCMV.lock){//���ڶ����� 
								flying_mvb nfmb;nfmb.init(npos);
								mvbs_new.push(nfmb);
								NFCMV.tx=NFCMV.ty=game_time;
								NFCMV.tx+=NFCMV.vx.wait_time;//��ֹ˲���ƶ�2�� 
								NFCMV.ty+=NFCMV.vy.wait_time;//��ֹ˲���ƶ�2��
								NFCMV.lock=1;
								//�ɲ���throw_thing() 
							}
							NFCMV.from=FCMV.from; 
						}
						else NFCMV.init();//ֹͣ�˶� 
						
						/*д��һ��ʺ 
						double v2=NPOS.fcmv.speed(),v12=speed-v2;
						double m1=POS.mass(),m2=NPOS.mass();
						double deltav1=-2.0*m2/(m1+m2)*v12,deltav2=2.0*m1/(m1+m2)*v12;
						if(fabs(v2+deltav2)>=1) throw_thing(npos,deltav2,0.5,angle,FCMV.from);//���ܴ��� 
						//else NPOS.fcmv.init();//��ײ����ֹͣ�˶� 
						double speed2=speed+deltav1;//FCMV�����ٶȣ������ɸ��� 
						if(speed2<0){
							speed2=-speed2;
							angle=(angle+180)%360;//����䷴ 
						}
						if(speed2>=1){
							FCMV.init4(speed2,angle);//����
							mvbs.push(fmb);//���·Żض��� 
						}
						else FCMV.init();//ֹͣ�˶�*/
					}
					else if(MVB.exist&&MVB.kind!=DESK&&speed>3&&RAND_BOOL(100)){//����û�д��ݵ��͸ı䷽��ֻ��mvb�ı䷽�� 
						double k=(MVB.kind==CHAIR?0.7:0.9);//˥��ϵ�� 
						vlc->speed=-(vlc->speed);vlc->vt();//��ǰ�ƶ��ٶȷ���ȡ��
						FCMV.init3(vx.speed*k,vy.speed*k);
						mvbs.push(fmb);//���·Żض��� 
						if(spider_leg_here(npos)&&NTHING.slg.id!=-1) spider_reduce_blood(NTHING.slg.id,0.5,FCMV.from);//ײ��B��֩�븽֫��Ѫ 
					}
					else FCMV.init();//ֹͣ�˶�
				}
			}
			while(!mvbs_new.empty()){//���µļӽ��� 
				flying_mvb u=mvbs_new.front();mvbs_new.pop();
				mvbs.push(u);
			}
		}
		void update_lights(){
			logMessage("update_lights");
			if(game_time%500==0) return;//���ÿ�����2��
			int num=pos_affect_light.size(),cnt=0;
			while(num>0&&cnt<=2){//Ҫ���¹��յ�λ�ã����Ƹ���Ƶ�ʣ� 
				num--;
				position_3D u=pos_affect_light.front();pos_affect_light.pop();
				MAP &POS=game_map[u.x][u.y][u.z];
				vector<PII> v;vector<position_3D> ret;
				for(int i=0;i<4;i++) v.push_back(MP(0,359));
				vision_init(1,v,ret,pos000);
				calculate_vision2(u,2,ret,INF,0);//�Ըı�ĵ�Ϊ��Դ���㡰���䡱��Χ���ҳ��� 
				for(int i=0;i<ret.size();i++){
					position_3D v=ret[i];
					MAP &NPOS=game_map[v.x][v.y][v.z];
					thing &NTHING=NPOS.things;
					light &NLGT=NTHING.lgt;
					if(NLGT.exist&&!NLGT.update){//��ֹ�ظ�����
						NLGT.update=true;//���������Ұ��Χ��������������ʱ���£���������� 
						if(pos_to_brightness(v,u,NLGT.p)>=5) lights_update.push(v);
						//�������յ���Ұ��Χ����Ʒ�ĵ�
					}
				}
				cnt++;
			}
			cnt=0;
			num=lights_update.size();
			while(num>0&&cnt<=1){
				num--;
				position_3D u=lights_update.front();lights_update.pop();
				MAP &POS=game_map[u.x][u.y][u.z];
				thing &THING=POS.things;
				light &LGT=THING.lgt;
				update_light_brightness(u);//����+���� 
				cnt++;
			}
		}
			void spread(int kind,position_3D u,position_3D v,double vel,int t){//u->v��ɢ��һ���Ũ�ȸߵ�Ũ�ȵͣ�
				MAP &UPOS=game_map[u.x][u.y][u.z];
				MAP &VPOS=game_map[v.x][v.y][v.z]; 
			    fog &UF=UPOS.things.fogs,&VF=VPOS.things.fogs;
				double (&a)[3]=UF.absorbance,(&b)[3]=VF.absorbance,tmp;
				//RGB_color &c=UF.col,&d=VF.col;
				switch(kind){
					case 0://������ɢ 
						for(int i=0;i<3;i++){//RGB
							tmp=abs(b[i]-a[i])*vel*t/1000.0;
							if(a[i]>b[i]) a[i]-=tmp,b[i]+=tmp;
							//else a[i]+=tmp,b[i]-=tmp;
							//ֻ����u->vŨ�ȸ�->�ͣ���ʡ���� 
						}//R/G/B��ɫ������ɢ 
						if(tmp>5&&UPOS.ist.player==lst_see_time&&VPOS.ist.player==lst_see_time
						&&game_flag["�ϴμ�������"]+500<=game_time){
							game_flag["������ɢ"]=true;//������Ұ 
							game_flag["�ϴμ�������"]=game_time;
						}
						break;
				}
			}
			void deal_fog(position_3D u,position_3D v){//��uƮ��v��fogu>fogv) 
				fog &FOGS=game_map[u.x][u.y][u.z].things.fogs;
				fog &NFOGS=game_map[v.x][v.y][v.z].things.fogs;
				if(!fog_through(v,u)) return;//����û���������� ||FOGS.absorbance<=NFOGS.absorbance
				spread(0,u,v,V_FOG_SPREAD,T_SPREAD_DELAY);
				if(!NFOGS.update){
					NFOGS.update=true;
					pos_fog.push(v);//��ɢ���½ڵ�
				}
				game_timer["��"]++;
			}
		void spread_fogs(){//������ɢ
			logMessage("spread_fogs");
			if(game_timer["������ɢ"]>game_time) return;//��һ��ʱ�����һ�� 
			game_timer["������ɢ"]=game_time+T_SPREAD_DELAY;
			int num=pos_fog.size();
			if(num==0) return;
			while(num--){
				position_3D u=pos_fog.front();pos_fog.pop();
				fog &FOGS=game_map[u.x][u.y][u.z].things.fogs;
				if(FOGS.exist()) pos_fog.push(u);//����һ������ͷŵ���β 
				else FOGS.update=false;//���ٸ������� 
				MAP &POS=game_map[u.x][u.y][u.z];
				for(int d=0;d<4;d++){
					position_3D v=dtp3(u,d,4);
					deal_fog(u,v);
				}
				if(upstair_here(u)) deal_fog(u,(position_3D){u.x,u.y,u.z+1});//��¥ 
				else if(downstair_here(u)) deal_fog(u,(position_3D){u.x,u.y,u.z-1});//��¥ 
				else if(bug_nest_here(u)) deal_fog(u,(position_3D){u.x,u.y,u.z+(u.z<=height?height:-height)});//Ʈ��/����Ѩ 
			}
		}
		void open_close_treasure(){
		}
		void on_off_candle(){
		}
		void move_barrel(){
		}
		void on_off_lamp(){
		}
		void delay_boom_TNT(){
		}
		void pour_water(){
		}
		void pour_magma(){
		}
	void deal_item(){
		logMessage("deal_item()",2);
		clean_dead(); 
		shoot_laser_beam();
		pierce_spear();
		throw_dart();
		shoot_spider_silk();
		fly_removable();
		update_lights();
		spread_fogs(); 
		open_close_treasure();
		on_off_candle();
		move_barrel();
		on_off_lamp();
		delay_boom_TNT();
		pour_water();
		pour_magma();
	}
		void player_flash_update(){
			logMessage("player_flash_update");
			if(player1.color!=0&&game_timer["���ͼ����˸"]<=game_time){
				player1.color=0;
				player1.flash=true;
			}
			if(player1.flash) pos_change.insert(player1.pos);
		}
		void game_map_update(){//������ʾ����Ļ�ϵ���Ϸ��ͼ 
			logMessage("game_map_update");
			//formatted_output(1,vital_signs_area,1,11,MMPP(0,360,-100,360),int_to_str(pos_in_sight.size(),3));
			//formatted_output(1,vital_signs_area,1,12,MMPP(0,360,-100,360),int_to_str(pos_change.size(),3));
			if(game_flag["�����Ұ���¼���"]
			||game_flag["��Ļ�����ж�"]&&game_time%100==0
			){
				game_flag["�����Ұ���¼���"]=game_flag["��Ļ�����ж�"]=false;
				int num=pos_lst_sight.size(),cnt=0;//�������
				while(num>0){//�ȴ�����յ��� 
					position_2D spos=pos_lst_sight.front();pos_lst_sight.pop();
					num--;
					if(!screen_z.count(spos)){
						if(pos_in_game_map(spos))
							formatted_output(1,whole_screen,spos.x,spos.y,MMPP(-100,360,-100,360),"  ");//�����Ļ�����λ��
						if(screen_pos.count(spos)) screen_pos.erase(spos);//��Ļ�����λ�õ���ʾ���ݱ����ò����ˣ�ɾ�� 
						continue;
					}
					position_3D npos=position_scrto3D(spos,screen_z[spos]);
					//��Ļ����ת��Ϊ��Ϸ��ͼ���꣬z���껻��������Ļ�϶�Ӧλ��Ҫ��ʾ��¥��
					string ncode=print_game_map_pos(npos,3);
					if(ncode!=screen_pos[spos])//����Ҫ��ʾ�����ݱ�����ϴβ�ͬ
						pos_lst_sight.push(spos);//�ı�������� 
					else pos_backup.insert(spos);//����Ļ�����λ�÷ŵ����ݶ�����
				}
				cnt=0; 
				while(!pos_lst_sight.empty()&&cnt<100){//�ٴ�����Ļ�ϸı��
					position_2D spos=pos_lst_sight.front();pos_lst_sight.pop();
					cnt++; 
					if(player1.spe.cfs.exist()&&RAND_BOOL(player1.spe.cfs.a)) continue;//��ҡ��Ի󡿣�ֻ��ն��в���� 
					position_3D npos=position_scrto3D(spos,screen_z[spos]);
					//��Ļ����ת��Ϊ��Ϸ��ͼ���꣬z���껻��������Ļ�϶�Ӧλ��Ҫ��ʾ��¥��
					screen_pos[spos]=print_game_map_pos(npos,1);//����µ����ݲ�����Ļ�����λ�õ���ʾ���ݱ������ 
					pos_backup.insert(spos);//����Ļ�����λ�÷ŵ����ݶ�����
				}
				if(!pos_lst_sight.empty()) game_flag["��Ļ�����ж�"]=true;//�ж��Ƿ�����ɾ� 
				num=pos_in_sight.size(); 
				cnt=0; 
				while(num>0&&cnt<50){//���Ŵ�����������ʾ����Ļ�� 
					position_3D npos=pos_in_sight.front();pos_in_sight.pop();
					num--;
					position_2D spos=position_3Dtoscr(npos);//npos����Ļ�ϵĶ�Ӧλ��
					screen_pos[spos]=print_game_map_pos(npos,1);//������������λ�õ���Ļ��Ϣ
					cnt++; 
					pos_backup.insert(spos);
				}
				if(!pos_in_sight.empty()) game_flag["��Ļ�����ж�"]=true;//�ж��Ƿ�����ɾ� 
				set<position_2D>::iterator it;
				for(it=pos_backup.begin();it!=pos_backup.end();it++){//��󱸷ݶ��е�����ȫ��copy���ϴ���ʾ����Ļ�ģ����´�ѭ���ã� 
					position_2D spos=*it;
					pos_lst_sight.push(spos);
				}
				pos_backup.clear();
				if(!game_flag["��Ļ�����ж�"]) screen_z.clear();//�����ϵ��´Σ���� 
				pos_change.clear();//���¼�����Ұ����ղ��ָ��µĶ��� 
			}
			else if(!pos_change.empty()//int cnt=0; &&cnt<=10���ָ��£�������
			){//���û�ƶ�����ʾ����Ϸ��ͼ�����б�ı仯������ͻȻð��һ���������⴦��
				while(pos_change.size()>0){
					position_3D npos=*(pos_change.begin());pos_change.erase(npos);
					position_2D spos=position_3Dtoscr(npos);//npos����Ļ�ϵĶ�Ӧλ�� 
					//string ncode=print_game_map_pos(npos,3);
					//if(ncode!=screen_pos[spos])//����Ҫ��ʾ�����ݱ�����ϴβ�ͬ
					screen_pos[spos]=print_game_map_pos(npos,1);//������������λ�õ���Ļ��Ϣ
					pos_lst_sight.push(spos);//��ӵ��ϴ���ʾ����Ļ�ģ����»غ��ã�
					//cnt++;
				}
			}
			/*&&game_time%50==0
			||(player1.enemy_move||player1.flash||player1.use_weapon||player1.items.rmv.dl_change
			||game_flag["���˱���ҹ���"]||game_flag["���ʬ��"]||game_flag["������"]||game_flag["��Ѫ"]||game_flag["����¥����"] 
			||game_flag["���ì�ı�λ��"]||game_flag["��ҽ��ı�λ��"]||game_flag["�����ڱ仯"]||game_flag["��Ʒ��"]||game_flag["��˿�仯"]
			||game_flag["������"]||game_flag["��"]||game_flag["��"]||game_flag["��noply"]
			||game_flag["���ո���"])*/
		}
			void lives_update(){//��������������� ",double_to_str(player1.vts.lfin.hurt,1),"repeat_str("��",x)repeat_str("��",y)
				logMessage("lives_update");
				if(player1.vts.lfin.change||player1.d1_change||player1.items.sn_change){
					if(player1.vts.lfin.life<10) formatted_output(1,vital_signs_area,0,0,MMPP(-100,360,0,0),"������Σ��");
					else{
						int x=player1.vts.lfin.life/10.0,y=(player1.vts.lfin.hurt+10-eps)/10.0;
						formatted_output(1,vital_signs_area,0,0,MMPP(-100,360,0,0),"                                        ");
						formatted_output(1,vital_signs_area,0,0,MMPP(-100,360,0,0)
						,"����ֵ��"+repeat_str("��",x)+repeat_str("��",y));
					}//"����ֵ��"+repeat_str("��",x)+repeat_str("��",y)+"       "+int_to_str(x)+"                 "
				}
				if(player1.vts.stg.change||player1.d1_change||player1.items.sn_change){
					string s="";//��ʾ��Ϣ 
					if(player1.vts.stg.physical_strength<25) s="�����漱��";
					else s="          ";
					formatted_output(1,vital_signs_area,50,0,MMPP(-100,360,0,120)
					,"����ֵ��"+int_to_str(player1.vts.stg.physical_strength)+"%  "+s);
				}
			}
			void score_update(){//�������� 
				logMessage("score_update");
				if(player1.scr.kc.change)
					formatted_output(1,vital_signs_area,160,0,MMPP(-100,360,0,60),"��ɱ����"+int_to_str(player1.scr.kc.sum));
			}
			void state_update(){//���״̬���� 
				logMessage("state_update");
				/*
				if(player1.ak_change||player1.d1_change||player1.items.sn_change)
					switch(player1.action_kind){
						case RUN:formatted_output(1,vital_signs_area,1,5,MMPP(-100,360,0,180),"����     ");break;
						case WALK:formatted_output(1,vital_signs_area,1,5,MMPP(-100,360,0,180),"����     ");break;
						case CHOOSE_ITEM:formatted_output(1,vital_signs_area,1,5,MMPP(-100,360,0,180),"ѡ����Ʒ ");break;
						case CHANGE_WPN:formatted_output(1,vital_signs_area,1,5,MMPP(-100,360,0,180),"�л����� ");break;
					}*/
				if(game_flag["��Ϸ��ͣ/����"]) formatted_output(1,whole_screen,1,47,MMPP(-100,360,0,360),(game_pause?"��Ϸ��ͣ":"        "));
			}
			void special_effect_update(){//��ӡ����Ч�� 
				logMessage("special_effect_update");
				//int cnt_spe=0;//��ӡ��Ч������ 
				string spe_sentence;//����һ�仰 
				special_effect &spe=player1.spe;
				bool flag_1s=game_time%1000==0;//һ��ʱ�����ѵ� 
				if(!flag_1s&&!spe.change()) return;//���ø�����Ļ int_to_str(++cnt_spe)+".
				if(spe.xry.change||spe.xry.num>1){//͸�� 
					spe_sentence+="��͸��"+int_to_str(spe.xry.num-1)+"�㣬"
					+int_to_str(spe.xry.time>=game_time?(spe.xry.time-game_time)/1000:0)+"�롿";
				}
				if(spe.wks.change||spe.wks.exist()){//����
					spe_sentence+="������"//+"-"+int_to_str(spe.wks.x)+"����/�룬"
					+int_to_str(spe.wks.end>=game_time?(spe.wks.end-game_time)/1000:0)+"�롿";
				}
				if(spe.vtg.change||spe.vtg.exist()){//ѣ��
					spe_sentence+="��ѣ��"//+double_to_str(spe.vtg.T/1000.0,1)+","
					+int_to_str(spe.vtg.end>=game_time?(spe.vtg.end-game_time)/1000:0)+"�롿";
				}
				if(spe.bds.change||spe.bds.exist()){//��ä
					spe_sentence+="��ʧ��"//+int_to_str(spe.bds.vision_dis)+","
					+int_to_str(spe.bds.end>=game_time?(spe.bds.end-game_time)/1000:0)+"�롿";
				}
				if(spe.mts.change||spe.mts.exist()){//�ж�
					spe_sentence+="���ж�"//+double_to_str(spe.mts.T/1000.0,1)+","+int_to_str(spe.mts.x)+","
					+int_to_str(spe.mts.end>=game_time?(spe.mts.end-game_time)/1000:0)+"�롿";
				}
				if(spe.cfs.change||spe.cfs.exist()){//�Ի�
					spe_sentence+="���Ի�"//+int_to_str(spe.cfs.a)
					+int_to_str(spe.cfs.end>=game_time?(spe.cfs.end-game_time)/1000:0)+"�롿";
				}
				int mx_size=70;
				if(spe_sentence.size()<=mx_size) spe_sentence+=repeat_char(' ',mx_size-spe_sentence.size());
				else spe_sentence.resize(mx_size);
				formatted_output(1,vital_signs_area,90,0,MMPP(-100,360,0,360),spe_sentence);
			}
			void weapon_update(){//����״̬���� 
				logMessage("weapon_update");
				if(player1.ak_change) player1.items.wpn_print1();
				if(player1.items.wpn.mode_change||player1.items.wpn.data_change||player1.items.wpn.sw_change) player1.items.wpn_print2();
				if(player1.items.wpn.sw_change) player1.items.wpn_print3();
			}
		void vital_signs_update(){
			logMessage("vital_signs_update");
			lives_update();
			score_update();
			state_update();
			special_effect_update();
			weapon_update();
		}
		void item_update(){
			logMessage("item_update");
			if(player1.ak_change) player1.items.print1();
			if(player1.items.il_change||player1.items.sn_change) player1.items.print2();
			if(player1.items.num_change||player1.items.sn_change) player1.items.print3();
		}
		void message_update(){
			logMessage("message_update");
			if(game_time%2000==0){
				int cnt=1,num=10;//�����Ϣ���� 
				while(!message_box.empty()&&cnt<=num){
					PPII u=message_box.front();message_box.pop();
					PII a=u.first,b=u.second;
					formatted_output(1,whole_screen,1,35+cnt,MMPP(-100,360,0,360)
					,being_name(a)+"��ɱ��"+being_name(b)+"                ");
					cnt++;
				}
				while(cnt<=num) formatted_output(1,whole_screen,1,20+cnt,MMPP(-100,360,0,360),"                            "),cnt++;
			}
		}
	void screen_update(){//��Ļ���� 
		logMessage("screen_update()",2); 
		player_flash_update();
		game_map_update();
		vital_signs_update();
		item_update();
		message_update();
		if(game_time%100==0){
			formatted_output(1,whole_screen,1,16,MMPP(0,30,-100,360),double_to_str(player1.w.speed,0,6));//+int_to_str(bugs.size(),6)
			formatted_output(1,whole_screen,1,17,MMPP(0,360,-100,360),int_to_str(pos_fog.size(),6));
			formatted_output(1,whole_screen,1,18,MMPP(0,360,-100,360),int_to_str(bugs.size(),6));
			formatted_output(1,whole_screen,1,19,MMPP(0,360,-100,360),int_to_str(Qbug.size(),6));
			formatted_output(1,whole_screen,1,20,MMPP(0,360,-100,360)
			,int_to_str(player1.pos.x,2)+","+int_to_str(player1.pos.y,2)+","+int_to_str(player1.pos.z,2));
			game_timer["��"]=0;
		}
		/**/
		//	if(game_time%1000==0){
				//formatted_output(1,vital_signs_area,1,16,MMPP(0,360,-100,360),int_to_str(game_timer["��"],6));
				//formatted_output(1,vital_signs_area,1,7,MMPP(0,360,-100,360),int_to_str(game_timer["ѭ"],6));//����ͳ��calculate_vision2�ĵ��ô��� 
				//formatted_output(1,vital_signs_area,1,16,MMPP(0,360,-100,360),int_to_str(game_timer["֩��"],6));
		//		game_timer["ѭ"]=game_timer["��"]=0;
				
		//	}
			//formatted_output(1,vital_signs_area,1,17,MMPP(0,360,-100,360),int_to_str(Qbug.size(),2));
	}
		void judge_win_lose(){
		}
		void delay_time(){//��ʱ1���� 
			do read_timer();
			while(now_timer<start_time+1);
			game_time+=now_timer-start_time;
		}
	void others(){
		logMessage("others()",2); 
		judge_win_lose();
		delay_time();
	}
void game(){//��Ϸ���� 
	//��ǰ��Ҫ���� 
	logMessage("game()",2);
	game_time=1;
	//print_maze();
	while(!game_end){
		read_timer();start_time=now_timer;//����ѭ����ʼʱ�� 
		assigned();
		pause();
		if(game_pause) continue;//��Ϸ��ͣ 
		deal_item();
		deal_enemy();
		deal_player();
		screen_update();
		others();
	}
} 
void win(){
	score &scr=player1.scr;
	MUSIC("Win.wav",1);
	formatted_output(2,whole_screen,40,19,MMPP(-100,360,0,120),
	"��Ӯ�ˣ�"+player1.name+"����������ʱ"+to_time(0,0,scr.time_spent/1000)+"��",1,150);
} 
void lose(){
	score &scr=player1.scr;
	MUSIC("Lose.wav",1);
	formatted_output(1,whole_screen,40,19,MMPP(-100,360,0,0),
	"�����ˣ�"+player1.name+"���������"+to_time(0,0,scr.time_spent/1000)+"��");
}
void detail(){//��ϸ��Ϸ��Ϣ����չʾ 
	PPII col=MMPP(-100,360,0,360);
	int kind=2;
	if(game_success) col=MMPP(-100,360,0,120),kind=2;
	else col=MMPP(-100,360,0,240),kind=1;
	score &scr=player1.scr;
	formatted_output(kind,whole_screen,40,20,col,"��ϸ��Ϣ��",1,150);
	if(scr.shoot_times!=0) scr.hit_rate=scr.shoot_hit_times*1.0/scr.shoot_times;//
	else scr.hit_rate=0;
	formatted_output(kind,whole_screen,40,21,col,
	"��ͼ��С����"+int_to_str(length)+"�� ��"+int_to_str(width)+"�� ��"+int_to_str(height)+"��"
	,1,150);
	formatted_output(kind,whole_screen,40,22,col,
	"��ɱ����"+int_to_str(scr.kc.sum)+" ��������ʣ�"+double_to_str(scr.hit_rate*100.0,1)+"%"
	,1,150);//
	formatted_output(kind,whole_screen,40,23,col,scr.kc.detail(),1,150);//��ӡ��ϸ 
	formatted_output(kind,whole_screen,40,24,col,
	"���ܹ���������"+int_to_str(scr.hurt_times)
	+" ʧȥ����ֵ��"+double_to_str(player1.vts.lfin.hurt)+"% �ظ�����ֵ��"+double_to_str(player1.vts.lfin.recovery)+"%"
	,1,150);
	if(kind==1) SLEEP(2000);
}
	void detect_start_again(){
		while(1){
			if(kbhit()){
				int c=_getch();
				switch(c){
					case PRESS_KEY_X:start_again=false;return;
					case PRESS_KEY_ENTER:start_again=true;return;
				}
			}
		}
	}
void ask_try_again(){
	formatted_output(1,whole_screen,40,25,MMPP(-100,360,0,360),"���»س����¿�ʼ ����X���˳���Ϸ");
	detect_start_again();//wait_until(PRESS_KEY_ENTER);start_again=true; 
	formatted_output(2,whole_screen,40,25,MMPP(-100,360,0,180),"��Ϸ������......",1,100);
}
void end(){//��ʱ���� 
	//��ǰҪ���� 
	formatted_output(2,whole_screen,40,20,MMPP(-100,360,0,60),player1.name+"����ӭ�´�������",1,150);
}
//�������� 
