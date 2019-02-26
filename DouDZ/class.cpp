#include "class.h"

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
//class card
//{
//	bool IsDZ = false;//������
//	bool IsOut = false;//���ƣ�
//	//����ʣ������
//	int frontN = 17;//ǰ��
//	int behindN = 17;//���
//	int myN = 17;//��
//	int KingBoom = 0;
//	int deck[20][2];int deckIndex = 0; //�������� ����㣬��������ǩ ��1��2��3Ϊ˳�ӡ����ԡ��ɻ���4Ϊը����0Ϊɢ�ƣ�
//	int deckTwo[20][2];int deckTwoIndex = 0;
//	int deckThree[20][2]; int deckThreeIndex =0;
//	int One[20];int OneIndex = 0;//����
//	int Two[20];int TwoIndex = 0;//˫��
//	int Three[20]; int ThreeIndex = 0;//����ͷ
//	int Four[20]; int FourIndex = 0;//ը��
//	//�� [3](3) - [15](2) 16(С��) 17(������
//	int myCard[20];//��ʣ��
//	int elseCard[20];//����ʣ�����
//	int c_list[20];//������
//	int mostLike = 0;//����ϲ������
//public:
//	card(int * Cards);
//	~card();
//	int ScoreOfDZ();//�е����ķ���,ը��������С����2���ɻ���«
//	bool CallDZ(int score, int MyScore);//�е����������� //������ȽУ���score=0,���������������ôscore=1;
//	int SortTheCard();//����
//	void SerchTheProgression(int LengthOfPg, int *Cards, int * result, int *Sum);//�ҳ���ΪN��˳��
//	void ActivePlay();//����
//	int PassivePlay(int *UpperCard, int * Out);//����
//	void EmergentOfOne();//����
//	void DZorNot(int * C, int YesOrNo);//��������
//	void UpdateC(int * C, int num, int whoseC);//������
//};
card::~card()
{

}

card::card()
{
	GoodNM = false;
	IsDZ = false;//������
	IsOut = false;//�������ƣ�
	//����ʣ������
	RestRounds = 0;//ʣ�����ƻغ�
	frontN = 17;//ǰ��
	behindN = 17;//���
	myN = 17;//��
	KingBoom = 0;//��ը
	deckIndex = 0; //�������� ����㣬��������ǩ ��1��2��3Ϊ˳�ӡ����ԡ��ɻ���4Ϊը����0Ϊɢ�ƣ�
	deckTwoIndex = 0;
	deckThreeIndex = 0;
	OneIndex = 0;//����
	OneMaxIndex = 0;
	OneElseMax = 0;
	TwoIndex = 0;//˫��
	TwoMaxIndex = 0;
	TwoElseMax = 0;
	ThreeIndex = 0;//����ͷ
	ThreeMaxIndex = 0;
	ThreeElseMax = 0;
	FourIndex = 0;//ը��
	//�� [3](3) - [15](2) 16(С��) 17(������
	mostLike = 0;//����ϲ������
}

card::card(int * Cards)//��ʼ������ ������
{
	GoodNM = false;
	IsDZ = false;//������
	IsOut = false;//�������ƣ�
	//����ʣ������
	RestRounds = 0;//ʣ�����ƻغ�
	frontN = 17;//ǰ��
	behindN = 17;//���
	myN = 17;//��
	KingBoom = 0;
	deckIndex = 0; //�������� ����㣬��������ǩ ��1��2��3Ϊ˳�ӡ����ԡ��ɻ���4Ϊը����0Ϊɢ�ƣ�
	deckTwoIndex = 0;
	deckThreeIndex = 0;
	OneIndex = 0;//����
	OneMaxIndex = 0;
	OneElseMax = 0;
	TwoIndex = 0;//˫��
	TwoMaxIndex = 0;
	TwoElseMax = 0;
	ThreeIndex = 0;//����ͷ
	ThreeMaxIndex = 0;
	ThreeElseMax = 0;
	FourIndex = 0;//ը��
	//�� [3](3) - [15](2) 16(С��) 17(������
	mostLike = 0;//����ϲ������
	//�ҵ��� �ͼ�����
	for (int i = 3; i < 16; ++i)
	{
		myCard[i] = Cards[i];
		elseCard[i] = 4 - Cards[i];
	}
	myCard[16] = Cards[16];
	myCard[17] = Cards[17];
	elseCard[16] = 1 - Cards[16];
	elseCard[17] = 1 - Cards[17];
	SortTheCard();
	RestRounds = GetRestRound();
}
/*
�ж������Ƶ�����
*/
void card::InToOut(int * out)
{
	if (deckIndex == 1)
	{
		out[0] = deck[0][0];
		out[1] = deck[0][1];
		out[2] = 1;
	}
	else if (deckIndex == 2)
	{
		out[0] = deck[0][0];
		out[1] = deck[0][1];
		out[2] = 2;
	}
	else if (deckTwoIndex == 1)
	{
		out[0] = deckTwo[0][0];
		out[1] = deckTwo[0][1];
		out[2] = 2;
	}
	else if (deckThreeIndex == 1)
	{
		out[0] = deckThree[0][0];
		out[1] = deckThree[0][1];
		out[2] = 3;
		if (OneIndex > 0)
		{
			out[3] = 3;
			out[4] = 1;
		}
		else if (TwoIndex > 0)
		{
			out[3] = 3;
			out[4] = 2;
		}
	}
	else if (ThreeIndex == 1)
	{
		out[0] = Three[0];
		out[1] = 3;
		out[2] = 0;
		if (OneIndex > 0)
		{
			out[3] = 3;
			out[4] = 1;
		}
		else if (TwoIndex > 0)
		{
			out[3] = 3;
			out[4] = 2;
		}
	}
	else if (FourIndex == 1)
	{
		out[0] = Four[0];
		out[1] = 4;
		out[2] = 4;
		if (OneIndex > 0)
		{
			out[3] = 3;
			out[4] = 1;
		}
		else if (TwoIndex > 0)
		{
			out[3] = 3;
			out[4] = 2;
		}
	}
	else if (KingBoom == 1)
	{
		out[0] = 17;
		out[1] = 2;
		out[2] = 4;
	}
	else if (TwoIndex == 1)
	{
		out[0] = Two[0];
		out[1] = 2;
		out[2] = 0;
	}
	else
	{
		out[0] = One[0];
		out[1] = 1;
		out[2] = 0;
	}
}
/*
��֪��ʲô��
*/
card::card(int * Cards, int * BCards, int *FCards, int DZindex)
{
	GoodNM = false;
	IsDZ = false;//������
	IsOut = false;//�������ƣ�
	//����ʣ������
	RestRounds = 0;//ʣ�����ƻغ�
	frontN = 17;//ǰ��
	behindN = 17;//���
	myN = 17;//��
	KingBoom = 0;
	deckIndex = 0; //�������� ����㣬��������ǩ ��1��2��3Ϊ˳�ӡ����ԡ��ɻ���4Ϊը����0Ϊɢ�ƣ�
	deckTwoIndex = 0;
	deckThreeIndex = 0;
	OneIndex = 0;//����
	OneMaxIndex = 0;
	OneElseMax = 0;
	TwoIndex = 0;//˫��
	TwoMaxIndex = 0;
	TwoElseMax = 0;
	ThreeIndex = 0;//����ͷ
	ThreeMaxIndex = 0;
	ThreeElseMax = 0;
	FourIndex = 0;//ը��
	//�� [3](3) - [15](2) 16(С��) 17(������
	mostLike = 0;//����ϲ������

	myN = behindN = frontN = 0;
	for (int i = 3; i < 18; ++i)
	{
		myN += Cards[i];
		behindN += BCards[i];
		frontN += FCards[i];
		myCard[i] = Cards[i];
		elseCard[i] = FCards[i] + BCards[i];
	}
	if (DZindex == 1)
	{
		IsDZ = true;
	}
	else if (DZindex == 2)
	{
		DZIndex = 1;
		IsGoodNM();
	}
	else
	{
		DZIndex = -1;
		IsGoodNM();
	}
	SortTheCard();
	RestRounds = GetRestRound();
}

int card::GetRestRound()//�󻹿��Գ����غϵ����Ž�
{
	//���Ż�
	int numOfRound = deckIndex + deckTwoIndex + ThreeIndex + deckThreeIndex + FourIndex + KingBoom;
	int sum = ThreeIndex;
	if (sum < OneIndex + TwoIndex)
	{
		numOfRound += OneIndex + TwoIndex - sum;
	}
	return numOfRound;
}

void card::UpdateC(int * C, int num, int whoseC)//������������
{
	if (whoseC == 0)
	{
		myN -= num;
		for (int i = 0; i < num; ++i)
		{
			myCard[C[i]]--;
		}

	}
	else
	{
		for (int i = 0; i < num; ++i)
		{
			elseCard[C[i]]--;
		}
		if (whoseC == 1)
		{
			behindN -= num;
		}
		else
		{
			frontN -= num;
		}
	}
	int maxOneRest = 0, maxTwoRest = 0, maxThreeRest = 0;;
	for (int i = 3; i < 16; ++i)
	{
		if (elseCard[i] > 2)
		{
			if (i > maxThreeRest)
			{
				maxThreeRest = i;
			}
			if (i > maxTwoRest)
			{
				maxTwoRest = i;
			}
			if (i > maxOneRest)
			{
				maxOneRest = i;
			}
		}
		else if (elseCard[i] > 1)
		{
			if (i > maxTwoRest)
			{
				maxTwoRest = i;
			}
			if (i > maxOneRest)
			{
				maxOneRest = i;
			}
		}
		else if (elseCard[i] > 0)
		{
			if (i > maxOneRest)
			{
				maxOneRest = i;
			}
		}
	}
	if (elseCard[16] == 1)
	{
		maxOneRest = 16;
	}
	if (elseCard[17] == 1)
	{
		maxOneRest = 17;
	}
	//�������
	OneElseMax = maxOneRest;
	TwoElseMax = maxTwoRest;
	ThreeElseMax = maxThreeRest;
}

void card::DZorNot(int * C, int YesOrNo)//�������� 1�������Ǻ�ң� 0Ϊ�Լ�
{
	const int DZaddC = 3;
	if (YesOrNo == 0)
	{
		IsDZ = true;
		myN += DZaddC;
		for (int i = 0; i < DZaddC; ++i)
		{
			myCard[C[i]]++;
			elseCard[C[i]]--;
		}
	}
	else if (YesOrNo ==1)
	{
		behindN += DZaddC;
	}
	else
	{
		frontN += DZaddC;
	}
}
/*
��������
*/
void card::ActivePlay(int * Out)//���� WhoseOut �Ѿ�=1 ���� -1
{
	if (GetRestRound() == 1)
	{
		if (deckIndex == 1)
		{
			Out[0] = deck[0][0];
			Out[1] = deck[0][1];
			Out[2] = 1;
			deckIndex--;
			return;
		}
		else if (deckTwoIndex == 1)
		{
			Out[0] = deckTwo[0][0];
			Out[1] = deckTwo[0][1];
			Out[2] = 2;
			deckTwoIndex--;
			return;
		}
		else if (deckThreeIndex == 1)
		{
			Out[0] = deckThree[0][0];
			Out[1] = deckThree[0][1];
			Out[2] = 3;
			deckThreeIndex--;
		}
		else if (ThreeIndex == 1)
		{
			Out[0] = Three[0];
			Out[1] = 3;
			Out[2] = 0;
			ThreeIndex--;
			if (OneIndex > 0)
			{
				Out[3] = One[0];
				Out[4] = 1;
				OneIndex--;
			}
			else if (TwoIndex > 0)
			{
				Out[3] = Two[0];
				Out[4] = 2;
				TwoIndex--;
			}
			else
			{
				//����
			}
			return;
		}
		else if (OneIndex == 1)
		{
			Out[0] = One[0];
			Out[1] = 1;
			Out[2] = 0;
			OneIndex--;
		}
		else if (TwoIndex == 1)
		{
			Out[0] = Two[0];
			Out[1] = 2;
			Out[2] = 0;
			TwoIndex--;
		}
		else if (KingBoom == 1)
		{
			Out[0] = 17;
			Out[1] = 2;
			Out[2] = 4;
			KingBoom = 0;
		}
		else if (FourIndex == 1)
		{
			Out[0] = Four[0];
			Out[1] = 4;
			Out[2] = 4;
			FourIndex--;
		}
		else
		{
			//û���ˣ�
		}
		return;
	}
	if (GetRestRound() == 2)
	{
		if (deckIndex == 1)
		{
			Out[0] = deck[0][0];
			Out[1] = deck[0][1];
			Out[2] = 1;
			deckIndex--;
			return;
		}
		else if (deckTwoIndex == 1)
		{
			Out[0] = deckTwo[0][0];
			Out[1] = deckTwo[0][1];
			Out[2] = 2;
			deckTwoIndex--;
			return;
		}
		else if (deckThreeIndex == 1)
		{
			Out[0] = deckThree[0][0];
			Out[1] = deckThree[0][1];
			Out[2] = 3;
			deckThreeIndex--;
			if (TwoIndex == 1)
			{
				Out[3] = Two[0];
				Out[4] = 1;
				Out[5] = Two[0];
			}
			return;
		}
		else if (ThreeIndex == 1)
		{
			Out[0] = Three[0];
			Out[1] = 3;
			Out[2] = 0;
			ThreeIndex--;
			if (OneIndex > 0 && TwoIndex > 0)//ʲôС���ĸ�
			{
				if (One[0] < Two[0])
				{
					Out[3] = One[0];
					Out[4] = 1;
					OneIndex--;
					for (int i = 0; i < OneIndex; ++i)
					{
						One[i] = One[i + 1];
					}
				}
				else
				{
					Out[3] = Two[0];
					Out[4] = 2;
					TwoIndex--;
					for (int i = 0; i < TwoIndex; ++i)
					{
						Two[i] = Two[i + 1];
					}
				}
			}
			else if (OneIndex > 0)//����
			{
				Out[3] = One[0];
				Out[4] = 1;
				OneIndex--;
				for (int i = 0; i < OneIndex; ++i)
				{
					One[i] = One[i + 1];
				}
			}
			else if (TwoIndex > 0)//����
			{
				Out[3] = Two[0];
				Out[4] = 2;
				TwoIndex--;
				for (int i = 0; i < TwoIndex; ++i)
				{
					Two[i] = Two[i + 1];
				}
			}
			else
			{
				//����
			}
			return;
		}
		else if (OneIndex == 2 && One[1] >= OneElseMax)
		{
			Out[0] = One[1];
			Out[1] = 1;
			Out[2] = 0;
			OneIndex--;
			return;
		}
		else if (OneIndex == 1 && One[0] >= OneElseMax)
		{
			Out[0] = One[0];
			Out[1] = 1;
			Out[2] = 0;
			OneIndex--;
			return;
		}
		else if (TwoIndex == 2 && Two[1] >= TwoElseMax)
		{
			Out[0] = Two[1];
			Out[1] = 2;
			Out[2] = 0;
			TwoIndex--;
			return;
		}
		else if (TwoIndex == 1 && Two[0] >= TwoElseMax)
		{
			Out[0] = Two[0];
			Out[1] = 2;
			Out[2] = 0;
			TwoIndex--;
			return;
		}
		else
		{
			//û���ˣ�
		}
	}
	if (IsDZ)//����AI
	{
		//************************�����ұ�˫****************************//
		if ((frontN == 1 || behindN == 1) && (frontN == 2 || behindN == 2))
		{
			if (deckThreeIndex > 0)//�ѷɻ����ˣ�������ѹ����
			{
				for (int i = 0; i < deckThreeIndex; ++i)
				{
					bool flag = false;
					for (int j = 0; j < ThreeIndex; j++)
					{
						if (Three[j] > deckThree[i][0])
						{
							flag = true;
							for (int k = ThreeIndex; k > j; --k)
							{
								Three[k - 1 + deckThree[i][1]] = Three[k - 1];
							}
							ThreeIndex += deckThree[i][0];
							for (int k = 0; k < deckThree[i][1]; ++k)
							{
								Three[j + k] = deckThree[i][0] + k;
							}
						}
					}
					if (flag == false)
					{
						for (int k = 0; k < deckThree[i][1]; ++k)
						{
							Three[ThreeIndex + k] = deckThree[i][0] + k;
						}
						ThreeIndex += deckThree[i][1];
					}
				}
			}
			//�ҳ���3����
			int lastOne = -1, lastTwo = -1;
			int maxOne = -1;
			for (int i = 3; i < 18; ++i)
			{
				if (elseCard[i] > 0)
				{
					lastOne = i;
					maxOne = i;
				}
				if (elseCard[i] > 1)
				{
					lastTwo = i;
					maxOne = i;
				}
			}
			//Ѱ�ұ�ǩ��С������	��ѹ���˵ĸϽ���
			if (deckIndex > 0)
			{	
				Out[0] = deck[0][0];
				Out[1] = deck[0][1];
				Out[2] = 1;
				deckIndex--;
				for (int i = 0; i < deckIndex; ++i)
				{
					deck[i][0] = deck[i + 1][0];
					deck[i][1] = deck[i + 1][1];
				}
				return;
			}
			else if (deckTwoIndex > 0)
			{
				Out[0] = deckTwo[0][0];
				Out[1] = deckTwo[0][1];
				Out[2] = 2;
				deckTwoIndex--;
				for (int i = 0; i < deckTwoIndex; ++i)
				{
					deckTwo[i][0] = deckTwo[i + 1][0];
					deckTwo[i][1] = deckTwo[i + 1][1];
				}
				return;
			}
			else//û������
			{
				//int lastOne = -1, lastTwo = -1;
				int UnsafeOneNum = 0, UnsafeTwoNum = 0;
				for (int i = 0; i < OneIndex; ++i)
				{
					if (One[i] < lastOne)
					{
						UnsafeOneNum++;
					}
					else
					{
						break;
					}
				}
				for (int i = 0; i < TwoIndex; ++i)
				{
					if (Two[i] < lastTwo)
					{
						UnsafeTwoNum++;
					}
					else
					{
						break;
					}
				}
				//-----------2����-------------//
				int Rounds = GetRestRound();
				if (Rounds == 2)
				{
					if (KingBoom == 1)
					{
						Out[0] = 17;
						Out[1] = 2;
						Out[2] = 4;
						KingBoom = 0;
						return;
					}
					if (FourIndex > 0)
					{
						Out[0] = Four[0];
						Out[1] = 4;
						Out[2] = 4;
						FourIndex--;
						for (int i = 0; i < FourIndex; ++i)
						{
							Four[i] = Four[i + 1];
						}
						return;
					}
				}
				//-----------�ָ���-------------//
				if (ThreeIndex > 0)
				{
					Out[0] = Three[0];
					Out[1] = 3;
					Out[2] = 0;//three����Ϊ����
					if (UnsafeOneNum > 0)
					{
						Out[3] = One[0];
						Out[4] = 1;
						OneIndex--;
						for (int i = 0; i < OneIndex; ++i)
						{
							One[i] = One[i + 1];
						}
					}
					else if (UnsafeTwoNum > 0)
					{
						Out[3] = Two[0];
						Out[4] = 2;
						TwoIndex--;
						for (int i = 0; i < TwoIndex; ++i)
						{
							Two[i] = Two[i + 1];
						}
					}
					else
					{
						//��Ӯ���Ų�����
					}
				}
				else if (TwoIndex > UnsafeTwoNum)
				{
					Out[0] = Two[TwoIndex - 1];
					Out[1] = 2;
					Out[2] = 0;
					TwoIndex--;
				}
				else if (FourIndex > 0)//�Ĵ��������
				{
					bool IsFour = false;
						Out[0] = Four[0];
						Out[1] = 4;
						Out[2] = 4;
						IsFour = true;
						if (UnsafeOneNum > 1)
						{
							Out[3] = One[0];
							Out[4] = 1;
							Out[5] = One[1];
							OneIndex -= 2;
							for (int i = 0; i < OneIndex; ++i)
							{
								One[i] = One[i + 2];
							}
						}
						else if (UnsafeTwoNum > 1)
						{
							Out[3] = Two[0];
							Out[4] = 2;
							Out[5] = Two[1];
							TwoIndex -= 2;
							for (int i = 0; i < TwoIndex; ++i)
							{
								Two[i] = Two[i + 2];
							}
						}
						else if (UnsafeTwoNum > 0 && UnsafeOneNum > 0 && Two[0] > One[0])
						{
							Out[3] = One[0];
							Out[4] = 1;
							Out[5] = Two[0];
							TwoIndex--;
							One[0] = Two[0];
							Two[0] = 0;
							
						}
						else if (UnsafeTwoNum > 0)
						{
							Out[3] = Two[0];
							TwoIndex--;
							Out[4] = 1;
							Out[5] = Two[0];
							Two[0] = 0;
						}
						else
						{
							//��Ӯ���Ų�����
						}
					if (IsFour)
					{
						FourIndex--;
						for (int i = 0; i < FourIndex; ++i)
						{
							Four[i] = Four[i + 1];
						}
					}
					return;
				}
				else//ֻʣ��˫��
				{
					if (UnsafeTwoNum == 0 && TwoIndex > 0)
					{
						if (TwoIndex > 1)
						{
							Out[0] = Two[0];
							Out[1] = 2;
							Out[2] = 0;
							TwoIndex--;
							for (int i = 0; i < TwoIndex; i++)
							{
								Two[i] = Two[i + 1];
							}
							return;
						}
						else
						{
							if (Two[0] <= lastOne)
							{
								Out[0] = Two[0];
								Out[1] = 2;
								Out[2] = 0;
								TwoIndex--;
								Two[0] = 0;
								return;
							}
							else
							{
								Out[0] = Two[0];
								Out[1] = 1;
								Out[2] = 0;
								TwoIndex--;
								bool flag = false;
								for (int i = 0; i < OneIndex; ++i)
								{
									if (One[i] > Two[0])
									{
										for (int j = OneIndex; j > i; --j)
										{
											One[j] = One[j - 1];
										}
										One[i] = Two[0];
										Two[0] = 0;
										flag = true;
										OneIndex++;
										break;
									}
								}
								if (!flag)
								{
									One[OneIndex] = Two[0];
									Two[0] = 0;
									OneIndex++;
								}
								return;
							}
						}
					}
					else if (UnsafeOneNum == OneIndex && UnsafeTwoNum == TwoIndex && UnsafeTwoNum > 0)//ֻ�ܶ�һ�Ѷ���û���ӣ�
					{
						TwoIndex--; UnsafeTwoNum--;
						Out[0] = Two[TwoIndex];
						Out[1] = 2;
						Out[2] = 0;
						return;
					}
					else if (UnsafeOneNum == OneIndex && UnsafeTwoNum == TwoIndex && UnsafeOneNum > 0)
					{
						OneIndex--; UnsafeTwoNum--;
						Out[0] = One[OneIndex];
						Out[1] = 2;
						Out[2] = 0;
						One[OneIndex] = 0;
						return;
					}
					else if (UnsafeOneNum == 1 && One[UnsafeOneNum - 1] > maxOne)
					{
						OneIndex--;
						Out[0] = One[OneIndex];
						Out[1] = 1;
						Out[2] = 0;
						return;
					}
					else if (UnsafeOneNum > 0 && UnsafeTwoNum == 0 && OneIndex > UnsafeOneNum)
					{
						OneIndex--;
						Out[0] = One[OneIndex - 1];
						Out[1] = 1;
						Out[2] = 0;
						One[OneIndex - 1] = One[OneIndex];
						One[OneIndex] = 0;
					}
					else if (UnsafeOneNum == 0 && UnsafeTwoNum == 1)
					{
						if (OneIndex - 1 > 0) 
						{
							if (One[OneIndex - 1] > maxOne)
							{
								OneIndex--;
								Out[0] = One[OneIndex - 1];
								Out[1] = 1;
								Out[2] = 0;
							}
							else
							{
								TwoIndex--;
								UnsafeTwoNum--;
								Out[0] = Two[TwoIndex];
								Out[1] = 2;
								Out[2] = 0;
							}

						}
						else
						{
							OneIndex--;
							Out[0] = One[OneIndex];
							Out[1] = 1;
							Out[2] = 0;
						}
					}
					else if (UnsafeOneNum == 0 && UnsafeTwoNum > 1)
					{
						UnsafeTwoNum--;
						TwoIndex--;
						Out[0] = Two[TwoIndex];
						Out[1] = 2;
						Out[2] = 0;
					}
					if (TwoIndex > 0 && Out[2] == -1)
					{
						TwoIndex--;
						Out[0] = Two[TwoIndex];
						Out[1] = 2;
						Out[2] = 0;
					}
					else if (OneIndex > 0 && Out[2] == -1)
					{
						OneIndex--;
						Out[0] = One[OneIndex];
						Out[1] = 1;
						Out[2] = 0;
					}
					return;
				}
				return;
			}
		}
		//********************����***************************//
		else if ((frontN == 1 || behindN == 1))
		{
			//Ѱ�ұ�ǩ��С������	
			if (deckIndex > 0)
			{
				Out[0] = deck[0][0];
				Out[1] = deck[0][1];
				Out[2] = 1;
				deckIndex--;
				for (int i = 0; i < deckIndex; ++i)
				{
					deck[i][0] = deck[i + 1][0];
					deck[i][1] = deck[i + 1][1];
				}
				return;
			}
			else if (deckTwoIndex > 0)
			{
				Out[0] = deckTwo[0][0];
				Out[1] = deckTwo[0][1];
				Out[2] = 2;
				deckTwoIndex--;
				for (int i = 0; i < deckTwoIndex; ++i)
				{
					deckTwo[i][0] = deckTwo[i + 1][0];
					deckTwo[i][1] = deckTwo[i + 1][1];
				}
				return;
			}
			else if (deckThreeIndex > 0)
			{
				//���������뿼��
				if (OneIndex >= deckThree[0][1] && One[deckThree[0][1]-1] < 15)
				{
					Out[0] = deckThree[0][0];
					Out[1] = deckThree[0][1];
					Out[2] = 3;
					Out[3] = One[0];
					Out[4] = 1;
					for (int i = 1; i < deckThree[0][1]; ++i)
					{
						Out[i + 4] = One[i];
					}
					OneIndex -= deckThree[0][1];
					for (int i = 0; i < OneIndex; ++i)
					{
						One[i] = One[i + deckThree[0][1]];
					}
				}
				else
				{
					int temp = 0;
					for (int i = 0; i < OneIndex; ++i)
					{
						if (One[i] < 15)
						{
							temp++;
						}
					}
					if (temp == 0)
					{
						if (TwoIndex >= deckThree[0][1] && Two[deckThree[0][1] - 1] < 15)
						{
							Out[0] = deckThree[0][0];
							Out[1] = deckThree[0][1];
							Out[2] = 3;
							Out[3] = Two[0];
							Out[4] = 2;
							for (int i = 1; i < deckThree[0][1]; ++i)
							{
								Out[i + 4] = Two[i];
							}
							TwoIndex -= deckThree[0][1];
							for (int i = 0; i < TwoIndex; ++i)
							{
								Two[i] = Two[i + deckThree[0][1]];
							}
						}
						else if (deckThree[0][1] % 2 == 0 && TwoIndex >= deckThree[0][1] / 2 && Two[deckThree[0][1] / 2 - 1] < 15)
						{
							Out[0] = deckThree[0][0];
							Out[1] = deckThree[0][1];
							Out[2] = 3;
							Out[3] = Two[0];
							Out[4] = 1;
							Out[5] = Two[0];
							for (int i = 1; i < deckThree[0][1] / 2; ++i)
							{
								Out[i + 5] = Two[i];
								Out[i + 6] = Two[i];
							}
							TwoIndex -= deckThree[0][1] / 2;
							for (int i = 0; i < TwoIndex; ++i)
							{
								Two[i] = Two[i + deckThree[0][1] / 2];
							}
						}
						else if (TwoIndex > 0)
						{
							int sum = TwoIndex;
							if (Two[sum - 1] > 14)
							{
								sum--;
							}
							if (sum > 1)
							{
								Out[0] = deckThree[0][0];
								Out[1] = sum;
								Out[2] = 3;
								Out[3] = Two[0];
								Out[4] = 2;
								for (int i = 1; i < sum; i++)
								{
									Out[i + 4] = Two[i];
								}
								TwoIndex -= sum;
								for (int i = 0; i < TwoIndex; ++i)
								{
									Two[i] = Two[i + 1];
								}
								if (deckThree[0][1] - sum > 1)
								{
									deckThree[0][0] = deckThree[0][0] + sum;
									deckThree[0][1] = deckThree[0][1] - sum;
								}
								else
								{
									if (deckThree[0][1] - sum == 1)
									{
										bool fg = false;
										for (int i = 0; i < ThreeIndex; ++i)
										{
											if (Three[i] > Out[0])
											{
												fg = true;
												for (int j = ThreeIndex; j > i; j--)
												{
													Three[j] = Three[j - 1];
												}
												Three[i] = Out[0] + Out[1];
												ThreeIndex++;
												break;
											}
										}
										if (!fg)
										{
											Three[ThreeIndex] = Out[0] + Out[1];
											ThreeIndex++;
										}
									}
									for (int i = 0; i < deckThreeIndex; ++i)
									{
										deckThree[i][0] = deckThree[i + 1][0];
										deckThree[i][1] = deckThree[i + 1][1];
									}
								}
								return;
							}
							else if (sum == 1)
							{
								Out[0] = deckThree[0][0];
								Out[1] = 2;
								Out[2] = 3;
								Out[3] = Two[0];
								Out[4] = 1;
								Out[5] = Two[0];
								TwoIndex--;
								for (int i = 0; i < TwoIndex; ++i)
								{
									Two[i] = Two[i + 1];
								}
								if (deckThree[0][1] - 2 > 1)
								{
									deckThree[0][0] = deckThree[0][0] + 2;
									deckThree[0][1] = deckThree[0][1] - 2;
								}
								else
								{
									if (deckThree[0][1] - 2 == 1)
									{
										bool fg = false;
										for (int i = 0; i < ThreeIndex; ++i)
										{
											if (Three[i] > Out[0])
											{
												fg = true;
												for (int j = ThreeIndex; j > i; j--)
												{
													Three[j] = Three[j - 1];
												}
												Three[i] = Out[0] + Out[1];
												ThreeIndex++;
												break;
											}
										}
										if (!fg)
										{
											Three[ThreeIndex] = Out[0] + Out[1];
											ThreeIndex++;
										}
									}
									for (int i = 0; i < deckThreeIndex; ++i)
									{
										deckThree[i][0] = deckThree[i + 1][0];
										deckThree[i][1] = deckThree[i + 1][1];
									}
								}
								return;
							}
							else
							{
								Out[0] = deckThree[0][0];
								Out[1] = deckThree[0][1];
								Out[2] = 3;
							}
						}
						else
						{
							Out[0] = deckThree[0][0];
							Out[1] = deckThree[0][1];
							Out[2] = 3;
						}
					}
					else
					{
						int det = (deckThree[0][1] - temp + 1) / 2;
						if (TwoIndex >= det && Two[det - 1] < 14)
						{
							Out[0] = deckThree[0][0];
							Out[1] = deckThree[0][1];
							Out[2] = 3;
							Out[3] = Two[0];
							Out[4] = 1;
							Out[5] = Two[0];
							for (int i = 1; i < det; ++i)
							{
								Out[i + 5] = Two[i];
								Out[i + 6] = Two[i];
							}
							TwoIndex -= det;
							for (int i = 0; i < TwoIndex; ++i)
							{
								Two[i] = Two[i + det];
							}
							int OneTemp = deckThree[0][1] - det * 2;
							for (int i = 0; i < OneTemp; ++i)
							{
								Out[i + det * 2 + 4] = One[i];
							}
							if (OneTemp > 0)
							{
								OneIndex -= OneTemp;
								for (int i = 0; i < OneIndex; ++i)
								{
									One[i] = One[i + 1];
								}
							}
							//��ֹ777888999,3455���������777888999��355
							for (int i = 3; i < 4 + Out[1]; ++i)
							{
								if (i == 4)
								{
									continue;
								}
								if (Out[i] > One[0])
								{
									int t1 = Out[i];
									Out[i] = One[0];
									One[0] = t1;
								}
							}
						}
						else
						{
							Out[0] = deckThree[0][0];
							Out[1] = deckThree[0][1];
							Out[2] = 3;
						}
					}
				}
				deckThreeIndex--;
				for (int i = 0; i < deckThreeIndex; ++i)
				{
					deckThree[i][0] = deckThree[i + 1][0];
					deckThree[i][1] = deckThree[i + 1][1];
				}
				return;
			}
			else//û������
			{
				int Rounds = GetRestRound();
				if (Rounds == 2)
				{
					if (KingBoom == 1)
					{
						Out[0] = 17;
						Out[1] = 2;
						Out[2] = 4;
						KingBoom = 0;
						return;
					}
					if (FourIndex > 0)
					{
						if (frontN >= 4 || behindN >= 4)
						{
							int i = Four[0] + 1;
							for (; i < 16; ++i)
							{
								if (elseCard[i] == 4)
								{
									break;
								}
							}
							if (i == 16)
							{
								Out[0] = Four[0];
								Out[1] = 4;
								Out[2] = 4;
								FourIndex--;
								for (int j = 0; j < FourIndex; ++j)
								{
									Four[j] = Four[j + 1];
								}
								return;
							}
						}
						else
						{
							Out[0] = Four[0];
							Out[1] = 4;
							Out[2] = 4;
							FourIndex--;
							for (int j = 0; j < FourIndex; ++j)
							{
								Four[j] = Four[j + 1];
							}
							return;
						}
					}
				}
				//---------�ָ���-------------//
				if (ThreeIndex > 0)
				{
					if (OneIndex > 0 && One[0] < 15)
					{
						Out[3] = One[0];
						Out[4] = 1;
						OneIndex--;
						for (int i = 0; i < OneIndex; ++i)
						{
							One[i] = One[i + 1];
						}
					}
					else if (TwoIndex > 0 && Two[0] < 14)//��A ��2����
					{
						Out[3] = Two[0];
						Out[4] = 2;
						TwoIndex--;
						for (int i = 0; i < TwoIndex; ++i)
						{
							Two[i] = Two[i + 1];
						}
					}
					Out[0] = Three[0];
					Out[1] = 3;
					Out[2] = 0;
					ThreeIndex--;
					for (int i = 0; i < ThreeIndex; ++i)
					{
						Three[i] = Three[i + 1];
					}
					return;
				}
				else if (FourIndex == 0)
				{
					if (TwoIndex > 0)
					{
						Out[0] = Two[0];
						Out[1] = 2;
						Out[2] = 0;
						TwoIndex--;
						for (int i = 0; i < TwoIndex; ++i)
						{
							Two[i] = Two[i + 1];
						}
						return;
					}
					else if (OneIndex > 0)
					{
						Out[0] = One[OneIndex - 1];
						Out[1] = 1;
						Out[2] = 0;
						OneIndex--;
						return;
					}
				}
				else if (OneIndex > FourIndex * 2 + 1)
				{
					Out[0] = One[FourIndex * 2 + 1];
					Out[1] = 1;
					Out[2] = 0;
					OneIndex--;
					for (int i = FourIndex * 2 + 1; i < OneIndex; ++i)
					{
						One[i] = One[i + 1];
					}
					return;
				}
				else
				{
					Out[0] = Four[0];
					Out[1] = 4;
					Out[2] = 4;
					for (int i = 0; i < FourIndex; ++i)
					{
						Four[i] = Four[i + 1];
					}
					FourIndex--;
					if (OneIndex > 1 && One[1] < OneElseMax)
					{
						Out[3] = One[0];
						Out[4] = 1;
						Out[5] = One[1];
						OneIndex -= 2;
						for (int i = 0; i < OneIndex; ++i)
						{
							One[i] = One[i + 2];
						}
					}
					else if (TwoIndex > 1 && Two[1] < TwoElseMax)
					{
						Out[3] = Two[0];
						Out[4] = 2;
						Out[5] = Two[1];
						TwoIndex -= 2;
						for (int i = 0; i < TwoIndex; ++i)
						{
							Two[i] = Two[i + 2];
						}
					}
					else if (TwoIndex == 1 && OneIndex == 1 && One[0] < 16)
					{
						TwoIndex--;
						Out[3] = Two[0];
						Out[4] = 1;
						if (Two[0] > One[0])
						{
							Out[5] = One[0];
							One[0] = Two[0];
						}
						else
						{
							Out[5] = Two[0];
						}
					}
					else if (TwoIndex == 1)
					{
						TwoIndex--;
						Out[3] = Two[0];
						Out[4] = 1;
						Out[5] = Two[0];
					}
					return;
				}
			}
		}
		//***********************��˫**************************//
		else if ((frontN == 2 || behindN == 2))
		{
			//Ѱ�ұ�ǩ��С������	
			if (deckIndex > 0)
			{
				Out[0] = deck[0][0];
				Out[1] = deck[0][1];
				Out[2] = 1;
				deckIndex--;
				for (int i = 0; i < deckIndex; ++i)
				{
					deck[i][0] = deck[i + 1][0];
					deck[i][1] = deck[i + 1][1];
				}
				return;
			}
			else if (deckTwoIndex > 0)
			{
				Out[0] = deckTwo[0][0];
				Out[1] = deckTwo[0][1];
				Out[2] = 2;
				deckTwoIndex--;
				for (int i = 0; i < deckTwoIndex; ++i)
				{
					deckTwo[i][0] = deckTwo[i + 1][0];
					deckTwo[i][1] = deckTwo[i + 1][1];
				}
				return;
			}
			else if (deckThreeIndex > 0)
			{
				//���������뿼��
				if (OneIndex >= deckThree[0][1] && One[deckThree[0][1] - 1] < 15)
				{
					Out[0] = deckThree[0][0];
					Out[1] = deckThree[0][1];
					Out[2] = 3;
					Out[3] = One[0];
					Out[4] = 1;
					for (int i = 1; i < deckThree[0][1]; ++i)
					{
						Out[i + 4] = One[i];
					}
					OneIndex -= deckThree[0][1];
					for (int i = 0; i < OneIndex; ++i)
					{
						One[i] = One[i + deckThree[0][1]];
					}
				}
				else
				{
					int temp = 0;
					for (int i = 0; i < OneIndex; ++i)
					{
						if (One[i] < 15)
						{
							temp++;
						}
					}
					if (temp == 0 || (TwoIndex >= deckThree[0][1] && Two[deckThree[0][1] - 1] < 13))
					{
						if (TwoIndex >= deckThree[0][1] && Two[deckThree[0][1] - 1] < 15)
						{
							Out[0] = deckThree[0][0];
							Out[1] = deckThree[0][1];
							Out[2] = 3;
							Out[3] = Two[0];
							Out[4] = 2;
							for (int i = 1; i < deckThree[0][1]; ++i)
							{
								Out[i + 4] = Two[i];
							}
							TwoIndex -= deckThree[0][1];
							for (int i = 0; i < TwoIndex; ++i)
							{
								Two[i] = Two[i + deckThree[0][1]];
							}
						}
						else if (deckThree[0][1] % 2 == 0 && TwoIndex >= deckThree[0][1] / 2 && Two[deckThree[0][1] / 2 - 1] < 15)
						{
							Out[0] = deckThree[0][0];
							Out[1] = deckThree[0][1];
							Out[2] = 3;
							Out[3] = Two[0];
							Out[4] = 1;
							Out[5] = Two[0];
							for (int i = 1; i < deckThree[0][1] / 2; ++i)
							{
								Out[i + 5] = Two[i];
								Out[i + 6] = Two[i];
							}
							TwoIndex -= deckThree[0][1] / 2;
							for (int i = 0; i < TwoIndex; ++i)
							{
								Two[i] = Two[i + deckThree[0][1] / 2];
							}
						}
						else if (TwoIndex > 0)
						{
							int sum = TwoIndex;
							if (Two[sum - 1] > 14)
							{
								sum--;
							}
							if (sum > 1)
							{
								Out[0] = deckThree[0][0];
								Out[1] = sum;
								Out[2] = 3;
								Out[3] = Two[0];
								Out[4] = 2;
								for (int i = 1; i < sum; i++)
								{
									Out[i + 4] = Two[i];
								}
								TwoIndex -= sum;
								for (int i = 0; i < TwoIndex; ++i)
								{
									Two[i] = Two[i + 1];
								}
								if (deckThree[0][1] - sum > 1)
								{
									deckThree[0][0] = deckThree[0][0] + sum;
									deckThree[0][1] = deckThree[0][1] - sum;
								}
								else
								{
									if (deckThree[0][1] - sum == 1)
									{
										bool fg = false;
										for (int i = 0; i < ThreeIndex; ++i)
										{
											if (Three[i] > Out[0])
											{
												fg = true;
												for (int j = ThreeIndex; j > i; j--)
												{
													Three[j] = Three[j - 1];
												}
												Three[i] = Out[0] + Out[1];
												ThreeIndex++;
												break;
											}
										}
										if (!fg)
										{
											Three[ThreeIndex] = Out[0] + Out[1];
											ThreeIndex++;
										}
									}
									for (int i = 0; i < deckThreeIndex; ++i)
									{
										deckThree[i][0] = deckThree[i + 1][0];
										deckThree[i][1] = deckThree[i + 1][1];
									}
								}
								return;
							}
							else if (sum == 1)
							{
								Out[0] = deckThree[0][0];
								Out[1] = 2;
								Out[2] = 3;
								Out[3] = Two[0];
								Out[4] = 1;
								Out[5] = Two[0];
								TwoIndex--;
								for (int i = 0; i < TwoIndex; ++i)
								{
									Two[i] = Two[i + 1];
								}
								if (deckThree[0][1] - 2 > 1)
								{
									deckThree[0][0] = deckThree[0][0] + 2;
									deckThree[0][1] = deckThree[0][1] - 2;
								}
								else
								{
									if (deckThree[0][1] - 2 == 1)
									{
										bool fg = false;
										for (int i = 0; i < ThreeIndex; ++i)
										{
											if (Three[i] > Out[0])
											{
												fg = true;
												for (int j = ThreeIndex; j > i; j--)
												{
													Three[j] = Three[j - 1];
												}
												Three[i] = Out[0] + Out[1];
												ThreeIndex++;
												break;
											}
										}
										if (!fg)
										{
											Three[ThreeIndex] = Out[0] + Out[1];
											ThreeIndex++;
										}
									}
									for (int i = 0; i < deckThreeIndex; ++i)
									{
										deckThree[i][0] = deckThree[i + 1][0];
										deckThree[i][1] = deckThree[i + 1][1];
									}
								}
								return;
							}
							else
							{
								Out[0] = deckThree[0][0];
								Out[1] = deckThree[0][1];
								Out[2] = 3;
							}
						}
						else
						{
							Out[0] = deckThree[0][0];
							Out[1] = deckThree[0][1];
							Out[2] = 3;
						}
					}
					else
					{
						int det = (deckThree[0][1] - temp + 1) / 2;
						if (TwoIndex >= det && Two[det - 1] < 14)
						{
							Out[0] = deckThree[0][0];
							Out[1] = deckThree[0][1];
							Out[2] = 3;
							Out[3] = Two[0];
							Out[4] = 1;
							Out[5] = Two[0];
							for (int i = 1; i < det; ++i)
							{
								Out[i + 5] = Two[i];
								Out[i + 6] = Two[i];
							}
							TwoIndex -= det;
							for (int i = 0; i < TwoIndex; ++i)
							{
								Two[i] = Two[i + det];
							}
							int OneTemp = deckThree[0][1] - det * 2;
							for (int i = 0; i < OneTemp; ++i)
							{
								Out[i + det * 2 + 4] = One[i];
							}
							if (OneTemp > 0)
							{
								OneIndex -= OneTemp;
								for (int i = 0; i < OneIndex; ++i)
								{
									One[i] = One[i + 1];
								}
							}
							//��ֹ777888999,3455���������777888999��355
							for (int i = 3; i < 4 + Out[1]; ++i)
							{
								if (i == 4)
								{
									continue;
								}
								if (Out[i] > One[0])
								{
									int t1 = Out[i];
									Out[i] = One[0];
									One[0] = t1;
								}
							}
						}
						else
						{
							Out[0] = deckThree[0][0];
							Out[1] = deckThree[0][1];
							Out[2] = 3;
						}
					}
				}
				deckThreeIndex--;
				for (int i = 0; i < deckThreeIndex; ++i)
				{
					deckThree[i][0] = deckThree[i + 1][0];
					deckThree[i][1] = deckThree[i + 1][1];
				}
				return;
			}
			int Rounds = GetRestRound();
			if (Rounds == 2)
			{
				if (KingBoom == 1)
				{
					Out[0] = 17;
					Out[1] = 2;
					Out[2] = 4;
					KingBoom = 0;
					return;
				}
				if (FourIndex > 0 && (elseCard[16] == 0 || elseCard[17] == 0))
				{
					if (frontN >= 4 || behindN >= 4)
					{
						int i = Four[0] + 1;
						for (; i < 16; ++i)
						{
							if (elseCard[i] == 4)
							{
								break;
							}
						}
						if (i == 16)
						{
							Out[0] = Four[0];
							Out[1] = 4;
							Out[2] = 4;
							FourIndex--;
							for (int j = 0; j < FourIndex; ++j)
							{
								Four[j] = Four[j + 1];
							}
							return;
						}
					}
					else
					{
						Out[0] = Four[0];
						Out[1] = 4;
						Out[2] = 4;
						FourIndex--;
						for (int i = 0; i < FourIndex; ++i)
						{
							Four[i] = Four[i + 1];
						}
						return;
					}
				}
				//����˫���
				if (OneIndex > 0)
				{
					for (int i = 17; i > 2; --i)
					{
						if (i <= One[OneIndex - 1])
						{
							OneIndex--;
							Out[0] = One[OneIndex];
							Out[1] = 1;
							Out[2] = 0;
							return;
						}
					}
				}
				if (TwoIndex > 0)
				{
					for (int i = 15; i > 2; --i)
					{
						if (i <= Two[TwoIndex - 1])
						{
							TwoIndex--;
							Out[0] = Two[TwoIndex];
							Out[1] = 2;
							Out[2] = 0;
							return;
						}
					}
				}
			}
			//---------�ָ���-------------//
			if (ThreeIndex > 0)
			{
				if (TwoIndex > 0 && Two[0] < TwoElseMax)
				{
					Out[3] = Two[0];
					Out[4] = 2;
					TwoIndex--;
					for (int i = 0; i < TwoIndex; ++i)
					{
						Two[i] = Two[i + 1];
					}
				}
				else if (OneIndex > 0 && One[0] < OneElseMax)//2����
				{
					Out[3] = One[0];
					Out[4] = 1;
					OneIndex--;
					for (int i = 0; i < OneIndex; ++i)
					{
						One[i] = One[i + 1];
					}
				}
				Out[0] = Three[0];
				Out[1] = 3;
				Out[2] = 0;
				ThreeIndex--;
				for (int i = 0; i < ThreeIndex; ++i)
				{
					Three[i] = Three[i + 1];
				}
				return;
			}
			else//û������
			{
				//��δ���ǲ���
				if (FourIndex == 0)
				{
					if (OneIndex > 1 && ((One[OneIndex - 1] > OneElseMax) || (TwoIndex > 0 && Two[0] > OneElseMax)))
					{
						Out[0] = One[OneIndex - 2];
						Out[1] = 1;
						Out[2] = 0;
						OneIndex--;
						return;
					}
					if (TwoIndex > 0)
					{
						Out[0] = Two[TwoIndex - 1];
						Out[1] = 2;
						Out[2] = 0;
						TwoIndex--;
						return;
					}
					else if (OneIndex > 0)
					{
						Out[0] = One[OneIndex - 1];
						Out[1] = 1;
						Out[2] = 0;
						return;
					}
				}
				else if (TwoIndex > FourIndex * 2 + 1)
				{
					// 7���� 2ը
					Out[0] = Two[FourIndex * 2 + 1];
					Out[1] = 2;
					Out[2] = 0;
					TwoIndex--;
					for (int i = FourIndex * 2 + 1; i < TwoIndex; ++i)
					{
						Two[i] = Two[i + 1];
					}
				}
				else
				{
					Out[0] = Four[0];
					Out[1] = 4;
					Out[2] = 4;
					for (int i = 0; i < FourIndex; ++i)
					{
						Four[i] = Four[i + 1];
					}
					FourIndex--;
					if (OneIndex > 1 && One[1] < OneElseMax)
					{
						Out[3] = One[0];
						Out[4] = 1;
						Out[5] = One[1];
						OneIndex -= 2;
						for (int i = 0; i < OneIndex; ++i)
						{
							One[i] = One[i + 2];
						}
					}
					else if (TwoIndex > 1 && Two[1] < TwoElseMax)
					{
						Out[3] = Two[0];
						Out[4] = 2;
						Out[5] = Two[1];
						TwoIndex -= 2;
						for (int i = 0; i < TwoIndex; ++i)
						{
							Two[i] = Two[i + 2];
						}
					}
					else if (TwoIndex == 1 && OneIndex == 1 && One[0] < OneElseMax)
					{
						TwoIndex--;
						Out[3] = Two[0];
						Out[4] = 1;
						if (Two[0] > One[0])
						{
							Out[5] = One[0];
							One[0] = Two[0];
						}
						else
						{
							Out[5] = Two[0];
						}
					}
					else if (TwoIndex == 1 && Two[0] < TwoElseMax)
					{
						TwoIndex--;
						Out[3] = Two[0];
						Out[4] = 1;
						Out[5] = Two[0];
					}
					else if (OneIndex > 0)
					{
						Out[0] = One[0];
						Out[1] = 1;
						Out[2] = 0;
					}
					else if (TwoIndex > 0)
					{
						Out[0] = Two[0];
						Out[1] = 2;
						Out[2] = 0;
					}
					return;
				}
				return;
			}
		}
		//**********************��������****************************//
		else
		{
			int Rounds = GetRestRound();
			if (deckIndex > 0 && (deck[0][0] + deck[0][1] - 1 < 11 || deck[0][1] > 6 || frontN < 9 || behindN < 9 || Rounds < 4 || (One[0] >= deck[0][0] && Two[0] >= deck[0][0])))//˳��
			{
				Out[0] = deck[0][0];
				Out[1] = deck[0][1];
				Out[2] = 1;
				deckIndex--;
				for (int i = 0; i < deckIndex; ++i)
				{
					deck[i][0] = deck[i + 1][0];
					deck[i][1] = deck[i + 1][1];
				}
				return;
			}
			else if (deckThreeIndex > 0 && deckThree[0][0] + deckThree[0][1] - 1 <= OneElseMax && (deckThree[0][0] + deckThree[0][1] - 1 < 11 || frontN < 6 || behindN < 6 || OneIndex - deckThree[0][1] < 3 || Rounds < 5 || (One[0] >= deckThree[0][0] && Two[0] >= deckThree[0][0])))
			{
				//���������뿼��
				if (ThreeIndex > 0 && Three[0]<deckThree[0][0])
				{
					Out[0] = Three[0];
					Out[1] = 3;
					Out[2] = 0;
					for (int i = 0; i < ThreeIndex; i++)
					{
						Three[i] = Three[i + 1];
					}
					ThreeIndex--;
					if (OneIndex > 0 && TwoIndex > 0)//ʲôС���ĸ�
					{
						if (One[0] < Two[0])
						{
							Out[3] = One[0];
							Out[4] = 1;
							OneIndex--;
							for (int i = 0; i < OneIndex; ++i)
							{
								One[i] = One[i + 1];
							}
						}
						else
						{
							Out[3] = Two[0];
							Out[4] = 2;
							TwoIndex--;
							for (int i = 0; i < TwoIndex; ++i)
							{
								Two[i] = Two[i + 1];
							}
						}
					}
					else if (OneIndex > 0)//����
					{
						Out[3] = One[0];
						Out[4] = 1;
						OneIndex--;
						for (int i = 0; i < OneIndex; ++i)
						{
							One[i] = One[i + 1];
						}
					}
					else if (TwoIndex > 0)//����
					{
						Out[3] = Two[0];
						Out[4] = 2;
						TwoIndex--;
						for (int i = 0; i < TwoIndex; ++i)
						{
							Two[i] = Two[i + 1];
						}
					}
					return;
				}
				if (OneIndex > deckThree[0][1] && TwoIndex > deckThree[0][1] && One[deckThree[0][1] - 1] < 13 && Two[deckThree[0][1] - 1] < 13)
				{
					int a = 0;
					int b = 0;
					for (int i = 0; i < deckThree[0][1]; i++)
					{
						a += One[i];
						b += Two[i];
					}
					if (a <= b)
					{
						Out[0] = deckThree[0][0];
						Out[1] = deckThree[0][1];
						Out[2] = 3;
						Out[3] = One[0];
						Out[4] = 1;
						for (int i = 1; i < deckThree[0][1]; i++)
						{
							Out[4 + i] = One[i];
						}
						OneIndex -= deckThree[0][1];
						for (int i = 0; i < OneIndex; i++)
						{
							One[i] = One[i + deckThree[0][1]];
						}
					}
					else
					{
						Out[0] = deckThree[0][0];
						Out[1] = deckThree[0][1];
						Out[2] = 3;
						Out[3] = Two[0];
						Out[4] = 2;
						for (int i = 1; i < deckThree[0][1]; i++)
						{
							Out[4 + i] = Two[i];
						}
						TwoIndex -= deckThree[0][1];
						for (int i = 0; i < TwoIndex; i++)
						{
							Two[i] = Two[i + deckThree[0][1]];
						}
					}
				}
				else if (OneIndex >= deckThree[0][1] && One[deckThree[0][1] - 1] < 15)
				{

					Out[0] = deckThree[0][0];
					Out[1] = deckThree[0][1];
					Out[2] = 3;
					Out[3] = One[0];
					Out[4] = 1;
					for (int i = 1; i < deckThree[0][1]; ++i)
					{
						Out[i + 4] = One[i];
					}
					OneIndex -= deckThree[0][1];
					for (int i = 0; i < OneIndex; ++i)
					{
						One[i] = One[i + deckThree[0][1]];
					}
				}
				else
				{
					int temp = 0;
					for (int i = 0; i < OneIndex; ++i)
					{
						if (One[i] < 15)
						{
							temp++;
						}
					}
					if (temp == 0 || (TwoIndex >= deckThree[0][1] && Two[deckThree[0][1] - 1] < 13))
					{
						if (TwoIndex >= deckThree[0][1] && Two[deckThree[0][1] - 1] < 15)
						{
							Out[0] = deckThree[0][0];
							Out[1] = deckThree[0][1];
							Out[2] = 3;
							Out[3] = Two[0];
							Out[4] = 2;
							for (int i = 1; i < deckThree[0][1]; ++i)
							{
								Out[i + 4] = Two[i];
							}
							TwoIndex -= deckThree[0][1];
							for (int i = 0; i < TwoIndex; ++i)
							{
								Two[i] = Two[i + deckThree[0][1]];
							}
						}
						else if (deckThree[0][1] % 2 == 0 && TwoIndex >= deckThree[0][1] / 2 && Two[deckThree[0][1] / 2 - 1] < 15)
						{
							Out[0] = deckThree[0][0];
							Out[1] = deckThree[0][1];
							Out[2] = 3;
							Out[3] = Two[0];
							Out[4] = 1;
							Out[5] = Two[0];
							for (int i = 1; i < deckThree[0][1] / 2; ++i)
							{
								Out[i + 5] = Two[i];
								Out[i + 6] = Two[i];
							}
							TwoIndex -= deckThree[0][1] / 2;
							for (int i = 0; i < TwoIndex; ++i)
							{
								Two[i] = Two[i + deckThree[0][1] / 2];
							}
						}
						else if (TwoIndex > 0)
						{
							int sum = TwoIndex;
							if (Two[sum - 1] > 14)
							{
								sum--;
							}
							if (sum > 1)
							{
								Out[0] = deckThree[0][0];
								Out[1] = sum;
								Out[2] = 3;
								Out[3] = Two[0];
								Out[4] = 2;
								for (int i = 1; i < sum; i++)
								{
									Out[i + 4] = Two[i];
								}
								TwoIndex -= sum;
								for (int i = 0; i < TwoIndex; ++i)
								{
									Two[i] = Two[i + 1];
								}
								if (deckThree[0][1] - sum > 1)
								{
									deckThree[0][0] = deckThree[0][0] + sum;
									deckThree[0][1] = deckThree[0][1] - sum;
								}
								else
								{
									if (deckThree[0][1] - sum == 1)
									{
										bool fg = false;
										for (int i = 0; i < ThreeIndex; ++i)
										{
											if (Three[i] > Out[0])
											{
												fg = true;
												for (int j = ThreeIndex; j > i; j--)
												{
													Three[j] = Three[j - 1];
												}
												Three[i] = Out[0] + Out[1];
												ThreeIndex++;
												break;
											}
										}
										if (!fg)
										{
											Three[ThreeIndex] = Out[0] + Out[1];
											ThreeIndex++;
										}
									}
									for (int i = 0; i < deckThreeIndex; ++i)
									{
										deckThree[i][0] = deckThree[i + 1][0];
										deckThree[i][1] = deckThree[i + 1][1];
									}
								}
								return;
							}
							else if (sum == 1)
							{
								Out[0] = deckThree[0][0];
								Out[1] = 2;
								Out[2] = 3;
								Out[3] = Two[0];
								Out[4] = 1;
								Out[5] = Two[0];
								TwoIndex--;
								for (int i = 0; i < TwoIndex; ++i)
								{
									Two[i] = Two[i + 1];
								}
								if (deckThree[0][1] - 2 > 1)
								{
									deckThree[0][0] = deckThree[0][0] + 2;
									deckThree[0][1] = deckThree[0][1] - 2;
								}
								else
								{
									if (deckThree[0][1] - 2 == 1)
									{
										bool fg = false;
										for (int i = 0; i < ThreeIndex; ++i)
										{
											if (Three[i] > Out[0])
											{
												fg = true;
												for (int j = ThreeIndex; j > i; j--)
												{
													Three[j] = Three[j - 1];
												}
												Three[i] = Out[0] + Out[1];
												ThreeIndex++;
												break;
											}
										}
										if (!fg)
										{
											Three[ThreeIndex] = Out[0] + Out[1];
											ThreeIndex++;
										}
									}
									for (int i = 0; i < deckThreeIndex; ++i)
									{
										deckThree[i][0] = deckThree[i + 1][0];
										deckThree[i][1] = deckThree[i + 1][1];
									}
								}
								return;
							}
							else
							{
								Out[0] = deckThree[0][0];
								Out[1] = deckThree[0][1];
								Out[2] = 3;
							}
						}
						else
						{
							Out[0] = deckThree[0][0];
							Out[1] = deckThree[0][1];
							Out[2] = 3;
						}
					}
					else
					{
						int det = (deckThree[0][1] - temp + 1) / 2;
						if (TwoIndex >= det && Two[det - 1] < 14)
						{
							Out[0] = deckThree[0][0];
							Out[1] = deckThree[0][1];
							Out[2] = 3;
							Out[3] = Two[0];
							Out[4] = 1;
							Out[5] = Two[0];
							for (int i = 1; i < det; ++i)
							{
								Out[i + 5] = Two[i];
								Out[i + 6] = Two[i];
							}
							TwoIndex -= det;
							for (int i = 0; i < TwoIndex; ++i)
							{
								Two[i] = Two[i + det];
							}
							int OneTemp = deckThree[0][1] - det * 2;
							for (int i = 0; i < OneTemp; ++i)
							{
								Out[i + det * 2 + 4] = One[i];
							}
							if (OneTemp > 0)
							{
								OneIndex -= OneTemp;
								for (int i = 0; i < OneIndex; ++i)
								{
									One[i] = One[i + 1];
								}
							}
							//��ֹ777888999,3455���������777888999��355
							for (int i = 3; i < 4 + Out[1]; ++i)
							{
								if (i == 4)
								{
									continue;
								}
								if (Out[i] > One[0])
								{
									int t1 = Out[i];
									Out[i] = One[0];
									One[0] = t1;
								}
							}
						}
						else
						{
							Out[0] = deckThree[0][0];
							Out[1] = deckThree[0][1];
							Out[2] = 3;
						}
					}
				}
				deckThreeIndex--;
				for (int i = 0; i < deckThreeIndex; ++i)
				{
					deckThree[i][0] = deckThree[i + 1][0];
					deckThree[i][1] = deckThree[i + 1][1];
				}
				return;
			}
			else if (ThreeIndex > 0 && Three[0]!=15 && Three[0]!=14 && (Three[0] < 11 || frontN < 4 || behindN < 4 || (OneIndex < 2 && TwoIndex < 2)))//�ж�����һ���Ƕ����ǲ���
			{
				Out[0] = Three[0];
				Out[1] = 3;
				Out[2] = 0;
				for (int i = 0; i < ThreeIndex; i++)
				{
					Three[i] = Three[i + 1];
				}
				ThreeIndex--;
				if (OneIndex > 0 && TwoIndex > 0)//ʲôС���ĸ�
				{
					if (One[0] < Two[0])
					{
						Out[3] = One[0];
						Out[4] = 1;
						OneIndex--;
						for (int i = 0; i < OneIndex; ++i)
						{
							One[i] = One[i + 1];
						}
					}
					else
					{
						Out[3] = Two[0];
						Out[4] = 2;
						TwoIndex--;
						for (int i = 0; i < TwoIndex; ++i)
						{
							Two[i] = Two[i + 1];
						}
					}
				}
				else if (OneIndex > 0)//����
				{
					Out[3] = One[0];
					Out[4] = 1;
					OneIndex--;
					for (int i = 0; i < OneIndex; ++i)
					{
						One[i] = One[i + 1];
					}
				}
				else if (TwoIndex > 0)//����
				{
					Out[3] = Two[0];
					Out[4] = 2;
					TwoIndex--;
					for (int i = 0; i < TwoIndex; ++i)
					{
						Two[i] = Two[i + 1];
					}
				}
				return;
			}
			else if (deckTwoIndex > 0 && (TwoIndex == 0 || deckTwo[0][0] <= Two[0]) && (deckTwo[0][0] + deckTwo[0][1] - 1 < 11 || frontN < 9 || behindN < 9 || Rounds < 5))//����
			{
				if (TwoIndex > 1&&Two[0]<deckTwo[0][0])
				{
					Out[0] = Two[0];
					Out[1] = 2;
					Out[2] = 0;
					return;
				}
				Out[0] = deckTwo[0][0];
				Out[1] = deckTwo[0][1];
				Out[2] = 2;
				deckTwoIndex--;
				for (int i = 0; i < deckTwoIndex; ++i)
				{
					deckTwo[i][0] = deckTwo[i + 1][0];
					deckTwo[i][1] = deckTwo[i + 1][1];
				}
				return;
			}
			//---------�ָ���-------------//
			if (ThreeIndex > 0 && OneIndex + TwoIndex < 4)
			{
				Out[0] = Three[0];
				Out[1] = 3;
				Out[2] = 0;
				for (int i = 0; i < ThreeIndex; i++)
				{
					Three[i] = Three[i + 1];
				}
				ThreeIndex--;
				if (OneIndex > 0 && TwoIndex > 0)//ʲôС���ĸ�
				{
					if (One[0] < Two[0])
					{
						Out[3] = One[0];
						Out[4] = 1;
						OneIndex--;
						for (int i = 0; i < OneIndex; ++i)
						{
							One[i] = One[i + 1];
						}
					}
					else
					{
						Out[3] = Two[0];
						Out[4] = 2;
						TwoIndex--;
						for (int i = 0; i < TwoIndex; ++i)
						{
							Two[i] = Two[i + 1];
						}
					}
				}
				else if (OneIndex > 0)//����
				{
					Out[3] = One[0];
					Out[4] = 1;
					OneIndex--;
					for (int i = 0; i < OneIndex; ++i)
					{
						One[i] = One[i + 1];
					}
				}
				else if (TwoIndex > 0)//����
				{
					Out[3] = Two[0];
					Out[4] = 2;
					TwoIndex--;
					for (int i = 0; i < TwoIndex; ++i)
					{
						Two[i] = Two[i + 1];
					}
				}
				return;
			}
			else if(OneIndex > 0 && TwoIndex > 0)//ʲôС���ĸ�
			{
				if(One[0] < Two[0])
				{
					Out[0] = One[0];
					Out[1] = 1;
					Out[2] = 0;
					OneIndex--;
					for (int i = 0; i < OneIndex; ++i)
					{
						One[i] = One[i + 1];
					}
					return;
				}
				else
				{
					Out[0] = Two[0];
					Out[1] = 2;
					Out[2] = 0;
					TwoIndex--;
					for (int i = 0; i < TwoIndex; ++i)
					{
						Two[i] = Two[i + 1];
					}
					return ;
				}
			}
			else if (OneIndex > 0)//����
			{
				Out[0] = One[0];
				Out[1] = 1;
				Out[2] = 0;
				OneIndex--;
				for (int i = 0; i < OneIndex; ++i)
				{
					One[i] = One[i + 1];
				}
			}
			else if (TwoIndex > 0)//����
			{
				Out[0] = Two[0];
				Out[1] = 2;
				Out[2] = 0;
				TwoIndex--;
				for (int i = 0; i < TwoIndex; ++i)
				{
					Two[i] = Two[i + 1];
				}
			}
			else if (FourIndex > 0)//four
			{
				Out[0] = Four[0];
				Out[1] = 4;
				Out[2] = 4;
				FourIndex--;
				for (int i = 0; i < FourIndex; ++i)
				{
					Four[i] = Four[i + 1];
				}
			}
			else if (KingBoom == 1)
			{
				Out[0] = 17;
				Out[1] = 2;
				Out[2] = 4;
				KingBoom = 0;
			}
			else//û����
			{
					
			}
			return;
		}
	}
	//****************ũ��*********************//
	else
	{
		// behindN == 1 && DZIndex == 1  ��ҵ�������
		//if (behindN == 1 && DZIndex == -1)//����ũ�񱨵����е���������
		//----------------------�¼�ũ�񱨵�||�ϼ�ũ���������¼ҵ�������һ��
		if ((behindN == 1 && DZIndex == -1 && frontN > 1) || (frontN == 1 && DZIndex == 2 && behindN > 1))
		{
			if (GetRestRound() == 1)
			{
				if (deckIndex == 1)
				{
					Out[0] = deck[0][0];
					Out[1] = deck[0][1];
					Out[2] = 1;
					deckIndex--;
					return;
				}
				else if (deckTwoIndex == 1)
				{
					Out[0] = deckTwo[0][0];
					Out[1] = deckTwo[0][1];
					Out[2] = 2;
					deckTwoIndex--;
					return;
				}
				else if (deckThreeIndex == 1)
				{
					Out[0] = deckThree[0][0];
					Out[1] = deckThree[0][1];
					Out[2] = 3;
					deckThreeIndex--;
				}
				else if (ThreeIndex == 1)
				{
					Out[0] = Three[0];
					Out[1] = 3;
					Out[2] = 0;
					ThreeIndex--;
					if (OneIndex > 0)
					{
						Out[3] = One[0];
						Out[4] = 1;
						OneIndex--;
					}
					else if (TwoIndex > 0)
					{
						Out[3] = Two[0];
						Out[4] = 2;
						TwoIndex--;
					}
					else
					{
						//����
					}
					return;
				}
				else if (OneIndex == 1)
				{
					Out[0] = One[0];
					Out[1] = 1;
					Out[2] = 0;
					OneIndex--;
				}
				else if (TwoIndex == 1)
				{
					Out[0] = Two[0];
					Out[1] = 2;
					Out[2] = 0;
					TwoIndex--;
				}
				else if (KingBoom == 1)
				{
					Out[0] = 17;
					Out[1] = 2;
					Out[2] = 4;
					KingBoom = 0;
				}
				else if (FourIndex == 1)
				{
					Out[0] = Four[0];
					Out[1] = 4;
					Out[2] = 4;
					FourIndex--;
				}
				else
				{
					//û���ˣ�
				}
				return;
			}
			else
			{
				for (int i = 3; i < 18; ++i)
				{
					if (myCard[i] < 4 && myCard[i] > 0)
					{
						Out[0] = i;
						Out[1] = 1;
						Out[2] = 0;
						return;
					}
				}
			}
			return;
		}
		//----------------------��������
		else if ((DZIndex == 2 && behindN == 1) || (DZIndex == -1 && frontN == 1))
		{
			//Ѱ�ұ�ǩ��С������	
			if (deckIndex > 0)
			{
				Out[0] = deck[0][0];
				Out[1] = deck[0][1];
				Out[2] = 1;
				deckIndex--;
				for (int i = 0; i < deckIndex; ++i)
				{
					deck[i][0] = deck[i + 1][0];
					deck[i][1] = deck[i + 1][1];
				}
				return;
			}
			else if (deckTwoIndex > 0)
			{
				Out[0] = deckTwo[0][0];
				Out[1] = deckTwo[0][1];
				Out[2] = 2;
				deckTwoIndex--;
				for (int i = 0; i < deckTwoIndex; ++i)
				{
					deckTwo[i][0] = deckTwo[i + 1][0];
					deckTwo[i][1] = deckTwo[i + 1][1];
				}
				return;
			}
			else if (deckThreeIndex > 0)
			{
				//���������뿼��
				if (OneIndex >= deckThree[0][1])
				{
					Out[0] = deckThree[0][0];
					Out[1] = deckThree[0][1];
					Out[2] = 3;
					Out[3] = One[0];
					Out[4] = 1;
					for (int i = 1; i < deckThree[0][1]; ++i)
					{
						Out[i + 4] = One[i];
					}
					OneIndex -= deckThree[0][1];
					for (int i = 0; i < OneIndex; ++i)
					{
						One[i] = One[i + deckThree[0][1]];
					}
				}
				else
				{
					int temp = 0;
					for (int i = 0; i < OneIndex; ++i)
					{
						if (One[i] < 15)
						{
							temp++;
						}
					}
					if (temp == 0)
					{
						if (TwoIndex >= deckThree[0][1] && Two[deckThree[0][1] - 1] < 14)
						{
							Out[0] = deckThree[0][0];
							Out[1] = deckThree[0][1];
							Out[2] = 3;
							Out[3] = Two[0];
							Out[4] = 2;
							for (int i = 1; i < deckThree[0][1]; ++i)
							{
								Out[i + 4] = Two[i];
							}
							TwoIndex -= deckThree[0][1];
							for (int i = 0; i < TwoIndex; ++i)
							{
								Two[i] = Two[i + deckThree[0][1]];
							}
						}
						else if (deckThree[0][1] % 2 == 0 && TwoIndex >= deckThree[0][1] / 2 && Two[deckThree[0][1] / 2 - 1] < 14)
						{
							Out[0] = deckThree[0][0];
							Out[1] = deckThree[0][1];
							Out[2] = 3;
							Out[3] = Two[0];
							Out[4] = 1;
							Out[5] = Two[0];
							for (int i = 1; i < deckThree[0][1] / 2; ++i)
							{
								Out[i + 5] = Two[i];
								Out[i + 6] = Two[i];
							}
							TwoIndex -= deckThree[0][1] / 2;
							for (int i = 0; i < TwoIndex; ++i)
							{
								Two[i] = Two[i + deckThree[0][1] / 2];
							}
						}
						else
						{
							Out[0] = deckThree[0][0];
							Out[1] = deckThree[0][1];
							Out[2] = 3;
						}
					}
					else
					{
						int det = (deckThree[0][1] - temp + 1) / 2;
						if (TwoIndex >= det && Two[det - 1] < 14)
						{
							Out[0] = deckThree[0][0];
							Out[1] = deckThree[0][1];
							Out[2] = 3;
							Out[3] = Two[0];
							Out[4] = 1;
							Out[5] = Two[0];
							for (int i = 1; i < det; ++i)
							{
								Out[i + 5] = Two[i];
								Out[i + 6] = Two[i];
							}
							TwoIndex -= det;
							for (int i = 0; i < TwoIndex; ++i)
							{
								Two[i] = Two[i + det];
							}
							int OneTemp = deckThree[0][1] - det * 2;
							for (int i = 0; i < OneTemp; ++i)
							{
								Out[i + det * 2 + 4] = One[i];
							}
							if (OneTemp > 0)
							{
								OneIndex -= OneTemp;
								for (int i = 0; i < OneIndex; ++i)
								{
									One[i] = One[i + 1];
								}
							}
							//��ֹ777888999,3455���������777888999��355
							for (int i = 3; i < 4 + Out[1]; ++i)
							{
								if (i == 4)
								{
									continue;
								}
								if (Out[i] > One[0])
								{
									int t1 = Out[i];
									Out[i] = One[0];
									One[0] = t1;
								}
							}
						}
						else
						{
							Out[0] = deckThree[0][0];
							Out[1] = deckThree[0][1];
							Out[2] = 3;
						}
					}
				}
				deckThreeIndex--;
				for (int i = 0; i < deckThreeIndex; ++i)
				{
					deckThree[i][0] = deckThree[i + 1][0];
					deckThree[i][1] = deckThree[i + 1][1];
				}
				return;
			}
			//������
			int Rounds = GetRestRound();
			if (Rounds == 2)
			{
				if (KingBoom == 1)
				{
					Out[0] = 17;
					Out[1] = 2;
					Out[2] = 4;
					KingBoom = 0;
					return;
				}
				if (FourIndex > 0)
				{
					Out[0] = Four[0];
					Out[1] = 4;
					Out[2] = 4;
					FourIndex--;
					return;
				}
			}
			//---------�ָ���-------------//
			if (ThreeIndex > 0)
			{
				if (OneIndex > 0 && One[0] < 16)
				{	
					Out[3] = One[0];
					Out[4] = 1;
					OneIndex--;
					for (int i = 0; i < OneIndex; ++i)
					{
						One[i] = One[i + 1];
					}
				}
				else if (TwoIndex > 0 && Two[0] < 14)//��A ��2����
				{
					Out[3] = Two[0];
					Out[4] = 2;
					TwoIndex--;
					for (int i = 0; i < TwoIndex; ++i)
					{
						Two[i] = Two[i + 1];
					}
				}
				Out[0] = Three[0];
				Out[1] = 3;
				Out[2] = 0;
				ThreeIndex--;
				for (int i = 0; i < ThreeIndex; ++i)
				{
					Three[i] = Three[i + 1];
				}
				return;
			}
			else//û������
			{
				if (TwoIndex > 0)
				{
					Out[0] = Two[0];
					Out[1] = 2;
					Out[2] = 0;
					TwoIndex--;
					for (int i = 0; i < TwoIndex; ++i)
					{
						Two[i] = Two[i + 1];
					}
				}
				else if (FourIndex == 0 && OneIndex > 0)
				{
					Out[0] = One[OneIndex - 1];
					Out[1] = 1;
					Out[2] = 0;
					OneIndex--;
				}
				else if (OneIndex > FourIndex * 2 + 1)
				{
					Out[0] = One[FourIndex * 2 + 1];
					Out[1] = 1;
					Out[2] = 0;
					OneIndex--;
					for (int i = FourIndex * 2 + 1; i < OneIndex; ++i)
					{
						One[i] = One[i + 1];
					}
				}
				else
				{
					Out[0] = Four[0];
					Out[1] = 4;
					Out[2] = 4;
					if (OneIndex > 1)
					{
						Out[3] = One[0];
						Out[4] = 1;
						Out[5] = One[1];
						OneIndex -= 2;
						for (int i = 0; i < OneIndex; ++i)
						{
							One[i] = One[i + 2];
						}
					}
				}
				return;
			}
		}
		//----------------------������˫
		else if ((DZIndex == 2 && behindN == 2) || (DZIndex == -1 && frontN == 2))
		{
			//Ѱ�ұ�ǩ��С������	
			if (deckIndex > 0)
			{
				Out[0] = deck[0][0];
				Out[1] = deck[0][1];
				Out[2] = 1;
				deckIndex--;
				for (int i = 0; i < deckIndex; ++i)
				{
					deck[i][0] = deck[i + 1][0];
					deck[i][1] = deck[i + 1][1];
				}
				return;
			}
			else if (deckTwoIndex > 0)
			{
				Out[0] = deckTwo[0][0];
				Out[1] = deckTwo[0][1];
				Out[2] = 2;
				deckTwoIndex--;
				for (int i = 0; i < deckTwoIndex; ++i)
				{
					deckTwo[i][0] = deckTwo[i + 1][0];
					deckTwo[i][1] = deckTwo[i + 1][1];
				}
				return;
			}
			else if (deckThreeIndex > 0)
			{
				//���������뿼��
				if (OneIndex >= deckThree[0][1] && One[deckThree[0][1] - 1] <= OneElseMax)
				{
					Out[0] = deckThree[0][0];
					Out[1] = deckThree[0][1];
					Out[2] = 3;
					Out[3] = One[0];
					Out[4] = 1;
					for (int i = 1; i < deckThree[0][1]; ++i)
					{
						Out[i + 4] = One[i];
					}
					OneIndex -= deckThree[0][1];
					for (int i = 0; i < OneIndex; ++i)
					{
						One[i] = One[i + deckThree[0][1]];
					}
				}
				else
				{
					int temp = 0;
					for (int i = 0; i < OneIndex; ++i)
					{
						if (One[i] < 15)
						{
							temp++;
						}
					}
					if (temp == 0 || (TwoIndex >= deckThree[0][1] && Two[deckThree[0][1] - 1] < 13))
					{
						if (TwoIndex >= deckThree[0][1] && Two[deckThree[0][1] - 1] <= OneElseMax)
						{
							Out[0] = deckThree[0][0];
							Out[1] = deckThree[0][1];
							Out[2] = 3;
							Out[3] = Two[0];
							Out[4] = 2;
							for (int i = 1; i < deckThree[0][1]; ++i)
							{
								Out[i + 4] = Two[i];
							}
							TwoIndex -= deckThree[0][1];
							for (int i = 0; i < TwoIndex; ++i)
							{
								Two[i] = Two[i + deckThree[0][1]];
							}
						}
						else if (deckThree[0][1] % 2 == 0 && TwoIndex >= deckThree[0][1] / 2 && Two[deckThree[0][1] / 2 - 1] < 14)
						{
							Out[0] = deckThree[0][0];
							Out[1] = deckThree[0][1];
							Out[2] = 3;
							Out[3] = Two[0];
							Out[4] = 1;
							Out[5] = Two[0];
							for (int i = 1; i < deckThree[0][1] / 2; ++i)
							{
								Out[i + 5] = Two[i];
								Out[i + 6] = Two[i];
							}
							TwoIndex -= deckThree[0][1] / 2;
							for (int i = 0; i < TwoIndex; ++i)
							{
								Two[i] = Two[i + deckThree[0][1] / 2];
							}
						}
						else
						{
							Out[0] = deckThree[0][0];
							Out[1] = deckThree[0][1];
							Out[2] = 3;
						}
					}
					else
					{
						int det = (deckThree[0][1] - temp + 1) / 2;
						if (TwoIndex >= det && Two[det - 1] < 14)
						{
							Out[0] = deckThree[0][0];
							Out[1] = deckThree[0][1];
							Out[2] = 3;
							Out[3] = Two[0];
							Out[4] = 1;
							Out[5] = Two[0];
							for (int i = 1; i < det; ++i)
							{
								Out[i + 5] = Two[i];
								Out[i + 6] = Two[i];
							}
							TwoIndex -= det;
							for (int i = 0; i < TwoIndex; ++i)
							{
								Two[i] = Two[i + det];
							}
							int OneTemp = deckThree[0][1] - det * 2;
							for (int i = 0; i < OneTemp; ++i)
							{
								Out[i + det * 2 + 4] = One[i];
							}
							if (OneTemp > 0)
							{
								OneIndex -= OneTemp;
								for (int i = 0; i < OneIndex; ++i)
								{
									One[i] = One[i + 1];
								}
							}
							//��ֹ777888999,3455���������777888999��355
							for (int i = 3; i < 4 + Out[1]; ++i)
							{
								if (i == 4)
								{
									continue;
								}
								if (Out[i] > One[0])
								{
									int t1 = Out[i];
									Out[i] = One[0];
									One[0] = t1;
								}
							}
						}
						else
						{
							Out[0] = deckThree[0][0];
							Out[1] = deckThree[0][1];
							Out[2] = 3;
						}
					}
				}
				deckThreeIndex--;
				for (int i = 0; i < deckThreeIndex; ++i)
				{
					deckThree[i][0] = deckThree[i + 1][0];
					deckThree[i][1] = deckThree[i + 1][1];
				}
				return;
			}
			//������
			int Rounds = GetRestRound();
			if (Rounds == 2)
			{
				if (KingBoom == 1)
				{
					Out[0] = 17;
					Out[1] = 2;
					Out[2] = 4;
					KingBoom = 0;
					return;
				}
				if (FourIndex > 0)
				{
					Out[0] = Four[0];
					Out[1] = 4;
					Out[2] = 4;
					FourIndex--;
					return;
				}
			}
			//---------�ָ���-------------//
			if (ThreeIndex > 0)
			{
				if (TwoIndex > 0 && Two[0] < TwoElseMax)
				{
					Out[3] = Two[0];
					Out[4] = 2;
					TwoIndex--;
					for (int i = 0; i < TwoIndex; ++i)
					{
						Two[i] = Two[i + 1];
					}
				}
				else if (OneIndex > 0 && One[0] <= OneElseMax)
				{
					Out[3] = One[0];
					Out[4] = 1;
					OneIndex--;
					for (int i = 0; i < OneIndex; ++i)
					{
						One[i] = One[i + 1];
					}
				}
				Out[0] = Three[0];
				Out[1] = 3;
				Out[2] = 0;
				ThreeIndex--;
				for (int i = 0; i < ThreeIndex; ++i)
				{
					Three[i] = Three[i + 1];
				}
				return;
			}
			else//û������
			{	
				int maxONE = 0;int tempN=0;
				for(int i = 0;i < OneIndex;++i)
				{
					if (One[i] >= OneElseMax)
					{
						tempN++;
					}
				}
				if (FourIndex == 0)
				{
					if (OneIndex > 1 && ((One[OneIndex - 1] > OneElseMax) || (TwoIndex > 0 && Two[0] > OneElseMax)))
					{
						Out[0] = One[OneIndex - 2];
						Out[1] = 1;
						Out[2] = 0;
						OneIndex--;
						return;
					}
					if (TwoIndex > 0 && Two[TwoIndex - 1] <= OneElseMax)
					{
						Out[0] = Two[TwoIndex - 1];
						Out[1] = 2;
						Out[2] = 0;
						TwoIndex--;
						return;
					}
					else if (OneIndex > 1)
					{
						Out[0] = One[OneIndex - 2];
						Out[1] = 1;
						Out[2] = 0;
						return;
					}
					else if (OneIndex > 0)
					{
						Out[0] = One[0];
						Out[1] = 1;
						Out[2] = 0;
						return;
					}
					else
					{
						Out[0] = Two[TwoIndex - 1];
						Out[1] = 2;
						Out[2] = 0;
						return;
					}
				}
				else if (TwoIndex > FourIndex * 2 + 1)
				{
					// 7���� 2ը
					Out[0] = Two[FourIndex * 2 + 1];
					Out[1] = 2;
					Out[2] = 0;
					TwoIndex--;
					for (int i = FourIndex * 2 + 1; i < TwoIndex; ++i)
					{
						Two[i] = Two[i + 1];
					}
				}
				else if (OneIndex > 1)
				{
					Out[0] = One[OneIndex - 2];
					Out[1] = 1;
					Out[2] = 0;
				}
				else if (OneIndex > 0)
				{
					Out[0] = One[0];
					Out[1] = 1;
					Out[2] = 0;
				}
				else
				{
					Out[0] = Four[0];
					Out[1] = 4;
					Out[2] = 4;
					if (TwoIndex > 1)
					{
						Out[3] = Two[0];
						Out[4] = 2;
						Out[5] = Two[1];
					}
					else if (TwoIndex > 0)
					{
						Out[3] = Two[0];
						Out[4] = 1;
						Out[5] = Two[0];
					}
				}
				return;
			}
			
		}
		//------------�ƺõ�ũ�� ||�����¼�
		else if (GoodNM || (DZIndex == -1))
		{
			int Rounds = GetRestRound();
			//Ѱ�ұ�ǩ��С������	
			if (deckIndex > 0 && (deck[0][0] + deck[0][1] - 1 < 12 || deck[0][1] > 6 || Rounds < 5 || (One[0] >= deck[0][0] && Two[0] >= deck[0][0])))
			{
				Out[0] = deck[0][0];
				Out[1] = deck[0][1];
				Out[2] = 1;
				deckIndex--;
				for (int i = 0; i < deckIndex; ++i)
				{
					deck[i][0] = deck[i + 1][0];
					deck[i][1] = deck[i + 1][1];
				}
				return;
			}
			else if (deckTwoIndex > 0 && (TwoIndex == 0 || deckTwo[0][0] <= Two[0]) && (deckTwo[0][0] + deckTwo[0][1] - 1 < 13 || Rounds < 4 ))
			{
				if (TwoIndex > 1 && Two[0]<deckTwo[0][0])
				{
					Out[0] = Two[0];
					Out[1] = 2;
					Out[2] = 0;
					return;
				}
				Out[0] = deckTwo[0][0];
				Out[1] = deckTwo[0][1];
				Out[2] = 2;
				deckTwoIndex--;
				for (int i = 0; i < deckTwoIndex; ++i)
				{
					deckTwo[i][0] = deckTwo[i + 1][0];
					deckTwo[i][1] = deckTwo[i + 1][1];
				}
				return;
			}
			else if (deckThreeIndex > 0 && deckThree[0][0] + deckThree[0][1] - 1 <= OneElseMax && (deckThree[0][0] + deckThree[0][1] - 1 < 11 || OneIndex - deckThree[0][1] < 3 || Rounds < 5))
			{
				//���������뿼��
				if (ThreeIndex > 0 && Three[0]<deckThree[0][0])
				{
					Out[0] = Three[0];
					Out[1] = 3;
					Out[2] = 0;
					for (int i = 0; i < ThreeIndex; i++)
					{
						Three[i] = Three[i + 1];
					}
					ThreeIndex--;
					if (OneIndex > 0 && TwoIndex > 0)//ʲôС���ĸ�
					{
						if (One[0] < Two[0])
						{
							Out[3] = One[0];
							Out[4] = 1;
							OneIndex--;
							for (int i = 0; i < OneIndex; ++i)
							{
								One[i] = One[i + 1];
							}
						}
						else
						{
							Out[3] = Two[0];
							Out[4] = 2;
							TwoIndex--;
							for (int i = 0; i < TwoIndex; ++i)
							{
								Two[i] = Two[i + 1];
							}
						}
					}
					else if (OneIndex > 0)//����
					{
						Out[3] = One[0];
						Out[4] = 1;
						OneIndex--;
						for (int i = 0; i < OneIndex; ++i)
						{
							One[i] = One[i + 1];
						}
					}
					else if (TwoIndex > 0)//����
					{
						Out[3] = Two[0];
						Out[4] = 2;
						TwoIndex--;
						for (int i = 0; i < TwoIndex; ++i)
						{
							Two[i] = Two[i + 1];
						}
					}
					return;
				}
				if (OneIndex > deckThree[0][1] && TwoIndex > deckThree[0][1] && One[deckThree[0][1] - 1] < 13 && Two[deckThree[0][1] - 1] < 13)
				{
					int a = 0;
					int b = 0;
					for (int i = 0; i < deckThree[0][1]; i++)
					{
						a += One[i];
						b += Two[i];
					}
					if (a <= b)
					{
						Out[0] = deckThree[0][0];
						Out[1] = deckThree[0][1];
						Out[2] = 3;
						Out[3] = One[0];
						Out[4] = 1;
						for (int i = 1; i < deckThree[0][1]; i++)
						{
							Out[4 + i] = One[i];
						}
						OneIndex -= deckThree[0][1];
						for (int i = 0; i < OneIndex; i++)
						{
							One[i] = One[i + deckThree[0][1]];
						}
					}
					else
					{
						Out[0] = deckThree[0][0];
						Out[1] = deckThree[0][1];
						Out[2] = 3;
						Out[3] = Two[0];
						Out[4] = 2;
						for (int i = 1; i < deckThree[0][1]; i++)
						{
							Out[4 + i] = Two[i];
						}
						TwoIndex -= deckThree[0][1];
						for (int i = 0; i < TwoIndex; i++)
						{
							Two[i] = Two[i + deckThree[0][1]];
						}
					}
				}
				else if (OneIndex >= deckThree[0][1] && One[deckThree[0][1] - 1] < 14)
				{
					Out[0] = deckThree[0][0];
					Out[1] = deckThree[0][1];
					Out[2] = 3;
					Out[3] = One[0];
					Out[4] = 1;
					for (int i = 1; i < deckThree[0][1]; ++i)
					{
						Out[i + 4] = One[i];
					}
					OneIndex -= deckThree[0][1];
					for (int i = 0; i < OneIndex; ++i)
					{
						One[i] = One[i + deckThree[0][1]];
					}
				}
				else
				{
					int temp = 0;
					for (int i = 0; i < OneIndex; ++i)
					{
						if (One[i] < 15)
						{
							temp++;
						}
					}
					if (temp == 0 || (TwoIndex >= deckThree[0][1] && Two[deckThree[0][1] - 1] < 13))
					{
						if (TwoIndex >= deckThree[0][1] && Two[deckThree[0][1] - 1] < 14)
						{
							Out[0] = deckThree[0][0];
							Out[1] = deckThree[0][1];
							Out[2] = 3;
							Out[3] = Two[0];
							Out[4] = 2;
							for (int i = 1; i < deckThree[0][1]; ++i)
							{
								Out[i + 4] = Two[i];
							}
							TwoIndex -= deckThree[0][1];
							for (int i = 0; i < TwoIndex; ++i)
							{
								Two[i] = Two[i + deckThree[0][1]];
							}
						}
						else if (deckThree[0][1] % 2 == 0 && TwoIndex >= deckThree[0][1] / 2 && Two[deckThree[0][1] / 2 - 1] < 14)
						{
							Out[0] = deckThree[0][0];
							Out[1] = deckThree[0][1];
							Out[2] = 3;
							Out[3] = Two[0];
							Out[4] = 1;
							Out[5] = Two[0];
							for (int i = 1; i < deckThree[0][1] / 2; ++i)
							{
								Out[i + 5] = Two[i];
								Out[i + 6] = Two[i];
							}
							TwoIndex -= deckThree[0][1] / 2;
							for (int i = 0; i < TwoIndex; ++i)
							{
								Two[i] = Two[i + deckThree[0][1] / 2];
							}
						}
						else
						{
							Out[0] = deckThree[0][0];
							Out[1] = deckThree[0][1];
							Out[2] = 3;
						}
					}
					else
					{
						int det = (deckThree[0][1] - temp + 1) / 2;
						if (TwoIndex >= det && Two[det - 1] < 14)
						{
							Out[0] = deckThree[0][0];
							Out[1] = deckThree[0][1];
							Out[2] = 3;
							Out[3] = Two[0];
							Out[4] = 1;
							Out[5] = Two[0];
							for (int i = 1; i < det; ++i)
							{
								Out[i + 5] = Two[i];
								Out[i + 6] = Two[i];
							}
							TwoIndex -= det;
							for (int i = 0; i < TwoIndex; ++i)
							{
								Two[i] = Two[i + det];
							}
							int OneTemp = deckThree[0][1] - det * 2;
							for (int i = 0; i < OneTemp; ++i)
							{
								Out[i + det * 2 + 4] = One[i];
							}
							if (OneTemp > 0)
							{
								OneIndex -= OneTemp;
								for (int i = 0; i < OneIndex; ++i)
								{
									One[i] = One[i + 1];
								}
							}
							//��ֹ777888999,3455���������777888999��355
							for (int i = 3; i < 4 + Out[1]; ++i)
							{
								if (i == 4)
								{
									continue;
								}
								if (Out[i] > One[0])
								{
									int t1 = Out[i];
									Out[i] = One[0];
									One[0] = t1;
								}
							}
						}
						else
						{
							Out[0] = deckThree[0][0];
							Out[1] = deckThree[0][1];
							Out[2] = 3;
						}
					}
				}
				deckThreeIndex--;
				for (int i = 0; i < deckThreeIndex; ++i)
				{
					deckThree[i][0] = deckThree[i + 1][0];
					deckThree[i][1] = deckThree[i + 1][1];
				}
				return;
			}
			else if (ThreeIndex > 0 && Three[0] != 15 && Three[0] != 14 && (Three[0] < 11 || (OneIndex < 2 && TwoIndex < 2)))//�ж�����һ���Ƕ����ǲ���
			{
				Out[0] = Three[0];
				Out[1] = 3;
				Out[2] = 0;
				for (int i = 0; i < ThreeIndex; i++)
				{
					Three[i] = Three[i + 1];
				}
				ThreeIndex--;
				if (OneIndex > 0 && TwoIndex > 0)//ʲôС���ĸ�
				{
					if (One[0] < Two[0])
					{
						Out[3] = One[0];
						Out[4] = 1;
						OneIndex--;
						for (int i = 0; i < OneIndex; ++i)
						{
							One[i] = One[i + 1];
						}
					}
					else
					{
						Out[3] = Two[0];
						Out[4] = 2;
						TwoIndex--;
						for (int i = 0; i < TwoIndex; ++i)
						{
							Two[i] = Two[i + 1];
						}
					}
				}
				else if (OneIndex > 0 && One[0] < 15)//����
				{
					Out[3] = One[0];
					Out[4] = 1;
					OneIndex--;
					for (int i = 0; i < OneIndex; ++i)
					{
						One[i] = One[i + 1];
					}
				}
				else if (TwoIndex > 0)//����
				{
					Out[3] = Two[0];
					Out[4] = 2;
					TwoIndex--;
					for (int i = 0; i < TwoIndex; ++i)
					{
						Two[i] = Two[i + 1];
					}
				}
				return;
			}	
			if (ThreeIndex > 0 && OneIndex + TwoIndex < 4)
			{
				Out[0] = Three[0];
				Out[1] = 3;
				Out[2] = 0;
				for (int i = 0; i < ThreeIndex; i++)
				{
					Three[i] = Three[i + 1];
				}
				ThreeIndex--;
				if (OneIndex > 0 && TwoIndex > 0)//ʲôС���ĸ�
				{
					if (One[0] < Two[0])
					{
						Out[3] = One[0];
						Out[4] = 1;
						OneIndex--;
						for (int i = 0; i < OneIndex; ++i)
						{
							One[i] = One[i + 1];
						}
					}
					else
					{
						Out[3] = Two[0];
						Out[4] = 2;
						TwoIndex--;
						for (int i = 0; i < TwoIndex; ++i)
						{
							Two[i] = Two[i + 1];
						}
					}
				}
				else if (OneIndex > 0 && One[0] < 15)//����
				{
					Out[3] = One[0];
					Out[4] = 1;
					OneIndex--;
					for (int i = 0; i < OneIndex; ++i)
					{
						One[i] = One[i + 1];
					}
				}
				else if (TwoIndex > 0)//����
				{
					Out[3] = Two[0];
					Out[4] = 2;
					TwoIndex--;
					for (int i = 0; i < TwoIndex; ++i)
					{
						Two[i] = Two[i + 1];
					}
				}
				return;
			}
			else if (OneIndex > 0 && TwoIndex > 0)//ʲôС���ĸ�
			{
				if (One[0] < Two[0])
				{
					Out[0] = One[0];
					Out[1] = 1;
					Out[2] = 0;
					OneIndex--;
					for (int i = 0; i < OneIndex; ++i)
					{
						One[i] = One[i + 1];
					}
					return;
				}
				else
				{
					Out[0] = Two[0];
					Out[1] = 2;
					Out[2] = 0;
					TwoIndex--;
					for (int i = 0; i < TwoIndex; ++i)
					{
						Two[i] = Two[i + 1];
					}
					return;
				}
			}
			else if (OneIndex > 0)//����
			{
				if (OneIndex == 2 && One[OneIndex - 1] >= OneElseMax)
				{
					Out[0] = One[OneIndex - 1];
					Out[1] = 1;
					Out[2] = 0;
					OneIndex--;
					return;
				}
				Out[0] = One[0];
				Out[1] = 1;
				Out[2] = 0;
				OneIndex--;
				for (int i = 0; i < OneIndex; ++i)
				{
					One[i] = One[i + 1];
				}
			}
			else if (TwoIndex > 0)//����
			{
				if (TwoIndex == 2 && Two[TwoIndex - 1] >= TwoElseMax)
				{
					Out[0] = Two[TwoIndex - 1];
					Out[1] = 2;
					Out[2] = 0;
					TwoIndex--;
					return;
				}
				Out[0] = Two[0];
				Out[1] = 2;
				Out[2] = 0;
				TwoIndex--;
				for (int i = 0; i < TwoIndex; ++i)
				{
					Two[i] = Two[i + 1];
				}
			}
			else if (FourIndex > 0)//four
			{
				Out[0] = Four[0];
				Out[1] = 4;
				Out[2] = 4;
				FourIndex--;
				for (int i = 0; i < FourIndex; ++i)
				{
					Four[i] = Four[i + 1];
				}
			}
			else if (KingBoom == 1)
			{
				Out[0] = 17;
				Out[1] = 2;
				Out[2] = 4;
				KingBoom = 0;
			}
			return;
		}
		//------------�Ʋ��ũ��&���ҷ�������
		else
		{
			int Rounds = GetRestRound();
			//Ѱ�ұ�ǩ��С������	
			if (deckIndex > 0 && (deck[0][0] + deck[0][1] - 1 < 12 || deck[0][1] > 6 || Rounds < 5 || One[0] >= deck[0][0] || behindN < 6))
			{
				Out[0] = deck[0][0];
				Out[1] = deck[0][1];
				Out[2] = 1;
				deckIndex--;
				for (int i = 0; i < deckIndex; ++i)
				{
					deck[i][0] = deck[i + 1][0];
					deck[i][1] = deck[i + 1][1];
				}
				return;
			}
			else if (deckTwoIndex > 0 && (TwoIndex == 0 || deckTwo[0][0] <= Two[0]) && (deckTwo[0][0] + deckTwo[0][1] - 1 < 13 || Rounds < 4 || behindN < 6))
			{
				Out[0] = deckTwo[0][0];
				Out[1] = deckTwo[0][1];
				Out[2] = 2;
				deckTwoIndex--;
				for (int i = 0; i < deckTwoIndex; ++i)
				{
					deckTwo[i][0] = deckTwo[i + 1][0];
					deckTwo[i][1] = deckTwo[i + 1][1];
				}
				return;
			}
			else if (deckThreeIndex > 0 && deckThree[0][0] + deckThree[0][1] - 1 <= OneElseMax && (deckThree[0][0] + deckThree[0][1] - 1 < 11 || OneIndex - deckThree[0][1] < 3 || Rounds < 5 || behindN < 6))
			{
				//���������뿼��
				if (ThreeIndex > 0 && Three[0]<deckThree[0][0])
				{
					Out[0] = Three[0];
					Out[1] = 3;
					Out[2] = 0;
					for (int i = 0; i < ThreeIndex; i++)
					{
						Three[i] = Three[i + 1];
					}
					ThreeIndex--;
					if (OneIndex > 0 && TwoIndex > 0)//ʲôС���ĸ�
					{
						if (One[0] < Two[0])
						{
							Out[3] = One[0];
							Out[4] = 1;
							OneIndex--;
							for (int i = 0; i < OneIndex; ++i)
							{
								One[i] = One[i + 1];
							}
						}
						else
						{
							Out[3] = Two[0];
							Out[4] = 2;
							TwoIndex--;
							for (int i = 0; i < TwoIndex; ++i)
							{
								Two[i] = Two[i + 1];
							}
						}
					}
					else if (OneIndex > 0)//����
					{
						Out[3] = One[0];
						Out[4] = 1;
						OneIndex--;
						for (int i = 0; i < OneIndex; ++i)
						{
							One[i] = One[i + 1];
						}
					}
					else if (TwoIndex > 0)//����
					{
						Out[3] = Two[0];
						Out[4] = 2;
						TwoIndex--;
						for (int i = 0; i < TwoIndex; ++i)
						{
							Two[i] = Two[i + 1];
						}
					}
					return;
				}
				if (OneIndex > deckThree[0][1] && TwoIndex > deckThree[0][1] && One[deckThree[0][1] - 1] < 13 && Two[deckThree[0][1] - 1] < 13)
				{
					int a = 0;
					int b = 0;
					for (int i = 0; i < deckThree[0][1]; i++)
					{
						a += One[i];
						b += Two[i];
					}
					if (a <= b)
					{
						Out[0] = deckThree[0][0];
						Out[1] = deckThree[0][1];
						Out[2] = 3;
						Out[3] = One[0];
						Out[4] = 1;
						for (int i = 1; i < deckThree[0][1]; i++)
						{
							Out[4 + i] = One[i];
						}
						OneIndex -= deckThree[0][1];
						for (int i = 0; i < OneIndex; i++)
						{
							One[i] = One[i + deckThree[0][1]];
						}
					}
					else
					{
						Out[0] = deckThree[0][0];
						Out[1] = deckThree[0][1];
						Out[2] = 3;
						Out[3] = Two[0];
						Out[4] = 2;
						for (int i = 1; i < deckThree[0][1]; i++)
						{
							Out[4 + i] = Two[i];
						}
						TwoIndex -= deckThree[0][1];
						for (int i = 0; i < TwoIndex; i++)
						{
							Two[i] = Two[i + deckThree[0][1]];
						}
					}
				}
				else if (OneIndex >= deckThree[0][1] && One[deckThree[0][1] - 1] < 14)
				{
					Out[0] = deckThree[0][0];
					Out[1] = deckThree[0][1];
					Out[2] = 3;
					Out[3] = One[0];
					Out[4] = 1;
					for (int i = 1; i < deckThree[0][1]; ++i)
					{
						Out[i + 4] = One[i];
					}
					OneIndex -= deckThree[0][1];
					for (int i = 0; i < OneIndex; ++i)
					{
						One[i] = One[i + deckThree[0][1]];
					}
				}
				else
				{
					int temp = 0;
					for (int i = 0; i < OneIndex; ++i)
					{
						if (One[i] < 15)
						{
							temp++;
						}
					}
					if (temp == 0 || (TwoIndex >= deckThree[0][1] && Two[deckThree[0][1] - 1] < 13))
					{
						if (TwoIndex >= deckThree[0][1] && Two[deckThree[0][1] - 1] < 14)
						{
							Out[0] = deckThree[0][0];
							Out[1] = deckThree[0][1];
							Out[2] = 3;
							Out[3] = Two[0];
							Out[4] = 2;
							for (int i = 1; i < deckThree[0][1]; ++i)
							{
								Out[i + 4] = Two[i];
							}
							TwoIndex -= deckThree[0][1];
							for (int i = 0; i < TwoIndex; ++i)
							{
								Two[i] = Two[i + deckThree[0][1]];
							}
						}
						else if (deckThree[0][1] % 2 == 0 && TwoIndex >= deckThree[0][1] / 2 && Two[deckThree[0][1] / 2 - 1] < 14)
						{
							Out[0] = deckThree[0][0];
							Out[1] = deckThree[0][1];
							Out[2] = 3;
							Out[3] = Two[0];
							Out[4] = 1;
							Out[5] = Two[0];
							for (int i = 1; i < deckThree[0][1] / 2; ++i)
							{
								Out[i + 5] = Two[i];
								Out[i + 6] = Two[i];
							}
							TwoIndex -= deckThree[0][1] / 2;
							for (int i = 0; i < TwoIndex; ++i)
							{
								Two[i] = Two[i + deckThree[0][1] / 2];
							}
						}
						else
						{
							Out[0] = deckThree[0][0];
							Out[1] = deckThree[0][1];
							Out[2] = 3;
						}
					}
					else
					{
						int det = (deckThree[0][1] - temp + 1) / 2;
						if (TwoIndex >= det && Two[det - 1] < 14)
						{
							Out[0] = deckThree[0][0];
							Out[1] = deckThree[0][1];
							Out[2] = 3;
							Out[3] = Two[0];
							Out[4] = 1;
							Out[5] = Two[0];
							for (int i = 1; i < det; ++i)
							{
								Out[i + 5] = Two[i];
								Out[i + 6] = Two[i];
							}
							TwoIndex -= det;
							for (int i = 0; i < TwoIndex; ++i)
							{
								Two[i] = Two[i + det];
							}
							int OneTemp = deckThree[0][1] - det * 2;
							for (int i = 0; i < OneTemp; ++i)
							{
								Out[i + det * 2 + 4] = One[i];
							}
							if (OneTemp > 0)
							{
								OneIndex -= OneTemp;
								for (int i = 0; i < OneIndex; ++i)
								{
									One[i] = One[i + 1];
								}
							}
							//��ֹ777888999,3455���������777888999��355
							for (int i = 3; i < 4 + Out[1]; ++i)
							{
								if (i == 4)
								{
									continue;
								}
								if (Out[i] > One[0])
								{
									int t1 = Out[i];
									Out[i] = One[0];
									One[0] = t1;
								}
							}
						}
						else
						{
							Out[0] = deckThree[0][0];
							Out[1] = deckThree[0][1];
							Out[2] = 3;
						}
					}
				}
				deckThreeIndex--;
				for (int i = 0; i < deckThreeIndex; ++i)
				{
					deckThree[i][0] = deckThree[i + 1][0];
					deckThree[i][1] = deckThree[i + 1][1];
				}
				return;
			}
			else if (ThreeIndex > 0 && Three[0] != 15 && Three[0] != 14 && (Three[0] < 11 || (OneIndex < 2 && TwoIndex < 2 || behindN < 5)))
			{
				Out[0] = Three[0];
				Out[1] = 3;
				Out[2] = 0;
				for (int i = 0; i < ThreeIndex; i++)
				{
					Three[i] = Three[i + 1];
				}
				ThreeIndex--;
				if (OneIndex > 0 && TwoIndex > 0)//ʲôС���ĸ�
				{
					if (One[0] < Two[0])
					{
						Out[3] = One[0];
						Out[4] = 1;
						OneIndex--;
						for (int i = 0; i < OneIndex; ++i)
						{
							One[i] = One[i + 1];
						}
					}
					else
					{
						Out[3] = Two[0];
						Out[4] = 2;
						TwoIndex--;
						for (int i = 0; i < TwoIndex; ++i)
						{
							Two[i] = Two[i + 1];
						}
					}
				}
				else if (OneIndex > 0 && One[0] < 15)//����
				{
					Out[3] = One[0];
					Out[4] = 1;
					OneIndex--;
					for (int i = 0; i < OneIndex; ++i)
					{
						One[i] = One[i + 1];
					}
				}
				else if (TwoIndex > 0)//����
				{
					Out[3] = Two[0];
					Out[4] = 2;
					TwoIndex--;
					for (int i = 0; i < TwoIndex; ++i)
					{
						Two[i] = Two[i + 1];
					}
				}
				return;
			}
			if (ThreeIndex > 0 && OneIndex + TwoIndex < 4)
			{
				Out[0] = Three[0];
				Out[1] = 3;
				Out[2] = 0;
				for (int i = 0; i < ThreeIndex; i++)
				{
					Three[i] = Three[i + 1];
				}
				ThreeIndex--;
				if (OneIndex > 0 && TwoIndex > 0)//ʲôС���ĸ�
				{
					if (One[0] < Two[0])
					{
						Out[3] = One[0];
						Out[4] = 1;
						OneIndex--;
						for (int i = 0; i < OneIndex; ++i)
						{
							One[i] = One[i + 1];
						}
					}
					else
					{
						Out[3] = Two[0];
						Out[4] = 2;
						TwoIndex--;
						for (int i = 0; i < TwoIndex; ++i)
						{
							Two[i] = Two[i + 1];
						}
					}
				}
				else if (OneIndex > 0 && One[0] < 15)//����
				{
					Out[3] = One[0];
					Out[4] = 1;
					OneIndex--;
					for (int i = 0; i < OneIndex; ++i)
					{
						One[i] = One[i + 1];
					}
				}
				else if (TwoIndex > 0)//����
				{
					Out[3] = Two[0];
					Out[4] = 2;
					TwoIndex--;
					for (int i = 0; i < TwoIndex; ++i)
					{
						Two[i] = Two[i + 1];
					}
				}
				return;
			}
			else//û������
			{
				int sum = 0;
				for (int i = 0; i < OneIndex; ++i)
				{
					if (One[i] > 7 && One[i] < 13 && sum < 3)
					{
						Out[0] = One[i];
						Out[1] = 1;
						Out[2] = 0;
						OneIndex--;
						for (int j = i; j < OneIndex; ++j)
						{
							One[j] = One[j + 1];
						}
						return;
					}
					sum++;
				}
				sum = 0;
				for (int i = 0; i < TwoIndex; ++i)
				{
					if (Two[i] > 7 && Two[i] < 13 && sum < 2)
					{
						Out[0] = Two[i];
						Out[1] = 2;
						Out[2] = 0;
						TwoIndex--;
						for (int j = i; j < TwoIndex; ++j)
						{
							Two[j] = Two[j + 1];
						}
						return;
					}
				}
				if (OneIndex > 0 && TwoIndex > 0)//ʲôС���ĸ�
				{
					if (One[0] < Two[0])
					{
						Out[0] = One[0];
						Out[1] = 1;
						Out[2] = 0;
						OneIndex--;
						for (int i = 0; i < OneIndex; ++i)
						{
							One[i] = One[i + 1];
						}
						return;
					}
					else
					{
						Out[0] = Two[0];
						Out[1] = 2;
						Out[2] = 0;
						TwoIndex--;
						for (int i = 0; i < TwoIndex; ++i)
						{
							Two[i] = Two[i + 1];
						}
						return;
					}
				}
				else if (OneIndex > 0)//����
				{
					if (OneIndex == 2 && One[OneIndex - 1] >= OneElseMax)
					{
						Out[0] = One[OneIndex - 1];
						Out[1] = 1;
						Out[2] = 0;
						OneIndex--;
						return;
					}
					Out[0] = One[0];
					Out[1] = 1;
					Out[2] = 0;
					OneIndex--;
					for (int i = 0; i < OneIndex; ++i)
					{
						One[i] = One[i + 1];
					}
				}
				else if (TwoIndex > 0)//����
				{
					if (TwoIndex == 2 && Two[TwoIndex - 1] >= TwoElseMax)
					{
						Out[0] = Two[TwoIndex - 1];
						Out[1] = 2;
						Out[2] = 0;
						TwoIndex--;
						return;
					}
					Out[0] = Two[0];
					Out[1] = 2;
					Out[2] = 0;
					TwoIndex--;
					for (int i = 0; i < TwoIndex; ++i)
					{
						Two[i] = Two[i + 1];
					}
				}
				else if (KingBoom == 1)
				{
					Out[0] = 17;
					Out[1] = 2;
					Out[2] = 4;
					KingBoom = 0;
				}
				else if (FourIndex > 0)//four
				{
					Out[0] = Four[0];
					Out[1] = 4;
					Out[2] = 4;
					FourIndex--;
					for (int i = 0; i < FourIndex; ++i)
					{
						Four[i] = Four[i + 1];
					}
				}
				else
				{
					//û���ˣ�
				}
				return;
			}
		}
	}
}
/*
ѹ��
*/
int card::PassivePlay(int *UpperCard, int * Out, int WhoseOut)//����
{
	//�Ƶ�����
	//���ţ����ӣ�����=0��
	//˳��=1;
	//����=2;
	//�ɻ�=3;
	if (GetRestRound() == 1)
	{
		if (KingBoom != 0)
		{
			Out[0] = 17;
			Out[1] = 2;
			Out[2] = 4;
			KingBoom = 0;
			return 1;
		}
		else if (FourIndex > 0)
		{
			Out[0] = Four[0];
			Out[1] = 4;
			Out[2] = 4;
			return 1;
		}
		if (UpperCard[2] == 0)
		{
			if (UpperCard[1] == 1)
			{
				if (OneIndex > 0 && One[0] > UpperCard[0])
				{
					Out[0] = One[0];
					Out[1] = 1;
					Out[2] = 0;
					return 1;
				}
				else if (TwoIndex > 0 && Two[0] > UpperCard[0] && Two[0] >= OneElseMax)
				{
					Out[0] = Two[0];
					Out[1] = 1;
					Out[2] = 0;
					return 1;
				}
				else if (ThreeIndex > 0 && Three[0] > UpperCard[0] && Three[0] >= OneElseMax&&Three[0] >= TwoElseMax)
				{
					Out[0] = Three[0];
					Out[1] = 1;
					Out[2] = 0;
					return 1;
				}
			}
			else if (UpperCard[1] == 2)
			{
				if (TwoIndex > 0 && Two[0] > UpperCard[0])
				{
					Out[0] = Two[0];
					Out[1] = 2;
					Out[2] = 0;
					return 1;
				}
				else if (ThreeIndex > 0 && Three[0] > UpperCard[0] && Three[0] >= OneElseMax)
				{
					Out[0] = Three[0];
					Out[1] = 2;
					Out[2] = 0;
					return 1;
				}
			}
			else if (UpperCard[1] == 3 && ThreeIndex > 0 && Three[0] > UpperCard[0])
			{
				if (UpperCard[4] == 1 && OneIndex > 0)
				{
					Out[0] = Three[0];
					Out[1] = 3;
					Out[2] = 0;
					Out[3] = One[0];
					Out[4] = 1;
					return 1;
				}
				else if (UpperCard[4] == 2 && TwoIndex > 0)
				{
					Out[0] = Three[0];
					Out[1] = 3;
					Out[2] = 0;
					Out[3] = Two[0];
					Out[4] = 2;
					return 1;
				}
				else if (UpperCard[4] == -1)
				{
					Out[0] = Three[0];
					Out[1] = 3;
					Out[2] = 0;
					return 1;
				}
			}
		}
		else if (UpperCard[2] == 1 && deckIndex > 0 && deck[0][0] > UpperCard[0] && deck[0][1] == UpperCard[1])
		{
			Out[0] = deck[0][0];
			Out[1] = deck[0][1];
			Out[2] = 1;
			return 1;
		}
	}
	if (UpperCard[0] == 17 && UpperCard[1] == 2 && UpperCard[2] == 4)
	{
		return -1;
	}
	//****************����*********************//
	if (IsDZ)
	{
		int MyRoundNum = GetRestRound();
		if (MyRoundNum == 2)
		{
			if (KingBoom == 1)
			{
				Out[0] = 17;
				Out[1] = 2;
				Out[2] = 4;
				KingBoom = 0;
				return 1;
			}
			if (UpperCard[1] == 4 && UpperCard[2] == 4 && UpperCard[4] == 0 && FourIndex > 0)
			{
				if (Four[FourIndex - 1] > UpperCard[0])
				{
					Out[0] = Four[FourIndex - 1];
					Out[1] = 4;
					Out[2] = 4;
					FourIndex--;
					for (int i = 0; i < FourIndex; ++i)
					{
						Four[i] = Four[i + 1];
					}
					return 1;
				}
			}
			else if (FourIndex > 0)
			{
				Out[0] = Four[0];
				Out[1] = 4;
				Out[2] = 4;
				FourIndex--;
				for (int i = 0; i < FourIndex; ++i)
				{
					Four[i] = Four[i + 1];
				}
				return 1;
			}
		}
		if (UpperCard[2] == 0)
		{
			if (UpperCard[1] == 1)//������
			{
				if (OneIndex > 0)
				{
					if (MyRoundNum < 3 && OneIndex + TwoIndex < 3 && One[OneIndex - 1] >= OneElseMax)
					{
						if (One[OneIndex - 1] > UpperCard[0])
						{
							Out[0] = One[OneIndex - 1];
							Out[1] = 1;
							Out[2] = 0;
							OneIndex--;
							return 1;
						}				
					}
					int TempOneNM = 0;
					if(behindN < 3 || frontN < 3)
					{
						for(int i=17;i>2;i--)
						{
							if(elseCard[i] >0)
							{
								TempOneNM = i;
								break;
							}
						}
					}
					for (int i = 0; i < OneIndex; ++i)
					{
						if (One[i] > UpperCard[0] && One[i] >= TempOneNM)
						{
							Out[0] = One[i];
							Out[1] = 1;
							Out[2] = 0;
							OneIndex--;
							for (int j = i; j < OneIndex; ++j)
							{
								One[j] = One[j + 1];
							}
							return 1;
						}
					}
					for (int i = OneIndex-1; i >= 0; --i)
					{
						if (One[i] > UpperCard[0])
						{
							Out[0] = One[i];
							Out[1] = 1;
							Out[2] = 0;
							OneIndex--;
							for (int j = i; j < OneIndex; ++j)
							{
								One[j] = One[j + 1];
							}
							return 1;
						}
					}
				}
				//else ����else��ϵ  one�п���û�������� //����
				{
					int MaxRestC = 0, IsHave = 0;
					for (int i = 15; i >= 3; --i)
					{
						if (myCard[i] > 0)
						{
							MaxRestC = i;
							IsHave = 1;
						}
						if (elseCard[i] > 0)
						{
							MaxRestC = i;
							break;
						}
					}
					if (UpperCard[0] >= MaxRestC)
					{
						MaxRestC = UpperCard[0] + 1;
					}
					if (deckIndex > 0 && (IsHave == 1 || frontN < 4 || behindN < 4))
					{
						for (int i = 0; i < deckIndex; ++i)
						{
							if (deck[i][1] > 5 && deck[i][0] + deck[i][1] - 1 >= MaxRestC)
							{
								Out[0] = deck[i][0] + deck[i][1] - 1;
								Out[1] = 1;
								Out[2] = 0;
								deck[i][1]--;
								return 1;
							}
						}
					}
					if (TwoIndex > 0 && (IsHave == 1 || frontN < 4 || behindN < 4))
					{
						for (int i = 0; i < TwoIndex; ++i)
						{
							if (Two[i] >= MaxRestC)
							{
								Out[0] = Two[i];
								Out[1] = 1;
								Out[2] = 0;
								TwoIndex--;
								while(i < TwoIndex)
								{
									Two[i] = Two[i + 1];
									++i;
								}
								int IsADD = 0;
								for (int j = 0; j < OneIndex; j++)
								{
									if (One[j] > Out[0])
									{
										for (int k = OneIndex; k > j; --k)
										{
											One[k] = One[k - 1];
										}
										++OneIndex;
										One[j] = Out[0];
										IsADD = 1;
										break;
									}
								}
								if(IsADD == 0)
								{
									One[OneIndex] = Out[0];
									OneIndex++;
								}
								return 1;
							}
						}
					}
					if (ThreeIndex > 0 && (IsHave == 1 || frontN < 4 || behindN < 4))
					{
						for (int i = 0; i < ThreeIndex; ++i)
						{
							if (Three[i] >= MaxRestC)
							{
								Out[0] = Three[i];
								Out[1] = 1;
								Out[2] = 0;
								ThreeIndex--;
								for (int j = 0; j < TwoIndex; j++)
								{
									if (Two[j] > Out[0])
									{
										for (int k = TwoIndex; k > j; --k)
										{
											Two[k] = Two[k - 1];
										}
										++TwoIndex;
										Two[j] = Out[0];
									}
								}
								return 1;
							}
						}
					}
					if (frontN < 4 || behindN < 4)
					{
						int boomtemp = -1;
						for (int i = 15; i > 2; i--)
						{
							if (elseCard[i] > 3)
							{
								boomtemp = i;
								break;
							}
						}
						if (boomtemp > 0 && FourIndex > 0)
						{
							Out[0] = Four[0];
							Out[1] = 4;
							Out[2] = 4;
							FourIndex--;
							for (int i = 0; i < FourIndex; ++i)
							{
								Four[i] = Four[i + 1];
							}
							return 1;
						}
						else if (KingBoom > 0)
						{
							Out[0] = 16;
							Out[1] = 1;
							Out[2] = 0;
							KingBoom = 0;
							One[OneIndex] = 17;
							OneIndex++;
							return 1;
						}
						else if (FourIndex > 0)
						{
							Out[0] = Four[0];
							Out[1] = 4;
							Out[2] = 4;
							FourIndex--;
							for (int i = 0; i < FourIndex; ++i)
							{
								Four[i] = Four[i + 1];
							}
							return 1;
						}
					}
				}

				return -1;
			}
			else if (UpperCard[1] == 2)
			{
				if (TwoIndex > 0)
				{
					if (MyRoundNum < 3 && OneIndex + TwoIndex < 3&& Two[TwoIndex - 1] >= TwoElseMax)
					{
						if (Two[TwoIndex - 1] > UpperCard[0])
						{
							Out[0] = Two[TwoIndex - 1];
							Out[1] = 2;
							Out[2] = 0;
							TwoIndex--;
							return 1;
						}		
					}
					int TempTwoNM = 0;
					if (behindN < 5 || frontN < 5)
					{
						for(int i=15;i>2;i--)
						{
							if(elseCard[i] >1)
							{
								TempTwoNM = i;
								break;
							}
						}
					}
					for (int i = 0; i < TwoIndex; ++i)
					{
						if (Two[i] > UpperCard[0] && Two[i] >= TempTwoNM)
						{
							Out[0] = Two[i];
							Out[1] = 2;
							Out[2] = 0;
							TwoIndex--;
							for (int j = i; j < TwoIndex; ++j)
							{
								Two[j] = Two[j + 1];
							}
							return 1;
						}
					}
					for (int i = TwoIndex - 1; i >= 0; --i)
					{
						if (Two[i] > UpperCard[0])
						{
							Out[0] = Two[i];
							Out[1] = 2;
							Out[2] = 0;
							TwoIndex--;
							for (int j = i; j < TwoIndex; ++j)
							{
								Two[j] = Two[j + 1];
							}
							return 1;
						}
					}
				}
				//����Ҫ�Ż�
				int MaxRestC = 0, IsHave = 0;
				for (int i = 15; i >= 3; --i)
				{
					if (myCard[i] > 1)
					{
						MaxRestC = i;
						IsHave = 1;
					}
					if (elseCard[i] > 1)
					{
						MaxRestC = i;
						break;
					}
				}
				if (UpperCard[0] >= MaxRestC)
				{
					MaxRestC = UpperCard[0] + 1;
				}
				if (deckTwoIndex > 0 && (IsHave == 1 || frontN < 4 || behindN < 4))
				{
					for (int i = 0; i < deckTwoIndex; ++i)
					{
						if (deckTwo[i][0] + deckTwo[i][1] - 1 >= MaxRestC)
						{
							if (frontN < 4 || behindN < 4)
							{
								if (deckTwo[i][1] > 3)
								{
									Out[0] = deckTwo[i][0] + deckTwo[i][1] - 1;
									Out[1] = 2;
									Out[2] = 0;
									deckTwo[i][1]--;
								}
								else
								{
									int temp = -1;
									for (int j = 0; j < 3; j++)
									{
										if (deckTwo[j][0] + j >= MaxRestC)
										{
											temp = i;
											break;
										}
									}
									Out[0] = deckTwo[i][0] + temp;
									Out[1] = 2;
									Out[2] = 0;
									bool flag = false;
									for (int j = 0; j < TwoIndex; ++j)
									{
										if (Two[j] > Out[0])
										{
											for (int k = TwoIndex; k > j; k--)
											{
												Two[k+1] = Two[k - 1];
											}
											flag = true;
											TwoIndex += 2;
											for (int k = 0; k < 3; k++)
											{
												if (k == temp)
												{
													continue;
												}
												Two[j + k] = deckTwo[j][0] + k;
											}
											break;
										}
									}
									deckTwoIndex--;
									for (int j = i; j < deckTwoIndex; ++j)
									{
										deckTwo[j][0] = deckTwo[j + 1][0];
										deckTwo[j][1] = deckTwo[j + 1][1];
									}
								}
								return 1;
							}
							else if (deckTwo[i][1] > 3)
							{
								Out[0] = deckTwo[i][0] + deckTwo[i][1] - 1;
								Out[1] = 2;
								Out[2] = 0;
								deckTwo[i][1]--;
								return 1;
							}
							else
							{

							}
						}
					}
				}
				if (ThreeIndex > 0 && (IsHave == 1 || frontN < 4 || behindN < 4) && One[0] > 8 && OneIndex < 3)
				{
					for (int i = 0; i < ThreeIndex; ++i)
					{
						if (Three[i] >= MaxRestC)
						{
							Out[0] = Three[i];
							Out[1] = 2;
							Out[2] = 0;
							ThreeIndex--;
							return 1;
						}
					}
				}
				if (frontN < 4 || behindN < 4)
				{
					int boomtemp = -1;
					for (int i = 15; i > 2; i--)
					{
						if (elseCard[i] > 3)
						{
							boomtemp = i;
							break;
						}
					}
					if (boomtemp > 0 && FourIndex > 0)
					{
						Out[0] = Four[0];
						Out[1] = 4;
						Out[2] = 4;
						FourIndex--;
						for (int i = 0; i < FourIndex; ++i)
						{
							Four[i] = Four[i + 1];
						}
						return 1;
					}
					else if (KingBoom > 0 && OneIndex < 3)
					{
						Out[0] = 17;
						Out[1] = 2;
						Out[2] = 4;
						KingBoom = 0;
						return 1;
					}
					else if (FourIndex > 0)
					{
						Out[0] = Four[0];
						Out[1] = 4;
						Out[2] = 4;
						FourIndex--;
						for (int i = 0; i < FourIndex; ++i)
						{
							Four[i] = Four[i + 1];
						}
						return 1;
					}
				}
			}
			else//UpperCard[3] ==3
			{
				bool IsRes = false;
				bool flag = false;
				int temp = 0;
				for (int i = 0; i < ThreeIndex; ++i)
				{
					if (Three[i] > UpperCard[0])
					{
						Out[0] = Three[i];
						Out[1] = 3;
						Out[2] = 0;
						temp = i;
						IsRes = true;
						break;
					}
				}
				//�ɻ����
				if (IsRes == false)
				{
					for (int i = 0; i < deckThreeIndex; ++i)
					{
						if (deckThree[i][0] + deckThree[i][1] - 1 > UpperCard[0])
						{
							Out[0] = deckThree[i][0] + deckThree[i][1] - 1;
							Out[1] = 3;
							Out[2] = 0;
							temp = 10 + i;
							IsRes = true;
							break;
						}
					}
				}
				//************���� 0,1,2
				if (IsRes == true)
				{
					if (UpperCard[4] == 1)
					{
						if (OneIndex > 0 && One[0] < 15)
						{
							Out[4] = 1;
							Out[3] = One[0];
							OneIndex++;
							for (int i = 0; i < OneIndex; ++i)
							{
								One[i] = One[i + 1];
							}
							flag = true;
						}
						else//�ص��Ż�//˼���Ƿ�һ��Ҫѹ������ӻ��ǲ�˳�ӻ��ǲ����������������//������˳�ӣ���������
						{
							if (frontN < 5 || behindN < 5)
							{
								int boomtemp = -1;
								for (int i = 15; i > 2; i--)
								{
									if (elseCard[i] > 3)
									{
										boomtemp = i;
										break;
									}
								}
								if (boomtemp > 0 && FourIndex > 0)
								{
									Out[0] = Four[0];
									Out[1] = 4;
									Out[2] = 4;
									Out[4] = 0;
									Out[3] = 0;
									FourIndex--;
									for (int i = 0; i < FourIndex; ++i)
									{
										Four[i] = Four[i + 1];
									}
									return 1;
								}
								else if (KingBoom > 0 && OneIndex < 3)
								{
									Out[0] = 17;
									Out[1] = 2;
									Out[2] = 4;
									KingBoom = 0;
									return 1;
								}
								else if (FourIndex > 0)
								{
									Out[0] = Four[0];
									Out[1] = 4;
									Out[2] = 4;
									Out[4] = 0;
									Out[3] = 0;
									FourIndex--;
									for (int i = 0; i < FourIndex; ++i)
									{
										Four[i] = Four[i + 1];
									}
									return 1;
								}
								else
								{
									if (deckIndex > 0)
									{
										for (int i = 0; i < deckIndex; ++i)
										{
											if (deck[i][1] > 5)
											{
												Out[3] = deck[i][0];
												Out[4] = 1;
												deck[i][0]++;
												deck[i][1]--;
												flag = true;
												break;
											}
										}
									}
									else if (TwoIndex > 1)
									{
										Out[3] = Two[TwoIndex - 2];
										Out[4] = 1;
										Two[TwoIndex - 2] = Two[TwoIndex - 1];
										bool fg = false;
										flag = true;
										for (int i = 0; i < OneIndex; ++i)
										{
											if (One[i] > Out[3])
											{
												for (int j = OneIndex; j > i; j--)
												{
													One[j] = One[j - 1];
												}
												OneIndex++;
												One[i] = Out[3];
												fg = true;
												break;
											}
										}
										if (!fg)
										{
											One[OneIndex] = Out[3];
											OneIndex++;
										}
									}
									else if (TwoIndex == 1)
									{
										Out[3] = Two[TwoIndex - 1];
										Out[4] = 1;
										TwoIndex--;
										bool fg = false;
										flag = true;
										for (int i = 0; i < OneIndex; ++i)
										{
											if (One[i] > Out[3])
											{
												for (int j = OneIndex; j > i; j--)
												{
													One[j] = One[j - 1];
												}
												OneIndex++;
												One[i] = Out[3];
												fg = true;
												break;
											}
										}
										if (!fg)
										{
											One[OneIndex] = Out[3];
											OneIndex++;
										}
									}
									else if (ThreeIndex > 1 && ThreeIndex - 2 != temp)
									{
										Out[3] = Three[ThreeIndex - 2];
										Out[4] = 1;
										Three[ThreeIndex - 2] = Three[ThreeIndex - 1];
										ThreeIndex--;
										flag = true;
										bool fg = false;
										for (int i = 0; i < TwoIndex; ++i)
										{
											if (Two[i] > Out[3])
											{
												for (int j = TwoIndex; j > i; j--)
												{
													Two[j] = Two[j - 1];
												}
												Two[i] = Out[3];
												TwoIndex++;
												fg = true;
												break;
											}
										}
										if (!fg)
										{
											Two[TwoIndex] = Out[3];
											TwoIndex++;
										}
									}
									else if ((ThreeIndex == 1 && Three[0] < 15 && ThreeIndex != temp)||(ThreeIndex > 1 && ThreeIndex - 2 != temp))
									{
										Out[3] = Three[ThreeIndex - 1];
										Out[4] = 1;
										ThreeIndex--;
										flag = true;
										bool fg = false;
										for (int i = 0; i < TwoIndex; ++i)
										{
											if (Two[i] > Out[3])
											{
												for (int j = TwoIndex; j > i; j--)
												{
													Two[j] = Two[j - 1];
												}
												Two[i] = Out[3];
												TwoIndex++;
												fg = true;
												break;
											}
										}
										if (!fg)
										{
											Two[TwoIndex] = Out[3];
											TwoIndex++;
										}
									}
									else
									{

									}
								}
							}
							else if (deckIndex > 0)
							{
								for (int i = 0; i < deckIndex; ++i)
								{
									if (deck[i][1] > 5)
									{
										Out[3] = deck[i][0];
										Out[4] = 1;
										deck[i][0]++;
										deck[i][1]--;
										flag = true;
										break;
									}
								}
							}
							else if (TwoIndex > 1)
							{
								Out[3] = Two[TwoIndex - 2];
								Out[4] = 1;
								Two[TwoIndex - 2] = Two[TwoIndex - 1];
								bool fg = false;
								flag = true;
								for (int i = 0; i < OneIndex; ++i)
								{
									if (One[i] > Out[3])
									{
										for (int j = OneIndex; j > i; j--)
										{
											One[j] = One[j - 1];
										}
										OneIndex++;
										One[i] = Out[3];
										fg = true;
										break;
									}
								}
								if (!fg)
								{
									One[OneIndex] = Out[3];
									OneIndex++;
								}
							}
							else if (TwoIndex == 1)
							{
								Out[3] = Two[TwoIndex - 1];
								Out[4] = 1;
								TwoIndex--;
								bool fg = false;
								flag = true;
								for (int i = 0; i < OneIndex; ++i)
								{
									if (One[i] > Out[3])
									{
										for (int j = OneIndex; j > i; j--)
										{
											One[j] = One[j - 1];
										}
										OneIndex++;
										One[i] = Out[3];
										fg = true;
										break;
									}
								}
								if (!fg)
								{
									One[OneIndex] = Out[3];
									OneIndex++;
								}
							}
							else
							{

							}
						}
					}
					else if (UpperCard[4] == 2)
					{
						if (TwoIndex > 0 && Two[0] < 13)
						{
							Out[4] = 2;
							Out[3] = Two[0];
							TwoIndex++;
							for (int i = 0; i < TwoIndex; ++i)
							{
								Two[i] = Two[i + 1];
							}
							flag = true;
						}
						else
						{
							if (deckTwoIndex > 0)
							{
								for (int i = 0; i < deckTwoIndex; ++i)
								{
									if (deckTwo[i][1] > 3)
									{
										Out[3] = deckTwo[i][0];
										Out[4] = 2;
										flag = true;
										deckTwo[i][0]++;
										deckTwo[i][1]--;
										break;
									}
									else if (deckTwo[i][0]+deckTwo[i][1] - 1 > 12 && i == deckTwoIndex - 1 && (frontN < 5 || behindN < 5))
									{
										Out[3] = deckTwo[i][0];
										Out[4] = 2;
										flag = true;
										bool fg = false;
										for (int j = 0; j < TwoIndex; ++j)
										{
											if (Two[j] > Out[3])
											{
												for (int k = TwoIndex; k > j; --k)
												{
													Two[k + 1] = Two[k - 1];
												}
												fg = true;
												Two[j] = deckTwo[i][0] + 1;
												Two[j + 1] = deckTwo[i][0] + 2;
												TwoIndex += 2;
												break;
											}
										}
										if (!fg)
										{
											Two[TwoIndex] = deckTwo[i][0] + 1;
											Two[TwoIndex + 1] = deckTwo[i][0] + 2;
											TwoIndex += 2;
										}
									}
									else
									{

									}
								}
							}
						}
					}
					else
					{
						flag = true;
					}
				}		
				if (IsRes && flag)
				{
					if (temp < 10)
					{
						for (int i = temp; i < ThreeIndex; i++)
						{
							Three[i] = Three[i + 1];
						}
						ThreeIndex--;
					}
					else
					{
						temp -= 10;
						if (deckThree[temp][1] > 2)
						{
							deckThree[temp][1]--;
						}
						else
						{
							bool fg = false;
							for (int i = 0; i < ThreeIndex; ++i)
							{
								if (Three[i] > deckThree[temp][0])
								{
									for (int j = ThreeIndex; j > i; --j)
									{
										Three[j] = Three[j - 1];
									}
									Three[i] = deckThree[temp][0];
									ThreeIndex++;
									fg = true;
									break;
								}
							}
							if (!fg)
							{
								Three[ThreeIndex] = deckThree[temp][0];
								ThreeIndex++;
							}
							for (int i = temp; i < deckThreeIndex; ++i)
							{
								deckThree[i][1] = deckThree[i + 1][1];
								deckThree[i][0] = deckThree[i + 1][0];
							}
						}
					}
					return 1;
				}
				if (frontN < 4 || behindN < 4)
				{
					int boomtemp = -1;
					for (int i = 15; i > 2; i--)
					{
						if (elseCard[i] > 3)
						{
							boomtemp = i;
							break;
						}
					}
					if (boomtemp > 0 && FourIndex > 0)
					{
						Out[0] = Four[0];
						Out[1] = 4;
						Out[2] = 4;
						FourIndex--;
						for (int i = 0; i < FourIndex; ++i)
						{
							Four[i] = Four[i + 1];
						}
						return 1;
					}
					else if (KingBoom > 0 && OneIndex < 3)
					{
						Out[0] = 17;
						Out[1] = 2;
						Out[2] = 4;
						KingBoom = 0;
						return 1;
					}
					else if (FourIndex > 0)
					{
						Out[0] = Four[0];
						Out[1] = 4;
						Out[2] = 4;
						FourIndex--;
						for (int i = 0; i < FourIndex; ++i)
						{
							Four[i] = Four[i + 1];
						}
						return 1;
					}
				}
				return -1;
			}
			return -1;
		}
		else if (UpperCard[2] == 1)
		{
			for (int i = 0; i < deckIndex; ++i)
			{
				if (deck[i][0] > UpperCard[0] && deck[i][1] == UpperCard[1])
				{
					Out[0] = deck[i][0];
					Out[1] = deck[i][1];
					Out[2] = 1;
					deckIndex--;
					for (int j = i; j < deckIndex; ++j)
					{
						deck[j][0] = deck[j + 1][0];
						deck[j][1] = deck[j + 1][1];
					}
					return 1;
				}
			}
			for (int i = 0; i < deckIndex; ++i)
			{
				if (deck[i][0] > UpperCard[0] && deck[i][1] == UpperCard[1] + 1)
				{
					int restOne = deck[i][0] + deck[i][1] - 1;
					for (int k = OneIndex; k > 0; --k)
					{
						//One[k-1] == restOne
						if (One[k - 1] > restOne)
						{
							One[k] = One[k - 1];
						}
						else
						{
							One[k] = restOne;
							break;
						}
					}
					OneIndex++;
					Out[0] = deck[i][0];
					Out[1] = deck[i][1] - 1;
					Out[2] = 1;
					deckIndex--;
					for (int j = i; j < deckIndex; ++j)
					{
						deck[j][0] = deck[j + 1][0];
						deck[j][1] = deck[j + 1][1];
					}
					return 1;
				}
				else if(deck[i][0] == UpperCard[0] && deck[i][1] == UpperCard[1] + 1)
				{
					int restOne = deck[i][0];
					for (int k = OneIndex; k > 0; --k)
					{
						//One[k-1] == restOne
						if (One[k - 1] > restOne)
						{
							One[k] = One[k - 1];
						}
						else
						{
							One[k] = restOne;
							break;
						}
					}
					OneIndex++;
					Out[0] = deck[i][0] + 1;
					Out[1] = deck[i][1] - 1;
					Out[2] = 1;
					deckIndex--;
					for (int j = i; j < deckIndex; ++j)
					{
						deck[j][0] = deck[j + 1][0];
						deck[j][1] = deck[j + 1][1];
					}
					return 1;
				}
			}
			if (frontN < 4 || behindN < 4)
			{
				int boomtemp = -1;
				for (int i = 15; i > 2; i--)
				{
					if (elseCard[i] > 3)
					{
						boomtemp = i;
						break;
					}
				}
				if (boomtemp > 0 && FourIndex > 0)
				{
					Out[0] = Four[0];
					Out[1] = 4;
					Out[2] = 4;
					FourIndex--;
					for (int i = 0; i < FourIndex; ++i)
					{
						Four[i] = Four[i + 1];
					}
					return 1;
				}
				else if (KingBoom > 0 && OneIndex < 3)
				{
					Out[0] = 17;
					Out[1] = 2;
					Out[2] = 4;
					KingBoom = 0;
					return 1;
				}
				else if (FourIndex > 0)
				{
					Out[0] = Four[0];
					Out[1] = 4;
					Out[2] = 4;
					FourIndex--;
					for (int i = 0; i < FourIndex; ++i)
					{
						Four[i] = Four[i + 1];
					}
					return 1;
				}
			}
		}
		else if (UpperCard[2] == 2)
		{
			for (int i = 0; i < deckTwoIndex; ++i)
			{
				if (deckTwo[i][0] > UpperCard[0] && deckTwo[i][1] == UpperCard[1])
				{
					Out[0] = deckTwo[i][0];
					Out[1] = deckTwo[i][1];
					Out[2] = 2;
					deckTwoIndex--;
					for (int j = i; j < deckTwoIndex; ++j)
					{
						deckTwo[j][0] = deckTwo[j + 1][0];
						deckTwo[j][1] = deckTwo[j + 1][1];
					}
					return 1;
				}
			}
			for (int i = 0; i < deckTwoIndex; ++i)
			{
				if (deckTwo[i][0] > UpperCard[0] && deckTwo[i][1] == UpperCard[1] + 1)
				{
					int restTwo = deckTwo[i][0] + deckTwo[i][1] - 1;
					for (int k = TwoIndex; k > 0; --k)
					{
						//One[k-1] == restOne
						if (Two[k - 1] > restTwo)
						{
							Two[k] = Two[k - 1];
						}
						else
						{
							Two[k] = restTwo;
							break;
						}
					}
					TwoIndex++;
					Out[0] = deckTwo[i][0];
					Out[1] = deckTwo[i][1] - 1;
					Out[2] = 2;
					deckTwoIndex--;
					for (int j = i; j < deckTwoIndex; ++j)
					{
						deckTwo[j][0] = deckTwo[j + 1][0];
						deckTwo[j][1] = deckTwo[j + 1][1];
					}
					return 1;
				}
				else if (deckTwo[i][0] == UpperCard[0] && deckTwo[i][1] == UpperCard[1] + 1)
				{
					int restTwo = deckTwo[i][0];
					for (int k = TwoIndex; k > 0; --k)
					{
						//One[k-1] == restOne
						if (Two[k - 1] > restTwo)
						{
							Two[k] = Two[k - 1];
						}
						else
						{
							Two[k] = restTwo;
							break;
						}
					}
					TwoIndex++;
					Out[0] = deckTwo[i][0] + 1;
					Out[1] = deckTwo[i][1] - 1;
					Out[2] = 2;
					deckTwoIndex--;
					for (int j = i; j < deckTwoIndex; ++j)
					{
						deckTwo[j][0] = deckTwo[j + 1][0];
						deckTwo[j][1] = deckTwo[j + 1][1];
					}
					return 1;
				}
			}		
			if (frontN < 4 || behindN < 4)
			{
				int boomtemp = -1;
				for (int i = 15; i > 2; i--)
				{
					if (elseCard[i] > 3)
					{
						boomtemp = i;
						break;
					}
				}
				if (boomtemp > 0 && FourIndex > 0)
				{
					Out[0] = Four[0];
					Out[1] = 4;
					Out[2] = 4;
					FourIndex--;
					for (int i = 0; i < FourIndex; ++i)
					{
						Four[i] = Four[i + 1];
					}
					return 1;
				}
				else if (KingBoom > 0 && OneIndex < 3)
				{
					Out[0] = 17;
					Out[1] = 2;
					Out[2] = 4;
					KingBoom = 0;
					return 1;
				}
				else if (FourIndex > 0)
				{
					Out[0] = Four[0];
					Out[1] = 4;
					Out[2] = 4;
					FourIndex--;
					for (int i = 0; i < FourIndex; ++i)
					{
						Four[i] = Four[i + 1];
					}
					return 1;
				}
			}
			return -1;
		}
		else if (UpperCard[2] == 3)
		{
			bool IsRes = false;
			int chai = 0;
			int chaiThree;
			for (int i = 0; i < deckThreeIndex; ++i)
			{
				//δ���� �ҵĳ��� ����Ŀ������//��Ϊ�ǵ������ɻ�һ�ֳ��������Ѿ��ܶ��ˣ���ʱ���������Σ�������ѹֱ�Ӳ�
				if (UpperCard[0] < deckThree[i][0] && UpperCard[1] <= deckThree[i][1])
				{
					Out[0] = deckThree[i][0];
					Out[1] = deckThree[i][1];
					Out[2] = 3;
					deckThreeIndex--;
					if (deckThree[i][1] - UpperCard[1] >= 2)
					{
						chai = 1;
						deckThree[i][0] = deckThree[i][0] + UpperCard[1] - 1;
						deckThree[i][1] = deckThree[i][1] - UpperCard[1];
					}
					else
					{
						if (deckThree[i][1] - UpperCard[1] > 0)
						{
							chai = 2;
							for (int j = 0; j < ThreeIndex; j++)
							{
								if (Three[j] > Out[0])
								{
									for (int k = ThreeIndex; k > j; --k)
									{
										Three[k - 1 + deckThree[i][1] - UpperCard[1]] = Three[k - 1];
									}
									ThreeIndex += deckThree[i][1] - UpperCard[1];
									for (int k = 0; k < deckThree[i][1] - UpperCard[1]; ++k)
									{
										Three[j + k] = deckThree[i][0] + UpperCard[1] + k;
									}
									chaiThree = j;
									break;
								}
							}
						}
						for (int j = i; j < deckThreeIndex; ++j)
						{
							deckThree[j][0] = deckThree[j + 1][0];
							deckThree[j][1] = deckThree[j + 1][1];
						}
					}
					IsRes = true;
					break;
				}
			}
			if (IsRes == true)
			{
				if (UpperCard[4] == 2)//������
				{
					int temp = UpperCard[1];
					//���ţ����Գ�����UpperCard[1]
					if (TwoIndex >= UpperCard[1] && Two[UpperCard[1]] < 14)
					{
						Out[3] = Two[0];
						Out[4] = 2;
						for (int i = 1; i < temp; ++i)
						{
							Out[4 + i] = Two[i];
						}
						TwoIndex -= temp;
						for (int i = 0; i < TwoIndex; ++i)
						{
							Two[i] = Two[i + temp];
						}
						return 1;
					}
					else if (deckTwoIndex > 0)
					{
						for (int k = TwoIndex; k > 0; --k)
						{
							if (Two[k - 1] > deckTwo[0][0])
							{
								Two[k - 1 + deckTwo[0][1]] = Two[k - 1];
							}
							else
							{
								for (int j = 0; j < deckTwo[0][1]; j++)
								{
									Two[k + j] = deckTwo[0][0] + j;
								}
								break;
							}
						}
						TwoIndex += deckTwo[0][1];
						for (int i = 0; i < deckTwoIndex; ++i)
						{
							deckTwo[i][1] = deckTwo[i + 1][1];
							deckTwo[i][0] = deckTwo[i + 1][0];
						}
						deckTwoIndex--;
						Out[3] = Two[0];
						Out[4] = 2;
						for (int i = 1; i < Out[1]; i++)
						{
							Out[4 + i] = Two[i + 1];
						}
						for (int i = 0; i < TwoIndex; i++)
						{
							Two[i] = Two[i + Out[1]];
						}
						TwoIndex -= Out[1];
						return 1;
					}
					else
					{
						return -1;
					}
				}
				else if (UpperCard[4] == 1)
				{
					int temp = UpperCard[1];
					//
					if (OneIndex >= UpperCard[1] && One[UpperCard[1] - 1] < 16)
					{
						Out[3] = One[0];
						Out[4] = 2;
						for (int i = 1; i < temp; ++i)
						{
							Out[4 + i] = One[i];
						}
						OneIndex -= temp;
						for (int i = 0; i < OneIndex; ++i)
						{
							One[i] = One[i + temp];
						}
						return 1;
					}
					else
					{

					}
				}
			}	
			if (frontN < 4 || behindN < 4)
			{
				int boomtemp = -1;
				for (int i = 15; i > 2; i--)
				{
					if (elseCard[i] > 3)
					{
						boomtemp = i;
						break;
					}
				}
				if (boomtemp > 0 && FourIndex > 0)
				{
					Out[0] = Four[0];
					Out[1] = 4;
					Out[2] = 4;
					FourIndex--;
					for (int i = 0; i < FourIndex; ++i)
					{
						Four[i] = Four[i + 1];
					}
					return 1;
				}
				else if (KingBoom > 0 )
				{
					Out[0] = 17;
					Out[1] = 2;
					Out[2] = 4;
					KingBoom = 0;
					return 1;
				}
				else if (FourIndex > 0)
				{
					Out[0] = Four[0];
					Out[1] = 4;
					Out[2] = 4;
					FourIndex--;
					for (int i = 0; i < FourIndex; ++i)
					{
						Four[i] = Four[i + 1];
					}
					return 1;
				}
			}
			return -1;
		}
		else if (UpperCard[2] == 4)//  �Ĵ�2 //���Ż���Ŀǰֱ��ը//���Ĵ����ˣ�˵��ũ����̓�������߱�Ӯ�ˣ�����ֱ��ը��
		{
			if (UpperCard[0] == 17)
			{
				return -1;
			}
			bool boom = false;
			bool ok = false;
			bool BB = false;
			if (FourIndex > 0)
			{
				boom = true;
			}
			if (UpperCard[4] == 1 && boom == true)
			{
				if (OneIndex > 1 && One[1] < 14)
				{
					Out[3] = One[0];
					Out[4] = 1;
					Out[5] = One[1];
					for (int i = 0; i < OneIndex; i++)
					{
						One[i] = One[i + 2];
					}
					OneIndex -= 2;
					ok = true;
				}
				else if (OneIndex == 1 && One[0] < 14)
				{
					if (TwoIndex > 0 && Two[0] < 14)
					{
						if (One[0] > Two[0])
						{
							Out[3] = Two[0];
							Out[4] = 1;
							Out[5] = Two[0];
							TwoIndex--;
							for (int i = 0; i < TwoIndex; i++)
							{
								Two[i] = Two[i + 1];
							}
							ok = true;
						}
						else
						{
							Out[3] = One[0];
							Out[4] = 1;
							Out[5] = Two[0];
							One[0] = Two[0];
							TwoIndex--;
							for (int i = 0; i < TwoIndex; i++)
							{
								Two[i] = Two[i + 1];
							}
							ok = true;
						}
					}
				}
				else if (TwoIndex > 0 && Two[0] < 14)
				{
					Out[3] = Two[0];
					Out[4] = 1;
					Out[5] = Two[0];
					TwoIndex--;
					for (int i = 0; i < TwoIndex; i++)
					{
						Two[i] = Two[i + 1];
					}
					ok = true;
				}
				else
				{

				}
			}
			else if (UpperCard[4] == 2 && boom == true)
			{
				if (TwoIndex > 1 && Two[1] < 14)
				{
					Out[3] = Two[0];
					Out[4] = 2;
					Out[5] = Two[1];
					TwoIndex -= 2;
					for (int i = 0; i < TwoIndex; i++)
					{
						Two[i] = Two[i + 2];
					}
					ok = true;
				}
			}
			else
			{
				BB = true;
			}
			if (ok == true || (BB == true && KingBoom == 0))
			{
				for (int i = 0; i < FourIndex; i++)
				{
					if (Four[i] > UpperCard[0])
					{
						Out[0] = Four[i];
						Out[1] = 4;
						Out[2] = 4;
						FourIndex--;
						for (int j = i; j < FourIndex; ++j)
						{
							Four[j] = Four[j + 1];
						}
					}
				}
				return 1;
			}
			if (KingBoom == 1)
			{
				Out[0] = 17;
				Out[1] = 2;
				Out[2] = 4;
				Out[3] = 0;
				Out[4] = 0;
				Out[5] = 0;
				KingBoom = 0;
				return 1;
			}
			if (FourIndex > 0 && UpperCard[4] > 0)
			{
				for (int i = 0; i < FourIndex; i++)
				{

					Out[0] = Four[i];
					Out[1] = 4;
					Out[2] = 4;
					Out[3] = 0;
					Out[4] = 0;
					Out[5] = 0;
					FourIndex--;
					for (int j = i; j < FourIndex; j++)
					{
						Four[j] = Four[j + 1];
					}
					return 1;
				}
			}
			return -1;
		}
		else
		{
			return -1;
		}
	}
	//*******************ũ��*******************//
	else
	{
		// behindN == 1 && DZIndex == 1  ��ҵ�������
		//if (behindN == 1 && DZIndex == -1)//����ũ�񱨵����е���������
	//	cout << 1 << endl;
	//	cout << UpperCard[0] << " " << UpperCard[1] << " " << UpperCard[2] << endl;
		int MyRoundNum = GetRestRound();
		if (MyRoundNum == 1 && (FourIndex > 0 || KingBoom != 0))
		{
			if (KingBoom != 0)
			{
				Out[0] = 17;
				Out[1] = 2;
				Out[2] = 4;
				KingBoom = 0;
				return 1;
			}
			else if (FourIndex > 0)
			{
				Out[0] = Four[0];
				Out[1] = 4;
				Out[2] = 4;
				return 1;
			}
		}
		if (MyRoundNum == 2)
		{
			if (KingBoom == 1)
			{
				Out[0] = 17;
				Out[1] = 2;
				Out[2] = 4;
				KingBoom = 0;
				return 1;
			}
			if (UpperCard[1] == 4 && UpperCard[2] == 4 && UpperCard[4] == 0 && FourIndex > 0)
			{
				if (Four[FourIndex - 1] > UpperCard[0])
				{
					Out[0] = Four[FourIndex - 1];
					Out[1] = 4;
					Out[2] = 4;
					FourIndex--;
					for (int i = 0; i < FourIndex; ++i)
					{
						Four[i] = Four[i + 1];
					}
					return 1;
				}
			}
			else if (FourIndex > 0)
			{
				Out[0] = Four[0];
				Out[1] = 4;
				Out[2] = 4;
				FourIndex--;
				for (int i = 0; i < FourIndex; ++i)
				{
					Four[i] = Four[i + 1];
				}
				return 1;
			}
		}
		if ((behindN == 1 && DZIndex == -1) || (frontN == 1 && DZIndex == 2 && behindN > 1))
		{
			if (WhoseOut == 1)
			{
				return -1;
			}
			//�������
			if (UpperCard[2] == 0)
			{
				if (UpperCard[1] == 1)
				{
					if (OneIndex > 0 && One[OneIndex - 1] > UpperCard[0])
					{
						Out[0] = One[OneIndex - 1];
						Out[1] = 1;
						Out[2] = 0;
						OneIndex--;
						return 1;
					}
					else if (FourIndex > 0)
					{
						bool IsMaxBoom = true;
						int temp = Four[FourIndex - 1];
						for (int i = temp + 1; i < 16; ++i)
						{
							if (elseCard[i] == 4)
							{
								IsMaxBoom = false;
								break;
							}
						}
						if (IsMaxBoom)
						{
							if (UpperCard[2] == 4 && UpperCard[0] > temp)
							{
								return -1;
							}
							Out[0] = temp;
							Out[1] = 4;
							Out[2] = 4;
							FourIndex--;
							return 1;
						}
						else
						{
							//��ը
						}
					}
					else if (TwoIndex > 0 && Two[TwoIndex - 1] > UpperCard[0])
					{
						Out[0] = Two[TwoIndex - 1];
						Out[1] = 1;
						Out[2] = 0;
						TwoIndex--;
						return 1;
					}
					else if (ThreeIndex > 0 && Three[ThreeIndex - 1] > UpperCard[0])
					{
						Out[0] = Three[ThreeIndex - 1];
						Out[1] = 1;
						Out[2] = 0;
						ThreeIndex--;
						return 1;
					}
					else if (deck[0][0] + deck[0][1] - 1 > UpperCard[0] && deck[0][1] > 5)
					{
						Out[0] = deck[0][0] + deck[0][1] - 1;
						Out[1] = 1;
						Out[2] = 0;
						deck[0][1]--;
						return 1;
					}

				}
				else if (UpperCard[1] == 2)
				{
					for (int i = 15; i > 3; i--)
					{
						if (i > UpperCard[0] &&  myCard[i] > 1 && myCard[i] < 4)
						{
							Out[0] = i;
							Out[1] = 2;
							Out[2] = 0;
							return 1;
						}
					}
				}
				else//UpperCard[3] ==3
				{
					bool IsRes = false;
					bool flag = false;
					int temp = 0;
					for (int i = ThreeIndex - 1; i >= 0; --i)
					{
						if (Three[i] > UpperCard[0])
						{
							Out[0] = Three[i];
							Out[1] = 3;
							Out[2] = 0;
							temp = i;
							IsRes = true;
							break;
						}
					}
					//�ɻ����
					if (IsRes == false)
					{
						for (int i = deckThreeIndex - 1; i >= 0; --i)
						{
							if (deckThree[i][0] + deckThree[i][1] - 1 > UpperCard[0])
							{
								Out[0] = deckThree[i][0] + deckThree[i][1] - 1;
								Out[1] = 3;
								Out[2] = 0;
								temp = 10 + i;
								IsRes = true;
								break;
							}
						}
					}
					//************���� 0,1,2
					if (IsRes == true)
					{
						if (UpperCard[4] == 1)
						{
							if (OneIndex > 0 && One[0] < 13)
							{
								Out[4] = 1;
								Out[3] = One[0];
								OneIndex++;
								for (int i = 0; i < OneIndex; ++i)
								{
									One[i] = One[i + 1];
								}
								flag = true;
							}
							else//�ص��Ż�//˼���Ƿ�һ��Ҫѹ������ӻ��ǲ�˳�ӻ��ǲ����������������//������˳�ӣ���������
							{
								if (WhoseOut == -1 && frontN < 5)
								{
									int boomtemp = -1;
									for (int i = 15; i > 2; i--)
									{
										if (elseCard[i] > 3)
										{
											boomtemp = i;
											break;
										}
									}
									if (boomtemp > 0 && FourIndex > 0)
									{
										Out[0] = Four[0];
										Out[1] = 4;
										Out[2] = 4;
										Out[4] = 0;
										Out[3] = 0;
										FourIndex--;
										for (int i = 0; i < FourIndex; ++i)
										{
											Four[i] = Four[i + 1];
										}
										return 1;
									}
									else if (KingBoom > 0 && OneIndex < 3)
									{
										Out[0] = 17;
										Out[1] = 2;
										Out[2] = 4;
										KingBoom = 0;
										return 1;
									}
									else if (FourIndex > 0)
									{
										Out[0] = Four[0];
										Out[1] = 4;
										Out[2] = 4;
										Out[4] = 0;
										Out[3] = 0;
										FourIndex--;
										for (int i = 0; i < FourIndex; ++i)
										{
											Four[i] = Four[i + 1];
										}
										return 1;
									}
									else
									{
										if (deckIndex > 0)
										{
											for (int i = 0; i < deckIndex; ++i)
											{
												if (deck[i][1] > 5)
												{
													Out[3] = deck[i][0];
													Out[4] = 1;
													deck[i][0]++;
													deck[i][1]--;
													flag = true;
													break;
												}
											}
										}
										else if (TwoIndex > 1)
										{
											Out[3] = Two[TwoIndex - 2];
											Out[4] = 1;
											Two[TwoIndex - 2] = Two[TwoIndex - 1];
											bool fg = false;
											flag = true;
											for (int i = 0; i < OneIndex; ++i)
											{
												if (One[i] > Out[3])
												{
													for (int j = OneIndex; j > i; j--)
													{
														One[j] = One[j - 1];
													}
													OneIndex++;
													One[i] = Out[3];
													fg = true;
													break;
												}
											}
											if (!fg)
											{
												One[OneIndex] = Out[3];
												OneIndex++;
											}
										}
										else if (TwoIndex == 1)
										{
											Out[3] = Two[TwoIndex - 1];
											Out[4] = 1;
											TwoIndex--;
											bool fg = false;
											flag = true;
											for (int i = 0; i < OneIndex; ++i)
											{
												if (One[i] > Out[3])
												{
													for (int j = OneIndex; j > i; j--)
													{
														One[j] = One[j - 1];
													}
													OneIndex++;
													One[i] = Out[3];
													fg = true;
													break;
												}
											}
											if (!fg)
											{
												One[OneIndex] = Out[3];
												OneIndex++;
											}
										}
										else if (ThreeIndex > 1 && ThreeIndex - 2 != temp)
										{
											Out[3] = Three[ThreeIndex - 2];
											Out[4] = 1;
											Three[ThreeIndex - 2] = Three[ThreeIndex - 1];
											ThreeIndex--;
											flag = true;
											bool fg = false;
											for (int i = 0; i < TwoIndex; ++i)
											{
												if (Two[i] > Out[3])
												{
													for (int j = TwoIndex; j > i; j--)
													{
														Two[j] = Two[j - 1];
													}
													Two[i] = Out[3];
													TwoIndex++;
													fg = true;
													break;
												}
											}
											if (!fg)
											{
												Two[TwoIndex] = Out[3];
												TwoIndex++;
											}
										}
										else if ((ThreeIndex == 1 && Three[0] < 15 && ThreeIndex != temp) || (ThreeIndex > 1 && ThreeIndex - 2 != temp))
										{
											Out[3] = Three[ThreeIndex - 1];
											Out[4] = 1;
											ThreeIndex--;
											flag = true;
											bool fg = false;
											for (int i = 0; i < TwoIndex; ++i)
											{
												if (Two[i] > Out[3])
												{
													for (int j = TwoIndex; j > i; j--)
													{
														Two[j] = Two[j - 1];
													}
													Two[i] = Out[3];
													TwoIndex++;
													fg = true;
													break;
												}
											}
											if (!fg)
											{
												Two[TwoIndex] = Out[3];
												TwoIndex++;
											}
										}
										else
										{

										}
									}
								}
								else if (WhoseOut == 1)
								{
									return -1;
								}
								else if (OneIndex > 0 && One[0] < 15)
								{
									Out[4] = 1;
									Out[3] = One[0];
									OneIndex++;
									for (int i = 0; i < OneIndex; ++i)
									{
										One[i] = One[i + 1];
									}
									flag = true;
								}
								else if (deckIndex > 0)
								{
									for (int i = 0; i < deckIndex; ++i)
									{
										if (deck[i][1] > 5)
										{
											Out[3] = deck[i][0];
											Out[4] = 1;
											deck[i][0]++;
											deck[i][1]--;
											flag = true;
											break;
										}
									}
								}
								else if (TwoIndex > 1)
								{
									Out[3] = Two[TwoIndex - 2];
									Out[4] = 1;
									Two[TwoIndex - 2] = Two[TwoIndex - 1];
									bool fg = false;
									flag = true;
									for (int i = 0; i < OneIndex; ++i)
									{
										if (One[i] > Out[3])
										{
											for (int j = OneIndex; j > i; j--)
											{
												One[j] = One[j - 1];
											}
											OneIndex++;
											One[i] = Out[3];
											fg = true;
											break;
										}
									}
									if (!fg)
									{
										One[OneIndex] = Out[3];
										OneIndex++;
									}
								}
								else if (TwoIndex == 1)
								{
									Out[3] = Two[TwoIndex - 1];
									Out[4] = 1;
									TwoIndex--;
									bool fg = false;
									flag = true;
									for (int i = 0; i < OneIndex; ++i)
									{
										if (One[i] > Out[3])
										{
											for (int j = OneIndex; j > i; j--)
											{
												One[j] = One[j - 1];
											}
											OneIndex++;
											One[i] = Out[3];
											fg = true;
											break;
										}
									}
									if (!fg)
									{
										One[OneIndex] = Out[3];
										OneIndex++;
									}
								}
								else
								{

								}
							}
						}
						else if (UpperCard[4] == 2)
						{
							if (TwoIndex > 0 && (Two[0] < 13 || behindN < 6))
							{
								Out[4] = 2;
								Out[3] = Two[0];
								TwoIndex++;
								for (int i = 0; i < TwoIndex; ++i)
								{
									Two[i] = Two[i + 1];
								}
								flag = true;
							}
							else
							{
								if (WhoseOut == -1 && behindN < 5)
								{
									int boomtemp = -1;
									for (int i = 15; i > 2; i--)
									{
										if (elseCard[i] > 3)
										{
											boomtemp = i;
											break;
										}
									}
									if (boomtemp > 0 && FourIndex > 0)
									{
										Out[0] = Four[0];
										Out[1] = 4;
										Out[2] = 4;
										Out[4] = 0;
										Out[3] = 0;
										FourIndex--;
										for (int i = 0; i < FourIndex; ++i)
										{
											Four[i] = Four[i + 1];
										}
										return 1;
									}
									else if (KingBoom > 0 && OneIndex < 3)
									{
										Out[0] = 17;
										Out[1] = 2;
										Out[2] = 4;
										KingBoom = 0;
										return 1;
									}
									else if (FourIndex > 0)
									{
										Out[0] = Four[0];
										Out[1] = 4;
										Out[2] = 4;
										Out[4] = 0;
										Out[3] = 0;
										FourIndex--;
										for (int i = 0; i < FourIndex; ++i)
										{
											Four[i] = Four[i + 1];
										}
										return 1;
									}
									else
									{
										if (deckIndex > 0)
										{
											for (int i = 0; i < deckIndex; ++i)
											{
												if (deck[i][1] > 5)
												{
													Out[3] = deck[i][0];
													Out[4] = 1;
													deck[i][0]++;
													deck[i][1]--;
													flag = true;
													break;
												}
											}
										}
										else if (TwoIndex > 1)
										{
											Out[3] = Two[TwoIndex - 2];
											Out[4] = 1;
											Two[TwoIndex - 2] = Two[TwoIndex - 1];
											bool fg = false;
											flag = true;
											for (int i = 0; i < OneIndex; ++i)
											{
												if (One[i] > Out[3])
												{
													for (int j = OneIndex; j > i; j--)
													{
														One[j] = One[j - 1];
													}
													OneIndex++;
													One[i] = Out[3];
													fg = true;
													break;
												}
											}
											if (!fg)
											{
												One[OneIndex] = Out[3];
												OneIndex++;
											}
										}
										else if (TwoIndex == 1)
										{
											Out[3] = Two[TwoIndex - 1];
											Out[4] = 1;
											TwoIndex--;
											bool fg = false;
											flag = true;
											for (int i = 0; i < OneIndex; ++i)
											{
												if (One[i] > Out[3])
												{
													for (int j = OneIndex; j > i; j--)
													{
														One[j] = One[j - 1];
													}
													OneIndex++;
													One[i] = Out[3];
													fg = true;
													break;
												}
											}
											if (!fg)
											{
												One[OneIndex] = Out[3];
												OneIndex++;
											}
										}
										else if (ThreeIndex > 1 && ThreeIndex - 2 != temp)
										{
											Out[3] = Three[ThreeIndex - 2];
											Out[4] = 1;
											Three[ThreeIndex - 2] = Three[ThreeIndex - 1];
											ThreeIndex--;
											flag = true;
											bool fg = false;
											for (int i = 0; i < TwoIndex; ++i)
											{
												if (Two[i] > Out[3])
												{
													for (int j = TwoIndex; j > i; j--)
													{
														Two[j] = Two[j - 1];
													}
													Two[i] = Out[3];
													TwoIndex++;
													fg = true;
													break;
												}
											}
											if (!fg)
											{
												Two[TwoIndex] = Out[3];
												TwoIndex++;
											}
										}
										else if ((ThreeIndex == 1 && Three[0] < 15 && ThreeIndex != temp) || (ThreeIndex > 1 && ThreeIndex - 2 != temp))
										{
											Out[3] = Three[ThreeIndex - 1];
											Out[4] = 1;
											ThreeIndex--;
											flag = true;
											bool fg = false;
											for (int i = 0; i < TwoIndex; ++i)
											{
												if (Two[i] > Out[3])
												{
													for (int j = TwoIndex; j > i; j--)
													{
														Two[j] = Two[j - 1];
													}
													Two[i] = Out[3];
													TwoIndex++;
													fg = true;
													break;
												}
											}
											if (!fg)
											{
												Two[TwoIndex] = Out[3];
												TwoIndex++;
											}
										}
										else
										{

										}
									}
								}
								else if (WhoseOut == 1)
								{
									return -1;
								}
								else if (deckTwoIndex > 0)
								{
									for (int i = 0; i < deckTwoIndex; ++i)
									{
										if (deckTwo[i][1] > 3)
										{
											Out[3] = deckTwo[i][0];
											Out[4] = 2;
											flag = true;
											deckTwo[i][0]++;
											deckTwo[i][1]--;
											break;
										}
										else if (deckTwo[i][0]+ deckTwo[i][1] - 1 > 12 && i == deckTwoIndex - 1 && (frontN < 5 || behindN < 5))
										{
											Out[3] = deckTwo[i][0];
											Out[4] = 2;
											flag = true;
											bool fg = false;
											for (int j = 0; j < TwoIndex; ++j)
											{
												if (Two[j] > Out[3])
												{
													for (int k = TwoIndex; k > j; --k)
													{
														Two[k + 1] = Two[k - 1];
													}
													fg = true;
													Two[j] = deckTwo[i][0] + 1;
													Two[j + 1] = deckTwo[i][0] + 2;
													TwoIndex += 2;
													break;
												}
											}
											if (!fg)
											{
												Two[TwoIndex] = deckTwo[i][0] + 1;
												Two[TwoIndex + 1] = deckTwo[i][0] + 2;
												TwoIndex += 2;
											}
										}
										else
										{

										}
									}
								}
							}
						}
						else
						{
							flag = true;
						}
					}
					if (IsRes && flag)
					{
						if (temp < 10)
						{
							for (int i = temp; i < ThreeIndex; i++)
							{
								Three[i] = Three[i + 1];
							}
							ThreeIndex--;
						}
						else
						{
							temp -= 10;
							if (deckThree[temp][1] > 2)
							{
								deckThree[temp][1]--;
							}
							else
							{
								bool fg = false;
								for (int i = 0; i < ThreeIndex; ++i)
								{
									if (Three[i] > deckThree[temp][0])
									{
										for (int j = ThreeIndex; j > i; --j)
										{
											Three[j] = Three[j - 1];
										}
										Three[i] = deckThree[temp][0];
										ThreeIndex++;
										fg = true;
										break;
									}
								}
								if (!fg)
								{
									Three[ThreeIndex] = deckThree[temp][0];
									ThreeIndex++;
								}
								for (int i = temp; i < deckThreeIndex; ++i)
								{
									deckThree[i][1] = deckThree[i + 1][1];
									deckThree[i][0] = deckThree[i + 1][0];
								}
							}
						}
						return 1;
					}
				}
			}
			else if (UpperCard[2] == 1)
			{
				for (int i = 0; i < deckIndex; ++i)
				{
					if (deck[i][0] > UpperCard[0] && deck[i][1] == UpperCard[1])
					{
						Out[0] = deck[i][0];
						Out[1] = deck[i][1];
						Out[2] = 1;
						deckIndex--;
						for (int j = i; j < deckIndex; ++j)
						{
							deck[j][0] = deck[j + 1][0];
							deck[j][1] = deck[j + 1][1];
						}
						return 1;
					}
				}
				for (int i = 0; i < deckIndex; ++i)
				{
					if (deck[i][0] > UpperCard[0] && deck[i][1] == UpperCard[1] + 1)
					{
						int restOne = deck[i][0] + deck[i][1] - 1;
						for (int k = OneIndex; k > 0; --k)
						{
							//One[k-1] == restOne
							if (One[k - 1] > restOne)
							{
								One[k] = One[k - 1];
							}
							else
							{
								One[k] = restOne;
								break;
							}
						}
						OneIndex++;
						Out[0] = deck[i][0];
						Out[1] = deck[i][1] - 1;
						Out[2] = 1;
						deckIndex--;
						for (int j = i; j < deckIndex; ++j)
						{
							deck[j][0] = deck[j + 1][0];
							deck[j][1] = deck[j + 1][1];
						}
						return 1;
					}
					else if (deck[i][0] == UpperCard[0] && deck[i][1] == UpperCard[1] + 1)
					{
						int restOne = deck[i][0];
						for (int k = OneIndex; k > 0; --k)
						{
							//One[k-1] == restOne
							if (One[k - 1] > restOne)
							{
								One[k] = One[k - 1];
							}
							else
							{
								One[k] = restOne;
								break;
							}
						}
						OneIndex++;
						Out[0] = deck[i][0] + 1;
						Out[1] = deck[i][1] - 1;
						Out[2] = 1;
						deckIndex--;
						for (int j = i; j < deckIndex; ++j)
						{
							deck[j][0] = deck[j + 1][0];
							deck[j][1] = deck[j + 1][1];
						}
						return 1;
					}
				}
			}
			else if (UpperCard[2] == 2)
			{
				for (int i = 0; i < deckTwoIndex; ++i)
				{
					if (deckTwo[i][0] > UpperCard[0] && deckTwo[i][1] == UpperCard[1])
					{
						Out[0] = deckTwo[i][0];
						Out[1] = deckTwo[i][1];
						Out[2] = 2;
						deckTwoIndex--;
						for (int j = i; j < deckTwoIndex; ++j)
						{
							deckTwo[j][0] = deckTwo[j + 1][0];
							deckTwo[j][1] = deckTwo[j + 1][1];
						}
						return 1;
					}
				}
				for (int i = 0; i < deckTwoIndex; ++i)
				{
					if (deckTwo[i][0] > UpperCard[0] && deckTwo[i][1] == UpperCard[1] + 1)
					{
						int restTwo = deckTwo[i][0] + deckTwo[i][1] - 1;
						for (int k = TwoIndex; k > 0; --k)
						{
							//One[k-1] == restOne
							if (Two[k - 1] > restTwo)
							{
								Two[k] = Two[k - 1];
							}
							else
							{
								Two[k] = restTwo;
								break;
							}
						}
						TwoIndex++;
						Out[0] = deckTwo[i][0];
						Out[1] = deckTwo[i][1] - 1;
						Out[2] = 2;
						deckTwoIndex--;
						for (int j = i; j < deckTwoIndex; ++j)
						{
							deckTwo[j][0] = deckTwo[j + 1][0];
							deckTwo[j][1] = deckTwo[j + 1][1];
						}
						return 1;
					}
					else if (deckTwo[i][0] == UpperCard[0] && deckTwo[i][1] == UpperCard[1] + 1)
					{
						int restTwo = deckTwo[i][0];
						for (int k = TwoIndex; k > 0; --k)
						{
							//One[k-1] == restOne
							if (Two[k - 1] > restTwo)
							{
								Two[k] = Two[k - 1];
							}
							else
							{
								Two[k] = restTwo;
								break;
							}
						}
						TwoIndex++;
						Out[0] = deckTwo[i][0] + 1;
						Out[1] = deckTwo[i][1] - 1;
						Out[2] = 2;
						deckTwoIndex--;
						for (int j = i; j < deckTwoIndex; ++j)
						{
							deckTwo[j][0] = deckTwo[j + 1][0];
							deckTwo[j][1] = deckTwo[j + 1][1];
						}
						return 1;
					}
				}
			}
			else if (UpperCard[2] == 3)
			{
				if (WhoseOut == 1 && ((DZIndex == -1) || (DZIndex == 2 && (behindN > 8 || UpperCard[0] > 9 || UpperCard[1] > 2))))
				{
					return -1;
				}
				bool IsRes = false;
				int chai = 0;
				int chaiThree;
				for (int i = 0; i < deckThreeIndex; ++i)
				{
					if (UpperCard[0] < deckThree[i][0] && UpperCard[1] <= deckThree[i][1])
					{
						Out[0] = deckThree[i][0];
						Out[1] = UpperCard[1];
						Out[2] = 3;
						deckThreeIndex--;
						if (deckThree[i][1] - UpperCard[1] >= 2)
						{
							chai = 1;
							deckThree[i][0] = deckThree[i][0] + UpperCard[1] - 1;
							deckThree[i][1] = deckThree[i][1] - UpperCard[1];
						}
						else
						{
							if (deckThree[i][1] - UpperCard[1] > 0)
							{
								chai = 2;
								for (int j = 0; j < ThreeIndex; j++)
								{
									if (Three[j] > Out[0])
									{
										for (int k = ThreeIndex; k > j; --k)
										{
											Three[k - 1 + deckThree[i][1] - UpperCard[1]] = Three[k - 1];
										}
										ThreeIndex += deckThree[i][1] - UpperCard[1];
										for (int k = 0; k < deckThree[i][1] - UpperCard[1]; ++k)
										{
											Three[j + k] = deckThree[i][0] + UpperCard[1] + k;
										}
										chaiThree = j;
										break;
									}
								}
							}
							for (int j = i; j < deckThreeIndex; ++j)
							{
								deckThree[j][0] = deckThree[j + 1][0];
								deckThree[j][1] = deckThree[j + 1][1];
							}
						}
						IsRes = true;
						break;
					}
				}
				if (IsRes == true)
				{
					if (UpperCard[4] == 2)//������
					{
						int temp = UpperCard[1];
						//���ţ����Գ�����UpperCard[1]
						if (TwoIndex >= UpperCard[1] && Two[UpperCard[1]] < 14)
						{
							Out[3] = Two[0];
							Out[4] = 2;
							for (int i = 1; i < temp; ++i)
							{
								Out[4 + i] = Two[i];
							}
							TwoIndex -= temp;
							for (int i = 0; i < TwoIndex; ++i)
							{
								Two[i] = Two[i + temp];
							}
							return 1;
						}
						else if (deckTwoIndex > 0)
						{
							for (int k = TwoIndex; k > 0; --k)
							{
								if (Two[k - 1] > deckTwo[0][0])
								{
									Two[k - 1 + deckTwo[0][1]] = Two[k - 1];
								}
								else
								{
									for (int j = 0; j < deckTwo[0][1]; j++)
									{
										Two[k + j] = deckTwo[0][0] + j;
									}
									break;
								}
							}
							TwoIndex += deckTwo[0][1];
							for (int i = 0; i < deckTwoIndex; ++i)
							{
								deckTwo[i][1] = deckTwo[i + 1][1];
								deckTwo[i][0] = deckTwo[i + 1][0];
							}
							deckTwoIndex--;
							Out[3] = Two[0];
							Out[4] = 2;
							for (int i = 1; i < Out[1]; i++)
							{
								Out[4 + i] = Two[i + 1];
							}
							for (int i = 0; i < TwoIndex; i++)
							{
								Two[i] = Two[i + Out[1]];
							}
							TwoIndex -= Out[1];
							return 1;
						}
						else
						{
							return -1;
						}
					}
					else if (UpperCard[4] == 1)
					{
						int temp = UpperCard[1];
						//
						if (OneIndex >= UpperCard[1] && One[UpperCard[1] - 1] < 16)
						{
							Out[3] = One[0];
							Out[4] = 1;
							for (int i = 1; i < temp; ++i)
							{
								Out[4 + i] = One[i];
							}
							OneIndex -= temp;
							for (int i = 0; i < OneIndex; ++i)
							{
								One[i] = One[i + temp];
							}
							return 1;
						}
						else
						{

						}
					}
				}
				if (DZIndex == 2 && behindN < 5)
				{
					int boomtemp = -1;
					for (int i = 15; i > 2; i--)
					{
						if (elseCard[i] > 3)
						{
							boomtemp = i;
							break;
						}
					}
					if (boomtemp > 0 && FourIndex > 0)
					{
						Out[0] = Four[0];
						Out[1] = 4;
						Out[2] = 4;
						FourIndex--;
						for (int i = 0; i < FourIndex; ++i)
						{
							Four[i] = Four[i + 1];
						}
						return 1;
					}
					else if (KingBoom > 0 && OneIndex < 3)
					{
						Out[0] = 17;
						Out[1] = 2;
						Out[2] = 4;
						KingBoom = 0;
						return 1;
					}
					else if (FourIndex > 0)
					{
						Out[0] = Four[0];
						Out[1] = 4;
						Out[2] = 4;
						FourIndex--;
						for (int i = 0; i < FourIndex; ++i)
						{
							Four[i] = Four[i + 1];
						}
						return 1;
					}
				}

			}
			else if (UpperCard[2] == 4)//  �Ĵ�2 //���Ż���Ŀǰֱ��ը//���Ĵ����ˣ�˵��ũ����̓�������߱�Ӯ�ˣ�����ֱ��ը��
			{
				if (UpperCard[0] == 17 || WhoseOut == 1)
				{
					return -1;
				}
				bool boom = false;
				bool ok = false;
				if (FourIndex > 0)
				{
					boom = true;
				}
				if (UpperCard[4] == 1 && boom == true)
				{
					if (OneIndex > 1 && One[1] < 14)
					{
						Out[3] = One[0];
						Out[4] = 1;
						Out[5] = One[1];
						for (int i = 0; i < OneIndex; i++)
						{
							One[i] = One[i + 2];
						}
						OneIndex -= 2;
						ok = true;
					}
					else if (OneIndex == 1 && One[0] < 14)
					{
						if (TwoIndex > 0 && Two[0] < 14)
						{
							if (One[0] > Two[0])
							{
								Out[3] = Two[0];
								Out[4] = 1;
								Out[5] = Two[0];
								TwoIndex--;
								for (int i = 0; i < TwoIndex; i++)
								{
									Two[i] = Two[i + 1];
								}
								ok = true;
							}
							else
							{
								Out[3] = One[0];
								Out[4] = 1;
								Out[5] = Two[0];
								One[0] = Two[0];
								TwoIndex--;
								for (int i = 0; i < TwoIndex; i++)
								{
									Two[i] = Two[i + 1];
								}
								ok = true;
							}
						}
					}
					else if (TwoIndex > 0 && Two[0] < 14)
					{
						Out[3] = Two[0];
						Out[4] = 1;
						Out[5] = Two[0];
						TwoIndex--;
						for (int i = 0; i < TwoIndex; i++)
						{
							Two[i] = Two[i + 1];
						}
						ok = true;
					}
					else
					{

					}
				}
				else if (UpperCard[4] == 2 && boom == true)
				{
					if (TwoIndex > 1 && Two[1] < 14)
					{
						Out[3] = Two[0];
						Out[4] = 2;
						Out[5] = Two[1];
						TwoIndex -= 2;
						for (int i = 0; i < TwoIndex; i++)
						{
							Two[i] = Two[i + 2];
						}
						ok = true;
					}
				}
				if (ok == true)
				{
					for (int i = 0; i < FourIndex; i++)
					{
						if (Four[i] > UpperCard[0])
						{
							Out[0] = Four[i];
							Out[1] = 4;
							Out[2] = 4;
							FourIndex--;
							for (int j = i; j < FourIndex; ++j)
							{
								Four[j] = Four[j + 1];
							}
						}
					}
					return 1;
				}
				if (KingBoom == 1)
				{
					Out[0] = 17;
					Out[1] = 2;
					Out[2] = 4;
					Out[3] = 0;
					Out[4] = 0;
					Out[5] = 0;
					KingBoom = 0;
					return 1;
				}
				if (FourIndex > 0)
				{
					for (int i = 0; i < FourIndex; i++)
					{

						Out[0] = Four[i];
						Out[1] = 4;
						Out[2] = 4;
						Out[3] = 0;
						Out[4] = 0;
						Out[5] = 0;
						FourIndex--;
						for (int j = i; j < FourIndex; j++)
						{
							Four[j] = Four[j + 1];
						}
						return 1;
					}
				}
				return -1;
			}
			else
			{
				return -1;
			}
			if (KingBoom == 1)
			{
				Out[0] = 17;
				Out[1] = 2;
				Out[2] = 4;
				KingBoom = 0;
				return 1;
			}
			if (FourIndex > 0)
			{
				bool IsMaxBoom = true;
				int temp = Four[FourIndex - 1];
				for (int i = temp + 1; i < 16; ++i)
				{
					if (elseCard[i] == 4)
					{
						IsMaxBoom = false;
						break;
					}
				}
				if (IsMaxBoom)
				{
					if (UpperCard[2] == 4 && UpperCard[0] > temp)
					{
						return -1;
					}
					Out[0] = temp;
					Out[1] = 4;
					Out[2] = 4;
					FourIndex--;
					return 1;
				}
				else
				{
					//��ը
				}
			}
			return -1;
		}
		//----------------------��������
		else if ((frontN == 1 && DZIndex == -1) || (DZIndex == 2 && behindN == 1))//�����ϼ�
		{
			int dzMaxOne = OneElseMax;
			if (WhoseOut == 1 && (UpperCard[2] > 0 || UpperCard[1] > 1 || (UpperCard[0] >= dzMaxOne) || DZIndex == -1))
			{
				return -1;
			}
			//����
			int UnSafeNum = 0;
			for (int i = 0; i < OneIndex; ++i)
			{
				if (One[i] < dzMaxOne)
				{
					UnSafeNum++;
				}
			}
			UnSafeNum -= ThreeIndex;
			int BigThanDZ = 0;
			for (int i = 0; i < deckThreeIndex; ++i)
			{
				UnSafeNum -= deckThree[i][1];
			}
			if (KingBoom == 1)
			{
				Out[0] = 17;
				Out[1] = 2;
				Out[2] = 4;
				KingBoom = 0;
				return 1;
			}
			else if (FourIndex > 0 && (UnSafeNum < 2))//�Ż�
			{
				Out[0] = Four[0];
				Out[1] = 4;
				Out[2] = 4;
				FourIndex--;
				for (int i = 0; i < FourIndex; ++i)
				{
					Four[i] = Four[i + 1];
				}
				return 1;
			}
			//if (WhoseOut == -1)
			{
				//�ؽ�  �������ĵ���
				if (UpperCard[2] == 0 && UpperCard[1] == 1)
				{
					if (UpperCard[0] >= dzMaxOne)
					{
						dzMaxOne = UpperCard[0] + 1;
					}
					if (OneIndex > 0 && One[OneIndex - 1] >= dzMaxOne)
					{
						Out[0] = One[OneIndex - 1];
						Out[1] = 1;
						Out[2] = 0;
						OneIndex--;
						return 1;
					}
					if (TwoIndex > 0 && Two[TwoIndex - 1] >= dzMaxOne)
					{
						Out[0] = Two[TwoIndex - 1];
						Out[1] = 1;
						Out[2] = 0;
						One[OneIndex] = Two[TwoIndex - 1];
						OneIndex++;
						TwoIndex--;
						return 1;
					}
					if (deckIndex > 0)
					{
						for (int i = 0; i < deckIndex; ++i)
						{
							if (deck[i][1] > 5 && deck[i][0] + deck[i][1] - 1 >= dzMaxOne)
							{
								Out[0] = deck[i][0] + deck[i][1] - 1;
								Out[1] = 1;
								Out[2] = 0;
								deck[i][1]--;
								return 1;
							}
						}
					}
					if (ThreeIndex > 0 && Two[TwoIndex - 1] >= dzMaxOne)
					{
						Out[0] = Three[ThreeIndex - 1];
						Out[1] = 1;
						Out[2] = 0;
						Two[TwoIndex] = Three[ThreeIndex - 1];
						TwoIndex++;
						ThreeIndex--;
						return 1;
					}
					//else ����else��ϵ  one�п���û�������� //����
					if (OneIndex > 0 && One[OneIndex - 1] > UpperCard[0])
					{
						OneIndex--;
						Out[0] = One[OneIndex];
						Out[1] = 1;
						Out[2] = 0;
						return 1;
					}	
				}
				else//����
				{
					if (UpperCard[2] == 0)
					{
						
						if (deckThreeIndex > 0)//�ѷɻ����ˣ�������ѹ����
						{
							for (int i = 0; i < deckThreeIndex; ++i)
							{
								bool flag = false;
								for (int j = 0; j < ThreeIndex; j++)
								{
									if (Three[j] > deckThree[i][0])
									{
										flag = true;
										for (int k = ThreeIndex; k > j; --k)
										{
											Three[k - 1 + deckThree[i][1]] = Three[k - 1];
										}
										ThreeIndex += deckThree[i][0];
										for (int k = 0; k < deckThree[i][1]; ++k)
										{
											Three[j + k] = deckThree[i][0] + k;
										}
									}
								}
								if (flag == false)
								{
									for (int k = 0; k < deckThree[i][1]; ++k)
									{
										Three[ThreeIndex + k] = deckThree[i][0] + k;
									}
									ThreeIndex += deckThree[i][1];
								}
							}
						}
						if (UpperCard[1] == 2)
						{
							if (TwoIndex > 0)
							{
								if (Two[TwoIndex - 1] > UpperCard[0])
								{
									Out[0] = Two[TwoIndex - 1];
									Out[1] = 2;
									Out[2] = 0;
									TwoIndex--;
									return 1;
								}
							}
							//gai
							if (deckTwoIndex > 0)
							{
								for (int i = 0; i < deckTwoIndex; ++i)
								{
									if (deckTwo[i][1] > 3 && deckTwo[i][0] + deckTwo[i][1] - 1 > UpperCard[0])
									{
										Out[0] = deckTwo[i][0] + deckTwo[i][1] - 1;
										Out[1] = 2;
										Out[2] = 0;
										deckTwo[i][1]--;
										return 1;
									}
									else if (deckTwo[i][0] + deckTwo[i][1] - 1 > UpperCard[0])
									{
										Out[0] = deckTwo[i][0] + deckTwo[i][1] - 1;
										Out[1] = 2;
										Out[2] = 0;
										Two[TwoIndex] = Out[0] - 2;
										TwoIndex++;
										Two[TwoIndex] = Out[0] - 1;
										TwoIndex++;
										for (int j = i; j < deckTwoIndex; ++i)
										{
											deckTwo[j][0] = deckTwo[j + 1][0];
											deckTwo[j][1] = deckTwo[j + 1][1];
										}
										return 1;
									}
								}
							}
							if (ThreeIndex > 0)
							{
								for (int i = 0; i < ThreeIndex; ++i)
								{
									if (Three[i] > UpperCard[0] && (UnSafeNum <= ThreeIndex || Three[i] > dzMaxOne))
									{
										Out[0] = Three[i];
										Out[1] = 2;
										Out[2] = 0;
										ThreeIndex--;
										return 1;
									}
								}
							}
						}
						else//UpperCard[3] ==3
						{
							bool IsRes = false;
							bool flag = false;
							int temp = 0;
							for (int i = 0; i < ThreeIndex; ++i)
							{
								if (Three[i] > UpperCard[0])
								{
									Out[0] = Three[i];
									Out[1] = 3;
									Out[2] = 0;
									temp = i;
									IsRes = true;
									break;
								}
							}
							//�ɻ����
							if (IsRes == false)
							{
								for (int i = 0; i < deckThreeIndex; ++i)
								{
									if (deckThree[i][0] + deckThree[i][1] - 1 > UpperCard[0])
									{
										Out[0] = deckThree[i][0] + deckThree[i][1] - 1;
										Out[1] = 3;
										Out[2] = 0;
										temp = 10 + i;
										IsRes = true;
										break;
									}
								}
							}
							//************���� 0,1,2
							if (IsRes == true)
							{
								if (UpperCard[4] == 1)
								{
									if (OneIndex > 0 && One[0] < 13)
									{
										Out[4] = 1;
										Out[3] = One[0];
										OneIndex++;
										for (int i = 0; i < OneIndex; ++i)
										{
											One[i] = One[i + 1];
										}
										flag = true;
									}
									else//�ص��Ż�//˼���Ƿ�һ��Ҫѹ������ӻ��ǲ�˳�ӻ��ǲ����������������//������˳�ӣ���������
									{
										if (WhoseOut == -1 && frontN < 5)
										{
											int boomtemp = -1;
											for (int i = 15; i > 2; i--)
											{
												if (elseCard[i] > 3)
												{
													boomtemp = i;
													break;
												}
											}
											if (boomtemp > 0 && FourIndex > 0)
											{
												Out[0] = Four[0];
												Out[1] = 4;
												Out[2] = 4;
												Out[4] = 0;
												Out[3] = 0;
												FourIndex--;
												for (int i = 0; i < FourIndex; ++i)
												{
													Four[i] = Four[i + 1];
												}
												return 1;
											}
											else if (KingBoom > 0 && OneIndex < 3)
											{
												Out[0] = 17;
												Out[1] = 2;
												Out[2] = 4;
												KingBoom = 0;
												return 1;
											}
											else if (FourIndex > 0)
											{
												Out[0] = Four[0];
												Out[1] = 4;
												Out[2] = 4;
												Out[4] = 0;
												Out[3] = 0;
												FourIndex--;
												for (int i = 0; i < FourIndex; ++i)
												{
													Four[i] = Four[i + 1];
												}
												return 1;
											}
											else
											{
												if (deckIndex > 0)
												{
													for (int i = 0; i < deckIndex; ++i)
													{
														if (deck[i][1] > 5)
														{
															Out[3] = deck[i][0];
															Out[4] = 1;
															deck[i][0]++;
															deck[i][1]--;
															flag = true;
															break;
														}
													}
												}
												else if (TwoIndex > 1)
												{
													Out[3] = Two[TwoIndex - 2];
													Out[4] = 1;
													Two[TwoIndex - 2] = Two[TwoIndex - 1];
													bool fg = false;
													flag = true;
													for (int i = 0; i < OneIndex; ++i)
													{
														if (One[i] > Out[3])
														{
															for (int j = OneIndex; j > i; j--)
															{
																One[j] = One[j - 1];
															}
															OneIndex++;
															One[i] = Out[3];
															fg = true;
															break;
														}
													}
													if (!fg)
													{
														One[OneIndex] = Out[3];
														OneIndex++;
													}
												}
												else if (TwoIndex == 1)
												{
													Out[3] = Two[TwoIndex - 1];
													Out[4] = 1;
													TwoIndex--;
													bool fg = false;
													flag = true;
													for (int i = 0; i < OneIndex; ++i)
													{
														if (One[i] > Out[3])
														{
															for (int j = OneIndex; j > i; j--)
															{
																One[j] = One[j - 1];
															}
															OneIndex++;
															One[i] = Out[3];
															fg = true;
															break;
														}
													}
													if (!fg)
													{
														One[OneIndex] = Out[3];
														OneIndex++;
													}
												}
												else if (ThreeIndex > 1 && ThreeIndex - 2 != temp)
												{
													Out[3] = Three[ThreeIndex - 2];
													Out[4] = 1;
													Three[ThreeIndex - 2] = Three[ThreeIndex - 1];
													ThreeIndex--;
													flag = true;
													bool fg = false;
													for (int i = 0; i < TwoIndex; ++i)
													{
														if (Two[i] > Out[3])
														{
															for (int j = TwoIndex; j > i; j--)
															{
																Two[j] = Two[j - 1];
															}
															Two[i] = Out[3];
															TwoIndex++;
															fg = true;
															break;
														}
													}
													if (!fg)
													{
														Two[TwoIndex] = Out[3];
														TwoIndex++;
													}
												}
												else if ((ThreeIndex == 1 && Three[0] < 15 && ThreeIndex != temp) || (ThreeIndex > 1 && ThreeIndex - 2 != temp))
												{
													Out[3] = Three[ThreeIndex - 1];
													Out[4] = 1;
													ThreeIndex--;
													flag = true;
													bool fg = false;
													for (int i = 0; i < TwoIndex; ++i)
													{
														if (Two[i] > Out[3])
														{
															for (int j = TwoIndex; j > i; j--)
															{
																Two[j] = Two[j - 1];
															}
															Two[i] = Out[3];
															TwoIndex++;
															fg = true;
															break;
														}
													}
													if (!fg)
													{
														Two[TwoIndex] = Out[3];
														TwoIndex++;
													}
												}
												else
												{

												}
											}
										}
										else if (OneIndex > 0 && One[0] < 15)
										{
											Out[4] = 1;
											Out[3] = One[0];
											OneIndex++;
											for (int i = 0; i < OneIndex; ++i)
											{
												One[i] = One[i + 1];
											}
											flag = true;
										}
										else if (deckIndex > 0)
										{
											for (int i = 0; i < deckIndex; ++i)
											{
												if (deck[i][1] > 5)
												{
													Out[3] = deck[i][0];
													Out[4] = 1;
													deck[i][0]++;
													deck[i][1]--;
													flag = true;
													break;
												}
											}
										}
										else if (TwoIndex > 1)
										{
											Out[3] = Two[TwoIndex - 2];
											Out[4] = 1;
											Two[TwoIndex - 2] = Two[TwoIndex - 1];
											bool fg = false;
											flag = true;
											for (int i = 0; i < OneIndex; ++i)
											{
												if (One[i] > Out[3])
												{
													for (int j = OneIndex; j > i; j--)
													{
														One[j] = One[j - 1];
													}
													OneIndex++;
													One[i] = Out[3];
													fg = true;
													break;
												}
											}
											if (!fg)
											{
												One[OneIndex] = Out[3];
												OneIndex++;
											}
										}
										else if (TwoIndex == 1)
										{
											Out[3] = Two[TwoIndex - 1];
											Out[4] = 1;
											TwoIndex--;
											bool fg = false;
											flag = true;
											for (int i = 0; i < OneIndex; ++i)
											{
												if (One[i] > Out[3])
												{
													for (int j = OneIndex; j > i; j--)
													{
														One[j] = One[j - 1];
													}
													OneIndex++;
													One[i] = Out[3];
													fg = true;
													break;
												}
											}
											if (!fg)
											{
												One[OneIndex] = Out[3];
												OneIndex++;
											}
										}
										else
										{

										}
									}
								}
								else if (UpperCard[4] == 2)
								{
									if (TwoIndex > 0 && (Two[0] < 13 || behindN < 6))
									{
										Out[4] = 2;
										Out[3] = Two[0];
										TwoIndex++;
										for (int i = 0; i < TwoIndex; ++i)
										{
											Two[i] = Two[i + 1];
										}
										flag = true;
									}
									else
									{
										if (WhoseOut == -1 && behindN < 5)
										{
											int boomtemp = -1;
											for (int i = 15; i > 2; i--)
											{
												if (elseCard[i] > 3)
												{
													boomtemp = i;
													break;
												}
											}
											if (boomtemp > 0 && FourIndex > 0)
											{
												Out[0] = Four[0];
												Out[1] = 4;
												Out[2] = 4;
												Out[4] = 0;
												Out[3] = 0;
												FourIndex--;
												for (int i = 0; i < FourIndex; ++i)
												{
													Four[i] = Four[i + 1];
												}
												return 1;
											}
											else if (KingBoom > 0 && OneIndex < 3)
											{
												Out[0] = 17;
												Out[1] = 2;
												Out[2] = 4;
												KingBoom = 0;
												return 1;
											}
											else if (FourIndex > 0)
											{
												Out[0] = Four[0];
												Out[1] = 4;
												Out[2] = 4;
												Out[4] = 0;
												Out[3] = 0;
												FourIndex--;
												for (int i = 0; i < FourIndex; ++i)
												{
													Four[i] = Four[i + 1];
												}
												return 1;
											}
											else
											{
												if (deckIndex > 0)
												{
													for (int i = 0; i < deckIndex; ++i)
													{
														if (deck[i][1] > 5)
														{
															Out[3] = deck[i][0];
															Out[4] = 1;
															deck[i][0]++;
															deck[i][1]--;
															flag = true;
															break;
														}
													}
												}
												else if (TwoIndex > 1)
												{
													Out[3] = Two[TwoIndex - 2];
													Out[4] = 1;
													Two[TwoIndex - 2] = Two[TwoIndex - 1];
													bool fg = false;
													flag = true;
													for (int i = 0; i < OneIndex; ++i)
													{
														if (One[i] > Out[3])
														{
															for (int j = OneIndex; j > i; j--)
															{
																One[j] = One[j - 1];
															}
															OneIndex++;
															One[i] = Out[3];
															fg = true;
															break;
														}
													}
													if (!fg)
													{
														One[OneIndex] = Out[3];
														OneIndex++;
													}
												}
												else if (TwoIndex == 1)
												{
													Out[3] = Two[TwoIndex - 1];
													Out[4] = 1;
													TwoIndex--;
													bool fg = false;
													flag = true;
													for (int i = 0; i < OneIndex; ++i)
													{
														if (One[i] > Out[3])
														{
															for (int j = OneIndex; j > i; j--)
															{
																One[j] = One[j - 1];
															}
															OneIndex++;
															One[i] = Out[3];
															fg = true;
															break;
														}
													}
													if (!fg)
													{
														One[OneIndex] = Out[3];
														OneIndex++;
													}
												}
												else if (ThreeIndex > 1 && ThreeIndex - 2 != temp)
												{
													Out[3] = Three[ThreeIndex - 2];
													Out[4] = 1;
													Three[ThreeIndex - 2] = Three[ThreeIndex - 1];
													ThreeIndex--;
													flag = true;
													bool fg = false;
													for (int i = 0; i < TwoIndex; ++i)
													{
														if (Two[i] > Out[3])
														{
															for (int j = TwoIndex; j > i; j--)
															{
																Two[j] = Two[j - 1];
															}
															Two[i] = Out[3];
															TwoIndex++;
															fg = true;
															break;
														}
													}
													if (!fg)
													{
														Two[TwoIndex] = Out[3];
														TwoIndex++;
													}
												}
												else if ((ThreeIndex == 1 && Three[0] < 15 && ThreeIndex != temp) || (ThreeIndex > 1 && ThreeIndex - 2 != temp))
												{
													Out[3] = Three[ThreeIndex - 1];
													Out[4] = 1;
													ThreeIndex--;
													flag = true;
													bool fg = false;
													for (int i = 0; i < TwoIndex; ++i)
													{
														if (Two[i] > Out[3])
														{
															for (int j = TwoIndex; j > i; j--)
															{
																Two[j] = Two[j - 1];
															}
															Two[i] = Out[3];
															TwoIndex++;
															fg = true;
															break;
														}
													}
													if (!fg)
													{
														Two[TwoIndex] = Out[3];
														TwoIndex++;
													}
												}
												else
												{

												}
											}
										}
										else if (WhoseOut == 1)
										{
											return -1;
										}
										else if (deckTwoIndex > 0)
										{
											for (int i = 0; i < deckTwoIndex; ++i)
											{
												if (deckTwo[i][1] > 3)
												{
													Out[3] = deckTwo[i][0];
													Out[4] = 2;
													flag = true;
													deckTwo[i][0]++;
													deckTwo[i][1]--;
													break;
												}
												else if (deckTwo[i][0]+ deckTwo[i][1] - 1 > 12 && i == deckTwoIndex - 1 && (frontN < 5 || behindN < 5))
												{
													Out[3] = deckTwo[i][0];
													Out[4] = 2;
													flag = true;
													bool fg = false;
													for (int j = 0; j < TwoIndex; ++j)
													{
														if (Two[j] > Out[3])
														{
															for (int k = TwoIndex; k > j; --k)
															{
																Two[k + 1] = Two[k - 1];
															}
															fg = true;
															Two[j] = deckTwo[i][0] + 1;
															Two[j + 1] = deckTwo[i][0] + 2;
															TwoIndex += 2;
															break;
														}
													}
													if (!fg)
													{
														Two[TwoIndex] = deckTwo[i][0] + 1;
														Two[TwoIndex + 1] = deckTwo[i][0] + 2;
														TwoIndex += 2;
													}
												}
												else
												{

												}
											}
										}
									}
								}
								else
								{
									flag = true;
								}
							}
							if (IsRes && flag)
							{
								if (temp < 10)
								{
									for (int i = temp; i < ThreeIndex; i++)
									{
										Three[i] = Three[i + 1];
									}
									ThreeIndex--;
								}
								else
								{
									temp -= 10;
									if (deckThree[temp][1] > 2)
									{
										deckThree[temp][1]--;
									}
									else
									{
										bool fg = false;
										for (int i = 0; i < ThreeIndex; ++i)
										{
											if (Three[i] > deckThree[temp][0])
											{
												for (int j = ThreeIndex; j > i; --j)
												{
													Three[j] = Three[j - 1];
												}
												Three[i] = deckThree[temp][0];
												ThreeIndex++;
												fg = true;
												break;
											}
										}
										if (!fg)
										{
											Three[ThreeIndex] = deckThree[temp][0];
											ThreeIndex++;
										}
										for (int i = temp; i < deckThreeIndex; ++i)
										{
											deckThree[i][1] = deckThree[i + 1][1];
											deckThree[i][0] = deckThree[i + 1][0];
										}
									}
								}
								return 1;
							}
						}
					}
					else if (UpperCard[2] == 1)
					{
						for (int i = 0; i < deckIndex; ++i)
						{
							if (deck[i][0] > UpperCard[0] && deck[i][1] == UpperCard[1])
							{
								Out[0] = deck[i][0];
								Out[1] = deck[i][1];
								Out[2] = 1;
								deckIndex--;
								for (int j = i; j < deckIndex; ++j)
								{
									deck[j][0] = deck[j + 1][0];
									deck[j][1] = deck[j + 1][1];
								}
								return 1;
							}
						}
						for (int i = 0; i < deckIndex; ++i)
						{
							if (deck[i][0] > UpperCard[0] && deck[i][1] == UpperCard[1] + 1)
							{
								int restOne = deck[i][0] + deck[i][1] - 1;
								for (int k = OneIndex; k > 0; --k)
								{
									//One[k-1] == restOne
									if (One[k - 1] > restOne)
									{
										One[k] = One[k - 1];
									}
									else
									{
										One[k] = restOne;
										break;
									}
								}
								OneIndex++;
								Out[0] = deck[i][0];
								Out[1] = deck[i][1] - 1;
								Out[2] = 1;
								deckIndex--;
								for (int j = i; j < deckIndex; ++j)
								{
									deck[j][0] = deck[j + 1][0];
									deck[j][1] = deck[j + 1][1];
								}
								return 1;
							}
							else if (deck[i][0] == UpperCard[0] && deck[i][1] == UpperCard[1] + 1)
							{
								int restOne = deck[i][0];
								for (int k = OneIndex; k > 0; --k)
								{
									//One[k-1] == restOne
									if (One[k - 1] > restOne)
									{
										One[k] = One[k - 1];
									}
									else
									{
										One[k] = restOne;
										break;
									}
								}
								OneIndex++;
								Out[0] = deck[i][0] + 1;
								Out[1] = deck[i][1] - 1;
								Out[2] = 1;
								deckIndex--;
								for (int j = i; j < deckIndex; ++j)
								{
									deck[j][0] = deck[j + 1][0];
									deck[j][1] = deck[j + 1][1];
								}
								return 1;
							}
						}
					}
					else if (UpperCard[2] == 2)
					{
						for (int i = 0; i < deckTwoIndex; ++i)
						{
							if (deckTwo[i][0] > UpperCard[0] && deckTwo[i][1] == UpperCard[1])
							{
								Out[0] = deckTwo[i][0];
								Out[1] = deckTwo[i][1];
								Out[2] = 2;
								deckTwoIndex--;
								for (int j = i; j < deckTwoIndex; ++j)
								{
									deckTwo[j][0] = deckTwo[j + 1][0];
									deckTwo[j][1] = deckTwo[j + 1][1];
								}
								return 1;
							}
						}
						for (int i = 0; i < deckTwoIndex; ++i)
						{
							if (deckTwo[i][0] + deckTwo[i][1] - 1 > UpperCard[0] + UpperCard[1] - 1 && deckTwo[i][1] > UpperCard[1])
							{
								int restTwo = deckTwo[i][0] + deckTwo[i][1] - 1;
								for (int j = 0; j < deckTwo[i][1] - UpperCard[1]; ++j)
								{
									Two[TwoIndex] = deckTwo[i][0] + j;
									TwoIndex++;
								}
								Out[0] = deckTwo[i][0] + deckTwo[i][1] - UpperCard[1];
								Out[1] = UpperCard[1];
								Out[2] = 2;
								deckTwoIndex--;
								for (int j = i; j < deckTwoIndex; ++j)
								{
									deckTwo[j][0] = deckTwo[j + 1][0];
									deckTwo[j][1] = deckTwo[j + 1][1];
								}
								return 1;
							}
						}
					}
					else if (UpperCard[2] == 3)
					{
						bool IsRes = false;
						int chai = 0;
						int chaiThree;
						for (int i = 0; i < deckThreeIndex; ++i)
						{
							if (UpperCard[0] < deckThree[i][0] && UpperCard[1] <= deckThree[i][1])
							{
								Out[0] = deckThree[i][0];
								Out[1] = UpperCard[1];
								Out[2] = 3;
								deckThreeIndex--;
								if (deckThree[i][1] - UpperCard[1] >= 2)
								{
									chai = 1;
									deckThree[i][0] = deckThree[i][0] + UpperCard[1] - 1;
									deckThree[i][1] = deckThree[i][1] - UpperCard[1];
								}
								else
								{
									if (deckThree[i][1] - UpperCard[1] > 0)
									{
										chai = 2;
										for (int j = 0; j < ThreeIndex; j++)
										{
											if (Three[j] > Out[0])
											{
												for (int k = ThreeIndex; k > j; --k)
												{
													Three[k - 1 + deckThree[i][1] - UpperCard[1]] = Three[k - 1];
												}
												ThreeIndex += deckThree[i][1] - UpperCard[1];
												for (int k = 0; k < deckThree[i][1] - UpperCard[1]; ++k)
												{
													Three[j + k] = deckThree[i][0] + UpperCard[1] + k;
												}
												chaiThree = j;
												break;
											}
										}
									}
									for (int j = i; j < deckThreeIndex; ++j)
									{
										deckThree[j][0] = deckThree[j + 1][0];
										deckThree[j][1] = deckThree[j + 1][1];
									}
								}
								IsRes = true;
								break;
							}
						}
						if (IsRes == true)
						{
							if (UpperCard[4] == 2)//������
							{
								int temp = UpperCard[1];
								//���ţ����Գ�����UpperCard[1]
								if (TwoIndex >= UpperCard[1] && Two[UpperCard[1]] < 14)
								{
									Out[3] = Two[0];
									Out[4] = 2;
									for (int i = 1; i < temp; ++i)
									{
										Out[4 + i] = Two[i];
									}
									TwoIndex -= temp;
									for (int i = 0; i < TwoIndex; ++i)
									{
										Two[i] = Two[i + temp];
									}
									return 1;
								}
								else if (deckTwoIndex > 0)
								{
									for (int k = TwoIndex; k > 0; --k)
									{
										if (Two[k - 1] > deckTwo[0][0])
										{
											Two[k - 1 + deckTwo[0][1]] = Two[k - 1];
										}
										else
										{
											for (int j = 0; j < deckTwo[0][1]; j++)
											{
												Two[k + j] = deckTwo[0][0] + j;
											}
											break;
										}
									}
									TwoIndex += deckTwo[0][1];
									for (int i = 0; i < deckTwoIndex; ++i)
									{
										deckTwo[i][1] = deckTwo[i + 1][1];
										deckTwo[i][0] = deckTwo[i + 1][0];
									}
									deckTwoIndex--;
									Out[3] = Two[0];
									Out[4] = 2;
									for (int i = 1; i < Out[1]; i++)
									{
										Out[4 + i] = Two[i + 1];
									}
									for (int i = 0; i < TwoIndex; i++)
									{
										Two[i] = Two[i + Out[1]];
									}
									TwoIndex -= Out[1];
									return 1;
								}
								else
								{
										
								}
							}
							else if (UpperCard[4] == 1)
							{
								int temp = UpperCard[1];
								//
								if (OneIndex >= UpperCard[1] && One[UpperCard[1] - 1] < 16)
								{
									Out[3] = One[0];
									Out[4] = 1;
									for (int i = 1; i < temp; ++i)
									{
										Out[4 + i] = One[i];
									}
									OneIndex -= temp;
									for (int i = 0; i < OneIndex; ++i)
									{
										One[i] = One[i + temp];
									}
									return 1;
								}
								else
								{

								}
							}
						}
						int boomtemp = -1;
						for (int i = 15; i > 2; i--)
						{
							if (elseCard[i] > 3)
							{
								boomtemp = i;
								break;
							}
						}
						if (boomtemp > 0 && FourIndex > 0)
						{
							Out[0] = Four[0];
							Out[1] = 4;
							Out[2] = 4;
							FourIndex--;
							for (int i = 0; i < FourIndex; ++i)
							{
								Four[i] = Four[i + 1];
							}
							return 1;
						}
						else if (KingBoom > 0 && OneIndex < 3)
						{
							Out[0] = 17;
							Out[1] = 2;
							Out[2] = 4;
							KingBoom = 0;
							return 1;
						}
						else if (FourIndex > 0)
						{
							Out[0] = Four[0];
							Out[1] = 4;
							Out[2] = 4;
							FourIndex--;
							for (int i = 0; i < FourIndex; ++i)
							{
								Four[i] = Four[i + 1];
							}
							return 1;
						}
					}
					else if (UpperCard[2] == 4)//  �Ĵ�2 //���Ż���Ŀǰֱ��ը//���Ĵ����ˣ�˵��ũ����̓�������߱�Ӯ�ˣ�����ֱ��ը��
					{
						if (UpperCard[0] == 17 || WhoseOut == 1)
						{
							return -1;
						}
						bool boom = false;
						bool ok = false;
						bool BB = false;
						if (FourIndex > 0)
						{
							boom = true;
						}
						if (UpperCard[4] == 1 && boom == true)
						{
							if (OneIndex > 1 && One[1] < 14)
							{
								Out[3] = One[0];
								Out[4] = 1;
								Out[5] = One[1];
								for (int i = 0; i < OneIndex; i++)
								{
									One[i] = One[i + 2];
								}
								OneIndex -= 2;
								ok = true;
							}
							else if (OneIndex == 1 && One[0] < 14)
							{
								if (TwoIndex > 0 && Two[0] < 14)
								{
									if (One[0] > Two[0])
									{
										Out[3] = Two[0];
										Out[4] = 1;
										Out[5] = Two[0];
										TwoIndex--;
										for (int i = 0; i < TwoIndex; i++)
										{
											Two[i] = Two[i + 1];
										}
										ok = true;
									}
									else
									{
										Out[3] = One[0];
										Out[4] = 1;
										Out[5] = Two[0];
										One[0] = Two[0];
										TwoIndex--;
										for (int i = 0; i < TwoIndex; i++)
										{
											Two[i] = Two[i + 1];
										}
										ok = true;
									}
								}
							}
							else if (TwoIndex > 0 && Two[0] < 14)
							{
								Out[3] = Two[0];
								Out[4] = 1;
								Out[5] = Two[0];
								TwoIndex--;
								for (int i = 0; i < TwoIndex; i++)
								{
									Two[i] = Two[i + 1];
								}
								ok = true;
							}
							else
							{

							}
						}
						else if (UpperCard[4] == 2 && boom == true)
						{
							if (TwoIndex > 1 && Two[1] < 14)
							{
								Out[3] = Two[0];
								Out[4] = 2;
								Out[5] = Two[1];
								TwoIndex -= 2;
								for (int i = 0; i < TwoIndex; i++)
								{
									Two[i] = Two[i + 2];
								}
								ok = true;
							}
						}
						else
						{
							BB = true;
						}
						if (ok == true || (BB == true && KingBoom == 0))
						{
							for (int i = 0; i < FourIndex; i++)
							{
								if (Four[i] > UpperCard[0])
								{
									Out[0] = Four[i];
									Out[1] = 4;
									Out[2] = 4;
									FourIndex--;
									for (int j = i; j < FourIndex; ++j)
									{
										Four[j] = Four[j + 1];
									}
								}
							}
							return 1;
						}
						if (KingBoom == 1)
						{
							Out[0] = 17;
							Out[1] = 2;
							Out[2] = 4;
							Out[3] = 0;
							Out[4] = 0;
							Out[5] = 0;
							KingBoom = 0;
							return 1;
						}
						if (FourIndex > 0 && UpperCard[4] > 0)
						{
							for (int i = 0; i < FourIndex; i++)
							{

								Out[0] = Four[i];
								Out[1] = 4;
								Out[2] = 4;
								Out[3] = 0;
								Out[4] = 0;
								Out[5] = 0;
								FourIndex--;
								for (int j = i; j < FourIndex; j++)
								{
									Four[j] = Four[j + 1];
								}
								return 1;
							}
						}
						return -1;
					}
				}
				if (FourIndex > 0)//�Ż�
				{
					Out[0] = Four[0];
					Out[1] = 4;
					Out[2] = 4;
					FourIndex--;
					for (int i = 0; i < FourIndex; ++i)
					{
						Four[i] = Four[i + 1];
					}
					return 1;
				}
			}
			return -1;
		}
		//----------------------������˫
		else if ((DZIndex == 2 && behindN == 2) || (DZIndex == -1 && frontN == 2))
		{
			int dzMaxOne = OneElseMax;
			bool Boom = false;
			if (WhoseOut == 1 && MyRoundNum > 2 && (UpperCard[2] > 0 || UpperCard[1] > 2 || (UpperCard[0] >= TwoElseMax) || DZIndex == -1))
			{
				return -1;
			}
			if (UpperCard[2] == 0)
			{
				if (deckThreeIndex > 0)//�ѷɻ����ˣ�������ѹ����
				{
					for (int i = 0; i < deckThreeIndex; ++i)
					{
						bool flag = false;
						for (int j = 0; j < ThreeIndex; j++)
						{
							if (Three[j] > deckThree[i][0])
							{
								flag = true;
								for (int k = ThreeIndex; k > j; --k)
								{
									Three[k - 1 + deckThree[i][1]] = Three[k - 1];
								}
								ThreeIndex += deckThree[i][0];
								for (int k = 0; k < deckThree[i][1]; ++k)
								{
									Three[j + k] = deckThree[i][0] + k;
								}
							}
						}
						if (flag == false)
						{
							for (int k = 0; k < deckThree[i][1]; ++k)
							{
								Three[ThreeIndex + k] = deckThree[i][0] + k;
							}
							ThreeIndex += deckThree[i][1];
						}
					}
				}
				if (UpperCard[1] == 1)
				{
					if (OneIndex > 0)
					{
						for (int i = OneIndex - 1; i >= 0; --i)
						{
							if (One[i] > UpperCard[0])
							{
								Out[0] = One[i];
								Out[1] = 1;
								Out[2] = 0;
								OneIndex--;
								for (int j = i; j < OneIndex; ++j)
								{
									One[j] = One[j + 1];
								}
								return 1;
							}
						}
					}
					else
					{
						int MaxRestC = 0, IsHave = 0;
						for (int i = 15; i >= 3; --i)
						{
							if (myCard[i] > 0)
							{
								MaxRestC = i;
								IsHave = 1;
							}
							if (elseCard[i] > 0)
							{
								MaxRestC = i;
								break;
							}
						}
						if (UpperCard[0] >= MaxRestC)
						{
							MaxRestC = UpperCard[0] + 1;
						}
						if (deckIndex > 0 && IsHave > 0 )
						{
							for (int i = 0; i < deckIndex; ++i)
							{
								if (deck[i][1] > 5 && deck[i][0] + deck[i][1] - 1 >= MaxRestC)
								{
									Out[0] = deck[i][0] + deck[i][1] - 1;
									Out[1] = 1;
									Out[2] = 0;
									deck[i][1]--;
									return 1;
								}
							}
						}
						if (TwoIndex > 0 && IsHave > 0)
						{
							for (int i = 0; i < TwoIndex; ++i)
							{
								if (Two[i] >= MaxRestC)
								{
									Out[0] = Two[i];
									Out[1] = 1;
									Out[2] = 0;
									TwoIndex--;
									int IsADD = 0;
									for (int j = 0; j < OneIndex; j++)
									{
										if (One[j] > Out[0])
										{
											for (int k = OneIndex; k > j; --k)
											{
												One[k] = One[k - 1];
											}
											++OneIndex;
											One[j] = Out[0];
											IsADD = 1;
										}
									}
									if (IsADD == 0)
									{
										One[OneIndex] = Out[0];
										OneIndex++;
									}
									return 1;
								}
							}
						}
						if (ThreeIndex > 0 && IsHave > 0)
						{
							for (int i = 0; i < ThreeIndex; ++i)
							{
								if (Three[i] >= MaxRestC)
								{
									Out[0] = Three[i];
									Out[1] = 1;
									Out[2] = 0;
									ThreeIndex--;
									for (int j = 0; j < TwoIndex; j++)
									{
										if (Two[j] > Out[0])
										{
											for (int k = TwoIndex; k > j; --k)
											{
												Two[k] = Two[k - 1];
											}
											++TwoIndex;
											Two[j] = Out[0];
										}
									}
									return 1;
								}
							}
						}
					}
				}
				else if (UpperCard[1] == 2)
				{
					if (TwoIndex > 0)
					{
						for (int i = 0; i < TwoIndex; ++i)
						{
							
							if (Two[i] > UpperCard[0] && Two[i] >= TwoElseMax)
							{
								
								Out[0] = Two[i];
								Out[1] = 2;
								Out[2] = 0;
								TwoIndex--;
								for (int j = i; j < TwoIndex; ++j)
								{
									Two[j] = Two[j + 1];
								}
								return 1;
							}
						}
					}
					int MaxRestC = 0, IsHave = 0;
					for (int i = 15; i >= 3; --i)
					{
						if (myCard[i] > 1)
						{
							MaxRestC = i;
							IsHave = 1;
						}
						if (elseCard[i] > 1)
						{
							MaxRestC = i;
							break;
						}
					}
					if (UpperCard[0] >= MaxRestC)
					{
						MaxRestC = UpperCard[0] + 1;
					}
					if (deckTwoIndex > 0 && IsHave > 0)
					{
						for (int i = 0; i < deckTwoIndex; ++i)
						{
							if (deckTwo[i][1] > 3 && deckTwo[i][0] + deckTwo[i][1] - 1 >= MaxRestC)
							{
								Out[0] = deckTwo[i][0] + deckTwo[i][1] - 1;
								Out[1] = 2;
								Out[2] = 0;
								deckTwo[i][1]--;
								return 1;
							}
						}
					}
					if (ThreeIndex > 0 && IsHave > 0)
					{
						for (int i = 0; i < ThreeIndex; ++i)
						{
							if (Three[i] >= MaxRestC)
							{
								Out[0] = Three[i];
								Out[1] = 2;
								Out[2] = 0;
								ThreeIndex--;
								return 1;
							}
						}
					}
					if (TwoIndex > 0 && Two[TwoIndex - 1] > UpperCard[0])
					{
						Out[0] = Two[TwoIndex - 1];
						Out[1] = 2;
						Out[2] = 0;
						return 1;
					}
				}
				else//UpperCard[3] ==3
				{
					bool IsRes = false;
					bool flag = false;
					int temp = 0;
					for (int i = 0; i < ThreeIndex; ++i)
					{
						if (Three[i] > UpperCard[0])
						{
							Out[0] = Three[i];
							Out[1] = 3;
							Out[2] = 0;
							temp = i;
							IsRes = true;
							break;
						}
					}
					//�ɻ����
					if (IsRes == false)
					{
						for (int i = 0; i < deckThreeIndex; ++i)
						{
							if (deckThree[i][0] + deckThree[i][1] - 1 > UpperCard[0])
							{
								Out[0] = deckThree[i][0] + deckThree[i][1] - 1;
								Out[1] = 3;
								Out[2] = 0;
								temp = 10 + i;
								IsRes = true;
								break;
							}
						}
					}
					//************���� 0,1,2
					if (IsRes == true)
					{
						if (UpperCard[4] == 1)
						{
							if (OneIndex > 0)
							{
								Out[4] = 1;
								Out[3] = One[0];
								OneIndex++;
								for (int i = 0; i < OneIndex; ++i)
								{
									One[i] = One[i + 1];
								}
								flag = true;
							}
							else//�ص��Ż�//˼���Ƿ�һ��Ҫѹ������ӻ��ǲ�˳�ӻ��ǲ����������������//������˳�ӣ���������
							{
									
								if (deckIndex > 0)
								{
									for (int i = 0; i < deckIndex; ++i)
									{
										if (deck[i][1] > 5)
										{
											Out[3] = deck[i][0];
											Out[4] = 1;
											deck[i][0]++;
											deck[i][1]--;
											flag = true;
											break;
										}
									}
								}
								else if (TwoIndex > 1)
								{
									Out[3] = Two[TwoIndex - 2];
									Out[4] = 1;
									Two[TwoIndex - 2] = Two[TwoIndex - 1];
									bool fg = false;
									flag = true;
									for (int i = 0; i < OneIndex; ++i)
									{
										if (One[i] > Out[3])
										{
											for (int j = OneIndex; j > i; j--)
											{
												One[j] = One[j - 1];
											}
											OneIndex++;
											One[i] = Out[3];
											fg = true;
											break;
										}
									}
									if (!fg)
									{
										One[OneIndex] = Out[3];
										OneIndex++;
									}
								}
								else if (TwoIndex == 1)
								{
									Out[3] = Two[TwoIndex - 1];
									Out[4] = 1;
									TwoIndex--;
									bool fg = false;
									flag = true;
									for (int i = 0; i < OneIndex; ++i)
									{
										if (One[i] > Out[3])
										{
											for (int j = OneIndex; j > i; j--)
											{
												One[j] = One[j - 1];
											}
											OneIndex++;
											One[i] = Out[3];
											fg = true;
											break;
										}
									}
									if (!fg)
									{
										One[OneIndex] = Out[3];
										OneIndex++;
									}
								}
								else if (ThreeIndex > 1 && ThreeIndex - 2 != temp)
								{
									Out[3] = Three[ThreeIndex - 2];
									Out[4] = 1;
									Three[ThreeIndex - 2] = Three[ThreeIndex - 1];
									ThreeIndex--;
									flag = true;
									bool fg = false;
									for (int i = 0; i < TwoIndex; ++i)
									{
										if (Two[i] > Out[3])
										{
											for (int j = TwoIndex; j > i; j--)
											{
												Two[j] = Two[j - 1];
											}
											Two[i] = Out[3];
											TwoIndex++;
											fg = true;
											break;
										}
									}
									if (!fg)
									{
										Two[TwoIndex] = Out[3];
										TwoIndex++;
									}
								}
								else if ((ThreeIndex == 1 && ThreeIndex != temp) || (ThreeIndex > 1 && ThreeIndex - 2 != temp))
								{
									Out[3] = Three[ThreeIndex - 1];
									Out[4] = 1;
									ThreeIndex--;
									flag = true;
									bool fg = false;
									for (int i = 0; i < TwoIndex; ++i)
									{
										if (Two[i] > Out[3])
										{
											for (int j = TwoIndex; j > i; j--)
											{
												Two[j] = Two[j - 1];
											}
											Two[i] = Out[3];
											TwoIndex++;
											fg = true;
											break;
										}
									}
									if (!fg)
									{
										Two[TwoIndex] = Out[3];
										TwoIndex++;
									}
								}
								else
								{

								}
							}
						}
						else if (UpperCard[4] == 2)
						{
							if (TwoIndex > 0 && Two[0] < OneElseMax)
							{
								Out[4] = 2;
								Out[3] = Two[0];
								TwoIndex++;
								for (int i = 0; i < TwoIndex; ++i)
								{
									Two[i] = Two[i + 1];
								}
								flag = true;
							}
							else
							{
								if (deckTwoIndex > 0)
								{
									for (int i = 0; i < deckTwoIndex; ++i)
									{
										if (deckTwo[i][1] > 3)
										{
											Out[3] = deckTwo[i][0];
											Out[4] = 2;
											flag = true;
											deckTwo[i][0]++;
											deckTwo[i][1]--;
											break;
										}
										else if (deckTwo[i][0]+ deckTwo[i][1] - 1 > 12 && i == deckTwoIndex - 1 && (frontN < 5 || behindN < 5))
										{
											Out[3] = deckTwo[i][0];
											Out[4] = 2;
											flag = true;
											bool fg = false;
											for (int j = 0; j < TwoIndex; ++j)
											{
												if (Two[j] > Out[3])
												{
													for (int k = TwoIndex; k > j; --k)
													{
														Two[k + 1] = Two[k - 1];
													}
													fg = true;
													Two[j] = deckTwo[i][0] + 1;
													Two[j + 1] = deckTwo[i][0] + 2;
													TwoIndex += 2;
													break;
												}
											}
											if (!fg)
											{
												Two[TwoIndex] = deckTwo[i][0] + 1;
												Two[TwoIndex + 1] = deckTwo[i][0] + 2;
												TwoIndex += 2;
											}
										}
										else
										{

										}
									}
								}
							}
						}
						else
						{
							flag = true;
						}
					}
					if (IsRes && flag)
					{
						if (temp < 10)
						{
							for (int i = temp; i < ThreeIndex; i++)
							{
								Three[i] = Three[i + 1];
							}
							ThreeIndex--;
						}
						else
						{
							temp -= 10;
							if (deckThree[temp][1] > 2)
							{
								deckThree[temp][1]--;
							}
							else
							{
								bool fg = false;
								for (int i = 0; i < ThreeIndex; ++i)
								{
									if (Three[i] > deckThree[temp][0])
									{
										for (int j = ThreeIndex; j > i; --j)
										{
											Three[j] = Three[j - 1];
										}
										Three[i] = deckThree[temp][0];
										ThreeIndex++;
										fg = true;
										break;
									}
								}
								if (!fg)
								{
									Three[ThreeIndex] = deckThree[temp][0];
									ThreeIndex++;
								}
								for (int i = temp; i < deckThreeIndex; ++i)
								{
									deckThree[i][1] = deckThree[i + 1][1];
									deckThree[i][0] = deckThree[i + 1][0];
								}
							}
						}
						return 1;
					}
					cout << IsRes << " " << flag << endl;
				}
			}
			else if (UpperCard[2] == 1)
			{
				for (int i = 0; i < deckIndex; ++i)
				{
					if (deck[i][0] > UpperCard[0] && deck[i][1] == UpperCard[1])
					{
						Out[0] = deck[i][0];
						Out[1] = deck[i][1];
						Out[2] = 1;
						deckIndex--;
						for (int j = i; j < deckIndex; ++j)
						{
							deck[j][0] = deck[j + 1][0];
							deck[j][1] = deck[j + 1][1];
						}
						return 1;
					}
				}
				for (int i = 0; i < deckIndex; ++i)
				{
					if (deck[i][0] > UpperCard[0] && deck[i][1] == UpperCard[1] + 1)
					{
						int restOne = deck[i][0] + deck[i][1] - 1;
						for (int k = OneIndex; k > 0; --k)
						{
							//One[k-1] == restOne
							if (One[k - 1] > restOne)
							{
								One[k] = One[k - 1];
							}
							else
							{
								One[k] = restOne;
								break;
							}
						}
						OneIndex++;
						Out[0] = deck[i][0];
						Out[1] = deck[i][1] - 1;
						Out[2] = 1;
						deckIndex--;
						for (int j = i; j < deckIndex; ++j)
						{
							deck[j][0] = deck[j + 1][0];
							deck[j][1] = deck[j + 1][1];
						}
						return 1;
					}
					else if (deck[i][0] == UpperCard[0] && deck[i][1] == UpperCard[1] + 1)
					{
						int restOne = deck[i][0];
						for (int k = OneIndex; k > 0; --k)
						{
							//One[k-1] == restOne
							if (One[k - 1] > restOne)
							{
								One[k] = One[k - 1];
							}
							else
							{
								One[k] = restOne;
								break;
							}
						}
						OneIndex++;
						Out[0] = deck[i][0] + 1;
						Out[1] = deck[i][1] - 1;
						Out[2] = 1;
						deckIndex--;
						for (int j = i; j < deckIndex; ++j)
						{
							deck[j][0] = deck[j + 1][0];
							deck[j][1] = deck[j + 1][1];
						}
						return 1;
					}
				}
			}
			else if (UpperCard[2] == 2)
			{
				for (int i = 0; i < deckTwoIndex; ++i)
				{
					if (deckTwo[i][0] > UpperCard[0] && deckTwo[i][1] == UpperCard[1])
					{
						Out[0] = deckTwo[i][0];
						Out[1] = deckTwo[i][1];
						Out[2] = 2;
						deckTwoIndex--;
						for (int j = i; j < deckTwoIndex; ++j)
						{
							deckTwo[j][0] = deckTwo[j + 1][0];
							deckTwo[j][1] = deckTwo[j + 1][1];
						}
						return 1;
					}
				}
				for (int i = 0; i < deckTwoIndex; ++i)
				{
					if (deckTwo[i][0] + deckTwo[i][1] - 1 > UpperCard[0] + UpperCard[1] - 1 && deckTwo[i][1] > UpperCard[1])
					{
						for (int j = 0; j < deckTwo[i][1]; j++)
						{
							if (deckTwo[i][0] + j > UpperCard[0])
							{
								Out[0] = deckTwo[i][0] + j;
								Out[1] = UpperCard[1];
								Out[2] = 2;
								return 1;
							}
						}
					}
				}
			}
			else if (UpperCard[2] == 3)
			{
				bool IsRes = false;
				int chai = 0;
				int chaiThree;
				for (int i = 0; i < deckThreeIndex; ++i)
				{
					if (UpperCard[0] < deckThree[i][0] && UpperCard[1] <= deckThree[i][1])
					{
						Out[0] = deckThree[i][0];
						Out[1] = UpperCard[1];
						Out[2] = 3;
						deckThreeIndex--;
						if (deckThree[i][1] - UpperCard[1] >= 2)
						{
							chai = 1;
							deckThree[i][0] = deckThree[i][0] + UpperCard[1] - 1;
							deckThree[i][1] = deckThree[i][1] - UpperCard[1];
						}
						else
						{
							if (deckThree[i][1] - UpperCard[1] > 0)
							{
								chai = 2;
								for (int j = 0; j < ThreeIndex; j++)
								{
									if (Three[j] > Out[0])
									{
										for (int k = ThreeIndex; k > j; --k)
										{
											Three[k - 1 + deckThree[i][1] - UpperCard[1]] = Three[k - 1];
										}
										ThreeIndex += deckThree[i][1] - UpperCard[1];
										for (int k = 0; k < deckThree[i][1] - UpperCard[1]; ++k)
										{
											Three[j + k] = deckThree[i][0] + UpperCard[1] + k;
										}
										chaiThree = j;
										break;
									}
								}
							}
							for (int j = i; j < deckThreeIndex; ++j)
							{
								deckThree[j][0] = deckThree[j + 1][0];
								deckThree[j][1] = deckThree[j + 1][1];
							}
						}
						IsRes = true;
						break;
					}
				}
				if (IsRes == true)
				{
					if (UpperCard[4] == 2)//������
					{
						int temp = UpperCard[1];
						//���ţ����Գ�����UpperCard[1]
						if (TwoIndex >= UpperCard[1] && Two[UpperCard[1]] < 14)
						{
							Out[3] = Two[0];
							Out[4] = 2;
							for (int i = 1; i < temp; ++i)
							{
								Out[4 + i] = Two[i];
							}
							TwoIndex -= temp;
							for (int i = 0; i < TwoIndex; ++i)
							{
								Two[i] = Two[i + temp];
							}
							return 1;
						}
						else if (deckTwoIndex > 0)
						{
							for (int k = TwoIndex; k > 0; --k)
							{
								if (Two[k - 1] > deckTwo[0][0])
								{
									Two[k - 1 + deckTwo[0][1]] = Two[k - 1];
								}
								else
								{
									for (int j = 0; j < deckTwo[0][1]; j++)
									{
										Two[k + j] = deckTwo[0][0] + j;
									}
									break;
								}
							}
							TwoIndex += deckTwo[0][1];
							for (int i = 0; i < deckTwoIndex; ++i)
							{
								deckTwo[i][1] = deckTwo[i + 1][1];
								deckTwo[i][0] = deckTwo[i + 1][0];
							}
							deckTwoIndex--;
							Out[3] = Two[0];
							Out[4] = 2;
							for (int i = 1; i < Out[1]; i++)
							{
								Out[4 + i] = Two[i + 1];
							}
							for (int i = 0; i < TwoIndex; i++)
							{
								Two[i] = Two[i + Out[1]];
							}
							TwoIndex -= Out[1];
							return 1;
						}
						else
						{

						}
					}
					else if (UpperCard[4] == 1)
					{
						int temp = UpperCard[1];
						//
						if (OneIndex >= UpperCard[1] && One[UpperCard[1] - 1] < 16)
						{
							Out[3] = One[0];
							Out[4] = 1;
							for (int i = 1; i < temp; ++i)
							{
								Out[4 + i] = One[i];
							}
							OneIndex -= temp;
							for (int i = 0; i < OneIndex; ++i)
							{
								One[i] = One[i + temp];
							}
							return 1;
						}
						else
						{

						}
					}
				}
			}
			else if (UpperCard[2] == 4)//  �Ĵ�2 //���Ż���Ŀǰֱ��ը//���Ĵ����ˣ�˵��ũ����̓�������߱�Ӯ�ˣ�����ֱ��ը��
			{
				if (UpperCard[0] == 17 || WhoseOut == 1)
				{
					return -1;
				}
				bool boom = false;
				bool ok = false;
				bool BB = false;
				if (FourIndex > 0)
				{
					boom = true;
				}
				if (UpperCard[4] == 1 && boom == true)
				{
					if (OneIndex > 1 && One[1] < 14)
					{
						Out[3] = One[0];
						Out[4] = 1;
						Out[5] = One[1];
						for (int i = 0; i < OneIndex; i++)
						{
							One[i] = One[i + 2];
						}
						OneIndex -= 2;
						ok = true;
					}
					else if (OneIndex == 1 && One[0] < 14)
					{
						if (TwoIndex > 0 && Two[0] < 14)
						{
							if (One[0] > Two[0])
							{
								Out[3] = Two[0];
								Out[4] = 1;
								Out[5] = Two[0];
								TwoIndex--;
								for (int i = 0; i < TwoIndex; i++)
								{
									Two[i] = Two[i + 1];
								}
								ok = true;
							}
							else
							{
								Out[3] = One[0];
								Out[4] = 1;
								Out[5] = Two[0];
								One[0] = Two[0];
								TwoIndex--;
								for (int i = 0; i < TwoIndex; i++)
								{
									Two[i] = Two[i + 1];
								}
								ok = true;
							}
						}
					}
					else if (TwoIndex > 0 && Two[0] < 14)
					{
						Out[3] = Two[0];
						Out[4] = 1;
						Out[5] = Two[0];
						TwoIndex--;
						for (int i = 0; i < TwoIndex; i++)
						{
							Two[i] = Two[i + 1];
						}
						ok = true;
					}
					else
					{

					}
				}
				else if (UpperCard[4] == 2 && boom == true)
				{
					if (TwoIndex > 1 && Two[1] < 14)
					{
						Out[3] = Two[0];
						Out[4] = 2;
						Out[5] = Two[1];
						TwoIndex -= 2;
						for (int i = 0; i < TwoIndex; i++)
						{
							Two[i] = Two[i + 2];
						}
						ok = true;
					}
				}
				else
				{
					BB = true;
				}
				if (ok == true || (BB == true && KingBoom == 0))
				{
					for (int i = 0; i < FourIndex; i++)
					{
						if (Four[i] > UpperCard[0])
						{
							Out[0] = Four[i];
							Out[1] = 4;
							Out[2] = 4;
							FourIndex--;
							for (int j = i; j < FourIndex; ++j)
							{
								Four[j] = Four[j + 1];
							}
						}
					}
					return 1;
				}
				if (KingBoom == 1)
				{
					Out[0] = 17;
					Out[1] = 2;
					Out[2] = 4;
					Out[3] = 0;
					Out[4] = 0;
					Out[5] = 0;
					KingBoom = 0;
					return 1;
				}
				if (FourIndex > 0 && UpperCard[4] > 0)
				{
					for (int i = 0; i < FourIndex; i++)
					{

						Out[0] = Four[i];
						Out[1] = 4;
						Out[2] = 4;
						Out[3] = 0;
						Out[4] = 0;
						Out[5] = 0;
						FourIndex--;
						for (int j = i; j < FourIndex; j++)
						{
							Four[j] = Four[j + 1];
						}
						return 1;
					}
				}
				return -1;
			}
			if (KingBoom == 1 && (WhoseOut != 1 || MyRoundNum == 1))
			{
				Out[0] = 17;
				Out[1] = 2;
				Out[2] = 4;
				KingBoom = 0;
				return 1;
			}
			else if (FourIndex > 0)//�Ż�
			{
				Out[0] = Four[0];
				Out[1] = 4;
				Out[2] = 4;
				FourIndex--;
				for (int i = 0; i < FourIndex; ++i)
				{
					Four[i] = Four[i + 1];
				}
				return 1;
			}
			return -1;
		}
		//------------�ƺõ�ũ�� ||�����¼�
		else if (GoodNM || (DZIndex == -1))
		{
			if (UpperCard[2] == 0)
			{
				if (UpperCard[1] == 1)
				{
					if (OneIndex > 0 && (myN == 1 || (MyRoundNum == 2 && One[OneIndex - 1] >= OneElseMax)) && One[OneIndex - 1] > UpperCard[0])
					{
						Out[0] = One[OneIndex - 1];
						Out[1] = 1;
						Out[2] = 0;
						OneIndex--;
						return 1;
					}
					if (OneIndex > 0)
					{
						if (MyRoundNum < 3 && OneIndex + TwoIndex < 3 && One[OneIndex - 1] >= OneElseMax)
						{
							if (One[OneIndex - 1] > UpperCard[0])
							{
								if (WhoseOut == 1 && (DZIndex == -1 || UpperCard[0] > 13))
								{
									return -1;
								}
								Out[0] = One[OneIndex - 1];
								Out[1] = 1;
								Out[2] = 0;
								OneIndex--;
								return 1;
							}
						}
						for (int i = 0; i < OneIndex; ++i)
						{
							if (One[i] > UpperCard[0])
							{
								if (WhoseOut == 1 && (DZIndex == -1 || UpperCard[0] > 13))
								{
									return -1;
								}
								Out[0] = One[i];
								Out[1] = 1;
								Out[2] = 0;
								OneIndex--;
								for (int j = i; j < OneIndex; ++j)
								{
									One[j] = One[j + 1];
								}
								return 1;
							}
						}
					}
					//else ����else��ϵ  one�п���û�������� //����
					if (WhoseOut == 1 && ((DZIndex == 2 && behindN > 9)) || (DZIndex == -1))
					{
						return -1;
					}
					else
					{
						int MaxRestC = 0, IsHave = 0;
						for (int i = 15; i >= 3; --i)
						{
							if (myCard[i] > 0)
							{
								MaxRestC = i;
								IsHave = 1;
							}
							if (elseCard[i] > 0)
							{
								MaxRestC = i;
								break;
							}
						}
						if (UpperCard[0] >= MaxRestC)
						{
							MaxRestC = UpperCard[0] + 1;
						}
						if (deckIndex > 0 && (IsHave > 0 || (DZIndex == -1 && frontN < 9) || (DZIndex == 2 && behindN < 9)))
						{
							for (int i = 0; i < deckIndex; ++i)
							{
								if (deck[i][1] > 5 && deck[i][0] + deck[i][1] - 1 >= MaxRestC)
								{
									Out[0] = deck[i][0] + deck[i][1] - 1;
									Out[1] = 1;
									Out[2] = 0;
									deck[i][1]--;
									return 1;
								}
							}
						}
						if (TwoIndex > 0 && (IsHave > 0 || (DZIndex == -1 && frontN < 5) || (DZIndex == 2 && behindN < 5)))
						{
							for (int i = 0; i < TwoIndex; ++i)
							{
								if (Two[i] >= MaxRestC)
								{
									Out[0] = Two[i];
									Out[1] = 1;
									Out[2] = 0;
									TwoIndex--;
									int IsADD = 0;
									for (int j = 0; j < OneIndex; j++)
									{
										if (One[j] > Out[0])
										{
											for (int k = OneIndex; k > j; --k)
											{
												One[k] = One[k - 1];
											}
											++OneIndex;
											One[j] = Out[0];
											IsADD = 1;
										}
									}
									if(IsADD == 0)
									{
										One[OneIndex] = Out[0];
										OneIndex++;
									}
									return 1;
								}
							}
						}
						if (ThreeIndex > 0 && (IsHave > 0 || (DZIndex == -1 && frontN < 6) || (DZIndex == 2 && behindN < 6)))
						{
							for (int i = 0; i < ThreeIndex; ++i)
							{
								if (Three[i] >= MaxRestC)
								{
									Out[0] = Three[i];
									Out[1] = 1;
									Out[2] = 0;
									ThreeIndex--;
									for (int j = 0; j < TwoIndex; j++)
									{
										if (Two[j] > Out[0])
										{
											for (int k = TwoIndex; k > j; --k)
											{
												Two[k] = Two[k - 1];
											}
											++TwoIndex;
											Two[j] = Out[0];
										}
									}
									return 1;
								}
							}
						}
					}
				}
				else if (UpperCard[1] == 2)
				{
					if (TwoIndex > 0)
					{
						if (TwoIndex > 0 && (myN == 2 || (MyRoundNum == 2 && Two[TwoIndex - 1] > TwoElseMax)) && Two[TwoIndex - 1] > UpperCard[0])
						{
							Out[0] = Two[TwoIndex - 1];
							Out[1] = 2;
							Out[2] = 0;
							TwoIndex--;
							return 1;
						}
						if (TwoIndex > 0 && MyRoundNum < 3 && OneIndex + TwoIndex < 3 && Two[TwoIndex - 1] >= TwoElseMax)
						{
							if (Two[TwoIndex - 1] > UpperCard[0])
							{
								if (WhoseOut == 1 && (DZIndex == -1 || UpperCard[0] > 13))
								{
									return -1;
								}
								Out[0] = Two[TwoIndex - 1];
								Out[1] = 2;
								Out[2] = 0;
								TwoIndex--;
								return 1;
							}
						}
						for (int i = 0; i < TwoIndex; ++i)
						{
							if (Two[i] > UpperCard[0])
							{
								if (WhoseOut == 1 && (DZIndex == -1 || Two[TwoIndex - 1] > 11))
								{
									return -1;
								}
								Out[0] = Two[i];
								Out[1] = 2;
								Out[2] = 0;
								TwoIndex--;
								for (int j = i; j < TwoIndex; ++j)
								{
									Two[j] = Two[j + 1];
								}
								return 1;
							}
						}
					}
					//gai
					if (WhoseOut == 1 && DZIndex == 2 && behindN > 9)
					{
						return -1;
					}
					// �����ٲ�
					int MaxRestC = 0, IsHave = 0;
					for (int i = 15; i >= 3; --i)
					{
						if (myCard[i] > 1)
						{
							MaxRestC = i;
							IsHave = 1;
						}
						if (elseCard[i] > 1)
						{
							MaxRestC = i;
							break;
						}
					}
					if (UpperCard[0] >= MaxRestC)
					{
						MaxRestC = UpperCard[0] + 1;
					}
					if (deckTwoIndex > 0 && (IsHave > 0 || (DZIndex == -1 && frontN < 9) || (DZIndex == 2 && behindN < 9)))
					{
						for (int i = 0; i < deckTwoIndex; ++i)
						{
							if (deckTwo[i][1] > 3 && deckTwo[i][0] + deckTwo[i][1] - 1 >= MaxRestC)
							{
								Out[0] = deckTwo[i][0] + deckTwo[i][1] - 1;
								Out[1] = 2;
								Out[2] = 0;
								deckTwo[i][1]--;
								return 1;
							}
						}
					}
					if (ThreeIndex > 0 && (IsHave > 0 || (DZIndex == -1 && frontN < 9) || (DZIndex == 2 && behindN < 9)))
					{
						for (int i = 0; i < ThreeIndex; ++i)
						{
							if (Three[i] >= MaxRestC)
							{
								Out[0] = Three[i];
								Out[1] = 2;
								Out[2] = 0;
								ThreeIndex--;
								return 1;
							}
						}
					}
				}
				else//UpperCard[3] ==3
				{
					if (WhoseOut == 1 && ((DZIndex == -1) || (DZIndex == 2 && (behindN > 8 || UpperCard[0] > 11))))
					{
						return -1;
					}
					bool IsRes = false;
					bool flag = false;
					int temp = 0;
					for (int i = 0; i < ThreeIndex; ++i)
					{
						if (Three[i] > UpperCard[0])
						{
							Out[0] = Three[i];
							Out[1] = 3;
							Out[2] = 0;
							temp = i;
							IsRes = true;
							break;
						}
					}
					//�ɻ����
					if (IsRes == false)
					{
						for (int i = 0; i < deckThreeIndex; ++i)
						{
							if (deckThree[i][0] + deckThree[i][1] - 1 > UpperCard[0])
							{
								Out[0] = deckThree[i][0] + deckThree[i][1] - 1;
								Out[1] = 3;
								Out[2] = 0;
								temp = 10 + i;
								IsRes = true;
								break;
							}
						}
					}
					//************���� 0,1,2
					if (IsRes == true)
					{
						if (UpperCard[4] == 1)
						{
							if (OneIndex > 0 && One[0] < 13)
							{
								Out[4] = 1;
								Out[3] = One[0];
								OneIndex++;
								for (int i = 0; i < OneIndex; ++i)
								{
									One[i] = One[i + 1];
								}
								flag = true;
							}
							else//�ص��Ż�//˼���Ƿ�һ��Ҫѹ������ӻ��ǲ�˳�ӻ��ǲ����������������//������˳�ӣ���������
							{
								if (WhoseOut == -1 && frontN < 5)
								{
									int boomtemp = -1;
									for (int i = 15; i > 2; i--)
									{
										if (elseCard[i] > 3)
										{
											boomtemp = i;
											break;
										}
									}
									if (boomtemp > 0 && FourIndex > 0)
									{
										Out[0] = Four[0];
										Out[1] = 4;
										Out[2] = 4;
										Out[4] = 0;
										Out[3] = 0;
										FourIndex--;
										for (int i = 0; i < FourIndex; ++i)
										{
											Four[i] = Four[i + 1];
										}
										return 1;
									}
									else if (KingBoom > 0 && OneIndex < 3)
									{
										Out[0] = 17;
										Out[1] = 2;
										Out[2] = 4;
										KingBoom = 0;
										return 1;
									}
									else if (FourIndex > 0)
									{
										Out[0] = Four[0];
										Out[1] = 4;
										Out[2] = 4;
										Out[4] = 0;
										Out[3] = 0;
										FourIndex--;
										for (int i = 0; i < FourIndex; ++i)
										{
											Four[i] = Four[i + 1];
										}
										return 1;
									}
									else
									{
										if (deckIndex > 0)
										{
											for (int i = 0; i < deckIndex; ++i)
											{
												if (deck[i][1] > 5)
												{
													Out[3] = deck[i][0];
													Out[4] = 1;
													deck[i][0]++;
													deck[i][1]--;
													flag = true;
													break;
												}
											}
										}
										else if (TwoIndex > 1)
										{
											Out[3] = Two[TwoIndex - 2];
											Out[4] = 1;
											Two[TwoIndex - 2] = Two[TwoIndex - 1];
											bool fg = false;
											flag = true;
											for (int i = 0; i < OneIndex; ++i)
											{
												if (One[i] > Out[3])
												{
													for (int j = OneIndex; j > i; j--)
													{
														One[j] = One[j - 1];
													}
													OneIndex++;
													One[i] = Out[3];
													fg = true;
													break;
												}
											}
											if (!fg)
											{
												One[OneIndex] = Out[3];
												OneIndex++;
											}
										}
										else if (TwoIndex == 1)
										{
											Out[3] = Two[TwoIndex - 1];
											Out[4] = 1;
											TwoIndex--;
											bool fg = false;
											flag = true;
											for (int i = 0; i < OneIndex; ++i)
											{
												if (One[i] > Out[3])
												{
													for (int j = OneIndex; j > i; j--)
													{
														One[j] = One[j - 1];
													}
													OneIndex++;
													One[i] = Out[3];
													fg = true;
													break;
												}
											}
											if (!fg)
											{
												One[OneIndex] = Out[3];
												OneIndex++;
											}
										}
										else if (ThreeIndex > 1 && ThreeIndex - 2 != temp)
										{
											Out[3] = Three[ThreeIndex - 2];
											Out[4] = 1;
											Three[ThreeIndex - 2] = Three[ThreeIndex - 1];
											ThreeIndex--;
											flag = true;
											bool fg = false;
											for (int i = 0; i < TwoIndex; ++i)
											{
												if (Two[i] > Out[3])
												{
													for (int j = TwoIndex; j > i; j--)
													{
														Two[j] = Two[j - 1];
													}
													Two[i] = Out[3];
													TwoIndex++;
													fg = true;
													break;
												}
											}
											if (!fg)
											{
												Two[TwoIndex] = Out[3];
												TwoIndex++;
											}
										}
										else if ((ThreeIndex == 1 && Three[0] < 15 && ThreeIndex != temp) || (ThreeIndex > 1 && ThreeIndex - 2 != temp))
										{
											Out[3] = Three[ThreeIndex - 1];
											Out[4] = 1;
											ThreeIndex--;
											flag = true;
											bool fg = false;
											for (int i = 0; i < TwoIndex; ++i)
											{
												if (Two[i] > Out[3])
												{
													for (int j = TwoIndex; j > i; j--)
													{
														Two[j] = Two[j - 1];
													}
													Two[i] = Out[3];
													TwoIndex++;
													fg = true;
													break;
												}
											}
											if (!fg)
											{
												Two[TwoIndex] = Out[3];
												TwoIndex++;
											}
										}
										else
										{

										}
									}
								}
								else if (WhoseOut == 1)
								{
									return -1;
								}
								else if (OneIndex > 0 && One[0] < 15)
								{
									Out[4] = 1;
									Out[3] = One[0];
									OneIndex++;
									for (int i = 0; i < OneIndex; ++i)
									{
										One[i] = One[i + 1];
									}
									flag = true;
								}
								else if (deckIndex > 0)
								{
									for (int i = 0; i < deckIndex; ++i)
									{
										if (deck[i][1] > 5)
										{
											Out[3] = deck[i][0];
											Out[4] = 1;
											deck[i][0]++;
											deck[i][1]--;
											flag = true;
											break;
										}
									}
								}
								else if (TwoIndex > 1)
								{
									Out[3] = Two[TwoIndex - 2];
									Out[4] = 1;
									Two[TwoIndex - 2] = Two[TwoIndex - 1];
									bool fg = false;
									flag = true;
									for (int i = 0; i < OneIndex; ++i)
									{
										if (One[i] > Out[3])
										{
											for (int j = OneIndex; j > i; j--)
											{
												One[j] = One[j - 1];
											}
											OneIndex++;
											One[i] = Out[3];
											fg = true;
											break;
										}
									}
									if (!fg)
									{
										One[OneIndex] = Out[3];
										OneIndex++;
									}
								}
								else if (TwoIndex == 1)
								{
									Out[3] = Two[TwoIndex - 1];
									Out[4] = 1;
									TwoIndex--;
									bool fg = false;
									flag = true;
									for (int i = 0; i < OneIndex; ++i)
									{
										if (One[i] > Out[3])
										{
											for (int j = OneIndex; j > i; j--)
											{
												One[j] = One[j - 1];
											}
											OneIndex++;
											One[i] = Out[3];
											fg = true;
											break;
										}
									}
									if (!fg)
									{
										One[OneIndex] = Out[3];
										OneIndex++;
									}
								}
								else
								{

								}
							}
						}
						else if (UpperCard[4] == 2)
						{
							if (TwoIndex > 0 && (Two[0] < 13 || behindN < 6))
							{
								Out[4] = 2;
								Out[3] = Two[0];
								TwoIndex++;
								for (int i = 0; i < TwoIndex; ++i)
								{
									Two[i] = Two[i + 1];
								}
								flag = true;
							}
							else
							{
								if (WhoseOut == -1 && behindN < 5)
								{
									int boomtemp = -1;
									for (int i = 15; i > 2; i--)
									{
										if (elseCard[i] > 3)
										{
											boomtemp = i;
											break;
										}
									}
									if (boomtemp > 0 && FourIndex > 0)
									{
										Out[0] = Four[0];
										Out[1] = 4;
										Out[2] = 4;
										Out[4] = 0;
										Out[3] = 0;
										FourIndex--;
										for (int i = 0; i < FourIndex; ++i)
										{
											Four[i] = Four[i + 1];
										}
										return 1;
									}
									else if (KingBoom > 0 && OneIndex < 3)
									{
										Out[0] = 17;
										Out[1] = 2;
										Out[2] = 4;
										KingBoom = 0;
										return 1;
									}
									else if (FourIndex > 0)
									{
										Out[0] = Four[0];
										Out[1] = 4;
										Out[2] = 4;
										Out[4] = 0;
										Out[3] = 0;
										FourIndex--;
										for (int i = 0; i < FourIndex; ++i)
										{
											Four[i] = Four[i + 1];
										}
										return 1;
									}
									else
									{
										if (deckIndex > 0)
										{
											for (int i = 0; i < deckIndex; ++i)
											{
												if (deck[i][1] > 5)
												{
													Out[3] = deck[i][0];
													Out[4] = 1;
													deck[i][0]++;
													deck[i][1]--;
													flag = true;
													break;
												}
											}
										}
										else if (TwoIndex > 1)
										{
											Out[3] = Two[TwoIndex - 2];
											Out[4] = 1;
											Two[TwoIndex - 2] = Two[TwoIndex - 1];
											bool fg = false;
											flag = true;
											for (int i = 0; i < OneIndex; ++i)
											{
												if (One[i] > Out[3])
												{
													for (int j = OneIndex; j > i; j--)
													{
														One[j] = One[j - 1];
													}
													OneIndex++;
													One[i] = Out[3];
													fg = true;
													break;
												}
											}
											if (!fg)
											{
												One[OneIndex] = Out[3];
												OneIndex++;
											}
										}
										else if (TwoIndex == 1)
										{
											Out[3] = Two[TwoIndex - 1];
											Out[4] = 1;
											TwoIndex--;
											bool fg = false;
											flag = true;
											for (int i = 0; i < OneIndex; ++i)
											{
												if (One[i] > Out[3])
												{
													for (int j = OneIndex; j > i; j--)
													{
														One[j] = One[j - 1];
													}
													OneIndex++;
													One[i] = Out[3];
													fg = true;
													break;
												}
											}
											if (!fg)
											{
												One[OneIndex] = Out[3];
												OneIndex++;
											}
										}
										else if (ThreeIndex > 1 && ThreeIndex - 2 != temp)
										{
											Out[3] = Three[ThreeIndex - 2];
											Out[4] = 1;
											Three[ThreeIndex - 2] = Three[ThreeIndex - 1];
											ThreeIndex--;
											flag = true;
											bool fg = false;
											for (int i = 0; i < TwoIndex; ++i)
											{
												if (Two[i] > Out[3])
												{
													for (int j = TwoIndex; j > i; j--)
													{
														Two[j] = Two[j - 1];
													}
													Two[i] = Out[3];
													TwoIndex++;
													fg = true;
													break;
												}
											}
											if (!fg)
											{
												Two[TwoIndex] = Out[3];
												TwoIndex++;
											}
										}
										else if ((ThreeIndex == 1 && Three[0] < 15 && ThreeIndex != temp) || (ThreeIndex > 1 && ThreeIndex - 2 != temp))
										{
											Out[3] = Three[ThreeIndex - 1];
											Out[4] = 1;
											ThreeIndex--;
											flag = true;
											bool fg = false;
											for (int i = 0; i < TwoIndex; ++i)
											{
												if (Two[i] > Out[3])
												{
													for (int j = TwoIndex; j > i; j--)
													{
														Two[j] = Two[j - 1];
													}
													Two[i] = Out[3];
													TwoIndex++;
													fg = true;
													break;
												}
											}
											if (!fg)
											{
												Two[TwoIndex] = Out[3];
												TwoIndex++;
											}
										}
										else
										{

										}
									}
								}
								else if (WhoseOut == 1)
								{
									return -1;
								}
								else if (deckTwoIndex > 0)
								{
									for (int i = 0; i < deckTwoIndex; ++i)
									{
										if (deckTwo[i][1] > 3)
										{
											Out[3] = deckTwo[i][0];
											Out[4] = 2;
											flag = true;
											deckTwo[i][0]++;
											deckTwo[i][1]--;
											break;
										}
										else if (deckTwo[i][0]+ deckTwo[0][1] - 1 > 12 && i == deckTwoIndex - 1 )
										{
											Out[3] = deckTwo[i][0];
											Out[4] = 2;
											flag = true;
											bool fg = false;
											for (int j = 0; j < TwoIndex; ++j)
											{
												if (Two[j] > Out[3])
												{
													for (int k = TwoIndex; k > j; --k)
													{
														Two[k + 1] = Two[k - 1];
													}
													fg = true;
													Two[j] = deckTwo[i][0] + 1;
													Two[j + 1] = deckTwo[i][0] + 2;
													TwoIndex += 2;
													break;
												}
											}
											if (!fg)
											{
												Two[TwoIndex] = deckTwo[i][0] + 1;
												Two[TwoIndex + 1] = deckTwo[i][0] + 2;
												TwoIndex += 2;
											}
										}
										else
										{

										}
									}
								}
							}
						}
						else
						{
							flag = true;
						}
					}
					if (IsRes && flag)
					{
						if (temp < 10)
						{
							for (int i = temp; i < ThreeIndex; i++)
							{
								Three[i] = Three[i + 1];
							}
							ThreeIndex--;
						}
						else
						{
							temp -= 10;
							if (deckThree[temp][1] > 2)
							{
								deckThree[temp][1]--;
							}
							else
							{
								bool fg = false;
								for (int i = 0; i < ThreeIndex; ++i)
								{
									if (Three[i] > deckThree[temp][0])
									{
										for (int j = ThreeIndex; j > i; --j)
										{
											Three[j] = Three[j - 1];
										}
										Three[i] = deckThree[temp][0];
										ThreeIndex++;
										fg = true;
										break;
									}
								}
								if (!fg)
								{
									Three[ThreeIndex] = deckThree[temp][0];
									ThreeIndex++;
								}
								for (int i = temp; i < deckThreeIndex; ++i)
								{
									deckThree[i][1] = deckThree[i + 1][1];
									deckThree[i][0] = deckThree[i + 1][0];
								}
							}
						}
						return 1;
					}
					if (DZIndex == 2 && behindN < 4)
					{
						int boomtemp = -1;
						for (int i = 15; i > 2; i--)
						{
							if (elseCard[i] > 3)
							{
								boomtemp = i;
								break;
							}
						}
						if (boomtemp > 0 && FourIndex > 0)
						{
							Out[0] = Four[0];
							Out[1] = 4;
							Out[2] = 4;
							FourIndex--;
							for (int i = 0; i < FourIndex; ++i)
							{
								Four[i] = Four[i + 1];
							}
							return 1;
						}
						else if (KingBoom > 0)
						{
							Out[0] = 17;
							Out[1] = 2;
							Out[2] = 4;
							KingBoom = 0;
							return 1;
						}
						else if (FourIndex > 0)
						{
							Out[0] = Four[0];
							Out[1] = 4;
							Out[2] = 4;
							FourIndex--;
							for (int i = 0; i < FourIndex; ++i)
							{
								Four[i] = Four[i + 1];
							}
							return 1;
						}
					}
					return -1;
				}
			}
			else if (UpperCard[2] == 1)
			{
				
				for (int i = 0; i < deckIndex; ++i)
				{
					if (deck[i][0] > UpperCard[0] && deck[i][1] == UpperCard[1])
					{
						if (WhoseOut == 1 && (DZIndex == -1 || deck[i][0] > 7 || deck[i][0] > 6))
						{
							return -1;
						}
						Out[0] = deck[i][0];
						Out[1] = deck[i][1];
						Out[2] = 1;
						deckIndex--;
						for (int j = i; j < deckIndex; ++j)
						{
							deck[j][0] = deck[j + 1][0];
							deck[j][1] = deck[j + 1][1];
						}
						return 1;
					}
				}
				if (WhoseOut == 1 && ((DZIndex == -1) || (behindN > 9 && DZIndex == 2)))
				{
					return -1;
				}
				for (int i = 0; i < deckIndex; ++i)
				{
					if (deck[i][0] > UpperCard[0] && deck[i][1] == UpperCard[1] + 1)
					{
						int restOne = deck[i][0] + deck[i][1] - 1;
						for (int k = OneIndex; k > 0; --k)
						{
							//One[k-1] == restOne
							if (One[k - 1] > restOne)
							{
								One[k] = One[k - 1];
							}
							else
							{
								One[k] = restOne;
								break;
							}
						}
						OneIndex++;
						Out[0] = deck[i][0];
						Out[1] = deck[i][1] - 1;
						Out[2] = 1;
						deckIndex--;
						for (int j = i; j < deckIndex; ++j)
						{
							deck[j][0] = deck[j + 1][0];
							deck[j][1] = deck[j + 1][1];
						}
						return 1;
					}
					else if (deck[i][0] == UpperCard[0] && deck[i][1] == UpperCard[1] + 1)
					{
						int restOne = deck[i][0];
						for (int k = OneIndex; k > 0; --k)
						{
							//One[k-1] == restOne
							if (One[k - 1] > restOne)
							{
								One[k] = One[k - 1];
							}
							else
							{
								One[k] = restOne;
								break;
							}
						}
						OneIndex++;
						Out[0] = deck[i][0] + 1;
						Out[1] = deck[i][1] - 1;
						Out[2] = 1;
						deckIndex--;
						for (int j = i; j < deckIndex; ++j)
						{
							deck[j][0] = deck[j + 1][0];
							deck[j][1] = deck[j + 1][1];
						}
						return 1;
					}
				}
				if (DZIndex == 2 && behindN < 4)
				{
					int boomtemp = -1;
					for (int i = 15; i > 2; i--)
					{
						if (elseCard[i] > 3)
						{
							boomtemp = i;
							break;
						}
					}
					if (boomtemp > 0 && FourIndex > 0)
					{
						Out[0] = Four[0];
						Out[1] = 4;
						Out[2] = 4;
						FourIndex--;
						for (int i = 0; i < FourIndex; ++i)
						{
							Four[i] = Four[i + 1];
						}
						return 1;
					}
					else if (KingBoom > 0)
					{
						Out[0] = 17;
						Out[1] = 2;
						Out[2] = 4;
						KingBoom = 0;
						return 1;
					}
					else if (FourIndex > 0)
					{
						Out[0] = Four[0];
						Out[1] = 4;
						Out[2] = 4;
						FourIndex--;
						for (int i = 0; i < FourIndex; ++i)
						{
							Four[i] = Four[i + 1];
						}
						return 1;
					}
				}
				return -1;
			}
			else if (UpperCard[2] == 2)
			{
				for (int i = 0; i < deckTwoIndex; ++i)
				{
					if (deckTwo[i][0] > UpperCard[0] && deckTwo[i][1] == UpperCard[1])
					{
						if (WhoseOut == 1 && (DZIndex == -1 || deckTwo[i][0] > 8 || deckTwo[i][1] > 3))
						{
							return -1;
						}
						Out[0] = deckTwo[i][0];
						Out[1] = deckTwo[i][1];
						Out[2] = 2;
						deckTwoIndex--;
						for (int j = i; j < deckTwoIndex; ++j)
						{
							deckTwo[j][0] = deckTwo[j + 1][0];
							deckTwo[j][1] = deckTwo[j + 1][1];
						}
						return 1;
					}
				}
				if (WhoseOut == 1 && ((DZIndex == -1) || (behindN > 9 && DZIndex == 2)))
				{
					return -1;
				}
				for (int i = 0; i < deckTwoIndex; ++i)
				{
					if (deckTwo[i][0] > UpperCard[0] && deckTwo[i][1] == UpperCard[1] + 1)
					{
						int restTwo = deckTwo[i][0] + deckTwo[i][1] - 1;
						for (int k = TwoIndex; k > 0; --k)
						{
							//One[k-1] == restOne
							if (Two[k - 1] > restTwo)
							{
								Two[k] = Two[k - 1];
							}
							else
							{
								Two[k] = restTwo;
								break;
							}
						}
						TwoIndex++;
						Out[0] = deckTwo[i][0];
						Out[1] = deckTwo[i][1] - 1;
						Out[2] = 2;
						deckTwoIndex--;
						for (int j = i; j < deckTwoIndex; ++j)
						{
							deckTwo[j][0] = deckTwo[j + 1][0];
							deckTwo[j][1] = deckTwo[j + 1][1];
						}
						return 1;
					}
					else if (deckTwo[i][0] == UpperCard[0] && deckTwo[i][1] == UpperCard[1] + 1)
					{
						int restTwo = deckTwo[i][0];
						for (int k = TwoIndex; k > 0; --k)
						{
							//One[k-1] == restOne
							if (Two[k - 1] > restTwo)
							{
								Two[k] = Two[k - 1];
							}
							else
							{
								Two[k] = restTwo;
								break;
							}
						}
						TwoIndex++;
						Out[0] = deckTwo[i][0] + 1;
						Out[1] = deckTwo[i][1] - 1;
						Out[2] = 2;
						deckTwoIndex--;
						for (int j = i; j < deckTwoIndex; ++j)
						{
							deckTwo[j][0] = deckTwo[j + 1][0];
							deckTwo[j][1] = deckTwo[j + 1][1];
						}
						return 1;
					}
				}
				if (DZIndex == 2 && behindN < 4)
				{
					int boomtemp = -1;
					for (int i = 15; i > 2; i--)
					{
						if (elseCard[i] > 3)
						{
							boomtemp = i;
							break;
						}
					}
					if (boomtemp > 0 && FourIndex > 0)
					{
						Out[0] = Four[0];
						Out[1] = 4;
						Out[2] = 4;
						FourIndex--;
						for (int i = 0; i < FourIndex; ++i)
						{
							Four[i] = Four[i + 1];
						}
						return 1;
					}
					else if (KingBoom > 0)
					{
						Out[0] = 17;
						Out[1] = 2;
						Out[2] = 4;
						KingBoom = 0;
						return 1;
					}
					else if (FourIndex > 0)
					{
						Out[0] = Four[0];
						Out[1] = 4;
						Out[2] = 4;
						FourIndex--;
						for (int i = 0; i < FourIndex; ++i)
						{
							Four[i] = Four[i + 1];
						}
						return 1;
					}
				}
				return -1;
			}
			else if (UpperCard[2] == 3)
			{
				if (WhoseOut == 1 && ((DZIndex == -1) || (DZIndex == 2 && (behindN > 8 || UpperCard[0] > 9 || UpperCard[1] > 2))))
				{
					return -1;
				}
				bool IsRes = false;
				int chai = 0;
				int chaiThree;
				for (int i = 0; i < deckThreeIndex; ++i)
				{
					if (UpperCard[0] < deckThree[i][0] && UpperCard[1] <= deckThree[i][1])
					{
						Out[0] = deckThree[i][0];
						Out[1] = UpperCard[1];
						Out[2] = 3;
						deckThreeIndex--;
						if (deckThree[i][1] - UpperCard[1] >= 2)
						{
							chai = 1;
							deckThree[i][0] = deckThree[i][0] + UpperCard[1] - 1;
							deckThree[i][1] = deckThree[i][1] - UpperCard[1];
						}
						else
						{
							if (deckThree[i][1] - UpperCard[1] > 0)
							{
								chai = 2;
								for (int j = 0; j < ThreeIndex; j++)
								{
									if (Three[j] > Out[0])
									{
										for (int k = ThreeIndex; k > j; --k)
										{
											Three[k - 1 + deckThree[i][1] - UpperCard[1]] = Three[k - 1];
										}
										ThreeIndex += deckThree[i][1] - UpperCard[1];
										for (int k = 0; k < deckThree[i][1] - UpperCard[1]; ++k)
										{
											Three[j + k] = deckThree[i][0] + UpperCard[1] + k;
										}
										chaiThree = j;
										break;
									}
								}
							}
							for (int j = i; j < deckThreeIndex; ++j)
							{
								deckThree[j][0] = deckThree[j + 1][0];
								deckThree[j][1] = deckThree[j + 1][1];
							}
						}
						IsRes = true;
						break;
					}
				}
				if (IsRes == true)
				{
					if (UpperCard[4] == 2)//������
					{
						int temp = UpperCard[1];
						//���ţ����Գ�����UpperCard[1]
						if (TwoIndex >= UpperCard[1] && Two[UpperCard[1]] < 14)
						{
							Out[3] = Two[0];
							Out[4] = 2;
							for (int i = 1; i < temp; ++i)
							{
								Out[4 + i] = Two[i];
							}
							TwoIndex -= temp;
							for (int i = 0; i < TwoIndex; ++i)
							{
								Two[i] = Two[i + temp];
							}
							return 1;
						}
						else if (deckTwoIndex > 0)
						{
							for (int k = TwoIndex; k > 0; --k)
							{
								if (Two[k - 1] > deckTwo[0][0])
								{
									Two[k - 1 + deckTwo[0][1]] = Two[k - 1];
								}
								else
								{
									for (int j = 0; j < deckTwo[0][1]; j++)
									{
										Two[k + j] = deckTwo[0][0] + j;
									}
									break;
								}
							}
							TwoIndex += deckTwo[0][1];
							for (int i = 0; i < deckTwoIndex; ++i)
							{
								deckTwo[i][1] = deckTwo[i + 1][1];
								deckTwo[i][0] = deckTwo[i + 1][0];
							}
							deckTwoIndex--;
							Out[3] = Two[0];
							Out[4] = 2;
							for (int i = 1; i < Out[1]; i++)
							{
								Out[4 + i] = Two[i + 1];
							}
							for (int i = 0; i < TwoIndex; i++)
							{
								Two[i] = Two[i + Out[1]];
							}
							TwoIndex -= Out[1];
							return 1;
						}
						else
						{
							return -1;
						}
					}
					else if (UpperCard[4] == 1)
					{
						int temp = UpperCard[1];
						//
						if (OneIndex >= UpperCard[1] && One[UpperCard[1] - 1] < 16)
						{
							Out[3] = One[0];
							Out[4] = 1;
							for (int i = 1; i < temp; ++i)
							{
								Out[4 + i] = One[i];
							}
							OneIndex -= temp;
							for (int i = 0; i < OneIndex; ++i)
							{
								One[i] = One[i + temp];
							}
							return 1;
						}
						else
						{

						}
					}
				}
				if (DZIndex == 2 && behindN < 4)
				{
					int boomtemp = -1;
					for (int i = 15; i > 2; i--)
					{
						if (elseCard[i] > 3)
						{
							boomtemp = i;
							break;
						}
					}
					if (boomtemp > 0 && FourIndex > 0)
					{
						Out[0] = Four[0];
						Out[1] = 4;
						Out[2] = 4;
						FourIndex--;
						for (int i = 0; i < FourIndex; ++i)
						{
							Four[i] = Four[i + 1];
						}
						return 1;
					}
					else if (KingBoom > 0)
					{
						Out[0] = 17;
						Out[1] = 2;
						Out[2] = 4;
						KingBoom = 0;
						return 1;
					}
					else if (FourIndex > 0)
					{
						Out[0] = Four[0];
						Out[1] = 4;
						Out[2] = 4;
						FourIndex--;
						for (int i = 0; i < FourIndex; ++i)
						{
							Four[i] = Four[i + 1];
						}
						return 1;
					}
				}
				return -1;
			}
			else if (UpperCard[2] == 4)//  �Ĵ�2 //���Ż���Ŀǰֱ��ը//���Ĵ����ˣ�˵��ũ����̓�������߱�Ӯ�ˣ�����ֱ��ը��
			{
				if (UpperCard[0] == 17 || WhoseOut == 1)
				{
					return -1;
				}
				bool boom = false;
				bool ok = false;
				bool BB = false;
				if (FourIndex > 0)
				{
					boom = true;
				}
				if (UpperCard[4] == 1 && boom == true)
				{
					if (OneIndex > 1 && One[1] < 14)
					{
						Out[3] = One[0];
						Out[4] = 1;
						Out[5] = One[1];
						for (int i = 0; i < OneIndex; i++)
						{
							One[i] = One[i + 2];
						}
						OneIndex -= 2;
						ok = true;
					}
					else if (OneIndex == 1 && One[0] < 14)
					{
						if (TwoIndex > 0 && Two[0] < 14)
						{
							if (One[0] > Two[0])
							{
								Out[3] = Two[0];
								Out[4] = 1;
								Out[5] = Two[0];
								TwoIndex--;
								for (int i = 0; i < TwoIndex; i++)
								{
									Two[i] = Two[i + 1];
								}
								ok = true;
							}
							else
							{
								Out[3] = One[0];
								Out[4] = 1;
								Out[5] = Two[0];
								One[0] = Two[0];
								TwoIndex--;
								for (int i = 0; i < TwoIndex; i++)
								{
									Two[i] = Two[i + 1];
								}
								ok = true;
							}
						}
					}
					else if (TwoIndex > 0 && Two[0] < 14)
					{
						Out[3] = Two[0];
						Out[4] = 1;
						Out[5] = Two[0];
						TwoIndex--;
						for (int i = 0; i < TwoIndex; i++)
						{
							Two[i] = Two[i + 1];
						}
						ok = true;
					}
					else
					{

					}
				}
				else if (UpperCard[4] == 2 && boom == true)
				{
					if (TwoIndex > 1 && Two[1] < 14)
					{
						Out[3] = Two[0];
						Out[4] = 2;
						Out[5] = Two[1];
						TwoIndex -= 2;
						for (int i = 0; i < TwoIndex; i++)
						{
							Two[i] = Two[i + 2];
						}
						ok = true;
					}
				}
				else
				{
					BB = true;
				}
				if (ok == true || (BB == true && KingBoom == 0))
				{
					for (int i = 0; i < FourIndex; i++)
					{
						if (Four[i] > UpperCard[0])
						{
							Out[0] = Four[i];
							Out[1] = 4;
							Out[2] = 4;
							FourIndex--;
							for (int j = i; j < FourIndex; ++j)
							{
								Four[j] = Four[j + 1];
							}
						}
					}
					return 1;
				}
				if (KingBoom == 1)
				{
					Out[0] = 17;
					Out[1] = 2;
					Out[2] = 4;
					Out[3] = 0;
					Out[4] = 0;
					Out[5] = 0;
					KingBoom = 0;
					return 1;
				}
				if (FourIndex > 0 && UpperCard[4] > 0)
				{
					for (int i = 0; i < FourIndex; i++)
					{

						Out[0] = Four[i];
						Out[1] = 4;
						Out[2] = 4;
						Out[3] = 0;
						Out[4] = 0;
						Out[5] = 0;
						FourIndex--;
						for (int j = i; j < FourIndex; j++)
						{
							Four[j] = Four[j + 1];
						}
						return 1;
					}
				}
				return -1;
			}
			else
			{
				return -1;
			}
		}
		//------------�����ϼ�����ũ��
		else
		{
			if (UpperCard[2] == 0)
			{
				if (UpperCard[1] == 1)
				{
					if (OneIndex > 0 && (myN == 1 || (MyRoundNum == 2 && One[OneIndex - 1] > OneElseMax)) && One[OneIndex - 1] > UpperCard[0])
					{
						Out[0] = One[OneIndex - 1];
						Out[1] = 1;
						Out[2] = 0;
						OneIndex--;
						return 1;
					}
					if (OneIndex > 0)
					{
						if (MyRoundNum < 3 && OneIndex + TwoIndex < 3 && One[OneIndex - 1] >= OneElseMax)
						{
							bool ISOK = false;
							for(int i = 0;i < OneIndex;++i)
							{
								if(One[i] > 7 && One[i] > UpperCard[0])
								{
									Out[0] = One[i];
									Out[1] = 1;
									Out[2] = 0;
									OneIndex--;
									for(;i < OneIndex;++i)
									{
										One[i]=One[i+1];
									}
									return 1;
								}
							}
							for(int i = 0;i < OneIndex;++i)
							{
								if(One[i] > UpperCard[0])
								{
									Out[0] = One[i];
									Out[1] = 1;
									Out[2] = 0;
									OneIndex--;
									for(;i < OneIndex;++i)
									{
										One[i]=One[i+1];
									}
									return 1;
								}
							}
						}
						for (int i = 0; i < OneIndex; ++i)
						{
							if (One[i] > UpperCard[0])
							{
								if (WhoseOut == 1 && (DZIndex == -1 || UpperCard[0] > 13))
								{
									return -1;
								}
								Out[0] = One[i];
								Out[1] = 1;
								Out[2] = 0;
								OneIndex--;
								for (int j = i; j < OneIndex; ++j)
								{
									One[j] = One[j + 1];
								}
								return 1;
							}
						}
					}
					if (WhoseOut == 1 && (UpperCard[0] > 13 || behindN > 8))
					{
						return -1;
					}
					else
					{
						int MaxRestC = 0, IsHave = 0;
						for (int i = 15; i >= 3; --i)
						{
							if (myCard[i] > 0)
							{
								MaxRestC = i;
								IsHave = 1;
							}
							if (elseCard[i] > 0)
							{
								MaxRestC = i;
								break;
							}
						}
						if (UpperCard[0] >= MaxRestC)
						{
							MaxRestC = UpperCard[0] + 1;
						}
						if (deckIndex > 0 && (IsHave > 0 || behindN < 9))
						{
							for (int i = 0; i < deckIndex; ++i)
							{
								if (deck[i][1] > 5 && deck[i][0] + deck[i][1] - 1 >= MaxRestC)
								{
									Out[0] = deck[i][0] + deck[i][1] - 1;
									Out[1] = 1;
									Out[2] = 0;
									deck[i][1]--;
									return 1;
								}
							}
						}
						if (TwoIndex > 0 && (IsHave > 0 || behindN < 5))
						{
							for (int i = 0; i < TwoIndex; ++i)
							{
								if (Two[i] >= MaxRestC)
								{
									Out[0] = Two[i];
									Out[1] = 1;
									Out[2] = 0;
									TwoIndex--;
									int IsADD = 0;
									for (int j = 0; j < OneIndex; j++)
									{
										if (One[j] > Out[0])
										{
											for (int k = OneIndex; k > j; --k)
											{
												One[k] = One[k - 1];
											}
											++OneIndex;
											One[j] = Out[0];
											IsADD = 1;
										}
									}
									if(IsADD == 0)
									{
										One[OneIndex] = Out[0];
										OneIndex++;
									}
									return 1;
								}
							}
						}
						if (ThreeIndex > 0 && (IsHave > 0 || behindN < 6))
						{
							for (int i = 0; i < ThreeIndex; ++i)
							{
								if (Three[i] >= MaxRestC)
								{
									Out[0] = Three[i];
									Out[1] = 1;
									Out[2] = 0;
									ThreeIndex--;
									for (int j = 0; j < TwoIndex; j++)
									{
										if (Two[j] > Out[0])
										{
											for (int k = TwoIndex; k > j; --k)
											{
												Two[k] = Two[k - 1];
											}
											++TwoIndex;
											Two[j] = Out[0];
										}
									}
									return 1;
								}
							}
						}
					}
				}
				else if (UpperCard[1] == 2)
				{
					if (TwoIndex > 0)
					{
						if (TwoIndex > 0 && (myN == 2 || (MyRoundNum == 2 && Two[TwoIndex - 1] >= TwoElseMax)) && Two[TwoIndex - 1] > UpperCard[0])
						{
							Out[0] = Two[TwoIndex - 1];
							Out[1] = 2;
							Out[2] = 0;
							TwoIndex--;
							return 1;
						}
						if (TwoIndex > 0 && MyRoundNum < 3 && OneIndex + TwoIndex < 3 && Two[TwoIndex - 1] >= TwoElseMax)
						{
							if (Two[TwoIndex - 1] > UpperCard[0])
							{
								if (WhoseOut == 1 && (DZIndex == -1 || Two[TwoIndex - 1] > 12))
								{
									return -1;
								}
								Out[0] = Two[TwoIndex - 1];
								Out[1] = 2;
								Out[2] = 0;
								TwoIndex--;
								return 1;
							}
						}
						for (int i = 0; i < TwoIndex; ++i)
						{
							if (Two[i] > UpperCard[0])
							{
								if (WhoseOut == 1 && (DZIndex == -1 || Two[TwoIndex - 1] > 13))
								{
									return -1;
								}
								Out[0] = Two[i];
								Out[1] = 2;
								Out[2] = 0;
								TwoIndex--;
								for (int j = i; j < TwoIndex; ++j)
								{
									Two[j] = Two[j + 1];
								}
								return 1;
							}
						}
					}
					//gai
					if (WhoseOut == 1 && (UpperCard[0] > 12 || behindN > 8))
					{
						return -1;
					}
					// �����ٲ�
					int MaxRestC = 0, IsHave = 0;
					for (int i = 15; i >= 3; --i)
					{
						if (myCard[i] > 1)
						{
							MaxRestC = i;
							IsHave = 1;
						}
						if (elseCard[i] > 1)
						{
							MaxRestC = i;
							break;
						}
					}
					if (UpperCard[0] >= MaxRestC)
					{
						MaxRestC = UpperCard[0] + 1;
					}
					if (deckTwoIndex > 0 && (IsHave > 0 || behindN < 9))
					{
						for (int i = 0; i < deckTwoIndex; ++i)
						{
							if (deckTwo[i][1] > 3 && deckTwo[i][0] + deckTwo[i][1] - 1 >= MaxRestC)
							{
								Out[0] = deckTwo[i][0] + deckTwo[i][1] - 1;
								Out[1] = 2;
								Out[2] = 0;
								deckTwo[i][1]--;
								return 1;
							}
						}
					}
					if (ThreeIndex > 0 && (IsHave > 0 || behindN < 9))
					{
						for (int i = 0; i < ThreeIndex; ++i)
						{
							if (Three[i] >= MaxRestC)
							{
								Out[0] = Three[i];
								Out[1] = 2;
								Out[2] = 0;
								ThreeIndex--;
								return 1;
							}
						}
					}
				}
				else//UpperCard[3] ==3
				{
					if (WhoseOut == 1 && (UpperCard[0] > 10 || behindN > 8))
					{
						return -1;
					}
					bool IsRes = false;
					bool flag = false;
					int temp = 0;
					for (int i = 0; i < ThreeIndex; ++i)
					{
						if (Three[i] > UpperCard[0])
						{
							Out[0] = Three[i];
							Out[1] = 3;
							Out[2] = 0;
							temp = i;
							IsRes = true;
							break;
						}
					}
					//�ɻ����
					if (IsRes == false)
					{
						for (int i = 0; i < deckThreeIndex; ++i)
						{
							if (deckThree[i][0] + deckThree[i][1] - 1 > UpperCard[0])
							{
								Out[0] = deckThree[i][0] + deckThree[i][1] - 1;
								Out[1] = 3;
								Out[2] = 0;
								temp = 10 + i;
								IsRes = true;
								break;
							}
						}
					}
					//************���� 0,1,2
					if (IsRes == true)
					{
						if (UpperCard[4] == 1)
						{
							if (OneIndex > 0 && One[0] < 13)
							{
								Out[4] = 1;
								Out[3] = One[0];
								OneIndex++;
								for (int i = 0; i < OneIndex; ++i)
								{
									One[i] = One[i + 1];
								}
								flag = true;
							}
							else//�ص��Ż�//˼���Ƿ�һ��Ҫѹ������ӻ��ǲ�˳�ӻ��ǲ����������������//������˳�ӣ���������
							{
								if (WhoseOut == -1 && frontN < 5)
								{
									int boomtemp = -1;
									for (int i = 15; i > 2; i--)
									{
										if (elseCard[i] > 3)
										{
											boomtemp = i;
											break;
										}
									}
									if (boomtemp > 0 && FourIndex > 0)
									{
										Out[0] = Four[0];
										Out[1] = 4;
										Out[2] = 4;
										Out[4] = 0;
										Out[3] = 0;
										FourIndex--;
										for (int i = 0; i < FourIndex; ++i)
										{
											Four[i] = Four[i + 1];
										}
										return 1;
									}
									else if (KingBoom > 0 && OneIndex < 3)
									{
										Out[0] = 17;
										Out[1] = 2;
										Out[2] = 4;
										KingBoom = 0;
										return 1;
									}
									else if (FourIndex > 0)
									{
										Out[0] = Four[0];
										Out[1] = 4;
										Out[2] = 4;
										Out[4] = 0;
										Out[3] = 0;
										FourIndex--;
										for (int i = 0; i < FourIndex; ++i)
										{
											Four[i] = Four[i + 1];
										}
										return 1;
									}
									else
									{
										if (deckIndex > 0)
										{
											for (int i = 0; i < deckIndex; ++i)
											{
												if (deck[i][1] > 5)
												{
													Out[3] = deck[i][0];
													Out[4] = 1;
													deck[i][0]++;
													deck[i][1]--;
													flag = true;
													break;
												}
											}
										}
										else if (TwoIndex > 1)
										{
											Out[3] = Two[TwoIndex - 2];
											Out[4] = 1;
											Two[TwoIndex - 2] = Two[TwoIndex - 1];
											bool fg = false;
											flag = true;
											for (int i = 0; i < OneIndex; ++i)
											{
												if (One[i] > Out[3])
												{
													for (int j = OneIndex; j > i; j--)
													{
														One[j] = One[j - 1];
													}
													OneIndex++;
													One[i] = Out[3];
													fg = true;
													break;
												}
											}
											if (!fg)
											{
												One[OneIndex] = Out[3];
												OneIndex++;
											}
										}
										else if (TwoIndex == 1)
										{
											Out[3] = Two[TwoIndex - 1];
											Out[4] = 1;
											TwoIndex--;
											bool fg = false;
											flag = true;
											for (int i = 0; i < OneIndex; ++i)
											{
												if (One[i] > Out[3])
												{
													for (int j = OneIndex; j > i; j--)
													{
														One[j] = One[j - 1];
													}
													OneIndex++;
													One[i] = Out[3];
													fg = true;
													break;
												}
											}
											if (!fg)
											{
												One[OneIndex] = Out[3];
												OneIndex++;
											}
										}
										else if (ThreeIndex > 1 && ThreeIndex - 2 != temp)
										{
											Out[3] = Three[ThreeIndex - 2];
											Out[4] = 1;
											Three[ThreeIndex - 2] = Three[ThreeIndex - 1];
											ThreeIndex--;
											flag = true;
											bool fg = false;
											for (int i = 0; i < TwoIndex; ++i)
											{
												if (Two[i] > Out[3])
												{
													for (int j = TwoIndex; j > i; j--)
													{
														Two[j] = Two[j - 1];
													}
													Two[i] = Out[3];
													TwoIndex++;
													fg = true;
													break;
												}
											}
											if (!fg)
											{
												Two[TwoIndex] = Out[3];
												TwoIndex++;
											}
										}
										else if ((ThreeIndex == 1 && Three[0] < 15 && ThreeIndex != temp) || (ThreeIndex > 1 && ThreeIndex - 2 != temp))
										{
											Out[3] = Three[ThreeIndex - 1];
											Out[4] = 1;
											ThreeIndex--;
											flag = true;
											bool fg = false;
											for (int i = 0; i < TwoIndex; ++i)
											{
												if (Two[i] > Out[3])
												{
													for (int j = TwoIndex; j > i; j--)
													{
														Two[j] = Two[j - 1];
													}
													Two[i] = Out[3];
													TwoIndex++;
													fg = true;
													break;
												}
											}
											if (!fg)
											{
												Two[TwoIndex] = Out[3];
												TwoIndex++;
											}
										}
										else
										{

										}
									}
								}
								else if (WhoseOut == 1)
								{
									return -1;
								}
								else if (OneIndex > 0 && One[0] < 15)
								{
									Out[4] = 1;
									Out[3] = One[0];
									OneIndex++;
									for (int i = 0; i < OneIndex; ++i)
									{
										One[i] = One[i + 1];
									}
									flag = true;
								}
								else if (deckIndex > 0)
								{
									for (int i = 0; i < deckIndex; ++i)
									{
										if (deck[i][1] > 5)
										{
											Out[3] = deck[i][0];
											Out[4] = 1;
											deck[i][0]++;
											deck[i][1]--;
											flag = true;
											break;
										}
									}
								}
								else if (TwoIndex > 1)
								{
									Out[3] = Two[TwoIndex - 2];
									Out[4] = 1;
									Two[TwoIndex - 2] = Two[TwoIndex - 1];
									bool fg = false;
									flag = true;
									for (int i = 0; i < OneIndex; ++i)
									{
										if (One[i] > Out[3])
										{
											for (int j = OneIndex; j > i; j--)
											{
												One[j] = One[j - 1];
											}
											OneIndex++;
											One[i] = Out[3];
											fg = true;
											break;
										}
									}
									if (!fg)
									{
										One[OneIndex] = Out[3];
										OneIndex++;
									}
								}
								else if (TwoIndex == 1)
								{
									Out[3] = Two[TwoIndex - 1];
									Out[4] = 1;
									TwoIndex--;
									bool fg = false;
									flag = true;
									for (int i = 0; i < OneIndex; ++i)
									{
										if (One[i] > Out[3])
										{
											for (int j = OneIndex; j > i; j--)
											{
												One[j] = One[j - 1];
											}
											OneIndex++;
											One[i] = Out[3];
											fg = true;
											break;
										}
									}
									if (!fg)
									{
										One[OneIndex] = Out[3];
										OneIndex++;
									}
								}
								else
								{

								}
							}
						}
						else if (UpperCard[4] == 2)
						{
							if (TwoIndex > 0 && (Two[0] < 13 || behindN < 6))
							{
								Out[4] = 2;
								Out[3] = Two[0];
								TwoIndex++;
								for (int i = 0; i < TwoIndex; ++i)
								{
									Two[i] = Two[i + 1];
								}
								flag = true;
							}
							else
							{
								if (WhoseOut == -1 && behindN < 5)
								{
									int boomtemp = -1;
									for (int i = 15; i > 2; i--)
									{
										if (elseCard[i] > 3)
										{
											boomtemp = i;
											break;
										}
									}
									if (boomtemp > 0 && FourIndex > 0)
									{
										Out[0] = Four[0];
										Out[1] = 4;
										Out[2] = 4;
										Out[4] = 0;
										Out[3] = 0;
										FourIndex--;
										for (int i = 0; i < FourIndex; ++i)
										{
											Four[i] = Four[i + 1];
										}
										return 1;
									}
									else if (KingBoom > 0 && OneIndex < 3)
									{
										Out[0] = 17;
										Out[1] = 2;
										Out[2] = 4;
										KingBoom = 0;
										return 1;
									}
									else if (FourIndex > 0)
									{
										Out[0] = Four[0];
										Out[1] = 4;
										Out[2] = 4;
										Out[4] = 0;
										Out[3] = 0;
										FourIndex--;
										for (int i = 0; i < FourIndex; ++i)
										{
											Four[i] = Four[i + 1];
										}
										return 1;
									}
									else
									{
										if (deckIndex > 0)
										{
											for (int i = 0; i < deckIndex; ++i)
											{
												if (deck[i][1] > 5)
												{
													Out[3] = deck[i][0];
													Out[4] = 1;
													deck[i][0]++;
													deck[i][1]--;
													flag = true;
													break;
												}
											}
										}
										else if (TwoIndex > 1)
										{
											Out[3] = Two[TwoIndex - 2];
											Out[4] = 1;
											Two[TwoIndex - 2] = Two[TwoIndex - 1];
											bool fg = false;
											flag = true;
											for (int i = 0; i < OneIndex; ++i)
											{
												if (One[i] > Out[3])
												{
													for (int j = OneIndex; j > i; j--)
													{
														One[j] = One[j - 1];
													}
													OneIndex++;
													One[i] = Out[3];
													fg = true;
													break;
												}
											}
											if (!fg)
											{
												One[OneIndex] = Out[3];
												OneIndex++;
											}
										}
										else if (TwoIndex == 1)
										{
											Out[3] = Two[TwoIndex - 1];
											Out[4] = 1;
											TwoIndex--;
											bool fg = false;
											flag = true;
											for (int i = 0; i < OneIndex; ++i)
											{
												if (One[i] > Out[3])
												{
													for (int j = OneIndex; j > i; j--)
													{
														One[j] = One[j - 1];
													}
													OneIndex++;
													One[i] = Out[3];
													fg = true;
													break;
												}
											}
											if (!fg)
											{
												One[OneIndex] = Out[3];
												OneIndex++;
											}
										}
										else if (ThreeIndex > 1 && ThreeIndex - 2 != temp)
										{
											Out[3] = Three[ThreeIndex - 2];
											Out[4] = 1;
											Three[ThreeIndex - 2] = Three[ThreeIndex - 1];
											ThreeIndex--;
											flag = true;
											bool fg = false;
											for (int i = 0; i < TwoIndex; ++i)
											{
												if (Two[i] > Out[3])
												{
													for (int j = TwoIndex; j > i; j--)
													{
														Two[j] = Two[j - 1];
													}
													Two[i] = Out[3];
													TwoIndex++;
													fg = true;
													break;
												}
											}
											if (!fg)
											{
												Two[TwoIndex] = Out[3];
												TwoIndex++;
											}
										}
										else if ((ThreeIndex == 1 && Three[0] < 15 && ThreeIndex != temp) || (ThreeIndex > 1 && ThreeIndex - 2 != temp))
										{
											Out[3] = Three[ThreeIndex - 1];
											Out[4] = 1;
											ThreeIndex--;
											flag = true;
											bool fg = false;
											for (int i = 0; i < TwoIndex; ++i)
											{
												if (Two[i] > Out[3])
												{
													for (int j = TwoIndex; j > i; j--)
													{
														Two[j] = Two[j - 1];
													}
													Two[i] = Out[3];
													TwoIndex++;
													fg = true;
													break;
												}
											}
											if (!fg)
											{
												Two[TwoIndex] = Out[3];
												TwoIndex++;
											}
										}
										else
										{

										}
									}
								}
								else if (WhoseOut == 1)
								{
									return -1;
								}
								else if (deckTwoIndex > 0)
								{
									for (int i = 0; i < deckTwoIndex; ++i)
									{
										if (deckTwo[i][1] > 3)
										{
											Out[3] = deckTwo[i][0];
											Out[4] = 2;
											flag = true;
											deckTwo[i][0]++;
											deckTwo[i][1]--;
											break;
										}
										else if (deckTwo[i][0]+ deckTwo[i][1] - 1 > 12 && i == deckTwoIndex - 1 && (frontN < 5 || behindN < 5))
										{
											Out[3] = deckTwo[i][0];
											Out[4] = 2;
											flag = true;
											bool fg = false;
											for (int j = 0; j < TwoIndex; ++j)
											{
												if (Two[j] > Out[3])
												{
													for (int k = TwoIndex; k > j; --k)
													{
														Two[k + 1] = Two[k - 1];
													}
													fg = true;
													Two[j] = deckTwo[i][0] + 1;
													Two[j + 1] = deckTwo[i][0] + 2;
													TwoIndex += 2;
													break;
												}
											}
											if (!fg)
											{
												Two[TwoIndex] = deckTwo[i][0] + 1;
												Two[TwoIndex + 1] = deckTwo[i][0] + 2;
												TwoIndex += 2;
											}
										}
										else
										{

										}
									}
								}
							}
						}
						else
						{
							flag = true;
						}
					}
					if (IsRes && flag)
					{
						if (temp < 10)
						{
							for (int i = temp; i < ThreeIndex; i++)
							{
								Three[i] = Three[i + 1];
							}
							ThreeIndex--;
						}
						else
						{
							temp -= 10;
							if (deckThree[temp][1] > 2)
							{
								deckThree[temp][1]--;
							}
							else
							{
								bool fg = false;
								for (int i = 0; i < ThreeIndex; ++i)
								{
									if (Three[i] > deckThree[temp][0])
									{
										for (int j = ThreeIndex; j > i; --j)
										{
											Three[j] = Three[j - 1];
										}
										Three[i] = deckThree[temp][0];
										ThreeIndex++;
										fg = true;
										break;
									}
								}
								if (!fg)
								{
									Three[ThreeIndex] = deckThree[temp][0];
									ThreeIndex++;
								}
								for (int i = temp; i < deckThreeIndex; ++i)
								{
									deckThree[i][1] = deckThree[i + 1][1];
									deckThree[i][0] = deckThree[i + 1][0];
								}
							}
						}
						return 1;
					}
					if (behindN < 4)
					{
						int boomtemp = -1;
						for (int i = 15; i > 2; i--)
						{
							if (elseCard[i] > 3)
							{
								boomtemp = i;
								break;
							}
						}
						if (boomtemp > 0 && FourIndex > 0)
						{
							Out[0] = Four[0];
							Out[1] = 4;
							Out[2] = 4;
							FourIndex--;
							for (int i = 0; i < FourIndex; ++i)
							{
								Four[i] = Four[i + 1];
							}
							return 1;
						}
						else if (KingBoom > 0 && OneIndex < 3)
						{
							Out[0] = 17;
							Out[1] = 2;
							Out[2] = 4;
							KingBoom = 0;
							return 1;
						}
						else if (FourIndex > 0)
						{
							Out[0] = Four[0];
							Out[1] = 4;
							Out[2] = 4;
							FourIndex--;
							for (int i = 0; i < FourIndex; ++i)
							{
								Four[i] = Four[i + 1];
							}
							return 1;
						}
					}
					return -1;
				}
				if (behindN < 5)
				{
					int boomtemp = -1;
					for (int i = 15; i > 2; i--)
					{
						if (elseCard[i] > 3)
						{
							boomtemp = i;
							break;
						}
					}
					if (boomtemp > 0 && FourIndex > 0)
					{
						Out[0] = Four[0];
						Out[1] = 4;
						Out[2] = 4;
						FourIndex--;
						for (int i = 0; i < FourIndex; ++i)
						{
							Four[i] = Four[i + 1];
						}
						return 1;
					}
					else if (KingBoom > 0 && OneIndex < 3)
					{
						Out[0] = 17;
						Out[1] = 2;
						Out[2] = 4;
						KingBoom = 0;
						return 1;
					}
					else if (FourIndex > 0)
					{
						Out[0] = Four[0];
						Out[1] = 4;
						Out[2] = 4;
						FourIndex--;
						for (int i = 0; i < FourIndex; ++i)
						{
							Four[i] = Four[i + 1];
						}
						return 1;
					}
				}
				return -1;
			}
			else if (UpperCard[2] == 1)
			{
				for (int i = 0; i < deckIndex; ++i)
				{
					if (deck[i][0] > UpperCard[0] && deck[i][1] == UpperCard[1])
					{
						if (WhoseOut == 1 && deck[i][0] > 6)
						{
							return -1;
						}
						Out[0] = deck[i][0];
						Out[1] = deck[i][1];
						Out[2] = 1;
						deckIndex--;
						for (int j = i; j < deckIndex; ++j)
						{
							deck[j][0] = deck[j + 1][0];
							deck[j][1] = deck[j + 1][1];
						}
						return 1;
					}
				}
				if (WhoseOut == 1 && (UpperCard[0] > 8 || behindN > 10 || UpperCard[1] > 6))
				{
					return -1;
				}
				for (int i = 0; i < deckIndex; ++i)
				{
					if (deck[i][0] > UpperCard[0] && deck[i][1] == UpperCard[1] + 1)
					{
						int restOne = deck[i][0] + deck[i][1] - 1;
						for (int k = OneIndex; k > 0; --k)
						{
							//One[k-1] == restOne
							if (One[k - 1] > restOne)
							{
								One[k] = One[k - 1];
							}
							else
							{
								One[k] = restOne;
								break;
							}
						}
						OneIndex++;
						Out[0] = deck[i][0];
						Out[1] = deck[i][1] - 1;
						Out[2] = 1;
						deckIndex--;
						for (int j = i; j < deckIndex; ++j)
						{
							deck[j][0] = deck[j + 1][0];
							deck[j][1] = deck[j + 1][1];
						}
						return 1;
					}
					else if (deck[i][0] == UpperCard[0] && deck[i][1] == UpperCard[1] + 1)
					{
						int restOne = deck[i][0];
						for (int k = OneIndex; k > 0; --k)
						{
							//One[k-1] == restOne
							if (One[k - 1] > restOne)
							{
								One[k] = One[k - 1];
							}
							else
							{
								One[k] = restOne;
								break;
							}
						}
						OneIndex++;
						Out[0] = deck[i][0] + 1;
						Out[1] = deck[i][1] - 1;
						Out[2] = 1;
						deckIndex--;
						for (int j = i; j < deckIndex; ++j)
						{
							deck[j][0] = deck[j + 1][0];
							deck[j][1] = deck[j + 1][1];
						}
						return 1;
					}
				}
				if (behindN < 5)
				{
					int boomtemp = -1;
					for (int i = 15; i > 2; i--)
					{
						if (elseCard[i] > 3)
						{
							boomtemp = i;
							break;
						}
					}
					if (boomtemp > 0 && FourIndex > 0)
					{
						Out[0] = Four[0];
						Out[1] = 4;
						Out[2] = 4;
						FourIndex--;
						for (int i = 0; i < FourIndex; ++i)
						{
							Four[i] = Four[i + 1];
						}
						return 1;
					}
					else if (KingBoom > 0 && OneIndex < 3)
					{
						Out[0] = 17;
						Out[1] = 2;
						Out[2] = 4;
						KingBoom = 0;
						return 1;
					}
					else if (FourIndex > 0)
					{
						Out[0] = Four[0];
						Out[1] = 4;
						Out[2] = 4;
						FourIndex--;
						for (int i = 0; i < FourIndex; ++i)
						{
							Four[i] = Four[i + 1];
						}
						return 1;
					}
				}
				return -1;
			}
			else if (UpperCard[2] == 2)
			{
				for (int i = 0; i < deckTwoIndex; ++i)
				{
					if (deckTwo[i][0] > UpperCard[0] && deckTwo[i][1] == UpperCard[1])
					{
						if (WhoseOut == 1 && (DZIndex == -1 || deckTwo[i][0] > 9))
						{
							return -1;
						}
						Out[0] = deckTwo[i][0];
						Out[1] = deckTwo[i][1];
						Out[2] = 2;
						deckTwoIndex--;
						for (int j = i; j < deckTwoIndex; ++j)
						{
							deckTwo[j][0] = deckTwo[j + 1][0];
							deckTwo[j][1] = deckTwo[j + 1][1];
						}
						return 1;
					}
				}
				if (WhoseOut == 1 && (UpperCard[0] > 8 || behindN > 10 || UpperCard[1] > 3))
				{
					return -1;
				}
				for (int i = 0; i < deckTwoIndex; ++i)
				{
					if (deckTwo[i][0] > UpperCard[0] && deckTwo[i][1] == UpperCard[1] + 1)
					{
						int restTwo = deckTwo[i][0] + deckTwo[i][1] - 1;
						for (int k = TwoIndex; k > 0; --k)
						{
							//One[k-1] == restOne
							if (Two[k - 1] > restTwo)
							{
								Two[k] = Two[k - 1];
							}
							else
							{
								Two[k] = restTwo;
								break;
							}
						}
						TwoIndex++;
						Out[0] = deckTwo[i][0];
						Out[1] = deckTwo[i][1] - 1;
						Out[2] = 2;
						deckTwoIndex--;
						for (int j = i; j < deckTwoIndex; ++j)
						{
							deckTwo[j][0] = deckTwo[j + 1][0];
							deckTwo[j][1] = deckTwo[j + 1][1];
						}
						return 1;
					}
					else if (deckTwo[i][0] == UpperCard[0] && deckTwo[i][1] == UpperCard[1] + 1)
					{
						int restTwo = deckTwo[i][0];
						for (int k = TwoIndex; k > 0; --k)
						{
							//One[k-1] == restOne
							if (Two[k - 1] > restTwo)
							{
								Two[k] = Two[k - 1];
							}
							else
							{
								Two[k] = restTwo;
								break;
							}
						}
						TwoIndex++;
						Out[0] = deckTwo[i][0] + 1;
						Out[1] = deckTwo[i][1] - 1;
						Out[2] = 2;
						deckTwoIndex--;
						for (int j = i; j < deckTwoIndex; ++j)
						{
							deckTwo[j][0] = deckTwo[j + 1][0];
							deckTwo[j][1] = deckTwo[j + 1][1];
						}
						return 1;
					}
				}
				if (behindN < 5)
				{
					int boomtemp = -1;
					for (int i = 15; i > 2; i--)
					{
						if (elseCard[i] > 3)
						{
							boomtemp = i;
							break;
						}
					}
					if (boomtemp > 0 && FourIndex > 0)
					{
						Out[0] = Four[0];
						Out[1] = 4;
						Out[2] = 4;
						FourIndex--;
						for (int i = 0; i < FourIndex; ++i)
						{
							Four[i] = Four[i + 1];
						}
						return 1;
					}
					else if (KingBoom > 0 && OneIndex < 3)
					{
						Out[0] = 17;
						Out[1] = 2;
						Out[2] = 4;
						KingBoom = 0;
						return 1;
					}
					else if (FourIndex > 0)
					{
						Out[0] = Four[0];
						Out[1] = 4;
						Out[2] = 4;
						FourIndex--;
						for (int i = 0; i < FourIndex; ++i)
						{
							Four[i] = Four[i + 1];
						}
						return 1;
					}
				}
				return -1;
			}
			else if (UpperCard[2] == 3)
			{
				if (WhoseOut == 1 && (UpperCard[0] > 8 || behindN > 10 || UpperCard[1] > 2))
				{
					return -1;
				}
				bool IsRes = false;
				int chai = 0;
				int chaiThree;
				for (int i = 0; i < deckThreeIndex; ++i)
				{
					if (UpperCard[0] < deckThree[i][0] && UpperCard[1] <= deckThree[i][1])
					{
						Out[0] = deckThree[i][0];
						Out[1] = UpperCard[1];
						Out[2] = 3;
						deckThreeIndex--;
						if (deckThree[i][1] - UpperCard[1] >= 2)
						{
							chai = 1;
							deckThree[i][0] = deckThree[i][0] + UpperCard[1] - 1;
							deckThree[i][1] = deckThree[i][1] - UpperCard[1];
						}
						else
						{
							if (deckThree[i][1] - UpperCard[1] > 0)
							{
								chai = 2;
								for (int j = 0; j < ThreeIndex; j++)
								{
									if (Three[j] > Out[0])
									{
										for (int k = ThreeIndex; k > j; --k)
										{
											Three[k - 1 + deckThree[i][1] - UpperCard[1]] = Three[k - 1];
										}
										ThreeIndex += deckThree[i][1] - UpperCard[1];
										for (int k = 0; k < deckThree[i][1] - UpperCard[1]; ++k)
										{
											Three[j + k] = deckThree[i][0] + UpperCard[1] + k;
										}
										chaiThree = j;
										break;
									}
								}
							}
							for (int j = i; j < deckThreeIndex; ++j)
							{
								deckThree[j][0] = deckThree[j + 1][0];
								deckThree[j][1] = deckThree[j + 1][1];
							}
						}
						IsRes = true;
						break;
					}
				}
				if (IsRes == true)
				{
					if (UpperCard[4] == 2)//������
					{
						int temp = UpperCard[1];
						//���ţ����Գ�����UpperCard[1]
						if (TwoIndex >= UpperCard[1] && Two[UpperCard[1]] < 14)
						{
							Out[3] = Two[0];
							Out[4] = 2;
							for (int i = 1; i < temp; ++i)
							{
								Out[4 + i] = Two[i];
							}
							TwoIndex -= temp;
							for (int i = 0; i < TwoIndex; ++i)
							{
								Two[i] = Two[i + temp];
							}
							return 1;
						}
						else if (deckTwoIndex > 0)
						{
							for (int k = TwoIndex; k > 0; --k)
							{
								if (Two[k - 1] > deckTwo[0][0])
								{
									Two[k - 1 + deckTwo[0][1]] = Two[k - 1];
								}
								else
								{
									for (int j = 0; j < deckTwo[0][1]; j++)
									{
										Two[k + j] = deckTwo[0][0] + j;
									}
									break;
								}
							}
							TwoIndex += deckTwo[0][1];
							for (int i = 0; i < deckTwoIndex; ++i)
							{
								deckTwo[i][1] = deckTwo[i + 1][1];
								deckTwo[i][0] = deckTwo[i + 1][0];
							}
							deckTwoIndex--;
							Out[3] = Two[0];
							Out[4] = 2;
							for (int i = 1; i < Out[1]; i++)
							{
								Out[4 + i] = Two[i + 1];
							}
							for (int i = 0; i < TwoIndex; i++)
							{
								Two[i] = Two[i + Out[1]];
							}
							TwoIndex -= Out[1];
							return 1;
						}
						else
						{
							return -1;
						}
					}
					else if (UpperCard[4] == 1)
					{
						int temp = UpperCard[1];
						//
						if (OneIndex >= UpperCard[1] && One[UpperCard[1] - 1] < 16)
						{
							Out[3] = One[0];
							Out[4] = 1;
							for (int i = 1; i < temp; ++i)
							{
								Out[4 + i] = One[i];
							}
							OneIndex -= temp;
							for (int i = 0; i < OneIndex; ++i)
							{
								One[i] = One[i + temp];
							}
							return 1;
						}
						else
						{

						}
					}
				}
				if (behindN < 5)
				{
					int boomtemp = -1;
					for (int i = 15; i > 2; i--)
					{
						if (elseCard[i] > 3)
						{
							boomtemp = i;
							break;
						}
					}
					if (boomtemp > 0 && FourIndex > 0)
					{
						Out[0] = Four[0];
						Out[1] = 4;
						Out[2] = 4;
						FourIndex--;
						for (int i = 0; i < FourIndex; ++i)
						{
							Four[i] = Four[i + 1];
						}
						return 1;
					}
					else if (KingBoom > 0 && OneIndex < 3)
					{
						Out[0] = 17;
						Out[1] = 2;
						Out[2] = 4;
						KingBoom = 0;
						return 1;
					}
					else if (FourIndex > 0)
					{
						Out[0] = Four[0];
						Out[1] = 4;
						Out[2] = 4;
						FourIndex--;
						for (int i = 0; i < FourIndex; ++i)
						{
							Four[i] = Four[i + 1];
						}
						return 1;
					}
				}
				return -1;
			}
			else if (UpperCard[2] == 4)//  �Ĵ�2 //���Ż���Ŀǰֱ��ը//���Ĵ����ˣ�˵��ũ����̓�������߱�Ӯ�ˣ�����ֱ��ը��
			{
				if (UpperCard[0] == 17 || WhoseOut == 1)
				{
					return -1;
				}
				bool boom = false;
				bool ok = false;
				bool BB = false;
				if (FourIndex > 0)
				{
					boom = true;
				}
				if (UpperCard[4] == 1 && boom == true)
				{
					if (OneIndex > 1 && One[1] < 14)
					{
						Out[3] = One[0];
						Out[4] = 1;
						Out[5] = One[1];
						for (int i = 0; i < OneIndex; i++)
						{
							One[i] = One[i + 2];
						}
						OneIndex -= 2;
						ok = true;
					}
					else if (OneIndex == 1 && One[0] < 14)
					{
						if (TwoIndex > 0 && Two[0] < 14)
						{
							if (One[0] > Two[0])
							{
								Out[3] = Two[0];
								Out[4] = 1;
								Out[5] = Two[0];
								TwoIndex--;
								for (int i = 0; i < TwoIndex; i++)
								{
									Two[i] = Two[i + 1];
								}
								ok = true;
							}
							else
							{
								Out[3] = One[0];
								Out[4] = 1;
								Out[5] = Two[0];
								One[0] = Two[0];
								TwoIndex--;
								for (int i = 0; i < TwoIndex; i++)
								{
									Two[i] = Two[i + 1];
								}
								ok = true;
							}
						}
					}
					else if (TwoIndex > 0 && Two[0] < 14)
					{
						Out[3] = Two[0];
						Out[4] = 1;
						Out[5] = Two[0];
						TwoIndex--;
						for (int i = 0; i < TwoIndex; i++)
						{
							Two[i] = Two[i + 1];
						}
						ok = true;
					}
					else
					{

					}
				}
				else if (UpperCard[4] == 2 && boom == true)
				{
					if (TwoIndex > 1 && Two[1] < 14)
					{
						Out[3] = Two[0];
						Out[4] = 2;
						Out[5] = Two[1];
						TwoIndex -= 2;
						for (int i = 0; i < TwoIndex; i++)
						{
							Two[i] = Two[i + 2];
						}
						ok = true;
					}
				}
				else
				{
					BB = true;
				}
				if (ok == true || (BB == true && KingBoom == 0))
				{
					for (int i = 0; i < FourIndex; i++)
					{
						if (Four[i] > UpperCard[0])
						{
							Out[0] = Four[i];
							Out[1] = 4;
							Out[2] = 4;
							FourIndex--;
							for (int j = i; j < FourIndex; ++j)
							{
								Four[j] = Four[j + 1];
							}
						}
					}
					return 1;
				}
				if (KingBoom == 1)
				{
					Out[0] = 17;
					Out[1] = 2;
					Out[2] = 4;
					Out[3] = 0;
					Out[4] = 0;
					Out[5] = 0;
					KingBoom = 0;
					return 1;
				}
				if (FourIndex > 0 && UpperCard[4] > 0)
				{
					for (int i = 0; i < FourIndex; i++)
					{

						Out[0] = Four[i];
						Out[1] = 4;
						Out[2] = 4;
						Out[3] = 0;
						Out[4] = 0;
						Out[5] = 0;
						FourIndex--;
						for (int j = i; j < FourIndex; j++)
						{
							Four[j] = Four[j + 1];
						}
						return 1;
					}
				}
				return -1;
			}
			else
			{
				return -1;
			}
		}
	}
	return -1;
}

int card::ScoreOfDZ()//������������������������ 2 1 -1
{
	//�ӷ֣� ը�� ���˽Ӳ��ϵ��� > 2
	//���֣� С��10�� ������    С��5
	int ScoreDZ = 0;
	int J_A = 0;
	for (int i = 0; i < OneIndex; ++i)
	{
		if (One[i] < 11)
		{
			ScoreDZ--;
		}
		else if (One[i]<15)
		{
			J_A++;
		}
	}
	for (int i = 0; i < TwoIndex; ++i)
	{
		if (Two[i] < 11)
		{
			ScoreDZ--;
		}
		else if (Two[i]<15)
		{
			J_A++;
		}
	}
	//�ɻ����������Դ�
	for (int i = 0; i < deckThreeIndex; ++i)
	{
		ScoreDZ += deckThree[i][1];
	}
	ScoreDZ += ThreeIndex;
	//ȥ���Ƶ�Ȩֵ����������<=0
	if (ScoreDZ > 0)
	{
		ScoreDZ = 0;
	}
	// 2��С��1�֣�����2��ը��2�֣���ը3��
	int BigScore = myCard[15] + myCard[16] + myCard[17] * 2 + FourIndex * 2;
	if ((BigScore > 4 && ScoreDZ > -4) || (BigScore > 1 && ScoreDZ == 0))
	{
		return 2;
	}
	else if (ScoreDZ > -4 || BigScore >2)
	{
		return 1;
	}
	return -1;
}

bool card::CallDZ(int score, int MyScore)//������ȽУ���score=0,���������������ôscore=1;
{
	if (MyScore > score)
	{
		return true;
	}
	return false;
}

void card::CaLL(int I)
{
	if(I == 1)
	{
		IsDZ = true;
		myN = 20;
	}
	else if(I == -1)
	{
		IsDZ = false;
		frontN = 20;
		DZIndex = -1;
		IsGoodNM();
	}
	else
	{
		IsDZ = false;
		behindN = 20;
		DZIndex = 2;
		IsGoodNM();
	}
}
/*
��������
*/
int card::GetBestSort(int x)
{
	int BestS = 0;
	bool flag = false;
	if (DZIndex == 1 && (frontN == 1 || behindN == 1))
	{
		flag = true;
	}
	else if ((DZIndex == 2 && behindN == 1) || (DZIndex == -1 && frontN == 1))
	{
		flag = true;
	}
	//i.	����ը���������ɻ�����������������˫˳������˳��, ˳�ӵ���,
	if(x==1)
	{
		int indexDeck = 0;
		int Cards[60];//���ƻ�ԭ�����飬���ȷ����ı�
		memcpy(Cards, myCard, sizeof(myCard));
		//������ͣ�ɢ��+1����ը��ը��-2,��С��-1���ɻ�-1����«-2
		int result[60]; int Sum;//�����¼
		//��ը
		if (Cards[16] && Cards[17])
		{
			BestS -= 2;
			Cards[16] = Cards[17] = 0;
		}
		//$��С��
		else if (Cards[16] || Cards[17])
		{
			BestS -= 1;
			Cards[16] = Cards[17] = 0;
		}
		//*********************��ʼ����***********************//
		//boom
		for (int i = 3; i < 16; ++i)
		{
			if (Cards[i] == 4)
			{
				BestS -= 2;
				Cards[i] = 0;
			}
		}
		SerchTheProgression(3, Cards, result, &Sum);//���ҷɻ�������sum
		for (int i = 0; i < Sum; ++i)
		{
			BestS -= result[i*3+1];
		}
		//
		for (int i = 3; i < 18; ++i)
		{
			if (Cards[i] == 3)//���к�«Ŷ
			{
				Cards[i] = 0;
				BestS -=1;
			}
		}
		//����
		SerchTheProgression(2, Cards, result, &Sum);
		//˳��
		SerchTheProgression(1, Cards, result, &Sum);
		//����
		for (int i = 3; i < 15; ++i)
		{
			if (Cards[i] == 1 && i < 14)
			{
				BestS += 1;
			}
			else if (Cards[i] == 2 && flag == false && i < 13)
			{
				BestS += 1;
			}
		}
	}
	//ii.	����˳�ӣ�˳�ӵ���, ����ը���������ɻ�������˫˳, ��������
	else if(x==2)
	{
		int indexDeck = 0;
		int Cards[60];//���ƻ�ԭ�����飬���ȷ����ı�
		memcpy(Cards, myCard, sizeof(myCard));
		//������ͣ�ɢ��+1����ը��ը��-2,��С��-1���ɻ�-1����«-2
		int result[60]; int Sum;//�����¼
		//��ը
		if (Cards[16] && Cards[17])
		{
			BestS -= 2;
			Cards[16] = Cards[17] = 0;
		}
		//��С��
		else if (Cards[16] || Cards[17])
		{
			BestS -= 1;
			Cards[16] = Cards[17] = 0;
		}
		//*********************��ʼ����***********************//
		//1
		SerchTheProgression(1, Cards, result, &Sum);
		//boom
		for (int i = 3; i < 16; ++i)
		{
			if (Cards[i] == 4)
			{
				BestS -= 2;
				Cards[i] = 0;
			}
		}
		//feiji
		SerchTheProgression(3, Cards, result, &Sum);
		for (int i = 0; i < Sum; ++i)
		{
			BestS -= result[i*3+1];
		}
		//2
		SerchTheProgression(2, Cards, result, &Sum);
		//����
		for (int i = 3; i < 18; ++i)
		{
			if (Cards[i] == 1 && i < 14)
			{
				BestS += 1;
			}
			else if (Cards[i] == 2 && flag == false && i < 13)
			{
				BestS += 1;
			}
			else if(Cards[i] == 3)
			{
				BestS -=1;
			}
		}
	}
	//iii.	����ը���������ɻ�����������������˳��, ˳�ӵ���, ����˫˳
	else if(x==3)
	{
		int indexDeck = 0;
		int Cards[60];//���ƻ�ԭ�����飬���ȷ����ı�
		memcpy(Cards, myCard, sizeof(myCard));
		//������ͣ�ɢ��+1����ը��ը��-2,��С��-1���ɻ�-1����«-2
		int result[60]; int Sum;//�����¼
		//��ը
		if (Cards[16] && Cards[17])
		{
			BestS -= 2;
			Cards[16] = Cards[17] = 0;
		}
		//$��С��
		else if (Cards[16] || Cards[17])
		{
			BestS -= 1;
			Cards[16] = Cards[17] = 0;
		}
		//*********************��ʼ����***********************//
		//boom
		for (int i = 3; i < 16; ++i)
		{
			if (Cards[i] == 4)
			{
				BestS -= 2;
				Cards[i] = 0;
			}
		}
		//feiji
		SerchTheProgression(3, Cards, result, &Sum);
		for (int i = 0; i < Sum; ++i)
		{
			BestS -= result[i*3+1];
		}
		//
		for (int i = 3; i < 18; ++i)
		{
			if (Cards[i] == 3)//����0Ŷ
			{
				Cards[i] = 0;
				BestS -=1;
			}
		}
		//1
		SerchTheProgression(1, Cards, result, &Sum);
		//2
		SerchTheProgression(2, Cards, result, &Sum);
		//����
		for (int i = 3; i < 18; ++i)
		{
			if (Cards[i] == 1 && i < 14)
			{
				BestS += 1;
			}
			else if (Cards[i] == 2 && flag == false && i < 13)
			{
				BestS += 1;
			}
		}
	}
	//iv.	����ը��������˳��, ˳�ӵ���, ����˫˳, �����ɻ�������������
	else if (x == 4)
	{
		int indexDeck = 0;
		int Cards[60];//���ƻ�ԭ�����飬���ȷ����ı�
		memcpy(Cards, myCard, sizeof(myCard));
		//������ͣ�ɢ��+1����ը��ը��-2,��С��-1���ɻ�-1����«-2
		int result[60]; int Sum;//�����¼
								//��ը
		if (Cards[16] && Cards[17])
		{
			BestS -= 2;
			Cards[16] = Cards[17] = 0;
		}
		//$��С��
		else if (Cards[16] || Cards[17])
		{
			BestS -= 1;
			Cards[16] = Cards[17] = 0;
		}
		//*********************��ʼ����***********************//
		//boom
		for (int i = 3; i < 16; ++i)
		{
			if (Cards[i] == 4)
			{
				BestS -= 2;
				Cards[i] = 0;
			}
		}
		//feiji
		//1
		SerchTheProgression(1, Cards, result, &Sum);
		//2
		SerchTheProgression(2, Cards, result, &Sum);
		//����
		SerchTheProgression(3, Cards, result, &Sum);
		for (int i = 0; i < Sum; ++i)
		{
			BestS -= result[i * 3 + 1];
		}
		//
		for (int i = 3; i < 18; ++i)
		{
			if (Cards[i] == 3)//����0Ŷ
			{
				Cards[i] = 0;
				BestS -= 1;
			}
			
		}
		for (int i = 3; i < 18; ++i)
		{
			if (Cards[i] == 1 && i < 14)
			{
				BestS += 1;
			}
			else if (Cards[i] == 2 && flag == false && i < 13)
			{
				BestS += 1;
			}
		}
	}
	//ը����˳�ӣ��ɻ���������˫˳
	else if (x == 5)
	{
		int indexDeck = 0;
		int Cards[60];//���ƻ�ԭ�����飬���ȷ����ı�
		memcpy(Cards, myCard, sizeof(myCard));
		//������ͣ�ɢ��+1����ը��ը��-2,��С��-1���ɻ�-1����«-2
		int result[60]; int Sum;//�����¼
								//��ը
		if (Cards[16] && Cards[17])
		{
			BestS -= 2;
			Cards[16] = Cards[17] = 0;
		}
		//��С��
		else if (Cards[16] || Cards[17])
		{
			BestS -= 1;
			Cards[16] = Cards[17] = 0;
		}
		//*********************��ʼ����***********************//
		for (int i = 3; i < 16; ++i)
		{
			if (Cards[i] == 4)
			{
				BestS -= 2;
				Cards[i] = 0;
			}
		}
		//1
		SerchTheProgression(1, Cards, result, &Sum);
		//feiji
		SerchTheProgression(3, Cards, result, &Sum);
		for (int i = 0; i < Sum; ++i)
		{
			BestS -= result[i * 3 + 1];
		}
		for (int i = 3; i < 18; ++i)
		{
			if (Cards[i] == 3)//����0Ŷ
			{
				Cards[i] = 0;
				BestS -= 1;
			}
		}
		//2
		SerchTheProgression(2, Cards, result, &Sum);
		//����
		for (int i = 3; i < 18; ++i)
		{
			if (Cards[i] == 1 && i < 14)
			{
				BestS += 1;
			}
			else if (Cards[i] == 2 && flag == false && i < 13)
			{
				BestS += 1;
			}
		}
	}
	//ը�����ɻ���˫˳��˳��,������
	else if (x == 6)
	{
		int indexDeck = 0;
		int Cards[60];//���ƻ�ԭ�����飬���ȷ����ı�
		memcpy(Cards, myCard, sizeof(myCard));
		//������ͣ�ɢ��+1����ը��ը��-2,��С��-1���ɻ�-1����«-2
		int result[60]; int Sum;//�����¼
								//��ը
		if (Cards[16] && Cards[17])
		{
			BestS -= 2;
			Cards[16] = Cards[17] = 0;
		}
		//��С��
		else if (Cards[16] || Cards[17])
		{
			BestS -= 1;
			Cards[16] = Cards[17] = 0;
		}
		//*********************��ʼ����***********************//
		for (int i = 3; i < 16; ++i)
		{
			if (Cards[i] == 4)
			{
				BestS -= 2;
				Cards[i] = 0;
			}
		}
		//1
		//feiji
		SerchTheProgression(3, Cards, result, &Sum);
		for (int i = 0; i < Sum; ++i)
		{
			BestS -= result[i * 3 + 1];
		}
		SerchTheProgression(2, Cards, result, &Sum);
		SerchTheProgression(1, Cards, result, &Sum);
		for (int i = 3; i < 18; ++i)
		{
			if (Cards[i] == 3)//����0Ŷ
			{
				Cards[i] = 0;
				BestS -= 1;
			}
		}
		//2
		
		//����
		for (int i = 3; i < 18; ++i)
		{
			if (Cards[i] == 1 && i < 14)
			{
				BestS += 1;
			}
			else if (Cards[i] == 2 && flag == false && i < 13)
			{
				BestS += 1;
			}
		}
	}

	return BestS;
}

int card::SortTheCard()//���� Ŀǰ����ը ը�� ��˳ ��˳ ����
{
	KingBoom = 0;//��ը
	deckIndex = 0; //�������� ����㣬��������ǩ ��1��2��3Ϊ˳�ӡ����ԡ��ɻ���4Ϊը����0Ϊɢ�ƣ�
	deckTwoIndex = 0;
	deckThreeIndex = 0;
	OneIndex = 0;//����
	OneMaxIndex = 0;
	OneElseMax = 0;
	TwoIndex = 0;//˫��
	TwoMaxIndex = 0;
	TwoElseMax = 0;
	ThreeIndex = 0;//����ͷ
	ThreeMaxIndex = 0;
	ThreeElseMax = 0;
	FourIndex = 0;//ը��
	int indexDeck = 0;
	int Cards[60];//���ƻ�ԭ�����飬���ȷ����ı�
	memcpy(Cards, myCard, sizeof(myCard));
	//������ͣ�ɢ��+1����ը��ը��-2,��С��-1���ɻ�-1����«-2
	int result[60]; int Sum;//�����¼
	//*********************************//
	int s1 = GetBestSort(1); //cout << "s1:" << s1 << endl;
	int s2 = GetBestSort(2); //cout << "s2:" << s2 << endl;
	int s3 = GetBestSort(3); //cout << "s3:" << s3 << endl;
	int s4 = GetBestSort(4); //cout << "s4:" << s4 << endl;
	int s5 = GetBestSort(5); //cout << "s5:" << s5 << endl;
	int s6 = GetBestSort(6); //cout << "s6:" << s6 << endl;
	int s; 
	if (s4 <= s2 && s4 <= s1 && s4 <= s3 && s4 <= s5 && s4 <= s6)
	{
		s = 4;
	}
	else if (s3 <= s2 && s3 <= s1 && s3 <= s4 && s3 <= s5 && s3 <= s6)
	{
		s = 3;
	}
	else if (s1 <= s3 && s1 <= s2 && s1 <= s4 && s1 <= s5 && s1 <= s6)
	{
		s = 1;
	}
	else if (s5 <= s3 && s5 <= s1 && s5 <= s4 && s5 <= s2 && s5 <= s6)
	{
		s = 5;
	}
	else if (s6 <= s3 && s6 <= s1 && s6 <= s4 && s6 <= s5 && s6 <= s2)
	{
		s = 6;
	}
	else
	{
		s = 2;
	}
	//cout << s << endl;
	//**********************************//
	if (s == 1)//����ը���������ɻ�����������������˫˳������˳��, ˳�ӵ���,
	{
		//��ը
		if (Cards[16] && Cards[17])
		{
			KingBoom = 1;
			Cards[16] = Cards[17] = 0;
		}
		//*********************��ʼ����***********************//
		// ը�����ɻ���˳�ӡ�����
		for (int i = 3; i < 16; ++i)
		{
			if (Cards[i] == 4)
			{
				Four[FourIndex] = i;//��ǰֻ��һ�������ֱ�Ӹ�ֵ
				FourIndex++;
				Cards[i] = 0;
			}
		}
		//3
		SerchTheProgression(3, Cards, result, &Sum);
		for (int i = 0; i < Sum; ++i)
		{
			deckThree[deckThreeIndex][0] = result[i * 3];
			deckThree[deckThreeIndex][1] = result[i * 3 + 1];
			deckThreeIndex++;
		}
		//333
		for (int i = 3; i < 18; ++i)
		{
			if (Cards[i] == 3)//����0Ŷ
			{
				Three[ThreeIndex++] = i;
				Cards[i] = 0;
			}
		}
		//2
		SerchTheProgression(2, Cards, result, &Sum);
		for (int i = 0; i < Sum; ++i)
		{
			deckTwo[deckTwoIndex][0] = result[i * 3];
			deckTwo[deckTwoIndex][1] = result[i * 3 + 1];
			deckTwoIndex++;
		}
		//1
		SerchTheProgression(1, Cards, result, &Sum);
		for (int i = 0; i < Sum; ++i)
		{
			deck[deckIndex][0] = result[i * 3];
			deck[deckIndex][1] = result[i * 3 + 1];
			deckIndex++;
		}
		//����
		for (int i = 3; i < 18; ++i)
		{
			if (Cards[i] == 1)
			{
				One[OneIndex++] = i;
			}
			else if (Cards[i] == 2)
			{
				Two[TwoIndex++] = i;
			}
		}
	}
	else if (s == 2)
	{
		//��ը
		if (Cards[16] && Cards[17])
		{
			KingBoom = 1;
			Cards[16] = Cards[17] = 0;
		}
		//*********************��ʼ����***********************//
		//1
		SerchTheProgression(1, Cards, result, &Sum);
		for (int i = 0; i < Sum; ++i)
		{
			deck[deckIndex][0] = result[i * 3];
			deck[deckIndex][1] = result[i * 3 + 1];
			deckIndex++;
		}
		// ը�����ɻ���˳�ӡ�����
		for (int i = 3; i < 16; ++i)
		{
			if (Cards[i] == 4)
			{
				Four[FourIndex] = i;//��ǰֻ��һ�������ֱ�Ӹ�ֵ
				FourIndex++;
				Cards[i] = 0;
			}
		}
		//3
		SerchTheProgression(3, Cards, result, &Sum);
		for (int i = 0; i < Sum; ++i)
		{
			deckThree[deckThreeIndex][0] = result[i * 3];
			deckThree[deckThreeIndex][1] = result[i * 3 + 1];
			deckThreeIndex++;
		}
		//2
		SerchTheProgression(2, Cards, result, &Sum);
		for (int i = 0; i < Sum; ++i)
		{
			deckTwo[deckTwoIndex][0] = result[i * 3];
			deckTwo[deckTwoIndex][1] = result[i * 3 + 1];
			deckTwoIndex++;
		}
		//����
		for (int i = 3; i < 18; ++i)
		{
			if (Cards[i] == 1)
			{
				One[OneIndex++] = i;
			}
			else if (Cards[i] == 2)
			{
				Two[TwoIndex++] = i;
			}
			else if (Cards[i] == 3)//����0Ŷ
			{
				Three[ThreeIndex++] = i;
			}
		}
	}
	else if (s == 3)
	{
		//��ը
		if (Cards[16] && Cards[17])
		{
			KingBoom = 1;
			Cards[16] = Cards[17] = 0;
		}
		//*********************��ʼ����***********************//
		// ը�����ɻ���˳�ӡ�����
		for (int i = 3; i < 16; ++i)
		{
			if (Cards[i] == 4)
			{
				Four[FourIndex] = i;//��ǰֻ��һ�������ֱ�Ӹ�ֵ
				FourIndex++;
				Cards[i] = 0;
			}
		}
		//3
		SerchTheProgression(3, Cards, result, &Sum);
		for (int i = 0; i < Sum; ++i)
		{
			deckThree[deckThreeIndex][0] = result[i * 3];
			deckThree[deckThreeIndex][1] = result[i * 3 + 1];
			deckThreeIndex++;
		}
		for (int i = 3; i < 18; ++i)
		{
			if (Cards[i] == 3)//����0Ŷ
			{
				Three[ThreeIndex++] = i;
				Cards[i]=0;
			}
		}
		//1
		SerchTheProgression(1, Cards, result, &Sum);
		for (int i = 0; i < Sum; ++i)
		{
			deck[deckIndex][0] = result[i * 3];
			deck[deckIndex][1] = result[i * 3 + 1];
			deckIndex++;
		}
		//2
		SerchTheProgression(2, Cards, result, &Sum);
		for (int i = 0; i < Sum; ++i)
		{
			deckTwo[deckTwoIndex][0] = result[i * 3];
			deckTwo[deckTwoIndex][1] = result[i * 3 + 1];
			deckTwoIndex++;
		}
		//����
		for (int i = 3; i < 18; ++i)
		{
			if (Cards[i] == 1)
			{
				One[OneIndex++] = i;
			}
			else if (Cards[i] == 2)
			{
				Two[TwoIndex++] = i;
			}
		}
	}
	else if (s == 4)
	{
		//ix.	����ը��������˳��, ˳�ӵ���, ����˫˳,�����ɻ�������������
		//��ը
		if (Cards[16] && Cards[17])
		{
			KingBoom = 1;
			Cards[16] = Cards[17] = 0;
		}
		//*********************��ʼ����***********************//
		// ը�����ɻ���˳�ӡ�����
		for (int i = 3; i < 16; ++i)
		{
			if (Cards[i] == 4)
			{
				Four[FourIndex] = i;//��ǰֻ��һ�������ֱ�Ӹ�ֵ
				FourIndex++;
				Cards[i] = 0;
			}
		}
		//1
		SerchTheProgression(1, Cards, result, &Sum);
		for (int i = 0; i < Sum; ++i)
		{
			deck[deckIndex][0] = result[i * 3];
			deck[deckIndex][1] = result[i * 3 + 1];
			deckIndex++;
		}
		//2
		SerchTheProgression(2, Cards, result, &Sum);
		for (int i = 0; i < Sum; ++i)
		{
			deckTwo[deckTwoIndex][0] = result[i * 3];
			deckTwo[deckTwoIndex][1] = result[i * 3 + 1];
			deckTwoIndex++;
		}
		//3
		SerchTheProgression(3, Cards, result, &Sum);
		for (int i = 0; i < Sum; ++i)
		{
			deckThree[deckThreeIndex][0] = result[i * 3];
			deckThree[deckThreeIndex][1] = result[i * 3 + 1];
			deckThreeIndex++;
		}
		for (int i = 3; i < 18; ++i)
		{
			if (Cards[i] == 3)//����0Ŷ
			{
				Three[ThreeIndex++] = i;
				Cards[i] = 0;
			}
		}
		//����
		for (int i = 3; i < 18; ++i)
		{
			if (Cards[i] == 1)
			{
				One[OneIndex++] = i;
			}
			else if (Cards[i] == 2)
			{
				Two[TwoIndex++] = i;
			}
		}
	}
	else if (s == 5)
	{
		//ix.	����ը��������˳��, ˳�ӵ���, ����˫˳,�����ɻ�������������
		//��ը
		if (Cards[16] && Cards[17])
		{
			KingBoom = 1;
			Cards[16] = Cards[17] = 0;
		}
		//*********************��ʼ����***********************//
		// ը�����ɻ���˳�ӡ�����
		for (int i = 3; i < 16; ++i)
		{
			if (Cards[i] == 4)
			{
				Four[FourIndex] = i;//��ǰֻ��һ�������ֱ�Ӹ�ֵ
				FourIndex++;
				Cards[i] = 0;
			}
		}
		//1
		SerchTheProgression(1, Cards, result, &Sum);
		for (int i = 0; i < Sum; ++i)
		{
			deck[deckIndex][0] = result[i * 3];
			deck[deckIndex][1] = result[i * 3 + 1];
			deckIndex++;
		}
		SerchTheProgression(3, Cards, result, &Sum);
		for (int i = 0; i < Sum; ++i)
		{
			deckThree[deckThreeIndex][0] = result[i * 3];
			deckThree[deckThreeIndex][1] = result[i * 3 + 1];
			deckThreeIndex++;
		}
		for (int i = 3; i < 18; ++i)
		{
			if (Cards[i] == 3)//����0Ŷ
			{
				Three[ThreeIndex++] = i;
				Cards[i] = 0;
			}
		}
		//2
		SerchTheProgression(2, Cards, result, &Sum);
		for (int i = 0; i < Sum; ++i)
		{
			deckTwo[deckTwoIndex][0] = result[i * 3];
			deckTwo[deckTwoIndex][1] = result[i * 3 + 1];
			deckTwoIndex++;
		}
		//����
		for (int i = 3; i < 18; ++i)
		{
			if (Cards[i] == 1)
			{
				One[OneIndex++] = i;
			}
			else if (Cards[i] == 2)
			{
				Two[TwoIndex++] = i;
			}
		}
	}
	else if (s == 6)
	{
		//ix.	����ը��������˳��, ˳�ӵ���, ����˫˳,�����ɻ�������������
		//��ը
		if (Cards[16] && Cards[17])
		{
			KingBoom = 1;
			Cards[16] = Cards[17] = 0;
		}
		//*********************��ʼ����***********************//
		// ը�����ɻ���˳�ӡ�����
		for (int i = 3; i < 16; ++i)
		{
			if (Cards[i] == 4)
			{
				Four[FourIndex] = i;//��ǰֻ��һ�������ֱ�Ӹ�ֵ
				FourIndex++;
				Cards[i] = 0;
			}
		}
		//3
		SerchTheProgression(3, Cards, result, &Sum);
		for (int i = 0; i < Sum; ++i)
		{
			deckThree[deckThreeIndex][0] = result[i * 3];
			deckThree[deckThreeIndex][1] = result[i * 3 + 1];
			deckThreeIndex++;
		}
		//2
		SerchTheProgression(2, Cards, result, &Sum);
		for (int i = 0; i < Sum; ++i)
		{
			deckTwo[deckTwoIndex][0] = result[i * 3];
			deckTwo[deckTwoIndex][1] = result[i * 3 + 1];
			deckTwoIndex++;
		}
		SerchTheProgression(1, Cards, result, &Sum);
		for (int i = 0; i < Sum; ++i)
		{
			deck[deckIndex][0] = result[i * 3];
			deck[deckIndex][1] = result[i * 3 + 1];
			deckIndex++;
		}
		for (int i = 3; i < 18; ++i)
		{
			if (Cards[i] == 3)//����0Ŷ
			{
				Three[ThreeIndex++] = i;
				Cards[i] = 0;
			}
		}
		//1
		
		//����
		for (int i = 3; i < 18; ++i)
		{
			if (Cards[i] == 1)
			{
				One[OneIndex++] = i;
			}
			else if (Cards[i] == 2)
			{
				Two[TwoIndex++] = i;
			}
		}
	}
	//**************************���ƽ���*********************//
	//�ҳ������
	//�������
	int maxOneRest = 0, maxTwoRest = 0, maxThreeRest = 0;
	for (int i = 3; i < 18; ++i)
	{
		if (elseCard[i] > 2)
		{
			if (i > maxThreeRest)
			{
				maxThreeRest = i;
			}
			if (i > maxTwoRest)
			{
				maxTwoRest = i;
			}
			if (i > maxOneRest)
			{
				maxOneRest = i;
			}
		}
		else if (elseCard[i] > 1)
		{
			if (i > maxTwoRest)
			{
				maxTwoRest = i;
			}
			if (i > maxOneRest)
			{
				maxOneRest = i;
			}
		}
		else if (elseCard[i] > 0)
		{
			if (i > maxOneRest)
			{
				maxOneRest = i;
			}
		}
	}
	//�������
	OneElseMax = maxOneRest;
	TwoElseMax = maxTwoRest;
	ThreeElseMax = maxThreeRest;
	for (int i = 0; i < OneIndex; ++i)
	{
		if (One[i] >= maxOneRest)
		{
			OneMax[OneMaxIndex++] = One[i];
		}
	}
	for (int i = 0; i < TwoIndex; ++i)
	{
		if (Two[i] >= maxTwoRest)
		{
			TwoMax[TwoMaxIndex++] = Two[i];
		}
	}
	for (int i = 0; i < ThreeIndex; ++i)
	{
		if (Three[i] >= maxThreeRest)
		{
			ThreeMax[ThreeMaxIndex++] = One[i];
		}
	}
	/*for (int i = 3; i < 18; i++)
	{
		if (myCard[i] > 0)
		{
			cout << i << " :" << myCard[i] << endl;
		}
	}*/
	return 0;
}

void card::IsGoodNM()
{
	int temp = FourIndex + KingBoom + ThreeIndex;
	for (int i = 0; i < OneIndex; ++i)
	{
		if (One[i] < OneElseMax)
		{
			temp--;
		}
		else
		{
			temp++;
		}
	}
	for (int i = 0; i < TwoIndex; ++i)
	{
		if (Two[i] < TwoElseMax)
		{
			temp--;
		}
		else
		{
			temp++;
		}
	}
	for (int i = 0; i < deckThreeIndex; ++i)
	{
		temp += deckThree[i][1];
	}
	if (temp > -3)
	{
		GoodNM = true;
	}
	else
	{
		GoodNM = false;
	}
}

void card::SerchTheProgression(int LengthOfPg, int *Cards, int * result, int * Sum)//�ҳ���ΪLengthOfPg��˳�ӣ��ɻ�����Ϊ3������2Ϊ����
{
	//���
	int res[30][2];
	//�涨˳�ӵĹ���
	int LofPg = 5, NofC = 1;
	if (LengthOfPg == 2)
	{
		LofPg = 3, NofC = 2;
	}
	else if (LengthOfPg == 3)
	{
		LofPg = 2, NofC =3;
	}
	//��ʼ
	int startP = 3, resCount = 0;
	//  ��̵�˳��
	for (int i = 3; i < 16 - LofPg; ++i)//���һ˳��10��ʼ
	{
		if (Cards[i] >= NofC)//˳�����
		{
			int endP = i;
			for (int j = 1; j < LofPg; ++j)
			{
				if (Cards[i + j] < NofC)
				{
					endP = i + j;
					break;
				}
			}
			if (endP != i)//�м���ϣ��Ӹ���֮����������¿�ʼ����
			{
				i = endP;
				//cout << i << endl;
			}
			else
			{
				for (int k = 0; k < LofPg; k++)//��ȡ���飬��������1
				{
					Cards[i + k] -= NofC;
				}
				//��¼˳�ӽ��
				res[resCount][0] = i;
				res[resCount][1] = LofPg;
				//cout << res[resCount][0] << ' ' << res[resCount][1] << endl;
				resCount++;
				i--;//i��ͷ���ƿ��ܲ�ֹһ˳
			}
		}
	}
	//��ʣ�µ��ƹ��˳����
	for (int i = 0; i < resCount; ++i)
	{
		int temp = res[i][0] + LofPg;
		for (int k = temp; k < 15; ++k)//��ൽA
		{
			if (Cards[k] == NofC)
			{
				Cards[k] -= NofC;
				res[i][1]++;
			}
			else
			{
				break;
			}
		}
	}
	//����Ƿ��ܰ�˳�Ӻϲ�
	int resNumber = resCount;
	for (int i = 0; i < resCount; ++i)
	{
		if (res[i][0] != -1)//�Ѿ����ϲ�
		{
			for (int j = i + 1; j < resCount; ++j)
			{
				if (res[j][0] != -1 && res[j][0] == res[i][0] + res[i][1])
				{
					res[j][0] = -1;
					res[i][1] += res[j][1];
					resNumber--;
				}
			}
		}	
	}
	//���ؽ��
	for (int i = 0; i < resCount; ++i)
	{
		if (res[i][0] != -1)
		{
			result[3 * i] = res[i][0];//��һ��
			result[3 * i + 1] = res[i][1];//����
			result[3 * i + 2] = LengthOfPg;//���� 2˳
		}
	}
	*Sum = resNumber;
}
/*
������ʾ
Out[0] �����һ����
Out[1] �����һ���Ƶ�����
Out[2] ������Ƶ����࣬0���������ƣ����ţ����ӣ����ţ�1��˳�ӣ�2��˫˳��3���ɻ���4��ը����ը
Out[4] �����ܴ������ƣ�������������
Out[3][5][6][... ] Ϊ�����ƵĴ�С
*/
void card::Sort(int * Out, vector<int> &vc)
{
	if (Out[2] == 0)
	{		
		cout << "����";
		for (int i = 0; i < Out[1]; ++i)
		{
			vc.push_back(Out[0]);
		}
		if (Out[1] == 3 && Out[4] > 0)
		{
			for (int i = 0; i < Out[4]; i++)
			{
				vc.push_back(Out[3]);
			}
		}
	}
			//˳��
	else if (Out[2] == 1)
	{
		for (int i = 0; i < Out[1]; ++i)
		{
			vc.push_back(Out[0] + i);
		}
	}
			//2˳
	else if (Out[2] == 2)
	{
		for (int i = 0; i < Out[1]; ++i)
		{
			vc.push_back(Out[0] + i);
			vc.push_back(Out[0] + i);
		}
	}
		//�ɻ�
	else if (Out[2] == 3)
	{
		for (int i = 0; i < Out[1]; ++i)
		{
			vc.push_back(Out[0] + i);
			vc.push_back(Out[0] + i);
			vc.push_back(Out[0] + i);
		}
		if (Out[4] > 0)
		{
			if (Out[4] > 1)
			{
				vc.push_back(Out[3]);
			}
			vc.push_back(Out[3]);
			for (int i = 1; i < Out[1]; ++i)
			{
				for (int j = 0; j < Out[4]; ++j)
				{
					vc.push_back(Out[4 + i]);
				}
			}
		}
	}
		//ը��
	else
	{
		if (Out[0] == 17 && Out[2] == 4)
		{
			vc.push_back(16);
			vc.push_back(17);
		}
		else
		{
			for (int i = 0; i < 4; ++i)
			{
				vc.push_back(Out[0]);
			}
			if (Out[4] > 0)
			{
				for (int i = 0; i < Out[4]; ++i)
				{
					vc.push_back(Out[3]);
				}
				for (int i = 0; i < Out[4]; ++i)
				{
					vc.push_back(Out[5]);
				}
			}
		}
	}
	return;
}
#endif
//over//���ڸ�����