#include <string>
#include <iostream>
#include <vector>
using namespace std;

#if 0
class card
{
	int  time = 0;//Ĭ��ʱ��Ϊ0,��ʱ������
	int index = 1;//��ʾ�ڼ�����
	int type;//������,��λ����abc��a = ��ɫ�����顢÷�������ҡ����ң�; bc = ����, 3-10,J,Q,K,A,2 = 3-15,����С��116,117
	string userid;//�û�ID,Ĭ��Ϊ��
};
#elif 0
class card_dz
{
	//�����е����Ͳ��ֻ�ɫ��3 - 10�ֱ���3 - 10����11����J��12����Q��13����K��14����A��15����2, 99����С����100�������
	//dz���������n1����������ϼ�ũ��n2����������¼�ũ��
	int n1;
	int n2;
	int dz[20];
	int nn[54 - 20];//ʣ�����
};

class card_n
{
	int dz;
	int n;
	int nm[17];
	int nn[54 - 17];//ʣ�����
};
#else
class card
{
	int DZIndex;
	bool GoodNM;
	bool IsDZ;//������
	bool IsOut;//�������ƣ�
	//����ʣ������
	int RestRounds;//ʣ�����ƻغ�
	int frontN;//ǰ��
	int behindN;//���
	int myN;//��
	int KingBoom;
	int deck[20][2]; int deckIndex; //�������� ����㣬��������ǩ ��1��2��3Ϊ˳�ӡ����ԡ��ɻ���4Ϊը����0Ϊɢ�ƣ�
	int deckTwo[20][2]; int deckTwoIndex;
	int deckThree[20][2]; int deckThreeIndex;
	int One[20]; int OneIndex;//����
	int OneMax[20]; int OneMaxIndex;
	int OneElseMax;
	int Two[20]; int TwoIndex;//˫��
	int TwoMax[20]; int TwoMaxIndex;
	int TwoElseMax;
	int Three[20]; int ThreeIndex;//����ͷ
	int ThreeMax[20]; int ThreeMaxIndex;
	int ThreeElseMax;
	int Four[20]; int FourIndex;//ը��
	//�� [3](3) - [15](2) 16(С��) 17(������
	int myCard[20];//�ҵ�����
	int elseCard[20];//���ֵ�ʣ�����
	int c_list[20];//������
	int mostLike;//����ϲ������
public:
	card();
	card(int * Cards);
	card(int * Cards, int * BCards, int * FCards, int DZIndex);
	~card();
	int GetBestSort(int x);
	int ScoreOfDZ();//�е����ķ���,ը��������С����2���ɻ���«
	bool CallDZ(int score, int MyScore);//�е����������� //������ȽУ���score=0,���������������ôscore=1;
	int SortTheCard();//����
	void SerchTheProgression(int LengthOfPg, int *Cards, int * result, int *Sum);//�ҳ���ΪN��˳��
	void ActivePlay(int * Out);//����
	int PassivePlay(int *UpperCard, int * Out, int WhoseOut = -1);//����
	void EmergentOfOne();//����
	void DZorNot(int * C, int YesOrNo);//��������
	void UpdateC(int * C, int num, int whoseC);//������
	int GetRestRound();
	void IsGoodNM();
	void InToOut(int * out);
	void CaLL(int I);
	void Sort(int * Out,vector<int> &vc);
};
#endif

